#include <string>

using namespace std;

/**
 * @brief Full chess program interface.
 *
 */
class Interface {
public:
    /**
     * @brief Default foreground and background color.
     *
     */
    static const string DEFAULT_CLR;

    /**
     * @brief Yellow background color.
     *
     */
    static const string YELLOW_BG;

    /**
     * @brief White background color.
     *
     */
    static const string WHITE_BG;

    /**
     * @brief Bright cyan background color.
     *
     */
    static const string BRIGHT_CYAN_BG;

    /**
     * @brief Cyan background color.
     *
     */
    static const string CYAN_BG;

    /**
     * @brief Yellow foreground color.
     *
     */
    static const string YELLOW_FG;

    /**
     * @brief Red foreground color.
     *
     */
    static const string RED_FG;

    /**
     * @brief Blue foreground color.
     *
     */
    static const string BLUE_FG;

    /**
     * @brief Clear the screen.
     *
     */
    static void clear();

    /**
     * @brief Run the program.
     *
     */
    void run();
};