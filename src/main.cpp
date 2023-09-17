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

#include "bank/Bank.h"
#include "core/Engine.h"
#include "core/ResourceManager.h"
#include "core/UserInterface.h"
#include "graphics/LairExplorerGraphic.h"
#include "graphics/LairGraphic.h"
#include "graphics/TextGraphic.h"
#include "graphics/TileGraphic.h"
#include "lair/DepthFirstExplorer.h"
#include "lair/Lair.h"
#include "lair/LairExplorer.h"
#include "lair/Tile.h"
#include "test.h"

// SDL defines a main function itself, so it has to be undefined such that the
// following main is picked up correctly
#undef main

long time_step(long time, long fps) { return (time * fps / 1000); }

enum EditState { ES_NONE = 0, ES_FORT = 2, ES_ADD = 1, ES_REM = -1 };

SDL_Point getTilePosition(SDL_Event ev) {
    SDL_Point p = {0, 0};
    if (ev.type == SDL_MOUSEBUTTONDOWN || ev.type == SDL_MOUSEBUTTONUP) {
        p.x = ev.button.x - 20;
        p.y = ev.button.y - 20;
    } else if (ev.type == SDL_MOUSEMOTION) {
        p.x = ev.motion.x - 20;
        p.y = ev.motion.y - 20;
    }
    p.x /= TileGraphic::TILE_WIDTH;
    p.y /= TileGraphic::TILE_WIDTH;
    return p;
}

int main(int, char**) {
    /*
    test::research_lab();
    test::bank();
    test::research_engine();
    */
    assert(SDL_Init(SDL_INIT_VIDEO) >= 0);

    SDL_Window* window = SDL_CreateWindow("Pokeys & Shrews",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        0);
    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    TTF_Font* font =
        ResourceManager::instance().loadFont("Monocraft-no-ligatures.ttf", 32);

    Lair lair(15, 11);
    UserInterface ui(font, renderer);
    Bank bank(100);
    Engine engine(nullptr, &bank, &lair, &ui);
    lair.setEngine(&engine);
    bank.setEngine(&engine);

    lair.addTile(1, 0);
    lair.addTile(0, 0);
    lair.addTile(1, 1);
    lair.addTile(2, 1);
    lair.addTile(2, 2);
    lair.addTile(3, 1);

    lair.removeTile(1, 0);
    lair.addTile(1, 0);

    DepthFirstExplorer e(lair.getTile(0, 0));
    LairExplorerGraphic g(&e);

    SDL_Event event;
    bool quit = false;
    int last = SDL_GetTicks();
    EditState editState = ES_NONE;
    while (!quit) {
        int dt = SDL_GetTicks() - last;
        last += dt;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;

            SDL_Point p = getTilePosition(event);
            Tile* cur = lair.getTile(p.x, p.y);

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                switch (event.button.button) {
                case SDL_BUTTON_LEFT: editState = cur ? ES_FORT : ES_ADD; break;
                case SDL_BUTTON_RIGHT:
                    editState = cur ? ES_REM : ES_NONE;
                    break;
                }
            } else if (event.type == SDL_MOUSEBUTTONUP) {
                editState = ES_NONE;
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                case SDLK_SPACE: e.next(); break;
                case SDLK_TAB: e.backtrack(3); break;
                case SDLK_UP: bank.deposit(1); break;
                case SDLK_DOWN:
                    if (bank.sufficientFunds(1)) bank.withdraw(1);
                    break;
                }
            }
            switch (editState) {

            case ES_FORT:
                if (cur) cur->fortify();
                break;

            case ES_ADD: lair.addTile(p.x, p.y); break;
            case ES_REM: lair.removeTile(p.x, p.y); break;
            case ES_NONE: break;
            }
        }

        ui.draw(renderer);
        g.update();
        g.draw(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}
