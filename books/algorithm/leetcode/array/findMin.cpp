#include <iostream>
#include <vector>
using namespace std;

class Solution
{
   public:
    int findMin(vector<int> &num)
    {
        int size = num.size();
        if (size == 0) {
            return 0;
        } else if (size == 1) {
            return num[0];
        } else if (size == 2) {
            return min(num[0], num[1]);
        }

        int b = 0;
        int e = size - 1;
        while (b < e - 1) {
            if (num[b] < num[e]) {
                return num[b];
            }

            int m = b + (e - b) / 2;
            if (num[m] > num[b]) {
                b = m;
            } else if (num[m] < num[b]) {
                e = m;
            }
        }
        return min(num[b], num[e]);
    }
};

int main(int argc, char *argv[])
{
    vector<int> num = {4, 5, 6, 7, 1, 2};
    int         ret = Solution().findMin(num);
    cout << ret << endl;
}
