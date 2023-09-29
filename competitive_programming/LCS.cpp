#include <bits/stdc++.h>

using namespace std;

string strA;
string strB;

int solveLCS(int posA, int posB, int commonLen)
{
    if (posA == strA.size())
    {
        return commonLen;
    }

    if (posB == strB.size())
    {
        return commonLen;
    }

    if (strA[posA] == strB[posB])
    {
        return solveLCS(posA + 1, posB + 1, commonLen + 1);
    }

    return max(solveLCS(posA + 1, posB, commonLen), solveLCS(posA, posB + 1, commonLen));
}

int solveSCS(int posA, int posB, int superStrLen)
{
    if (posA == strA.size())
    {
        return (superStrLen + (strB.size() - posB));
    }

    if (posB == strB.size())
    {
        return (superStrLen + (strA.size() - posA));
    }

    if (strA[posA] == strB[posB])
    {
        return solveSCS(posA + 1, posB + 1, superStrLen + 1);
    }
    cout << posA << " " << posB << " " << superStrLen << endl;
    int value1 = solveSCS(posA + 1, posB, superStrLen + 1);
    int value2 = solveSCS(posA, posB + 1, superStrLen + 1);
    cout << value1 << " " << value2 << endl;
    return min(value1, value2);
}

int solveLBS(int pos, bool isIncreasing)
{
}

int main()
{
    strA = "adef";
    strB = "def";

    cout << solveSCS(0, 0, 0) << endl;
    return 0;
}