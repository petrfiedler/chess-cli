#ifndef PIECE_7815
#define PIECE_7815
#include "Piece.h"
#endif

/**
 * @brief Queen chess piece.
 *
 */
class Queen : public Piece {
public:
    /**
     * @brief Check if move with this piece is valid.
     *
     * @param move move to check
     * @param gameData current game state
     * @return true if the move is valid
     */
    bool checkValidMove(const Move& move, const GameData& gameData) const override;
};