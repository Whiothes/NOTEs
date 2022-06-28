#include <iostream>
#include <vector>
using namespace std;

class Solution
{
   public:
    vector<vector<int> > generate(int numRows)
    {
        vector<vector<int> > vals;
        vals.resize(numRows);

        for (int i = 0; i < numRows; i++) {
            vals[i].resize(i + 1);
            vals[i][0]                  = 1;
            vals[i][vals[i].size() - 1] = 1;
            for (int j = 1; j < vals[i].size() - 1; ++j) {
                vals[i][j] = vals[i - 1][j - 1] + vals[i - 1][j];
            }
        }

        return vals;
    }
};

int main()
{
    auto res = Solution().generate(5);

    for (auto i = res.begin(); i != res.end(); ++i) {
        auto it = *i;
        for (auto j = it.begin(); j != it.end(); ++j) {
            cout << *j << " ";
        }
        cout << endl;
    }
}
