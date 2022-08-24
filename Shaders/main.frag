#version 330
const int MAX_LIGHTS = 20;
const float ambientFactor = 0.1;
const float QUADRATIC_ATTEN = 0.05;
const float LINEAR_ATTEN = 0.33;

in vec2 texCoordOut;
in vec3 normalWorld, fragWorld;
out vec4 color;

struct LightStruct {
  bool enabled;
  int type;
  vec4 ambient, diffuse, specular;
  vec3 direction;
  float angle;
  vec3 position;
};

struct Material {
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float shininess;
  float alpha;
};

uniform sampler2D albedo;
uniform Material material;
uniform vec3 observerPos;

layout(std140) uniform Lights { LightStruct lights[MAX_LIGHTS]; };

void main() {
  vec4 texColor = texture(albedo, texCoordOut);
  color = vec4(0);
  vec3 nWorld = normalize(normalWorld);
  for (int i = 0; i < MAX_LIGHTS; i++) {
    if (lights[i].enabled) {
      if (lights[i].type == 0) { // Directional
        vec3 fragToLight = -lights[i].direction;
        float diffuseFactor = max(dot(fragToLight, nWorld), 0);
        vec3 fragToObserver = normalize(-fragWorld + observerPos);
        vec3 halfWay = normalize(fragToLight + fragToObserver);
        float specFactor =
            max(pow(dot(halfWay, nWorld), material.shininess), 0) /
            (distance(fragWorld, observerPos) * LINEAR_ATTEN);
        color +=
            diffuseFactor * lights[i].diffuse * material.diffuse * texColor +
            specFactor * lights[i].specular * material.specular +
            ambientFactor * lights[i].ambient * material.ambient;
      } else if (lights[i].type == 1) { // Point
        vec3 fragToLight = normalize(-fragWorld + lights[i].position);
        float quadraticAtten =
            ((pow(distance(fragWorld, lights[i].position), 2)) *
             QUADRATIC_ATTEN);
        float diffuseFactor = max(dot(fragToLight, nWorld), 0) / quadraticAtten;
        vec3 fragToObserver = normalize(-fragWorld + observerPos);
        vec3 halfWay = normalize(fragToLight + fragToObserver);
        float specFactor =
            max(pow(dot(halfWay, nWorld), material.shininess), 0) /
            (quadraticAtten + distance(fragWorld, observerPos) * LINEAR_ATTEN);
        color +=
            diffuseFactor * lights[i].diffuse * material.diffuse * texColor +
            specFactor * lights[i].specular * material.specular +
            ambientFactor * lights[i].ambient * material.ambient;
      } else if (lights[i].type == 2) { // Spot
        vec3 fragToLight = normalize(-fragWorld + lights[i].position);
        float dirToLight = dot(-fragToLight, normalize(lights[i].direction));
        if (dirToLight < cos(radians(lights[i].angle)))
          continue;
        float quadraticAtten =
            ((pow(distance(fragWorld, lights[i].position), 2)) *
             QUADRATIC_ATTEN);
        float diffuseFactor = max(dot(fragToLight, nWorld), 0) / quadraticAtten;
        vec3 fragToObserver = normalize(-fragWorld + observerPos);
        vec3 halfWay = normalize(fragToLight + fragToObserver);
        float specFactor =
            max(pow(dot(halfWay, nWorld), material.shininess), 0) /
            (quadraticAtten + distance(fragWorld, observerPos) * LINEAR_ATTEN);
        color +=
            diffuseFactor * lights[i].diffuse * material.diffuse * texColor +
            specFactor * lights[i].specular * material.specular +
            ambientFactor * lights[i].ambient * material.ambient;
      }
    }
  }
  color.a = texColor.a * material.alpha;
}