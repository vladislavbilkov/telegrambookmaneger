#include <bits/types/struct_tm.h>
#include <iostream>
#include <list>
#include <stdio.h>
#include <string>
#include <tgbot/Bot.h>
#include <tgbot/tgbot.h>
#include <tgbot/tools/StringTools.h>
#include <tgbot/types/BotCommand.h>
#include <tgbot/types/ForceReply.h>
#include <tgbot/types/KeyboardButton.h>
#include <tgbot/types/Message.h>
#include <vector>


#include "BotLogics.h"

    const std::string Menucommand[] = {"/start", "/all", "/add", "/del", "/reading", "/readed", "/edit", "/help"};
    const std::string Menudescription[] = {"Lets start", "Show adding book", "For add book next message must be forwarded ", "For delete reply sended message",
    "Show what book you reading", "Show what book you readed", "for edit reply massage for this text(all ,reading ,readed) ", "get help"};

//Initial command for bots
std::vector<TgBot::BotCommand::Ptr> InitialCommands() {
    std::vector<TgBot::BotCommand::Ptr> botcommand;
    for(int i = 0; i < Menucommand->size(); i++) {
        TgBot::BotCommand::Ptr tmp(new TgBot::BotCommand);
        tmp->command = Menucommand[i];
        tmp->description = Menudescription[i];
        botcommand.push_back(tmp);
    }
    return botcommand;
}

int main() {
    //Initial block
    TgBot::Bot bot("5122355550:AAEjkevANONuLCEDSIknt9zzW9TI7nX7iCg");
    TgBot::BotCommand tmp;
    bot.getApi().setMyCommands(InitialCommands());
    BotLogics logics;
    bool isadd = false;

    logics.LoadData();
    //command block
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Welcome to the book maneger");
        return;
    });
    bot.getEvents().onCommand("add", [&bot, &isadd, &logics](TgBot::Message::Ptr message) {
        isadd = true;
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
    bot.getEvents().onCommand("del", [&bot, &logics](TgBot::Message::Ptr message) {
        logics.DeleteBook(bot, message);
        return ;
    });
    bot.getEvents().onCommand("edit", [&bot, &logics](TgBot::Message::Ptr message) {
        
        return ;
    });

    //message block
    bot.getEvents().onAnyMessage([&bot, &isadd, &logics](TgBot::Message::Ptr message) {
        for (std::string i : Menucommand) {
            if (StringTools::startsWith(message->text, i)) {
                return;      
            }
        }
        //add command 
        if(isadd == true) {
            logics.AddBook(message);
            bot.getApi().sendMessage(message->chat->id, "Book will be added to the all list");
            isadd = false;
            return;
        }

        bot.getApi().sendMessage(message->chat->id, "Please use command");
    });

    //bot loop 
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