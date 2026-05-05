#include <iostream>
#include <iomanip>
using namespace std;

// Forward declarations of demonstration functions
void demonstrateTrie();
void demonstratePatricia();
void demonstrateManacher();

int main() {
    cout << "\n" << string(60, '=') << endl;
    cout << "        CSF303 PRACTICAL 6: ADVANCED ALGORITHMS" << endl;
    cout << string(60, '=') << endl;

    cout << "\nThis program demonstrates three advanced algorithms:" << endl;
    cout << "  1. Trie (Prefix Tree) - Basic Implementation" << endl;
    cout << "  2. PATRICIA Tree (Radix Tree) - Compressed Trie" << endl;
    cout << "  3. Manacher's Algorithm - Longest Palindromic Substring" << endl;

    // Demonstrate Trie
    demonstrateTrie();

    // Demonstrate PATRICIA
    demonstratePatricia();

    // Demonstrate Manacher
    demonstrateManacher();

    cout << "\n" << string(60, '=') << endl;
    cout << "              DEMONSTRATION COMPLETED" << endl;
    cout << string(60, '=') << "\n" << endl;

    return 0;
}
