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
    camera.setFOV(object["fov"].GetFloat(),false);
    camera.transform = parseTransform(object["transform"].GetObject());
    camera.rigidbody = parseRigidbody(object["rigidbody"].GetObject());
}
static inline Material parseMaterial(GenericObject<false, Value> object)
{
    vec4 ambient = parseVec4(object["ambient"].GetArray());
    vec4 diffuse = parseVec4(object["diffuse"].GetArray());
    vec4 specular = parseVec4(object["specular"].GetArray());
    float shininess = object["shininess"].GetFloat();
    return Material(ambient, diffuse, specular, shininess);
}
static inline vector<Material> parseMaterials(GenericArray<false, Value> array)
{
    vector<Material> materials;
    for (unsigned i = 0; i < array.Size(); ++i)
    {
        materials.push_back(parseMaterial(array[i].GetObject()));
    }
    return materials;
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
static inline vector<shared_ptr<Mesh>> parseAnimation(GenericObject<false, Value> object)
{
    vector<shared_ptr<Mesh>> animation;
    const char *path = object["path"].GetString();
    const char *name = object["name"].GetString();
    const char *format = object["format"].GetString();
    int count = object["count"].GetInt();
    char buffer[256];
    for (unsigned i = 1; i <= count; ++i)
    {
        sprintf(buffer, "%s/%s_%06d.%s", path, name, i, format);
        shared_ptr<Mesh> mesh(new Mesh(buffer));
        animation.push_back(mesh);
    }
    return animation;
}
static inline vector<vector<shared_ptr<Mesh>>> parseAnimations(GenericArray<false, Value> array)
{
    vector<vector<shared_ptr<Mesh>>> animations;
    for (unsigned i = 0; i < array.Size(); ++i)
    {
        animations.push_back(parseAnimation(array[i].GetObject()));
    }
    return animations;
}
static inline vector<shared_ptr<Mesh>> parseMeshes(GenericArray<false, Value> array)
{
    vector<shared_ptr<Mesh>> meshes;
    for (unsigned i = 0; i < array.Size(); ++i)
    {
        Mesh mesh = parseMesh(array[i].GetObject());
        shared_ptr<Mesh> meshPtr(new Mesh(mesh));
        meshes.push_back(meshPtr);
    }
    return meshes;
}
static inline vector<GameObject *> parseGameObjects(GenericArray<false, Value> array,
                                                    const vector<shared_ptr<Mesh>> &meshes,
                                                    const vector<Material> &materials,
                                                    const vector<vector<shared_ptr<Mesh>>> &animations,
                                                    vec2 mapMinLimit,
                                                    vec2 mapMaxLimit)
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
        Material material;
        if (array[i].HasMember("material"))
        {
            material = materials[array[i]["material"].GetInt()];
        }
        int animationIndex = -1;
        if (array[i].HasMember("animation"))
        {
            animationIndex = array[i]["animation"].GetInt();
        }
        GameObject *gameObject;
        switch (classType)
        {
        case CLASSES::STATICGO:
            gameObject = new StaticGO(mesh, material, parent);
            break;
        case CLASSES::PLAYER:
            gameObject = new Player(mesh, material, mapMinLimit, mapMaxLimit, parent);
            if (array[i].HasMember("ammo"))
            {
                ((Player *)gameObject)->totalAmmo = array[i]["ammo"].GetInt();
            }
            break;
        case CLASSES::ANT:
            gameObject = new Ant(mesh, material, parent);
            break;
        case CLASSES::RAGED_ANT:
            gameObject = new RagedAnt(animations[animationIndex], mesh, material, parent, gameObjects[0]);
            break;
        default:
            printf("Unknown class ID was in the scene : %d,using StaticGO instead.\n GameObject ID: %d\n", classType,
                   i);
            gameObject = new StaticGO(mesh, material, parent);
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
static inline vector<Light> parseLights(GenericArray<false, Value> array, const vector<GameObject *> gameObjects)
{
    vector<Light> lights;
    for (unsigned i = 0; i < array.Size(); ++i)
    {
        int classType = array[i]["class"].GetInt();
        vec4 ambient = parseVec4(array[i]["ambient"].GetArray());
        vec4 diffuse = parseVec4(array[i]["diffuse"].GetArray());
        vec4 specular = parseVec4(array[i]["specular"].GetArray());
        GameObject *parent = nullptr;
        if (array[i].HasMember("parent"))
        {
            parent = gameObjects[array[i]["parent"].GetInt()];
        }
        vec3 position, direction;
        float angle;
        switch (classType)
        {
        case LightType::POINT:
            position = parseVec(array[i]["position"].GetArray());
            lights.push_back(Light(i, ambient, diffuse, specular, position, parent));
            glEnable(GL_LIGHT0 + i);
            break;
        case LightType::DIRECTIONAL:
            direction = parseVec(array[i]["direction"].GetArray());
            lights.push_back(Light(i, ambient, diffuse, specular, LightType::DIRECTIONAL, direction, parent));
            glEnable(GL_LIGHT0 + i);
            break;
        case LightType::SPOT:
            position = parseVec(array[i]["position"].GetArray());
            direction = parseVec(array[i]["direction"].GetArray());
            angle = array[i]["angle"].GetFloat();
            lights.push_back(Light(i, ambient, diffuse, specular, position, direction, angle, parent));
            glEnable(GL_LIGHT0 + i);
            break;
        default:
            printf("Unknown lightType %d, ignoring light", i);
            i--;
            break;
        }
    }
    return lights;
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
    auto materials = parseMaterials(json["materials"].GetArray());
    /*auto meshes = parseMeshes(json["meshes"].GetArray());
    auto animations = parseAnimations(json["animations"].GetArray());
    auto mapMinLimitData = json["mapMinLimit"].GetArray();
    auto mapMaxLimitData = json["mapMaxLimit"].GetArray();
    vec2 mapMinLimit = {mapMinLimitData[0].GetFloat(), mapMinLimitData[1].GetFloat()};
    vec2 mapMaxLimit = {mapMaxLimitData[0].GetFloat(), mapMaxLimitData[1].GetFloat()};
    gameObjects = parseGameObjects(json["gameobjects"].GetArray(), meshes, materials,
                                   animations, mapMinLimit, mapMaxLimit);
    lights = parseLights(json["lights"].GetArray(), gameObjects);
    if (json.HasMember("skybox"))
        skybox = Skybox(&camera, json["skybox"].GetString());*/
}
Scene::~Scene()
{
    for (unsigned i = 0; i < gameObjects.size(); ++i)
    {
        delete gameObjects[i];
    }
}
void Scene::destroyGameObject(int index)
{
    delete gameObjects[index];
    gameObjects.erase(gameObjects.begin() + index);
}