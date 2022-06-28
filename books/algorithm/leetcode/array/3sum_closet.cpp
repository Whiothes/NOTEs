#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
   public:
    int threeSumCloset(vector<int> &num, int target)
    {
        if (num.size() <= 2) {
            return -1;
        }

        int ret      = 0;
        int distance = INT_MAX;
        sort(num.begin(), num.end());

        for (int i = 0; i < num.size(); ++i) {
            int j = i + 1;
            int k = num.size() - 1;

            while (j < k) {
                int tmp_ret = num[i] + num[j] + num[k];
                int tmp_distance;

                if (tmp_ret < target) {
                    ++j;
                    tmp_distance = target - tmp_ret;
                    if (tmp_distance < distance) {
                        distance = tmp_distance;
                        ret      = tmp_ret;
                    }
                } else if (tmp_ret > target) {
                    --k;
                    tmp_distance = tmp_ret - target;
                    if (tmp_distance < distance) {
                        distance = tmp_distance;
                        ret      = tmp_ret;
                    }
                } else {
                    return tmp_ret;
                }
            }
        }

        return ret;
    }
};

int main()
{
    vector<int> num = {-5, 3, 2, -6, 3};

    auto ret = Solution().threeSumCloset(num, -12);
    cout << ret << endl;

    return 0;
}
