#include <iostream>
#include <vector>

int LowerBound(const std::vector<long long> &array, long long element)
{
    int leftBorder = 0, rightBorder = array.size();
    while(leftBorder < rightBorder)
    {
        int center = (leftBorder + rightBorder) / 2;
        if (element <= array[center])
        {
            rightBorder = center;
        }
        else
        {
            leftBorder = center + 1;
        }
    }
    return leftBorder;
}

int UpperBound(const std::vector<long long> &array, long long element)
{
    int leftBorder = 0, rightBorder = array.size();
    while(leftBorder < rightBorder)
    {
        int center = (leftBorder + rightBorder) / 2;
        if (element < array[center])
        {
            rightBorder = center;
        }
        else
        {
            leftBorder = center + 1;
        }
    }
    return leftBorder;
}


int main()
{
    int n = 0, k = 0;
    std::cin >> n;
    std::vector<long long> array(n, 0);
    for (int i = 0; i < n; i++)
    {
        std::cin >> array[i];
    }
    std::cin >> k;
    std::vector<long long> numbers(k, 0);
    for (int i = 0; i < k; i++)
    {
        std::cin >> numbers[i];
    }
    std::vector<int> b(k, 0), l(k, n), r(k, n);
    int leftBound = 0, rightBound = array.size(), center = 0;

    for (int i = 0; i < k; i++)
    {
        l[i] = LowerBound(array, numbers[i]);
        r[i] = UpperBound(array, numbers[i]);
        leftBound = 0, rightBound = n, center = 0;
        while (leftBound < rightBound)
        {
            center = (leftBound + rightBound) / 2;
            if (numbers[i] == array[center])
            {
                b[i] = 1;
                break;
            }
            else if (numbers[i] < array[center])
            {
                rightBound = center;
            }
            else
            {
                leftBound = center + 1;
            }
        }
    }

    for (int i = 0; i < k; i++)
    {
        std::cout << b[i] << " " << l[i] << " " << r[i];
        std::cout << '\n';
    }
    return 0;
}
