#ifndef MENU_INTERFACE_3545
#define MENU_INTERFACE_3545
#include "MenuInterface.h"
#endif
#ifndef GAME_INTERFACE_9768
#define GAME_INTERFACE_9768
#include "GameInterface.h"
#endif

#include <iostream>
#include <fstream>

MenuInterface::MenuInterface() {
    m_GameTypes[0] = new GamePVP();
    for (int i = 1; i <= 3; i++) {
        m_GameTypes[i] = new GameAI(i);
    }
}

MenuInterface::~MenuInterface() {
    for (const auto& gameType : m_GameTypes) {
        delete gameType;
    }
}

void MenuInterface::showMenu() const {
    Interface::clear();
    cout << Interface::YELLOW_FG << "Welcome to Chess!" << Interface::DEFAULT_CLR << endl << endl;

    int gameType = selectGameType();
    cout << endl;
    string fen = loadGamePrompt();
    startGame(gameType, fen, gameType);
}

int MenuInterface::selectGameType() const {
    cout << Interface::BLUE_FG << "Game type:" << endl;
    cout << endl;
    cout << " 1: Player vs Player" << endl;
    cout << " 2: Player vs Computer" << endl;
    cout << Interface::DEFAULT_CLR << endl;
    string input;
    while (42) {
        cout << "Select game type [1/2]: ";
        cin >> input;
        if (!cin.fail() && (input == "1" || input == "2")) break;
        cout << Interface::RED_FG << "Invalid input." << Interface::DEFAULT_CLR << endl << endl;
    }

    if (input == "1") {
        return 0;
    }
    else {
        cout << endl;
        return selectDifficulty();
    }
}

int MenuInterface::selectDifficulty() const {
    cout << Interface::BLUE_FG << "Difficulty:" << endl;
    cout << endl;
    cout << " 1: Easy" << endl;
    cout << " 2: Medium" << endl;
    cout << " 3: Hard" << endl;
    cout << Interface::DEFAULT_CLR << endl;
    string input;
    while (42) {
        cout << "Select difficulty [1/2/3]: ";
        cin >> input;
        if (!cin.fail() && (input == "1" || input == "2" || input == "3")) break;
        cout << Interface::RED_FG << "Invalid input." << Interface::DEFAULT_CLR << endl << endl;
    }
    return stoi(input);
}

string MenuInterface::loadGamePrompt() const {
    string input;
    while (42) {
        cout << "Do you want to load the game from file? [y/n]: ";
        cin >> input;
        if (!cin.fail() && (input == "y" || input == "n")) break;
        cout << Interface::RED_FG << "Invalid input." << Interface::DEFAULT_CLR << endl << endl;
    }
    string fen = "";
    cout << endl;
    if (input == "y") {
        fen = loadGame();
    }
    return fen;
}

string MenuInterface::loadGame() const {
    cout << Interface::BLUE_FG << "If you don't want to load the game from file anymore, type '!cancel'.";
    cout << Interface::DEFAULT_CLR << endl << endl;
    string input;
    cin.ignore();
    while (42) {
        cout << "Enter file name: ";
        if (!getline(cin >> ws, input)) {
            cout << Interface::RED_FG << "Invalid input." << Interface::DEFAULT_CLR << endl << endl;
            continue;
        }
        if (input == "!cancel") return "";
        string fen = getFenFromFile(input);
        if (fen.length()) return fen;
        cout << Interface::RED_FG << "Invalid file." << Interface::DEFAULT_CLR << endl << endl;
    }
}

string MenuInterface::getFenFromFile(const string& filePath) const {
    ifstream file;
    file.open(filePath);
    if (!file || !file.good()) return "";
    string fen;
    if (!getline(file, fen)) return "";
    if (!Fen::checkValidFen(fen)) return "";
    return fen;
}

void MenuInterface::startGame(int type, const string& fen, bool isAI) const {
    Game* game = m_GameTypes[type];
    game->reset();
    if (!fen.empty()) game->loadGame(fen);
    if (GameInterface(game, isAI).play()) showMenu();
}