#include "Task.h"

int main(int, char**) {
    Task* task = Task::create(1);
    task->run();
}
