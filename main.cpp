#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef vector<vector<int>> matrix;

matrix edges;   // #of vert -> [#neighbour, #neighbour, ...]
matrix res;
set<int> covered;


int vertex_cover(int root, int incl, int parent)
{
    covered.insert(root);
    if(edges[root].empty())
        return incl;
    if(res[root][incl] != -1)
        return res[root][incl];
    int sum = 0;
    for(int i = 0; i < edges[root].size(); i++)
    {
        int vert = edges[root][i];
        if (vert != parent)
        {
            if(incl == 0)
                sum += vertex_cover(vert, 1, root);
            else
                sum += min(vertex_cover(vert, 0, root), vertex_cover(vert, 1, root));
        }
    }
    res[root][incl] = sum + incl;
    return res[root][incl];
}


int main() {

    int num = 0;
    int neighbours = 0;
    cin >> num;
    for(int i = 0; i < num; i++)
    {
        vector<int> tmp;
        vector<int> tmp2 = {-1,-1};
        cin >> neighbours;
        for(int j = 0; j < neighbours; j ++)
        {
            int x;
            cin >> x;
            tmp.push_back(x);
        }
        res.push_back(tmp2);
        edges.push_back(tmp);
    }

    int out = min(vertex_cover(0,0,0), vertex_cover(0,1,0));
    while(covered.size() < num)
    {
        for(int i = 1; i < num; i++)
            if (!covered.count(i))
                out += min(vertex_cover(i,0,i), vertex_cover(i,1,i));
    }
    cout << out;
    return 0;
}
