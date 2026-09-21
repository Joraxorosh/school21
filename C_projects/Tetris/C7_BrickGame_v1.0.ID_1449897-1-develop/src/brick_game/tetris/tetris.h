#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @enum UserAction_t
 * @brief Enumerates possible user actions in the game.
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/**
 * @enum GameState
 * @brief Enumerates possible states in the game.
 */
typedef enum { INIT, DROP, MOVING, COLLISION, PAUSE, GAMEOVER } GameState;

/**
 * @struct GameInfo_t
 * @brief Holds the dynamic information about the game's current state.
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

/**
 * @struct Block
 * @brief Represents a single block in the game.
 */
typedef struct Block {
  int b;
} Block;

/**
 * @struct Figure
 * @brief Represents a game figure composed of multiple blocks.
 */
typedef struct Figure {
  int x;
  int y;
  int size;
  Block **blocks;
} Figure;

/**
 * @struct FiguresT
 * @brief Holds templates for all possible figures in the game.
 */
typedef struct FiguresT {
  int count;
  int size;
  Block **blocks;
} FiguresT;

/**
 * @struct Field
 * @brief Represents the playing field.
 */
typedef struct Field {
  int width;
  int height;
  Block **blocks;
} Field;

/**
 * @struct Player
 * @brief Represents the player's current action.
 */
typedef struct Player {
  int action;
} Player;

/**
 * @struct Game
 * @brief Main game structure holding all game-related data.
 */
typedef struct Game {
  Field *field;
  Figure *figure;
  FiguresT *figurest;
  Player *player;
  Block **tet_templates;

  int score;
  int high_score;
  int ticks_left;
  int ticks;
  int speed;
  int level;
  int next;

  int pause;
  int state;

} Game;

/**
 *@brief Initialization of the game.
 * Program starts here
 */
void initGame();

/**
 * @brief Creates and initializes the main game structure (Game). It sets up the
 game field, figures templates, and initializes game parameters like score, high
 score, and game state.
 * @param field_width: The width of the game field.
 * @param field_height: The height of the game field.
 * @param figures_size: The size of the figures.
 * @param count: The number of different figures.
 * @return A pointer to the initialized Game structure.
 */
Game *createGame(int field_width, int field_height, int figures_size,
                 int count);

/**
 * @brief  Allocates and initializes the game field with the specified
 * dimensions.
 * @param width: The width of the game field.
 * @param height: The height of the game field.
 * @return A pointer to the initialized Field structure.
 */
Field *createField(int width, int height);

/**
 * @brief  Initializes the templates for the Tetris figures using predefined
 * figure arrays.
 * @return An array of pointers to Block, representing different figure
 * templates.
 */
Block **createTemplates();

/**
 * @brief  Creates and initializes the structure holding the figures templates
 * and their metadata.
 * @param count: Number of different figures.
 * @param figures_size: Size of each figure.
 * @param figures_template: Pointer to the array of figure templates.
 * @return A pointer to the initialized FiguresT structure.
 */
FiguresT *createFiguresT(int count, int figures_size, Block **figures_template);

/**
 * @brief Allocates memory for a new figure and initializes its blocks to zero.
 * @param tetg: Pointer to the game state.
 * @return Pointer to the newly created figure.
 */
Figure *createFigure(Game *tetg);

/**
 * @brief Creates a printable representation of the current game field.
 * @param width: Width of the field.
 * @param height: Height of the field.
 * @return 2D array of integers representing the field state.
 */
int **createPrintField(int width, int height);

/**
 * @brief Generates the next block to be played, based on the current game
 * state.
 * @param size: Size of the block.
 * @return 2D array of integers representing the next block.
 */
int **createNextBlock(int size);

/**
 * @brief Processes user input and updates the player's action in the game
 * structure.
 * @param action: The action performed by the user.
 * @param hold: Indicates whether the action is being held down.
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Initializes a new figure in the game, sets its starting position,
 * checks for collisions, and updates the next figure.
 * @param tetg Pointer to the game state.
 */
void dropNewFigure(Game *tetg);

/**
 * @brief Updates and returns the current state of the game, including field and
 * next block representations.
 * @return GameInfo_t structure containing the current game state.
 */
GameInfo_t updateCurrentState();

/**
 * @brief Processes one tick of the game logic, handling user actions and game
 * rules.
 * @param tetg: Pointer to the game structure.
 */
void calculate(Game *tetg);

