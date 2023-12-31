#include "Task.h"
#include "app/Game.h"
#include "app/GameTest.h"
#include "app/SmartContractDemo.h"

Task* Task::create(int task) {
    switch (task) {
    case 0: return new SmartContractDemo();
    case 1: return new Game();
    case 2: return new GameTest();
    }
    return nullptr;
}