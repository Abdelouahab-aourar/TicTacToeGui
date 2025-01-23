#include "Engine.hpp"
#include <iostream>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

Engine Engine::instance;

bool Engine::Init(int w, int h, const char* title)
{
    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
        printf("failed to init SDL. Err: %s\n", SDL_GetError());
        return false;
    }
    if(!IMG_Init(IMG_INIT_PNG))
    {
        printf("failed to init SDL_image. Err: %s\n", SDL_GetError());
        return false;
    }
    if(TTF_Init())
    {
        printf("failed to init SDL_ttf. Err: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(title, 300, 300, w, h, SDL_WINDOW_RESIZABLE);
    if(!window)
    {
        printf("failed to Create window. Err: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        printf("failed to Create renderer. Err: %s\n", SDL_GetError());
        return false;
    }

    running = true;

    return true;
}

void Engine::HandleEvents()
{
    for(auto b : input)
        b.released = 0;

    mouse.LMBreleased = 0;
    mouse.RMBreleased = 0;
    mouse.MMBreleased = 0;

    while(SDL_PollEvent(&event))
    {
        mouse.x = event.button.x;
        mouse.y = event.button.y;
        
        switch(event.type)
        {
            case SDL_QUIT:
                running = false;
                break;
            //keyboard input
            case SDL_KEYDOWN:
                input[event.key.keysym.scancode].pressed = true;
                break;
            case SDL_KEYUP:
                input[event.key.keysym.scancode].pressed = false;
                input[event.key.keysym.scancode].released = true;
                break;
            //mouse input
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT)
                    mouse.LMBpressed = 1;
                else if(event.button.button == SDL_BUTTON_RIGHT)
                    mouse.RMBpressed = 1;
                else if(event.button.button == SDL_BUTTON_MIDDLE)
                    mouse.MMBpressed = 1;
                mouse.x = event.button.x;
                mouse.y = event.button.y;
                break;
            case SDL_MOUSEBUTTONUP:                
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    mouse.LMBpressed = 0;
                    mouse.LMBreleased = 1;
                }
                else if(event.button.button == SDL_BUTTON_LEFT)
                {
                    mouse.LMBpressed = 0;
                    mouse.LMBreleased = 1;
                }
                else if(event.button.button == SDL_BUTTON_LEFT)
                {
                    mouse.LMBpressed = 0;
                    mouse.LMBreleased = 1;
                }
                break;

            default:
                break;
        }
    }
}

SDL_Texture* Engine::loadTexture(const char* path)
{
    SDL_Surface* temp = IMG_Load(path);
    if(!temp)
    {
        printf("failed to load surface from file %s. Err: %s\n", path, SDL_GetError());
        return nullptr;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, temp);
    if(!tex)
    {
        printf("failed to Create texture from file %s. Err: %s\n", path, SDL_GetError());
        return nullptr;
    }

    SDL_FreeSurface(temp);

    return tex;
}

void Engine::ClearScreen(uint8_t R, uint8_t G, uint8_t B)
{
    SDL_SetRenderDrawColor(renderer, R, G, B, 255);
    SDL_RenderClear(renderer);
}

void Engine::Draw(SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dest)
{
    SDL_RenderCopy(renderer, tex, src, dest);
}

void Engine::Present()
{
    SDL_RenderPresent(renderer);
}


void openWebLink(const std::string& url) {
#ifdef _WIN32
    // Windows command
    std::string command = "start " + url;
#elif __APPLE__
    // macOS command
    std::string command = "open " + url;
#elif __linux__
    // Linux command
    std::string command = "xdg-open " + url;
#else
    std::cerr << "Unsupported platform!" << std::endl;
    return;
#endif

    // Execute the command
    if (std::system(command.c_str())) {
        std::cerr << "Failed to open the URL: " << url << std::endl;
    }
}