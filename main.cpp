#include <iostream>
#include "CZufall.h"
#include <time.h>
#include "CLotto.h"
#include <fstream>

double monte_carlo(int r, int k, int n, int N, bool typ)
{
    CLotto lotto(k,n,-1);
    lotto.set_tippzettel(lotto.ziehung());
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

int main() {
   /* 
    CZufall::initialisiere(time(NULL));
    CZufall::test(3,7,10000);
    std::cout << std::endl;
    CZufall::initialisiere(time(NULL));
    CZufall::test(3,7,10000);
    std::cout << std::endl;
    CZufall::initialisiere(time(NULL));
    CZufall::test(3,7,10000);
    CZufall::test_falsch(3,7,10000);
    */
   std::cout << "Wahrscheinlichkeit fuer 2 Treffer bei 8-aus-33-Lotto\nSpieler 1: " << monte_carlo(2,8,33,1000000,false)*100 << "%\n" << "Spieler 2: " << monte_carlo(2,8,33,1000000,true)*100 << "%\n";

    std::cin.get();
    auto input = std::ifstream("/dev/random",std::ios_base::binary);
    int* result = new int[1000000000];
    input.read((char*) result, 4000000000);
    std::cout << "hi";
    return 0;

}