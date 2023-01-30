#include "Sounds.h"

Sounds::Sounds()
{
#ifdef _WIN32
   StepsBuffer.loadFromFile("sonds/usefull/Sand_Boots_Walking.wav");
   HurtBuffer.loadFromFile("sonds/usefull/21.wav");
#else
    StepsBuffer.loadFromFile("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/sonds/usefull/Sand_Boots_Walking.wav");
    HurtBuffer.loadFromFile("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/sonds/usefull/21.wav");
#endif // _WIN32

    steps.setBuffer(StepsBuffer);

    HurtSound.setBuffer(HurtBuffer);
    HurtSound.setVolume(10.f);
    HurtSound.setPitch(1.5f);
    //HurtSound.isRelativeToListener();
    //HurtSound.setMinDistance(80);
    //HurtSound.setAttenuation(1.64);

}
void Sounds::damaged(float x, float y, float dist) {
    float vol;
    vol = 20.f - dist * 0.0001;
    if (vol < 0) {
        vol = 0.f;
    }
    HurtSound.setVolume(vol);
    HurtSound.setPosition(x, -1000, y);
    HurtSound.play();
}
