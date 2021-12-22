#include <Scene.h>
using namespace std;
using namespace aw;
using namespace rapidjson;
using namespace glm;
static inline vec3 parseVec(GenericArray<false, Value> array)
{
    return {array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat()};
}

static inline vec4 parseVec4(GenericArray<false, Value> array)
{
    return {array[0].GetFloat(), array[1].GetFloat(),
            array[2].GetFloat(), array[3].GetFloat()};
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
static inline Mesh parseMesh(GenericObject<false, Value> object)
{
    const char *path = object["path"].GetString();
    const char *texturePath = nullptr;
    if (object.HasMember("texture"))
    {
        texturePath = object["texture"].GetString();
    }
    if (object.HasMember("color"))
    {
        vec4 color = parseVec4(object["color"].GetArray());
        return Mesh(path, color, texturePath);
    }
    else
    {
        return Mesh(path, texturePath);
    }
}
static inline vector<shared_ptr<Mesh>> parseMeshes(GenericArray<false, Value> array)
{
    vector<shared_ptr<Mesh>> meshes;
    for (unsigned i = 0; i < array.Size(); ++i)
    {
        meshes.push_back(make_shared<Mesh>(parseMesh(array[i].GetObject())));
    }
    return meshes;
}
static inline vector<GameObject *> parseGameObjects(GenericArray<false, Value> array,
                                                    const vector<shared_ptr<Mesh>> &meshes)
{
    vector<GameObject *> gameObjects;
    for (unsigned i = 0; i < array.Size(); ++i)
    {
        int classType = array[i]["class"].GetInt();
        GameObject *parent = nullptr;
        if (array[i].HasMember("parent"))
        {
            int parentIndex = array[i]["parent"].GetInt();
            parent = gameObjects[parentIndex];
        }
        int meshIndex = array[i]["mesh"].GetInt();
        shared_ptr<Mesh> mesh = meshes[meshIndex];
        bool isStatic = true;
        if (array[i].HasMember("rigidbody"))
        {
            isStatic = false;
        }
        GameObject *gameObject;
        switch (classType)
        {
        case 0:
            gameObject = new DummyGO(*mesh, parent);
            break;
        case 1:
            gameObject = new StaticGO(mesh, parent);
            break;
        default:
            printf("Unknown class ID was in the scene : %d,using StaticGO instead.\n GameObject ID: %d\n", classType,
                   i);
            gameObject = new StaticGO(mesh, parent);
            break;
        }
        gameObject->isStatic = isStatic;
        gameObject->transform = parseTransform(array[i]["transform"].GetObject());
        if (!isStatic)
        {
            gameObject->rigidbody = parseRigidbody(array[i]["rigidbody"].GetObject());
        }
        gameObjects.push_back(gameObject);
    }
    return gameObjects;
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
    auto meshes = parseMeshes(json["meshes"].GetArray());
    gameObjects = parseGameObjects(json["gameobjects"].GetArray(), meshes);
}
Scene::~Scene()
{
    for (unsigned i = 0; i < gameObjects.size(); ++i)
    {
        delete gameObjects[i];
    }
}