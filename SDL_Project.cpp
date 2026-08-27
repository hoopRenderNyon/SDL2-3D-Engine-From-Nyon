#include <iostream>
#include <SDL2/SDL.h>
#include <algorithm>
#include <cmath>
#include <vector>

struct _2DLine
{
    int x, y, x1, y1;
};
struct Point{
    int x, y;
};
struct Point3D{
    int x, y, z;
};

bool Loop();
bool Init();
void Quit();

int POV = 60;
const Point s_z = {640, 320};
SDL_Window *window;
SDL_Renderer *renderer;
class SDL3D{
public:
    Point Trans3D_to_2D(Point3D point){
        float W = (float)s_z.x;
        float H = (float)s_z.y;
        float aspect = W/H;

        float povRad = POV * 3.14159265f / 180.0f;
        float tanHaif = tan(povRad / 2.0f);
        if (point.z <= 0.001f) {return {999, 999};}

        float ndc_x = point.x / (point.z * tanHaif * aspect);
        float ndc_y = point.x / (point.z * tanHaif);

        float x_f = (ndc_x + 1.0f) * (W / 2.0f);
        float y_f = (1.0f - ndc_y) * (H / 2.0f);
        
        int x_int = (int)std::round(x_f);
        int y_int = (int)std::round(y_f);

        x_int = std::clamp(x_int, 0, ((int)W - 1));
        y_int = std::clamp(y_int, 0, ((int)W - 1));

        return {x_int, y_int};
    }
};

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
    int result = SDL_CreateWindowAndRenderer(s_z.x, s_z.y, 0, &window, &renderer);
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