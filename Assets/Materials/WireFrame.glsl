struct VertexInput
{
  vec3 Position;
  vec3 Normal;
  vec4 Color;
};

interface IVertexOutput
{
  vec4 Color;
  vec3 WorldPos;
  vec3 WorldNormal;
};

struct VertexOutput
{
  vec4 Color;
  vec3 WorldPos;
  vec3 WorldNormal;
};

struct DirectionalLight
{
  vec3 Direction;
  vec4 Color;
  float AmbientIntensity;
  float DiffuseIntensity;
  float SpecularIntensity;
  float SpecularPower;
};

uniform vec4 _Color;
uniform mat4 _MATRIX_MVP;
uniform mat4 _Object2World;

uniform vec3 _WorldSpaceCameraPos;

uniform DirectionalLight _Light;

shader vertexMain(in vec3 Position, in vec3 Normal, in vec4 Color, out IVertexOutput OUT)
{
  vec4 position = vec4(Position, 1);
  vec4 normal = vec4(Normal, 0);

  gl_Position = _MATRIX_MVP * position;
  OUT.Color = Color;
  OUT.WorldPos = (_Object2World * position).xyz;
  OUT.WorldNormal = normalize((_Object2World * normal)).xyz;
}

vec4 computeLight(VertexOutput INPUT)
{
  vec4 ambientColor = _Light.Color * _Light.AmbientIntensity;
  float diffuseFactor = dot(INPUT.WorldNormal, -_Light.Direction);

  vec4 diffuseColor  = vec4(0, 0, 0, 0);
  vec4 specularColor = vec4(0, 0, 0, 0);

  if (diffuseFactor > 0)
  {
    diffuseColor = _Light.Color * _Light.DiffuseIntensity * diffuseFactor;

    vec3 vertexToEye = normalize(_WorldSpaceCameraPos - INPUT.WorldPos);
    vec3 lightReflect = normalize(reflect(_Light.Direction, INPUT.WorldNormal));
    float specularFactor = dot(vertexToEye, lightReflect);
    specularFactor = pow(specularFactor, _Light.SpecularPower);
    if (specularFactor > 0) {
      specularColor = _Light.Color * _Light.SpecularIntensity * specularFactor;
    }
  }

  return (ambientColor + diffuseColor + specularColor);
}

shader fragmentMain(in IVertexOutput IN, out vec4 FragColor)
{
  VertexOutput INPUT;
  INPUT.Color = IN.Color;
  INPUT.WorldPos = IN.WorldPos;
  INPUT.WorldNormal = IN.WorldNormal;

  vec4 totalLight = computeLight(INPUT);

  FragColor = _Color * totalLight;
  //FragColor = vec4(1,1,1,1);
}

program Main
{
  vs(410) = vertexMain();
  fs(410) = fragmentMain();
};
