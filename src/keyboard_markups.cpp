#include <keyboard_markups.hpp>

namespace keyboard_markups
{
    void construct_main_reply_kb_markup()
    {
        system_info_btn->text = "System info";
        system_controls_btn->text = "System controls";

        main_reply_kb_markup->keyboard = {{system_info_btn, system_controls_btn}};
        main_reply_kb_markup->resizeKeyboard = true;
    }

    void construct_system_info_inline_kb_markup()
    {
        pm2_status_btn->text = "PM2 status";
        pm2_status_btn->callbackData = "get_pm2_status";

        pm2_logs_btn->text = "PM2 logs";
        pm2_logs_btn->callbackData = "choose_pm2_logs_process";

        system_metrics_btn->text = "System metrics";
        system_metrics_btn->callbackData = "get_system_metrics";

        reboot_required_btn->text = "Is reboot required";
        reboot_required_btn->callbackData = "reboot_required";

        updates_available_btn->text = "Are updates available";
        updates_available_btn->callbackData = "updates_available";

        system_info_inline_kb_markup->inlineKeyboard = 
        {
            {pm2_status_btn, pm2_logs_btn}, 
            {system_metrics_btn}, 
            {reboot_required_btn, updates_available_btn}
        };
    }

    void construct_return_to_system_info_inline_kb_markup()
    {
        return_to_system_info_btn->text = "Go back";
        return_to_system_info_btn->callbackData = "return_to_system_info";

        return_to_system_info_inline_kb_markup->inlineKeyboard = 
        {
            {return_to_system_info_btn}
        };
    }

    void construct_return_to_pm2_logs_inline_kb_markup()
    {
        return_to_pm2_logs_btn->text = "Go back";
        return_to_pm2_logs_btn->callbackData = "choose_pm2_logs_process";

        return_to_pm2_logs_inline_kb_markup->inlineKeyboard = 
        {
            {return_to_pm2_logs_btn}
        };
    }

    void construct_system_controls_inline_kb_markup()
    {
        update_packages_btn->text = "Update packages";
        update_packages_btn->callbackData = "update_packages";

        pm2_tools_btn->text = "PM2 tools";
        pm2_tools_btn->callbackData = "pm2_tools";

        reboot_system_btn->text = "Reboot system";
        reboot_system_btn->callbackData = "reboot_system";

        shutdown_system_btn->text = "Shut down system";
        shutdown_system_btn->callbackData = "shutdown_system";

        cancel_system_controls_command_btn->text = "No";
        cancel_system_controls_command_btn->callbackData = "return_to_system_controls";

        system_controls_inline_kb_markup->inlineKeyboard = 
        {
            {update_packages_btn, pm2_tools_btn}, 
            {reboot_system_btn, shutdown_system_btn}
        };
    }

    void construct_return_to_system_controls_inline_kb_markup()
    {
        return_to_system_controls_btn->text = "Go back";
        return_to_system_controls_btn->callbackData = "return_to_system_controls";

        return_to_system_controls_inline_kb_markup->inlineKeyboard = 
        {
            {return_to_system_controls_btn}
        };
    }

    void construct_pm2_tools_inline_kb_markup()
    {
        start_pm2_process_btn->text = "Start process";
        start_pm2_process_btn->callbackData = "start_pm2_process";

        stop_pm2_process_btn->text = "Stop process";
        stop_pm2_process_btn->callbackData = "stop_pm2_process";

        restart_pm2_process_btn->text = "Restart process";
        restart_pm2_process_btn->callbackData = "restart_pm2_process";

        pm2_tools_inline_kb_markup->inlineKeyboard = 
        {
            {start_pm2_process_btn, stop_pm2_process_btn},
            {restart_pm2_process_btn},
            {return_to_system_controls_btn}
        };
    }

    void construct_return_to_pm2_tools_inline_kb_markup()
    {
        return_to_pm2_tools_btn->text = "Go back";
        return_to_pm2_tools_btn->callbackData = pm2_tools_btn->callbackData;

        return_to_pm2_tools_inline_kb_markup->inlineKeyboard = 
        {
            {return_to_pm2_tools_btn}
        };
    }

