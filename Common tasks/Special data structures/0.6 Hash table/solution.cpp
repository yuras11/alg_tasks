#include <iostream>
#include <fstream>
#include <vector>

std::ofstream fout;
std::ifstream fin;


int main()
{
    fin.open("input.txt");
    long long m, c, n;
    fin >> m >> c >> n;
    std::vector<long long> keys(n, 0);
    for (long long i = 0; i < n; i++)
    {
        fin >> keys[i];
    }
    fin.close();
    fout.open("output.txt");
    std::vector<long long> hashTable(m, -1);
    long long j;
    long long index;
    long long amountOfOccupiedCells = 0;
    bool isFound = false;

    for (long long i = 0; i < n; i++)
    {
        j = 0;
        while (j < m)
        {
            index = ((keys[i] % m) + c*j) % m;
            if (hashTable[index] == keys[i])
            {
                isFound = true;
                break;
            }
            if (hashTable[index] == -1)
            {
                isFound = false;
                break;
            }
            j++;
        }

        if (j == m - 1)
        {
            isFound = false;
        }

        j = 0;

        if (!isFound)
        {
            while (j < m)
            {
                index = ((keys[i] % m) + c*j) % m;
                if (hashTable[index] != -1)
                {
                    j++;
                }
                else
                {
                    hashTable[index] = keys[i];
                    amountOfOccupiedCells++;
                    break;
                }
            }
        }

    }

    for (long long k = 0; k < m; k++)
    {
        fout << hashTable[k] << ' ';
    }

    fout.close();

    return 0;
}
