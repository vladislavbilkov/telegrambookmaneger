#ifndef BOTLOGICS
#define BOTLOGICS

#include <cstdint>
#include <tgbot/Bot.h>
#include <tgbot/tgbot.h>
#include <list>
#include <tgbot/types/Message.h>
#include "InfoToDelete.h"
#include "InfoToSave.h"

class BotLogics
{
    std::list<InfoToSave> ListAllAddingBook;
    std::list<InfoToSave> ListReadingBook;
    std::list<InfoToSave> ListReadedBook;

    std::int32_t FindIdMessageToDel(std::int32_t findid);
    void SaveChange();
    public:
    std::list<InfoToDelete> ListReplyMessage;
    BotLogics();
    void AddBook(TgBot::Message::Ptr message);
    void ViewAllBook(TgBot::Bot &bot, std::int64_t chatID);
    void ViewWantReadBook(TgBot::Bot &bot, std::int64_t chatID);
    void ViewReading(TgBot::Bot &bot, std::int64_t chatID);
    void ViewReaded(TgBot::Bot &bot, std::int64_t chatID);
    void DeleteBook(TgBot::Message::Ptr &message);
    void LoadData();
};
#endif