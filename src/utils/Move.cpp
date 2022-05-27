#ifndef MOVE_9545
#define MOVE_9545
#include "../utils/Move.h"
#endif

Move::Move() {
    m_FromY = -1;
    m_FromX = -1;
    m_ToY = -1;
    m_ToX = -1;
}

Move::Move(int fromy, int fromx, int toy, int tox) :
    m_FromY(fromy), m_FromX(fromx), m_ToY(toy), m_ToX(tox) {
}

pair<int, int> Move::from() const {
    return make_pair(m_FromY, m_FromX);
}

pair<int, int> Move::to() const {
    return make_pair(m_ToY, m_ToX);
}

Move Move::flipped() const {
    return Move(7 - m_FromY, m_FromX, 7 - m_ToY, m_ToX);
}

ostream& operator<<(ostream& ost, const Move& move) {
    ost << static_cast<char>(move.m_FromX + 'a');
    ost << (8 - move.m_FromY);
    ost << " -> ";
    ost << static_cast<char>(move.m_ToX + 'a');
    ost << (8 - move.m_ToY);

    return ost;
}

bool Move::operator==(const Move& rhs) const {
    return m_FromY == rhs.m_FromY
        && m_FromX == rhs.m_FromX
        && m_ToY == rhs.m_ToY
        && m_ToX == rhs.m_ToX;
}


size_t Move::Hash::operator()(const Move& move) const {
    return move.m_FromY * 1000 + move.m_FromX * 100 + move.m_ToY * 10 + move.m_ToX;
}