#ifndef BOTLOGICS
#define BOTLOGICS

#include <cstdint>
#include <new>
#include <string>
#include <tgbot/Bot.h>
#include <tgbot/tgbot.h>
#include <list>
#include "InfoToSave.h"

class BotLogics
{
    std::list<InfoToSave> ListAllAddingBook;
    std::list<InfoToSave> ListWantToReadBook;
    std::list<InfoToSave> ListReadingBook;
    std::list<InfoToSave> ListReadedBook;
    public:
    BotLogics();
    void AddBook(TgBot::Message::Ptr message);
    void ViewAllBook(TgBot::Bot &bot, std::int64_t chatID);
    void ViewWantReadBook(TgBot::Bot &bot, std::int64_t chatID);
    void ViewReading(TgBot::Bot &bot, std::int64_t chatID);
    void ViewReaded(TgBot::Bot &bot, std::int64_t chatID);
    void LoadData();
    void SaveChange();
};
#endif