#include <cassert>
#include <iostream>

#include "SDL.h"
#include "SDL_events.h"
#include "SDL_image.h"

#include "SDL_keycode.h"
#include "SDL_mouse.h"
#include "core/Engine.h"
#include "graphics/LairGraphic.h"
#include "graphics/TileGraphic.h"
#include "lair/Lair.h"
#include "lair/Tile.h"
#include "test.h"

// SDL defines a main function itself, so it has to be undefined such that the
// following main is picked up correctly
#undef main

long time_step(long time, long fps) { return (time * fps / 1000); }

int main(int, char**) {
    /*
    test::research_lab();
    test::bank();
    test::research_engine();
    */
    Lair lair(10, 10);
    Engine engine(nullptr, nullptr, &lair);
    lair.setEngine(&engine);

    lair.addTile(1, 0);
    lair.addTile(0, 0);
    lair.addTile(1, 1);
    lair.addTile(2, 1);
    lair.addTile(2, 2);
    lair.addTile(3, 1);

    lair.removeTile(1, 0);
    lair.addTile(1, 0);

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

    int i = 0;

    SDL_Event event;
    bool quit = false;
    int time = SDL_GetTicks();
    while (!quit) {
        int dt = SDL_GetTicks() - time;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
            if (event.type == SDL_MOUSEMOTION) {
                int x = (event.motion.x - 20) / TileGraphic::TILE_WIDTH;
                int y = (event.motion.y - 20) / TileGraphic::TILE_WIDTH;
                if (event.button.button == SDL_BUTTON(SDL_BUTTON_LEFT)) {
                    lair.addTile(x, y);

                } else if (event.button.button ==
                           SDL_BUTTON(SDL_BUTTON_RIGHT)) {
                    lair.removeTile(x, y);
                }
            }
        }

        engine.draw(renderer);

        time += dt;
    }
    return 0;
}
