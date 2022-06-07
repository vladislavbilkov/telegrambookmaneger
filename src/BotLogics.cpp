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
    ListReplyMessage.clear();
    if(ListAllAddingBook.empty()) {
        bot.getApi().sendMessage(chatID, "Nothing to read, maybe need add from all list?");
        return;
    }
    for (InfoToSave i : ListAllAddingBook) {
        printf("List Message ID - %d. Message chat ID - %ld. Teg - %d\n", i.GetMessageID(), i.GetChatID(), i.Teg);
        if(chatID == i.GetChatID()) {
            ListReplyMessage.push_back(InfoToDelete(bot.getApi().sendMessage(chatID, ".", false, i.GetMessageID())->messageId, i.GetMessageID()));
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

void BotLogics::DeleteBook(TgBot::Message::Ptr &message)
{
    std::int32_t originid = FindIdMessageToDel(message->replyToMessage->messageId);
    printf("Delete block origin id message - %d\n", originid);
    if (originid == -1) {
        return;
    }
    for (std::list<InfoToSave>::iterator it = ListAllAddingBook.begin(); it != ListAllAddingBook.end(); it++) {
        if (it->GetMessageID() == originid) {
            ListAllAddingBook.erase(it);
            //send msg
            break;
        }
    }
    SaveChange();   
}

void BotLogics::LoadData()
{
    LoadFromFile load;
    auto tmp = load.GetList();//TODO: check how work
    for (InfoToSave i : tmp) {
        printf("Load Message ID - %d. Message chat ID - %ld. Teg - %d\n", i.GetMessageID(), i.GetChatID(), i.Teg);
        if (i.Teg == 2) {
            ListReadedBook.push_back(i);
        }
        else if (i.Teg == 1) {
            ListReadingBook.push_back(i);
        }
        else {
            ListAllAddingBook.push_back(i);
        }
    }
}

void BotLogics::SaveChange()
{
    std::list<InfoToSave> tmp = ListAllAddingBook;
    tmp.splice(tmp.end(), ListReadingBook);
    tmp.splice(tmp.end(), ListReadedBook);
    (SaveTOFile(tmp));
}
 
BotLogics::BotLogics()
{
     
}

std::int32_t BotLogics::FindIdMessageToDel(std::int32_t findid) 
{
    for (InfoToDelete i : ListReplyMessage) {
        printf("Find id block id massage- %d find id -%d\n", i.replymessage, findid);
        if (findid == i.replymessage) {
            return i.originalmessage;
        }
    }
    return -1;
}