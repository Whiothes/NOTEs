#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
   public:
    vector<vector<int> > threeSum(vector<int> &num)
    {
        vector<vector<int> > ret;
        if (num.size() <= 2) return ret;

        sort(num.begin(), num.end());
        for (auto i = 0; i < num.size() - 2; ++i) {
            int j = i + 1;
            int k = num.size() - 1;
            while (j < k) {
                vector<int> cur;
                if (num[i] + num[j] + num[k] == 0) {
                    cur.push_back(num[i]);
                    cur.push_back(num[j]);
                    cur.push_back(num[k]);
                    ret.push_back(cur);
                    ++j, --k;
                    while (j < k && num[j - 1] == num[j]) {
                        ++j;
                    }
                    while (j < k && num[k] == num[k - 1]) {
                        --k;
                    }
                } else if (num[i] + num[j] + num[k] < 0) {
                    ++j;
                } else {
                    --k;
                }
            }
            while (i < num.size() - 1 && num[i] == num[i + 1]) ++i;
        }
        return ret;
    }
};

int main()
{
    vector<int> num = {-5, 3, 2, -6, 3};

    auto ret = Solution().threeSum(num);
    for (auto it = ret.begin(); it != ret.end(); ++it) {
        for (auto jt = (*it).begin(); jt != (*it).end(); ++jt) {
            cout << *jt << " ";
        }
        cout << endl;
    }

    return 0;
}
