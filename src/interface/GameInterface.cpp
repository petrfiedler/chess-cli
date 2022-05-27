#ifndef GAME_INTERFACE_9768
#define GAME_INTERFACE_9768
#include "GameInterface.h"
#endif
#ifndef INTERFACE_9684
#define INTERFACE_9684
#include "Interface.h"
#endif

#include <thread>
#include <chrono>
#include <fstream>
#include <iomanip>

GameInterface::GameInterface(Game* game, bool isAI) {
    m_Game = game;
    m_IsAI = isAI;
}

string GameInterface::handlePromotion() {
    string input;
    cout << "Promote to [r/n/b/q]: ";
    cin >> input;
    if (readCommand(input)) return handlePromotion();
    if (input == "quit" || input == "restart") return input;
    if (input != "r" && input != "n" && input != "b" && input != "q") {
        return Interface::RED_FG + "Invalid piece" + Interface::DEFAULT_CLR;
    }
    int promoteTo = 0;
    switch (input[0]) {
    case 'r': {promoteTo = 2; break;}
    case 'n': {promoteTo = 3; break;}
    case 'b': {promoteTo = 4; break;}
    case 'q': {promoteTo = 5; break;}
    }
    if (!m_Game->promote(promoteTo)) {
        return Interface::RED_FG + "Promotion to this piece would cause check." + Interface::DEFAULT_CLR;
    }
    return "";
}

string GameInterface::askMove() {
    string input;
    cout << "Your move: ";
    cin >> input;
    if (readCommand(input)) {
        return askMove();
    }
    if (input == "quit" || input == "restart") return input;
    pair<int, int> from, to;
    try {
        from = parseMove(input);
    }
    catch (const exception& e) {
        return Interface::RED_FG + e.what() + Interface::DEFAULT_CLR;
    }
    cin >> input;
    try {
        to = parseMove(input);
        if (!m_Game->makeMove(Move(from.first, from.second, to.first, to.second))) {
            return Interface::RED_FG + "Invalid move." + Interface::DEFAULT_CLR;
        }
    }
    catch (const exception& e) {
        return Interface::RED_FG + e.what() + Interface::DEFAULT_CLR;
    }
    return "";
}

bool GameInterface::gameEnded() const {
    while (42) {
        cout << "Play again? [y/n]: ";
        string input;
        cin >> input;
        if (input == "n" || input == "y") return input == "y";
        cout << Interface::RED_FG << "Invalid input." << Interface::DEFAULT_CLR << endl << endl;
    }
}

void GameInterface::makeAIMove() const {
    cout << "Computer is thinking..." << endl;
    auto start = chrono::high_resolution_clock::now();
    m_Game->makeMove(Move());
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start).count();
    if (duration < 1) this_thread::sleep_for(chrono::seconds(1 - duration));
    ostringstream os;
    os << m_Game->lastMove();
}

// Main game loop
bool GameInterface::play() {
    string message = "";
    while (42) {
        printGame(message);
        if (m_Game->state() > 1) return gameEnded();
        else if (m_IsAI && !m_Game->currentPlayer()) makeAIMove();
        else if (m_Game->isPromotion()) message = handlePromotion();
        else message = askMove();
        if (message == "quit") return false;
        else if (message == "restart") return true;
    }
    return false;
}

string GameInterface::getPieceChar(int piece) const {
    array<string, 7> repr;
    if (piece < 0) {
        repr = { " "s, "♟"s, "♜"s, "♞"s, "♝"s, "♛"s, "♚"s };
    }
    else {
        repr = { " "s, "♙"s, "♖"s, "♘"s, "♗"s, "♕"s, "♔"s };
    }
    return repr[abs(piece)];
}

string GameInterface::getPieceCharASCII(int piece) const {
    array<string, 7> repr;
    if (piece < 0) {
        repr = { " ", "p", "r", "n", "b", "q", "k" };
    }
    else {
        repr = { " ", "P", "R", "N", "B", "Q", "K" };
    }
    return repr[abs(piece)];
}

