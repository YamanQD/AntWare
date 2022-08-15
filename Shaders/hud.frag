#version 330 core
layout(location = 0) out vec4 outColor0;
in vec2 uv;
uniform vec3 color;
uniform sampler2D albedo;
void main() {
  vec4 sampledColor = texture(albedo, uv);
  if (sampledColor.a == 0.0)
    discard;
  outColor0 = vec4(color, 1.0) * sampledColor;
}
