#ifndef PIECE_7815
#define PIECE_7815
#include "Piece.h"
#endif

#include <cmath>


Piece::~Piece() = default;

bool Piece::checkBoundaries(const Move & move) const {
    int y = move.to().first;
    int x = move.to().second;
    return x >= 0 && x <= 7 && y >= 0 && y <= 7;
}

int Piece::getSign(const pair<int, int>&coords, const array<array<int, 8>, 8>&board) const {
    int piece = board[coords.first][coords.second];
    return piece / abs(piece);
}

bool Piece::isOponent(const Move & move, const array<array<int, 8>, 8>&board) const {
    if (isEmptyDestination(move, board)) return false;
    return getSign(move.from(), board) != getSign(move.to(), board);
}

bool Piece::isEmptyDestination(const Move & move, const array<array<int, 8>, 8>&board) const {
    return board[move.to().first][move.to().second] == 0;
}

bool Piece::isEmptyPath(const Move & move, const array<array<int, 8>, 8>&board) const {
    int y = move.from().first;
    int x = move.from().second;
    while (42) {
        // don't consider destination square (end of cycle)
        if (y == move.to().first && x == move.to().second) {
            return true;
        }
        // don't consider starting square
        if (y != move.from().first || x != move.from().second) {
            // check emptiness
            if (board[y][x] != 0) return false;
        }
        // inc/dec
        if (move.from().second < move.to().second) x++;
        else if (move.from().second > move.to().second)  x--;
        if (move.from().first < move.to().first) y++;
        else if (move.from().first > move.to().first) y--;
    }
    return false;
}

bool Piece::isOrthogonalMove(const Move & move) const {
    return move.from().first == move.to().first || move.from().second == move.to().second;
}

bool Piece::isDiagonalMove(const Move & move) const {
    int dy = abs(move.from().first - move.to().first);
    int dx = abs(move.from().second - move.to().second);
    return dx == dy;
}

Move Piece::getMoveView(const Move & move, const GameData & gameData) const {
    int pieceCode = gameData.board()[move.from().first][move.from().second];
    if (pieceCode > 0) return move;
    return move.flipped();
}

array<array<int, 8>, 8> Piece::getBoardView(const Move & move, const GameData & gameData) const {
    int pieceCode = gameData.board()[move.from().first][move.from().second];
    // white player board view
    if (pieceCode > 0) return gameData.board();

    // black player board view
    array<array<int, 8>, 8> flippedBoard;
    for (size_t i = 0; i < 8; i++) {
        flippedBoard[7 - i] = gameData.board()[i];
    }
    return flippedBoard;
}
