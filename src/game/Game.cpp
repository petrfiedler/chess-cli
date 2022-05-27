#ifndef GAME_6876
#define GAME_6876
#include "Game.h"
#endif

Game::Game() {
    // initial game state
    reset();

    m_Pieces = {
        nullptr,
        new Pawn(),
        new Rook(),
        new Knight(),
        new Bishop(),
        new Queen(),
        new King()
    };
}

void Game::reset() {
    m_GameData = GameData();
    m_GameState = 0;
    m_Promotion = make_pair(-1, -1);
    m_LastMove = Move();
}

Game::~Game() {
    for (auto piece : m_Pieces) {
        delete piece;
    }
}

array<array<int, 8>, 8> Game::board() const {
    return m_GameData.board();
}

void Game::checkSelectedPiece(int piece) const {
    if (piece == 0) {
        throw invalid_argument("No piece on selected square.");
    }
    if ((piece > 0) != m_GameData.currentPlayer()) {
        throw invalid_argument("Can't move oponent's piece.");
    }
}

bool Game::checkLegalMove(const Move& move) const {
    int figure = m_GameData.board()[move.from().first][move.from().second];
    if (figure == 0) return false;
    Piece* piece = m_Pieces[abs(figure)];

    bool isLegal = piece->checkValidMove(move, m_GameData);
    return isLegal;
}

bool Game::currentPlayer() const {
    return m_GameData.currentPlayer();
}

string Game::fen() const {
    return Fen::generate(m_GameData);
}

void Game::manageEnPassant(const Move& move, GameData& gameData) const {
    if (abs(gameData.board()[move.from().first][move.from().second]) == 1
        && move.from().second != move.to().second
        && gameData.board()[move.to().first][move.to().second] == 0) {
        gameData.kill(make_pair(move.from().first, move.to().second));
    }
}

void Game::manageCastling(const Move& move, GameData& gameData) const {
    if (abs(gameData.board()[move.from().first][move.from().second]) == 6
        && abs(move.from().second - move.to().second) == 2) {
        int rookFromX = 7 * (move.to().second / 4);
        int rookToX = rookFromX == 7 ? 5 : 3;
        Move rookMove(move.from().first, rookFromX, move.from().first, rookToX);
        gameData.move(rookMove, true);
    }
}

Move Game::lastMove() const {
    return m_LastMove;
}

void Game::movePieces(const Move& move, GameData& gameData) const {
    manageEnPassant(move, gameData);
    manageCastling(move, gameData);
    gameData.move(move);
}

bool Game::loadGame(const string& fen) {
    try {
        m_GameData = Fen::load(fen);
    }
    catch (invalid_argument& e) {
        return false;
    }
    evaluateState();
    return true;
}

unordered_set<Move, Move::Hash> Game::getLegalMoves(pair<int, int> from, const GameData& gameData) const {
    unordered_set<Move, Move::Hash> moves;
    int figure = gameData.board()[from.first][from.second];
    if (figure == 0) {
        return moves;
    }
    // go through each square and determine if the move there is legal
    Piece* piece = m_Pieces[abs(figure)];
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (piece->checkValidMove(Move(from.first, from.second, y, x), gameData)) {
                moves.insert(Move(from.first, from.second, y, x));
            }
        }
    }
    return moves;
}

unordered_set<Move, Move::Hash> Game::getFullyLegalMoves(pair<int, int> from, const GameData& gameData) const {
    unordered_set<Move, Move::Hash> moves = getLegalMoves(from, gameData);
    // select only moves that don't lead to check
    int figure = gameData.board()[from.first][from.second];
    unordered_set<Move, Move::Hash> movesNoCheck;
    for (const Move& move : moves) {
        GameData gameDataCopy = gameData;
        movePieces(move, gameDataCopy);
        if (!isCheck(gameDataCopy, figure > 0)) {
            movesNoCheck.insert(move);
        }
    }
    return movesNoCheck;
}

bool Game::isCheck(const GameData& gameData, bool player) const {
    // get target king position
    pair<int, int> targetKing;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if ((gameData.board()[y][x] == 6 && player) || (gameData.board()[y][x] == -6 && !player)) {
                targetKing = make_pair(y, x);
                break;
            }
        }
    }
    // go through the board and find if any legal move leads to the king
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            unordered_set<Move, Move::Hash> legalMoves = getLegalMoves(make_pair(y, x), gameData);
            for (const Move& move : legalMoves) {
                if (move.to() == targetKing) return true;
            }
        }
    }
    return false;
}

