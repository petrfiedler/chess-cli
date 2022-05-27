#ifndef PIECE_7815
#define PIECE_7815
#include "Piece.h"
#endif

/**
 * @brief King chess piece.
 *
 */
class King : public Piece {
private:
    /**
     * @brief Determine if the move is castling move.
     *
     * @param move move to check
     * @param gameData current game state
     * @return true if the move is valid castling move
     */
    bool isCastling(const Move& move, const GameData& gameData) const;

    /**
     * @brief Determine if the move is by one square.
     *
     * @param move move to check
     * @return true if the move is by one square
     */
    bool isKingMove(const Move& move) const;
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