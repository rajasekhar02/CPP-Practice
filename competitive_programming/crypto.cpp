#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    char vowels[6] = {'e', 'i', 'y', 'a', 'o', 'u'};
    map<char, int> vowelsMap = {
        {'e', 0},
        {'i', 1},
        {'y', 2},
        {'a', 3},
        {'o', 4},
        {'u', 5}};
    char consonants[20] = {'p', 'k', 'x', 'z', 'n', 'j', 'd', 'c', 'w', 'g', 'b', 'v', 'h', 'q', 't', 's', 'r', 'l', 'm', 'f'};
    map<char, int> consonantsMap = {
        {'p', 0},
        {'k', 1},
        {'x', 2},
        {'z', 3},
        {'n', 4},
        {'j', 5},
        {'d', 6},
        {'c', 7},
        {'w', 8},
        {'g', 9},
        {'b', 10},
        {'v', 11},
        {'h', 12},
        {'q', 13},
        {'t', 14},
        {'s', 15},
        {'r', 16},
        {'l', 17},
        {'m', 18},
        {'f', 19}};
    cin >> t;
    cin.ignore();
    while (t--)
    {
        string str;
        getline(cin, str);
        string outStr = str;
        for (int i = 0; i < str.size(); i++)
        {
            if (vowelsMap.find(tolower(str[i])) != vowelsMap.end())
            {
                outStr[i] = (str[i] > 64 && str[i] < 90) ? toupper(vowels[(vowelsMap.at(tolower(str[i])) + 3) % 6]) : vowels[(vowelsMap.at(tolower(str[i])) + 3) % 6];
            }
            else if (consonantsMap.find(tolower(str[i])) != consonantsMap.end())
            {
                outStr[i] = (str[i] > 64 && str[i] < 90) ? toupper(consonants[(consonantsMap.at(tolower(str[i])) + 10) % 20]) : consonants[(consonantsMap.at(tolower(str[i])) + 10) % 20];
            }
            else
            {
                outStr[i] = str[i];
            }
        }
        cout << outStr << endl;
    }
    // cout << "bye" << endl;
    return 0;
}