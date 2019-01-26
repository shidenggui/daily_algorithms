/*
 * Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
 * 
 * Example 1:
 * 
 * Input: "babad"
 * Output: "bab"
 * Note: "aba" is also a valid answer.
 * Example 2:
 * 
 * Input: "cbbd"
 * Output: "bb"
 *
 * 思路：
 * 回文字符串的中心有两种可能，一种是在某个字符上，例如 "aba"，有 n 种可能。一种是在两个字符中间 例如 "abba"，有 n - 1 种可能。总共 2n - 1 种。
 * 确定中心之后只需要往两边扩展就可以判断是否是回文字符串，然后保存其中最大的长度和左侧开始的位置即可。需要 O(n)。这里需要注意的是不要扩张到超过字符串的起始和结尾
 * 总共的时间复杂度为 O(N^2) 空间复杂度 O(1)
 *: 8 ms, faster than 56.25% 
 * 据说还有一种 O(N) 时间复杂度，O(N) 空间复杂度的方法，叫做 Manacher’s Algorithm 
 * https://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-1/
 * 如果后期有兴趣会研究下
 */
int find(char *s, int left, int right, int *left_start) {
    while (left >= 0 && s[right] != '\0') {
        if (s[left] != s[right])
            break;
        left--;
        right++;
    }
    *left_start = left + 1;
    // (right - 1) - (left + 1) + 1
    return right - left - 1;
}

char* longestPalindrome(char* s) {
    if (!s)
        return NULL;
    int max_len = 0;
    int max_left;
    
    int len, left;
    for (int i = 0; s[i] != '\0'; i++) {
        len = find(s, i, i, &left);
        if (len > max_len) {
            max_len = len;
            max_left = left;
        }
        
        len = find(s, i, i + 1, &left);
        if (len > max_len) {
            max_len = len;
            max_left = left;
        }
    }
    char *lps = malloc(sizeof(char) * (max_len + 1));
    memcpy(lps, s + max_left, max_len);
    lps[max_len] = '\0';
    
    return lps;
}
