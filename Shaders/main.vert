#version 330

layout(location = 0) in vec3 positionModel;
layout(location = 1) in vec3 normalModel;
layout(location = 2) in vec2 texCoord;
out vec2 texCoordOut;
out vec3 normalWorld, fragWorld;

uniform mat4 VP, M;

void main() {
  fragWorld = vec3(M * vec4(positionModel, 1));
  gl_Position = VP * vec4(fragWorld, 1);
  normalWorld = vec3(transpose(inverse(M)) * vec4(normalModel, 0));
  texCoordOut = texCoord;
}