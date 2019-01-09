#include <assert.h>

int zeros(unsigned n) {
    if (n == 0)
        return 0;
    int two_counts = 0;
    int five_counts = 0;

    int twos[n + 1]; 
    int fives[n + 1];
    for (int i = 1; i <= n ; i++) {
        if (i % 2 == 0) {
            twos[i] = twos[i / 2] + 1;
            two_counts += twos[i];
        } else
            twos[i] = 0;

        if (i % 5 == 0) {
            fives[i] = fives[i / 5] + 1;
            five_counts += fives[i];
        } else
            fives[i] = 0;
    }
    return two_counts < five_counts? two_counts: five_counts;
}

// 书中有个优化，因为能被 5 除的数，肯定比能被 2 除的数少，所以只要统计 5 的数量就可以了
int zeros2(unsigned n) {
    if (n == 0)
        return 0;
    int five_counts = 0;

    int fives[n + 1];
    for (int i = 1; i <= n ; i++) {
        if (i % 5 != 0)
            fives[i] = 0;
        else {
            fives[i] = fives[i / 5] + 1;
            five_counts += fives[i];

        }
    }
    return five_counts;
}

// 上面方法的缺陷是需要 O(N) 的空间，有没有办法减少对应的复杂度呢
// 书中提到 从 1 到 N 中 5 的数量可以由以下方式求得 
// N / 5 表示不大于 N 的书中 5 的倍数贡献的 5 的数量，比如 N = 5，这 N / 5 = 1，因为不大于的 5 的数量就只有 5
// 当 N = 10 时，N / 5 = 2，表示不大于 N 的 5 的倍数的数量为 2, 实际数为 5, 10
// 当 N = 25 时，N / 5 = 5，表示不大于 N 的 5 的倍数的数量为 2, 实际数为 5, 10, 15, 20, 25
// 而 N / （5 ^ 2) 除了 N / 5 之外，25 的倍数额外贡献的 5 的数量，在 N = 25 时 N / 25 = 1 为 25，加上 N / 5 = 5 正好后面有 6 个 0
// clever !!! 空间复杂度 O(1) 时间复杂度 O(LogN)
int zeros3(unsigned n) {
    int counts = 0;
    while (n) {
        counts += n / 5;
        n /= 5;
    }
    return counts;
}

void test_zeros() {
    assert(zeros(5) == 1);
    assert(zeros(10) == 2);
    assert(zeros(14) == 2);
    assert(zeros(15) == 3);
    assert(zeros(25) == 6);

    assert(zeros2(5) == 1);
    assert(zeros2(10) == 2);
    assert(zeros2(14) == 2);
    assert(zeros2(15) == 3);
    assert(zeros2(25) == 6);

    assert(zeros3(5) == 1);
    assert(zeros3(10) == 2);
    assert(zeros3(14) == 2);
    assert(zeros3(15) == 3);
    assert(zeros3(25) == 6);
}

int main() {
    test_zeros();
}
