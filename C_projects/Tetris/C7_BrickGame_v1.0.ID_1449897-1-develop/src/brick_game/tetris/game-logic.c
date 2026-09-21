#include "tetris.h"

void userInput(UserAction_t action, bool hold) {
  if (!hold) {
    switch (action) {
      case Left:
        tetg->player->action = Left;
        break;
      case Right:
        tetg->player->action = Right;
        break;
      case Up:
        tetg->player->action = Up;
        break;
      case Down:
        tetg->player->action = Down;
        break;
      case Start:
        tetg->player->action = Start;
        break;
      case Pause:
        tetg->player->action = Pause;
        break;
      case Terminate:
        tetg->player->action = Terminate;
        break;
      default:
        tetg->player->action = Action;
        break;
    }
  }
}

void dropNewFigure(Game *tetg) {
  tetg->figure = createFigure(tetg);
  Figure *figure = createFigure(tetg);
  figure->x = tetg->field->width / 2 - figure->size / 2;
  figure->y = 0;
  int fnum = tetg->next;

  for (int i = 0; i < figure->size; i++)
    for (int j = 0; j < figure->size; j++)
      figure->blocks[i][j].b =
          tetg->figurest->blocks[fnum][i * figure->size + j].b;
  if (tetg->figure != NULL) freeFigure(tetg->figure);
  tetg->figure = figure;

  fnum = rand() % tetg->figurest->count;  // update next fig
  tetg->next = fnum;
}

GameInfo_t updateCurrentState() {
  GameInfo_t game_info = {0};
  calculate(tetg);

  if (tetg->state != GAMEOVER) {
    if (game_info.field != NULL)
      freePrintField(game_info.field, tetg->field->height);
    game_info.field = createPrintField(tetg->field->width, tetg->field->height);

    if (game_info.next != NULL)
      freeNextBlock(game_info.next, tetg->figurest->size);

    game_info.next = createNextBlock(tetg->figurest->size);

    game_info.score = tetg->score;
    game_info.high_score = tetg->high_score;
    game_info.level = tetg->level;
    game_info.speed = tetg->speed;
    game_info.pause = tetg->pause;
  }
  return game_info;
}

void calculate(Game *tetg) {
  if (tetg->ticks_left <= 0 && tetg->state != PAUSE && tetg->state != INIT)
    calcOne(tetg);  // to slower down 30 fps game
  if (tetg->state == GAMEOVER) return;

  switch (tetg->player->action) {
    case Right:
      if (tetg->pause) break;
      moveFigureRight(tetg);
      if (collision(tetg)) moveFigureLeft(tetg);
      break;
    case Left:
      if (tetg->pause) break;
      moveFigureLeft(tetg);
      if (collision(tetg)) moveFigureRight(tetg);
      break;
    case Down:
      if (tetg->pause) break;
      moveFigureDown(tetg);
      if (collision(tetg)) moveFigureUp(tetg);
      break;
    case Up: {
      if (tetg->pause) break;
      handleRotation(tetg);
    } break;
    case Pause:
      if (tetg->pause) {
        tetg->pause = 0;
        tetg->state = MOVING;
      } else {
        tetg->pause = 1;
        tetg->state = PAUSE;
      }
      break;
    case Terminate:
      tetg->state = GAMEOVER;
      break;
    case Start:
      tetg->pause = 0;
      tetg->state = MOVING;
      break;
    default:
      break;
  }

  tetg->ticks_left--;
}

void calcOne(Game *tetg) {
  tetg->ticks_left = tetg->ticks;
  moveFigureDown(tetg);
  tetg->state = MOVING;
  if (collision(tetg)) {
    moveFigureUp(tetg);
    plantFigure(tetg);
    countScore(tetg);
    if (tetg->figure != NULL) freeFigure(tetg->figure);
    dropNewFigure(tetg);
    tetg->state = DROP;
    if (collision(tetg)) {
      tetg->state = GAMEOVER;
    }
  }
}

void moveFigureDown(Game *tetg) { tetg->figure->y++; }

void moveFigureUp(Game *tetg) { tetg->figure->y--; }

void moveFigureRight(Game *tetg) { tetg->figure->x++; }

void moveFigureLeft(Game *tetg) { tetg->figure->x--; }

int collision(Game *tetg) {
  Figure *figure = tetg->figure;
  Field *field = tetg->field;

  for (int i = 0; i < figure->size; i++)
    for (int j = 0; j < figure->size; j++) {
      if (figure->blocks[i][j].b != 0) {
        int fx = figure->x + j;
        int fy = figure->y + i;
        if (fx < 0 || fx >= field->width || fy < 0 || fy >= field->height) {
          tetg->state = COLLISION;
          return 1;
        }
        if (field->blocks[fy][fx].b != 0) {
          tetg->state = COLLISION;
          return 1;
        }
      }
    }
  return 0;
}

int eraseLines(Game *tetg) {
  Field *tfl = tetg->field;
  int count = 0;
  for (int i = tfl->height - 1; i >= 0; i--) {
    while (lineFilled(i, tfl)) {
      dropLine(i, tfl);
      count++;
    }
  }
  return count;
}

int lineFilled(int i, Field *tfl) {
  for (int j = 0; j < tfl->width; j++)
    if (tfl->blocks[i][j].b == 0) return 0;
  return 1;
}

void dropLine(int i, Field *tfl) {
  if (i == 0)
    for (int j = 0; j < tfl->width; j++) tfl->blocks[i][j].b = 0;
  else {
    for (int k = i; k > 0; k--)
      for (int j = 0; j < tfl->width; j++)
        tfl->blocks[k][j].b = tfl->blocks[k - 1][j].b;  // move line up
  }
}

Figure *rotFigure(Game *tetg) {
  Figure *figure = createFigure(tetg);
  Figure *old_figure = tetg->figure;
  figure->x = old_figure->x;
  figure->y = old_figure->y;
  int size = figure->size;

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      figure->blocks[i][j].b = old_figure->blocks[j][size - 1 - i].b;
  return figure;
}

void handleRotation(Game *tetg) {
  Figure *t = rotFigure(tetg);
  Figure *told = tetg->figure;
  tetg->figure = t;
  if (collision(tetg)) {
    tetg->figure = told;
    freeFigure(t);
  } else
    freeFigure(told);
}

void plantFigure(Game *tetg) {
  Figure *figure = tetg->figure;
  for (int i = 0; i < figure->size; i++)
    for (int j = 0; j < figure->size; j++)
      if (figure->blocks[i][j].b != 0) {
        int fx = figure->x + j;
        int fy = figure->y + i;
        if (fx >= 0 && fx < tetg->field->width && fy >= 0 &&
            fy < tetg->field->height) {
          tetg->field->blocks[fy][fx].b = figure->blocks[i][j].b;
        }
      }
}

void countScore(Game *tetg) {
  int erased_lines = eraseLines(tetg);
  switch (erased_lines) {
    case 0:
      break;
    case 1:
      tetg->score += 100;
      break;
    case 2:
      tetg->score += 300;
      break;
    case 3:
      tetg->score += 700;
      break;
    default:
      tetg->score += 1500;
      break;
  }
  if (tetg->score > tetg->high_score) {
    tetg->high_score = tetg->score;
    saveHighScore(tetg->high_score);
  }

  int new_level = tetg->score / 600 + 1;  // +1 чтобы начать с уровня 1
  if (new_level > tetg->level && new_level <= 10) {
    tetg->level = new_level;
    tetg->speed = new_level;
  }
}