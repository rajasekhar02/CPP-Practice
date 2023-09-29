#include <bits/stdc++.h>
using namespace std;

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "[";
    for (int i = 0; i < v.size(); ++i)
    {
        os << " <" << v[i].first << " " << v[i].second << ">";
        if (i != v.size() - 1)
            os << ", ";
    }
    os << " ]\n";
    return os;
}

int main()
{
    int t; // number of test cases
    int n; // number of houses
    cin >> t;
    double carCenter, carLength;
    double start, end;
    double temp;
    while (t--)
    {
        cin >> n;
        vector<pair<double, int>> houseLine;
        vector<pair<double, double>> houseCentersAndCarLengths;
        double sumonPositionLeft = 0;
        double sumonPositionRight = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> carCenter >> carLength;
            temp = carLength / 2;
            start = carCenter - temp;
            end = carCenter + temp;
            if (i == 0)
            {
                sumonPositionLeft = start;
                sumonPositionRight = end;
            }
            houseCentersAndCarLengths.push_back(make_pair(carCenter, carLength));
            houseLine.push_back(make_pair(start, i));
            houseLine.push_back(make_pair(end, i));
        }
        sort(houseLine.begin(), houseLine.end(),
             [](const pair<double, double> &a, const pair<double, double> &b) -> bool
             {
                 if (a.first - b.first != 0)
                 {
                     return a.first < b.first;
                 }
                 return a.second > b.second;
             });

        vector<int> marked(n);
        vector<int> order(n);
        for (int i = 0; i < 2 * n; i++)
        {
            if (marked[houseLine[i].second] == 0)
            {
                order.push_back(houseLine[i].second);
                marked[houseLine[i].second]++;
            }
        }
        int sumonInOrder = 0;
        for (int i = 0; i < order.size(); i++)
        {
            if (order[i] == 0)
            {
                sumonInOrder = i;
            }
        }
        int countSatisfied = 0;
        double otherX = sumonPositionRight;
        double otherY = sumonPositionRight;
        for (int i = sumonInOrder + 1; i < order.size(); i++)
        {
            otherY = otherX + houseCentersAndCarLengths[order[i]].second;
            if (houseCentersAndCarLengths[order[i]].first >= otherX && houseCentersAndCarLengths[order[i]].first <= otherY)
            {
                countSatisfied++;
            }
            otherX = otherY;
        }
        // cout << countSatisfied << endl;
        otherX = sumonPositionLeft;
        otherY = sumonPositionLeft;
        // cout << otherY << endl;
        for (int i = sumonInOrder - 1; i >= 0; i--)
        {
            otherX = otherY - houseCentersAndCarLengths[order[i]].second;
            if (houseCentersAndCarLengths[order[i]].first >= otherX && houseCentersAndCarLengths[order[i]].first <= otherY)
            {
                countSatisfied++;
            }
            otherY = otherX;
        }
        cout << (countSatisfied + 1) << endl;
    }
    return 0;
}