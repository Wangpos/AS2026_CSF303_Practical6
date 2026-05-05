# CSF303 Practical 6: Advanced Algorithms Implementation

## Reflection and Analysis

---

## 1. TRIE (PREFIX TREE) IMPLEMENTATION

### Algorithm Overview

A **Trie** (or Prefix Tree) is a tree-like data structure that stores strings character-by-character. Each node represents a character, and paths from root to nodes represent prefixes or complete words.

### Key Features

- **Structure**: Each node contains a map of character → child node pointers
- **Insert Operation**: O(m) where m is string length
  - Traverse/create nodes for each character
  - Mark final node as end-of-word
- **Search Operation**: O(m)
  - Traverse tree following string characters
  - Check if final node is marked as word
- **Delete Operation**: O(m)
  - Find the word path
  - Remove end-of-word marker
  - Clean up nodes with no children

### Implementation Details

```cpp
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord = false;
};
```

### Advantages

✓ Fast prefix-based searches  
✓ Useful for autocomplete, spell-checking  
✓ Can check if string is prefix of any word

### Disadvantages

✗ Space complexity: O(ALPHABET_SIZE × m × n)  
✗ Slower than hash tables for single lookups  
✗ Many intermediate nodes create overhead

### Test Results

- Successfully inserted 6 words (apple, app, application, apply, banana, band)
- All searches worked correctly
- Deletion with proper cleanup verified
- Prefix checking functional

---

## 2. PATRICIA TREE (RADIX TREE) IMPLEMENTATION

### Algorithm Overview

**PATRICIA** (Practical Algorithm to Retrieve Information Coded in Alphanumeric) is a compressed trie that stores strings on edges instead of individual characters. This eliminates intermediate nodes with single children, making it more space-efficient than standard tries.

### Key Differences from Trie

| Feature            | Trie                        | PATRICIA                    |
| ------------------ | --------------------------- | --------------------------- |
| Nodes              | Store single characters     | Store edge labels (strings) |
| Space              | O(ALPHABET_SIZE × m × n)    | O(n) - only n words         |
| Intermediate nodes | Many                        | Removed/compressed          |
| Speed              | Fast character-by-character | Faster due to compression   |

### Implementation Strategy

1. **Longest Common Prefix (LCP)**: Find matching characters between edge label and key
2. **Edge Matching**:
   - Full match: Continue traversal with remaining string
   - Partial match: Split edge and create new intermediate node
   - No match: Create new leaf node

3. **Operations**:
   - **Insert**: O(m) - traverse and potentially split edges
   - **Search**: O(m) - follow edges with matching prefixes
   - **Delete**: O(m) - remove word marker and clean up single-child nodes

### Core Algorithm

```
Insert(key):
  node = root, remaining = key
  while remaining is not empty:
    for each child of node:
      lcp = getLongestCommonPrefix(child.edgeLabel, remaining)
      if lcp > 0:
        if lcp == child.edgeLabel.length && lcp == remaining.length:
          Mark child as end-of-word
        else if lcp == child.edgeLabel.length:
          node = child, remaining = remaining[lcp:]
        else:
          Split edge at lcp position
```

### Advantages

✓ Significantly reduced space complexity  
✓ Same time complexity as trie  
✓ Better for strings with common prefixes  
✓ Used in routing tables, DNS systems

### Test Results

- Correctly inserted 7 words
- All searches verified (found existing words, correctly identified missing words)
- Deletions with proper edge compression working
- Edge splitting during insertion verified

---

## 3. MANACHER'S ALGORITHM

### Algorithm Overview

**Manacher's Algorithm** finds the longest palindromic substring in linear time O(n). It uses symmetry properties of palindromes and preprocessing to avoid re-checking already-verified characters.

### Key Insight: String Preprocessing

The algorithm inserts a special character (e.g., '#') between all characters:

```
Original: "babad"
Processed: "^#b#a#b#a#d#$"
```

**Why?** This converts even-length palindromes into odd-length palindromes in the processed string, allowing unified handling.

### Algorithm Steps

1. **Preprocessing**: Insert '#' between characters and add anchors '^' and '$'

2. **Main Loop**: For each position i, maintain:
   - `palindromeArray[i]`: Radius of palindrome centered at i
   - `centerIndex`: Center of rightmost palindrome found
   - `rightBoundary`: Right boundary of rightmost palindrome

3. **Optimization**: For position i within rightBoundary:
   - Mirror position: `mirror = 2 * centerIndex - i`
   - Use previously computed `palindromeArray[mirror]` to avoid recomputation
   - Only expand if needed (symmetry helps)

### Pseudocode

