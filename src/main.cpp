#include <iostream>
#include <list>
#include <stdio.h>
#include <string>
#include <tgbot/tgbot.h>
#include <tgbot/tools/StringTools.h>
#include <tgbot/types/ForceReply.h>
#include <tgbot/types/Message.h>


#include "BotLogics.h"

int main() {
    TgBot::Bot bot("5122355550:AAEjkevANONuLCEDSIknt9zzW9TI7nX7iCg");
    BotLogics logics;
    logics.LoadData();
    bool isadd = false;
    const std::string command[] = {"/start", "/all", "/add", "/reading", "/readed", "/want", "/help"};
    
    //command block
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Welcome to the book maneger");
        return;
    });
    bot.getEvents().onCommand("add", [&bot, &isadd, &logics](TgBot::Message::Ptr message) {
        isadd = true;
        return;
    });
    bot.getEvents().onCommand("want", [&bot, &logics](TgBot::Message::Ptr message) {
        logics.ViewWantReadBook(bot, message->chat->id);
        return;
    });
    bot.getEvents().onCommand("reading", [&bot, &logics](TgBot::Message::Ptr message) {
        logics.ViewReading(bot, message->chat->id);
        return;
    });
    bot.getEvents().onCommand("readed", [&bot, &logics](TgBot::Message::Ptr message) {
        logics.ViewReaded(bot, message->chat->id);
        return;
    });
    bot.getEvents().onCommand("all", [&bot, &logics](TgBot::Message::Ptr message) {
        logics.ViewAllBook(bot, message->chat->id);
        return;
    });

    //message block
    bot.getEvents().onAnyMessage([&bot, &isadd, &logics, command](TgBot::Message::Ptr message) {
        for (std::string i : command) {
            if (StringTools::startsWith(message->text, i)) {
                return;      
            }
        }
        if(isadd == true) {
            logics.AddBook(message);
            bot.getApi().sendMessage(message->chat->id, "Book will be added to the all list");
            isadd = false;
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Please use command");
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