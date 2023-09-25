#include "Game.h"

#include "core/Engine.h"
#include "core/Storyteller.h"
#include "core/UserInterface.h"
#include "editor/TrapSelector.h"
#include "entity/Bank.h"
#include "entity/DamageTrap.h"
#include "entity/StunTrap.h"
#include "entity/TeleportTrap.h"
#include "graphics/TileGraphic.h"
#include "lair/Lair.h"
#include "raylib.h"
#include <memory>
#include <queue>
#include <stdlib.h>

#include "research/ResearchLab.h"
#include "research/TrapResearch.h"

void Game::init() {
    srand(static_cast<unsigned int>(time(nullptr)));

    SetTraceLogLevel(LOG_WARNING);
    InitWindow(800, 600, "Pokeys & Shrews");
    _font = LoadFont("res/Monocraft-no-ligatures.ttf");

    _lab = std::make_unique<ResearchLab>();
    _lair = std::make_unique<Lair>(12, 10);
    _bank = std::make_unique<Bank>(100);
    _storyteller = std::make_unique<Storyteller>(3, 3);
    _gui = std::make_unique<UserInterface>(_font);
    _trapSelector = std::make_unique<TrapSelector>(_font);
    _trapSelector->setPosition({20, 200});

    _engine = std::make_unique<Engine>(_lab.get(),
        _bank.get(),
        _lair.get(),
        _gui.get(),
        _storyteller.get(),
        _trapSelector.get());

    _gui->setEngine(_engine.get());
    _lab->setEngine(_engine.get());
    _lair->setEngine(_engine.get());
    _bank->setEngine(_engine.get());
    _storyteller->setEngine(_engine.get());

    loadMap("res/map.txt");
    _bank->setBalance(100);

    _engine->researchManager()->addResearch(new TrapResearch(
        (new DamageTrap(2, _engine.get())), 5.f, 10, _engine.get()));
    _engine->researchManager()->addResearch(new TrapResearch(
        (new TeleportTrap(2.f, _engine.get())), 5.f, 10, _engine.get()));
    _engine->researchManager()->addResearch(new TrapResearch(
        (new StunTrap(3.f, 10.f, _engine.get())), 5.f, 10, _engine.get()));
}

void Game::execute() {
    std::queue<TileEntity*> traps;
    traps.push(new DamageTrap(2, _engine.get()));
    traps.push(new TeleportTrap(2.f, _engine.get()));

    while (!_engine->shouldQuit()) {
        handleInput();
        update(GetFrameTime());
        if (WindowShouldClose()) {
            _engine->quit();
            continue;
        }

        BeginDrawing();
        draw();
        EndDrawing();
    }
}
void Game::cleanup() {}

void Game::handleInput() {
    if (IsKeyReleased(KEY_TAB) && !_researchQueue.empty()) {
        if (_engine->researchRequested(nullptr,
                new TrapResearch(
                    _researchQueue.front(), 5.f, 10, _engine.get()))) {
            _researchQueue.pop();
        }
    }
    if (IsKeyReleased(KEY_SPACE)) {
        _gui->reload();
    }
    if (IsKeyReleased(KEY_UP)) {
        _bank->deposit(11);
    }
    if (IsKeyReleased(KEY_DOWN)) {
        if (_bank->sufficientFunds(11)) _bank->withdraw(1);
    }
}
void Game::update(float dt) {
    if (IsKeyReleased(KEY_SPACE)) {
        _storyteller->togglePause();
    }
    _lair->update(dt);
    _lab->update(dt);
    _storyteller->update(dt);
    _gui->update(dt);
    _trapSelector->update(dt);
    _engine->tileEditor().update(dt);
    _engine->researchManager()->update(dt);
}
void Game::draw() {
    ClearBackground({74, 13, 4, 255});
    _engine->tileEditor().draw();
    _gui->draw();
    _engine->researchManager()->draw();
    _trapSelector->draw();
}

void Game::loadMap(const std::string& path) {
    char* data = LoadFileText(path.c_str());
    int x = 0;
    int y = 0;
    for (size_t i = 0; data[i] != '\0'; i++, x++) {
        if (data[i] == '\n') {
            while (data[i] == '\n' || data[i] == '\r')
                i++;
            x = 0;
            y++;
        }
        if (isspace(data[i])) continue;

        Tile* tile = _lair->addTile(x, y);
        _bank->deposit(Engine::TILE_COST);
        if (data[i] != '_') {
            _lair->fortifyTile(x, y);
            tile->bake(Tile::FIXED);
            _bank->deposit(Engine::FORT_COST);
        }
        if (data[i] == 'B') {
            _lair->addEntity(x, y, _bank.get());
            tile->bake(Tile::STATIC);
        }
        if (data[i] == 'T') {
            _lair->addEntity(x, y, new DamageTrap(4, _engine.get()));
        }
    }
}

void Game::execute() {
    while (!WindowShouldClose()) {
        handleInput();
        update(GetFrameTime());
        BeginDrawing();
        draw();
        EndDrawing();
    }
}