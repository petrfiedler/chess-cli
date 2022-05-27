#ifndef GAME_DATA_1655
#define GAME_DATA_1655
#include "GameData.h"
#endif

GameData::GameData() {
    m_Board = { {
        {-2,-3,-4,-5,-6,-4,-3,-2 },
        {-1,-1,-1,-1,-1,-1,-1,-1 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 1 },
        { 2, 3, 4, 5, 6, 4, 3, 2 }
    } };

    m_CurrentPlayer = 1;

    m_Castling = { {1, 1, 1, 1} };

    m_EnPassant = make_pair(-1, -1);

    m_HalfmoveClock = 0;

    m_FullmoveClock = 1;
}

array<array<int, 8>, 8> GameData::board() const {
    return m_Board;
}

bool GameData::currentPlayer() const {
    return m_CurrentPlayer;
}

bool GameData::castlingKW() const {
    return m_Castling[0];
}

bool GameData::castlingQW() const {
    return m_Castling[1];
}

bool GameData::castlingKB() const {
    return m_Castling[2];
}

bool GameData::castlingQB() const {
    return m_Castling[3];
}

pair<int, int> GameData::enPassantPos() const {
    return m_EnPassant;
}

int GameData::halfmoveClock() const {
    return m_HalfmoveClock;
}

int GameData::fullmoveClock() const {
    return m_FullmoveClock;
}

bool GameData::isEnPassant() const {
    return m_EnPassant.first != -1;
}

void GameData::move(const Move& move, bool noClock) {
    // update halfmove clock
    if (!noClock) {
        if (m_Board[move.to().first][move.to().second] == 0 &&
            abs(m_Board[move.from().first][move.from().second]) != 1) {
            m_HalfmoveClock++;
        }
        else {
            m_HalfmoveClock = 0;
        }
    }

    // update en passant
    if (abs(m_Board[move.from().first][move.from().second]) == 1
        && abs(move.from().first - move.to().first) == 2) {
        m_EnPassant = make_pair((move.from().first + move.to().first) / 2, move.to().second);
    }
    else {
        m_EnPassant = make_pair(-1, -1);
    }

    // update castling
    if (m_Board[move.from().first][move.from().second] == 6) {
        m_Castling[0] = false;
        m_Castling[1] = false;
    }
    else if (m_Board[move.from().first][move.from().second] == -6) {
        m_Castling[2] = false;
        m_Castling[3] = false;
    }
    // moving rook
    else if (abs(m_Board[move.from().first][move.from().second]) == 2) {
        if (move.from().first == 7 && move.from().second == 7) {
            m_Castling[0] = false;
        }
        else if (move.from().first == 7 && move.from().second == 0) {
            m_Castling[1] = false;
        }
        else if (move.from().first == 0 && move.from().second == 7) {
            m_Castling[2] = false;
        }
        else if (move.from().first == 0 && move.from().second == 0) {
            m_Castling[3] = false;
        }
    }
    // killing rook
    if (abs(m_Board[move.to().first][move.to().second]) == 2) {
        if (move.to().first == 7 && move.to().second == 7) {
            m_Castling[0] = false;
        }
        else if (move.to().first == 7 && move.to().second == 0) {
            m_Castling[1] = false;
        }
        else if (move.to().first == 0 && move.to().second == 7) {
            m_Castling[2] = false;
        }
        else if (move.to().first == 0 && move.to().second == 0) {
            m_Castling[3] = false;
        }
    }

    // update board
    m_Board[move.to().first][move.to().second] = m_Board[move.from().first][move.from().second];
    m_Board[move.from().first][move.from().second] = 0;

}

void GameData::kill(pair<int, int> square) {
    m_Board[square.first][square.second] = 0;

    // reset halfmove clock
    m_HalfmoveClock = 0;
}

void GameData::place(pair<int, int> square, int piece) {
    m_Board[square.first][square.second] = piece;
}

void GameData::setCurrentPlayer(bool value) {
    m_CurrentPlayer = value;
}

void GameData::setCastling(array<bool, 4> value) {
    m_Castling = value;
}

void GameData::setEnPassant(pair<int, int> value) {
    m_EnPassant = value;
}

void GameData::setHalfmoveClock(int value) {
    m_HalfmoveClock = value;
}

void GameData::setFullmoveClock(int value) {
    m_FullmoveClock = value;
}

void GameData::setBoard(array<array<int, 8>, 8> value) {
    m_Board = value;
}

void GameData::nextPlayer() {
    m_CurrentPlayer = !m_CurrentPlayer;

    // update fullmove clock
    if (m_CurrentPlayer) {
        m_FullmoveClock++;
    }
}