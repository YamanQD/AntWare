#version 330 core
layout(location=0) out vec4 outColor0;
in vec2 uv;
uniform vec4 color;
uniform sampler2D albedo;
void main(){
  outColor0=color*texture(albedo,uv);
}
