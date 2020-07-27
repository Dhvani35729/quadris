#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include <string>

enum Command
{
    LEFT,
    RIGHT,
    DOWN,
    CLOCKWISE,
    COUNTERCLOCKWISE,
    DROP,
    LEVEL_UP,
    LEVEL_DOWN,
    NO_RANDOM_FILE,
    RANDOM,
    SEQUENCE_FILE,
    RESTART,
    HINT,
    I,
    J,
    L,
    S,
    Z,
    O,
    T,
};

// Controller
class Interpreter
{
public:
    Interpreter();
    ~Interpreter();
    std::vector<Command> processCommand(std::string);

private:
};

#endif
