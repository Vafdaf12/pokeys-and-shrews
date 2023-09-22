#pragma once
#include "Task.h"

#include "core/Storyteller.h"
#include "core/UserInterface.h"
#include "editor/EntityEditor.h"
#include "entity/Bank.h"
#include "raylib.h"
#include "research/ResearchLab.h"

#include <memory>
#include <queue>
#include <string>

class Game : public Task {
private:
    enum class EditAction {
        None,
        Fortify,
        AddTile,
        RemoveTile,
        AddEntity,
        RemoveEntity
    };

    void init() override;
    void execute() override;
    void cleanup() override;

    void update(float dt);
    void draw();
    void handleInput();

    EditAction getAction() const;

    void loadMap(const std::string& path);
    Vector2 getWorldSpacePosition(Vector2 pos) const;

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
    std::unique_ptr<EntityEditor> _entityEditor;

    // Utility & Debug
    std::queue<TileEntity*> _researchQueue;
};
