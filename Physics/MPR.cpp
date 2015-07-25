#include "MPR.h"

#include <Components/Transform.h>
#include <Physics/Collider.h>
#include <GameObject.h>

using namespace walt;
using namespace glm;

const int OuterIterationLimit = 15;
const float MinCollisionDepth = 0.1f;
const float CollideEpsilon = 1e-3f;

MPR::MPR()
{
}

MPR::~MPR()
{
}

bool MPR::FindCollision(Collider& a, Collider& b, vec3& pointA, vec3& pointB, vec3&normal)
{/*
    a.transform->position = vec3(0, 0, 0);
    a.transform->rotation = quat();
    a.transform->scaling = vec3(1);

    b.transform->position = vec3(0, 0.4f, 0);
    b.transform->rotation = quat();
    b.transform->scaling = vec3(1);*/

    // v0 = center of Minkowski sum
    auto v01 = a.transform->position();
    auto v02 = b.transform->position();
    auto v0 = v02 - v01;

    // Avoid case where centers overlap -- any direction is fine in this case
    if (IsZero(v0)) v0 = vec3(0.00001f, 0, 0);

    // v1 = support in direction of origin
    auto n1 = -v0;
    vec3 v11 = a.findSupport(v0);
    vec3 v12 = b.findSupport(n1);
    auto v1 = v12 - v11;

    if (dot(v1, n1) <= 0)
    {
        normal = n1;
        return false;
    }

    // v2 - support perpendicular to v1,v0
    auto n2 = cross(v1, v0);
    if (IsZero(n2))
    {
        n2 = v1 - v0;
        n2 = normalize(n2);
        normal = n2;
        pointA = v11;
        pointB = v12;
        return true;
    }

    auto tmp = -n2;
    vec3 v21 = a.findSupport(tmp);
    vec3 v22 = b.findSupport(n2);
    auto v2 = v22 - v21;

    if (dot(v2, n2) <= 0)
    {
        normal = n2;
        return false;
    }

    // Determine whether origin is on + or - side of plane (v1,v0,v2)
    auto n3 = cross(v1 - v0, v2 - v0);
    auto dist = dot(n3, v0);

    if (IsZero(n3))
    {
        tmp = -n1;
        v11 = a.findSupport(tmp);
        v12 = b.findSupport(n1);
        v1 = v12 - v11;
        tmp = -n2;
        v21 = a.findSupport(tmp);
        v22 = b.findSupport(n2);
        v2 = v22 - v21;
    }
    assert(!IsZero(n3));

    // If the origin is on the - side of the plane, reverse the direction of the plane
    if (dist > 0)
    {
        auto tmp = v1;
        v1 = v2;
        v2 = tmp;

        tmp = v11;
        v11 = v21;
        v21 = tmp;

        tmp = v12;
        v12 = v22;
        v22 = tmp;

        n3 = -n3;
    }

    //
    // Phase One: Identify a portal

    for (;;)
    {
        // Obtain the support point in a direction perpendicular to the existing plane
        // Note: This point is guaranteed to lie off the plane
        tmp = -n3;
        vec3 v31 = a.findSupport(tmp);
        vec3 v32 = b.findSupport(n3);
        auto v3 = v32 - v31;

        if (dot(v3, n3) <= 0)
        {
            normal = n3;
            return false;
        }

        // If origin is outside (v1,v0,v3), then eliminate v2 and loop
        if (dot(cross(v1, v3), v0) < 0)
        {
            v2 = v3;
            v21 = v31;
            v22 = v32;
            n3 = cross(v1 - v0, v3 - v0);
            continue;
        }

        // If origin is outside (v3,v0,v2), then eliminate v1 and loop
        if (dot(cross(v3, v2), v0) < 0)
        {
            v1 = v3;
            v11 = v31;
            v12 = v32;
            n3 = cross(v3 - v0, v2 - v0);
            continue;
        }

        auto hit = false;

        //
        // Phase Two: Refine the portal

        auto phase2 = 0;

        // We are now inside of a wedge...
        for (;;)
        {
            phase2++;
            if (phase2 > 1)
            {
                //TODO
                bool doneIt = false;
                auto trackingOn = true;
                if (!trackingOn && !doneIt)
                {
                    doneIt = true;
                    return false;
                }
            }

            // Compute normal of the wedge face
            auto n4 = cross(v2 - v1, v3 - v1);

            // Can this happen???  Can it be handled more cleanly?
            if (IsZero(n4))
            {
                //TODO
                return false;
                assert(false);
                return true;
            }

            n4 = normalize(n4);

            // Compute distance from origin to wedge face
            auto d = dot(n4, v1);

            // If the origin is inside the wedge, we have a hit
            if (d >= 0 && !hit)
            {
                normal = n4;

                // Compute the barycentric coordinates of the origin
                auto b0 = dot(cross(v1, v2), v3);
                auto b1 = dot(cross(v3, v2), v0);
                auto b2 = dot(cross(v0, v1), v3);
                auto b3 = dot(cross(v2, v1), v0);
                auto sum = b0 + b1 + b2 + b3;

                if (sum <= 0)
                {
                    b0 = 0;
                    b1 = dot(cross(v2, v3), n4);
                    b2 = dot(cross(v3, v1), n4);
                    b3 = dot(cross(v1, v2), n4);
                    sum = b1 + b2 + b3;
                }

                auto inv = 1.f / sum;

                pointA = (b0 * v01 + b1 * v11 + b2 * v21 + b3 * v31) * inv;
                pointB = (b0 * v02 + b1 * v12 + b2 * v22 + b3 * v32) * inv;

                // HIT!!!
                hit = true;
            }

            // Find the support point in the direction of the wedge face
            tmp = -n4;
            vec3 v41 = a.findSupport(tmp);
            vec3 v42 = b.findSupport(n4);
            auto v4 = v42 - v41;

            auto delta = dot(v4 - v3, n4);
            auto separation = -dot(v4, n4);

            // If the boundary is thin enough or the origin is outside the support plane for the newly discovered vertex, then we can terminate
            if (delta <= CollideEpsilon || separation >= 0 || phase2 > 20)
            {
                if (phase2 > 20)
                {
                    printf("%d", phase2);
                }
                normal = n4;
                return hit;
            }

            // Compute the tetrahedron dividing face (v4,v0,v1)
            auto d1 = dot(cross(v4, v1), v0);

            // Compute the tetrahedron dividing face (v4,v0,v2)
            auto d2 = dot(cross(v4, v2), v0);

            // Compute the tetrahedron dividing face (v4,v0,v3)
            auto d3 = dot(cross(v4, v3), v0);

            if (d1 < 0)
            {
                if (d2 < 0)
                {
                    // Inside d1 & inside d2 ==> eliminate v1
                    v1 = v4;
                    v11 = v41;
                    v12 = v42;
                }
                else
                {
                    // Inside d1 & outside d2 ==> eliminate v3
                    v3 = v4;
                    v31 = v41;
                    v32 = v42;
                }
            }
            else
            {
                if (d3 < 0)
                {
                    // Outside d1 & inside d3 ==> eliminate v2
                    v2 = v4;
                    v21 = v41;
                    v22 = v42;
                }
                else
                {
                    // Outside d1 & outside d3 ==> eliminate v1
                    v1 = v4;
                    v11 = v41;
                    v12 = v42;
                }
            }
        }
    }
}
