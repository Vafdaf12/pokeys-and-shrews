#include "Task.h"

int main(int, char**) {
    Task* task = Task::create(0);
    task->run();
}
