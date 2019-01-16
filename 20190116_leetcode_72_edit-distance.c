int min3(int a, int b, int c) {
    if (a <= b && a <= c)
        return a;
    if (b <= a && b <= c)
        return b;
    return c;
}

int max2(int a, int b) {
    return a > b? a: b;
}

int str_len(char *s) {
    if (!s)
        return 0;
    int len = 0;
    for (; *s != '\0'; s++)
        len++;
    return len;
}

int minDistance(char *s1, char *s2) {
    if (!s1 || !s2)
        // 其中任意一个为空时，返回另外一个的长度
        return max2(str_len(s1), str_len(s2));
    int s1_len = str_len(s1);
    int s2_len = str_len(s2);

    int matrix[s1_len + 1][s2_len + 1];
    for (int i = 0; i < s2_len + 1; i++)
        matrix[0][i] = i;
    
    for (int i = 0; i < s1_len + 1; i++)
        matrix[i][0] = i;

    for (int i = 1; i < s1_len + 1; i++) {
        for (int j = 1; j < s2_len + 1; j++) {
            if (s1[i - 1] == s2[j - 1])
                matrix[i][j] = matrix[i - 1][j - 1];
            else
                // 这边是原始举例加 1
                matrix[i][j] = min3(
                        matrix[i][j - 1],
                        matrix[i - 1][j],
                        matrix[i - 1][j - 1]
                ) + 1;
        }
    }
    return matrix[s1_len][s2_len];
}

