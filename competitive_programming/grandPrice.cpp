#include <bits/stdc++.h>
using namespace std;

vector<string> split(string s, string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int c, r, v;
        cin >> c >> r >> v;
        cin.ignore();
        string str;
        map<string, int> votes;
        for (int i = 0; i < v; i++)
        {
            getline(cin, str);
            if (votes.find(str) == votes.end())
            {
                votes.insert({str, 1});
            }
            else
            {
                votes.at(str)++;
            }
        }
        map<string, int> mark;
        int maxSatisfies = 0;
        for (auto iter : votes)
        {
            if (mark.find(iter.first) != mark.end())
                continue;
            vector<string> vote = split(iter.first, " ");
            string reverse = vote[1] + " " + vote[0];
            if (votes.find(reverse) == votes.end())
            {
                maxSatisfies += iter.second;
            }
            else
            {
                maxSatisfies += max(iter.second, votes.at(reverse));
                mark[reverse] = 1;
            }

            mark[iter.first] = 1;
        }
        cout << maxSatisfies << endl;
    }
    return 0;
}