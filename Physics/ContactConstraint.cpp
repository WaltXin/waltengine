#include "ContactConstraint.h"

#include <Components/Transform.h>
#include <Physics/Collider.h>
#include <Physics/Physics.h>
#include <GameObject.h>

using namespace walt;
using namespace glm;

ContactConstraint::ContactConstraint(Collider* a, Collider* b, glm::vec3& localA, glm::vec3& localB, glm::vec3& normal)
{
    this->a = a;
    this->b = b;
    this->localA = localA;
    this->localB = localB;
    this->normal = normal;
    beta = 1;
    cachedMomentum = 0;
}

ContactConstraint::~ContactConstraint()
{
}

void ContactConstraint::prepareForIteration()
{
    vec3 ra = a->transform->toWorldDirection(localA);
    vec3 rb = b->transform->toWorldDirection(localB);

    vec3 pa = a->transform->position() + ra;
    vec3 pb = b->transform->position() + rb;

    beta = Physics::betaFactor / Physics::elapsedStepSeconds;
    positionError = dot(beta * (pb - pa), normal);
    positionError += Physics::positionErrorDiminish;
    
    invMomentA = transformDirection(cross(ra, normal), a->getInverseWorldInertiaTensor());
    invMomentB = transformDirection(cross(rb, normal), b->getInverseWorldInertiaTensor());

    float term1 = a->computedInverseMass();
    float term2 = b->computedInverseMass();
    float term3 = dot(normal, cross(invMomentA, ra) + cross(invMomentB, rb));

    effectiveMass = Physics::effectiveMassFactor / (term1 + term2 + term3);

    cachedMomentum *= Physics::timeRatio;
    cachedAngularMomentum *= Physics::timeRatio;

    a->velocity -= cachedMomentum * normal * a->computedInverseMass();
    b->velocity += cachedMomentum * normal * b->computedInverseMass();
    a->angularVelocity -= cachedMomentum * invMomentA;
    b->angularVelocity += cachedMomentum * invMomentB;

    cachedAngularMomentum = vec3();
}

void ContactConstraint::update(glm::vec3& localA, glm::vec3& localB, glm::vec3& normal)
{
    this->localA = localA;
    this->localB = localB;
    this->normal = normal;
}

void ContactConstraint::iterate()
{
    vec3 ra = a->transform->toWorldDirection(localA);
    vec3 rb = b->transform->toWorldDirection(localB);

    auto padot = a->velocity + cross(a->angularVelocity, ra);
    auto pbdot = b->velocity + cross(b->angularVelocity, rb);
    auto relativeVelocity = pbdot - padot;

    auto velocityError = dot(relativeVelocity, normal);

    auto deltaVelocity = -velocityError - positionError;

    auto momentumPacket = deltaVelocity * effectiveMass;

    momentumPacket = min(momentumPacket, -cachedMomentum);

    auto momentumPacketWithDir = momentumPacket * normal;

    a->velocity -= momentumPacketWithDir * a->computedInverseMass();
    b->velocity += momentumPacketWithDir * b->computedInverseMass();
    a->angularVelocity -= momentumPacket * invMomentA;
    b->angularVelocity += momentumPacket * invMomentB;

    cachedMomentum += momentumPacket;

    const bool friction = true;

    if (friction)
    {
        padot = a->velocity + cross(a->angularVelocity, ra);
        pbdot = b->velocity + cross(b->angularVelocity, rb);

        relativeVelocity = pbdot - padot;

        auto angularVelocityDir = relativeVelocity - dot(relativeVelocity, normal) * normal;
        if (IsZero(angularVelocityDir)) return;
        angularVelocityDir = normalize(angularVelocityDir);

        auto angularVelocityError = dot(relativeVelocity, angularVelocityDir);

        invMomentA = transformDirection(cross(ra, angularVelocityDir), a->getInverseWorldInertiaTensor());
        invMomentB = transformDirection(cross(rb, angularVelocityDir), b->getInverseWorldInertiaTensor());

        auto term1 = a->computedInverseMass();
        auto term2 = b->computedInverseMass();
        auto term3 = dot(angularVelocityDir, cross(invMomentA, ra) + cross(invMomentB, rb));

        effectiveMass = Physics::effectiveMassFactor / (term1 + term2 + term3);

        auto angularDeltaVelocity = -angularVelocityError;
        auto angularMomentumPacket = angularDeltaVelocity * effectiveMass;
        angularMomentumPacket = max(angularMomentumPacket, cachedMomentum / 2);

        auto angularMomentumPacketWithDir = angularMomentumPacket * angularVelocityDir;

        a->velocity -= angularMomentumPacketWithDir * a->computedInverseMass();
        b->velocity += angularMomentumPacketWithDir * b->computedInverseMass();
        a->angularVelocity -= angularMomentumPacket * invMomentA;
        b->angularVelocity += angularMomentumPacket * invMomentB;

        cachedAngularMomentum = angularMomentumPacketWithDir;
    }
}
