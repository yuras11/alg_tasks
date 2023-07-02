#include <iostream>
#include <fstream>
#include <vector>

std::ifstream fin;
std::ofstream fout;

int main()
{
    fin.open("input.txt");
    long long n;
    fin >> n;
    std::string firstString, secondString, current;
    fin >> firstString >> secondString;
    fin.close();
    fout.open("output.txt");

    std::vector<long long> P(3*n + 1, 0);
    current = secondString + "$" + firstString + firstString;

    for(long long i = 1; i < current.size(); i++)
    {
        long long k = P[i-1];
        while (k > 0 && current[i] != current[k])
        {
            k = P[k-1];
        }
        if (current[i] == current[k])
        {
            P[i] = k + 1;
        }
        else
        {
            P[i] = k;
        }
    }

    long long index = LONG_LONG_MIN;
    for (long long i = n+1; i < current.size(); i++)
    {
        if (P[i] == n)
        {
            index = i;
            break;
        }
    }
    if (index != LONG_LONG_MIN)
    {
        fout << index - 2*n;
    }
    else
    {
        fout << "-1";
    }


    fout.close();

    return 0;
}
