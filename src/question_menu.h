#include "question_answer.c"
    
void show_question_menu(void (*_answer_question)(question_answer_t answer), const char* id, const char* either, const char* or);
void hide_question_menu(void);
