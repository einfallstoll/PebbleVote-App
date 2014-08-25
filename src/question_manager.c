#include <pebble.h>
#include "key_mappings.h"
#include "simple_window.h"
#include "question_window.h"

static Window *loading;
static DictionaryIterator *data;
static int currentQuestion;
static const char *currentId;

void start_questions(void);
void in_received_handler(DictionaryIterator *received, void *context);
static void answer_question(question_answer_t answer);

static void show_next_question() {
    Tuple *count = dict_find(data, KEY_COUNT);
    if (!count || currentQuestion >= count->value->int8) {
        window_stack_pop(true);
        start_questions();
    } else {
        int index = ++currentQuestion * 10;
        Tuple *id = dict_find(data, ++index);
        Tuple *either = dict_find(data, ++index);
        Tuple *or = dict_find(data, ++index);
        currentId = id->value->cstring;
        window_stack_pop(true);
        show_question_window(answer_question, id->value->cstring, either->value->cstring, or->value->cstring);
    }
}

static void answer_question(question_answer_t answer) {
    window_stack_pop(true);
    loading = show_simple_window("Selection is being uploaded...");
    
    app_message_register_inbox_received(in_received_handler);
    
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    
    Tuplet data = TupletCString(KEY_DATA, currentId);
    dict_write_tuplet(iter, &data);
    
    switch (answer) {
        case QUESTION_ANSWER_EITHER: {
            Tuplet type = TupletCString(KEY_TYPE, "either");
            dict_write_tuplet(iter, &type);
            break;
        }
        case QUESTION_ANSWER_OR: {
            Tuplet type = TupletCString(KEY_TYPE, "or");
            dict_write_tuplet(iter, &type);
            break;
        }
        case QUESTION_ANSWER_REPORT: {
            Tuplet type = TupletCString(KEY_TYPE, "report");
            dict_write_tuplet(iter, &type);
            break;
        }
        case QUESTION_ANSWER_SKIP: {
            Tuplet type = TupletCString(KEY_TYPE, "skip");
            dict_write_tuplet(iter, &type);
            break;
        }
    }
    dict_write_end(iter);
    
    app_message_outbox_send();
}

void in_received_handler(DictionaryIterator *received, void *context) {
    Tuple *status = dict_find(received, KEY_STATUS);
    Tuple *type = dict_find(received, KEY_TYPE);
    Tuple *count = dict_find(received, KEY_COUNT);
    if (status && strcmp(status->value->cstring, "success") == 0 && type) {
        if (strcmp(type->value->cstring, "random") == 0 && count) {
            APP_LOG(APP_LOG_LEVEL_INFO, "Random questions received");
            if (count->value->int8 == 0) {
                window_stack_pop(true);
                show_simple_window("No questions available");
            } else {
                currentQuestion = 0;
                data = received;
                show_next_question();
            }
        }
        if (strcmp(type->value->cstring, "answered") == 0) {
            show_next_question();
        }
    } else {
        window_stack_pop(true);
        show_simple_window("An error occured.");
    }
}

void start_questions(void) {
    loading = show_simple_window("Questions are being loaded...");
    
    app_message_register_inbox_received(in_received_handler);
    
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    
    Tuplet type = TupletCString(KEY_TYPE, "random");
    dict_write_tuplet(iter, &type);
    
    Tuplet inbox = TupletInteger(KEY_INBOX, app_message_inbox_size_maximum());
    dict_write_tuplet(iter, &inbox);
    
    dict_write_end(iter);
    
    app_message_outbox_send();
}
