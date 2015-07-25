#pragma once

#define typeof(T) #T

#define len(a) (sizeof(a) / sizeof(a[0]))

namespace walt
{
    const glm::vec3 Right = glm::vec3(1, 0, 0);
    const glm::vec3 Left = glm::vec3(-1, 0, 0);
    const glm::vec3 Up = glm::vec3(0, 1, 0);
    const glm::vec3 Down = glm::vec3(0, -1, 0);
    const glm::vec3 Backward = glm::vec3(0, 0, 1);
    const glm::vec3 Forward = glm::vec3(0, 0, -1);

    const float Pi = (float)3.14159265358979323846;
    const float PiOver2 = Pi / 2;
    const float PiOver3 = Pi / 3;
    const float PiOver4 = Pi / 4;
    const float PiOver6 = Pi / 6;
    const float TwoPi = Pi * 2;

    inline float toRadian(float x)
    {
        return (float)(x * Pi / 180.0f);
    }

    inline float toDegree(float x)
    {
        return (float)(x * 180.0f / Pi);
    }

    inline glm::vec3 toGlmVec3(const aiVector3D &v)
    {
        return glm::vec3(v.x, v.y, v.z);
    }

    inline glm::vec3 safeNormalize(const glm::vec3 &v)
    {
        return glm::length(v) > 0 ? glm::normalize(v) : glm::vec3(0, 1, 0);
    }

    inline glm::quat safeNormalize(const glm::quat &v)
    {
        return glm::length(v) > 0 ? glm::normalize(v) : v;
    }

    inline float acosDegree(float cos)
    {
        return toDegree(acos(cos));
    }

    //TODO: don't rely on compiler return-value optimization

    inline glm::vec3 transformDirection(const glm::mat4& t, const glm::vec3& v)
    {
        return glm::vec3(t * glm::vec4(v, 0));
    }

    inline glm::vec3 transformDirection(const glm::vec3& v, const glm::mat4& t)
    {
        return glm::vec3(t * glm::vec4(v, 0));
    }

    inline glm::vec3 transformPosition(const glm::mat4& t, const glm::vec3& v)
    {
        return glm::vec3(t * glm::vec4(v, 1));
    }

    inline glm::vec3 transformPosition(const glm::vec3& v, const glm::mat4& t)
    {
        return glm::vec3(t * glm::vec4(v, 1));
    }

    inline glm::vec3 transformPosition(const glm::vec3& v, const glm::quat q)
    {
        return glm::vec3(glm::toMat4(q) * glm::vec4(v, 1));
    }

    inline glm::vec3 transformDirection(const glm::vec3& v, const glm::quat q)
    {
        return glm::vec3(glm::toMat4(q) * glm::vec4(v, 0));
    }

    const float PositiveZero = 1.f / 16384.f;
    const float NegativeZero = -PositiveZero;

    inline bool IsZero(float f)
    {
        return f > NegativeZero && f < PositiveZero;
    }

    inline bool IsZero(const glm::vec3& v)
    {
        return IsZero(v.x) && IsZero(v.y) && IsZero(v.z);
    }
}
