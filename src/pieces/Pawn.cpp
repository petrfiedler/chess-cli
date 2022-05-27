#include "Pawn.h"
#include <cmath>

bool Pawn::checkValidMove(const Move& move, const GameData& gameData) const {
    Move moveView = getMoveView(move, gameData);
    array<array<int, 8>, 8> boardView = getBoardView(move, gameData);

    if (!checkBoundaries(moveView)) return false;
    // move by one
    if (moveView.from().first - moveView.to().first == 1) {
        // move diagonally to opponent's piece or en passant
        if (abs(moveView.from().second - moveView.to().second) == 1
            && (isOponent(moveView, boardView)
                || isEnPassant(move, gameData))) {
            return true;
        }
        // move forward to empty square
        if (abs(moveView.from().second - moveView.to().second) == 0
            && isEmptyDestination(moveView, boardView)) {
            return true;
        }
        return false;
    }
    // move by two on first move
    if (moveView.from().first == 6
        && moveView.from().first - moveView.to().first == 2
        && moveView.from().second == moveView.to().second
        && isEmptyDestination(moveView, boardView)
        && isEmptyPath(moveView, boardView)) {
        return true;
    }
    return false;
}

bool Pawn::isEnPassant(const Move& move, const GameData& gameData) const {
    return move.to() == gameData.enPassantPos();
}