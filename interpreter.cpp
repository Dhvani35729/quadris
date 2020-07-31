
#include "interpreter.h"

#include <iostream>
#include <string>
#include <cassert>

Interpreter::Interpreter()
{
    std::cout << "Interpreter born" << std::endl;
}

Interpreter::~Interpreter()
{
    std::cout << "Interpreter died" << std::endl;
}

std::vector<Command> Interpreter::getCommands()
{
    return this->commands_;
}

void Interpreter::addCommand(Command c)
{
    this->commands_.push_back(c);
}

void Interpreter::resetCommand()
{
    this->commands_.clear();
}

std::istream &operator>>(std::istream &in, Interpreter &i)
{

    std::string cmd;
    in >> cmd;
    i.resetCommand();

    if (cmd == "left" || cmd == "lef" || cmd == "l") // l is not supposed to be supported (cuz levelup/leveldown). added for convenience, delete later
    {
        i.addCommand(LEFT);
    }
    else if (cmd == "right" || cmd == "ri" || cmd == "rig" || cmd == "righ" || cmd == "right" || cmd == "r") // r is not supported, added for convenience, delete later
    {
        i.addCommand(RIGHT);
    }
    else if (cmd == "down" || cmd == "do" || cmd == "dow")
    {
        i.addCommand(DOWN);
    }
    else if (cmd == "drop" || cmd == "dr" || cmd == "dro")
    {
        i.addCommand(DROP);
    }
    else if (cmd == "clockwise" || cmd == "cl" || cmd == "clo" || cmd == "cloc" ||
            cmd == "clock" || cmd == "clockw" || cmd == "clockwi" || cmd == "clockwis" || cmd == "cw") // idk if cw is supported but it is now
    {
        i.addCommand(CLOCKWISE);
    }
    else if (cmd == "counterclockwise" || cmd == "co" || cmd == "cou" || cmd == "coun" || cmd == "count" ||
            cmd == "counte" || cmd == "counter" || cmd == "counterc" || cmd == "countercl" || cmd == "counterclo" ||
            cmd == "countercloc" || cmd == "counterclock" || cmd == "counterclockw" || cmd == "counterclockwi" ||
            cmd == "counterclockwis" || cmd == "ccw") // idk if ccw is supported but it is now
    {
        i.addCommand(COUNTERCLOCKWISE);
    }
    else if (cmd == "random" || cmd == "ra" || cmd == "ran" || cmd == "rand" || cmd == "rando") //Relevant only during levels 3 and 4, this command restores randomness in these levels.
    {
        i.addCommand(RANDOM);
    }
    else if (cmd == "norandom file" || cmd == "n" || cmd == "no" || cmd == "nor" || cmd == "nora" || cmd == "noran" ||
                cmd == "norand" ||cmd == "norando" || cmd == "norandom" || cmd == "norandom " || cmd == "norandom f" ||
                cmd == "norandom fi" || cmd == "norandom fil") //Relevant only during levels 3 and 4, this command restores randomness in these levels.
    {
        i.addCommand(NO_RANDOM_FILE);
    }
    else if (cmd == "levelup" || cmd == "levelu" || cmd == "lu") // lu not supported, abbreviated for convenience
    {
        i.addCommand(LEVEL_UP);
    }
    else if (cmd == "leveldown" || cmd == "leveld" || cmd == "ld") // ld not supported, abbreviated for convenience
    {
        i.addCommand(LEVEL_DOWN);
    }
    else if (cmd == "restart" || cmd == "re" || cmd == "res" || cmd == "rest" || cmd == "resta" || cmd == "restar")
    {
        i.addCommand(RESTART);
    }
    else if (cmd == "hint" || cmd == "h" || cmd == "hi" || cmd == "hin")
    {
        i.addCommand(HINT);
    }
    else if (cmd == "sequence file" || cmd == "s" || cmd == "se" || cmd == "seq" || cmd == "sequ" || cmd == "seque" ||
            cmd == "sequen" || cmd == "sequenc" || cmd == "sequence" || cmd == "sequence " || cmd == "sequence f" ||
            cmd == "sequence fi" || cmd == "sequence fil")
    {
        i.addCommand(SEQUENCE_FILE);
    }
    else if (cmd == "I")
    {
        i.addCommand(I);
    }
    else if (cmd == "J")
    {
        i.addCommand(J);
    }
    else if (cmd == "L")
    {
        i.addCommand(L);
    }
    else if (cmd == "S")
    {
        i.addCommand(S);
    }
    else if (cmd == "Z")
    {
        i.addCommand(Z);
    }
    else if (cmd == "O")
    {
        i.addCommand(O);
    }
    else if (cmd == "T")
    {
        i.addCommand(T);
    }
    else
    {
        i.addCommand(BAD_COMMAND);
    }

    assert(!in.fail());

    return in;
}
