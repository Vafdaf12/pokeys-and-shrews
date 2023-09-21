
#include <cassert>
#include <ctime>
#include <ctype.h>
#include <iostream>
#include <string>

#include "raylib.h"

#include "entity/TeleportTrap.h"
#include "graphics/TileGraphic.h"

#include "core/Storyteller.h"
#include "core/UserInterface.h"
#include "entity/Bank.h"
#include "entity/DamageTrap.h"
#include "lair/Lair.h"
#include "research/ResearchLab.h"
#include "ui/Button.h"
#include "ui/Label.h"

// SDL defines a main function itself, so it has to be undefined such that the
// following main is picked up correctly
#undef main

long time_step(long time, long fps) { return (time * fps / 1000); }

enum EditState {
    ES_NONE = 0,
    ES_FORT = 2,
    ES_ADD = 1,
    ES_REM = -2,
    ES_REME = -1,
    ES_TRAP = 3
};

Vector2 getTilePosition() {
    Vector2 pos = GetMousePosition();

    pos.x -= UserInterface::MAP_OFFSET.x;
    pos.y -= UserInterface::MAP_OFFSET.y;

    if (pos.x >= 0) pos.x /= TileGraphic::TILE_WIDTH;
    if (pos.y >= 0) pos.y /= TileGraphic::TILE_WIDTH;

    return pos;
}
void loadMap(const std::string& filename, Lair& lair, Bank& bank) {
    char* data = LoadFileText(filename.c_str());
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

        Tile* tile = lair.addTile(x, y);
        if (data[i] != '_') lair.fortifyTile(x, y);
        if (data[i] == 'B') {
            lair.addEntity(x, y, &bank);
            tile->bake();
        }
    }
}

int main(int, char**) {
    // test::research_lab();
    // test::bank();
    // test::research_engine();
    srand(time(nullptr));

    InitWindow(800, 600, "Pokeys & Shrews");

    Font font = LoadFont("res/Monocraft-no-ligatures.ttf");

    ResearchLab lab;
    Lair lair(11, 11);
    UserInterface ui(font);
    Bank bank(100);
    Storyteller storyteller;

    Engine engine(&lab, &bank, &lair, &ui, &storyteller);
    ui.setEngine(&engine);
    lair.setEngine(&engine);
    bank.setEngine(&engine);
    storyteller.setEngine(&engine);

    loadMap("res/map.txt", lair, bank);

    Timer timer(100);
    EditState editState = ES_NONE;
    int n = 1;

    while (!engine.shouldQuit()) {
        if (WindowShouldClose()) {
            engine.quit();
        }

        float delta = GetFrameTime();

        Vector2 p = getTilePosition();
        Tile* tile = lair.getTile(p.x, p.y);

        editState = ES_NONE;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (tile && tile->isFortified())
                editState = tile->getEntity() ? ES_NONE : ES_TRAP;
            else if (tile) editState = ES_FORT;
            else editState = ES_ADD;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && tile) {
            if (!tile->isFortified()) editState = ES_REM;
            else if (tile->getEntity() && !tile->isBaked()) editState = ES_REME;
        }
        if (IsKeyReleased(KEY_TAB)) {
            engine.researchRequested(nullptr,
                new ResearchTask(
                    "Trap #" + std::to_string(n++), 5.f, 10, &engine));
        }
        if (IsKeyReleased(KEY_UP)) {
            bank.deposit(1);
        }
        if (IsKeyReleased(KEY_DOWN)) {
            if (bank.sufficientFunds(1)) bank.withdraw(1);
        }

        switch (editState) {
        case ES_FORT: lair.fortifyTile(p.x, p.y); break;
        case ES_ADD: lair.addTile(p.x, p.y); break;
        case ES_REM: lair.removeTile(p.x, p.y); break;
        case ES_REME: lair.removeEntity(p.x, p.y); break;
        case ES_NONE: break;
        case ES_TRAP: lair.addEntity(p.x, p.y, new TeleportTrap(2.0f, &engine));
        }
        lab.update(delta);
        storyteller.update(delta);
        ui.update(delta);

        BeginDrawing();
        ui.draw();

        EndDrawing();
    }

    return 0;
}
