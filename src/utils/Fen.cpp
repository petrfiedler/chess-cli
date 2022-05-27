#ifndef FEN_3455
#define FEN_3455
#include "../utils/Fen.h"
#endif

string Fen::pieceString(int code) {
    switch (code) {
    case 1: return "P";
    case 2: return "R";
    case 3: return "N";
    case 4: return "B";
    case 5: return "Q";
    case 6: return "K";
    case -1: return "p";
    case -2: return "r";
    case -3: return "n";
    case -4: return "b";
    case -5: return "q";
    case -6: return "k";
    default: return "";
    }
}

int Fen::pieceCode(char repr) {
    switch (repr) {
    case 'P': return 1;
    case 'R': return 2;
    case 'N': return 3;
    case 'B': return 4;
    case 'Q': return 5;
    case 'K': return 6;
    case 'p': return -1;
    case 'r': return -2;
    case 'n': return -3;
    case 'b': return -4;
    case 'q': return -5;
    case 'k': return -6;
    default: return 0;
    }
}


string Fen::generate(const GameData& game) {
    string fen = "";

    // board state
    int empty = 0;
    for (int y = 0; y < 8; y++) {
        empty = 0;
        for (int x = 0; x < 8; x++) {
            if (game.board()[y][x] == 0) {
                empty++;
            }
            else {
                if (empty != 0) {
                    fen += to_string(empty);
                    empty = 0;
                }
                fen += pieceString(game.board()[y][x]);
            }
        }
        if (empty != 0) {
            fen += to_string(empty);
        }
        if (y != 7) {
            fen += "/";
        }
    }
    fen += " ";

    // active player
    fen += (game.currentPlayer() ? "w" : "b");
    fen += " ";

    // castling
    fen += (game.castlingKW() ? "K" : "");
    fen += (game.castlingQW() ? "Q" : "");
    fen += (game.castlingKB() ? "k" : "");
    fen += (game.castlingQB() ? "q" : "");
    if (!game.castlingKW() && !game.castlingQW() && !game.castlingKB() && !game.castlingQB()) {
        fen += "-";
    }
    fen += " ";

    // en passant
    if (game.isEnPassant()) {
        fen += 'a' + game.enPassantPos().second;
        fen += to_string(8 - game.enPassantPos().first);
    }
    else {
        fen += "-";
    }
    fen += " ";

    // halfmove clock
    fen += to_string(game.halfmoveClock());
    fen += " ";

    // fullmove clock
    fen += to_string(game.fullmoveClock());

    return fen;
}

vector<string> Fen::splitToWords(const string& str) {
    vector<string> words;
    string word = "";
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == ' ') {
            words.push_back(word);
            word = "";
        }
        else {
            word += str[i];
        }
    }
    words.push_back(word);

    return words;
}

bool Fen::checkFenBoard(const string& fenBoard) {
    bool whiteKing = false;
    bool blackKing = false;
    int segments = 1;
    int segmentSquares = 0;
    string allowedPieces = "prkqbnPRKQBN";

    for (char c : fenBoard) {
        // end of segment
        if (c == '/') {
            // one line (segment) has to have 8 squares
            if (segmentSquares != 8) return false;
            segments++;
            segmentSquares = 0;
        }

        // count squares
        else if (c > '0' && c < '9') {
            segmentSquares += c - '0';
        }
        else if (allowedPieces.find(c) != string::npos) {
            segmentSquares++;
        }
        else {
            return false;
        }

        // there have to be two kings
        if (c == 'K') {
            // there can only be one white king
            if (whiteKing) return false;
            whiteKing = true;
        }
        else if (c == 'k') {
            // there can only be one black king
            if (blackKing) return false;
            blackKing = true;
        }
    }

    return segments == 8 && whiteKing && blackKing;
}

bool Fen::checkFenFlags(const vector<string>& fenWords) {
    // check active player flag
    if (fenWords[1] != "w" && fenWords[1] != "b") return false;

    //check castling flags
    if (fenWords[2] != "-") {
        array<int, 4> castlingCount = { 0, 0, 0, 0 };
        if (fenWords[2].size() > 4) return false;
        for (char c : fenWords[2]) {
            if (c == 'K') castlingCount[0]++;
            else if (c == 'Q') castlingCount[1]++;
            else if (c == 'k') castlingCount[2]++;
            else if (c == 'q') castlingCount[3]++;
            else return false;
        }
        for (int count : castlingCount) {
            if (count > 1) return false;
        }
    }

    // check en passant flag
    if (fenWords[3] != "-") {
        if (fenWords[3].size() != 2) return false;
        if (fenWords[3][0] < 'a' || fenWords[3][0] > 'h') return false;
        if (fenWords[3][1] < '1' || fenWords[3][1] > '8') return false;
    }

    // check halfmove clock flag
    for (char c : fenWords[4]) {
        if (c < '0' || c > '9') return false;
    }
    if (stoi(fenWords[4]) > 100) return false;

    // check fullmove clock flag
    for (char c : fenWords[5]) {
        if (c < '0' || c > '9') return false;
    }

    return true;
}

bool Fen::checkValidFenWords(const vector<string>& fenWords) {
    // check game data
    if (fenWords.size() != 6) return false;
    if (!checkFenBoard(fenWords[0])) return false;
    if (!checkFenFlags(fenWords)) return false;

    return true;
}

array<array<int, 8>, 8> Fen::buildBoard(const string& fenBoard) {
    // initialize zero array
    array<array<int, 8>, 8> board;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = 0;
        }
    }

    size_t rowIndex = 0;
    size_t columnIndex = 0;
    for (char c : fenBoard) {
        if (c == '/') {
            columnIndex = 0;
            rowIndex++;
        }
        else if (c > '0' && c < '9') {
            int emptySize = c - '0';
            columnIndex += emptySize;
        }
        else {
            board[rowIndex][columnIndex] = pieceCode(c);
            columnIndex++;
        }
    }

    return board;
}

void Fen::setFlags(GameData& game, const vector<string>& fenWords) {
    // active player flag
    game.setCurrentPlayer(fenWords[1] == "w");

    // castling flags
    array<bool, 4> castling = { 0,0,0,0 };
    for (char c : fenWords[2]) {
        switch (c) {
        case 'K': castling[0] = true; break;
        case 'Q': castling[1] = true; break;
        case 'k': castling[2] = true; break;
        case 'q': castling[3] = true; break;
        }
    }
    game.setCastling(castling);

    // en passant
    if (fenWords[3] == "-") {
        game.setEnPassant(make_pair(-1, -1));
    }
    else {
        int x = fenWords[3][0] - 'a';
        int y = 8 - (fenWords[3][1] - '0');
        game.setEnPassant(make_pair(y, x));
    }

    // halfmove clock
    game.setHalfmoveClock(stoi(fenWords[4]));

    // fullmove clock
    game.setFullmoveClock(stoi(fenWords[5]));
}

GameData Fen::load(const string& fen) {
    vector<string> fenWords = splitToWords(fen);

    if (!checkValidFenWords(fenWords)) throw invalid_argument("Invalid FEN format.");

    GameData game = GameData();
    array<array<int, 8>, 8> board = buildBoard(fenWords[0]);
    setFlags(game, fenWords);
    game.setBoard(board);

    return game;
}

bool Fen::checkValidFen(const string& fen) {
    vector<string> fenWords = splitToWords(fen);
    return checkValidFenWords(fenWords);
}