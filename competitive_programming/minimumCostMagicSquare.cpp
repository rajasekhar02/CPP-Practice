#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> nMagicSquare{{2, 7, 6}, {9, 5, 1}, {4, 3, 8}};

vector<vector<int>> notMagicSquare{{5, 3, 4}, {1, 5, 8}, {6, 4, 2}};

vector<vector<int>> notMagicSquare1{{4, 9, 2}, {3, 5, 7}, {8, 1, 5}};

vector<vector<int>> notMagicSquare2{{4, 8, 2}, {4, 5, 7}, {6, 1, 6}};

// int isMagicSquare(vector<vector<int>> magicSquare)
// {
//     vector<int> rows(magicSquare.size(), 0);
//     vector<int> columns(magicSquare[0].size(), 0);
//     int leftDiagonal = 0;
//     int rightDiagonal = 0;
//     for (int i = 0; i < rows.size(); i++)
//     {
//         for (int j = 0; j < columns.size(); j++)
//         {
//             rows[i] += magicSquare[i][j];
//             columns[j] += magicSquare[i][j];
//             if (abs(i - j) == (rows.size() - 1))
//             {
//                 rightDiagonal += magicSquare[i][j];
//             }
//             else if (i == 1 && j == 1)
//             {
//                 rightDiagonal += magicSquare[i][j];
//                 leftDiagonal += magicSquare[i][j];
//             }
//             else if (i == j)
//             {
//                 leftDiagonal += magicSquare[i][j];
//             }
//         }
//     }
//     cout << "left Diagonal: " << leftDiagonal << " " << rightDiagonal << endl;
//     if (leftDiagonal != rightDiagonal)
//     {
//         return false;
//     }
//     for (int i = 0; i < rows.size(); i++)
//     {
//         if ((i < (rows.size() - 1)) && rows[i] != rows[i + 1])
//             return false;
//         if ((i < (columns.size() - 1)) && columns[i] != columns[i + 1])
//             return false;

//         if (rows[i] != columns[i] || rows[i] != leftDiagonal)
//         {
//             return false;
//         }
//     }
//     return true;
// }

int isMagicSquare(vector<vector<int>> magicSquare)
{
    int m = magicSquare.size();
    int n = magicSquare[0].size();
    int sum1 = 0, sum2 = 0;
    // finding the sum of first diagonal
    for (int i = 0; i < n; i++)
        sum1 = sum1 + magicSquare[i][i];
    // finding the sum of seciond diagonal
    for (int i = 0; i < n; i++)
        sum2 = sum2 + magicSquare[i][n - 1 - i];

    // Checking, whether the sum of two diagonal is same or not
    if (sum1 != sum2)
        return 0;

    // finding the sum of each row
    for (int i = 0; i < n; i++)
    {

        int rowSum = 0;
        for (int j = 0; j < m; j++)
            rowSum = rowSum + magicSquare[i][j];

        // checking, whether eachh row sum is equal to diagonal sum or not
        if (rowSum != sum1)
            return 0;
    }

    // finding the sum of each column
    for (int i = 0; i < n; i++)
    {

        int columnSum = 0;
        for (int j = 0; j < n; j++)
            columnSum += magicSquare[j][i];

        // checking, whether each column sum is equal to diagonal sum or not
        if (columnSum != sum1)
            return 0;
    }

    return true;
}

int solveMagicSquare(vector<vector<int>> magicSquare, int posI, int posJ, int cost)
{
    if (isMagicSquare(magicSquare))
    {
        return cost;
    }
    // if (posJ >= magicSquare[0].size())
    // {
    //     return solveMagicSquare(magicSquare, posI + 1, 0, cost);
    // }
    // if (posI >= magicSquare.size())
    // {
    //     return 1e9;
    // }
    long long int minCost = 1e9;

    // for (int row = posI; row < magicSquare.size(); row++)
    // {
    //     for (int col = posJ; col < magicSquare.size(); col++)
    //     {
    for (int num = 1; num <= 9; num++)
    {
        // if (magicSquare[posI][posJ] == num)
        //     continue;
        vector<vector<int>> newMagicSquare(magicSquare);
        newMagicSquare[posI][posJ] = num;
        long long int costN = solveMagicSquare(newMagicSquare, posI, posJ + 1, cost + abs(magicSquare[posI][posJ] - num));
        if (minCost > costN)
        {
            minCost = costN;
        }
        cout << minCost << endl;
    }
    // cout << "asdf" << endl;
    //     }
    // }
    return minCost;
}

int solveMagicSquare2(vector<vector<int>> magicSquare, int row, int col, int cost)
{

    if (isMagicSquare(magicSquare))
    {
        for (int i = 0; i < magicSquare.size(); i++)
        {
            for (int j = 0; j < magicSquare[0].size(); j++)
            {
                cout << magicSquare[i][j] << " ";
            }
            cout << endl;
        }
        cout << "cost: " << cost << endl;
        return cost;
    }
    if (col == (magicSquare[0].size()))
    {
        // cout << row << " " << col << endl;
        return solveMagicSquare2(magicSquare, row + 1, 0, cost);
    }
    if (row == magicSquare.size())
    {
        return 1e4;
    }
    int minCost = 1e4;
    int cost = 0;
    int value = magicSquare[row][col];
    for (int i = value; i < (10 + value); i++)
    {
        vector<vector<int>> newMagicSquare(magicSquare);
        int newValue = i % 9;
        newMagicSquare[row][col] = newValue;
        int costN = solveMagicSquare2(newMagicSquare, row, col + 1, cost + abs(newValue - value));
        if (costN < minCost)
        {
            minCost = costN;
        }
    }
    return minCost;
}

int solveMagicSquare3(vector<vector<int>> magicSquare, int row, int col, int cost)
{

    if (isMagicSquare(magicSquare))
    {
        for (int i = 0; i < magicSquare.size(); i++)
        {
            for (int j = 0; j < magicSquare[0].size(); j++)
            {
                cout << magicSquare[i][j] << " ";
            }
            cout << endl;
        }
        return cost;
    }
    if (col == (magicSquare[0].size()))
    {
        // cout << row << " " << col << endl;
        return solveMagicSquare2(magicSquare, row + 1, 0, cost);
    }
    if (row == magicSquare.size())
    {
        return 1e9;
    }
    int minCost = 1e4;
    int value = magicSquare[row][col];
    for (int errorCorrection = 0; errorCorrection < 10; errorCorrection++)
    {

        int cost = solveMagicSquare2(magicSquare, row, col + 1, cost);
        vector<vector<int>> newMagicSquare(magicSquare);
        int newValue = (value + errorCorrection) % 9;
        newMagicSquare[row][col] = newValue;

        if (cost < minCost)
        {
            minCost = cost;
        }
    }
    return minCost;
}

int main()
{

    cout << "minimum cost " << solveMagicSquare2(notMagicSquare1, 0, 0, 0) << endl;

    return 0;
}