#include "Task.h"

#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char** argv) {
    std::stringstream s((std::string(argv[1])));
    int x;
    s >> x;

    Task* task = Task::create(x);
    task->run();
}
