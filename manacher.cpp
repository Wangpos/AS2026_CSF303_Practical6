#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * Manacher's Algorithm - Find the Longest Palindromic Substring
 * 
 * Algorithm Overview:
 * - Uses an auxiliary array to track palindrome radius at each position
 * - Maintains a "center" and "right" boundary of previously found palindromes
 * - Preprocesses string by inserting special characters (e.g., '#') between characters
 * - This converts even-length palindromes to odd-length in the modified string
 * 
 * Time Complexity: O(n) - Linear time
 * Space Complexity: O(n) - For the auxiliary array and modified string
 * 
 * Key Insight:
 * - By inserting special characters, we can use symmetry properties of palindromes
 * - We never backtrack, making it linear time
 */

class ManacherAlgorithm {
private:
    string originalString;
    string processedString;
    vector<int> palindromeArray;
    int centerIndex;
    int rightBoundary;
    string longestPalindrome;
    int maxRadius;

    // Preprocess string by inserting separator '#'
    string preprocessString(const string& s) {
        string processed = "^#";
        for (char c : s) {
            processed += c;
            processed += '#';
        }
        processed += '$';
        return processed;
    }

    // Expand around center (used in standard approach for comparison)
    pair<int, int> expandAroundCenter(int left, int right) {
        while (left >= 0 && right < originalString.length() &&
               originalString[left] == originalString[right]) {
            left--;
            right++;
        }
        return {left + 1, right - 1};
    }

public:
    ManacherAlgorithm() : centerIndex(0), rightBoundary(0), maxRadius(0) {}

    // Main Manacher's algorithm
    void findLongestPalindrome(const string& s) {
        originalString = s;
        if (s.empty()) {
            cout << "Empty string provided" << endl;
            return;
        }

        processedString = preprocessString(s);
        palindromeArray.assign(processedString.length(), 0);

        centerIndex = 0;
        rightBoundary = 0;
        maxRadius = 0;
        int maxCenter = 0;

        for (int i = 1; i < processedString.length() - 1; i++) {
            // Mirror of i with respect to centerIndex
            int mirror = 2 * centerIndex - i;

            // If i is within the right boundary, we can use previously computed values
            if (i < rightBoundary) {
                palindromeArray[i] = min(rightBoundary - i, palindromeArray[mirror]);
            }

            // Try to expand palindrome centered at i
            while (processedString[i + palindromeArray[i] + 1] ==
                   processedString[i - palindromeArray[i] - 1]) {
                palindromeArray[i]++;
            }

            // If palindrome centered at i extends past rightBoundary, update center and right
            if (i + palindromeArray[i] > rightBoundary) {
                centerIndex = i;
                rightBoundary = i + palindromeArray[i];
            }

            // Track the longest palindrome
            if (palindromeArray[i] > maxRadius) {
                maxRadius = palindromeArray[i];
                maxCenter = i;
            }
        }

        // Extract the longest palindrome
        int start = (maxCenter - maxRadius) / 2;
        longestPalindrome = originalString.substr(start, maxRadius);
    }

    // Get the longest palindromic substring
    string getLongestPalindrome() const {
        return longestPalindrome;
    }

    // Get all palindromes of a certain length
    vector<string> getAllPalindromes(int minLength = 1) {
        vector<string> palindromes;

        for (int i = 1; i < processedString.length() - 1; i++) {
            int radius = palindromeArray[i];
            if (radius >= minLength / 2) {
                int start = (i - radius) / 2;
                int len = radius;
                if (len >= minLength) {
                    string pal = originalString.substr(start, len);
                    // Avoid duplicates
                    if (find(palindromes.begin(), palindromes.end(), pal) == palindromes.end()) {
                        palindromes.push_back(pal);
                    }
                }
            }
        }

        sort(palindromes.begin(), palindromes.end(),
             [](const string& a, const string& b) {
                 return a.length() > b.length();
             });

        return palindromes;
    }

    // Print detailed information
    void printDetails() {
        cout << "Original String: " << originalString << endl;
        cout << "Processed String: " << processedString << endl;
        cout << "Palindrome Array: ";
        for (int val : palindromeArray) {
            cout << val << " ";
        }
        cout << endl;
        cout << "Longest Palindrome: " << longestPalindrome << " (length: " << longestPalindrome.length() << ")" << endl;
    }

    // Additional method for comparing with brute force (for testing)
    string bruteForceFind(const string& s) {
        if (s.empty()) return "";

        string longest = string(1, s[0]);

        for (int i = 0; i < s.length(); i++) {
            // Odd length palindromes
            auto [l, r] = expandAroundCenter(i, i);
            if (r - l + 1 > longest.length()) {
                longest = s.substr(l, r - l + 1);
            }

            // Even length palindromes
            if (i + 1 < s.length()) {
                tie(l, r) = expandAroundCenter(i, i + 1);
                if (r - l + 1 > longest.length()) {
                    longest = s.substr(l, r - l + 1);
                }
            }
        }

        return longest;
    }
};

void demonstrateManacher() {
    cout << "\n========== MANACHER'S ALGORITHM IMPLEMENTATION ==========" << endl;

    vector<string> testCases = {
        "babad",
        "cbbd",
        "racecar",
        "forgeeksskeegfor",
        "a",
        "ac",
        "abacabad",
        "bananas",
        "abacdcaba",
        ""
    };

    for (const string& testCase : testCases) {
        if (testCase.empty()) continue;

        cout << "\n--- Input: \"" << testCase << "\" ---" << endl;

        ManacherAlgorithm manacher;
        manacher.findLongestPalindrome(testCase);

        cout << "Longest Palindrome: \"" << manacher.getLongestPalindrome() << "\"" << endl;
        cout << "Length: " << manacher.getLongestPalindrome().length() << endl;

        // Show all palindromes of length >= 2
        vector<string> allPalindromes = manacher.getAllPalindromes(2);
        if (!allPalindromes.empty()) {
            cout << "All Palindromic Substrings (length >= 2): ";
            for (int i = 0; i < min(5, (int)allPalindromes.size()); i++) {
                cout << "\"" << allPalindromes[i] << "\" ";
            }
            if (allPalindromes.size() > 5) cout << "... (" << allPalindromes.size() << " total)";
            cout << endl;
        }
    }

    cout << "\n========================================================" << endl;

    // Demonstration of algorithm correctness with brute force comparison
    cout << "\n--- VERIFICATION (Manacher vs Brute Force) ---" << endl;
    ManacherAlgorithm manacher;
    vector<string> verifyTests = {"abacabad", "forgeeksskeegfor", "racecar"};

    for (const string& test : verifyTests) {
        manacher.findLongestPalindrome(test);
        string manacharResult = manacher.getLongestPalindrome();
        string bruteForceResult = manacher.bruteForceFind(test);

        cout << "Input: \"" << test << "\"" << endl;
        cout << "  Manacher's: \"" << manacharResult << "\" | Brute Force: \"" << bruteForceResult << "\"" << endl;
        cout << "  Match: " << (manacharResult.length() == bruteForceResult.length() ? "✓ YES" : "✗ NO") << endl;
    }

    cout << "\n========================================================\n" << endl;
}
