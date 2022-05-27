#ifndef GAME_6876
#define GAME_6876
#include "../game/Game.h"
#endif

/**
 * @brief Interface component with the actual game.
 *
 */
class GameInterface {
private:
    /**
     * @brief Current game.
     *
     */
    Game* m_Game;

    /**
     * @brief Inidcator of AI player.
     *
     */
    bool m_IsAI;

    /**
     * @brief Decode piece code to one-char string representation.
     *
     * @param piece piece code
     * @return piece string representation
     */
    string getPieceChar(int piece) const;

    /**
     * @brief Decode piece code to ASCII char representation.
     *
     * @param piece piece code
     * @return string with one ASCII char
     */
    string getPieceCharASCII(int piece) const;

    /**
     * @brief Print board to stdout.
     *
     */
    void printBoard() const;

    /**
     * @brief Print board with additional game info.
     *
     * @param message optional message to show
     */
    void printGame(const string& message = "") const;

    /**
     * @brief Parse move coordinates from move instruction string.
     *
     * @param move instruction string
     * @return parsed coordinates
     */
    pair<int, int> parseMove(const string& move) const;

    /**
     * @brief Ask player to make a move.
     *
     * @return message based on user input
     */
    string askMove();

    /**
     * @brief Let AI make a move.
     *
     */
    void makeAIMove() const;

    /**
     * @brief Ask player to pick piece to promote to.
     *
     * @return message based on user input
     */
    string handlePromotion();

    /**
     * @brief Ask player to play again.
     *
     * @return true if player wants to play again
     */
    bool gameEnded() const;

    /**
     * @brief Read user input for commands.
     *
     * @param input user input
     * @return true if user typed one of the commands
     */
    bool readCommand(const string& input);

    /**
     * @brief Print help message to stdout.
     *
     */
    void printHelp() const;

    /**
     * @brief Print additional game info to stdout.
     *
     */
    void showInfo() const;

    /**
     * @brief Try to save the game to specified location.
     *
     */
    void saveGame() const;

public:
    /**
     * @brief Construct a new Game Interface object.
     *
     * @param game pointer to abstract game object
     * @param isAI indicator of AI player
     */
    GameInterface(Game* game, bool isAI);

    /**
     * @brief Start the game interface.
     *
     * @return true if player wants to play again
     */
    bool play();
};