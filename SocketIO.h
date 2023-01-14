#include "DefaultIO.h"

class SocketIO : public DefaultIO{
    public:
    string read() override;
    void write(string output) override;
};