#include <iostream>

using namespace std;

class Solution
{
   public:
    void merge(int A[], int m, int B[], int n)
    {
        int i = m + n - 1;
        int j = m - 1;
        int k = n - 1;

        for (; i >= 0; i--) {
            if (j >= 0 && k >= 0) {
                if (A[j] > B[k]) {
                    A[i] = A[j];
                    --j;
                } else {
                    A[i] = B[k];
                    --k;
                }

            } else if (j >= 0) {
                A[i] = A[j];
                --j;
            } else if (k >= 0) {
                A[j] = B[k];
                --k;
            }
        }
    }
};

int main()
{
    int A[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int B[5]  = {1, 2, 3, 4, 5};
    int m     = 10;
    int n     = sizeof(B) / sizeof(int);

    Solution().merge(A, m, B, n);

    for (int i = 0; i < m + n; ++i) {
        cout << A[i] << " ";
    }
    cout << endl;
}
