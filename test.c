#include <stdio.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#define WIDTH 640
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
      thickLineColor(renderer, 0, 0, WIDTH, HEIGHT, 20, 0xFF00FFFF) ;
      thickLineColor(renderer, 0, HEIGHT, WIDTH, 0, 20, 0xFF00FFFF) ;
      SDL_RenderPresent(renderer);
      SDL_Delay(10);
   }

   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
   return 0;
}
