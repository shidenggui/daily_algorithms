/*
 * https://leetcode.com/problems/majority-element/submissions/
 */

int majorityElement(int* arr, int n) {
    int majority;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (count != 0) {
            if (arr[i] == majority)
                count++;
            else
                count--;
        } else {
            majority = arr[i];
            count = 1;
        }
    }
    return majority;
}

// test cases:
// input: [0], 1 output: 0
// input: [3, 2, 3], 3 output: 3
