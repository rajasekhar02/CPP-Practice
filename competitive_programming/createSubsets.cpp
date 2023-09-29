#include <bits/stdc++.h>
using namespace std;

vector<int> nums;
vector<vector<int>> subsetsArr;

void findNoOfSubsetsAt1(int position)
{
    if (position == nums.size())
    {
        return;
    }
    findNoOfSubsetsAt1(position + 1);
    int size = subsetsArr.size();
    for (int subsetWithSize = 0; subsetWithSize < size; subsetWithSize++)
    {
        vector<int> new_subset(subsetsArr[subsetWithSize]);
        new_subset.push_back(nums[position]);
        subsetsArr.push_back(new_subset);
    }
}

void findNoOfSubsetsAt2(int position)
{
    if (position == nums.size())
    {
        return;
    }
    int size = subsetsArr.size();
    for (int subsetWithSize = 0; subsetWithSize < size; subsetWithSize++)
    {
        vector<int> new_subset(subsetsArr[subsetWithSize]);
        new_subset.push_back(nums[position]);
        subsetsArr.push_back(new_subset);
    }
    findNoOfSubsetsAt2(position + 1);
}

void findNoOfSubsetsAt3(int position, vector<vector<int>> &subsetsArr1)
{
    if (position == nums.size())
    {
        return;
    }
    int size = subsetsArr1.size();
    for (int subsetWithSize = 0; subsetWithSize < size; subsetWithSize++)
    {
        vector<int> new_subset(subsetsArr1[subsetWithSize]);
        new_subset.push_back(nums[position]);
        subsetsArr1.push_back(new_subset);
    }
    findNoOfSubsetsAt3(position + 1, subsetsArr1);
}

vector<vector<int>> findNoOfSubsetsAt(int position)
{
    if (position == nums.size())
    {
        return vector<vector<int>>{vector<int>{}};
    }
    vector<vector<int>> subsets = findNoOfSubsetsAt(position + 1);
    int size = subsets.size();
    for (int subsetWithSize = 0; subsetWithSize < size; subsetWithSize++)
    {
        vector<int> new_subset(subsets[subsetWithSize]);
        new_subset.push_back(nums[position]);
        subsets.push_back(new_subset);
    }
    return subsets;
}

void findNoOfSubsetsAt1WithBug(int position)
{
    if (position == nums.size())
    {
        return;
    }
    findNoOfSubsetsAt1WithBug(position + 1);
    // Due to bug in the for loop condition this function with produce a memory limit exceeded error
    // This bug is cleared in other methods
    for (int subsetWithSize = 0; subsetWithSize < subsetsArr.size(); subsetWithSize++)
    {
        vector<int> new_subset(subsetsArr[subsetWithSize]);
        new_subset.push_back(nums[position]);
        subsetsArr.push_back(new_subset);
    }
}