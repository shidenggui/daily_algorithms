/*
 * 求一个数组中出现超过一半次数的数字。
 * 有两种办法：
 * 1. 使用 quick selection，快排的变种，这种的缺陷是要变动原来的数组，优点是如果最后的 num 实际不超过一半的话，只要检查左侧一半的数字即可。
 * 2. 根据数字规律，也就是下面的做法，On-line 算法。非常优雅，缺陷就是检查是否超过一半要扫描整个数组。
 */
#include <assert.h>
#include <stdbool.h>

bool g_invalid_input = false;

// arr must exist one number more than half, otherwise need check result
int more_than_half(int *arr, int n) {
    if (!arr || n <= 0) {
        g_invalid_input = true;
        return 0;
    }

    int num = arr[0];
    int times = 1;
    for (int i = 1; i < n; i++) {
        if (times == 0) {
            times++;
            num = arr[i];
        } else if (arr[i] == num)
            times++;
        else
            times--;
    }
    return num;
}

void test_more_than_half() {
    assert(more_than_half((int*)&(int[]){1}, 1) == 1);
    assert(more_than_half((int*)&(int[]){1, 1, 2}, 3) == 1);
    assert(more_than_half((int*)&(int[]){1, 1, 2, 2, 2}, 5) == 2);
    assert(more_than_half((int*)&(int[]){1, 2, 1, 2, 2}, 5) == 2);
    assert(more_than_half((int*)&(int[]){1, 2, 1, 2, 2}, 5) == 2);
    assert(more_than_half((int*)&(int[]){1, 2, 3, 2, 2, 2, 5, 4, 2}, 9) == 2);
}

int main() {
    test_more_than_half();
}
