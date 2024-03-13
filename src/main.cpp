#include <iostream>
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include <memory>
#include <vector>

const int WIDTH = 1280, HEIGHT = 720;

std::vector<std::unique_ptr<Entity>> mapItems;

int main( int argc, char *argv[] )
{

    const int mapSize = 5;
    const char map[mapSize][mapSize] = {
        {'1', '0', '1', '0', '1'},
        {'0', '1', '0', '1', '0'},
        {'1', '0', '1', '0', '1'},
        {'0', '1', '0', '1', '0'},
        {'1', '0', '#', '0', '1'}
    };
 
    // Print the map
    for (int i = 0; i < mapSize; ++i) 
    {
        for (int j = 0; j < mapSize; ++j) {
            std::cout << map[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    if(SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        std::cout << "FAILED TO INIT SDL : " << SDL_GetError() << std::endl;
    }

    if(!IMG_Init(IMG_INIT_PNG))
    {
        std::cout << "IMG INIT has failed" << SDL_GetError() << std::endl;
    }

    RenderWindow window("GAME v1.0", WIDTH, HEIGHT);
    
    SDL_Texture *grassTexture = window.loadTexture("../res/gfx/ground_grass1.png");
    SDL_Texture *cobra = window.loadTexture("../res/gfx/cobra.png");
    SDL_Texture *knight = window.loadTexture("../res/gfx/hulking_knight.png");

    
    for (int i = 0; i < mapSize; ++i) 
    {
        for (int j = 0; j < mapSize; ++j) {
            if(map[i][j] == '1')
            {
                mapItems.push_back(std::make_unique<Entity>(Entity(Vector2f(i*32, j*32), Vector2f(32,32), grassTexture)));
            }                
            else if(map[i][j] == '0')
            {
                mapItems.push_back(std::make_unique<Entity>(Entity(Vector2f(i*32, j*32), Vector2f(32,32), knight)));
            }
            else
            {
                mapItems.push_back(std::make_unique<Entity>(Entity(Vector2f(i*64, j*176), Vector2f(64,176), cobra) ));
            }
        }
    }

    Entity player(Vector2f(10, 0),Vector2f(64,176), cobra);

    bool gameRunning = true;

    SDL_Event event;

    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = Utils::hireTimeInSeconds();

    while(gameRunning)
    {
        int startTicks = SDL_GetTicks();
        float newTime = Utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;

        currentTime = newTime;

        accumulator += frameTime;

        while(accumulator >= timeStep)
        {
            while (SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT)
                {
                    gameRunning = false;
                }
            }

            accumulator -= timeStep;
        }

        const float alpha = accumulator / timeStep;

        window.clear();

        window.render(player);
        // for(auto &item : mapItems)
        //     window.render(*item);


        window.display();

        int frameTicks = SDL_GetTicks() - startTicks;
        if(frameTicks < 1000 / window.getRefreshRate())
            SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
    }

    window.cleanUp();
    SDL_Quit();

}
