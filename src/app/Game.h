#pragma once
#include "Task.h"

#include "core/Storyteller.h"
#include "core/UserInterface.h"
#include "editor/TrapSelector.h"
#include "entity/Bank.h"
#include "raylib.h"
#include "research/ResearchLab.h"

#include <memory>
#include <queue>
#include <string>

class Game : public Task {
private:
    void init() override;
    void execute() override;

    void update(float dt);
    void draw();
    void handleInput();

    void loadMap(const std::string& path);

private:
    // Resources
    Font _font;

    // Game World
    std::unique_ptr<Engine> _engine;

    std::unique_ptr<ResearchLab> _lab;
    std::unique_ptr<Lair> _lair;
    std::unique_ptr<UserInterface> _gui;
    std::unique_ptr<Bank> _bank;
    std::unique_ptr<Storyteller> _storyteller;
    std::unique_ptr<TrapSelector> _trapSelector;

    // Utility & Debug
    std::queue<TileEntity*> _researchQueue;
};
