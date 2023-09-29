#include <bits/stdc++.h>

using namespace std;

vector<int> nums;
vector<pair<int, int>> numsWithWeight;
int countSubsetsSum(int pos, int sum)
{
    if (sum == 0)
    {
        return 1;
    }
    int subsetCount = 0;
    for (int i = pos; i < nums.size(); i++)
    {
        if (sum - nums[i] < 0)
            continue;
        int value = countSubsetsSum(i + 1, sum - nums[i]);
        if (value > 0)
        {
            subsetCount += value;
        }
    }
    return subsetCount;
}

int MaximumWeightSubsetsSum(int pos, int sum, int weight)
{
    if (sum == 0)
    {
        return weight;
    }
    int max = -999;
    for (int i = pos; i < numsWithWeight.size(); i++)
    {
        int tempSum = sum - numsWithWeight[i].first;
        if (tempSum < 0)
            continue;
        int calWgt = weight + numsWithWeight[i].second;
        int value = MaximumWeightSubsetsSum(i + 1, tempSum, calWgt);
        if (value > max)
        {
            max = value;
        }
    }
    return max;
}

int countSubsetsSumWithBug(int pos, int sum)
{
    if (sum == 0)
    {
        return 1;
    }
    int subsetCount = 0;
    for (int i = pos; i < nums.size(); i++)
    {
        if (sum - nums[i] < 0)
            continue;
        int value = countSubsetsSum(i + 1, sum - nums[i]);
        if (value > 0)
        {
            // this is a bug. because if it only counting once for all the solutions under the subtree
            subsetCount++;
        }
    }
    return subsetCount;
}

int main()
{
    int sum = 15;
    numsWithWeight = vector<pair<int, int>>{
        {8, 0},
        {6, 5},
        {7, 7},
        {5, 3},
        {3, 4},
        {10, 10},
        {9, 12}};
    sort(nums.begin(), nums.end());
    cout << MaximumWeightSubsetsSum(0, sum, 0) << endl;
    return 0;
}