/**
 * @brief Handles the logic for one game tick, moving the figure down and
 * checking for collisions.
 * @param tetg: Pointer to the game structure.
 */
void calcOne(Game *tetg);

/**
 * @brief Moves the current figure one unit downwards.
 * @param tetg: Pointer to the game state.
 */
void moveFigureDown(Game *tetg);

/**
 * @brief Moves the current figure one unit upwards.
 * @param tetg: Pointer to the game state.
 */
void moveFigureUp(Game *tetg);

/**
 * @brief Moves the current figure one unit to the right.
 * @param tetg: Pointer to the game state.
 */
void moveFigureRight(Game *tetg);

/**
 * @brief Moves the current figure one unit to the left.
 * @param tetg: Pointer to the game state.
 */
void moveFigureLeft(Game *tetg);

/**
 * @brief Checks if the current figure collides with the boundaries of the field
 * or other blocks.
 * @param tetg: Pointer to the game state.
 * @return 1 if there is a collision, otherwise 0.
 */
int collision(Game *tetg);

/**
 * @brief Checks for filled lines in the field and removes them, moving all
 * above lines down.
 * @param tetg: Pointer to the game state.
 * @return The number of lines erased.
 */
int eraseLines(Game *tetg);

/**
 * @brief Checks if a specific line in the field is completely filled.
 * @param i: Index of the line to check.
 * @param tfl: Pointer to the field.
 * @return 1 if the line is filled, otherwise 0.
 */
int lineFilled(int i, Field *tfl);

/**
 * @brief Removes a line from the field and moves all lines above it down by
 * one.
 * @param i: Index of the line to drop.
 * @param tfl: Pointer to the field.
 */
void dropLine(int i, Field *tfl);

/**
 * @brief Creates a new figure as a rotated version of the current figure.
 * @param tetg: Pointer to the game state.
 * @return Pointer to the rotated figure.
 */
Figure *rotFigure(Game *tetg);

/**
 * @brief Attempts to rotate the current figure and checks for collisions.
 * Reverts if a collision occurs.
 * @param tetg: Pointer to the game state.
 */
void handleRotation(Game *tetg);

/**
 * @brief Places the current figure's blocks into the game field if they are
 * within bounds.
 * @param tetg: Pointer to the game state.
 */
void plantFigure(Game *tetg);

/**
 * @brief  Updates the game score based on the number of lines erased and
 * adjusts the game level and speed accordingly.
 * @param tetg: Pointer to the game structure.
 */
void countScore(Game *tetg);

/**
 * @brief Saves the high score to a file.
 * @param high_score: The high score to save.
 */
void saveHighScore(int high_score);

/**
 * @brief Loads the high score from a file.
 * @return The high score as an integer.
 */
int loadHighScore();

extern Game *tetg;

// MEMORY FREE

/**
 * @brief Frees all memory allocated for the game, including the game structure,
 * field, figures, templates, and player.
 * @param tetg: A pointer to the game structure to be freed.
 */
void freeGame(Game *tetg);

/**
 * @brief Frees all memory allocated for the field structure, including the
 * blocks within the field.
 * @param tetf: A pointer to the field structure to be freed.
 */
void freeField(Field *tetf);

/**
 * @brief Frees the memory allocated for a figure, including its blocks.
 * @param tf: A pointer to the figure to be freed.
 */
void freeFigure(Figure *tf);

/**
 * @brief Frees the memory allocated for the FiguresT structure.
 * @param tetft: A pointer to the FiguresT structure to be freed.
 */
void freeFiguresT(FiguresT *tetft);

/**
 * @brief Frees the memory allocated for block templates.
 * @param templates: A pointer to the array of block templates to be freed.
 */
void freeTemplates(Block **templates);

/**
 * @brief Frees the memory allocated for a print field array.
 * @param print_field: A pointer to the print field array to be freed.
 * @param height: The number of rows in the print field array.
 */
void freePrintField(int **print_field, int height);

/**
 * @brief Frees the memory allocated for the next block array.
 * @param next: A pointer to the next block array to be freed.
 * @param size: The number of rows in the next block array.
 */
void freeNextBlock(int **next, int size);

/**
 * @brief Frees the GUI-related structures, including the print field and next
 * block.
 * @param game: A structure containing GUI-related data.
 * @param size: The size parameter used for freeing the next block.
 * @param height: The height parameter used for freeing the print field.
 */
void freeGui(GameInfo_t game, int size, int height);

#endif