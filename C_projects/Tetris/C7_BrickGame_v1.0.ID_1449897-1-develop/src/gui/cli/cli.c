#include "cli.h"

void initGui() {
  initscr();
  curs_set(0);
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_YELLOW);
  init_pair(2, COLOR_GREEN, COLOR_GREEN);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_GREEN, COLOR_BLACK);

  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  scrollok(stdscr, TRUE);
}

void printGame(GameInfo_t game, struct timespec sp_start,
               struct timespec sp_end) {
  printField(game);

  printNextFigure(game);

  printInfo(game);

  freeGui(game, 5, 20);
  handleDelay(sp_start, sp_end, game.speed);
  refresh();
}

void printField(GameInfo_t game) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      int sym = game.field[i][j] != 0 ? 2 : 1;
      attron(COLOR_PAIR(sym));
      mvaddch(i + 3, j * 2 + 2, ' ');
      mvaddch(i + 3, j * 2 + 3, ' ');
      attroff(COLOR_PAIR(sym));
    }
  }
}

void printNextFigure(GameInfo_t game) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      int sym = game.next[i][j] != 0 ? 2 : 0;
      attron(COLOR_PAIR(sym));
      mvaddch(i + 5, j * 2 + 28, ' ');
      mvaddch(i + 5, j * 2 + 29, ' ');
      attroff(COLOR_PAIR(sym));
    }
  }
}

void printInfo(GameInfo_t game) {
  attron(COLOR_PAIR(3));
  mvwprintw(stdscr, 1, 10, "TETRIS");
  attroff(COLOR_PAIR(3));

  attron(COLOR_PAIR(4));
  mvwprintw(stdscr, 3, 26, "Next figure:");
  mvwprintw(stdscr, 11, 26, "Lvl: %d", game.level);
  mvwprintw(stdscr, 13, 26, "Speed: %d", game.speed);
  mvwprintw(stdscr, 15, 26, "Score: %d", game.score);
  clrtoeol();
  mvwprintw(stdscr, 17, 26, "High score: %d", game.high_score);
  if (game.pause) mvwprintw(stdscr, 12, 2, "Press ENTER to play.");
  attroff(COLOR_PAIR(4));
  attron(COLOR_PAIR(5));
  mvwprintw(stdscr, 24, 6, "Press:");
  mvwprintw(stdscr, 24, 14, "Start: 'Enter'");
  mvwprintw(stdscr, 25, 14, "Pause: 'p'");
  mvwprintw(stdscr, 26, 14, "Exit: 'q'");
  mvwprintw(stdscr, 27, 14, "Arrows to move: '<' '>'");
  mvwprintw(stdscr, 28, 14, "Space to rotate: '___'");
  mvwprintw(stdscr, 29, 14, "Arrow down to plant: 'v'");
  attroff(COLOR_PAIR(5));
}

UserAction_t getAction() {
  int ch = getch();
  switch (ch) {
    case 68:
      return Left;
    case 67:
      return Right;
    case ' ':
      return Up;
    case 66:
      return Down;
    case '\n':
      return Start;
    case 'p':
      return Pause;
    case 'q':
      return Terminate;
    default:
      return Action;
  }
}

void handleDelay(struct timespec sp_start, struct timespec sp_end,
                 int game_speed) {
  clock_gettime(CLOCK_MONOTONIC, &sp_end);
  struct timespec ts1, ts2 = {0, 0};
  if (sp_end.tv_sec - sp_start.tv_sec <= 0 &&
      (ts2.tv_nsec = (20000000 - game_speed * 1500000) -
                     (sp_end.tv_nsec - sp_start.tv_nsec)) > 0) {
    nanosleep(&ts2, &ts1);
  }
}