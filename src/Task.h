#pragma once

class Task {
public:
    virtual ~Task() {}

    void run() {
        init();
        execute();
        cleanup();
    }

protected:
    virtual void init() {}
    virtual void execute() = 0;
    virtual void cleanup() {}

    static Task* create(int task);
};
