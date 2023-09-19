#include <cassert>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>

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
#include "core/EventLoop.h"
#include "core/ResourceManager.h"
#include "core/Storyteller.h"
#include "core/Timer.h"
#include "core/UserInterface.h"
#include "graphics/HeroGraphic.h"
#include "graphics/LairExplorerGraphic.h"
#include "graphics/TextGraphic.h"
#include "graphics/TileGraphic.h"
#include "hero/Hero.h"
#include "lair/DepthFirstExplorer.h"
#include "lair/Lair.h"
#include "lair/LairExplorer.h"
#include "lair/Tile.h"
#include "research/ResearchLab.h"
#include "research/ResearchTask.h"
#include "test.h"
#include "trap/DamageTrap.h"

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
    srand(time(nullptr));
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

    ResearchLab lab;
    Lair lair(15, 11);
    UserInterface ui(renderer, font);
    Bank bank(100);
    Storyteller storyteller;
    Engine engine(&lab, &bank, &lair, &ui, &storyteller);
    lair.setEngine(&engine);
    bank.setEngine(&engine);
    storyteller.setEngine(&engine);

    lair.addTile(1, 0);
    lair.addTile(0, 0);
    lair.addTile(1, 1);
    lair.addTile(2, 1);
    lair.addTile(2, 2);
    lair.addTile(3, 1)->addTrap(new DamageTrap(5));

    lair.removeTile(1, 0);
    lair.addTile(1, 0);

    SDL_Event event;
    int last = SDL_GetTicks();

    Timer timer(100);
    EditState editState = ES_NONE;
    int n = 1;

    EventLoop eventLoop;
    eventLoop.onMouseDown(EventLoop::BUTTON_LEFT, [&](EventLoop::EventType e) {
        auto [x, y] = getTilePosition(event);
        if (!lair.getTile(x, y)) editState = ES_ADD;
        else editState = ES_FORT;
    });
    eventLoop.onMouseDown(EventLoop::BUTTON_RIGHT, [&](EventLoop::EventType e) {
        auto [x, y] = getTilePosition(event);
        if (!lair.getTile(x, y)) return;
        editState = ES_REM;
    });
    auto stopEdit = [&](auto) { editState = ES_NONE; };

    eventLoop.onMouseUp(
        EventLoop::BUTTON_LEFT | EventLoop::BUTTON_RIGHT, stopEdit);

    eventLoop.onKeyPressed(SDLK_TAB, [&](auto) {
        engine.researchRequested(new ResearchTask(
            "Trap #" + std::to_string(n++), 1000, 10, &engine));
    });
    eventLoop.onKeyPressed(SDLK_UP, [&](auto) { bank.deposit(1); });
    eventLoop.onKeyPressed(SDLK_DOWN, [&](auto) {
        if (bank.sufficientFunds(1)) bank.deposit(1);
    });

    while (!eventLoop.shouldQuit()) {
        int dt = SDL_GetTicks() - last;
        last += dt;
        SDL_Point p = {-1, -1};

        while (SDL_PollEvent(&event)) {
            eventLoop.handleEvent(event);
            p = getTilePosition(event);
        }

        switch (editState) {
        case ES_FORT: lair.fortifyTile(p.x, p.y); break;
        case ES_ADD: lair.addTile(p.x, p.y); break;
        case ES_REM: lair.removeTile(p.x, p.y); break;
        case ES_NONE: break;
        }
        lab.update(dt);
        storyteller.update(dt);

        ui.draw();
        /*
        for (auto& g : explorerGraphics) {
            g.update(dt);
            g.draw(renderer);
        }
        */

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}
