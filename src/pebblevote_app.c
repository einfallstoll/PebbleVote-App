#include <pebble.h>
#include "main_menu.h"
#include "simple_window.h"

void in_dropped_handler(AppMessageResult reason, void *context) {
    switch(reason) {
        case APP_MSG_ALREADY_RELEASED: {
            APP_LOG(APP_LOG_LEVEL_ERROR, "The resource had already been released.");
            break;
        }
        case APP_MSG_BUFFER_OVERFLOW: {
            APP_LOG(APP_LOG_LEVEL_ERROR, "The buffer was too small to contain the incoming message.");
            break;
        }
        case APP_MSG_BUSY: {
            APP_LOG(APP_LOG_LEVEL_ERROR, "There are pending (in or outbound) messages that need to be processed first before new ones can be received or sent.");
            break;
        }
        case APP_MSG_CALLBACK_ALREADY_REGISTERED: {
            APP_LOG(APP_LOG_LEVEL_ERROR, "The callback node was already registered, or its ListNode has not been initialized.");
            break;
        }
        case APP_MSG_CALLBACK_NOT_REGISTERED: {
            APP_LOG(APP_LOG_LEVEL_ERROR, "The callback could not be deregistered, because it had not been registered before.");
            break;
        }
        case APP_MSG_INVALID_ARGS: {
            APP_LOG(APP_LOG_LEVEL_ERROR, "The function was called with invalid arguments.");
            break;
        }
        case APP_MSG_NOT_CONNECTED: {
            APP_LOG(APP_LOG_LEVEL_ERROR, "The other end was not connected.");
            break;
        }
        case APP_MSG_OK: {
            APP_LOG(APP_LOG_LEVEL_INFO, "All good, operation was successful.");
            return;
        }
        case APP_MSG_OUT_OF_MEMORY: {
            APP_LOG(APP_LOG_LEVEL_ERROR, "The support library did not have sufficient application memory to perform the requested operation.");
            break;
        }
        case APP_MSG_SEND_REJECTED: {
            APP_LOG(APP_LOG_LEVEL_ERROR, "The other end rejected the sent data, with a \"nack\" reply.");
            break;
        }
        case APP_MSG_SEND_TIMEOUT: {
            APP_LOG(APP_LOG_LEVEL_ERROR, "The other end did not confirm receiving the sent data with an (n)ack in time.");
            break;
        }
        case APP_MSG_APP_NOT_RUNNING: {
            APP_LOG(APP_LOG_LEVEL_ERROR, "The local application was not running.");
            break;
        }
        case APP_MSG_CLOSED: {
            APP_LOG(APP_LOG_LEVEL_ERROR, "App message was closed.");
            break;
        }
        case APP_MSG_INTERNAL_ERROR: {
            APP_LOG(APP_LOG_LEVEL_ERROR, "An internal OS error prevented APP_MSG from completing an operation.");
            break;
        }
    }
    
    window_stack_pop(true);
    show_simple_window("An error occured.");
}

static void register_standard_inbox_dropped() {
    app_message_register_inbox_dropped(in_dropped_handler);
}

int main(void) {
    register_standard_inbox_dropped();
    
    app_message_open(app_message_inbox_size_maximum(), APP_MESSAGE_OUTBOX_SIZE_MINIMUM);

    show_main_menu();
    app_event_loop();
    return 0;
}
