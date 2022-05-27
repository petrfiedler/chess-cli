#ifndef GAME_6876
#define GAME_6876
#include "Game.h"
#endif

/**
 * @brief Inner chess behaviour for two players.
 *
 */
class GamePVP : public Game {
public:
    /**
     * @brief Make chess move.
     *
     * @param move move to make
     * @return true if the move is valid
     */
    bool makeMove(const Move& move) override;
};