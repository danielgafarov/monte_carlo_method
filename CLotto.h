/**
 * @file CLotto.h
 * @brief Lottery simulation class declaration.
 *
 * CLotto provides functionality for drawing `k` unique numbers
 * from the range [1..n] and comparing the result against a user
 * supplied ticket (`tippzettel`).  The class uses the CZufall
 * random number generator for reproducible experiments.
 */

#include <vector>

class CLotto
{
    private:
    /// user ticket containing exactly `k` chosen numbers
    std::vector<int> tippzettel;
    /// how many numbers are drawn / ticket size
    int k, n;
    public:
    /**
     * @param k number of values to draw and ticket length
     * @param n maximum possible value for each draw (inclusive)
     * @param s seed for the random number generator; if negative
     *          `time(NULL)` is used instead.
     */
    CLotto(int k, int n, int s);

    /**
     * Replace the stored ticket with a new vector of numbers.  The
     * caller is responsible for ensuring the vector has length `k`.
     * @param tippzettel vector of `k` integers representing the user's ticket
     */
    void set_tippzettel(std::vector<int> tippzettel);

    /**
     * Perform a random draw and return a vector of `k` unique numbers.
     */
    std::vector<int> ziehung();

    /**
     * Do a draw internally and count how many numbers match the
     * previously stored ticket.  Returns the number of equal entries.
     * @return the amount of matching numbers between the drawn set and the ticket
     */
    int ziehung_vergleich();
};