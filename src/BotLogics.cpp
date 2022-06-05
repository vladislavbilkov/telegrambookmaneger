#include "BotLogics.h"
#include "InfoToSave.h"
#include "WriteRead.h"
#include <cstdint>
#include <cstdio>
#include <list>
#include <string>
#include <tgbot/types/Message.h>

void BotLogics::AddBook(TgBot::Message::Ptr message)
{
    InfoToSave obg(message->messageId, message->chat->id);
    ListAllAddingBook.push_back(obg);
    (SaveTOFile(obg));
    printf("List Message ID - %d. Message chat ID - %ld. Teg - %d\n", obg.GetMessageID(), obg.GetChatID(), obg.Teg);
}

void BotLogics::ViewAllBook(TgBot::Bot &bot, std::int64_t chatID)
{
    if(ListAllAddingBook.empty()) {
        bot.getApi().sendMessage(chatID, "Nothing to read, maybe need add from all list?");
        return;
    }
    for (InfoToSave i : ListAllAddingBook) {
        printf("List Message ID - %d. Message chat ID - %ld. Teg - %d\n", i.GetMessageID(), i.GetChatID(), i.Teg);
        if(chatID == i.GetChatID()) {
            bot.getApi().sendMessage(chatID, ".", false, i.GetMessageID());
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
        printf("Load Message ID - %d. Message chat ID - %ld. Teg - %d\n", i.GetMessageID(), i.GetChatID(), i.Teg);
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
    for (InfoToSave i : ListAllAddingBook) {
        printf("List Message ID - %d. Message chat ID - %ld. Teg - %d\n", i.GetMessageID(), i.GetChatID(), i.Teg);
    }
}

void BotLogics::SaveChange()
{
    std::list<InfoToSave> tmp = ListAllAddingBook;
    tmp.splice(tmp.end(), ListWantToReadBook);
    tmp.splice(tmp.end(), ListReadingBook);
    tmp.splice(tmp.end(), ListReadedBook);
    (SaveTOFile(tmp));
}
 BotLogics::BotLogics()
 {
     
 }

