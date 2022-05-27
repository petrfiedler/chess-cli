
#include <iostream>

using namespace std;

/**
 * @brief Move coordinates.
 *
 */
class Move {
private:
    /**
     * @brief Y-coordinate of the move origin.
     */
    int m_FromY;

    /**
     * @brief X-coordinate of the move origin.
     */
    int m_FromX;

    /**
     * @brief Y-coordinate of the move destination.
     */
    int m_ToY;

    /**
     * @brief X-coordinate of the move destination.
     */
    int m_ToX;

public:
    /**
     * @brief Construct a new Move object.
     *
     */
    Move();

    /**
     * @brief Construct a new Move object.
     *
     * @param fromy y-coordinate of the move origin
     * @param fromx x-coordinate of the move origin
     * @param toy y-coordinate of the move destination
     * @param tox x-coordinate of the move destination
     */
    Move(int fromy, int fromx, int toy, int tox);

    /**
     * @brief Get coordinates of the move origin.
     *
     * @return move origin coordinates [y, x]
     */
    pair<int, int> from() const;

    /**
     * @brief Get coordinates of the move destination.
     *
     * @return move destination coordinates [y, x]
     */
    pair<int, int> to() const;

    /**
     * @brief Get move from black player's perspective.
     *
     * @return flipped move
     */
    Move flipped() const;

    /**
     * @brief Equality operator.
     *
     * @param rhs right hand side operand
     * @return true if both operands are equal
     */
    bool operator== (const Move& rhs) const;

    /**
     * @brief Hash functor.
     *
     */
    struct Hash {
        /**
         * @brief Hash function.
         *
         * @param move move to hash
         * @return hash
         */
        size_t operator()(const Move& move) const;
    };

    /**
     * @brief Print move to output stream.
     *
     * @param ost output stream
     * @param move move to print
     * @return output stream
     */
    friend ostream& operator<< (ostream& ost, const Move& move);
};