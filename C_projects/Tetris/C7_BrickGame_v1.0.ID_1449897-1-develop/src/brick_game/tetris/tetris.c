#include "tetris.h"

#include "../../gui/cli/cli.h"

int main() {
  struct timespec sp_start, sp_end = {0, 0};
  srand(time(NULL));
  initGui();
  initGame();

  while (tetg->state != GAMEOVER) {
    clock_gettime(CLOCK_MONOTONIC, &sp_start);
    userInput(getAction(), 0);

    GameInfo_t game_info = updateCurrentState();

    if (tetg->state == GAMEOVER) {
      freeGui(game_info, tetg->figurest->size, tetg->field->height);
      continue;
    } else
      printGame(game_info, sp_start, sp_end);
  };
  freeGame(tetg);

  endwin();

  return 0;
}