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

    std::int32_t FindIDMessageToDel(std::int32_t findID);
    void SaveChange();
    public:
    std::list<InfoToDelete> ListReplyMessage;
    BotLogics();
    void AddBook(TgBot::Message::Ptr message);
    void ViewAllBook(TgBot::Bot &bot, std::int64_t chatID);
    void ViewWantReadBook(TgBot::Bot &bot, std::int64_t chatID);
    void ViewReading(TgBot::Bot &bot, std::int64_t chatID);
    void ViewReaded(TgBot::Bot &bot, std::int64_t chatID);
    void DeleteBook(TgBot::Bot &bot, TgBot::Message::Ptr &message);
    void EditBook(TgBot::Bot &bot, TgBot::Message::Ptr &message);
    void LoadData();
};
#endif