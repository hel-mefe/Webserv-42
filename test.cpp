# include <iostream>
# include <vector>

using namespace std;

vector<vector<int> > *func2(vector<int> &r)
{
    vector<vector<int> > *k = new vector<vector<int> >();

    k->push_back(r);
    return k;
}
vector<vector<int> >* func1()
{
    vector<int> r;
    r.push_back(10);
    vector<vector<int> > *t = func2(r);
    return t;
}

int main(void)
{
    vector<vector<int> > *o = func1();
    cout << o->size() << " " << o->at(0)[0] << endl ;
}