#ifndef GAME_DATA_1655
#define GAME_DATA_1655
#include "../game/GameData.h"
#endif

/**
 * @brief Forsyth-Edwards Notation utilities.
 *
 */
class Fen {
private:
    /**
     * @brief Convert from piece code to piece string representation.
     *
     * @param code piece code
     * @return piece string representation
     */
    static string pieceString(int piece);

    /**
     * @brief Convert from piece string representation to piece code.
     *
     * @param repr piece string representation
     * @return piece code
     */
    static int pieceCode(char repr);

    /**
     * @brief Split string to words.
     *
     * @param str string to split
     * @return vector of words
     */
    static vector<string> splitToWords(const string& str);

    /**
     * @brief Check if board represented by FEN is valid.
     *
     * @param fenBoard string with board in FEN format
     * @return validity
     */
    static bool checkFenBoard(const string& fenBoard);

    /**
     * @brief Check if flags represented by FEN are valid.
     *
     * @param fenWords FEN string splitted to words
     * @return validity
     */
    static bool checkFenFlags(const vector<string>& fenWords);

    /**
     * @brief Build game board from FEN board string.
     *
     * @param fenBoard FEN board string
     * @return game board array
     */
    static array<array<int, 8 >, 8> buildBoard(const string& fenBoard);

    /**
     * @brief Set flags to game data from FEN string.
     *
     * @param game game data to modify
     * @param fenWords FEN string splitted to words
     */
    static void setFlags(GameData& game, const vector<string>& fenWords);

    /**
     * @brief Check if FEN string is valid.
     *
     * @param fenWords FEN string splitted to words
     * @return validity
     */
    static bool checkValidFenWords(const vector<string>& fenWords);

public:
    /**
     * @brief Generate FEN string from game data.
     *
     * @param game game data
     * @return FEN string
     */
    static string generate(const GameData& game);

    /**
     * @brief Load FEN data into new GameData object. If FEN is invalid, throw an exception.
     *
     * @param fen FEN string
     * @return new GameData object
     */
    static GameData load(const string& fen);

    /**
     * @brief Check if FEN string has valid format.
     *
     * @param fen FEN string check
     * @return true if the FEN string has valid format
     */
    static bool checkValidFen(const string& fen);
};