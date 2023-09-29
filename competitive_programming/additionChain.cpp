#include <bits/stdc++.h>
using namespace std;
int n;
int countA = 0;
int maxLen = 3;
bool additionChain(vector<int> chain, int len)
{
    if (chain[len - 1] == n)
    {
        for (int i = 0; i < chain.size(); i++)
        {
            cout << chain[i] << " ";
        }
        cout << endl;
        cout << (chain.size() - 1) << endl;
        countA++;
        return true;
    }
    for (int i = len - 1; i >= 0; i--)
    {
        for (int j = i; j >= 0; j--)
        {
            int tempSum = chain[i] + chain[j];
            if (tempSum > n || tempSum <= chain[len - 1] || (tempSum < n && len == maxLen))
                continue;
            vector<int> temp(chain);
            temp.push_back(tempSum);
            if (additionChain(temp, len + 1))
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    n = 374;

    while (1)
    {
        if (additionChain(vector<int>{1}, 1))
        {
            break;
        }
        maxLen++;
        cout << maxLen << endl;
    }
    cout << "happy ending" << endl;
    return 0;
}