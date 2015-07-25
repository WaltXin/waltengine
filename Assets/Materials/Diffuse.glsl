struct Input
{
  vec3 Position;
  vec3 Normal;
};

interface IVertexOutput
{
  vec3 Albedo;
  vec3 Normal;
  float Alpha;
  vec3 LightDir;
};

struct VertexOutput
{
  vec3 Albedo;
  vec3 Normal;
  float Alpha;
  vec3 LightDir;
};

uniform vec4 _Color;
uniform mat4 _MATRIX_MVP;
uniform mat4 _Object2World;
uniform vec3 _WorldSpaceCameraPos;
uniform vec3 _ObjectSpaceLightPos;
uniform vec4 _LightColor;

shader vertexMain(in Input IN : 0, out IVertexOutput o)
{
  gl_Position = _MATRIX_MVP * vec4(IN.Position, 1.0);
  vec4 normal = _Object2World * vec4(IN.Normal, 0);

  o.Albedo = _Color.xyz;
  o.Alpha = _Color.w;
  o.Normal = normal.xyz;
  o.LightDir = gl_Position - _ObjectSpaceLightPos;
}

vec4 LightingLambert(VertexOutput IN, float atten)
{
  float diff = max(0, dot(IN.Normal, IN.LightDir));

  vec4 c;
  c.rgb = IN.Albedo * _LightColor.rgb * (diff * atten * 2);
  c.a = IN.Alpha;
  return c;
}

shader fragmentMain(in IVertexOutput IN, out vec4 FragColor)
{
  VertexOutput input;
  input.Albedo = IN.Albedo;
  input.Normal = IN.Normal;
  input.Alpha = IN.Alpha;
  input.LightDir = IN.LightDir;

  FragColor = LightingLambert(input, 1.0);
}

program Main
{
  vs(410) = vertexMain();
  fs(410) = fragmentMain();
};
