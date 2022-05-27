#include "Knight.h"
#include <cmath>

bool Knight::checkValidMove(const Move& move, const GameData& gameData) const {
    Move moveView = getMoveView(move, gameData);
    array<array<int, 8>, 8> boardView = getBoardView(move, gameData);

    if (!checkBoundaries(moveView)) return false;
    // must move in L shape
    if (!isKnightMove(moveView)) return false;
    // can kill where it moves
    if (isOponent(moveView, boardView)) return true;
    if (!isEmptyDestination(moveView, boardView)) return false;
    return true;
}

bool Knight::isKnightMove(const Move& move) const {
    int dy = abs(move.from().first - move.to().first);
    int dx = abs(move.from().second - move.to().second);
    return (dy == 1 && dx == 2) || (dy == 2 && dx == 1);
}