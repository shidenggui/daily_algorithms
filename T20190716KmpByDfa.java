public class T20190716KmpByDfa {
    private static final int max = 256;

    public int search(String haystack, String needle) {
        int[][] dfa = calculateDFA(needle.toCharArray());
        int j = 0;
        int i = 0;
        for (; i < haystack.length() && j < needle.length(); i++)
            j = dfa[haystack.charAt(i)][j];
        if (j == needle.length())
            return i - j;
        return -1;
    }

    public int[][] calculateDFA(char pattern[]) {
        int[][] dfa = new int[max][pattern.length];
        dfa[pattern[0]][0] = 1;
        int restartState = 0;
        for (int i = 1; i < pattern.length; i++) {
            for (int j = 0; j < max; j++)
                dfa[j][i] = dfa[j][restartState];
            dfa[pattern[i]][i] = i + 1;
            restartState = dfa[pattern[i]][restartState];
        }
        return dfa;

    }

    public static void main(String args[]) {
        var result = new T20190716KmpByDfa().search("dfadfaac", "dfaa");
        System.out.println(result);
    }
}

