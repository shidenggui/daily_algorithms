/*
 * 思路就是维持一个滑动窗口，确实是非常有意思的思路
 * 空间复杂度 O(ASCII_SIZE) 时间复杂度 O(n)
 */
int max2(int a, int b) {
    return a > b? a: b;
}

int lengthOfLongestSubstring(char* s) {
    if (!s)
        return 0;
    int chars[256];
    memset(chars, -1, sizeof(chars));
    
    int max_len = 0;
    int prev_idx;
    for (int left = 0, right = 0; s[right] != '\0'; right++) {
        prev_idx = chars[s[right]];
        if (prev_idx >= left) 
            left = prev_idx + 1;
        max_len = max2(right - left + 1, max_len);
        chars[s[right]] = right;
    }
    return max_len;
}
