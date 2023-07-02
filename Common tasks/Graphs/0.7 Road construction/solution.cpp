#include <iostream>
#include <fstream>
#include <vector>

std::ifstream fin;
std::ofstream fout;

class Self
{
public:
    std::vector<int> size;
    std::vector<int> parent;
};

class DSU
{
    int amountOfElements;
    Self self;
public:
    DSU(int n)
    {
        this->amountOfElements = n;
        for (int i = 0; i < n; i++)
        {
            this->self.size.push_back(1);
            this->self.parent.push_back(i + 1);
        }
    }
    
    int FindSet(int x)
    {
        if (x == self.parent[x - 1])
        {
            return x;
        }
        self.parent[x - 1] = FindSet(self.parent[x - 1]);
        return self.parent[x - 1];
    }

    int Union(int x, int y)
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

};


int main()
{
    fin.open("input.txt");
    int n, q;
    fin >> n >> q;
    std::vector<long long> firstQueries(q, 0), secondQueries(q, 0);
    for (int i = 0; i < q; i++)
    {
        fin >> firstQueries[i] >> secondQueries[i];
    }
    fin.close();
    fout.open("output.txt");
    DSU dsu(n);
    for (int i = 0; i < q; i++)
    {
        fout << dsu.Union(firstQueries[i], secondQueries[i]) << '\n';
    }
    fout.close();
    return 0;
}
