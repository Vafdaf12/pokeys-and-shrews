#include <iostream>

#include "research/ResearchLab.h"

// SDL defines a main function itself, so it has to be undefined such that the
// following main is picked up correctly
#undef main

long time_step(long time, long fps) { return (time * fps / 1000); }

int main(int, char**) {
    ResearchLab lab;
    lab.enqueue(new ResearchItem("Item1", 10));
    lab.enqueue(new ResearchItem("Item2", 2));
    lab.enqueue(new ResearchItem("Item3", 5));

    for (int i = 0; i < 4; i++) {
        lab.tick();
    }
    std::cout << lab << std::endl;
    for (int i = 0; i < 6; i++) {
        lab.tick();
    }
    std::cout << lab << std::endl;
    delete lab.cancel(1);
    delete lab.cancel(0);
    std::cout << lab << std::endl;

    /*
    assert(SDL_Init(SDL_INIT_VIDEO) >= 0);
    std::string base = SDL_GetBasePath();
    base += "res/Spritesheet.png";

    std::cout << base << std::endl;

    SDL_Window* window = SDL_CreateWindow("Pokeys & Shrews",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        0);
    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    SDL_Surface* image = IMG_Load(base.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect rect = {100, 100, 100, 100};
    SDL_Rect src = {0, 0, 32, 32};

    SDL_Event event;
    bool quit = false;
    int time = SDL_GetTicks();
    while (!quit) {
        int dt = SDL_GetTicks() - time;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, &src, &rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawLine(renderer, (time) % 800, 0, 800 - (time % 800), 600);
        SDL_RenderPresent(renderer);

        time += dt;
        src.y = (time_step(time, 10)%4)*32;
    }
    */
    return 0;
}
