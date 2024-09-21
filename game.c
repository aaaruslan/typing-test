#include "game.h"
#include "main.h"

void calculate_game_statistics(char *text, int current_char, int time_limit, time_t start_time, time_t *end_time, int *errors, GameStatistics *stats) {
    int total_words = 0;
    double typing_speed_cpm = 0;
    double typing_speed_wpm = 0;

    int correct_chars = current_char - *errors;
    int total_chars = current_char;

    for (int j = 0; j < current_char; j++) {
        if (!isalpha(text[j]) && text[j+1] != '\0' && isalpha(text[j+1])) {
            total_words++;
        }
    }

    // Calculate typing speed in characters per minute (cpm) and words per minute (wpm)
    time_t passed_time = time(NULL);
    double elapsed_time;
    if (end_time != NULL) {
        elapsed_time = (double) difftime(*end_time, start_time);
    } else {
        elapsed_time = (double) difftime(passed_time, start_time);
    }
    if (elapsed_time > 0) {
        typing_speed_cpm = ((double) total_chars / elapsed_time) * MINUTE;
        typing_speed_wpm = ((double) total_words / elapsed_time) * MINUTE;
    }

    stats->correct_chars = correct_chars;
    stats->total_chars = total_chars;
    stats->total_words = total_words;
    stats->elapsed_time = elapsed_time;
    stats->typing_speed_cpm = typing_speed_cpm;
    stats->typing_speed_wpm = typing_speed_wpm;
}


void play_game(char *text, int time_limit, int max_errors) {
    clear();
    mvprintw(0, 0, "%s", text);
    refresh();

    // Set up a timer
    time_t start_time = time(NULL);
    time_t end_time = start_time + time_limit;

    int current_char = 0;
    int errors = 0;
    while (current_char < strlen(text)) {
        move(0, current_char);
        int ch = getch();

        if (time(NULL) > end_time) {
            break;
        }

        if (errors >= max_errors) {
            break;
        }

        // Check if input character is correct
        if (ch == text[current_char]) {
            attron(COLOR_PAIR(1));
            addch(ch);
            attroff(COLOR_PAIR(1));
            current_char++;
        } else {
            attron(COLOR_PAIR(2));
            addch(text[current_char]);
            attroff(COLOR_PAIR(2));
            errors++;
            current_char++;
        }
    }

    // Calculate game statistics
    GameStatistics *stats = malloc(sizeof(GameStatistics));
    if (time(NULL) > end_time) {
        calculate_game_statistics(text, current_char, time_limit, start_time, &end_time, &errors, stats);
    } else {
        calculate_game_statistics(text, current_char, time_limit, start_time, NULL, &errors, stats);
    }

    clear();
    if (time(NULL) > end_time) {
        mvprintw(1, 1, "Game over! Time is up!");
    }
    if (errors >= max_errors) {
        mvprintw(1, 1, "Game over! You made too much mistakes");
    } else {
        mvprintw(1, 1, "Game Over!");
    }
    mvprintw(3, 1, "Correct characters: %d", stats->correct_chars);
    mvprintw(4, 1, "Incorrect characters: %d", errors);
    mvprintw(5, 1, "Total characters: %d", stats->total_chars);
    mvprintw(6, 1, "Average typing speed (cpm): %6.2f", stats->typing_speed_cpm);
    mvprintw(7, 1, "Average typing speed (wpm): %6.2f", stats->typing_speed_wpm);
    refresh();

    getch();
    endwin();
    free(stats);
}
