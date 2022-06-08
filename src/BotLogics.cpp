#include "BotLogics.h"
#include "InfoToSave.h"
#include "WriteRead.h"
#include <cstdint>
#include <cstdio>
#include <list>
#include <string>
#include <tgbot/Bot.h>
#include <tgbot/types/Message.h>

void BotLogics::AddBook(TgBot::Message::Ptr message)
{
    InfoToSave obg(message->messageId, message->chat->id);
    ListAllAddingBook.push_back(obg);
    (SaveTOFile(obg));
}

void BotLogics::ViewAllBook(TgBot::Bot &bot, std::int64_t chatID)
{
    ListReplyMessage.clear();
    if(ListAllAddingBook.empty()) {
        bot.getApi().sendMessage(chatID, "Nothing to read, maybe need add from all list?");
        return;
    }
    for (InfoToSave i : ListAllAddingBook) {
        if(chatID == i.GetChatID()) {
            ListReplyMessage.push_back(InfoToDelete(bot.getApi().sendMessage(chatID, ".", false, i.GetMessageID())->messageId, i.GetMessageID()));
        }
    }
}

void BotLogics::ViewReading(TgBot::Bot &bot, std::int64_t chatID)
{
    if (ListReadingBook.empty()) {
        bot.getApi().sendMessage(chatID, "Nothing reading book, maybe need add from all want read list?");
        return;
    }
    for (InfoToSave i : ListReadingBook) {
        if(chatID == i.GetChatID()) {
            ListReplyMessage.push_back(InfoToDelete(bot.getApi().sendMessage(chatID, ".", false, i.GetMessageID())->messageId, i.GetMessageID()));
        }
    }
}

void BotLogics::ViewReaded(TgBot::Bot &bot, std::int64_t chatID)
{
    if (ListReadedBook.empty()) {
        bot.getApi().sendMessage(chatID, "You dont readed books");
        return;
    }
    for (InfoToSave i : ListReadedBook) {
        if(chatID == i.GetChatID()) {
            bot.getApi().sendMessage(chatID, ".", false, i.GetMessageID());
        }
    }
}

void BotLogics::DeleteBook(TgBot::Bot &bot, TgBot::Message::Ptr &message)
{
    std::int32_t originid = FindIDMessageToDel(message->replyToMessage->messageId);
    if (originid == -1) {
        bot.getApi().sendMessage(message->chat->id, "Sorry dont find message, please check your reply message");
        return;
    }
    for (std::list<InfoToSave>::iterator it = ListAllAddingBook.begin(); it != ListAllAddingBook.end(); it++) {
        if (it->GetMessageID() == originid) {
            ListAllAddingBook.erase(it);
            bot.getApi().sendMessage(message->chat->id, "message been delete");
            break;
        }
    }
    SaveChange();   
}

void BotLogics::EditBook(TgBot::Bot &bot, TgBot::Message::Ptr &message)
{
    char whatid = CheckWhatIsEdit(message->text);
    if (whatid == -1) {
        bot.getApi().sendMessage(message->chat->id, "Sorry don`t understand your teg. Please check and try again");
        return;
    }

    std::int32_t originid = FindIDMessageToDel(message->replyToMessage->messageId);
    if (originid == -1) {
        bot.getApi().sendMessage(message->chat->id, "Sorry dont find message, please check your reply message");
        return;
    }

    if (ChangeList(whatid, originid)) {
        bot.getApi().sendMessage(message->chat->id, "Ok");
        for (InfoToSave i : ListReadingBook) {
            if (i.GetChatID() == message->chat->id) {
                bot.getApi().pinChatMessage(message->chat->id, i.GetMessageID());
            }
        }
    }else {
        bot.getApi().sendMessage(message->chat->id, "Bed. Please check your message");
        return;
    }
    SaveChange();
}

void BotLogics::LoadData()
{
    LoadFromFile load;
    auto tmp = load.GetList();
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

std::int32_t BotLogics::FindIDMessageToDel(std::int32_t findID) 
{
    for (InfoToDelete i : ListReplyMessage) {
        printf("Find id block id massage- %d find id -%d\n", i.ReplyMessage, findID);
        if (findID == i.ReplyMessage) {
            return i.OriginalMessage;
        }
    }
    return -1;
}

char BotLogics::CheckWhatIsEdit(std::string messagetext)
{
    if (messagetext == "/edit all") {
        return 0;
    } else if (messagetext == "/edit reading") {
        return 1;
    } else if (messagetext == "/edit readed") {
        return 2;
    } else {
        return -1;
    }
}

bool BotLogics::ChangeList( char whatid, std::int32_t originid)
{
    for (std::list<InfoToSave>::iterator it = ListReadingBook.begin(); it != ListReadingBook.end(); it++) {
        if (it->GetMessageID() == originid) {
            it->Teg = whatid;
            if(whatid == 0) {ListAllAddingBook.push_back(*it); ListReadingBook.erase(it);}
            else if(whatid == 2) {ListReadedBook.push_back(*it); ListReadingBook.erase(it);}
            return true;
        }
    }

    for (std::list<InfoToSave>::iterator it = ListReadedBook.begin(); it != ListReadedBook.end(); it++) {
        if (it->GetMessageID() == originid) {
            it->Teg = whatid;
            if(whatid == 0) {ListAllAddingBook.push_back(*it); ListReadedBook.erase(it);}
            else if(whatid == 1) {ListReadingBook.push_back(*it); ListReadedBook.erase(it);}
            return true;
        }
    }

    for (std::list<InfoToSave>::iterator it = ListAllAddingBook.begin(); it != ListAllAddingBook.end(); it++) {
        if (it->GetMessageID() == originid) {
            it->Teg = whatid;
            if(whatid == 1) {ListReadingBook.push_back(*it); ListAllAddingBook.erase(it);}
            else if(whatid == 2) {ListReadedBook.push_back(*it); ListAllAddingBook.erase(it);}
            return true;
        }
    }

    return false;
}