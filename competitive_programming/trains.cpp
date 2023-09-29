#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long int n;
        cin >> n;
        long long int mul = 1;
        vector<int> mark(10);
        int foundNumber = 0;
        while (1)
        {
            long long int newN = mul * n;
            long long int temp = newN;
            while (temp > 0)
            {
                int rem = temp % 10;
                mark[rem]++;
                temp /= 10;
                if (mark[rem] == 1)
                {
                    foundNumber++;
                }
            }
            if (foundNumber == 10)
            {
                break;
            }

            mul++;
        }
        cout << mul << endl;
    }
    return 0;
}