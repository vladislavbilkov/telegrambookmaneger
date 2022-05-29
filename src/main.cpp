#include <stdio.h>
#include <tgbot/tgbot.h>


#include "Telegram_Events.cpp"

int main() {
    TgBot::Bot bot("5122355550:AAEjkevANONuLCEDSIknt9zzW9TI7nX7iCg");
    initAddbotevents(bot);
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());

        if(checkbotcommand(message)) {
            bot.getApi().sendMessage(message->chat->id, "don`t understand" + message->text);
        }
    });
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}