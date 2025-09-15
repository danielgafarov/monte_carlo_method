#include <iostream>
#include "CZufall.h"
#include <time.h>
#include "CLotto.h"
#include <fstream>

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
    int r = 6, k = 6,n = 49;
    std::string zettel = "123456";
    if(argc > 1) {
        r = std::stoi(argv[1]);
        k = std::stoi(argv[2]);
        n = std::stoi(argv[3]);
        zettel = argv[4];
    }
    std::vector<int> zettel_split = {};
    for (char& c : zettel){
        zettel_split.push_back(c - '0');
    }
    for(char i : zettel_split)
        std::cout << i;
    double result = monte_carlo(r,k,n,1000000,false,zettel_split);
    std::cout << "Sie haben mit eine Million simulierten Versuchen " << result * 1000000 << "-mal " << r << " Richtige gehabt.\n" 
    << "Wahrscheinlichkeit fuer " << r << " Richtige bei " << k << "-aus-" << n <<"-Lotto: " << result * 100 << "%\n"
    << "(Für sehr unwahrscheinliche Ereignisse (z.B. 6 Richtige bei 6 aus 49) stimmt die Wahrscheinlichkeit nicht)\n";
    return 0;
}