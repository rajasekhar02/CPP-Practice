#include <bits/stdc++.h>
using namespace std;
vector<int> nums;
vector<vector<int>> bestLen;
vector<int> bestLen1d;
int solveLISBug(int position, int prev_big_num_idx)
{

    if (position >= nums.size())
    {
        // this last index value is zero because the counting is starting from the last position
        return 0;
    }

    if (nums[position] > nums[prev_big_num_idx])
    {
        return 1 + solveLISBug(position + 1, prev_big_num_idx);
    }

    int len_if_this_position_neglected = solveLISBug(position + 1, prev_big_num_idx);

    int len_if_seq_start_from_this_position = solveLISBug(position + 1, position);

    return max(len_if_this_position_neglected, len_if_seq_start_from_this_position);
}

int solveLISBug1(int position, int prev_big_num_idx, int length)
{

    if (position >= nums.size())
    {
        // this last index value is zero because the counting is starting from the last position
        return length;
    }

    if (nums[position] > nums[prev_big_num_idx])
    {
        return solveLISBug1(position + 1, prev_big_num_idx, length + 1);
    }

    int len_if_this_position_neglected = solveLISBug1(position + 1, prev_big_num_idx, length);

    int len_if_seq_start_from_this_position = solveLISBug1(position + 1, position, 0);
    cout << len_if_this_position_neglected << " " << len_if_seq_start_from_this_position << endl;

    return max(len_if_this_position_neglected, len_if_seq_start_from_this_position);
}

int solveLISRec(int position, int prev_big_num_idx, int length)
{

    if (position >= nums.size())
    {
        // this last index value is zero because the counting is starting from the last position
        return length;
    }
    if (nums[prev_big_num_idx] >= nums[position])
    {
        return solveLISRec(position + 1, prev_big_num_idx, length);
    }

    int len_if_this_position_neglected = solveLISRec(position + 1, prev_big_num_idx, length);

    int len_if_seq_includes_this_position = solveLISRec(position + 1, position, length + 1);

    return max(len_if_this_position_neglected, len_if_seq_includes_this_position);
}

int solveLISDP(int position, int prev_big_num_idx)
{
    if (position >= nums.size())
    {
        return 0;
    }
    if (bestLen[position][prev_big_num_idx] != -1)
    {
        return bestLen[position][prev_big_num_idx];
    }
    if (nums[prev_big_num_idx] >= nums[position])
    {
        return solveLISDP(position + 1, prev_big_num_idx);
    }

    int len_if_this_position_neglected = solveLISDP(position + 1, prev_big_num_idx);

    int len_if_seq_includes_this_position = 1 + solveLISDP(position + 1, position);

    bestLen[position][prev_big_num_idx] = max(len_if_this_position_neglected, len_if_seq_includes_this_position);

    return bestLen[position][prev_big_num_idx];
}

int solveLISDP2(int position, int prev_big_num_idx, int length)
{
    if (position >= nums.size())
    {
        return length;
    }
    if (bestLen[position][prev_big_num_idx] != -1)
    {
        return length + (bestLen[position][prev_big_num_idx] - 1);
    }
    if (nums[prev_big_num_idx] >= nums[position])
    {
        return solveLISDP2(position + 1, prev_big_num_idx, length);
    }
    // In this region prev_big_num_idx is less than the number at the current position
    int len_if_this_position_neglected = solveLISDP2(position + 1, prev_big_num_idx, length);

    int len_if_seq_includes_this_position = solveLISDP2(position + 1, position, length + 1);
    bestLen[position][prev_big_num_idx] = max(len_if_this_position_neglected, len_if_seq_includes_this_position);
    return bestLen[position][prev_big_num_idx];
}

