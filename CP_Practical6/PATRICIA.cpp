#include <iostream>
#include <string>
#include <climits>
using namespace std;

// ─────────────────────────────────────────────
//  Utility: extract bit k from a string key
//  Bit 0 = MSB of first character.
// ─────────────────────────────────────────────
static int getBit(const string& key, int bit) {
    int byteIndex = bit / 8;
    int bitIndex  = 7 - (bit % 8);         // MSB-first within each byte
    if (byteIndex >= (int)key.size()) return 0;
    return (key[byteIndex] >> bitIndex) & 1;
}

// Number of bits needed to represent a string
static int keyBits(const string& key) {
    return (int)key.size() * 8;
}

// First bit position where two strings differ
static int firstDifferingBit(const string& a, const string& b) {
    int maxBits = max(keyBits(a), keyBits(b));
    for (int i = 0; i < maxBits; i++) {
        if (getBit(a, i) != getBit(b, i)) return i;
    }
    return maxBits;   // identical up to the shorter length
}

// ─────────────────────────────────────────────
//  PATRICIA Node
// ─────────────────────────────────────────────
struct PatriciaNode {
    string key;         // full key stored at this node
    int    bit;         // bit position this node tests
    PatriciaNode* left;
    PatriciaNode* right;

    PatriciaNode(const string& k, int b)
        : key(k), bit(b), left(nullptr), right(nullptr) {}
};

// ─────────────────────────────────────────────
//  PATRICIA Trie Class
// ─────────────────────────────────────────────
class PatriciaTrie {
private:
    PatriciaNode* root;

    // ── Internal search ─────────────────────
    // Follows bit tests downward until a back-edge is detected.
    // A back-edge is identified by the child's bit index being
    // ≤ the current node's bit index (we are going "up" the tree).
    PatriciaNode* internalSearch(const string& key) {
        if (!root) return nullptr;

        PatriciaNode* prev = root;
        PatriciaNode* cur  = (getBit(key, root->bit) == 0) ? root->left : root->right;

        // If root points to itself (singleton tree), handle directly
        if (!cur) return root;

        while (cur->bit > prev->bit) {
            prev = cur;
            cur  = (getBit(key, cur->bit) == 0) ? cur->left : cur->right;
            if (!cur) break;
        }
        return cur;
    }

public:
    PatriciaTrie() : root(nullptr) {}

    // ── SEARCH ──────────────────────────────
    // Time: O(log n) bit tests + O(L) for the final key comparison
    bool search(const string& key) {
        PatriciaNode* found = internalSearch(key);
        if (!found) return false;
        return found->key == key;
    }

    // ── INSERT ──────────────────────────────
    // 1. Search to find where the key would land.
    // 2. Compute the first differing bit between key and the node found.
    // 3. Walk from root again to find the correct insertion point
    //    (the first node whose bit index exceeds the differing bit).
    // 4. Create a new node and wire it in with back-edges.
    // Time: O(log n) bit tests
    void insert(const string& key) {
        if (!root) {
            // Empty tree: root points to itself
            root = new PatriciaNode(key, -1);
            root->left  = root;
            root->right = root;
            cout << "[PATRICIA] Inserted (root): \"" << key << "\"\n";
            return;
        }

        PatriciaNode* found = internalSearch(key);
        if (found && found->key == key) {
            cout << "[PATRICIA] \"" << key << "\" already exists.\n";
            return;
        }

        // Find first differing bit
        int diffBit = firstDifferingBit(key, found ? found->key : "");

        // Walk from root to find insertion point
        PatriciaNode* prev = root;
        PatriciaNode* cur  = (getBit(key, root->bit) == 0) ? root->left : root->right;

        while (cur && cur->bit > prev->bit && cur->bit < diffBit) {
            prev = cur;
            cur  = (getBit(key, cur->bit) == 0) ? cur->left : cur->right;
        }

        // Create new node; its children point to itself (back-edge) or existing node
        PatriciaNode* newNode = new PatriciaNode(key, diffBit);
        if (getBit(key, diffBit) == 0) {
            newNode->left  = newNode;   // back-edge to self
            newNode->right = cur;
        } else {
            newNode->left  = cur;
            newNode->right = newNode;  // back-edge to self
        }

        // Wire into parent
        if (getBit(key, prev->bit) == 0)
            prev->left  = newNode;
        else
            prev->right = newNode;

        cout << "[PATRICIA] Inserted: \"" << key << "\" at bit " << diffBit << "\n";
    }

