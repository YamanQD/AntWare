#include <SoundBuffers.h>
using namespace aw;
using namespace sf;

SoundBuffer gunShot, footsteps;

void SoundBuffers::init()
{
	gunShot.loadFromFile("Assets/Audio/gunshot.wav");
	footsteps.loadFromFile("Assets/Audio/playerFootsteps.ogg");
}