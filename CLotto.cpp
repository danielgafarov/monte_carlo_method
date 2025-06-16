#include "CLotto.h"
#include <vector>
#include "CZufall.h"
#include <time.h>

CLotto::CLotto(int k, int n, int s) : tippzettel(std::vector<int>(k)), k(k), n(n)
{
    if(s < 0)
    {
        CZufall::initialisiere(time(NULL));
    }
    else
    {
        CZufall::initialisiere(s);
    }
}

void CLotto::set_tippzettel(std::vector<int> tippzettel)
{
    this->tippzettel = tippzettel;
}

std::vector<int> CLotto::ziehung()
{
    std::vector<int> ziehung(k,-1);
    bool schon_gezogen = false;
    int zahl;
    for(int i = 0; i < k; i++)
    {
        zahl = CZufall::wert(1,n);
        for(int j = 0;j < i;j++)
        {
            if(ziehung[j] == zahl)
            {
                schon_gezogen = true;
                break;
            }
        }
        if(schon_gezogen)
        {
            i--;
            schon_gezogen = false;
        }
        else
        ziehung[i] = zahl;
    }
    return ziehung;
}

int CLotto::ziehung_vergleich()
{
    std::vector<int> ergebnis = ziehung();
    int gleiche = 0;
    for(int i = 0; i < k; i++)
    {
        for(int j = 0; j < k; j++)
        {
            if(ergebnis[i] == tippzettel[j])
            {
                gleiche++;
                break;
            }
        }
    }
    return gleiche;
}

