#ifndef GAME_6876
#define GAME_6876
#include "Game.h"
#endif

#include <climits>

/**
 * @brief Inner chess behaviour with AI player.
 *
 */
class GameAI : public Game {
private:
    /**
     * @brief Game difficulty.
     *
     */
    int m_Level;

    /**
     * @brief Get static board score. (higher for white, lower for black)
     *
     * @param gameData game data to evaluate
     * @return board score
     */
    int evaluateBoard(const GameData& gameData) const;

    /**
     * @brief Get static value of piece.
     *
     * @param piece piece to evaluate
     * @return value
     */
    static int pieceValue(int piece);

    /**
     * @brief Make move as AI.
     *
     */
    void makeAIMove();

    /**
     * @brief Get all possible moves of current player.
     *
     * @param gameData game data to analyze
     * @return unordered set of valid moves
     */
    unordered_set<Move, Move::Hash> possibleMoves(const GameData& gameData) const;

    /**
     * @brief Simulate chess move.
     *
     * @param gameData input game data
     * @param move move to make
     * @return game data after move
     */
    GameData simulateMove(const GameData& gameData, const Move& move) const;

    /**
     * @brief Evaluate a move.
     *
     * @param gameData game data to analyze
     * @param depth depth of the game tree
     * @param alpha highest white player value yet seen
     * @param beta lowest black player value yet seen
     * @return best outcome value of current player's move
     */
    int minimax(const GameData& gameData, int depth, int alpha = INT_MIN, int beta = INT_MAX) const;

    /**
     * @brief Determine if game is over.
     *
     * @param gameData game data to analyze
     * @return true if the game is over
     */
    bool isGameOver(const GameData& gameData) const;

    /**
     * @brief Determine if the piece at given position can be attacked by other piece.
     *
     * @param position position of the target piece
     * @param gameData game data to analyze
     * @return true if the piece at the position can be attacked
     */
    bool canBeAttacked(pair<int, int> position, const GameData& gameData) const;

    /**
     * @brief
     *
     * @param position
     * @param gameData
     * @return true
     * @return false
     */
    bool canAttackKing(pair<int, int> position, const GameData& gameData) const;

public:
    /**
     * @brief Construct a new GameAI object.
     *
     * @param level game difficulty
     */
    GameAI(int level);

    /**
     * @brief Make chess move.
     *
     * @param move move to make
     * @return true if the move is valid
     */
    bool makeMove(const Move& move) override;
};