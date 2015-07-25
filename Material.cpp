#include "Material.h"

#include <GL/glew.h>
#include <gl/glfx.h>
#include <glm/gtc/type_ptr.hpp>

#include <Material.h>
#include <Shader.h>

using namespace walt;
using namespace glm;

Material::Material()
{
}

Material::~Material()
{
    delete shader;
}

Material* walt::Material::load(MaterialType materialType)
{
    auto* shader = Shader::findEffect("Assets/Materials/Phong.glsl");
    //auto* shader = Shader::findVF("Assets/Materials/Phong.vs", "Assets/Materials/Phong.fs");

    auto material = new Material();
    material->shader = shader;

    return material;
}

void Material::set(const char* propertyName, const vec3& value)
{
    shader->use();
    auto location = shader->getUniformLocation(propertyName);
    glUniform3fv(location, 1, value_ptr(value));
}

void Material::set(const char* propertyName, const vec4& value)
{
    shader->use();
    auto location = shader->getUniformLocation(propertyName);
    glUniform4fv(location, 1, value_ptr(value));
}

void Material::set(const char* propertyName, const mat3& value)
{
    shader->use();
    auto location = shader->getUniformLocation(propertyName);
    glUniformMatrix3fv(location, 1, false, value_ptr(value));
}

void Material::set(const char* propertyName, const mat4& value)
{
    shader->use();
    auto location = shader->getUniformLocation(propertyName);
    glUniformMatrix4fv(location, 1, false, value_ptr(value));
}

void Material::set(const char* propertyName, float value)
{
    shader->use();
    auto location = shader->getUniformLocation(propertyName);
    glUniform1f(location, value);
}

void Material::setColor(const vec3& value)
{
    set(UniformColor, vec4(value, 1));
}

void Material::setColor(const vec4& value)
{
    set(UniformColor, value);
}

void Material::setWVP(const mat4& value)
{
    set(UniformWVP, value);
}

void Material::setWorldMatrix(const mat4& value)
{
    set(UniformWorldMatrix, value);
}

void Material::setCameraPos(const vec3& value)
{
    set(UniformCameraPos, value);
}

void Material::setLightDirection(const vec3& value)
{
    set(UniformLightDirection, value);
}

void Material::setLightColor(const vec4& value)
{
    set(UniformLightColor, value);
}

void Material::setAmbientIntensity(float value)
{
    set(UniformAmbientIntensity, value);
}

void Material::setDiffuseIntensity(float value)
{
    set(UniformDiffuseIntensity, value);
}

void Material::setSpecularIntensity(float value)
{
    set(UniformSpecularIntensity, value);
}

void Material::setSpecularPower(float value)
{
    set(UniformSpecularPower, value);
}

const char* Material::UniformColor = "_Color";
const char* Material::UniformWVP = "_MATRIX_MVP";
const char* Material::UniformWorldMatrix = "_Object2World";
const char* Material::UniformCameraPos = "_WorldSpaceCameraPos";
const char* Material::UniformLightDirection = "_Light.Direction";
const char* Material::UniformLightColor = "_Light.Color";
const char* Material::UniformAmbientIntensity = "_Light.AmbientIntensity";
const char* Material::UniformDiffuseIntensity = "_Light.DiffuseIntensity";
const char* Material::UniformSpecularIntensity = "_Light.SpecularIntensity";
const char* Material::UniformSpecularPower = "_Light.SpecularPower";
