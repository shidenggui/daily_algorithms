char* longestCommonPrefix(char** strs, int n) {
    if (!strs || n < 1)
        return "";
    char c;
    for (int i = 0; strs[0][i] != '\0'; i++) {
        c = strs[0][i];
        for (int j = 1; j < n; j++) {
            if (strs[j][i] == '\0' || strs[j][i] != c) {
                char *s = malloc(sizeof(char) * (i + 1));
                memcpy(s, strs[0], i);
                s[i] = '\0';
                return s;
            }
        }
    }
    return strs[0];
}
