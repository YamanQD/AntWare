#include <Scene.h>
using namespace std;
using namespace aw;
using namespace rapidjson;
using namespace glm;
static inline vec3 parseVec(GenericArray<false, Value> array)
{
    return {array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat()};
}
static inline Transform parseTransform(GenericObject<false, Value> object)
{
    vec3 position = parseVec(object["position"].GetArray());
    vec3 rotation = parseVec(object["rotation"].GetArray());
    vec3 scale = parseVec(object["scale"].GetArray());
    return Transform(position, rotation, scale);
}
static inline Rigidbody parseRigidbody(GenericObject<false, Value> object)
{
    Rigidbody rb;
    rb.velocity = parseVec(object["velocity"].GetArray());
    rb.angularVelocity = parseVec(object["angularVelocity"].GetArray());
    rb.acceleration = parseVec(object["acceleration"].GetArray());
    rb.angularAcceleration = parseVec(object["angularAcceleration"].GetArray());
    rb.mass = object["mass"].GetFloat();
    rb.linearLock = object["linearLock"].GetInt();
    rb.angularLock = object["angularLock"].GetInt();
    return rb;
}
static inline void parseCamera(GenericObject<false, Value> object, Camera &camera)
{
    camera.setFOV(object["fov"].GetFloat());
    camera.transform = parseTransform(object["transform"].GetObject());
    camera.rigidbody = parseRigidbody(object["rigidbody"].GetObject());
}
Scene::Scene(const char *path) : camera(45.0f)
{
    fstream sceneStream(path, ios::ate | ios::in);
    vector<char> fileData;
    if (sceneStream.is_open())
    {
        fileData.resize(sceneStream.tellg());
        sceneStream.seekg(0, ios::beg);
        sceneStream.read(fileData.data(), fileData.size());
        sceneStream.flush();
        sceneStream.close();
    }
    else
    {

        throw runtime_error("LEVEL JSON file was not found");
    }
    Document json;
    json.Parse(fileData.data(), fileData.size());
    parseCamera(json["camera"].GetObject(), camera);
}
Scene::~Scene()
{
}