#ifndef PIECE_7815
#define PIECE_7815
#include "Piece.h"
#endif

/**
 * @brief Knight chess piece.
 *
 */
class Knight : public Piece {
private:
    /**
     * @brief Determine if the move is L-shaped.
     *
     * @param move move to check
     * @return true if the move is L-shaped
     */
    bool isKnightMove(const Move& move) const;
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