void GameInterface::printBoard() const {
    string letters = " a b c d e f g h";
    cout << letters << endl;
    for (int y = 0; y < 8; y++) {
        cout << 8 - y;
        for (int x = 0; x < 8; x++) {
            if ((x + y) % 2 != 0) cout << Interface::YELLOW_BG;
            else cout << Interface::WHITE_BG;
            if (m_Game->lastMove().from() == make_pair(y, x) ||
                m_Game->lastMove().to() == make_pair(y, x)) {
                if ((x + y) % 2 != 0) cout << Interface::CYAN_BG;
                else cout << Interface::BRIGHT_CYAN_BG;
            }
            cout << getPieceChar(m_Game->board()[y][x]) << " ";
        }
        cout << Interface::DEFAULT_CLR << 8 - y << endl;
    }
    cout << letters << endl;
}

void GameInterface::printGame(const string& message) const {
    Interface::clear();
    cout << message << endl << endl;
    printBoard();

    if (m_Game->state() == 1) {
        cout << Interface::YELLOW_FG << setw(6) << "" << "CHECK!" << Interface::DEFAULT_CLR << endl;
    }
    else if (m_Game->state() == 2) {
        cout << endl << Interface::BLUE_FG << setw(4) << "" << "CHECKMATE!" << endl;
        cout << setw(4) << "" << "White won!" << Interface::DEFAULT_CLR << endl << endl;
    }
    else if (m_Game->state() == 3) {
        cout << endl << Interface::BLUE_FG << setw(4) << "" << "CHECKMATE!" << endl;
        cout << setw(4) << "" << "Black won!" << Interface::DEFAULT_CLR << endl << endl;
    }
    else if (m_Game->state() == 4) {
        cout << endl << Interface::BLUE_FG << setw(4) << "" << "STALEMATE!" << Interface::DEFAULT_CLR << endl << endl;
    }
    else cout << endl;

    if (m_Game->state() < 2) {
        cout << "Current player: " << (m_Game->currentPlayer() ? "White" : "Black") << endl;
    }
    cout << endl;
}

pair<int, int> GameInterface::parseMove(const string& move) const {
    if (move.length() != 2) {
        throw invalid_argument("Invalid move instruction.");
    }
    int m[2] = { tolower(move[0]), tolower(move[1]) };
    int x = -1, y = -1;
    if (m[0] >= '1' && m[0] <= '8' && m[1] >= 'a' && m[1] <= 'h') {
        y = 8 - (move[0] - '0');
        x = m[1] - 'a';
    }
    else if (m[1] >= '1' && m[1] <= '8' && m[0] >= 'a' && m[0] <= 'h') {
        y = 8 - (move[1] - '0');
        x = m[0] - 'a';
    }
    else {
        throw invalid_argument("Invalid move instruction.");
    }
    return make_pair(y, x);
}

void GameInterface::printHelp() const {
    cout << endl << Interface::BLUE_FG;
    cout << "Move pieces by typing their coordinates." << endl;
    cout << "Example: a1 b2" << endl << endl;
    cout << "Commands:" << endl;
    cout << "  quit: quit the game" << endl;
    cout << "  info: show additional game info" << endl;
    cout << "  restart: go back to main menu" << endl;
    cout << "  save [file name]: save the game to file" << endl;
    cout << "  help: print this message" << endl;
    cout << Interface::DEFAULT_CLR << endl;
}

void GameInterface::showInfo() const {
    cout << endl << Interface::BLUE_FG;
    cout << "Game info:" << endl;
    cout << "  Castling: " << m_Game->castling() << endl;
    cout << "  Halfmove clock: " << m_Game->halfmoveClock() << endl;
    cout << "  Number of moves: " << m_Game->moves() << endl;
    cout << Interface::DEFAULT_CLR << endl;
}

void GameInterface::saveGame() const {
    string location;
    cin >> location;
    ofstream file;
    file.open(location);
    if (file.is_open()) {
        file << m_Game->fen();
        file.close();
        cout << Interface::BLUE_FG << "Game successfully saved to " << location << Interface::DEFAULT_CLR << endl << endl;
    }
    else {
        cout << Interface::RED_FG << "Invalid file name." << Interface::DEFAULT_CLR << endl << endl;
    }
}

bool GameInterface::readCommand(const string& input) {
    if (input == "help") printHelp();
    else if (input == "info") showInfo();
    else if (input == "save") saveGame();
    else return false;
    return true;
}