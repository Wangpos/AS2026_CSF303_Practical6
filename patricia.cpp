#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

/**
 * PATRICIA Algorithm (Practical Algorithm to Retrieve Information Coded in Alphanumeric)
 * Also known as Radix Tree or Compact Trie
 * 
 * Key Difference from Trie:
 * - Nodes are compressed to store strings instead of single characters
 * - Removes intermediate nodes with only one child
 * - More space efficient than standard trie
 * 
 * Time Complexity:
 * - Insert: O(m) where m is the length of the key
 * - Search: O(m) where m is the length of the key
 * - Delete: O(m) where m is the length of the key
 * Space Complexity: O(n) where n is the number of words
 */

struct PatriciaNode {
    string edgeLabel;           // String label on the edge
    vector<shared_ptr<PatriciaNode>> children;
    bool isEndOfWord = false;
    string value = "";          // Optional: store associated value
};

class PatriciaTree {
private:
    shared_ptr<PatriciaNode> root;

    // Find the longest common prefix between two strings
    int getLCP(const string& s1, const string& s2) {
        int i = 0;
        while (i < s1.length() && i < s2.length() && s1[i] == s2[i]) {
            i++;
        }
        return i;
    }

    // Search and return node and remaining suffix
    pair<shared_ptr<PatriciaNode>, string> findNode(const string& key) {
        auto node = root;
        string remaining = key;

        while (!remaining.empty()) {
            bool found = false;
            for (auto& child : node->children) {
                int lcp = getLCP(child->edgeLabel, remaining);
                if (lcp > 0) {
                    if (lcp == child->edgeLabel.length()) {
                        // Full edge match, continue with remaining
                        remaining = remaining.substr(lcp);
                        node = child;
                        found = true;
                        break;
                    } else if (lcp == remaining.length()) {
                        // Remaining is a prefix of edge label
                        return {node, remaining};
                    }
                    break;
                }
            }
            if (!found) {
                return {nullptr, ""};
            }
        }
        return {node, ""};
    }

public:
    PatriciaTree() {
        root = make_shared<PatriciaNode>();
        root->edgeLabel = "";
    }

    // Insert a word into the PATRICIA tree
    void insert(const string& word) {
        auto node = root;
        string remaining = word;

        while (!remaining.empty()) {
            bool found = false;

            for (auto& child : node->children) {
                int lcp = getLCP(child->edgeLabel, remaining);
                if (lcp > 0) {
                    found = true;

                    if (lcp == child->edgeLabel.length() && lcp == remaining.length()) {
                        // Exact match
                        if (child->isEndOfWord) {
                            cout << "✗ Already exists: " << word << endl;
                        } else {
                            child->isEndOfWord = true;
                            cout << "✓ Inserted: " << word << endl;
                        }
                        return;
                    } else if (lcp == child->edgeLabel.length()) {
                        // Edge fully matched, continue traversal
                        node = child;
                        remaining = remaining.substr(lcp);
                        break;
                    } else {
                        // Partial match - need to split the edge
                        auto newNode = make_shared<PatriciaNode>();
                        newNode->edgeLabel = child->edgeLabel.substr(lcp);
                        newNode->children.push_back(child);
                        newNode->isEndOfWord = child->isEndOfWord;

                        child->edgeLabel = child->edgeLabel.substr(0, lcp);
                        child->children.clear();
                        child->children.push_back(newNode);
                        child->isEndOfWord = false;

                        remaining = remaining.substr(lcp);
                        if (!remaining.empty()) {
                            auto leafNode = make_shared<PatriciaNode>();
                            leafNode->edgeLabel = remaining;
                            leafNode->isEndOfWord = true;
                            child->children.push_back(leafNode);
                        } else {
                            child->isEndOfWord = true;
                        }
                        cout << "✓ Inserted: " << word << endl;
                        return;
                    }
                }
            }

            if (!found) {
                // Create new child node
                auto newNode = make_shared<PatriciaNode>();
                newNode->edgeLabel = remaining;
                newNode->isEndOfWord = true;
                node->children.push_back(newNode);
                cout << "✓ Inserted: " << word << endl;
                return;
            }
        }
        // Mark current node as end of word
        node->isEndOfWord = true;
        cout << "✓ Inserted: " << word << endl;
    }

