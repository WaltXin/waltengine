#pragma once

#include <Object.h>

#include <glm/glm.hpp>

#include <stdafx.h>

namespace walt
{
    enum class MaterialType
    {
        PhongMaterial,
        NumMaterialTypes
    };

    class Shader;

    class Material : public Object
    {
    public:
        Material();
        ~Material();

        static Material* load(MaterialType materialType);

        Shader *shader;

        void set(const char* propertyName, const glm::vec3& value);
        void set(const char* propertyName, const glm::vec4& value);
        void set(const char* propertyName, const glm::mat3& value);
        void set(const char* propertyName, const glm::mat4& value);
        void set(const char* propertyName, float value);

        void setColor(const glm::vec3& value);
        void setColor(const glm::vec4& value);
        void setWVP(const glm::mat4& value);
        void setWorldMatrix(const glm::mat4& value);
        void setCameraPos(const glm::vec3& value);
        void setLightDirection(const glm::vec3& value);
        void setLightColor(const glm::vec4& value);
        void setAmbientIntensity(float value);
        void setDiffuseIntensity(float value);
        void setSpecularIntensity(float value);
        void setSpecularPower(float value);

        static const char* UniformColor;
        static const char* UniformWVP;
        static const char* UniformWorldMatrix;
        static const char* UniformCameraPos;
        static const char* UniformLightDirection;
        static const char* UniformLightColor;
        static const char* UniformAmbientIntensity;
        static const char* UniformDiffuseIntensity;
        static const char* UniformSpecularIntensity;
        static const char* UniformSpecularPower;
    };
}
