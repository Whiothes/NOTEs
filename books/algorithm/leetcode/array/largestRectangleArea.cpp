#include <iostream>
#include <vector>
using namespace std;

class Solution
{
 public:
  int largestRectangleArea(vector<int> &height)
  {
    vector<int> s;
    height.push_back(0);

    int sum = 0;
    int i   = 0;

    while (i < height.size()) {
      if (s.empty() || height[i] > height[s.back()]) {
        cout << "i = " << i << ", height = " << height[i] << endl;
        s.push_back(i);
        i++;
      } else {
        int t = s.back();
        cout << "i = " << i << ", t = " << t;
        s.pop_back();
        sum = max(sum, height[t] * (s.empty() ? i : i - s.back() - 1));
        cout << ", sum = " << sum << endl;
      }
    }
    return sum;
  }
};

int main()
{
  vector<int> height = {2, 1, 10, 5, 6, 2, 3};

  cout << Solution().largestRectangleArea(height) << endl;
}
