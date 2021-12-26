#include <App.h>
using namespace aw;
using namespace rapidjson;
using namespace std;
App::App() {}
App &App::instance()
{
    static App app;
    return app;
}
void App::init(int argc, char **argv)
{
    readSettingsFile();
    WINDOW.init(settings.resHeight, settings.resWidth);
    RENDERER.init();
    currentScene = new Scene(argv[1]);
    start();
}
void App::terminate()
{
    RENDERER.terminate();
    WINDOW.terminate();
    delete currentScene;
}
void App::loop()
{
    sf::Clock clock;
    float deltaTime = 0.0f;
    while (true)
    {
        sf::Event event;
        while (WINDOW.internal.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                terminate();
                return;
            case sf::Event::Resized:
                // TODO
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left)
                    ((Player *)(currentScene->gameObjects[0]))->dispatchBullet();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                {
                    terminate();
                    return;
                }
            default:
                break;
            }
        }
        PHYSICS.apply(currentScene, deltaTime);
        update();
        RENDERER.renderScene(currentScene);
        deltaTime = clock.restart().asSeconds();
    }
}
void App::update()
{
    for (unsigned i = 0; i < currentScene->gameObjects.size(); ++i)
    {
        currentScene->gameObjects[i]->update();
    }
    currentScene->camera.transform = currentScene->gameObjects[0]->transform;
    currentScene->camera.transform.translate({0, 0.5f, 0});

    auto player = ((Player *)(currentScene->gameObjects[0])); // TODO hold in class
    auto bullets = player->bullets;
    auto gameObjectsSize = currentScene->gameObjects.size();
    auto bulletsSize = player->bullets.size();
    for (unsigned i = 0; i < gameObjectsSize; ++i)
    {
        if (currentScene->gameObjects[i]->getClass() == 3)
        {
            for (unsigned j = 0; j < bulletsSize; ++j)
            {
                if (currentScene->gameObjects[i]->aabb.isColliding(bullets[j].transform.getPosition()))
                {
                    auto ant = ((Ant *)(currentScene->gameObjects[i]));
                    ant->damage(1);
                    if (ant->getHp() == 0)
                    {
                        currentScene->destroyGameObject(i);
                        --i;
                        --gameObjectsSize;
                    }
                    player->destroyBullet(j);
                    --j;
                    --bulletsSize;
                }
            }
        }
    }
}
void App::start()
{
    for (unsigned i = 0; i < currentScene->gameObjects.size(); ++i)
    {
        currentScene->gameObjects[i]->start();
    }
}
void App::readSettingsFile()
{
    fstream settingsFileStream("./settings.json", ios::in | ios::ate);
    vector<char> fileData;
    if (settingsFileStream.is_open())
    {
        fileData.resize(settingsFileStream.tellg());
        settingsFileStream.seekg(0, ios::beg);
        settingsFileStream.read(fileData.data(), fileData.size());
        settingsFileStream.flush();
        settingsFileStream.close();
    }
    else
    {
        settingsFileStream = fstream("./default_settings.json", ios::in | ios::ate);
        if (settingsFileStream.is_open())
        {
            fileData.resize(settingsFileStream.tellg());
            settingsFileStream.seekg(0, ios::beg);
            settingsFileStream.read(fileData.data(), fileData.size());
            settingsFileStream.flush();
            settingsFileStream.close();
        }
        else
        {
            throw runtime_error("No valid settings file was found");
        }
    }
    Document settingsFileJSON;
    settingsFileJSON.Parse(fileData.data(), fileData.size());
    settings.resHeight = settingsFileJSON["resolution"]["height"].GetInt();
    settings.resWidth = settingsFileJSON["resolution"]["width"].GetInt();
}