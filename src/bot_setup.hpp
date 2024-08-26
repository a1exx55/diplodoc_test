#ifndef BOT_SETUP_HPP
#define BOT_SETUP_HPP

#include <config.hpp>
#include <handlers.hpp>
#include <keyboard_markups.hpp>

#include <signal.h>
#include <iostream>

#include <tgbot/Bot.h>
#include <tgbot/net/TgLongPoll.h>

void setup_bot()
{
    try
    {
        config::init();

        signal(
            SIGINT, 
            [](int) 
            {
                std::clog << "Bot was successfully shut down!\n";
                exit(0);
            });

        TgBot::Bot bot(config::bot_token);

        keyboard_markups::construct_kb_markups();
        handlers::register_handlers(bot);

        bot.getApi().deleteWebhook();

        TgBot::TgLongPoll long_poll(bot);

        std::clog << "Bot was successfully started!\n";

        while (true) 
        {
            try
            {
                long_poll.start();
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::clog << "Bot was unexpectedly shut down due to an error!\n";
    }
}

#endif