#ifndef KEYBOARD_MARKUPS_HPP
#define KEYBOARD_MARKUPS_HPP

#include <tgbot/types/ReplyKeyboardMarkup.h>
#include <tgbot/types/InlineKeyboardMarkup.h>

namespace keyboard_markups
{
    inline auto system_info_btn = std::make_shared<TgBot::KeyboardButton>();
    inline auto system_controls_btn = std::make_shared<TgBot::KeyboardButton>();
    inline auto main_reply_kb_markup = std::make_shared<TgBot::ReplyKeyboardMarkup>();

    inline auto pm2_status_btn = std::make_shared<TgBot::InlineKeyboardButton>();
    inline auto pm2_logs_btn = std::make_shared<TgBot::InlineKeyboardButton>();
    inline auto system_metrics_btn = std::make_shared<TgBot::InlineKeyboardButton>();
    inline auto reboot_required_btn = std::make_shared<TgBot::InlineKeyboardButton>();
    inline auto updates_available_btn = std::make_shared<TgBot::InlineKeyboardButton>();
    inline auto system_info_inline_kb_markup = std::make_shared<TgBot::InlineKeyboardMarkup>();

    inline auto return_to_system_info_btn = std::make_shared<TgBot::InlineKeyboardButton>();
    inline auto return_to_system_info_inline_kb_markup = std::make_shared<TgBot::InlineKeyboardMarkup>();

    inline auto update_packages_btn = std::make_shared<TgBot::InlineKeyboardButton>();
    inline auto reboot_system_btn = std::make_shared<TgBot::InlineKeyboardButton>();
    inline auto shutdown_system_btn = std::make_shared<TgBot::InlineKeyboardButton>();
    inline auto cancel_system_controls_command_btn = std::make_shared<TgBot::InlineKeyboardButton>();
    inline auto system_controls_inline_kb_markup = std::make_shared<TgBot::InlineKeyboardMarkup>();
    
    inline auto return_to_system_controls_btn = std::make_shared<TgBot::InlineKeyboardButton>();
    inline auto return_to_system_controls_inline_kb_markup = std::make_shared<TgBot::InlineKeyboardMarkup>();
    
    inline auto verify_system_reboot_btn = std::make_shared<TgBot::InlineKeyboardButton>();
    inline auto reboot_system_verification_inline_kb_markup = std::make_shared<TgBot::InlineKeyboardMarkup>();

    inline auto verify_system_shutdown_btn = std::make_shared<TgBot::InlineKeyboardButton>();
    inline auto shutdown_system_verification_inline_kb_markup = std::make_shared<TgBot::InlineKeyboardMarkup>();

    void construct_kb_markups();
}

#endif