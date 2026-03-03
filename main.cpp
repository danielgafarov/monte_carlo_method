#include <iostream>
#include "CZufall.h"      // random number utilities
#include <time.h>
#include "CLotto.h"       // lottery simulation class
#include <fstream>
#include <sstream>

/**
 * Perform a Monte Carlo experiment computing the empirical
 * probability of getting exactly `r` correct numbers in a lotto
 * draw.
 *
 * @param r number of matching numbers required
 * @param k how many numbers are drawn / length of the ticket
 * @param n upper bound of the number range (1..n)
 * @param N how many trials to run
 * @param typ if true, ticket is replaced with the last draw before
 *            comparing (simulating rolling draws)
 * @param zettel initial ticket values used for comparison
 * @return fraction of trials with exactly `r` matches
 */
double monte_carlo(int r, int k, int n, int N, bool typ, std::vector<int> zettel)
{
    CLotto lotto(k, n, -1);          // create with random seed
    lotto.set_tippzettel(zettel);     // set the starting ticket
    int treffer = 0;
    if (typ)
    {
        // rolling ticket: after each draw, use the drawn numbers as
        // the next ticket to compare.
        for (int i = 0; i < N; i++)
        {
            lotto.set_tippzettel(lotto.ziehung());
            if (lotto.ziehung_vergleich() == r)
                treffer++;
        }
    }
    else
    {
        // fixed ticket throughout all trials
        for (int i = 0; i < N; i++)
        {
            if (lotto.ziehung_vergleich() == r)
                treffer++;
        }
    }
    return double(treffer) / double(N);
}

int main(int argc, char *argv[])
{
    // default parameters: look for 3 matches in 6 of 49 with ticket 1..6
    int r = 3, k = 6, n = 49;
    std::string zettel = "1,2,3,4,5,6";
    // allow overrides via command line
    if (argc == 5)
    {
        r = std::stoi(argv[1]);
        k = std::stoi(argv[2]);
        n = std::stoi(argv[3]);
        zettel = argv[4];
    }
    // parse comma-separated ticket into integers
    std::vector<int> zettel_split = {};
    std::stringstream ss(zettel);
    for (int i; ss >> i;)
    {
        if (i < 1 || i > n)
        {
            std::cout << "Falsche Eingabe, bitte beachten sie, dass die Zahlen im Tippzettel nicht kleiner als 1 und nicht größer als \"Kugeln insgesamt\" sein dürfen.\n";
            return 0;
        }
        zettel_split.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }
    // validate logical relationships between parameters
    if (!(r <= k && k <= n && zettel_split.size() == k))
    {
        std::cout << "Falsche Eingabe, bitte beachten sie, dass \"Richtige\" nicht größer als \"Gezogene Kugeln\" sein darf und \"Gezogene Kugeln\" nicht größer als \"Kugeln insgesamt\" sein darf. Die Anzahl der getippten Zahlen sollte der Menge der gezogenen Kugeln entsprechen und einzelne Zahlen müssen mit Kommas getrennt werden.\n";
        return 0;
    }
    // run simulation with one million trials
    double result = monte_carlo(r, k, n, 1000000, false, zettel_split);
    std::cout << "Sie haben mit eine Million simulierten Versuchen " << result * 1000000 << "-mal " << r << " Richtige gehabt.\n"
              << "Wahrscheinlichkeit für " << r << " Richtige bei " << k << "-aus-" << n << "-Lotto: " << result * 100 << "%\n"
              << "Für sehr unwahrscheinliche Ereignisse (z.B. 6 Richtige bei 6 aus 49) stimmt die Wahrscheinlichkeit nicht\n";
    return 0;
}