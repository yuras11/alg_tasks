#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


int main()
{
    long long n = 0;
    std::vector<long long> sequence;
    long long element = 0;
    std::ifstream fin;
    std::ofstream fout;
    std::string inputPath = "input.txt";
    std::string outputPath = "output.txt";
    fin.open(inputPath);
    fin >> n;

    for (long long i = 0; i < n; i++)
    {
        fin >> element;
        sequence.push_back(element);
    }

    std::vector<long long> lis;
    lis.push_back(sequence[0]);

    for(long long i = 1; i < n; i++)
    {
        if (sequence[i] > lis[lis.size() - 1])
        {
            lis.push_back(sequence[i]);
        }
        else
        {
            long long index = std::upper_bound(lis.begin(), lis.end(), sequence[i]) - lis.begin();
            if (index != 0 && lis[index-1] < sequence[i])
            {
                lis[index] = sequence[i];
            }
            else if (index == 0)
            {
                lis[index] = std::min(lis[index], sequence[i]);
            }
        }
    }
    fin.close();
    fout.open(outputPath);
    fout << lis.size();
    fout.close();
    return 0;
}
