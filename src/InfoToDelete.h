#ifndef INFOTODELETE
#define INFOTODELETE

#include <cstdint>

class InfoToDelete 
{
    public:
    std::int32_t originalmessage;
    std::int32_t replymessage;
    InfoToDelete(std::int32_t rplmsg, std::int32_t orgmsg) { 
        originalmessage = orgmsg;
        replymessage = rplmsg;
    }
};

#endif