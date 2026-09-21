#ifndef CLI_H
#define CLI_H
#include <ncurses.h>

#include "../../brick_game/tetris/tetris.h"

/**
 * @brief Initializes the graphical user interface for the game. This function
 * sets up the terminal for displaying the game, initializes color pairs, and
 * configures terminal settings such as cursor visibility and input modes.
 */
void initGui();

/**
 * @brief Prints the entire game state to the screen, including the game field,
 * the next figure, and game information like score and level. It also refreshes
 * the screen to update the display.
 * @param game: The current game state containing field, next figure, and game
 * @param sp_start Time of starting loop.
 * @param sp_end Time of ending loop.
 * stats.
 */
void printGame(GameInfo_t game, struct timespec sp_start,
               struct timespec sp_end);

/**
 * @brief Displays the game field on the screen. It iterates through each cell
 * of the game field and prints a space character with a color based on the
 * cell's state.
 * @param game: The current game state containing the field to be displayed.
 */
void printField(GameInfo_t game);

/**
 * @brief Displays the next figure on the screen in a designated area. It uses a
 * different color to distinguish the next figure from the game field.
 * @param game: The current game state containing the next figure to be
 * displayed.
 */
void printNextFigure(GameInfo_t game);

/**
 * @brief Prints game-related information such as the current level, speed,
 * score, and high score. It also displays controls and game status (e.g.,
 * paused) to the player.
 * @param game: The current game state containing information to be displayed.
 */
void printInfo(GameInfo_t game);

/**
 * @brief Reads a single character from the keyboard input and returns an action
 * based on the key pressed. Actions include moving the figure in different
 * directions, starting a new game, pausing, and terminating the game.
 * @return UserAction_t: The action to be taken based on the user's input.
 */
UserAction_t getAction();

/**
 * @brief Calculates and executes a delay based on the game speed and the time
 * taken to execute the last frame.
 * @param sp_start: Start time of the last frame.
 * @param sp_end: End time of the last frame.
 * @param game_speed: Current speed of the game which affects the delay
 * duration.
 */
void handleDelay(struct timespec sp_start, struct timespec sp_end,
                 int game_speed);

#endif