    // Search for a word in the PATRICIA tree
    bool search(const string& word) {
        auto node = root;
        string remaining = word;

        while (!remaining.empty()) {
            bool found = false;

            for (auto& child : node->children) {
                int lcp = getLCP(child->edgeLabel, remaining);

                if (lcp > 0) {
                    if (lcp == child->edgeLabel.length() && lcp == remaining.length()) {
                        if (child->isEndOfWord) {
                            cout << "✓ Found: " << word << endl;
                            return true;
                        }
                        cout << "✗ Not found: " << word << " (prefix only)" << endl;
                        return false;
                    } else if (lcp == child->edgeLabel.length()) {
                        node = child;
                        remaining = remaining.substr(lcp);
                        found = true;
                        break;
                    }
                    cout << "✗ Not found: " << word << endl;
                    return false;
                }
            }

            if (!found) {
                cout << "✗ Not found: " << word << endl;
                return false;
            }
        }

        if (node->isEndOfWord) {
            cout << "✓ Found: " << word << endl;
            return true;
        }
        cout << "✗ Not found: " << word << endl;
        return false;
    }

    // Delete a word from the PATRICIA tree
    bool deleteWord(const string& word) {
        function<bool(shared_ptr<PatriciaNode>&, const string&)> deleteHelper =
            [&](shared_ptr<PatriciaNode>& node, const string& remaining) -> bool {
            if (remaining.empty()) {
                if (!node->isEndOfWord) {
                    return false;
                }
                node->isEndOfWord = false;
                return true;
            }

            for (int i = 0; i < node->children.size(); i++) {
                auto& child = node->children[i];
                int lcp = getLCP(child->edgeLabel, remaining);

                if (lcp > 0) {
                    if (lcp == child->edgeLabel.length()) {
                        string newRemaining = remaining.substr(lcp);
                        if (deleteHelper(child, newRemaining)) {
                            if (!child->isEndOfWord && child->children.size() == 1) {
                                auto grandchild = child->children[0];
                                grandchild->edgeLabel = child->edgeLabel + grandchild->edgeLabel;
                                node->children[i] = grandchild;
                            }
                            return true;
                        }
                    }
                    return false;
                }
            }
            return false;
        };

        if (deleteHelper(root, word)) {
            cout << "✓ Deleted: " << word << endl;
            return true;
        }
        cout << "✗ Could not delete: " << word << " (not found)" << endl;
        return false;
    }
};

void demonstratePatricia() {
    cout << "\n========== PATRICIA TREE IMPLEMENTATION ==========" << endl;
    PatriciaTree patricia;

    cout << "\n--- INSERT OPERATIONS ---" << endl;
    patricia.insert("apple");
    patricia.insert("app");
    patricia.insert("application");
    patricia.insert("apply");
    patricia.insert("banana");
    patricia.insert("band");
    patricia.insert("bandana");

    cout << "\n--- SEARCH OPERATIONS ---" << endl;
    patricia.search("apple");
    patricia.search("app");
    patricia.search("appl");
    patricia.search("application");
    patricia.search("grape");
    patricia.search("banana");
    patricia.search("bandana");

    cout << "\n--- DELETE OPERATIONS ---" << endl;
    patricia.deleteWord("app");
    patricia.search("app");
    patricia.search("apple");

    patricia.deleteWord("bandana");
    patricia.search("bandana");
    patricia.search("band");

    patricia.deleteWord("grape");

    cout << "\n--- SEARCH AFTER DELETION ---" << endl;
    patricia.search("apple");
    patricia.search("application");
    patricia.search("app");

    cout << "\n==================================================\n" << endl;
}
