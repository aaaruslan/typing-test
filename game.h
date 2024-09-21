#ifndef RK1_GAME_H
#define RK1_GAME_H
#include "main.h"

typedef struct {
    int correct_chars;
    int total_chars;
    int total_words;
    double elapsed_time;
    double typing_speed_cpm;
    double typing_speed_wpm;
} GameStatistics;

void play_game(char *text, int time_limit, int max_errors);
void calculate_game_statistics(char *text, int current_char, int time_limit, time_t start_time, time_t *end_time, int *errors, GameStatistics *stats);

#endif //RK1_GAME_H
