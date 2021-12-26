#pragma once
#include <SFML/Audio.hpp>
namespace aw
{
	class SoundBuffers
	{
	public:
		static sf::SoundBuffer gunShot, footsteps;
		static void init();
	};
}