# include <iostream>
# include <unordered_map>

using namespace std;

int main(void)
{
    unordered_map<string, int> m;

    m["Hello"] = 10;
    m["World"] = 20;
    m["Hello"] = 102;
    for (auto x: m)
        cout << x.first << " " << x.second << endl ;
}