#include <Menu.h>
using namespace aw;
using namespace std;
using namespace sf;
using namespace glm;
Menu::Menu() {}
Menu &Menu::instance()
{
    static Menu menu;
    return menu;
}
void Menu::init(vector<string> levels, vector<string> labels)
{
    this->levels = levels;
    for (unsigned i = 0; i < labels.size(); ++i)
    {
        GLuint tex;
        Hud::loadTexture(labels[i].c_str(), tex);
        this->labels.push_back(tex);
    }
    Hud::loadTexture("Assets/Textures/Main Menu BG.png", backgroundTex);
}
string Menu::loop()
{
    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D((-16.0f / 2.0f),
               (16.0f / 2.0f),
               (-9.0f / 2.0f),
               (9.0f / 2.0f));
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    bool isSelecting = true;
    while (isSelecting)
    {
        Event event;
        while (WINDOW.internal.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                return "exit";
            case Event::KeyReleased:
                if (event.key.code == Keyboard::Escape)
                {
                    return "exit";
                }
                if (event.key.code == Keyboard::Enter)
                {
                    isSelecting = false;
                }
                else if (event.key.code == Keyboard::Down)
                {
                    selectedLvl++;
                    selectedLvl = selectedLvl % levels.size();
                }
                else if (event.key.code == Keyboard::Up)
                {
                    if (selectedLvl == 0)
                    {
                        selectedLvl = levels.size() - 1;
                    }
                    else
                    {
                        selectedLvl--;
                    }
                }
            default:
                break;
            }
        }
        vec2 labelPos = firstLevelPos;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Hud::drawQuad(backgroundTex, {0, 0}, backgroundSize);
        for (unsigned i = 0; i < labels.size(); ++i)
        {
            if (i != selectedLvl)
            {
                Hud::drawQuad(labels[i], labelPos, labelSize, dimColor);
            }
            else
            {
                Hud::drawQuad(labels[i], labelPos, labelSize);
            }
            labelPos.y += yMargain;
        }
        WINDOW.internal.display();
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 1.0f);
    return levels[selectedLvl];
}