```
Manacher(s):
  s = preprocess(s)
  P = array of size len(s), all 0
  center = 0, right = 0

  for i from 1 to len(s)-1:
    mirror = 2*center - i

    if i < right:
      P[i] = min(right - i, P[mirror])

    // Try to expand palindrome
    while s[i + P[i] + 1] == s[i - P[i] - 1]:
      P[i]++

    // Update center and right if needed
    if i + P[i] > right:
      center = i
      right = i + P[i]

  return longest palindrome from P
```

### Complexity Analysis

- **Time**: O(n) - Each character visited at most twice
- **Space**: O(n) - For palindrome array and processed string

### Why Linear Time?

- Never backtracks: When we find a palindrome boundary, we don't revisit those characters
- Symmetry property: For palindromes, mirrored positions have related properties
- Right boundary only moves forward: Never decreases during algorithm

### Test Cases Verified

| Input              | Output       | Length |
| ------------------ | ------------ | ------ |
| "babad"            | "bab"        | 3      |
| "cbbd"             | "bb"         | 2      |
| "racecar"          | "racecar"    | 7      |
| "forgeeksskeegfor" | "geeksskeeg" | 10     |
| "abacabad"         | "abacaba"    | 7      |
| "abacdcaba"        | "abacdcaba"  | 9      |

### Verification

- Compared Manacher's algorithm with brute force (expand-around-center)
- All results match perfectly ✓

### Advantages

✓ Linear time complexity (better than O(n²) brute force)  
✓ Elegant use of symmetry properties  
✓ Optimal algorithm for this problem  
✓ Foundation for advanced string algorithms

---

## 4. COMPARATIVE ANALYSIS

### Time Complexity Comparison

| Algorithm | Insert | Search | Delete | Space    |
| --------- | ------ | ------ | ------ | -------- |
| Trie      | O(m)   | O(m)   | O(m)   | O(n × m) |
| PATRICIA  | O(m)   | O(m)   | O(m)   | O(n)     |
| Manacher  | N/A    | O(n)   | N/A    | O(n)     |

_where m = string length, n = number of strings_

### Use Cases

**Trie**

- Autocomplete systems
- Spell checking
- IP routing (traditional approach)
- Dictionary implementations

**PATRICIA/Radix Tree**

- IP routing tables (modern approach)
- DNS systems
- Text compression
- Memory-constrained applications

**Manacher's Algorithm**

- Longest palindromic substring finding
- Palindrome-related substring problems
- Text analysis and compression

---

## 5. IMPLEMENTATION INSIGHTS

### Design Decisions

1. **Trie**: Used `unordered_map` for character mapping
   - Flexible alphabet size
   - Dynamic memory allocation per node
   - Easy to understand and implement

2. **PATRICIA**: Implemented edge-label compression
   - More complex due to edge splitting
   - Significant space savings for large datasets
   - Demonstrated proper LCP computation

3. **Manacher**: Preprocessing with sentinel characters
   - Unified odd/even length handling
   - Clear separation of concerns
   - Included verification against brute force

### Challenges Overcome

1. **Trie Deletion**: Proper cleanup of nodes to avoid memory waste
2. **PATRICIA**: Handling edge cases of partial prefix matches
3. **Manacher**: Careful index management in processed string

---

## 6. LEARNING OUTCOMES

### Key Takeaways

1. **String Data Structures**: Understanding different tree-based approaches for string storage and retrieval

2. **Algorithm Optimization**:
   - How preprocessing can lead to better complexity
   - Using symmetry/mathematical properties for optimization
   - Space-time tradeoffs (PATRICIA is better in space but more complex)

3. **Practical Applications**: Each algorithm serves specific real-world needs
   - Tries: User-facing features (autocomplete)
   - PATRICIA: Infrastructure (routing)
   - Manacher: Text analysis

4. **Complexity Analysis**: Going from O(n²) to O(n) through clever algorithm design

---

## 7. FILES SUBMITTED

- `trie.cpp` - Complete Trie implementation with tests
- `patricia.cpp` - PATRICIA tree implementation with tests
- `manacher.cpp` - Manacher's algorithm implementation with tests
- `main.cpp` - Main driver program
- `Makefile` - Build configuration
- Program output screenshots (showing all operations)
- This reflection document

---

## 8. COMPILATION AND EXECUTION

**To compile:**

```bash
make clean && make
```

**To run:**

```bash
./algorithms
```

**To clean:**

```bash
make clean
```

---

## Conclusion

This practical exercise successfully demonstrated three fundamental advanced algorithms:

1. **Trie** - A foundational string structure combining simplicity with good performance
2. **PATRICIA** - An optimized variant showing the importance of space efficiency
3. **Manacher's Algorithm** - A masterclass in algorithmic optimization using mathematical properties

All implementations are tested, verified, and demonstrate O(m) or O(n) efficiency. The code is well-documented with clear explanations of complexity, design choices, and practical applications.

**Status**: ✓ Complete and tested
