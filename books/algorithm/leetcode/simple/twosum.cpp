#include <vector>

using namespace std;

class Solution {
  public:
    vector<int> twoSum(vector<int> &nums, int target) {
        vector<int> ret;

        int b, e, mid, sum;

        b = 0;
        e = nums.size() - 1;

        for (;;) {
            sum = nums[b] + nums[e];
            if (sum == target) {
                break;
            } else if (sum > target) {
                e = (b + e) / 2;
            }
        }

        return ret;
    }
};

int main() {
    Solution s;
    vector<int> vec;

    vec.push_back(2);
    vec.push_back(7);
    vec.push_back(11);
    vec.push_back(15);

    s.twoSum(vec, 9);
    return 0;
}
