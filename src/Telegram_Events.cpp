#ifndef TELEGRAMEVENTS
#define TELEGRAMEVENTS

#include "BotLogics.h"
#include <tgbot/export.h>
#include <tgbot/tgbot.h>
#include <tgbot/types/Message.h>

void initAddbotevents(TgBot::Bot &bot) {
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Welcome to the book maneger");
    });
    bot.getEvents().onCommand("add", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Adding book to library");
        bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
            bot.getApi().sendMessage(message->chat->id, "Saved");            
        });
    });
    
    bot.getEvents().onCommand("reading", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "List reading books");
    });
    bot.getEvents().onCommand("readed", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "List readed books");
    });
}

bool checkbotcommand(TgBot::Message::Ptr &message) {
    if (StringTools::startsWith(message->text, "/start")) {
        return false;
    }
    if (StringTools::startsWith(message->text, "/add")) {
        return false;
    }
    if (StringTools::startsWith(message->text, "/reading")) {
        return false;
    }
    if (StringTools::startsWith(message->text, "/readed")) {
        return false;
    }
    return true;
}

#endif