#include "BotLogics.h"
#include "InfoToSave.h"
#include "WriteRead.h"
#include <cstdint>
#include <cstdio>
#include <string>
#include <tgbot/types/Message.h>

void BotLogics::AddBook(TgBot::Message::Ptr message)
{
    InfoToSave obg(message->messageId, message->chat->id);
    ListAllAddingBook.push_back(obg);
    (SaveTOFile(obg));
}

void BotLogics::ViewAllBook(TgBot::Bot &bot, std::int64_t chatID)
{
    if(ListAllAddingBook.empty()) {
        bot.getApi().sendMessage(chatID, "Nothing to read, maybe need add from all list?");
        return;
    }
    for (InfoToSave i : ListAllAddingBook) {
        if(chatID == i.GetChatID()) {
            bot.getApi().sendMessage(chatID, "." ,false, i.GetMessageID());
        }
    }
    
}

void BotLogics::ViewWantReadBook(TgBot::Bot &bot, std::int64_t chatID)
{
    if (ListWantToReadBook.empty()) {
        bot.getApi().sendMessage(chatID, "Nothing to you want read, maybe need add from all list?");
    }
    for (InfoToSave n : ListWantToReadBook) {
        if (n.GetChatID() == chatID) {
            bot.getApi().sendMessage(chatID, "", n.GetMessageID());
        }
    }
}

void BotLogics::ViewReading(TgBot::Bot &bot, std::int64_t chatID)
{
    if (ListReadingBook.empty()) {
        bot.getApi().sendMessage(chatID, "Nothing reading book, maybe need add from all want read list?");
    }

}

void BotLogics::ViewReaded(TgBot::Bot &bot, std::int64_t chatID)
{
    if (ListReadedBook.empty()) {
        bot.getApi().sendMessage(chatID, "Nothing readed");
    }
    for (InfoToSave n : ListReadedBook) {
        if (n.GetChatID() == chatID) {
            bot.getApi().sendMessage(chatID, "", n.GetMessageID());
        }
    }
}

void BotLogics::LoadData()
{
    LoadFromFile load;
    auto tmp = load.GetList();//TODO: check how work
    for (InfoToSave i : tmp) {
        if (i.Teg == 3) {
            ListReadedBook.push_back(i);
        }
        else if (i.Teg == 2) {
            ListReadingBook.push_back(i);
        }
        else if (i.Teg == 1) {
            ListWantToReadBook.push_back(i);
        }
        else {
            ListAllAddingBook.push_back(i);
        }
    }
}

void BotLogics::SaveChange()
{
    (SaveTOFile(ListAllAddingBook));
    (SaveTOFile(ListWantToReadBook));
    (SaveTOFile(ListReadedBook));
    (SaveTOFile(ListReadingBook));
}
 BotLogics::BotLogics()
 {
     
 }

