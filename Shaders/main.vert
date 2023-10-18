#version 330

const uint MAX_BONES=20u;

layout(location = 0) in vec3 positionModel;
layout(location = 1) in vec3 normalModel;
layout(location = 2) in vec2 texCoord;
layout(location=3) in uint boneID;
out vec2 texCoordOut;
out vec3 normalWorld, fragWorld;

uniform bool skinned=false;

uniform mat4 VP, M;
uniform mat4 bones[MAX_BONES];

void main() {
  if(skinned){
    fragWorld=vec3(M*bones[boneID]*vec4(positionModel,1));
  }else{
    fragWorld = vec3(M * vec4(positionModel, 1));
  }
  gl_Position = VP * vec4(fragWorld, 1);
  normalWorld = vec3(transpose(inverse(M)) * vec4(normalModel, 0));
  texCoordOut = texCoord;
}