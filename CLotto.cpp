// CLotto.cpp
// Implementation of the CLotto class declared in CLotto.h
// Provides simple lottery drawing operations using the CZufall
// random number helper.

#include "CLotto.h"
#include <vector>
#include "CZufall.h"
#include <time.h>

// Constructor: reserve space for the ticket and initialize RNG.
CLotto::CLotto(int k, int n, int s) : tippzettel(std::vector<int>(k)), k(k), n(n)
{
    // if caller supplied a negative seed, use current time
    if(s < 0)
    {
        CZufall::initialisiere(time(NULL));
    }
    else
    {
        CZufall::initialisiere(s);
    }
}

// Store a new ticket vector; caller should supply exactly k values.
void CLotto::set_tippzettel(std::vector<int> tippzettel)
{
    this->tippzettel = tippzettel;
}

// Perform a random drawing of k unique numbers in [1..n].
// Repeats a draw if a duplicate is generated to ensure uniqueness.
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
            // duplicate found - try again for this position
            i--;
            schon_gezogen = false;
        }
        else
            ziehung[i] = zahl;
    }
    return ziehung;
}

// Draw a set of numbers and compare them with the stored ticket,
// returning the count of matches.
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

