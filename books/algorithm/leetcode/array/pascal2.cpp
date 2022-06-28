#include <iostream>
#include <vector>

using namespace std;


class Solution {
 public:
  vector <int> getRow(int rowIndex) {
    vector <int> vals;

    vals.resize(rowIndex + 1, 1);

    for (auto i = 0; i < rowIndex + 1; ++i) {
      for (auto j = i - 1; j >= 1; --j) {
        vals[j] = vals[j] + vals[j-1];
      }
    }

    return vals;
  }
};

int main() {
  auto res = Solution().getRow(4);
  for (auto it= res.begin( ); it != res.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
}
