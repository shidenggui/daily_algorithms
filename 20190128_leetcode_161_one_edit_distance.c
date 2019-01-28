#include <assert.h>
#include <stdbool.h>

int str_len(char *s) {
    int count = 0;
    for (; *s != '\0'; s++)
        count++;
    return count;
}
int one_edit_distance(char *s1, char *s2) {
    if (!s1 || !s2)
        return false;

    int m = str_len(s1);
    int n = str_len(s2);
    if (m > n) return one_edit_distance(s2, s1);
    if (n - m >= 2) return false;

    int i = 0;
    // 使用 i < m 效率更高
    // while (s1[i] != '\0' && s1[i] == s2[i]) i++;
    while (i < m && s1[i] == s2[i]) i++;
    if (i == m) return m != n;

    if (m != n)
        return false;
    i++;
    // 使用 i < m 效率更高
    // while (s1[i] != '\0' && s1[i] == s2[i]) i++;
    while (i < m && s1[i] == s2[i]) i++;
    return i == m;
}

void test_one_edit_distance() {
    assert(one_edit_distance("", "") == false);
    assert(one_edit_distance("a", "") == true);
    assert(one_edit_distance("aa", "aab") == true);
    assert(one_edit_distance("aba", "aab") == false);
    assert(one_edit_distance("aba", "ada") == true);

}

int main() {
    test_one_edit_distance();
}
