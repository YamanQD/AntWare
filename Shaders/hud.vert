#version 330 core
layout(location = 0) in vec4 positionModel;
out vec2 uv;
const mat4 ortho = mat4(vec4(0.125, 0, 0, 0), vec4(0, 0.222222224, 0, 0),
                        vec4(0, 0, -1, 0), vec4(0, 0, 0, 1));
uniform mat4 model;
void main() {
  uv = (positionModel.xy + vec2(1.0)) * 0.5;
  gl_Position = ortho * model * positionModel;
}