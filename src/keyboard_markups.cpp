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
        pm2_logs_btn->callbackData = "get_pm2_logs";

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

    void construct_system_controls_inline_kb_markup()
    {
        update_packages_btn->text = "Update packages";
        update_packages_btn->callbackData = "update_packages";

        reboot_system_btn->text = "Reboot system";
        reboot_system_btn->callbackData = "reboot_system";

        shutdown_system_btn->text = "Shut down system";
        shutdown_system_btn->callbackData = "shutdown_system";

        return_to_system_controls_btn->text = "No";
        return_to_system_controls_btn->callbackData = "return_to_system_controls";

        system_controls_inline_kb_markup->inlineKeyboard = 
        {
            {update_packages_btn}, 
            {reboot_system_btn, shutdown_system_btn}
        };
    }

    void construct_reboot_system_verification_inline_kb_markup()
    {
        verify_system_reboot_btn->text = "Yes";
        verify_system_reboot_btn->callbackData = "verify_system_reboot";

        reboot_system_verification_inline_kb_markup->inlineKeyboard = 
        {
            {verify_system_reboot_btn}, 
            {return_to_system_controls_btn}
        };
    }

    void construct_shutdown_system_verification_inline_kb_markup()
    {
        verify_system_shutdown_btn->text = "Yes";
        verify_system_shutdown_btn->callbackData = "verify_system_shutdown";

        shutdown_system_verification_inline_kb_markup->inlineKeyboard = 
        {
            {verify_system_shutdown_btn}, 
            {return_to_system_controls_btn}
        };
    }

    void construct_kb_markups()
    {
        construct_main_reply_kb_markup();
        construct_system_info_inline_kb_markup();
        construct_system_controls_inline_kb_markup();
        construct_reboot_system_verification_inline_kb_markup();
        construct_shutdown_system_verification_inline_kb_markup();
    }
}