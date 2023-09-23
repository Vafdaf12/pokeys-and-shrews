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

class GameTest : public Task {
private:
    void execute() override;

    void testLair();
};