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
    EXIT,
    BOT_MODE,
    BAD_COMMAND
};

// Controller
class Interpreter
{
public:
    Interpreter();
    ~Interpreter();
    std::vector<std::pair<Command, int>> getCommands();
    void addCommand(Command, int);
    void resetCommand();

private:
    std::vector<std::pair<Command, int>> commands_;
};

std::istream &operator>>(std::istream &, Interpreter &);

#endif
