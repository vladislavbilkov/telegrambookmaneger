#ifndef BOTLOGICS
#define BOTLOGICS

#include <tgbot/tgbot.h>
#include <list>
#include "InfoToSave.h"

class BotLogics
{
    std::list<InfoToSave> listallbook;
    
    public:
    bool addbook(TgBot::Message:: Ptr &message);
    void print();
};
#endif