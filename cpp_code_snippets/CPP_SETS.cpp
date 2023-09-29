#include <bits/stdc++.h>
using namespace std;

int main()
{
    double elapsed_secs = 0;
    clock_t begin = clock();
    unordered_set<int> flat_un_ord_set;
    for (int i = 0; i < (1000 * 1000); i++)
    {
        flat_un_ord_set.insert(i);
    }
    int value = *flat_un_ord_set.find(12);
    clock_t end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "\tTIME:\t" << elapsed_secs << endl;
    // ------- end ------------//
    begin = clock();
    elapsed_secs = 0;
    set<int> flat_ord_set;
    for (int i = 0; i < (1000 * 1000); i++)
    {
        flat_ord_set.insert(i);
    }
    value = *flat_ord_set.find(12);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "\tTIME:\t" << elapsed_secs << endl;
    // ------- end ------------//
    return 0;
}