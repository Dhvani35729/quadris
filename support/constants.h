#ifndef CONSTANTS_H
#define CONSTANTS_H

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

#endif