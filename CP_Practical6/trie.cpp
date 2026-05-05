#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// ─────────────────────────────────────────────
//  Trie Node
// ─────────────────────────────────────────────
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEnd;          // true if this node terminates a stored word
    int passCount;       // how many words pass through this node (for safe deletion)

    TrieNode() : isEnd(false), passCount(0) {}
};

// ─────────────────────────────────────────────
//  Trie Class
// ─────────────────────────────────────────────
class Trie {
private:
    TrieNode* root;

    // Recursive helper: deletes nodes bottom-up when safe
    bool deleteHelper(TrieNode* node, const string& word, int depth) {
        if (!node) return false;

        // Base case: we have consumed all characters
        if (depth == (int)word.size()) {
            if (!node->isEnd) return false;   // word was never inserted
            node->isEnd = false;
            node->passCount--;
            // Safe to delete this node if no children remain
            return node->children.empty();
        }

        char ch = word[depth];
        auto it = node->children.find(ch);
        if (it == node->children.end()) return false;  // word not present

        bool shouldDeleteChild = deleteHelper(it->second, word, depth + 1);

        if (shouldDeleteChild) {
            delete it->second;
            node->children.erase(it);
        }

        node->passCount--;
        // Current node can be deleted if it is no longer an end marker
        // and has no remaining children
        return !node->isEnd && node->children.empty();
    }

public:
    Trie() { root = new TrieNode(); }

    // ── INSERT ──────────────────────────────
    // Walk down the trie, creating nodes as needed.
    // Time:  O(L)  where L = length of word
    // Space: O(L)  worst case (entirely new branch)
    void insert(const string& word) {
        TrieNode* cur = root;
        cur->passCount++;

        for (char ch : word) {
            if (cur->children.find(ch) == cur->children.end()) {
                cur->children[ch] = new TrieNode();
            }
            cur = cur->children[ch];
            cur->passCount++;
        }
        cur->isEnd = true;
        cout << "[Trie] Inserted: \"" << word << "\"\n";
    }

    // ── SEARCH ──────────────────────────────
    // Follow each character; return true only if the final node is an end marker.
    // Time:  O(L)
    // Space: O(1)
    bool search(const string& word) {
        TrieNode* cur = root;
        for (char ch : word) {
            auto it = cur->children.find(ch);
            if (it == cur->children.end()) return false;
            cur = it->second;
        }
        return cur->isEnd;
    }

    // ── PREFIX SEARCH ───────────────────────
    // Returns true if any stored word starts with the given prefix.
    // Time:  O(L)
    bool startsWith(const string& prefix) {
        TrieNode* cur = root;
        for (char ch : prefix) {
            auto it = cur->children.find(ch);
            if (it == cur->children.end()) return false;
            cur = it->second;
        }
        return true;
    }

    // ── DELETE ──────────────────────────────
    // Uses the recursive helper above to clean up nodes bottom-up.
    // Only nodes that are no longer needed (not an end of another word,
    // no remaining children) are freed.
    // Time:  O(L)
    bool deleteWord(const string& word) {
        if (!search(word)) {
            cout << "[Trie] \"" << word << "\" not found — nothing deleted.\n";
            return false;
        }
        deleteHelper(root, word, 0);
        cout << "[Trie] Deleted: \"" << word << "\"\n";
        return true;
    }

    ~Trie() {
        // BFS/DFS cleanup omitted for brevity; in production use a proper destructor
    }
};

// ─────────────────────────────────────────────
//  Driver
// ─────────────────────────────────────────────
int main() {
    cout << "══════════════════════════════════\n";
    cout << "          TRIE DEMO\n";
    cout << "══════════════════════════════════\n\n";

    Trie trie;

    // Insert
    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");
    trie.insert("apt");
    trie.insert("bat");
    trie.insert("ball");
    cout << "\n";

    // Search
    cout << "Search \"app\"         : " << (trie.search("app")         ? "FOUND" : "NOT FOUND") << "\n";
    cout << "Search \"apple\"       : " << (trie.search("apple")       ? "FOUND" : "NOT FOUND") << "\n";
    cout << "Search \"ap\"          : " << (trie.search("ap")          ? "FOUND" : "NOT FOUND") << "\n";
    cout << "StartsWith \"app\"     : " << (trie.startsWith("app")     ? "YES"   : "NO")        << "\n";
    cout << "StartsWith \"ba\"      : " << (trie.startsWith("ba")      ? "YES"   : "NO")        << "\n";
    cout << "StartsWith \"xyz\"     : " << (trie.startsWith("xyz")     ? "YES"   : "NO")        << "\n";
    cout << "\n";

    // Delete
    trie.deleteWord("app");
    cout << "Search \"app\" after delete : " << (trie.search("app")   ? "FOUND" : "NOT FOUND") << "\n";
    cout << "Search \"apple\" (unaffected): " << (trie.search("apple") ? "FOUND" : "NOT FOUND") << "\n";

    trie.deleteWord("xyz");   // should report not found
    cout << "\n";

    return 0;
}