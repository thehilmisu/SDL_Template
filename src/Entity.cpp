#include "Entity.hpp"

Entity::Entity(Vector2f p_pos, Vector2f p_size, SDL_Texture *p_tex)
    : pos(p_pos), tex(p_tex)
{
    currentFrame.x = p_pos.x;
    currentFrame.y = p_pos.y;
    currentFrame.w = p_size.x;
    currentFrame.h = p_size.y;
}


SDL_Texture* Entity::getTex()
{
    return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
    return currentFrame;
}