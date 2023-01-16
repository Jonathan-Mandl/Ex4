
#include "Command.h"

//empty implementation.

Command::Command(string description, DefaultIO* dio) : description(description), dio(dio) {

}
string Command::getDescription()
{
    return this->description;
}