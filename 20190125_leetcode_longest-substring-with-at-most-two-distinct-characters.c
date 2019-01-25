#include <assert.h>

int max2(int a, int b) {
    return a > b? a: b;
}

int lengthOfLongestSubstringTwoDistinct(char *s) {
    if (!s || *s == '\0')
        return 0;

    int max_len = 0;
    int idx = -1;
    int left = 0, right = 1;
    for (; s[right] != '\0'; right++) {
        if (s[right] == s[right - 1])
            continue;
        if (idx >= 0 && s[idx] != s[right]) {
            max_len = max2(right - left, max_len);
            left = idx + 1;
        }
        idx = right - 1;
    }
    return max2(max_len, right - left);
}

void test_lengthOfLongestSubstringTwoDistinct() {
    assert(lengthOfLongestSubstringTwoDistinct("") == 0);
    assert(lengthOfLongestSubstringTwoDistinct("abccc") == 4);
    assert(lengthOfLongestSubstringTwoDistinct("abcccdd") == 5);
    assert(lengthOfLongestSubstringTwoDistinct("aaabbb") == 6);
}

int main() {
    test_lengthOfLongestSubstringTwoDistinct();
}
