#ifndef INFOTOSAVE
#define INFOTOSAVE

#include <cstdint>
#include <tgbot/tgbot.h>

class InfoToSave {
    std::int32_t MessageID;
    std::int64_t ChatID;
    public:
    InfoToSave(TgBot::Message::Ptr &message) {
        MessageID = message->messageId;
        ChatID = message->chat->id;
    }
};

#endif