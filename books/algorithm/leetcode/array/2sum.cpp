#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
  public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        vector<int> ret;

        if (numbers.size() <= 1)
            return ret;

        unordered_map<int, int> myMap;
        for (auto i = 0; i < numbers.size(); ++i) {
            myMap[numbers[i]] = i;
        }

        for (auto i = 0; i < numbers.size(); ++i) {
            int rest_val = target - numbers[i];
            if (myMap.find(rest_val) != myMap.end()) {
                int index = myMap[rest_val];
                if (index == i)
                    continue;

                if (index < i) {
                    ret.push_back(index + 1);
                    ret.push_back(i + 1);
                    return ret;
                } else {
                    ret.push_back(i + 1);
                    ret.push_back(index + 1);
                    return ret;
                }
            }
        }
        ret.push_back(-1);
        return ret;
    }
};

int main() {
    vector<int> numbers = {1, 3, 5, 8, 9, 7, 2, 6};
    auto res = Solution().twoSum(numbers, 20);
    for (auto it = res.begin(); it != res.end(); ++it) {
        if (*it == -1)
            cout << "not found";
        else
            cout << *it << " ";
    }
    cout << endl;
}
