    #include <time.h>
    #include <stdlib.h>
    #include <iostream>
    #include "CZufall.h"
    #include <vector>

    int CZufall::wert(int a, int b)
    {
        return (rand() % (b - a + 1)) + a;
    }

    void CZufall::initialisiere(int s)
    {
        srand(s);
    }

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

