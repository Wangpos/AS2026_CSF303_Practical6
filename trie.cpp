#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

/**
 * Basic Trie (Prefix Tree) Implementation
 * Time Complexity:
 * - Insert: O(m) where m is the length of the key
 * - Search: O(m) where m is the length of the key
 * - Delete: O(m) where m is the length of the key
 * Space Complexity: O(ALPHABET_SIZE * m * n) where n is the number of words
 */

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord = false;
};

class Trie {
private:
    TrieNode* root;

    // Helper function for deletion
    bool deleteHelper(TrieNode* node, const string& word, int index) {
        if (index == word.length()) {
            if (!node->isEndOfWord) {
                return false; // Word doesn't exist
            }
            node->isEndOfWord = false;
            return node->children.empty(); // Delete node if it has no children
        }

        char ch = word[index];
        if (node->children.find(ch) == node->children.end()) {
            return false; // Word doesn't exist
        }

        TrieNode* child = node->children[ch];
        bool shouldDeleteChild = deleteHelper(child, word, index + 1);

        if (shouldDeleteChild) {
            node->children.erase(ch);
            return node->children.empty() && !node->isEndOfWord;
        }
        return false;
    }

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert a word into the trie
    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEndOfWord = true;
        cout << "✓ Inserted: " << word << endl;
    }

    // Search for a word in the trie
    bool search(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                cout << "✗ Not Found: " << word << endl;
                return false;
            }
            node = node->children[ch];
        }
        if (node->isEndOfWord) {
            cout << "✓ Found: " << word << endl;
            return true;
        }
        cout << "✗ Prefix exists but not a complete word: " << word << endl;
        return false;
    }

    // Delete a word from the trie
    void deleteWord(const string& word) {
        if (deleteHelper(root, word, 0)) {
            cout << "✓ Deleted: " << word << endl;
        } else {
            cout << "✗ Could not delete: " << word << " (not found)" << endl;
        }
    }

    // Check if a prefix exists in the trie
    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (node->children.find(ch) == node->children.end()) {
                return false;
            }
            node = node->children[ch];
        }
        return true;
    }
};

void demonstrateTrie() {
    cout << "\n========== TRIE IMPLEMENTATION ==========" << endl;
    Trie trie;

    cout << "\n--- INSERT OPERATIONS ---" << endl;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");
    trie.insert("apply");
    trie.insert("banana");
    trie.insert("band");

    cout << "\n--- SEARCH OPERATIONS ---" << endl;
    trie.search("apple");
    trie.search("app");
    trie.search("appl");
    trie.search("application");
    trie.search("grape");
    trie.search("banana");

    cout << "\n--- PREFIX CHECK ---" << endl;
    cout << "Prefix 'app' exists: " << (trie.startsWith("app") ? "YES" : "NO") << endl;
    cout << "Prefix 'ban' exists: " << (trie.startsWith("ban") ? "YES" : "NO") << endl;
    cout << "Prefix 'cat' exists: " << (trie.startsWith("cat") ? "YES" : "NO") << endl;

    cout << "\n--- DELETE OPERATIONS ---" << endl;
    trie.deleteWord("app");
    trie.search("app");
    trie.search("apple");
    
    trie.deleteWord("banana");
    trie.search("banana");
    
    trie.deleteWord("grape");
    
    cout << "\n--- SEARCH AFTER DELETION ---" << endl;
    trie.search("apple");
    trie.search("application");
    trie.search("app");

    cout << "\n========================================\n" << endl;
}