#include <bits/stdc++.h>
using namespace std;
int main()
{
    // read inputs
    int n, m;
    vector<string> solStr;
    int directions[8][2] = {
        {-1, -1},
        {-1, 0},
        {-1, 1},
        {0, -1},
        {0, 1},
        {1, -1},
        {1, 0},
        {1, 1}};

    while (1)
    {
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;
        cin.ignore();
        vector<string> grid;
        vector<string> outGrid;
        for (int i = 0; i < n; i++)
        {
            string str;
            getline(cin, str);
            grid.push_back(str);
            outGrid.push_back(str);
        }

        for (int xEle = 0; xEle < n; xEle++)
        {
            for (int yEle = 0; yEle < m; yEle++)
            {
                int countWater = 0;
                for (int eachDirection = 0; eachDirection < 8; eachDirection++)
                {
                    int newX = xEle + directions[eachDirection][0];
                    int newY = yEle + directions[eachDirection][1];
                    // cout << newX << " " << newY << " " << eachDirection << endl;
                    if (newX < 0 || newX >= n)
                        continue;
                    if (newY < 0 || newY >= m)
                        continue;
                    if (grid[newX][newY] == '*')
                    {
                        countWater++;
                    }
                }
                if (grid[xEle][yEle] != '*')
                {
                    outGrid[xEle][yEle] = (char)('0' + countWater);
                }
            }
            solStr.push_back(outGrid[xEle]);
        }
    }
    for (int i = 0; i < solStr.size(); i++)
    {
        cout << solStr[i] << endl;
    }
    return 0;
}