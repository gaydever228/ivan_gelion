#pragma once
#include "Libraries.h"

class Entity
{

public:

    String File;
    Image image;
    Texture texture;
    Sprite sprite;
    float x, y, w, h, dx, dy, speed, animation_speed, current_frame;
    int xBlocks, yBlocks;
    int direction, health;
    bool is_life, is_bullet;

    Entity(String F, float X, float Y, float W, float H);

    ~Entity();

    virtual void update(float time, bool** Map);

    virtual void interaction_with_map(bool** Map);

    virtual void animate(int dir);

    void sleepcp(int milliseconds);
};