int solveRecurnc2(int position)
{
    if (position >= nums.size())
    {
        return 0;
    }
    int maxLen = 0;
    for (int i = position + 1; i < nums.size(); i++)
    {
        if (nums[position] >= nums[i])
        {
            continue;
        }
        int valueRec = solveRecurnc2(i);
        maxLen = max(maxLen, 1 + valueRec);
    }
    return maxLen;
}
int solveRecurnc1(int position, int prev_big_num_idx)
{
    if (position >= nums.size())
    {
        return 0;
    }
    int maxLen = 0;
    for (int i = position; i < nums.size(); i++)
    {
        if (nums[prev_big_num_idx] >= nums[i])
        {
            continue;
        }
        int valueRec = solveRecurnc1(i + 1, i);
        maxLen = max(maxLen, 1 + valueRec);
    }
    return maxLen;
}
int solveDP3(int position, int prev_big_num_idx)
{
    if (position >= nums.size())
    {
        return 0;
    }
    int maxLen = 0;
    for (int i = position; i < nums.size(); i++)
    {
        if (nums[prev_big_num_idx] >= nums[i])
        {
            continue;
        }
        int valueRec = bestLen1d[i];

        if (valueRec == -1)
        {
            valueRec = 1 + solveDP3(i + 1, i);
        }
        maxLen = max(maxLen, valueRec);
        cout << i << " " << position << " " << maxLen << " " << bestLen1d[i] << endl;
        bestLen1d[i] = maxLen;
    }
    return maxLen;
}
int solveDP3_1(int position, int prev_big_num_idx)
{
    if (position >= nums.size())
    {
        return 0;
    }
    int maxLen = 0;
    for (int i = position; i < nums.size(); i++)
    {
        if (nums[prev_big_num_idx] >= nums[i])
        {
            continue;
        }
        int valueRec = bestLen[prev_big_num_idx][i];

        if (valueRec == -1)
        {
            valueRec = 1 + solveDP3_1(i + 1, i);
        }
        maxLen = max(maxLen, valueRec);
        // cout << i << " " << position << " " << maxLen << " " << bestLen[prev_big_num_idx][i] << endl;
        bestLen[prev_big_num_idx][i] = maxLen;
    }
    return maxLen;
}
int solvedp3_2(int position)
{
    // it has a state that return different length which is a bug
    if (position >= nums.size())
    {
        return 0;
    }
    int maxLen = 0;
    for (int i = position + 1; i < nums.size(); i++)
    {
        if (nums[position] >= nums[i])
        {
            continue;
        }
        int valueRec = bestLen1d[i];

        if (valueRec == -1)
        {
            valueRec = 1 + solvedp3_2(i);
        }
        maxLen = max(maxLen, valueRec);
        bestLen1d[i] = maxLen;
    }
    return maxLen;
}

int iter_dp_lis(){
    vector<int> arr = nums;
    for(int i=1;i<arr.size();i++){
        for(int j=0;j<i;j++){
            if(arr[i]<=arr[j]) continue;
            bestLen[i][j] = max( j-1 > 0 ? (bestLen[i-1][j-1]+1):1, bestLen[i-1][j]);
        }
    }
    return bestLen[arr.size()-1][arr.size()-2];
}

int main()
{
    // 3
    // 4
    // 1
    // 4
    // 3
    // 3
    vector<vector<int>> testcases = {
        vector<int>{4, 10, 4, 3, 8, 9},
        vector<int>{10, 9, 2, 5, 3, 7, 101, 18},
        vector<int>{7, 7, 7, 7, 7, 7, 7},
        vector<int>{0, 1, 0, 3, 2, 3},
        vector<int>{10, 9, 2, 5, 3, 4},
        vector<int>{18, 55, 66, 2, 3, 54}

    };
    for (int i = 0; i < testcases.size(); i++)
    {
        nums = vector<int>(testcases[i].size() + 1, -1e9);
        for (int j = 0; j < testcases[i].size(); j++)
        {
            nums[j + 1] = testcases[i][j];
        }
        bestLen = vector<vector<int>>(nums.size(), vector<int>(nums.size(), 0));
        // bestLen1d = vector<int>(nums.size(), -1);
        int value = iter_dp_lis();
        cout << "answer: " << value << endl;
    }
    return 0;
}