#pragma once

#include <SDL2/SDL.h>

#include <string>


struct Key{
    bool pressed = false;
    bool released = false;
};

struct Mouse{
    bool RMBpressed = false, RMBreleased = false;
    bool LMBpressed = false, LMBreleased = false;
    bool MMBpressed = false, MMBreleased = false;

    int x, y;
};

class Engine
{
public:

    static Engine& Get(){
        return instance;
    }

    bool Init(int w, int h, const char* title);
    void HandleEvents();
    void ClearScreen(uint8_t R, uint8_t G, uint8_t B);
    void Draw(SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dest);
    void Present();

    bool isRunning() { return running; }
    void Quit() { running = false; }

    Key* getInput() { return input; }
    Mouse& getMouseState() { return mouse; }

    SDL_Texture* loadTexture(const char* path);

private:
    Engine() {}

    static Engine instance;

    SDL_Renderer* renderer;
    SDL_Window* window;

    SDL_Event event;

    bool running = false;

    Key input[256];
    Mouse mouse;
};


struct Button{

    Button(const char* texPath, int x, int y, int w, int h, void (*function)()) : func(function)
    {
        tex = Engine::Get().loadTexture(texPath);
        src = {0, 0, w, h};
        dest = {x, y, w, h};
    }

    void changeTexCoord(int x, int y, int w, int h)
    {
        src = {x, y, w, h};
    }

    void update(float dt)
    {
        if(mouseOver() && Engine::Get().getMouseState().LMBreleased)
            func();
    }

    void draw()
    {
        Engine::Get().Draw(tex, &src, &dest);
    }

    bool clicked()
    {
        return mouseOver() &&  Engine::Get().getMouseState().LMBreleased;
    }

    bool mouseOver()
    {
        int mouseX = Engine::Get().getMouseState().x;
        int mouseY = Engine::Get().getMouseState().y;

        return (mouseX > dest.x && mouseX < dest.x + dest.w && mouseY > dest.y && mouseY < dest.y + dest.h);
    }
    
protected:
    SDL_Texture* tex;
    SDL_Rect src, dest;

    void (*func)();


};

void openWebLink(const std::string& url);