bool Game::isCheckmate(const GameData& gameData) const {
    // get player in check
    int playerInCheck = 0;
    if (isCheck(m_GameData, 1)) {
        playerInCheck = 1;
    }
    else if (!isCheck(m_GameData, 0)) {
        return false;
    }

    // go through board and check if there is piece with fully legal move
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (((gameData.board()[y][x] > 0) == playerInCheck)
                && (gameData.board()[y][x] != 0)) {
                // get legal moves from current piece
                unordered_set<Move, Move::Hash> legalMoves = getFullyLegalMoves(make_pair(y, x), gameData);
                if (legalMoves.size() != 0) return false;
            }
        }
    }
    return true;
}

bool Game::isStalemate(const GameData& gameData) const {
    if (gameData.halfmoveClock() >= 100) return true;
    // count available moves
    int availableMoves[2] = { 0, 0 };
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (gameData.board()[y][x] != 0) {
                // get legal moves from current piece
                unordered_set<Move, Move::Hash> legalMoves = getFullyLegalMoves(make_pair(y, x), gameData);
                availableMoves[gameData.board()[y][x] > 0] += legalMoves.size();
                if (availableMoves[0] != 0 && availableMoves[1] != 0) return false;
            }
        }
    }
    return true;
}

string Game::castling() const {
    string castling = "";
    if (m_GameData.castlingKW()) castling += "K";
    if (m_GameData.castlingQW()) castling += "Q";
    if (m_GameData.castlingKB()) castling += "k";
    if (m_GameData.castlingQB()) castling += "q";
    if (castling.empty()) castling = "-";
    return castling;
}

int Game::halfmoveClock() const {
    return m_GameData.halfmoveClock();
}

int Game::moves() const {
    return m_GameData.fullmoveClock();
}

void Game::evaluateState() {
    m_GameState = isCheck(m_GameData, m_GameData.currentPlayer());
    if (isCheckmate(m_GameData)) {
        m_GameState += m_GameData.currentPlayer() + 1;
    }
    else if (isStalemate(m_GameData)) {
        m_GameState = 4;
    }
}

int Game::state() const {
    return m_GameState;
}

bool Game::makeNormalMove(const Move& move) {
    // save old game data for transactional behaviour
    GameData oldGameData = m_GameData;
    // check validity of move
    int piece = m_GameData.board()[move.from().first][move.from().second];
    checkSelectedPiece(piece);
    if (!checkLegalMove(move)) return false;
    // manage special moves
    manageEnPassant(move, m_GameData);
    manageCastling(move, m_GameData);
    // make the move
    m_GameData.move(move);
    // if the player put or kept himself in check or can't promote, the move is invaid
    if (!managePromotion(move.to())
        || isCheck(m_GameData, m_GameData.currentPlayer())) {
        m_GameData = oldGameData;
        return false;
    }
    // if promotion happened, let player choose the figure before changing the player
    if (isPromotion()) return true;
    m_GameData.nextPlayer();
    // evaluate game state
    evaluateState();
    m_LastMove = move;
    return true;
}

bool Game::managePromotion(const pair<int, int>& position) {
    int figure = m_GameData.board()[position.first][position.second];
    if ((abs(figure) != 1) ||
        (position.first != 7 && position.first != 0)) return true;
    // check if piece choice that doesn't cause check exists
    int possiblePieces[4] = { 2, 3, 4, 5 };
    for (int possiblePiece : possiblePieces) {
        GameData gameData = m_GameData;
        gameData.place(position, possiblePiece * (figure / abs(figure)));
        if (!isCheck(gameData, m_GameData.currentPlayer())) {
            m_Promotion = position;
            return true;
        }
    }
    return false;
}

bool Game::isPromotion() const {
    return m_Promotion.first != -1;
}

bool Game::promote(int piece) {
    if (!m_GameData.currentPlayer()) piece *= -1;
    // back up old game data
    GameData oldGameData = m_GameData;
    m_GameData.place(m_Promotion, piece);
    // promotion must not put player in check
    if (isCheck(m_GameData, m_GameData.currentPlayer())) {
        m_GameData = oldGameData;
        return false;
    }
    // complete the turn
    m_GameData.nextPlayer();
    evaluateState();
    m_Promotion = make_pair(-1, -1);
    return true;
}