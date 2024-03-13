#include "RenderWindow.hpp"
#include <iostream>

RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                                p_w, p_h,SDL_WINDOW_SHOWN);


    if(window == NULL)
    {
        std::cout << "Window Failed to open" << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


}

SDL_Texture* RenderWindow::loadTexture(const char *p_filePath)
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if(texture == NULL)
        std::cout << "Failed to load texture" << SDL_GetError() << std::endl;

    return texture;
}

void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}

