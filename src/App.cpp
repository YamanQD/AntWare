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
    srandom(time(nullptr));
    readSettingsFile();
    WINDOW.init(settings.resHeight, settings.resWidth);
    RENDERER.init();
    currentScene = new Scene(argv[1]);
    currentScene->lights[0].toggle();
    auto player = ((Player *)(currentScene->gameObjects[0]));
    HUD.setHP(player->hp * 10);
    HUD.setInHandAmmo(player->inHandAmmo);
    HUD.setTotalAmmo(player->totalAmmo);
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
    auto player = ((Player *)(currentScene->gameObjects[0]));
    sf::Clock clock, shootTimer, reloadTimer;
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
                if (
                    event.mouseButton.button == sf::Mouse::Left &&
                    reloadTimer.getElapsedTime().asSeconds() > 1.5f &&
                    shootTimer.getElapsedTime().asSeconds() > 0.2f &&
                    !ended)
                {
                    if (player->inHandAmmo > 0)
                    {
                        player->dispatchBullet();
                        player->inHandAmmo--;
                        shootTimer.restart();
                        HUD.setInHandAmmo(player->inHandAmmo);
                        HUD.setTotalAmmo(player->totalAmmo);
                    }
                    else
                    {
                        if (player->totalAmmo > 0 && reloadTimer.getElapsedTime().asSeconds() > 1.5f)
                        {
                            reloadTimer.restart();
                            player->reload();
                        }
                    }
                }
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::F && !ended)
                {
                    currentScene->lights[0].toggle();
                }
                if (event.key.code == sf::Keyboard::R && reloadTimer.getElapsedTime().asSeconds() > 1.5f && !ended)
                {
                    if (player->totalAmmo > 0)
                    {
                        reloadTimer.restart();
                        player->reload();
                    }
                }
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
        if (!ended)
        {
            PHYSICS.apply(currentScene, deltaTime);
            update();
            RENDERER.renderScene(currentScene);
            deltaTime = clock.restart().asSeconds();
        }
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
    isWin = true;
    for (unsigned i = 0; i < gameObjectsSize; ++i)
    {
        if (currentScene->gameObjects[i]->getClass() == 3)
        {
            isWin = false;
            auto ant = ((Ant *)(currentScene->gameObjects[i]));
            if (ant->timeToDestroy())
            {
                currentScene->destroyGameObject(i);
                --i;
                --gameObjectsSize;
            }
            for (unsigned j = 0; j < bulletsSize; ++j)
            {
                if (ant->aabb.isColliding(bullets[j].transform.getPosition()))
                {
                    ant->damage(1);
                    player->destroyBullet(j);
                    --j;
                    --bulletsSize;
                }
            }

            if (ant->aabb.isColliding(currentScene->gameObjects[0]->aabb) &&
                getTime() > 2.0f) // TODO check player's children collisions with ant too
            {
                if (getTime() - player->timeSinceDamage > 1.0f)
                {
                    player->damage(1.0f);
                    player->timeSinceDamage = getTime();
                    HUD.setHP(player->hp * 10);
                }
            }
        }
    }
    if (isWin)
    {
        ended = true;
    }
}
void App::start()
{
    for (unsigned i = 0; i < currentScene->gameObjects.size(); ++i)
    {
        currentScene->gameObjects[i]->start();
    }
    timeSinceStart.restart();
}
float App::getTime()
{
    return timeSinceStart.getElapsedTime().asSeconds();
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