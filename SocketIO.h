#include "DefaultIO.h"

class SocketIO : public DefaultIO{
    int client_sock;
    
    public:
    SocketIO(int client_sock);
    std::string read() override;
    void write(std::string output) override;
};