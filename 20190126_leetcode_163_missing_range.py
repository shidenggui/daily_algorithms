#Ques tion: Given a sorted integer array where the range of elements are [0, 99] inclusive, return its missing ranges.
#For example, given [0, 1, 3, 50, 75], return [“2”, “4->49”, “51->74”, “76->99”] Example Ques tions  Candidate Might As k: Q: What if the given array is empty? A: Then you should return [“0->99”] as those ranges are missing.
#Q: What if the given array contains all elements from the ranges? A: Return an empty list, which means no range is missing.
# 关键在于提供 start - 1 和 end + 1 的sentinel，这样就不需要考虑 edge cases了。
# 这里通过 使得 prev 初始值为 start - 1 来提供 第一个初始值，
# 然后再循环完所有 arr 后，额外判断 end + 1 和 prev 的加上最后一个 sentinel 
def missing_range(arr, start, end):
    n = len(arr)
    
    result = []
    prev = start - 1
    for value in arr:
        if value - prev >= 2:
            result.append('{}->{}'.format(prev + 1, value - 1))
        prev = value

    if end + 1 - prev >= 2:
        result.append('{}->{}'.format(prev + 1, end))

    return result

def test():
    assert(str(missing_range([0, 1, 3, 50, 75], 0, 99)) == "['2->2', '4->49', '51->74', '76->99']")
    assert(str(missing_range([], 0, 99)) == "['0->99']")
    assert(str(missing_range([3], 0, 99)) == "['0->2', '4->99']")
    assert(str(missing_range(list(range(0, 100)), 0, 99)) == "[]")

# C++ 
public List<String> findMissingRanges(int[] vals, int start, int end) {
    List<String> ranges = new ArrayList<>();
    int prev = start - 1;
    for (int i = 0; i <= vals.length; i++) {
        int curr = (i == vals.length) ? end + 1 : vals[i];
        if (curr - prev >= 2) { ranges.add(getRange(prev + 1, curr - 1)); }
        prev = curr;
    }
    return ranges;
}

private String getRange(int from, int to) {
    return (from == to) ? String.valueOf(from) : from + "->" + to; 
}
