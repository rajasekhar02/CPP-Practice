#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> shops(n);
        for (int i = 0; i < n; i++)
        {
            cin >> shops[i];
        }
        sort(shops.begin(), shops.end());
        long long int min = 999999999;
        for (int i = 0; i < n; i++)
        {
            long long int sum = abs(shops[i] - shops[0]) * 2 + abs(shops[i] - shops[n - 1]) * 2;
            if (sum < min)
            {
                min = sum;
            }
        }
        cout << min << endl;
    }
    return 0;
}