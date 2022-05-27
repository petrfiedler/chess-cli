#ifndef MOVE_9545
#define MOVE_9545
#include "../utils/Move.h"
#endif

#include <array>
#include <vector>

/**
 * @brief Static chess game data.
 *
 */
class GameData {
private:
    /**
     * @brief Board represnted by 2d array of piece codes.
     *
     * 0: empty
     * 1: pawn
     * 2: rook
     * 3: knight
     * 4: bishop
     * 5: queen
     * 6: king
     * positive: white
     * negative: black
     *
     */
    array<array<int, 8>, 8> m_Board;

    /**
     * @brief Current player.
     *
     * 1: white
     * 0: black
     *
     */
    bool m_CurrentPlayer;

    /**
     * @brief Castling possibility.
     *
     * [0]: kingside white
     * [1]: queenside black
     * [2]: kingside black
     * [3]: queenside black
     *
     */
    array<bool, 4> m_Castling;

    /**
     * @brief Position of square skipped by pawn's first move.
     * if the last move did not enable en passant, value is [-1, -1]
     *
     */
    pair<int, int> m_EnPassant;

    /**
     * @brief Number of moves without killing or using pawn.
     *
     */
    int m_HalfmoveClock;

    /**
     * @brief Number of total full moves.
     *
     */
    int m_FullmoveClock;

public:
    /**
     * @brief Construct a new Game Data object.
     *
     */
    GameData();

    /**
     * @brief Get current game board.
     *
     * @return 2d array of piece codes
     */
    array<array<int, 8>, 8> board() const;

    /**
     * @brief Get current player.
     *
     * @return true: white
     * @return false: black
     */
    bool currentPlayer() const;

    /**
     * @brief Determine if white kingside castling is enable.
     *
     * @return true if white kingside castling is enable
     */
    bool castlingKW() const;

    /**
     * @brief Determine if white queenside castling is enable.
     *
     * @return true if white queenside castling is enable
     */
    bool castlingQW() const;

    /**
     * @brief Determine if black kingside castling is enable.
     *
     * @return true if black kingside castling is enable
     */
    bool castlingKB() const;

    /**
     * @brief Determine if black queenside castling is enable.
     *
     * @return true if black queenside castling is enable
     */
    bool castlingQB() const;

    /**
     * @brief Get position of possible en passant destination.
     *
     * @return destination coordinates
     */
    pair<int, int> enPassantPos() const;

    /**
     * @brief Get the number of half moves withou using pawn or killing.
     *
     * @return value of halfmove clock
     */
    int halfmoveClock() const;

    /**
     * @brief Get the total number of full moves.
     *
     * @return value of fullmove clock
     */
    int fullmoveClock() const;

    /**
     * @brief Set the current player.
     *
     * @param value new current player value
     */
    void setCurrentPlayer(bool value);

    /**
     * @brief Set castling flags.
     *
     * @param value array of castling flags
     */
    void setCastling(array<bool, 4> value);

    /**
     * @brief Set en passant destination square.
     *
     * @param value coordinates of destination square
     */
    void setEnPassant(pair<int, int> value);

    /**
     * @brief Set halfmove clock value.
     *
     * @param value halfmove clock value
     */
    void setHalfmoveClock(int value);

    /**
     * @brief Set fullmove clock value.
     *
     * @param value fullmove clock value
     */
    void setFullmoveClock(int value);

    /**
     * @brief Replace the game board with new one.
     *
     * @param value new board
     */
    void setBoard(array<array<int, 8>, 8> value);

    /**
     * @brief Move piece along with updating game flags.
     *
     * @param move move to make
     * @param noClock turn off clock update
     */
    void move(const Move& move, bool noClock = false);

    /**
     * @brief Kill piece at given position.
     *
     * @param square position to kill at
     */
    void kill(pair<int, int> square);

    /**
     * @brief Place a piece at given position.
     *
     * @param square coordinates of position to place to
     * @param piece piece to place
     */
    void place(pair<int, int> square, int piece);

    /**
     * @brief Toggle players.
     *
     */
    void nextPlayer();

    /**
     * @brief Determine if en passant is available.
     *
     * @return true if en passant is available
     */
    bool isEnPassant() const;
};