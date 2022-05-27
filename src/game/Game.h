#ifndef GAME_DATA_1655
#define GAME_DATA_1655
#include "GameData.h"
#endif

#ifndef PIECES_9265
#define PIECES_9265
#include "../pieces/Pawn.h"
#include "../pieces/Rook.h"
#include "../pieces/Knight.h"
#include "../pieces/Bishop.h"
#include "../pieces/Queen.h"
#include "../pieces/King.h"
#endif

#ifndef FEN_3455
#define FEN_3455
#include "../utils/Fen.h"
#endif

#include <unordered_set>

/**
 * @brief Inner chess behaviour.
 *
 */
class Game {
protected:
    /**
     * @brief Game data.
     *
     */
    GameData m_GameData;

    /**
     * @brief Game state.
     * 0: normal
     * 1: check
     * 2: white won
     * 3: black won
     * 4: stalemate
     *
    */
    int m_GameState;

    /**
     * @brief Coordinates of piece promotion.
     * (-1, -1) in case of no promotion
     *
     */
    pair<int, int> m_Promotion;

    /**
     * @brief Piece decoding table.
     *
     */
    array<Piece*, 7> m_Pieces;

    /**
     * @brief Last move.
     *
     */
    Move m_LastMove;

    /**
     * @brief Check if selected piece is current player's piece.
     * Throw an exception if it is not.
     *
     * @param piece piece code
     */
    void checkSelectedPiece(int piece) const;

    /**
     * @brief Check if move is legal.
     *
     * @param move move to check
     * @return true if move is legal
     */
    bool checkLegalMove(const Move& move) const;

    /**
     * @brief Kill pawn if en passant happened.
     *
     * @param move potential move of killer pawn
     * @param gameData game data to modify
     */
    void manageEnPassant(const Move& move, GameData& gameData) const;

    /**
     * @brief Move rook if castling happened.
     *
     * @param move potential king castling move
     * @param gameData game data to modify
     */
    void manageCastling(const Move& move, GameData& gameData) const;

    /**
     * @brief Set promotion position if promotion happened.
     *
     * @param position potential pawn ending position
     * @return false if promotion causes check
     */
    bool managePromotion(const pair<int, int>& position);

    /**
     * @brief Make move along with special moves that the move causes.
     *
     * @param move move to make
     * @param gameData game data to modify
     */
    void movePieces(const Move& move, GameData& gameData) const;

    /**
     * @brief Get all legal moves from given position. (not checking for check)
     *
     * @param from starting square
     * @param gameData game data to analyze
     * @return unordered set of legal moves
     */
    unordered_set<Move, Move::Hash> getLegalMoves(pair<int, int> from, const GameData& gameData) const;

    /**
     * @brief Get all legal moves from given position that don't lead to check of current player.
     *
     * @param from starting square
     * @param gameData game data to analyze
     * @return unordered set of fully legal moves
     */
    unordered_set<Move, Move::Hash> getFullyLegalMoves(pair<int, int> from, const GameData& gameData) const;

    /**
     * @brief Check if given player is in check.
     *
     * @param gameData game data to analyze
     * @param player player to check
     * @return true if player is in check
     */
    bool isCheck(const GameData& gameData, bool player) const;

    /**
     * @brief Check if a game is in stalemate state.
     *
     * @param gameData game data to analyze
     * @return true if game is in stalemate state
     */
    bool isStalemate(const GameData& gameData) const;

    /**
     * @brief Set the current game state.
     *
     */
    void evaluateState();

    /**
     * @brief Check if there is a check in the current game.
     *
     * @return true if there is a check
     */
    bool isCheck() const;

    /**
     * @brief Check if a game is in checkmate state.
     *
     * @param gameData game data to analyze
     * @return true if game is in checkmate state
     */
    bool isCheckmate(const GameData& gameData) const;

    /**
     * @brief Modify current game data by making full normal chess move.
     *
     * @param move move to make
     * @return true if move is valid
     */
    bool makeNormalMove(const Move& move);

public:
    /**
     * @brief Construct a new Game object.
     *
     */
    Game();

    /**
     * @brief Destroy the Game object.
     *
     */
    virtual ~Game();

    /**
     * @brief Reset the game to initial state.
     *
     */
    void reset();

    /**
     * @brief Return current game board.
     *
     * @return board represented by 2d array of piece codes
     */
    array<array<int, 8>, 8> board() const;

    /**
     * @brief Load game from FEN string.
     *
     * @param fen FEN string
     * @return true if FEN is in valid format
     */
    bool loadGame(const string& fen);

    /**
     * @brief Get current player.
     *
     * @return true: white
     * @return false: black
     */
    bool currentPlayer() const;

    /**
     * @brief Get waiting for pawn promotion state.
     *
     * @return true if the game is waiting for pawn promotion
     */
    bool isPromotion() const;

    /**
     * @brief Promote pawn waiting for promotion.
     *
     * @param piece piece code to promote to
     * @return true if the promotion is valid
     */
    bool promote(int piece);

    /**
     * @brief Get the current game state.
     *
     * @return 0: normal
     * @return 1: check
     * @return 2: white won
     * @return 3: black won
     * @return 4: stalemate
     */
    int state() const;

    /**
     * @brief Get FEN string representing the current game.
     *
     * @return string
     */
    string fen() const;

    /**
     * @brief Get castling state.
     *
     * @return string representing castling in FEN format
     */
    string castling() const;

    /**
     * @brief Get the total number of full moves.
     *
     * @return number of full moves
     */
    int moves() const;

    /**
     * @brief Get the number of half moves without killing or moving pawn.
     *
     * @return halfmove clock value
     */
    int halfmoveClock() const;

    /**
     * @brief Make chess move.
     *
     * @param move move to make
     * @return true if the move is valid
     */
    virtual bool makeMove(const Move& move) = 0;

    /**
     * @brief Get the last move.
     *
     * @return last move
     */
    Move lastMove() const;
};