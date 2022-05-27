#include "Bishop.h"

bool Bishop::checkValidMove(const Move& move, const GameData& gameData) const {
    Move moveView = getMoveView(move, gameData);
    array<array<int, 8>, 8> boardView = getBoardView(move, gameData);

    if (!checkBoundaries(moveView)) return false;
    // must move diagonally
    if (!isDiagonalMove(moveView)) return false;
    // path must be empty
    if (!isEmptyPath(moveView, boardView)) return false;
    // can kill where it moves
    if (isOponent(moveView, boardView)) return true;
    if (!isEmptyDestination(moveView, boardView)) return false;
    return true;
}