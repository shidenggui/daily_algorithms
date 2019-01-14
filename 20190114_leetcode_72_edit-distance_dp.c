/*
 * edit distance 的 dp 解法。
 * 首先构造一个矩阵, 行 i 列 j，分别映射的是 s1[:i] s2[:j]
 *     '\0'  a  b
 * '\0'  0   1  2
 *   a   1
 *   b   2
 *
 *   然后初始化对应的初始值
 *   在遍历计算的时候要注意是 s1[i - 1] == s2[j - 1]，因为矩阵开头插入了一个 '\0'
 *   剩下的就是类似递归的思路：
 *   1. 如果当前字符相等的话，则 matrix[i][j] = matrix[i - 1][j - 1]
 *   2. 如果不相同，由以下三种情况取最小值
 *      1. s2 不变，由 s1 增加一个字符而来
 *      2. s1 不变，由 s2 增加一个字符而来
 *      3. 由 s1 和 s2 同时增加一个字符而来
 *  最后结果存储在 matrix[s1_len][s2_len]
 */ 
int max2(int a, int b) {
    return a > b? a: b;
}

int min3(int a, int b, int c) {
    if (a <= b && a <= c)
        return a;
    if (b <= a && b <= c)
        return b;
    return c;
}

int str_len(char *s) {
    if (!s)
        return 0;
    int count = 0;
    for (; *s != '\0'; s++)
        count++;
    return count;
}

int minDistance(char* s1, char* s2) {
    if (!s1 || !s2)
        return max2(str_len(s1), str_len(s2));
    int s1_len = str_len(s1);
    int s2_len = str_len(s2);
    int matrix[s1_len + 1][s2_len + 1];
    
    for (int i = 0; i <= s2_len; i++)
        matrix[0][i] = i;
    for (int i = 0; i <= s1_len; i++)
        matrix[i][0] = i;
    
    for (int i = 1; i <= s1_len; i++) {
        for (int j = 1; j <= s2_len; j++) {
            if (s1[i - 1] == s2[j - 1])
                matrix[i][j] = matrix[i - 1][j - 1];
            else {
                matrix[i][j] = min3(
                    matrix[i - 1][j],
                    matrix[i][j - 1],
                    matrix[i - 1][j - 1]
                ) + 1;
            }
        }
    }
    
    return matrix[s1_len][s2_len];
}
