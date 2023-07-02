#include <iostream>
#include <fstream>
#include <vector>

std::ofstream fout;
std::ifstream fin;

int main()
{
    long long n;
    fin.open("input.txt");
    fin >> n;
    std::vector<long long> numbers(n, 0);
    for (long long i = 0; i < n; i++)
    {
        fin >> numbers[i];
    }
    fin.close();
    fout.open("output.txt");

    if (n == 1)
    {
        fout << "Yes";
        return 0;
    }
    if (n == 2)
    {
        if (numbers[0] <= numbers[1])
        {
            fout << "Yes";
            return 0;
        }
        else
        {
            fout << "No";
            return 0;
        }
    }

    bool flag = false;

    for (long long i = 0; i < n; i++)
    {
        if ( (2 * i + 1 < n && numbers[i] > numbers[2*i + 1]) || 2 * i + 2 < n && (numbers[i] > numbers[2*i + 2]))
        {
            flag = true;
            break;
        }
    }

    if (flag)
    {
        fout << "No";
    }
    else
    {
        fout << "Yes";
    }

    return 0;
}
