#include "game.h"
#include "main.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <difficulty> <time limit> <errors limit>\n", argv[0]);
        printf("Difficulty: easy, medium, hard\n");
        printf("Time: time limit in seconds. Max: %d\n", MAX_TIME);
        printf("Errors: max number of errors. Max: %d\n", MAX_ERRORS);
        return 1;
    }
    char *difficulty = argv[1];
    int time_limit = atoi(argv[2]);
    int max_errors = atoi(argv[3]);
    if (strcmp(difficulty, "easy") != 0 && strcmp(difficulty, "medium") != 0 && strcmp(difficulty, "hard") != 0) {
        printf("Invalid difficulty level: %s\n", difficulty);
        return 1;
    }
    if (time_limit <= 0 || time_limit > MAX_TIME) {
        printf("Invalid time limit. Maximum available time is %d\n", MAX_TIME);
        return 1;
    }
    if (max_errors <= 0 || max_errors > MAX_ERRORS) {
        printf("Invalid max errors. Maximum available errors number is %d\n", MAX_ERRORS);
        return 1;
    }

    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(1);

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    FILE *fp;
    if (strcmp(difficulty, "easy") == 0) {
        fp = fopen("easy_text.txt", "r");
    } else if (strcmp(difficulty, "medium") == 0) {
        fp = fopen("medium_text.txt", "r");
    } else {
        fp = fopen("hard_text.txt", "r");
    }
    if (fp == NULL) {
        printf("Error opening text file\n");
        return 1;
    }

    char text[MAX_TEXT_LENGTH];
    fgets(text, MAX_TEXT_LENGTH, fp);
    fclose(fp);

    play_game(text, time_limit, max_errors);

    return 0;
}