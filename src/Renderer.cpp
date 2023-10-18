#include <Renderer.h>
using namespace aw;
using namespace std;
Renderer::Renderer()
{
}
Renderer &Renderer::instance()
{
    static Renderer renderer;
    return renderer;
}
void Renderer::init()
{
    glewExperimental = true;
    glewInit();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mainShader = loadShaderProgram("Shaders/main.vert", "Shaders/main.frag");
    glUseProgram(mainShader);
    shadelessLocation = getUniformLocation("shadeless");
    skinnedLocation=getUniformLocation("skinned");
    glUseProgram(0);
    HUD.setShaderProgram(loadShaderProgram("Shaders/hud.vert", "Shaders/hud.frag"));
    assert(glGetError() == 0);
}
void Renderer::renderScene(Scene *scene)
{
    glUseProgram(mainShader);
    scene->camera.update();
    for (unsigned i = 0; i < scene->lights.size(); ++i)
    {
        scene->lights[i].update();
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUniform1i(shadelessLocation, 1);
    scene->skybox.draw();
    glUniform1i(shadelessLocation, 0);
    for (unsigned i = 0; i < scene->gameObjects.size(); ++i)
    {
        if (i == 1)
            continue; // muzzle
        if (scene->gameObjects[i]->getClass() == CLASSES::ANT)
            continue; // Draw ants last for better transpernecy
        scene->gameObjects[i]->draw();
    }
    for (unsigned i = 0; i < scene->gameObjects.size(); ++i)
    {
        if (scene->gameObjects[i]->getClass() != CLASSES::ANT)
            continue;
        scene->gameObjects[i]->draw();
    }
    
    glUniform1i(shadelessLocation, 1);
    scene->gameObjects[1]->draw();
    glUniform1i(shadelessLocation, 0);

    HUD.draw();
    assert(glGetError() == 0);
    WINDOW.internal.display();
}
GLuint Renderer::getMainShader()
{
    return mainShader;
}
void Renderer::terminate()
{
}
GLuint Renderer::getUniformLocation(const char *uniform)
{
    glUseProgram(mainShader);
    return glGetUniformLocation(mainShader, uniform);
}
GLuint Renderer::loadShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath)
{
    GLuint program;
    vector<char> vertexShaderCode = readBinFile(vertexShaderPath);
    vector<char> fragmentShaderCode = readBinFile(fragmentShaderPath);
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLint vertexShaderSize = vertexShaderCode.size();
    GLint fragmentShaderSize = fragmentShaderCode.size();
    char *pVertexShaderCode = vertexShaderCode.data();
    char *pFragmentShaderCode = fragmentShaderCode.data();
    glShaderSource(vertexShader, 1, &pVertexShaderCode, &vertexShaderSize);
    glShaderSource(fragmentShader, 1, &pFragmentShaderCode, &fragmentShaderSize);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);
#ifdef DEBUG
    GLint infoLogLen;
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLen);
    vector<char> infoLog(infoLogLen);
    glGetShaderInfoLog(vertexShader, infoLog.size(), nullptr, infoLog.data());
    infoLog.push_back('\0');
    printf(infoLog.data());
    infoLog.resize(0);
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLen);
    infoLog.resize(infoLogLen);
    glGetShaderInfoLog(fragmentShader, infoLog.size(), nullptr, infoLog.data());
    infoLog.push_back('\0');
    printf(infoLog.data());
    infoLog.resize(0);
#endif
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
#ifdef DEBUG
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);
    infoLog.resize(infoLogLen);
    glGetProgramInfoLog(program, infoLogLen, nullptr, infoLog.data());
    infoLog.push_back('\0');
    printf(infoLog.data());
#endif
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    assert(glGetError() == 0);
    return program;
}

GLuint Renderer::getSkinnedToggleLocation(){
    return skinnedLocation;
}