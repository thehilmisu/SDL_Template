#include <iostream>
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include <memory>
#include <vector>
#include <math.h>  

const int WIDTH = 1280, HEIGHT = 720;

// Will be used later to convert from radians to degrees
#define	PI		(3.14f)
#define RAD_TO_DEG	((X) * (180.0f / PI))

std::vector<std::unique_ptr<Entity>> mapItems;

float LookAt(Vector2f p2, Vector2f position)
{
    int DeltaX;
    int DeltaY;
    float result;
    DeltaX = position.x - p2.x;
    DeltaY = position.y - p2.y;
    result = (std::atan2(-DeltaX, DeltaY) * 180.00000) / 3.141592;
    return  result;
}

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
    
    SDL_Texture *grassTexture = window.loadTexture("../res/gfx/ground_grass_1.png");
    SDL_Texture *cobra = window.loadTexture("../res/gfx/cobra.png");
    SDL_Texture *knight = window.loadTexture("../res/gfx/hulking_knight.png");

    
    // for (int i = 0; i < mapSize; ++i) 
    // {
    //     for (int j = 0; j < mapSize; ++j) {
    //         if(map[i][j] == '1')
    //         {
    //             mapItems.push_back(std::make_unique<Entity>(Entity(Vector2f(i*32, j*32), Vector2f(32,32), grassTexture)));
    //         }                
    //         else if(map[i][j] == '0')
    //         {
    //             mapItems.push_back(std::make_unique<Entity>(Entity(Vector2f(i*32, j*32), Vector2f(32,32), knight)));
    //         }
    //         else
    //         {
    //             mapItems.push_back(std::make_unique<Entity>(Entity(Vector2f(i*64, j*176), Vector2f(64,176), cobra) ));
    //         }
    //     }
    // }

    //only helicopter is in the mapItems currently
    mapItems.push_back(std::make_unique<Entity>(Vector2f(600, 320), cobra));

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
            if ( SDL_QUIT == event.type )
            { break; }

            if ( SDL_MOUSEMOTION == event.type )
            {
                int x, y;
                SDL_GetMouseState( &x, &y );

                std::cout << x << " : " << y << std::endl;

                //move texture along with mouse
                //mapItems.at(0).get()->setPos(Vector2f(x,y));

                //Rotate texture according to mouse positio

                // Get the angle of the 2D vector
                float angle = LookAt(Vector2f(x,y), mapItems.at(0).get()->getPos());
                mapItems.at(0).get()->setAngle(angle);
                mapItems.at(0).get()->setScale(64, 176);
                

            }

            if ( SDL_MOUSEBUTTONDOWN == event.type )
            {
                if ( SDL_BUTTON_LEFT == event.button.button )
                { std::cout << "Left mouse button is down" << std::endl; }
                else if ( SDL_BUTTON_RIGHT == event.button.button )
                { std::cout << "Right mouse button is down" << std::endl; }
                else if ( SDL_BUTTON_MIDDLE == event.button.button )
                { std::cout << "Middle mouse button is down" << std::endl; }
            }

            if ( SDL_MOUSEBUTTONUP == event.type )
            {
                if ( SDL_BUTTON_LEFT == event.button.button )
                { std::cout << "Left mouse button is up" << std::endl; }
                else if ( SDL_BUTTON_RIGHT == event.button.button )
                { std::cout << "Right mouse button is up" << std::endl; }
                else if ( SDL_BUTTON_MIDDLE == event.button.button )
                { std::cout << "Middle mouse button is up" << std::endl; }
            }

            if ( SDL_MOUSEWHEEL == event.type )
            {
                if ( event.wheel.y > 0 ) // scroll up
                { std::cout << "Mouse wheel is scrolling up" << std::endl; }
                else if ( event.wheel.y < 0 ) // scroll down
                { std::cout << "Mouse wheel is scrolling down" << std::endl; }

                if ( event.wheel.x > 0 ) // scroll right
                { std::cout << "Mouse wheel is scrolling right" << std::endl; }
                else if ( event.wheel.x < 0 ) // scroll left
                { std::cout << "Mouse wheel is scrolling left" << std::endl; }
            }

            if ( SDL_KEYDOWN == event.type )
            {
                //std::cout << "Key is down" << std::endl;

                if ( SDLK_a == event.key.keysym.sym )
                { std::cout << "A is down - Move left" << std::endl; }
                else if ( SDLK_s == event.key.keysym.sym )
                { std::cout << "S is down - Move down" << std::endl; }
                else if ( SDLK_d == event.key.keysym.sym )
                { std::cout << "D is down - Move right" << std::endl; }
                else if ( SDLK_w == event.key.keysym.sym )
                { std::cout << "W is down - Move up" << std::endl; }
            }
            else if ( SDL_KEYUP == event.type )
            {
                //std::cout << "Key is up" << std::endl;
                if ( SDLK_a == event.key.keysym.sym )
                { std::cout << "A is up - Stop moving left" << std::endl; }
                else if ( SDLK_s == event.key.keysym.sym )
                { std::cout << "S is up - Stop moving down" << std::endl; }
                else if ( SDLK_d == event.key.keysym.sym )
                { std::cout << "D is up - Stop moving right" << std::endl; }
                else if ( SDLK_w == event.key.keysym.sym )
                { std::cout << "W is up - Stop moving up" << std::endl; }
            }
            }

            accumulator -= timeStep;
        }

        const float alpha = accumulator / timeStep;

        window.clear();

        window.renderT(*mapItems.at(0).get());
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
