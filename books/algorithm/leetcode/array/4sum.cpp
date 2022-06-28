#include <iostream>
#include <vector>
using namespace std;

class Solution
{
   public:
    vector<vector<int> > fourSum(vector<int> &num, int target)
    {
        vector<vector<int> > ret;
        if (num.size() <= 3) {
            return ret;
        }
        sort(num.begin(), num.end());
        for (auto i = 0; i < num.size() - 3; ++i) {
            if (i > 0 && num[i] == num[i - 1]) {
                continue;
            }

            for (int j = i + 1; j < num.size() - 2; ++j) {
                if (j > i + 1 && num[j] == num[j - 1]) {
                    continue;
                }

                int k = j + 1;
                int l = num.size() - 1;
                while (k < l) {
                    int sum = num[i] + num[k] + num[j] + num[l];
                    if (sum == target) {
                        vector<int> cur;
                        cur.push_back(num[i]);
                        cur.push_back(num[j]);
                        cur.push_back(num[k]);
                        cur.push_back(num[l]);

                        ret.push_back(cur);
                        do {
                            ++k;
                        } while (k < l && num[k] == num[k - 1]);
                        do {
                            --l;
                        } while (k < l && num[l] == num[l + 1]);
                    } else if (sum < target) {
                        k++;
                    } else {
                        l--;
                    }
                }
            }
        }
        return ret;
    }
};

int main()
{
    vector<int> num = {-5, 3, 2, -6, 3, -1, -1};

    auto ret = Solution().fourSum(num, -5);

    for (auto it = ret.begin(); it != ret.end(); ++it) {
        for (auto jt = (*it).begin(); jt != (*it).end(); ++jt) {
            cout << *jt << " ";
        }
        cout << endl;
    }

    return 0;
}
