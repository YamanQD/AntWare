#version 330
const int MAX_LIGHTS = 20;

in vec2 texCoordOut;
out vec4 color;

struct LightStruct {
  bool enabled;
  int type;
  vec4 ambient, diffuse, specular;
  vec3 direction;
  float angle;
};

struct Material {
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float shininess;
};

uniform sampler2D albedo;
uniform LightStruct lights[MAX_LIGHTS];
uniform Material material;
uniform vec3 observerPos;

void main() { color = texture(albedo, texCoordOut); }