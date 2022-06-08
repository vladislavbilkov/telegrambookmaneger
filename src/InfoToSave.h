#ifndef INFOTOSAVE
#define INFOTOSAVE

#include <cstdint>
#include <string>
#include <tgbot/tgbot.h>

class InfoToSave {
    std::int32_t MessageID = 0;
    std::int64_t ChatID = 0;
    public:
    char Teg = 0;
    InfoToSave(){}
    InfoToSave(std::int32_t messageid ,std::int64_t chatid) {
        MessageID = messageid;
        ChatID = chatid;
    }
    std::int32_t GetMessageID() {
        return MessageID;
    }
    std::int64_t GetChatID() {
        return ChatID;
    }
};
//Teg 0 - all book list
//1 - Reading book
//2 - Readed book
#endif