#ifndef INTERFACE_9684
#define INTERFACE_9684
#include "Interface.h"
#endif
#ifndef MENU_INTERFACE_3545
#define MENU_INTERFACE_3545
#include "MenuInterface.h"
#endif

const string Interface::DEFAULT_CLR = "\033[39;49m";
const string Interface::YELLOW_BG = "\033[30;43m";
const string Interface::WHITE_BG = "\033[30;107m";
const string Interface::CYAN_BG = "\033[30;46m";
const string Interface::BRIGHT_CYAN_BG = "\033[30;106m";
const string Interface::YELLOW_FG = "\033[33;49m";
const string Interface::RED_FG = "\033[31;49m";
const string Interface::BLUE_FG = "\033[94;49m";

void Interface::clear() {
    cout << "\x1B[2J\x1B[H";
}

void Interface::run() {
    MenuInterface().showMenu();
}