#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

std::ofstream fout;
std::ifstream fin;
int main()
{
    long long n;
    fin.open("input.txt");
    fin >> n;
    fin.close();
    fout.open("output.txt");
    std::vector<long long> powers;

    std::bitset<64> bitset(n);
    for (long long i = 0; i < bitset.size(); i++)
    {
        if (bitset[i] == 1)
        {
            powers.push_back(i);
        }
    }
    for (long long i = 0 ; i < powers.size(); i++)
    {
        fout << powers[i] << '\n';
    }

    fout.close();
    return 0;
}
