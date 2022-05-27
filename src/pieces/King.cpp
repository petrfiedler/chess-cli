#include "King.h"
#include <iostream>
#include <cmath>

bool King::checkValidMove(const Move& move, const GameData& gameData) const {
    Move moveView = getMoveView(move, gameData);
    array<array<int, 8>, 8> boardView = getBoardView(move, gameData);

    if (!checkBoundaries(moveView)) return false;
    // move must be by one square
    if (!isKingMove(moveView) && !isCastling(move, gameData)) return false;
    // can kill where it moves
    if (isOponent(moveView, boardView)) return true;
    if (!isEmptyDestination(moveView, boardView)) return false;
    return true;
}

bool King::isKingMove(const Move& move) const {
    int dy = abs(move.from().first - move.to().first);
    int dx = abs(move.from().second - move.to().second);
    return dy <= 1 && dx <= 1;
}

bool King::isCastling(const Move& move, const GameData& gameData) const {
    // must start on 4th column
    if (move.from().second != 4) return false;

    // black king castling
    if (move.from().first == 0) {
        // check column
        if (move.to().second != 2 && move.to().second != 6) return false;
        else if (move.to().second == 6 && !gameData.castlingKB()) return false;
        else if (move.to().second == 2 && !gameData.castlingQB()) return false;
    }

    // white king castling
    else if (move.from().first == 7) {
        // check column
        if (move.to().second != 2 && move.to().second != 6) return false;
        else if (move.to().second == 6 && !gameData.castlingKW()) return false;
        else if (move.to().second == 2 && !gameData.castlingQW()) return false;
    }

    // invalid row
    else return false;

    // path from king to rook
    Move pathToRook = Move(move.from().first, move.from().second, move.to().first, 7 * (move.to().second / 4));

    // rook of the same color must be there
    int color = gameData.board()[move.from().first][move.from().second] > 0 ? 1 : 0;
    int endOfPathPiece = gameData.board()[pathToRook.to().first][pathToRook.to().second];
    if ((color && endOfPathPiece != 2)
        || (!color && endOfPathPiece != -2)) return false;

    // path between king and rook must be empty
    return isEmptyPath(pathToRook, gameData.board());
}