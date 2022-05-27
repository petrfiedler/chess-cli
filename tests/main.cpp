#ifndef INTERFACE_9684
#define INTERFACE_9684
#include "../src/interface/MenuInterface.h"
#endif

#include <cassert>

/*
*   TESTS
*/
int main() {
    cout << "\033[91;49m" << endl;

    // test pawn moves
    GamePVP g1 = GamePVP();

    assert(g1.board()[6][1] == 1);
    assert(!g1.makeMove(Move(6, 1, 6, 1)));
    assert(!g1.makeMove(Move(6, 1, 7, 1)));
    assert(!g1.makeMove(Move(6, 1, 6, 0)));
    assert(!g1.makeMove(Move(6, 1, 6, 2)));
    assert(!g1.makeMove(Move(6, 1, 7, 0)));
    assert(!g1.makeMove(Move(6, 1, 7, 2)));
    assert(g1.makeMove(Move(6, 1, 5, 1)));

    g1.reset();
    assert(g1.board()[6][1] == 1);
    assert(!g1.makeMove(Move(6, 1, 3, 1)));
    assert(g1.makeMove(Move(6, 1, 4, 1)));

    assert(g1.board()[1][1] == -1);
    assert(!g1.makeMove(Move(1, 1, 1, 1)));
    assert(!g1.makeMove(Move(1, 1, 0, 1)));
    assert(!g1.makeMove(Move(1, 1, 1, 0)));
    assert(!g1.makeMove(Move(1, 1, 1, 2)));
    assert(!g1.makeMove(Move(1, 1, 0, 0)));
    assert(!g1.makeMove(Move(1, 1, 0, 2)));
    assert(g1.makeMove(Move(1, 1, 2, 1)));

    assert(g1.currentPlayer() == 1);

    // test en passant
    string enPassant = "rnbqkbnr/pp2pppp/8/1Ppp4/8/8/P1PPPPPP/RNBQKBNR w KQkq c6 0 3";
    GamePVP g2 = GamePVP();
    assert(g2.loadGame(enPassant));

    assert(g2.board()[6][1] == 0);
    assert(g2.board()[3][1] == 1);
    assert(g2.board()[1][2] == 0);
    assert(g2.board()[2][2] == 0);
    assert(g2.board()[3][2] == -1);
    assert(g2.makeMove(Move(3, 1, 2, 2)));
    assert(g2.board()[2][2] == 1);
    assert(g2.board()[3][2] == 0);

    // test rook moves
    string noPawns = "rnbqkbnr/8/8/8/8/8/8/RNBQKBNR w KQkq c6 0 1";
    GamePVP g3 = GamePVP();
    assert(g3.loadGame(noPawns));

    assert(g3.board()[7][0] == 2);
    assert(!g3.makeMove(Move(7, 0, 7, 0)));
    assert(!g3.makeMove(Move(7, 0, 7, 1)));
    assert(!g3.makeMove(Move(7, 0, 8, 1)));
    assert(g3.makeMove(Move(7, 0, 5, 0)));

    assert(!g3.currentPlayer());
    assert(g3.board()[0][0] == -2);
    assert(!g3.makeMove(Move(0, 0, 0, 0)));
    assert(!g3.makeMove(Move(0, 0, 0, 5)));
    assert(g3.makeMove(Move(0, 0, 4, 0)));

    assert(g3.currentPlayer());
    assert(g3.makeMove(Move(5, 0, 4, 0)));
    assert(g3.board()[4][0] == 2);

    assert(g3.makeMove(Move(0, 7, 7, 7)));

    assert(g3.makeMove(Move(4, 0, 4, 7)));

    assert(g3.fen() == "1nbqkbn1/8/8/8/7R/8/8/1NBQKBNr b - - 1 3");

    // test knight moves
    GamePVP g4 = GamePVP();

    assert(g4.board()[7][1] == 3);
    assert(!g4.makeMove(Move(7, 1, 7, 1)));
    assert(!g4.makeMove(Move(7, 1, 6, 1)));
    assert(!g4.makeMove(Move(7, 1, 6, 3)));
    assert(g4.makeMove(Move(7, 1, 5, 2)));

    assert(g4.board()[0][1] == -3);
    assert(!g4.makeMove(Move(0, 1, 1, 3)));
    assert(!g4.makeMove(Move(0, 1, 1, 1)));
    assert(!g4.makeMove(Move(0, 1, 0, 1)));
    assert(g4.makeMove(Move(0, 1, 2, 2)));

    assert(g4.makeMove(Move(5, 2, 3, 3)));
    assert(g4.board()[3][3] == 3);

    assert(g4.makeMove(Move(2, 2, 4, 3)));
    assert(g4.board()[2][2] == 0);

    assert(g4.board()[1][4] == -1);
    assert(g4.makeMove(Move(3, 3, 1, 4)));
    assert(g4.board()[1][4] == 3);

    assert(g4.board()[6][2] == 1);
    assert(g4.makeMove(Move(4, 3, 6, 2)));
    assert(g4.board()[6][2] == -3);

    assert(!g4.makeMove(Move(1, 4, 2, 4)));

    // test bishop moves
    GamePVP g5 = GamePVP();
    assert(g5.loadGame(noPawns));

    assert(g5.board()[7][2] == 4);
    assert(!g5.makeMove(Move(7, 2, 7, 3)));
    assert(!g5.makeMove(Move(7, 2, 7, 1)));
    assert(!g5.makeMove(Move(7, 2, 6, 2)));
    assert(g5.makeMove(Move(7, 2, 2, 7)));

    assert(g5.makeMove(Move(0, 3, 6, 3)));
    assert(g5.board()[6][3] == -5);

    assert(!g5.makeMove(Move(2, 7, 7, 2)));

    // test queen moves
    GamePVP g6 = GamePVP();
    assert(g6.loadGame(noPawns));

    assert(g6.board()[7][3] == 5);
    assert(!g6.makeMove(Move(7, 3, 7, 3)));
    assert(!g6.makeMove(Move(7, 3, 7, 2)));
    assert(!g6.makeMove(Move(7, 3, 7, 4)));
    assert(g6.makeMove(Move(7, 3, 4, 0)));

    assert(g6.board()[0][3] == -5);
    assert(!g6.makeMove(Move(0, 3, 0, 3)));
    assert(!g6.makeMove(Move(0, 3, 0, 2)));
    assert(!g6.makeMove(Move(0, 3, 0, 5)));
    assert(!g6.makeMove(Move(0, 3, 0, 42)));
    assert(!g6.makeMove(Move(0, 3, 4, 4)));
    assert(g6.makeMove(Move(0, 3, 1, 3)));

    assert(g6.board()[0][0] == -2);
    assert(g6.makeMove(Move(4, 0, 0, 0)));
    assert(g6.board()[0][0] == 5);

    // test king moves
    GamePVP g7 = GamePVP();
    assert(g7.loadGame(noPawns));

    assert(g7.board()[7][4] == 6);
    assert(!g7.makeMove(Move(7, 4, 7, 3)));
    assert(!g7.makeMove(Move(7, 4, 7, 5)));
    assert(!g7.makeMove(Move(7, 4, 7, 4)));
    assert(g7.makeMove(Move(7, 4, 6, 5)));

    assert(g7.board()[0][4] == -6);
    assert(!g7.makeMove(Move(0, 4, 0, 4)));
    assert(!g7.makeMove(Move(0, 4, 2, 4)));
    assert(g7.makeMove(Move(0, 4, 1, 4)));

    assert(g7.makeMove(Move(6, 5, 7, 4)));

    assert(g7.makeMove(Move(0, 3, 6, 3)));
    assert(g7.board()[6][3] == -5);
    assert(g7.state() == 1);
    assert(g7.makeMove(Move(7, 4, 6, 3)));
    assert(g7.state() == 0);

    // test castling
    GamePVP g8 = GamePVP();
    string castling = "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 42";

    assert(g8.loadGame(castling));
    assert(g8.castling() == "KQkq");

    assert(g8.board()[7][7] == 2);
    assert(g8.makeMove(Move(7, 4, 7, 6)));
    assert(g8.board()[7][4] == 0);
    assert(g8.board()[7][6] == 6);
    assert(g8.board()[7][5] == 2);
    assert(g8.board()[7][7] == 0);
    assert(g8.castling() == "kq");

    assert(g8.board()[0][0] == -2);
    assert(g8.board()[0][4] == -6);
    assert(g8.makeMove(Move(0, 4, 0, 2)));
    assert(g8.board()[0][4] == 0);
    assert(g8.board()[0][0] == 0);
    assert(g8.board()[0][2] == -6);
    assert(g8.board()[0][3] == -2);
    assert(g8.castling() == "-");

    // test promotion
    GamePVP g9 = GamePVP();
    string promotion = "3R4/p1p2k1P/5n2/5Qp1/3r4/2P5/b4bP1/5R1K w - - 1 40";

    assert(g9.loadGame(promotion));

    assert(g9.board()[1][7] == 1);
    assert(!g9.isPromotion());
    assert(g9.makeMove(Move(1, 7, 0, 7)));
    assert(g9.isPromotion());
    assert(g9.board()[0][7] == 1);
    assert(g9.promote(5));
    assert(g9.board()[0][7] == 5);
    assert(!g9.isPromotion());

    // test check
    GamePVP g10 = GamePVP();
    assert(g10.loadGame(noPawns));

    assert(g10.state() == 0);
    assert(g10.makeMove(Move(7, 3, 6, 4)));
    assert(g10.state() == 1);

    assert(!g10.makeMove(Move(0, 4, 1, 4)));
    assert(!g10.makeMove(Move(0, 0, 1, 0)));
    assert(g10.makeMove(Move(0, 4, 1, 5)));
    assert(g10.state() == 0);

    // test checkmate
    GamePVP g11 = GamePVP();
    string pawnToCheckmate = "1nbB3k/r2pN2p/5PP1/2p5/2P1P3/P7/P7/RN2K3 w Q - 1 40";
    assert(g11.loadGame(pawnToCheckmate));

    assert(g11.halfmoveClock() == 1);

    assert(g11.state() == 0);
    assert(g11.makeMove(Move(2, 6, 1, 6)));
    assert(g11.state() == 2);

    GamePVP g12 = GamePVP();
    string rookToCheckmate = "3R4/p1p2kp1/5n2/5Q2/8/1bP5/5bPP/r4R1K b - - 0 35";
    assert(g12.loadGame(rookToCheckmate));

    assert(g12.moves() == 35);

    assert(g12.state() == 0);
    assert(g12.makeMove(Move(7, 0, 7, 5)));
    assert(g12.state() == 3);

    // test stalemate
    GamePVP g13 = GamePVP();
    string knightToStalemate = "1k6/8/2BN1PP1/2B5/2P5/2N5/4P3/6KR w - - 5 36";
    assert(g13.loadGame(knightToStalemate));

    assert(g13.state() == 0);
    assert(g13.makeMove(Move(5, 2, 3, 1)));
    assert(g13.state() == 4);

    assert(g13.lastMove() == Move(5, 2, 3, 1));

    // test game loading
    GamePVP g14 = GamePVP();
    assert(!g14.loadGame(""));
    assert(!g14.loadGame("8/8/8/8/8/8/8/8 w - - 0 1"));
    assert(g14.loadGame("K7/8/8/8/8/8/8/7k w - - 0 1"));
    assert(!g14.loadGame("K7/8/8/8/8/8/7k w - - 0 1"));
    assert(!g14.loadGame("K7/8/8/8/8/8/8/7k w - 0 1"));
    assert(!g14.loadGame("K7/8/8/8/8/8/8/7k w Q 0 1"));
    assert(!g14.loadGame("K7/8/8/8/8/8/8/7k w QQ - 0 1"));
    assert(!g14.loadGame("K7/8/8/8/8/8/8/7k w - - 101 1"));
    assert(!g14.loadGame("K7/8/8/8/8/8/8/7k w - - 0"));

    // test game reset
    GamePVP g15 = GamePVP();
    assert(g15.loadGame(g13.fen()));

    assert(g15.state() == 4);
    g15.reset();
    assert(g15.state() == 0);
    assert(g15.fen() == GamePVP().fen());

    // test Move
    Move m1 = Move(1, 2, 3, 4);
    assert(m1.from() == make_pair(1, 2));
    assert(m1.to() == make_pair(3, 4));

    assert(m1.flipped() == Move(6, 2, 4, 4));

    // all tests passed
    cout << "\033[92;49m" << "All tests passed. :--)" << endl;
    return 0;
}