#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <vector>
#include <set>
#include <utility>
#include <fstream>
#include <chrono>
#include <cassert>
using namespace std;
// auto const seed = 123;
auto const hes = std::random_device{}();
mt19937 urbg = mt19937{};

struct interval
{
    double leftValue;
    double rightValue;
    int index;
    interval()
    {
        this->leftValue = -1.0;
        this->rightValue = -1.0;
        this->index = -1;
    }
    interval(int index, double leftValue, double rightValue)
    {
        this->leftValue = leftValue;
        this->rightValue = rightValue;
        this->index = index;
    }
    char *getDotNodeFormat(const char *color = "black")
    {
        char *s;
        int stringLen = snprintf(NULL, 0, "struct%d [shape=record, color=%s, label=\"%f|I%d|%f\"];", this->index, color, this->leftValue, this->index, this->rightValue);
        s = (char *)malloc(sizeof(char) * stringLen + 1);
        snprintf(s, stringLen, "struct%d [shape=record, color=%s, label=\"%f|I%d|%f\"];", this->index, color, this->leftValue, this->index, this->rightValue);
        return s;
    }
    bool operator<(interval otherInterval) const
    {
        return this->rightValue < otherInterval.rightValue;
    }
};
ostream &operator<<(ostream &os, interval value)
{
    os << value.index << " " << value.leftValue << " " << value.rightValue << endl;
    return os;
}
vector<string> split(string s, char c)
{
    vector<string> res;
    string tempStr = "";
    for (int index = 0; index < s.length(); index++)
    {
        if (s[index] != c)
        {
            tempStr += s[index];
        }
        else
        {
            res.push_back(tempStr);
            tempStr = "";
        }
    }
    res.push_back(tempStr);
    return res;
}
vector<vector<int>> getAdjacencyListForGivenIntervals(vector<interval> intervals, bool undirectional)
{
    int totalLength = intervals.size();
    vector<vector<int>> adjacencyList(totalLength, vector<int>());
    for (int i = 0; i < totalLength; i++)
    {
        interval x = intervals[i];
        for (int j = i + 1; j < totalLength; j++)
        {
            interval y = intervals[j];
            if (y.leftValue > x.leftValue && y.leftValue > x.rightValue)
                continue;
            if (y.rightValue < x.leftValue && y.rightValue < x.rightValue)
                continue;
            adjacencyList[i].push_back(j);
            if (undirectional)
            {
                adjacencyList[j].push_back(i);
            }
        }
    }
    return adjacencyList;
}
void printAdjacencyList(vector<vector<int>> adjacencyList)
{
    for (int i = 0; i < adjacencyList.size(); i++)
    {
        printf("[%d]: ", i);
        for (int j = 0; j < adjacencyList[i].size(); j++)
        {
            cout << " -> " << adjacencyList[i][j];
        }
        cout << endl;
    }
}
void printDOTFormat(vector<interval> intervals, vector<vector<int>> adjacencyList, vector<int> maxIndependentSet, string fileName)
{
    string fileNameString = "./graphDot/" + fileName + ".dot";
    set<int> maxIndependentSetType(maxIndependentSet.begin(), maxIndependentSet.end());
    string colors[2] = {"black", "red"};
    ofstream fout(fileNameString);
    fout << "graph IntervalGraph {" << endl;
    for (int i = 0; i < intervals.size(); i++)
    {
        int nodeColorIndex = maxIndependentSetType.find(i) != maxIndependentSetType.end() ? 1 : 0;
        fout << intervals[i].getDotNodeFormat(colors[nodeColorIndex].c_str()) << endl;
    }
    for (int i = 0; i < intervals.size(); i++)
    {
        if (adjacencyList[i].size() == 0)
        {
            fout << " struct" << i << ";" << endl;
        }

        for (int j = 0; j < adjacencyList[i].size(); j++)
        {
            fout << " struct" << i << " -- "
                 << "struct" << adjacencyList[i][j] << ";" << endl;
        }
    }
    fout << "}" << endl;
    // a node has two values
    fout.close();
}
bool areTwoNodesAdjacent(int node1, int node2, vector<vector<int>> adjacencyList)
{
    vector<int> nodesAdjacent = adjacencyList[node1];
    return find(nodesAdjacent.begin(), nodesAdjacent.end(), node2) != nodesAdjacent.end();
}
vector<int> getMaximumIndependentSet(vector<interval> intervals, vector<vector<int>> adjacencyList)
{
    vector<int> maxIndependentSet;
    vector<int> markedIntervals(intervals.size());
    vector<pair<double, int>> rightIntervals;
    int count = 0;
    while (count != intervals.size())
    {
        rightIntervals = vector<pair<double, int>>();
        for (int i = 0; i < intervals.size(); i++)
        {
            if (markedIntervals[i] == 0)
            {
                rightIntervals.push_back(make_pair(intervals[i].rightValue, i));
            }
        }
        sort(rightIntervals.begin(), rightIntervals.end());
        if (rightIntervals.size() == 0)
        {
            cout << "1 set" << endl;
            break;
        }
        int index = rightIntervals[0].second;
        maxIndependentSet.push_back(index);
        vector<int> overlappingIntervals = adjacencyList[index];
        markedIntervals[index] = 1;
        for (int i = 0; i < overlappingIntervals.size(); i++)
        {
            markedIntervals[overlappingIntervals[i]] = 1;
        }
        count = 0;
        for (int i = 0; i < intervals.size(); i++)
        {
            if (markedIntervals[i] == 1)
            {
                cout << i << endl;
                count++;
            }
        }
    }
    // cout << intervals.size() << endl;
    // for (int i = 0; i < maxIndependentSet.size(); i++)
    // {
    //     cout << maxIndependentSet[i] << endl;
    // }
    return maxIndependentSet;
}
double getMaximumIndependentSetAlgo2(vector<interval> intervals, vector<interval> &maximumIndependenSet)
{
    int n = intervals.size();
    vector<pair<double, int>> linearIntervals(2 * n);
    for (int i = 0; i < n; i++)
    {
        linearIntervals[2 * i] = make_pair(intervals[i].leftValue, intervals[i].index);
        linearIntervals[2 * i + 1] = make_pair(intervals[i].rightValue, intervals[i].index);
    }
    sort(linearIntervals.begin(), linearIntervals.end());
    int mid1 = n / 2;
    int mid2 = mid1 + 1;
    double mid = (linearIntervals[mid1].first + linearIntervals[mid2].first) / 2;
    vector<interval> sLeft, sRight, sMid;
    for (int i = 0; i < n; i++)
    {
        if (intervals[i].rightValue < mid)
        {
            sLeft.push_back(intervals[i]);
            cout << intervals[i] << endl;
        }
        else if (intervals[i].leftValue > mid)
        {
            sRight.push_back(intervals[i]);
        }
        else
        {
            sMid.push_back(intervals[i]);
        }
    }
    cout << sLeft.size() << " " << sRight.size() << " " << sMid.size() << " " << endl;
    double rightMostPoint;
    vector<int> xAndMaximumIndependentSet;
    if (sLeft.size() > 0)
    {
        rightMostPoint = getMaximumIndependentSetAlgo2(sLeft, maximumIndependenSet);
        vector<int> midElementsToDelete;
        vector<interval> newSMid;
        for (int j = 0; j < sMid.size(); j++)
        {
            if (!(sMid[j].leftValue <= rightMostPoint && sMid[j].rightValue >= rightMostPoint))
            {
               newSMid.push_back(sMid[j]);
            }
        }
        sMid = vector<interval>(newSMid.begin(),newSMid.end());
    }
    interval leftMostRightIntervalInSMid;
    if (sMid.size() >= 1)
    {
        sort(sMid.begin(),sMid.end());
        leftMostRightIntervalInSMid = sMid[0];
    }
    if (sRight.size() == 0)
    {
        if (leftMostRightIntervalInSMid.index >= 0)
        {
            maximumIndependenSet.push_back(leftMostRightIntervalInSMid);
            rightMostPoint = leftMostRightIntervalInSMid.rightValue;
        }
    }
    else
    {
        vector<interval> sMidUnionSRight;
        if (leftMostRightIntervalInSMid.index >= 0)
        {
            sMidUnionSRight.push_back(leftMostRightIntervalInSMid);
        }
        sMidUnionSRight.insert(sMidUnionSRight.end(), sRight.begin(), sRight.end());
        rightMostPoint = getMaximumIndependentSetAlgo2(sMidUnionSRight, maximumIndependenSet);
    }
    return rightMostPoint;
}
void generateFileWithIntervals(int noOfIntervals)
{
    //**//
    int n = noOfIntervals;
    urbg.seed(hes);
    uniform_real_distribution<double> distr1{0, 1};
    double possibleValuesForT[4] = {(double)(1 / n), (double)(1 / sqrt(n)), (double)(1 / log(n)), 0.25f};
    vector<pair<double, int>> linearIntervals(2 * n);
    double tValue = possibleValuesForT[1] + 10e-10;
    uniform_real_distribution<double> tDirstr1{0, tValue};
    auto now = std::chrono::system_clock::now();
    auto now_sec = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
    char *now_sec_str = &std::to_string(now_sec.count())[0];
    //**//
    int fileNameSize = snprintf(NULL, 0, "Intervals-%d-%s.csv", noOfIntervals, now_sec_str);
    char filename[fileNameSize + 1]; // filename
    snprintf(filename, fileNameSize + 1, "Intervals-%d-%s.csv", noOfIntervals, now_sec_str);
    //**//
    ofstream fout(filename);
    for (int i = 0; i < n; i++)
    {
        double leftValue = distr1(urbg);
        double vi = tDirstr1(urbg);
        double rightValue = min(leftValue + vi, 1.0);
        fout << leftValue << "," << rightValue << endl;
        // fout<<leftValue<<","<<rightValue<< (i == n-1)? "":",";
    }
    fout.close();
}
void generateFileWithIntervals2(string fileName, int noOfIntervals)
{
    int n = noOfIntervals;
    urbg.seed(hes);
    uniform_real_distribution<double> distr1{0, 1};
    double possibleValuesForT[4] = {(double)(1 / n), (double)(1 / sqrt(n)), (double)(1 / log(n)), 0.25f};
    vector<pair<double, int>> linearIntervals(2 * n);
    double tValue = possibleValuesForT[1] + 10e-10;
    uniform_real_distribution<double> tDirstr1{0, tValue};
    ofstream fout("./data/" + fileName);
    for (int i = 0; i < n; i++)
    {
        double leftValue = distr1(urbg);
        double vi = tDirstr1(urbg);
        double rightValue = min(leftValue + vi, 1.0);
        fout << to_string(leftValue) + "," + to_string(rightValue) + (i == n - 1 ? "" : ",");
    }
    fout.close();
}
vector<interval> readIntervalsFromFile(string fileName, int n)
{
    ifstream fin(fileName);
    vector<interval> intervals;
    if (!fin.is_open())
        return intervals;
    string line;
    int count = 0;
    while (getline(fin, line) && count < n)
    {
        vector<string> intervalStr = split(line, ',');
        intervals.push_back(interval(count, stof(intervalStr[0]), stof(intervalStr[1])));
        count++;
    }
    fin.close();
    return intervals;
}
vector<interval> readIntervalsFromFile2(string fileName, int n)
{
    ifstream fin(fileName);
    vector<interval> intervals;
    if (!fin.is_open())
        return intervals;
    string line;
    int count = 0;
    getline(fin, line);
    vector<string> intervalStr = split(line, ',');
    for (int i = 0; i < n; i++)
    {
        intervals.push_back(interval(i, stof(intervalStr[(2 * i)]), stof(intervalStr[(2 * i + 1)])));
    }
    cout << intervals.size() << endl;
    fin.close();
    return intervals;
}
int main(int argc, char **argv)
{
    assert(!(argc < 3));
    int n = atoi((argv[1]));
    string fileName = string(argv[2]);
    generateFileWithIntervals2(fileName, n);
    vector<interval> intervalsV = readIntervalsFromFile2("./data/" + fileName, n);
    vector<vector<int>> adjacencyList1 = getAdjacencyListForGivenIntervals(intervalsV, true);
    vector<vector<int>> adjacencyList2 = getAdjacencyListForGivenIntervals(intervalsV, false);
    vector<int> maximumIndependentSet = getMaximumIndependentSet(intervalsV, adjacencyList1);
    // printAdjacencyList(adjacencyList1);
    printDOTFormat(intervalsV, adjacencyList2,maximumIndependentSet,fileName.substr(0,fileName.size()-4));
    // vector<vector<int>> adjacencyList2 = getAdjacencyListForGivenSortedIntervalParts(intervalsV, leftIntervals, rightIntervals);
    // printAdjacencyList(adjacencyList1);
    // cout << << endl;
    vector<interval> maximumIndependentIntervals;
    getMaximumIndependentSetAlgo2(intervalsV, maximumIndependentIntervals);
    cout<<maximumIndependentIntervals.size()<<endl;
    for(int i=0;i<maximumIndependentIntervals.size();i++){
        cout<<maximumIndependentIntervals[i]<<endl;
    }
    return 0;
}