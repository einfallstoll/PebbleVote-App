#include "question_menu.h"

void show_question_window(void (*_answer_question)(question_answer_t answer), const char* id, const char* either, const char* or);
void hide_question_window(void);
