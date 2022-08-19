#version 330
const int MAX_LIGHTS = 20;
const float ambientFactor = 0.1;

in vec2 texCoordOut;
in vec3 normalWorld, fragWorld;
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
uniform Material material;
uniform vec3 observerPos;

layout(std140) uniform Lights { LightStruct lights[MAX_LIGHTS]; };

void main() {
  vec4 texColor = texture(albedo, texCoordOut);
  color = vec4(0);
  for (int i = 0; i < MAX_LIGHTS; i++) {
    if (lights[i].enabled) {
      if (lights[i].type == 0) {        // Directional
      } else if (lights[i].type == 1) { // Point
        vec3 fragToLight = normalize(-fragWorld + lights[i].direction);
        float diffuseFactor = dot(fragToLight, normalWorld);
        vec3 fragToObserver = normalize(-fragWorld + observerPos);
        vec3 halfWay = normalize(fragToLight + fragToObserver);
        float specFactor = pow(dot(halfWay, normalWorld), material.shininess);
        color +=
            diffuseFactor * lights[i].diffuse * material.diffuse * texColor +
            specFactor * lights[i].specular * material.specular +
            ambientFactor * lights[i].ambient * material.ambient;
      } else if (lights[i].type == 2) { // Spot
      }
    }
  }
  color.a = texColor.a;
}