    // ── DELETE ──────────────────────────────
    // PATRICIA deletion is the most complex operation because back-edges
    // must be carefully rewired.
    //
    // Cases:
    //   A) The node to delete (D) has a back-edge pointing to itself.
    //      → We can simply unlink D from its parent.
    //
    //   B) D's back-edge points elsewhere (D is referenced by another node R).
    //      → We must:
    //        1. Find R (the node whose back-edge points to D).
    //        2. Replace D's position in the tree with another node (its child).
    //        3. Move D's key into R (overwrite R's key with D's key is WRONG;
    //           instead we replace D with its non-self child and fix R's pointer).
    //
    // For simplicity this implementation handles both cases with a two-pass
    // traversal tracking parent/grandparent relationships.
    bool deleteWord(const string& key) {
        if (!root) {
            cout << "[PATRICIA] Tree is empty.\n";
            return false;
        }

        // ── Special case: single-node tree ──
        if (root->left == root && root->right == root) {
            if (root->key == key) {
                delete root;
                root = nullptr;
                cout << "[PATRICIA] Deleted (last node): \"" << key << "\"\n";
                return true;
            }
            cout << "[PATRICIA] \"" << key << "\" not found.\n";
            return false;
        }

        // ── Find target node and its parent ─
        PatriciaNode* prev   = root;
        PatriciaNode* cur    = (getBit(key, root->bit) == 0) ? root->left : root->right;
        PatriciaNode* parent = root;

        while (cur->bit > prev->bit) {
            parent = prev;
            prev   = cur;
            cur    = (getBit(key, cur->bit) == 0) ? cur->left : cur->right;
        }

        if (cur->key != key) {
            cout << "[PATRICIA] \"" << key << "\" not found.\n";
            return false;
        }

        PatriciaNode* target = cur;   // node to delete

        // ── Case A: back-edge points to self ─
        bool selfRef = (target->left == target || target->right == target);
        if (selfRef) {
            // Which child of parent points to target?
            PatriciaNode* replacement =
                (target->left == target) ? target->right : target->left;

            if (getBit(key, prev->bit) == 0)
                prev->left  = replacement;
            else
                prev->right = replacement;

            // If prev itself was the parent of target via a non-back edge,
            // also fix prev's parent (already handled above since we track parent)
            delete target;
            cout << "[PATRICIA] Deleted: \"" << key << "\"\n";
            return true;
        }

        // ── Case B: another node R holds a back-edge to target ─
        // Find R: the node whose back-edge leads back to target.
        // R is prev in the traversal above (it followed a back-edge to target).
        PatriciaNode* R = prev;

        // Replace target's key slot in the tree with its non-self child.
        // Since target's back-edge goes to R and R ≠ target,
        // we overwrite R's key with target's key — R now represents target's word.
        // Then we remove target's node by re-linking.
        R->key = target->key;   // R inherits the word

        // Now unlink target: replace target's slot in parent with the
        // target's child that is NOT R (the forward child, not the back-edge child).
        PatriciaNode* forwardChild =
            (target->left == R) ? target->right : target->left;

        if (getBit(key, parent->bit) == 0)
            parent->left  = forwardChild;
        else
            parent->right = forwardChild;

        delete target;
        cout << "[PATRICIA] Deleted: \"" << key << "\"\n";
        return true;
    }

    // ── Traversal helper (in-order by bit index) ──
    void printAll(PatriciaNode* node, PatriciaNode* sentinel, int depth = 0) {
        if (!node || node == sentinel) return;
        // PATRICIA is tricky to traverse without loops — simplified display
        cout << string(depth * 2, ' ') << "[bit=" << node->bit << "] \"" << node->key << "\"\n";
    }
};

// ─────────────────────────────────────────────
//  Driver
// ─────────────────────────────────────────────
int main() {
    cout << "\n══════════════════════════════════\n";
    cout << "       PATRICIA TRIE DEMO\n";
    cout << "══════════════════════════════════\n\n";

    PatriciaTrie pt;

    pt.insert("hello");
    pt.insert("help");
    pt.insert("world");
    pt.insert("word");
    pt.insert("hero");
    cout << "\n";

    cout << "Search \"hello\"  : " << (pt.search("hello")  ? "FOUND" : "NOT FOUND") << "\n";
    cout << "Search \"help\"   : " << (pt.search("help")   ? "FOUND" : "NOT FOUND") << "\n";
    cout << "Search \"hero\"   : " << (pt.search("hero")   ? "FOUND" : "NOT FOUND") << "\n";
    cout << "Search \"hell\"   : " << (pt.search("hell")   ? "FOUND" : "NOT FOUND") << "\n";
    cout << "Search \"world\"  : " << (pt.search("world")  ? "FOUND" : "NOT FOUND") << "\n";
    cout << "\n";

    pt.deleteWord("help");
    cout << "Search \"help\" after delete : " << (pt.search("help")  ? "FOUND" : "NOT FOUND") << "\n";
    cout << "Search \"hello\" (unaffected): " << (pt.search("hello") ? "FOUND" : "NOT FOUND") << "\n";
    cout << "\n";

    return 0;
}