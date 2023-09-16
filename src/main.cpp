#include <cassert>
#include <iostream>

#include "SDL.h"
#include "SDL_events.h"
#include "SDL_image.h"
#include "SDL_keycode.h"
#include "SDL_mouse.h"
#include "SDL_render.h"
#include "SDL_timer.h"
#include "SDL_ttf.h"

#include "core/Engine.h"
#include "core/UserInterface.h"
#include "graphics/LairGraphic.h"
#include "graphics/TextGraphic.h"
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
    Lair lair(15, 11);
    UserInterface ui;
    Engine engine(nullptr, nullptr, &lair, &ui);
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
    assert(TTF_Init() == 0);
    std::string base = SDL_GetBasePath();
    base += "res/Monocraft-no-ligatures.ttf";

    std::cout << base << std::endl;

    SDL_Window* window = SDL_CreateWindow("Pokeys & Shrews",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        0);
    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    TTF_Font* font = TTF_OpenFont(base.c_str(), 32);
    TextGraphic text("Text", font, renderer);
    text.setPosition(0, 0);

    std::string texts[] = {
        "Text #1",
        "Text #2",
        "Text #3",
    };

    int i = 0;

    SDL_Event event;
    bool quit = false;
    int last = SDL_GetTicks();
    int time = 0;
    while (!quit) {
        int dt = SDL_GetTicks() - last;
        last += dt;
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
        text.setColor(time % 255, 0, 0);

        ui.draw(renderer);
        text.draw(renderer);
        SDL_RenderPresent(renderer);

        time += dt;
        if (time > 1000) {
            time -= 1000;
            i = (i + 1) % 3;
            text.setText(texts[i]);
        }
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
