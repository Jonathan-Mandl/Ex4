#include "DefaultIO.h"

class StandardIO : public DefaultIO{
    public:
    string read() override;
    void write(string output) override;
};