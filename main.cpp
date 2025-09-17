#include <iostream>
#include "CZufall.h"
#include <time.h>
#include "CLotto.h"
#include <fstream>
#include <sstream>

double monte_carlo(int r, int k, int n, int N, bool typ, std::vector<int> zettel)
{
    CLotto lotto(k,n,-1);
    lotto.set_tippzettel(zettel);
    int treffer = 0;
    if(typ)
    {
        for(int i = 0; i < N; i++)
        {
            lotto.set_tippzettel(lotto.ziehung());
            if(lotto.ziehung_vergleich() == r)
                treffer++;
        }
    }
    else
    {
        for(int i = 0; i < N; i++)
        {
            if(lotto.ziehung_vergleich() == r)
                treffer++;
        }
    }
    return double(treffer)/double(N);
}

int main(int argc, char *argv[]) {
    int r = 3, k = 6,n = 49;
    std::string zettel = "1,2,3,4,5,6";
    if(argc == 5) {
        r = std::stoi(argv[1]);
        k = std::stoi(argv[2]);
        n = std::stoi(argv[3]);
        zettel = argv[4];
    }
    std::vector<int> zettel_split = {};
    std::stringstream ss(zettel);
    for (int i; ss >> i;) {
        zettel_split.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }
    if(!(r <= k && k <= n && zettel_split.size() == k)) {
        std::cout << "Falsche Eingabe, bitte beachten sie, dass \"Richtige\" nicht gröser als \"Gezogene Kugeln\" sein darf und \"Gezogene Kugeln\" nicht gröser als \"Kugeln insgesamt\" sein darf. Die Anzahl der getippten Zahlen sollte der Menge der gezogenen Kugeln entsprechen und einzelne Zahlen müssen mit Kommas getrennt werden.\n";
        return 0;
    }
    double result = monte_carlo(r,k,n,1000000,false,zettel_split);
    std::cout << "Sie haben mit eine Million simulierten Versuchen " << result * 1000000 << "-mal " << r << " Richtige gehabt.\n" 
    << "Wahrscheinlichkeit fuer " << r << " Richtige bei " << k << "-aus-" << n <<"-Lotto: " << result * 100 << "%\n"
    << "Für sehr unwahrscheinliche Ereignisse (z.B. 6 Richtige bei 6 aus 49) stimmt die Wahrscheinlichkeit nicht\n";
    return 0;
}