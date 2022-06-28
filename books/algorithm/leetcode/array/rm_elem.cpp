#include <iostream>
using namespace std;

class Solution {
   public:
    int removeElement(int A[], int n, int elem) {
        int i = 0;
        int j = 0;

        for (j = 0; j < n; ++j) {
            if (A[j] == elem) {
                continue;
            }

            A[i] = A[j];
            ++i;
        }
        return i;
    }
};

int main() {
    Solution S = Solution();

    int A[] = {1, 2, 7, 3, 4, 5, 6, 7, 7, 9, 10};
    int res = S.removeElement(A, sizeof(A) / sizeof(int), 7);

    cout << "remain count: " << res << endl;
    for (int i = 0; i < res; ++i) {
        cout << A[i] << " ";
    }
    cout << endl;
}
