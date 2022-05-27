#ifndef PIECE_7815
#define PIECE_7815
#include "Piece.h"
#endif

/**
 * @brief Pawn chess piece.
 *
 */
class Pawn : public Piece {
private:
    /**
     * @brief Determine if the move is en passant move.
     *
     * @param move move to check
     * @param gameData current game state
     * @return true if the move is valid en passant move
     */
    bool isEnPassant(const Move& move, const GameData& gameData) const;
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