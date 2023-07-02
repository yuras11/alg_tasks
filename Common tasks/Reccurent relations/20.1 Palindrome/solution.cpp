#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
    std::string str;
    std::ifstream fin;
    std::ofstream fout;
    std::string inputPath = "input.txt";
    std::string outputPath = "output.txt";
    fin.open(inputPath);
    if (fin.is_open())
    {
        fin >> str;
    }
    fin.close();
    fout.open(outputPath);
    if(str.empty())
    {
        fout << 0 << '\n';
        return 0;
    }

    size_t size = str.size();
    std::vector<std::vector<long long>> F(size,  std::vector<long long> (size,0));
    std::string palindrom;

    for (int i = 0; i < size-1; i++)
    {
        F[i][i] = 1;
        if (str[i] == str[i+1])
        {
            F[i][i+1] = 2;
        }
        else
        {
            F[i][i+1] = 1;
        }
    }
    F[size-1][size-1] = 1;

    for (long long j = 2; j < size; j++)
    {
        for (long long i = j-2; i >= 0; i--)
        {
            if (str[i] == str[j])
            {
                F[i][j] = F[i+1][j-1] + 2;
            }
            else
            {
                F[i][j] = std::max(F[i+1][j], F[i][j-1]);
            }
        }
    }

    if (F[0][size-1] == 1)
    {
        fout << 1 << '\n' << str[0];
        return 0;
    }

    fout << F[0][size-1] << '\n';

    long long i = 0, j = size-1;

    while (F[i][j] != 0)
    {
        if (F[i][j] > F[i][j-1] && F[i][j] > F[i+1][j])
        {
            palindrom += str[j];
            i++;
            j--;
        }
        else if (F[i][j] == F[i][j-1])
        {
            j--;
        }
        else
        {
            i++;
        }
    }

    std::string part = palindrom.substr(0, F[0][size-1] - palindrom.size());
    std::reverse(part.begin(), part.end());
    palindrom += part;

    fout << palindrom;
    fout.close();
    return 0;
}
