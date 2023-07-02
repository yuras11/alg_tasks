#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

std::ifstream fin;
std::ofstream fout;

long long FindSum(const std::vector<long long> &numbers)
{
    long long sum = 0;
    for (long long i : numbers)
    {
        sum += i;
    }
    return sum;
}

int main()
{
    long long n;
    fin.open("huffman.in");
    fin >> n;
    std::vector<long long> numbers(n, 0);
    for (long long i = 0; i < n; i++)
    {
        fin >> numbers[i];
    }
    fin.close();
    fout.open("huffman.out");
    std::vector<long long> copy(n, 0);
    for (long long i = 0; i < n; i++)
    {
        copy[i] = numbers[i];
    }
    std::reverse(numbers.begin(), numbers.end());
    std::queue<long long> queue;
    long long sum = 0;
    long long firstValue = numbers.back();
    numbers.pop_back();
    long long secondValue = numbers.back();
    numbers.pop_back();
    long long value = firstValue + secondValue;
    queue.push(value);
    sum += value;
    while (!numbers.empty())
    {
        if (queue.front() >= numbers.back())
        {
            firstValue = numbers.back();
            numbers.pop_back();
            if (queue.front() >= numbers.back())
            {
                secondValue = numbers.back();
                numbers.pop_back();
            }
            else
            {
                secondValue = queue.front();
                queue.pop();
            }
        }
        else
        {
            firstValue = queue.front();
            queue.pop();
            if (!queue.empty() && queue.front() < numbers.back())
            {
                secondValue = queue.front();
                queue.pop();
            }
            else
            {
                secondValue = numbers.back();
                numbers.pop_back();
            }
        }
        value = firstValue + secondValue;
        queue.push(value);
        sum += value;
    }

    while (!queue.empty())
    {
        firstValue = queue.front();
        queue.pop();
        secondValue = 0;
        if (!queue.empty())
        {
            secondValue = queue.front();
            queue.pop();
            value = firstValue + secondValue;
            sum += value;
            queue.push(value);
        }
        else
        {
            sum += firstValue;
        }
    }

    fout << sum - FindSum(copy);

    fout.close();
    return 0;
}
