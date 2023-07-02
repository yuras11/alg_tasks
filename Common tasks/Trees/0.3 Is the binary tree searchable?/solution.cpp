#include <iostream>
#include <fstream>
#include <vector>

std::ifstream fin;
std::ofstream fout;

class Node
{
public:
    long long value;
    Node* right;
    Node* left;

    Node (long long value)
    {
        this->value = value;
        this->right = nullptr;
        this->left = nullptr;
    }
};

int main()
{
    fin.open("bst.in");
    fout.open("bst.out");
    long long n, m;
    fin >> n;
    if (n == 1)
    {
        fout << "YES";
        return 0;
    }
    fin >> m;
    std::vector<long long> M(n-1, 0), P(n-1, 0);
    std::vector<char> C(n-1, ' ');

    for (long long i = 0; i < n-1; i++)
    {
        fin >> M[i] >> P[i] >> C[i];
    }
    fin.close();
    Node* tree = new Node(m);
    std::vector<Node*> nodes(n);
    std::vector<std::pair<long long, long long>> borders(n);
    borders[0] = std::make_pair(LONG_LONG_MIN, LONG_LONG_MAX);
    nodes[0] = tree;
    bool flag = false;
    for (long long i = 0; i <= n-2; i++)
    {
        if (C[i] == 'L')
        {
            nodes[P[i]-1]->left = new Node(M[i]);
            nodes[i+1] = nodes[P[i]-1]->left;
            borders[i+1] = std::make_pair(borders[P[i]-1].first, nodes[P[i]-1]->value - 1);
        }
        else
        {
            nodes[P[i]-1]->right = new Node(M[i]);
            nodes[i+1] = nodes[P[i]-1]->right;
            borders[i+1] = std::make_pair(nodes[P[i]-1]->value, borders[P[i]-1].second);
        }
    }

    for(int i = 0; i < borders.size(); i++)
    {
        if(nodes[i]->value > borders[i].second || nodes[i]->value < borders[i].first)
        {
            flag = true;
            break;
        }
    }
    fout << (flag ? "NO" : "YES");
    fout.close();
    return 0;
}
