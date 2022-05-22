#version 330

layout(location=0) in vec3 positionModel;
layout(location=1) in vec3 normalModel;
layout(location=2) in vec2 texCoord;
out vec2 texCoordOut;
		
uniform mat4 VP,M;

void main(){
  gl_Position=VP*M*vec4(positionModel,1);
  texCoordOut=texCoord;
}