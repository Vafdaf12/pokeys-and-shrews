
#include <cassert>
#include <ctime>
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

enum EditState { ES_NONE = 0, ES_FORT = 2, ES_ADD = 1, ES_REM = -1 };

Vector2 getTilePosition() {
    Vector2 pos = GetMousePosition();
    pos.x -= 20;
    pos.y -= 20;

    if (pos.x >= 0) pos.x /= TileGraphic::TILE_WIDTH;
    if (pos.y >= 0) pos.y /= TileGraphic::TILE_WIDTH;

    return pos;
}

int main(int, char**) {
    // test::research_lab();
    // test::bank();
    // test::research_engine();
    srand(time(nullptr));

    InitWindow(800, 600, "Pokeys & Shrews");

    Font font = GetFontDefault();

    ui::Button label(
        font, "Click Me", []() { std::cout << "Clicked" << std::endl; });
    label.setPosition({0, 100});

    ResearchLab lab;
    Lair lair(15, 11);
    UserInterface ui(font);
    Bank bank(100);
    Storyteller storyteller;

    Engine engine(&lab, &bank, &lair, &ui, &storyteller);
    ui.setEngine(&engine);
    lair.setEngine(&engine);
    bank.setEngine(&engine);
    storyteller.setEngine(&engine);

    lair.addTile(1, 0);
    lair.addTile(0, 0);
    lair.addTile(1, 1);
    lair.addTile(2, 1);
    lair.addTile(2, 2);
    TeleportTrap* trap = new TeleportTrap(5000);
    {
        Tile* t = lair.addTile(3, 1);
        t->setEntity(trap);
        t->fortify();
    }
    {
        Tile* t = lair.addTile(3, 2);
        t->setEntity(&bank);
        t->fortify();
    }

    lair.removeTile(1, 0);
    lair.addTile(1, 0);

    Timer timer(100);
    EditState editState = ES_NONE;
    int n = 1;

    while (!engine.shouldQuit()) {
        if (WindowShouldClose()) {
            engine.quit();
        }

        int dt = GetFrameTime() * 1000;

        Vector2 p = getTilePosition();
        bool tileExists = lair.getTile(p.x, p.y) != nullptr;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            editState = tileExists ? ES_FORT : ES_ADD;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            editState = tileExists ? ES_REM : ES_NONE;
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) ||
            IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            editState = ES_NONE;
        }
        if (IsKeyReleased(KEY_TAB)) {
            engine.researchRequested(new ResearchTask(
                "Trap #" + std::to_string(n++), 1000, 10, &engine));
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
        case ES_NONE: break;
        }
        lab.update(dt);
        // storyteller.update(dt);
        trap->update(dt);
        label.update(dt);
        ui.update(dt);

        BeginDrawing();
        ui.draw();

        label.draw();
        EndDrawing();
    }

    return 0;
}
