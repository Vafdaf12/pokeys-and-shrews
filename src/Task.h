#pragma once

class Task {
public:
    virtual ~Task() {}

    void run() {
        init();
        execute();
        cleanup();
    }
    static Task* create(int task);

protected:
    virtual void init() {}
    virtual void execute() = 0;
    virtual void cleanup() {}
};
