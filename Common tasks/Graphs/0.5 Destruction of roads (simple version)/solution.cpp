#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::ifstream fin;
std::ofstream fout;

class Self
{
public:
    std::vector<long long> size;
    std::vector<long long> parent;
};

class DSU
{
    long long amountOfElements;
    Self self;
public:
    DSU(long long n)
    {
        this->amountOfElements = n;
        for (int i = 0; i < n; i++)
        {
            this->self.size.push_back(1);
            this->self.parent.push_back(i + 1);
        }
    }

    long long FindSet(long long x)
    {
        if (x == self.parent[x - 1])
        {
            return x;
        }
        self.parent[x - 1] = FindSet(self.parent[x - 1]);
        return self.parent[x - 1];
    }

    long long Union(long long x, long long y)
    {
        x = FindSet(x);
        y = FindSet(y);
        if (x != y)
        {
            if (self.size[x - 1] < self.size[y - 1])
            {
                std::swap(x, y);
            }
            self.parent[y - 1] = x;
            self.size[x - 1] += self.size[y - 1];
            amountOfElements--;
        }
        return amountOfElements;
    }

    long long GetAmountOfElements()
    {
        return this->amountOfElements;
    }

};

int main()
{
    fin.open("input.txt");
    long long n, m, q;
    std::string str;
    fin >> n >> m >> q;
    std::vector<long long> firstVertexes(m, 0), secondVertexes(m, 0);
    std::vector<bool> destroyed(m, false);
    for (long long i = 0; i < m; i++)
    {
        fin >> firstVertexes[i] >> secondVertexes[i];
    }
    std::vector<long long> roads(q, 0);
    for (long long i = 0; i < q; i++)
    {
        fin >> roads[i];
    }
    fin.close();
    fout.open("output.txt");
    DSU dsu(n);

    for (long long i = 0; i < q; i++)
    {
        destroyed[roads[i] - 1] = true;
    }

    for (long long i = 0; i < m; i++)
    {
        if (!destroyed[i])
        {
            dsu.Union(firstVertexes[i], secondVertexes[i]);
        }
    }
    if (dsu.GetAmountOfElements() != 1)
    {
        str += "0";
    }
    else
    {
        for (long long i = 0; i < q; i++)
        {
            fout << 1;
        }
        return 0;
    }
    for (long long i = q - 1; i >= 0; i--)
    {
        if (i == 0 && str.size() == q)
        {
            break;
        }
        long long value = dsu.Union(firstVertexes[roads[i] - 1], secondVertexes[roads[i] - 1]);
        if (value != 1)
        {
            str += "0";
        }
        else
        {
            str += "1";
        }
    }

    std::reverse(str.begin(), str.end());
    fout << str;
    fout.close();
    return 0;
}
