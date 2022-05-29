#include "BotLogics.h"
#include "InfoToSave.h"

bool BotLogics::addbook(TgBot::Message::Ptr &message)
{
    listallbook.push_back(InfoToSave(message));
    return true;
}

void BotLogics::print()
{
    printf("workinghghg");
    //print("Message %s\n Chat id %d \n Message id %d", savedmsg->text.c_str(), savedmsg->chat->id, savedmsg->message->id);
}