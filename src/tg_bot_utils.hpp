#ifndef TG_BOT_UTILS_HPP
#define TG_BOT_UTILS_HPP

#include <tgbot/Bot.h>
#include <unordered_set>

namespace tg_bot_utils
{
    enum class text_comparison_policy
    {
        equal,
        starts_with
    };

    inline void register_command_handlers(
        TgBot::Bot& bot, 
        std::vector<std::pair<std::string, std::function<void(const TgBot::Api&, const TgBot::Message::Ptr)>>>&& commands_to_handlers,
        std::function<bool(const TgBot::Message::Ptr)>&& handlers_execution_condition = {})
    {
        for (auto& command_to_handler : commands_to_handlers)
        {
            bot.getEvents().onCommand(
                std::move(command_to_handler.first),
                [&bot, handler = std::move(command_to_handler.second), handlers_execution_condition = std::move(handlers_execution_condition)]
                (const TgBot::Message::Ptr message)
                {
                    if (!handlers_execution_condition || handlers_execution_condition(message))
                    {
                        handler(bot.getApi(), message);
                    }
                }); 
        }
    }

    inline void register_message_handlers(
        TgBot::Bot& bot, 
        std::unordered_map<std::string, std::function<void(const TgBot::Api&, const TgBot::Message::Ptr)>>&& messages_to_handlers,
        std::function<bool(const TgBot::Message::Ptr)>&& handlers_execution_condition = {})
    {
        bot.getEvents().onNonCommandMessage(
            [&bot, messages_to_handlers = std::move(messages_to_handlers), handlers_execution_condition = std::move(handlers_execution_condition)]
            (const TgBot::Message::Ptr message)
            {
                if (!handlers_execution_condition || handlers_execution_condition(message))
                {
                    auto handler_it = messages_to_handlers.find(message->text);

                    if (handler_it != messages_to_handlers.cend())
                    {
                        handler_it->second(bot.getApi(), message);
                    }
                }                
            });
    }

    inline void register_callback_handlers(
        TgBot::Bot& bot, 
        std::unordered_map<std::string, std::function<void(const TgBot::Api&, const TgBot::CallbackQuery::Ptr)>>&& callback_data_to_handlers,
        text_comparison_policy text_comparison,
        std::function<bool(const TgBot::CallbackQuery::Ptr)>&& handlers_execution_condition = {})
    {
        bot.getEvents().onCallbackQuery(
            [&bot, callback_data_to_handlers = std::move(callback_data_to_handlers), handlers_execution_condition = std::move(handlers_execution_condition), text_comparison]
            (const TgBot::CallbackQuery::Ptr callback)
            {
                if (!handlers_execution_condition || handlers_execution_condition(callback))
                {
                    switch (text_comparison)
                    {
                        case text_comparison_policy::equal:
                        {
                            auto handler_it = callback_data_to_handlers.find(callback->data);

                            if (handler_it != callback_data_to_handlers.cend())
                            {
                                handler_it->second(bot.getApi(), callback);
                            }

                            break;
                        }
                        case text_comparison_policy::starts_with:
                        {
                            for (const auto& callback_data_to_handler : callback_data_to_handlers)
                            {
                                if (callback->data.starts_with(callback_data_to_handler.first))
                                {
                                    callback_data_to_handler.second(bot.getApi(), callback);
                                }
                            }

                            break;
                        }
                    }
                }                
            });
    }

    inline std::string& escape_markdown_message(std::string& message)
    {
        static std::unordered_set<char> chars_to_escape{'_', '*', '[', ']', '(', ')', '~', '`', '>', '#', '+', '-', '=', '|', '{', '}', '.', '!'};

        for (size_t i = 0; i < message.size(); ++i)
        {
            if (chars_to_escape.contains(message[i]))
            {
                message.insert(i, "\\");
                ++i;
            }
        }

        return message;
    }

    inline std::string escape_markdown_message(const std::string& message)
    {
        static std::unordered_set<char> chars_to_escape{'_', '*', '[', ']', '(', ')', '~', '`', '>', '#', '+', '-', '=', '|', '{', '}', '.', '!'};

        std::string escaped_message;
        escaped_message.reserve(message.size());

        for (auto symbol : message)
        {
            if (chars_to_escape.contains(symbol))
            {
                escaped_message += '\\';
            }

            escaped_message += symbol;
        }

        return escaped_message;
    }
}

#endif