#include <stdio.h>
#include <stdlib.h>


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* twoSum(int* nums, int numsSize, int target) {
  int  i   = 0;
  int  j   = 0;
  int* res = (int*)calloc(2, sizeof(int));
  for (i = 0; i < numsSize - 1; ++i) {
    for (j = i + 1; j < numsSize; ++j) {
      if (nums[i] + nums[j] == target) {
        res[0] = i;
        res[1] = j;
        break;
      }
    }
  }
  return res;
}

int main(int argc, char* argv[argc]) {
  int* res = twoSum(nums, sizeof(nums) / sizeof(int), 929);
  printf("%d\n", nums[412] + nums[583]);
  printf("[%d, %d]", res[0], res[1]);

  return 0;
}
