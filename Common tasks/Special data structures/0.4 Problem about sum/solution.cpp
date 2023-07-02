#include <iostream>
#include <vector>

void BuildTree(const std::vector<long long> &A, std::vector<long long> &treeOfSegments, long long index, long long left, long long right)
{
    if (right - left == 1)
    {
        treeOfSegments[index] = A[left];
    }
    else
    {
        long long m = (left + right) / 2;
        BuildTree(A, treeOfSegments, 2 * index, left, m);
        BuildTree(A, treeOfSegments, 2 * index + 1, m, right);
        treeOfSegments[index] = treeOfSegments[2 * index] + treeOfSegments[2 * index + 1];
    }
}

void Build(const std::vector<long long> &A, std::vector<long long> &treeOfSegments, long long n)
{
    BuildTree(A, treeOfSegments, 1, 0, n);
}

void DoAdd(std::vector<long long> &treeOfSegments, long long index, long long left, long long right, long long i, long long x)
{
    if (right - left == 1)
    {
        treeOfSegments[index] += x;
        return;
    }
    long long m = (left + right) / 2;
    if (i < m)
    {
        DoAdd(treeOfSegments, 2 * index, left, m, i, x);
    }
    else
    {
        DoAdd(treeOfSegments, 2 * index + 1, m, right, i, x);
    }
    treeOfSegments[index] = treeOfSegments[2 * index] + treeOfSegments[2 * index + 1];
}

void Add(std::vector<long long> &treeOfSegments, long long n, long long i, long long x)
{
    DoAdd(treeOfSegments, 1, 0, n, i, x);
}

long long FindSum(std::vector<long long> &treeOfSegments, long long index, long long left, long long right, long long l, long long r)
{
    if (l == left && r == right)
    {
        return treeOfSegments[index];
    }
    long long m = (left + right) / 2;
    if (r <= m)
    {
        return FindSum(treeOfSegments, 2 * index, left, m, l, r);
    }
    if (m <= l)
    {
        return FindSum(treeOfSegments, 2 * index + 1, m, right, l, r);
    }
    return FindSum(treeOfSegments, 2 * index, left, m, l, m) + FindSum(treeOfSegments, 2 * index + 1, m, right, m, r);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    long long n;
    std::cin >> n;
    std::vector<long long> A(n, 0);
    for (long long i = 0; i < n; i++)
    {
        std::cin >> A[i];
    }
    long long q;
    std::cin >> q;
    std::vector<std::string> queries(q, "");
    std::vector<long long> firstNumbers(q, 0), secondNumbers(q, 0);
    for (long long i = 0; i < q; i++)
    {
        std::cin >> queries[i] >> firstNumbers[i] >> secondNumbers[i];
    }
    std::vector<long long> treeOfSegments(4*n);
    Build(A, treeOfSegments, n);

    for (long long i = 0; i < q; i++)
    {
        if (queries[i] == "FindSum")
        {
            std::cout << FindSum(treeOfSegments, 1, 0, n, firstNumbers[i], secondNumbers[i]) << '\n';
        }
        else
        {
            Add(treeOfSegments, n, firstNumbers[i], secondNumbers[i]);
        }
    }

    return 0;
}
