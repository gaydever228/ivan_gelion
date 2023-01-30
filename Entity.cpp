#include "Entity.h"

Entity::Entity(String F, float X, float Y, float W, float H)
{
    dx = 0; dy = 0; speed = 0; direction = 0;
    is_life = true;
    is_bullet = false;
    File = F;//им€ файла+расширение
    w = W; h = H;//высота и ширина
#ifdef _WIN32
    image.loadFromFile("Images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. ¬ нашем случае "hero.png" и получитс€ запись идентична€ image.loadFromFile("images/hero/png");

#else
    image.loadFromFile(File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. ¬ нашем случае "hero.png" и получитс€ запись идентична€ image.loadFromFile("images/hero/png");
#endif // _WIN32
    texture.loadFromImage(image);//закидываем наше изображение в текстуру
    sprite.setTexture(texture);//заливаем спрайт текстурой
    x = X; y = Y;//координата по€влени€ спрайта
    sprite.setPosition(x, y);
}

Entity::~Entity()
{
}


void Entity::interaction_with_map(bool** MAP)//ф-ци€ взаимодействи€ с картой
{
}

void Entity::animate(int dir)
{
}

void Entity::sleepcp(int milliseconds) // Cross-platform sleep function
{
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif // _WIN32
}


void Entity::update(float time, bool** Map)
{
}
