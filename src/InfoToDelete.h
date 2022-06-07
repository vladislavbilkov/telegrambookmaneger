#ifndef INFOTODELETE
#define INFOTODELETE

#include <cstdint>

class InfoToDelete 
{
    public:
    std::int32_t OriginalMessage;
    std::int32_t ReplyMessage;
    InfoToDelete(std::int32_t rplmsg, std::int32_t orgmsg) { 
        OriginalMessage = orgmsg;
        ReplyMessage = rplmsg;
    }
};

#endif