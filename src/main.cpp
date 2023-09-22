#include "Task.h"

int main(int, char**) {
    Task* task = Task::create(2);
    task->run();
}
