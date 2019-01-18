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
    for (int i = 0; i <= s1_len; i++)
        matrix[i][0] = i;
    for (int i = 0; i <= s2_len; i++)
        matrix[0][i] = i;
    
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
