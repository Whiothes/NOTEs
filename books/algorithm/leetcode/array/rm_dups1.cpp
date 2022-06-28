#include <iostream>
using namespace std;

class Solution {
   public:
    int removeDuplicates(int A[], int n) {
        if (!n) return n;

        int i       = 0;
        int j       = 0;
        int counter = 0;

        for (j = 1; j < n; ++j) {
            if (A[i] == A[j]) {
                counter++;
                if (counter < 2) {
                    A[++i] = A[j];
                }
            } else {
                A[++i]  = A[j];
                counter = 0;
            }
        }

        return i + 1;
    }
};

int main() {
    int A[] = {0, 1, 3, 3, 3, 3, 7, 8, 10};

    int size = sizeof(A) / sizeof(int);

    int num = Solution().removeDuplicates(A, size);

    for (int i = 0; i < num; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}
