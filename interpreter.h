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
    BOT_MODE,
    BAD_COMMAND
};

// Controller
class Interpreter
{
public:
    Interpreter();
    ~Interpreter();
    std::vector<Command> getCommands();
    void addCommand(Command);
    void resetCommand();

private:
    std::vector<Command> commands_;
};

std::istream &operator>>(std::istream &, Interpreter &);

#endif
