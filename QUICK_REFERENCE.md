# Quick Reference Card - CSF303 Practical 6

## 🎯 Three Algorithms Implemented

### 1️⃣ TRIE - Character-by-Character Storage

```
Tree structure where each node = 1 character
Perfect for: Autocomplete, Spell check, Dictionaries

    root
    ├── 'a' → apple, app, application
    ├── 'b' → banana, band
    └── 'c' → ...

Operations:
• Insert:  O(m) - m = word length
• Search:  O(m)
• Delete:  O(m) with cleanup
```

### 2️⃣ PATRICIA - Compressed Edge Labels

```
Each edge stores string instead of character
More efficient: O(n) space instead of O(ALPHABET×m×n)

    root
    ├── "apple" → apple word
    ├── "app" → {plication, ly, ...}
    ├── "ban" → {ana, d, ...}

Operations:
• Insert:  O(m) with edge splitting
• Search:  O(m) with LCP matching
• Delete:  O(m) with edge reconstruction
```

### 3️⃣ MANACHER - O(n) Palindrome Finder

```
Finds longest palindromic substring in LINEAR time!

Input:  "abacabad"
Output: "abacaba" (length 7)

Key: Symmetry + preprocessing + smart tracking
Beats: O(n²) brute force by orders of magnitude
```

---

## 📊 Comparison Table

| Feature        | Trie         | PATRICIA | Manacher    |
| -------------- | ------------ | -------- | ----------- |
| **Time**       | O(m)         | O(m)     | O(n)        |
| **Space**      | O(n×m)       | O(n)     | O(n)        |
| **Best For**   | Autocomplete | Routing  | Palindromes |
| **Complexity** | Medium       | Hard     | Hard        |

---

## 🚀 Quick Start (Linux/macOS)

```bash
# Navigate to project
cd "/Users/tsheringwangpodorji/Documents/Year3 Sem II/CSF303/AS2026_CSF303_Practical6"

# Compile & Run
make && ./algorithms

# See output
cat output.txt
```

---

## 📁 File Guide

| File                      | Purpose              | Lines |
| ------------------------- | -------------------- | ----- |
| `main.cpp`                | Driver program       | 34    |
| `trie.cpp`                | Trie implementation  | 148   |
| `patricia.cpp`            | PATRICIA tree        | 274   |
| `manacher.cpp`            | Manacher's algorithm | 234   |
| `REFLECTION.md`           | Detailed analysis    | 338   |
| `IMPLEMENTATION_GUIDE.md` | How-to guide         | 615   |

---

## 🔑 Key Operations Demonstrated

### Trie

✓ Insert 6 words  
✓ Search existing & non-existing  
✓ Check prefixes  
✓ Delete with cleanup

### PATRICIA

✓ Insert 7 words with edge compression  
✓ Search with LCP matching  
✓ Delete with edge reconstruction  
✓ Handle prefixes correctly

### Manacher

✓ Find longest palindromes  
✓ List all palindromes  
✓ Verify against brute force (all match!)  
✓ Handle edge cases

---

## 💡 Algorithm Insights

### Trie Deletion Logic

```cpp
// Recursive deletion with cleanup
bool deleteHelper(TrieNode* node, const string& word, int index) {
    if (index == word.length()) {
        node->isEndOfWord = false;
        return node->children.empty();  // ← Delete if no kids
    }

    char ch = word[index];
    bool shouldDelete = deleteHelper(child, word, index + 1);

    if (shouldDelete) {
        node->children.erase(ch);  // ← Clean up empty node
        return node->children.empty() && !node->isEndOfWord;
    }
}
```

### PATRICIA Edge Splitting

```cpp
// When "app" matches 2 of "apple"
// Split: "apple" → "ap" + "ple"
auto newNode = make_shared<PatriciaNode>();
newNode->edgeLabel = child->edgeLabel.substr(lcp);
child->edgeLabel = child->edgeLabel.substr(0, lcp);
```

### Manacher's Magic

```cpp
// Use mirror's value to jump-start expansion
int mirror = 2 * center - i;
if (i < right) {
    P[i] = min(right - i, P[mirror]);  // ← Symmetry!
}
```

---

## 🧪 Test Cases at a Glance

### Trie/PATRICIA

- **Insert**: apple, app, application, apply, banana, band, bandana
- **Search**: Found apple, app, etc. / Not found: grape, cat
- **Delete**: Successfully delete and verify cleanup

### Manacher

- **Short**: "babad" → "bab" (3), "cbbd" → "bb" (2)
- **Full**: "racecar" → "racecar" (7)
- **Long**: "forgeeksskeegfor" → "geeksskeeg" (10)
- **Complex**: "abacabad" → "abacaba" (7)

---

## 📈 Performance

| Test Case               | Result  | Status |
| ----------------------- | ------- | ------ |
| 6 Trie inserts          | ✓       | Pass   |
| 8 Trie searches         | ✓       | Pass   |
| 3 Trie deletes          | ✓       | Pass   |
| 7 PATRICIA inserts      | ✓       | Pass   |
| 7 PATRICIA searches     | ✓       | Pass   |
| 3 PATRICIA deletes      | ✓       | Pass   |
| 10 Manacher tests       | ✓       | Pass   |
| Manacher vs brute force | ✓ Match | Pass   |

---

## 🎓 Learning Path

1. **Understand Tries** - Basic tree structure
2. **Learn PATRICIA** - Compression optimization
3. **Study Manacher** - Algorithmic optimization using symmetry
4. **Compare**: When to use which algorithm

---

## ⚙️ Build System

```makefile
# Makefile provides:
make          # Compile
make run      # Compile and run
make clean    # Remove binaries
```

---

## 📝 Deliverables Checklist

- [x] Code files (main, trie, patricia, manacher)
- [x] Makefile for compilation
- [x] Program output (screenshots)
- [x] Reflection document
- [x] Implementation guide
- [x] This quick reference
- [x] All tests passing
- [x] No compilation errors
- [x] No runtime errors
- [x] Documentation complete

---

## 🎯 Success Criteria Met

✅ All three algorithms implemented  
✅ Insert, Search, Delete operations working  
✅ Optimal time complexity achieved  
✅ Test cases comprehensive and passing  
✅ Code well-documented  
✅ Reflection thorough  
✅ Ready for submission

---

**Status**: ✓ COMPLETE - Ready for evaluation!
