#include "Map.h"
#ifdef _WIN32
Map::Map():Entity("MapTextures.png", -1000 , -1000 , 512, 128)
{
}
#else
Map::Map():Entity("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/MapTextures.png", -1000 , -1000 , 512, 128)
{
}
#endif // _WIN32
