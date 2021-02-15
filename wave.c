#include <stdio.h>
#include <math.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#define WIDTH 1000
#define HEIGHT 480

#define maxN 2000
double ys[maxN];
double xs[maxN];

int main(int argc, char* argv[])
{

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf ("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Wave test", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
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

    int cycle = 0;

    int quit = 0;

    int delay = 10;
    int baseX = 100;
    int baseY = 240;

    double dX = 3.0;
    double zY = 1/10.0;
    int coY = 30;

    int tot = 0;
    double t = 0;
    int fun = 5; 

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
                        zY -= 0.01;
                        break;
                    case SDLK_RIGHT:
                        zY += 0.01;
                        break;
                    case SDLK_z:
                        fun ++;
                        break;
                    case SDLK_x:
                        fun --;
                        if( fun == 0 ) fun = 1;
                        break;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        for(int i = 0; i < maxN; i++)
            xs[i] = xs[i] + dX;

        for(int i = maxN - 1 ; i > 0 ; i--) { 
            ys[i] = ys[i-1]; 
            xs[i] = xs[i-1];
        }
        t += zY;
        ys[0] = baseY + coY * cos(t);
        xs[0] = baseX; 
        tot++; 
        if( tot > maxN ) tot--;




        hlineColor(renderer, 0, WIDTH-1, baseY, 0xFFFFFFFF);
        vlineColor(renderer, baseX, 0, HEIGHT-1, 0xFFFFFFFF);

        for(int i = 0; i + fun < tot; i++) {
            //filledCircleColor(renderer, xs[i], ys[i], 3, 0xFF0000FF);
            thickLineColor(renderer, xs[i], ys[i], xs[i+fun], ys[i+fun], 1, 0xFF00FF00);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(delay);
        cycle++;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
