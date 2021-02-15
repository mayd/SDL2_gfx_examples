#include <stdio.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#define WIDTH 600
#define HEIGHT 300

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

    int quit = 0;
    while (!quit)
    {
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = 1;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        thickLineColor(renderer, 10, 10, 60, 60, 5, 0xFF0FFFF0) ;
        circleColor(renderer, 150, 40, 30, 0xFF00FF00);
        arcColor(renderer, 250, 40, 30, 45, 200, 0xFF0000FF);
        aacircleColor(renderer, 350, 40, 30, 0xFF00FF00);
        filledCircleColor(renderer, 450, 40, 30, 0xFF00FFFF);
        ellipseColor(renderer, 550, 40, 30, 10, 0xFF00FF00);
        aaellipseColor(renderer, 50, 140, 30, 10, 0xFF00FF00);
        filledEllipseColor(renderer, 150, 140, 30, 10, 0xFF00FF00);
        pieColor(renderer, 250, 140, 30, -45, 45, 0xFF00FF00);
        filledPieColor(renderer, 350, 140, 30, 45, -45, 0xFF00FF00);
        aatrigonColor(renderer, 400, 140, 480, 140, 440, 170, 0xFF0FF0FF);

        Sint16 ptx[] = {510,590, 590, 550, 510};
        Sint16 pty[] = {130, 130, 180, 150, 180};
        aapolygonColor(renderer, ptx, pty, 5, 0xFF0F0F0F);

        rectangleColor(renderer, 20, 210, 90, 260, 0xFF000000);
        pixelColor(renderer, 150, 250, 0xFF0FA0A0);
        boxColor(renderer, 220, 210, 290, 260, 0xFFCFBFAF);

        characterColor(renderer, 350, 230, 'X', 0xFF0000FF);
        stringColor(renderer, 450, 230, "LiTi & sesajad", 0xFFAABBCC);


        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
