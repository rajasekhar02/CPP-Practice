#include <bits/stdc++.h>
using namespace std;

vector<int> nums;
vector<vector<int>> subsetsArr;
map<int, set<int>> numToSubsetLens;

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
        if (numToSubsetLens[nums[position]].find(subsetWithSize) != numToSubsetLens[nums[position]].end())
        {
            continue;
        }
        vector<int> new_subset(subsetsArr[subsetWithSize]);
        new_subset.push_back(nums[position]);
        subsetsArr.push_back(new_subset);
        numToSubsetLens[nums[position]].insert(subsetWithSize);
    }
}
vector<vector<int>> subsetsWithDup(vector<int> &numsArr)
{
    sort(numsArr.begin(), numsArr.end());
    nums = numsArr;
    subsetsArr.push_back(vector<int>{});
    findNoOfSubsetsAt1(0);
    return subsetsArr;
}
vector<vector<int>> subsetsWithDupWithBug(vector<int> &numsArr)
{
    // without sorting the arr will result in duplicate subsets
    nums = numsArr;
    subsetsArr.push_back(vector<int>{});
    findNoOfSubsetsAt1(0);
    return subsetsArr;
}
