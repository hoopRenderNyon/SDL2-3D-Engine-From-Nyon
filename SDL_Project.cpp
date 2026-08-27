#include <iostream>
#include <SDL2/SDL.h>

struct _2DLine
{
    int x, y, x1, y1;
};

bool Loop();
bool Init();
void Quit();

SDL_Window *window;
SDL_Renderer *renderer;

int main(int argc, char** args){
    if (Init()){
        while(Loop()){
            SDL_Delay(20);
        }
    }
    Quit();
}

bool Loop(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:
                return false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        return false;
                        break;
                }
            default:
                return true;
                break;
        }
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderPresent(renderer);
    return true;
}

bool Init(){
    SDL_Init(SDL_INIT_EVERYTHING);
    int result = SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);
    if (result != 0){
        std::cout << "Feiled of Window and Render: %s" << SDL_GetError();
        return false;
    }
    return true;
}

void Quit(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;
    SDL_Quit();
}