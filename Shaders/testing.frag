#version 330
const int MAX_LIGHTS=20;

in vec2 texCoordOut;
out vec4 color;

struct LightStruct
{
  bool enabled;
	int type;
	vec4 ambient, diffuse, specular;
	vec3 direction;
	float angle;
};

uniform sampler2D albedo;
uniform LightStruct lights[MAX_LIGHTS];

void main(){
  color=texture(albedo,texCoordOut);
}