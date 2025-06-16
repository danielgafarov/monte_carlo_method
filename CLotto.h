#include <vector>

class CLotto
{
    private:
    std::vector<int> tippzettel;
    int k, n;
    public:
    CLotto(int k, int n, int s);
    void set_tippzettel(std::vector<int> tippzettel);
    std::vector<int> ziehung();
    int ziehung_vergleich();
};