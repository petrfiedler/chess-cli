#ifndef GAME_AI_7856
#define GAME_AI_7856
#include "../game/GameAI.h"
#endif
#ifndef GAME_PVP_9468
#define GAME_PVP_9468
#include "../game/GamePVP.h"
#endif
#ifndef INTERFACE_9684
#define INTERFACE_9684
#include "Interface.h"
#endif

/**
 * @brief Interface component with game setting menu.
 *
 */
class MenuInterface {
private:
    /**
     * @brief Array of pointers to different game types.
     *
     */
    array<Game*, 4> m_GameTypes;

    /**
     * @brief Ask if player wants to load the game from file.
     *
     * @return FEN string (or empty string if player doesn't want to load)
     */
    string loadGamePrompt() const;

    /**
     * @brief Ask player to specify game file location.
     *
     * @return FEN string (or empty string if player doesn't want to load from file anymore)
     */
    string loadGame() const;

    /**
     * @brief
     *
     * @return int
     */
    int selectGameType()const;

    /**
     * @brief Ask player to select AI difficulty.
     *
     * @return difficulty level
     */
    int selectDifficulty() const;

    /**
     * @brief Get FEN string from file.
     *
     * @param filePath path to file with FEN string
     * @return FEN string (or empty string on failure)
     */
    string getFenFromFile(const string& filePath) const;

    /**
     * @brief Start the game.
     *
     * @param type game type code
     * @param fen FEN string to load the game from
     * @param isAI indicator of AI player
     */
    void startGame(int type, const string& fen, bool isAI) const;

public:
    /**
     * @brief Construct a new Menu Interface object.
     *
     */
    MenuInterface();

    /**
     * @brief Destroy the Menu Interface object.
     *
     */
    ~MenuInterface();

    /**
     * @brief Show the game menu.
     *
     */
    void showMenu() const;
};