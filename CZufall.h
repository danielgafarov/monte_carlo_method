/**
 * @file CZufall.h
 * @brief Simple wrapper around C's rand()/srand() with basic
 *        utilities for testing distribution.
 *
 * All methods are static since the class merely provides a namespace
 * for the functions.  The class is used by CLotto to generate random
 * values.
 */

class CZufall
{
    public:
    /**
     * Produce a random integer in the closed interval [a, b].
     * @param a lower bound of the random number range (inclusive)
     * @param b upper bound of the random number range (inclusive)
     * @return uniformly distributed random number between a and b.
     */
    static int wert(int a, int b);

    /**
     * Seed the pseudo‑random number generator.  Typical usage is to provide
     * either a fixed seed for reproducible behavior or `time(NULL)` for
     * varying sequences.
     * @param s the seed value; if negative, `time(NULL)` is used instead.
     */
    static void initialisiere(int s);

    /**
     * Fill `n` random draws from [a, b] and print a simple frequency table.
     * Useful for checking whether `wert` appears uniform over many trials.
     * @param a lower bound of the random number range (inclusive)
     * @param b upper bound of the random number range (inclusive)
     * @param n number of random draws to perform for the test
     */
    static void test(int a, int b, int n);

    /**
     * A deliberately incorrect test that re‑seeds the generator inside the
     * loop.  Included for demonstration of poor seeding practice.
     */
    static void test_falsch(int a, int b, int n);
};