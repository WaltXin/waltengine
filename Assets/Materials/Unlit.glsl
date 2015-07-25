struct Input
{
  vec3 Position;
  vec3 Normal;
};

interface VertexOutput
{
  vec4 Color;
};

uniform vec4 _Color;
uniform mat4 _MATRIX_MVP;

shader vertexMain(in Input IN : 0, out VertexOutput o)
{
  gl_Position = _MATRIX_MVP * vec4(IN.Position, 1.0);
  o.Color = _Color;
}

shader fragmentMain(in VertexOutput IN, out vec4 FragColor)
{
  FragColor = IN.Color;
}

program Main
{
  vs(410) = vertexMain();
  fs(410) = fragmentMain();
};