    void construct_reboot_system_verification_inline_kb_markup()
    {
        verify_system_reboot_btn->text = "Yes";
        verify_system_reboot_btn->callbackData = "verify_system_reboot";

        reboot_system_verification_inline_kb_markup->inlineKeyboard = 
        {
            {verify_system_reboot_btn}, 
            {cancel_system_controls_command_btn}
        };
    }

    void construct_shutdown_system_verification_inline_kb_markup()
    {
        verify_system_shutdown_btn->text = "Yes";
        verify_system_shutdown_btn->callbackData = "verify_system_shutdown";

        shutdown_system_verification_inline_kb_markup->inlineKeyboard = 
        {
            {verify_system_shutdown_btn}, 
            {cancel_system_controls_command_btn}
        };
    }

    TgBot::InlineKeyboardMarkup::Ptr construct_pm2_logs_processes_inline_kb_markup(
        const std::vector<std::pair<size_t, std::string>>& processes_data)
    {
        auto pm2_processes_inline_kb_markup = std::make_shared<TgBot::InlineKeyboardMarkup>();

        for (size_t i = 0; i < processes_data.size(); ++i)
        {
            auto pm2_process_btn = std::make_shared<TgBot::InlineKeyboardButton>();
            pm2_process_btn->text = processes_data[i].second;
            pm2_process_btn->callbackData = "get_pm2_logs_" + std::to_string(processes_data[i].first);

            if (i % 2 == 0)
            {
                pm2_processes_inline_kb_markup->inlineKeyboard.emplace_back(
                    std::vector<TgBot::InlineKeyboardButton::Ptr>{pm2_process_btn});
            }
            else
            {
                pm2_processes_inline_kb_markup->inlineKeyboard.back().emplace_back(pm2_process_btn);
            }
        }

        pm2_processes_inline_kb_markup->inlineKeyboard.emplace_back(
            std::vector<TgBot::InlineKeyboardButton::Ptr>{return_to_system_info_btn});

        return pm2_processes_inline_kb_markup;
    }

    TgBot::InlineKeyboardMarkup::Ptr construct_pm2_tools_processes_inline_kb_markup(
        const std::vector<std::pair<size_t, std::string>> &processes_data, 
        const std::string &callback_data_starts_with)
    {
        auto pm2_processes_inline_kb_markup = std::make_shared<TgBot::InlineKeyboardMarkup>();

        if (processes_data.size() > 1)
        {
            auto pm2_process_btn = std::make_shared<TgBot::InlineKeyboardButton>();
            pm2_process_btn->text = "All";
            pm2_process_btn->callbackData = callback_data_starts_with + "all";

            pm2_processes_inline_kb_markup->inlineKeyboard.emplace_back(
                std::vector<TgBot::InlineKeyboardButton::Ptr>{pm2_process_btn});
        }

        for (size_t i = 0; i < processes_data.size(); ++i)
        {
            auto pm2_process_btn = std::make_shared<TgBot::InlineKeyboardButton>();
            pm2_process_btn->text = processes_data[i].second;
            pm2_process_btn->callbackData = callback_data_starts_with + std::to_string(processes_data[i].first);

            if (i % 2 == 0)
            {
                pm2_processes_inline_kb_markup->inlineKeyboard.emplace_back(
                    std::vector<TgBot::InlineKeyboardButton::Ptr>{pm2_process_btn});
            }
            else
            {
                pm2_processes_inline_kb_markup->inlineKeyboard.back().emplace_back(pm2_process_btn);
            }
        }

        pm2_processes_inline_kb_markup->inlineKeyboard.emplace_back(
            std::vector<TgBot::InlineKeyboardButton::Ptr>{return_to_pm2_tools_btn});

        return pm2_processes_inline_kb_markup;
    }

    void construct_kb_markups()
    {
        construct_main_reply_kb_markup();
        construct_system_info_inline_kb_markup();
        construct_return_to_system_info_inline_kb_markup();
        construct_return_to_pm2_logs_inline_kb_markup();
        construct_system_controls_inline_kb_markup();
        construct_return_to_system_controls_inline_kb_markup();
        construct_pm2_tools_inline_kb_markup();
        construct_return_to_pm2_tools_inline_kb_markup();
        construct_reboot_system_verification_inline_kb_markup();
        construct_shutdown_system_verification_inline_kb_markup();
    }
}