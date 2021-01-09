Given two string arrays word1 and word2, return true if the two arrays represent the same string, and false otherwise.

A string is represented by an array if the array elements concatenated in order forms the string.

 

Example 1:

Input: word1 = ["ab", "c"], word2 = ["a", "bc"]
Output: true
Explanation:
word1 represents string "ab" + "c" -> "abc"
word2 represents string "a" + "bc" -> "abc"
The strings are the same, so return true.
Example 2:

Input: word1 = ["a", "cb"], word2 = ["ab", "c"]
Output: false
Example 3:

Input: word1  = ["abc", "d", "defg"], word2 = ["abcddefg"]
Output: true
 

Constraints:

1 <= word1.length, word2.length <= 103
1 <= word1[i].length, word2[i].length <= 103
1 <= sum(word1[i].length), sum(word2[i].length) <= 103
word1[i] and word2[i] consist of lowercase letters.

```
class Solution {
public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        int word1Id = 0, word2Id = 0;
        int i = 0, j = 0;
        while (word1Id < word1.size() && word2Id < word2.size()) {
            if (word1[word1Id][i] != word2[word2Id][j]) return false;
            ++i; ++j;
            if (i == word1[word1Id].size()) {
                ++word1Id;
                i = 0;
            }
            if (j == word2[word2Id].size()) {
                ++word2Id;
                j = 0;
            }
        }
        return word1Id == word1.size() && word2Id == word2.size();
    }
};
```
