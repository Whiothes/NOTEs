#include <stdio.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2,
                              int nums2Size) {
    double a   = 0.0;
    double b   = 0.0;
    double res = 0.0;

    int *nums = (int *)calloc(nums1Size + nums2Size, sizeof(int));

}

int main(int argc, char* argv[argc]) {
    int nums1[] = {1, 1};
    int nums2[] = {1, 2};

  printf("%f\n", findMedianSortedArrays(nums1, sizeof(nums1) / sizeof(int),
                                        nums2, sizeof(nums2) / sizeof(int)));

  return 0;
}
