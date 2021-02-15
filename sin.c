#include <stdio.h>
#include <math.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#define WIDTH 1000
#define HEIGHT 480

int main(int argc, char* argv[])
{

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf ("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL2_gfx test", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    if (window == NULL)
    {
        printf ("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return 2;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        printf ("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        return 3;
    }

    SDL_Event e;

    int cycles = 0;
    int quit = 0;
    int baseX = 100;
    int baseY = 240;
    int coX = 20;
    int coY = 100;
    double z = 1/20.0;

    while (!quit)
    {
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = 1;
            else if( e.type == SDL_KEYDOWN ) { 
                switch( e.key.keysym.sym ) { 
                    case SDLK_UP:
                        coY++; 
                        break;
                    case SDLK_DOWN:
                        coY--;
                        break;
                    case SDLK_LEFT:
                        coX--;
                        break;
                    case SDLK_RIGHT:
                        coX++;
                        break;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);


        hlineColor(renderer, 0, WIDTH-1, baseY, 0xFFFFFFFF);
        vlineColor(renderer, baseX, 0, HEIGHT-1, 0xFFFFFFFF);
        for(int tt = 0; tt < 2000; tt++) { 
            double t = tt * z;
            //filledCircleColor( renderer, baseX + coX * t, baseY + coY * sin(t) , 3, 0xFF00FF00);
            thickLineColor( renderer, baseX + coX * t, baseY + coY * sin(t), baseX + coX * (t+20*z), baseY + coY * sin(t+20*z), 1, 0xFF703799);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
        cycles++;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
