#ifndef SOUNDS_H
#define SOUNDS_H
#include "Libraries.h"

class Sounds
{
public:
    Sounds();
    sf::SoundBuffer StepsBuffer;
    sf::Sound steps;
    sf::SoundBuffer HurtBuffer;
    sf::Sound HurtSound;
    void damaged(float x, float y, float dist);
    void TheWall(float x, float y, float dist);
};

#endif // SOUNDS_H