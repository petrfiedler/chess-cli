#ifndef GAME_AI_7856
#define GAME_AI_7856
#include "GameAI.h"
#endif

GameAI::GameAI(int level) {
    if (level < 1 || level > 3) {
        throw std::invalid_argument("Level must be between 1 and 3.");
    }
    m_Level = level;
}

void GameAI::makeAIMove() {
    // find the best move using minimax algorithm
    Move bestMove = Move();
    int value, lowestValue = INT_MAX;
    for (const auto& move : possibleMoves(m_GameData)) {
        GameData gameData = simulateMove(m_GameData, move);
        value = minimax(gameData, m_Level - 1);
        // lowest value is the best
        if (value <= lowestValue) {
            bestMove = move;
            lowestValue = value;
        }
    }
    // make the move
    makeNormalMove(bestMove);
    // manage promotion
    if (isPromotion()) {
        // try promoting to pieces (starting with queen)
        for (int piece = 5; piece > 1; piece--) {
            if (promote(piece)) break;
        }
    }

}

bool GameAI::makeMove(const Move& move) {
    // AI's turn (ignoring move)
    if (!m_GameData.currentPlayer()) {
        makeAIMove();
        return true;
    }
    // human's turn
    return makeNormalMove(move);
}

int GameAI::pieceValue(int piece) {
    int sign = piece / abs(piece);
    switch (abs(piece)) {
    case 1: return 1 * sign; // pawn
    case 2: return 5 * sign; // rook
    case 3: return 2 * sign; // bishop
    case 4: return 3 * sign; // knight
    case 5: return 9 * sign; // queen
    default: return 0; // king / empty
    }
}

bool GameAI::canBeAttacked(pair<int, int> position, const GameData& gameData) const {
    // check if any pice that has valid move there exists
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            Piece* piece = m_Pieces[abs(gameData.board()[y][x])];
            if (gameData.board()[y][x] != 0 &&
                piece->checkValidMove(Move(y, x, position.first, position.second), gameData)) {
                return true;
            }
        }
    }
    return false;
}

bool GameAI::canAttackKing(pair<int, int> position, const GameData& gameData) const {
    if (gameData.board()[position.first][position.second] == 0) return false;
    // find kings
    pair<int, int> blackKing;
    pair<int, int> whiteKing;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (gameData.board()[y][x] == -6) {
                blackKing = make_pair(y, x);
            }
            else if (gameData.board()[y][x] == 6) {
                whiteKing = make_pair(y, x);
            }
        }
    }
    // check if the piece has valid move to any of the kings
    Piece* piece = m_Pieces[abs(gameData.board()[position.first][position.second])];
    if (piece->checkValidMove(Move(position.first, position.second, blackKing.first, blackKing.second), gameData) ||
        piece->checkValidMove(Move(position.first, position.second, whiteKing.first, whiteKing.second), gameData)) {
        return true;
    }
    return false;
}

int GameAI::evaluateBoard(const GameData& gameData) const {
    int score = 0;
    // add points for check
    if (isCheck(gameData, 1)) {
        score -= 10;
        if (isCheckmate(gameData)) score -= 100;
    }
    else if (isCheck(gameData, 0)) {
        score += 10;
        if (isCheckmate(gameData)) score += 100;
    }
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            int piece = gameData.board()[y][x];
            // add points for pieces that are not under attack
            if (!canBeAttacked(make_pair(y, x), gameData)) {
                score += pieceValue(piece);
                // pawn gets points for the distance he travelled
                if (piece == -1) score -= y - 2;
                else if (piece == 1) score += 5 - y;
            }
            // remove points for pieces that are under attack
            else {
                score -= pieceValue(piece);
                // remove more points if piece that caused check is under attack
                if (canAttackKing(make_pair(y, x), gameData)) score -= 3 * pieceValue(piece);
            }
        }
    }
    return score;
}

unordered_set<Move, Move::Hash> GameAI::possibleMoves(const GameData& gameData) const {
    unordered_set<Move, Move::Hash> moves;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if ((gameData.board()[y][x] != 0) &&
                ((gameData.board()[y][x] > 0) == gameData.currentPlayer())) {
                // get legal moves from current piece
                unordered_set<Move, Move::Hash> legalMoves = getFullyLegalMoves(make_pair(y, x), gameData);
                moves.insert(legalMoves.begin(), legalMoves.end());
            }
        }
    }
    return moves;
}

GameData GameAI::simulateMove(const GameData& gameData, const Move& move) const {
    GameData newGameData = gameData;
    movePieces(move, newGameData);
    newGameData.nextPlayer();
    // promotion
    int figure = gameData.board()[move.from().first][move.from().second];
    if ((abs(figure) == 1) &&
        (move.to().first == 7 || move.to().first == 0)) {
        newGameData.place(move.to(), 5 * (figure / abs(figure)));
    }
    return newGameData;
}

bool GameAI::isGameOver(const GameData& gameData) const {
    return isCheck(gameData, 0) || isCheck(gameData, 1) || isStalemate(gameData);
}

int GameAI::minimax(const GameData& gameData, int depth, int alpha, int beta) const {
    // leaf
    if (depth == 0 || isGameOver(gameData)) {
        return evaluateBoard(gameData);
    }
    // initialize to worst possible values
    int value, minimaxValue = gameData.currentPlayer() ? INT_MIN : INT_MAX;
    unordered_set<Move, Move::Hash> moves = possibleMoves(gameData);
    // each possible move is a new branch
    for (const auto& move : moves) {
        GameData newGameData = simulateMove(gameData, move);
        // recursive call
        value = minimax(newGameData, depth - 1, alpha, beta);
        // white is trying to maximize
        if (gameData.currentPlayer()) {
            minimaxValue = value >= minimaxValue ? value : minimaxValue;
            // alpha is the highest of values of the branches
            alpha = alpha > value ? alpha : value;
        }
        // black is trying to minimize
        else {
            minimaxValue = value <= minimaxValue ? value : minimaxValue;
            // beta is the lowest of values of the branches
            beta = beta < value ? beta : value;
        }
        // prune branches with no outcome (alpha should be lower than beta for possible outcome)
        if (beta <= alpha) {
            break;
        }
    }
    return minimaxValue;
}