    // CZufall.cpp
// Concrete definitions for CZufall utility routines.
// Designed around the C standard library rand()/srand().

#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "CZufall.h"
#include <vector>

// Return a random integer between a and b inclusive.  Assumes a <= b.
int CZufall::wert(int a, int b)
{
    return (rand() % (b - a + 1)) + a;
}

// Initialize the random number generator with the given seed.
void CZufall::initialisiere(int s)
{
    srand(s);
}

// Run `n` draws and print frequencies.  Seeding must be done before
// calling this function in order to see predictable results.
void CZufall::test(int a, int b, int n)
{
    int size = b - a + 1;
    std::vector<int> anzahl(size);
    for(int i = 0; i < n; i++)
    {
        anzahl[wert(a,b) - a]++;
    }
    for(int i = 0;i < size;i++)
    {
        std::cout << a+i << ": " << anzahl[i] << std::endl;
    }
}

// Incorrect test demonstrating what happens if you reseed the RNG
// on every iteration.  The distribution typically collapses to a
// single value because time(NULL) rarely changes between calls.
void CZufall::test_falsch(int a, int b, int n)
{
    int size = b - a + 1;
    std::vector<int> anzahl(size);
    for(int i = 0; i < n; i++)
    {
        initialisiere(time(NULL));
        anzahl[wert(a,b) - a]++;
    }
    for(int i = 0;i < size;i++)
    {
        std::cout << a+i << ": " << anzahl[i] << std::endl;
    }
}

