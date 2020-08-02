#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include <string>

#define NUM_COMMANDS 23
#define NUM_DIRECTION 5

enum Command
{
    TYPE_DIRECTION = 0,
    TYPE_OTHER = NUM_DIRECTION,
    BAD_COMMAND = NUM_COMMANDS,
};

enum Direction
{
    LEFT = TYPE_DIRECTION,
    RIGHT,
    DOWN,
    CLOCKWISE,
    COUNTERCLOCKWISE,
};

enum Other
{
    DROP = TYPE_OTHER,
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
    RENAME,
    BOT_MODE,
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
    Command completer(std::string);
    bool renameCommad(std::string, std::string);
    void parseRaw(std::istream &in, std::string);

private:
    std::vector<std::pair<Command, int>> commands_;
    std::vector<std::string> commandNames_;
};

std::istream &operator>>(std::istream &, Interpreter &);

#endif
