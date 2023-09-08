#include "SDL_filesystem.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include <assert.h>
#include <iostream>

#include <SDL.h>
#include <string>

// SDL defines a main function itself, so it has to be undefined such that the
// following main is picked up correctly
#undef main

int main(int, char**) {
    assert(SDL_Init(SDL_INIT_VIDEO) >= 0);
    std::string base = SDL_GetBasePath();
    base += "res/Hero1.bmp"; 

    std::cout << base << std::endl;

    SDL_Window* window = SDL_CreateWindow("Pokeys & Shrews",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        0);
    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    SDL_Surface* image = SDL_LoadBMP(base.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect rect = {100, 100, 400, 100};

    SDL_Event event;
    bool quit = false;
    int time = SDL_GetTicks();
    while (!quit) {
        int dt = SDL_GetTicks() - time;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawLine(renderer, (time) % 800, 0, 800 - (time % 800), 600);
        SDL_RenderPresent(renderer);

        time += dt;
    }
    return 0;
}
