#ifndef MOVE_9545
# define MOVE_9545
#include "../utils/Move.h"
#endif

#ifndef GAME_DATA_1655
#define GAME_DATA_1655
#include "../game/GameData.h"
#endif

/**
 * @brief Chess piece.
 *
 */
class Piece {
protected:
    /**
     * @brief Check if move is within boundaries.
     *
     * @param move move to check
     * @return true if the move is within boundaries
     */
    bool checkBoundaries(const Move& move) const;

    /**
     * @brief Get sign of piece at given position.
     *
     * @param coords position of piece
     * @param board game board
     * @return piece sign
     */
    int getSign(const pair<int, int>& coords, const array<array<int, 8>, 8>& board) const;

    /**
     * @brief Check if the move destination is occupied by oponent's piece.
     *
     * @param move move to check
     * @param board game board
     * @return true if the move leads to oponent's piece
     */
    bool isOponent(const Move& move, const array<array<int, 8>, 8>& board) const;

    /**
     * @brief Check if the move destination is empty.
     *
     * @param move move to check
     * @param board game board
     * @return true if the move destination is empty
     */
    bool isEmptyDestination(const Move& move, const array<array<int, 8>, 8>& board) const;

    /**
     * @brief Check if move path is empty. (not considering destination square)
     *
     * @param move move to check
     * @param board game board
     * @return true if the path is empty
     */
    bool isEmptyPath(const Move& move, const array<array<int, 8>, 8>& board) const;

    /**
     * @brief Check if the move is either horizontal or vertical.
     *
     * @param move move to check
     * @return true if the move is orthogonal
     */
    bool isOrthogonalMove(const Move& move) const;

    /**
     * @brief Check if the move is diagonal
     *
     * @param move move to check
     * @return true if the move is diagonal
     */
    bool isDiagonalMove(const Move& move) const;

    /**
     * @brief Get move view from current player's perspective.
     *
     * @param move move from white's perspective
     * @param gameData current game data
     * @return move - flipped if the player is black
     */
    Move getMoveView(const Move& move, const GameData& gameData) const;

    /**
     * @brief Get board view from current player's perspective.
     *
     * @param move current player's move
     * @param gameData current game data
     * @return game board (flipped if the player is black)
     */
    array<array<int, 8>, 8> getBoardView(const Move& move, const GameData& gameData) const;

public:
    /**
     * @brief Destroy the Piece object.
     *
     */
    virtual ~Piece();

    /**
     * @brief Check if move with this piece is valid.
     *
     * @param move move to check
     * @param gameData current game state
     * @return true if the move is valid
     */
    virtual bool checkValidMove(const Move& move, const GameData& gameData) const = 0;
};