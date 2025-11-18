#include <iostream>
using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
    }
};

class Trie {
private:
    TrieNode* root;

    // Helper function for deletion
    bool deleteHelper(TrieNode* node, const string& key, int depth) {
        if (!node)
            return false;

        // Base case: end of word
        if (depth == key.size()) {
            if (!node->isEndOfWord)
                return false;  // word not found

            node->isEndOfWord = false;

            // If node has no children, it can be deleted
            return isEmpty(node);
        }

        int index = key[depth] - 'a';
        if (!deleteHelper(node->children[index], key, depth + 1))
            return false;

        // Delete the child node
        delete node->children[index];
        node->children[index] = nullptr;

        // Return true if no children & not end of another word
        return !node->isEndOfWord && isEmpty(node);
    }

    bool isEmpty(TrieNode* node) {
        for (int i = 0; i < 26; i++)
            if (node->children[i] != nullptr)
                return false;
        return true;
    }

public:
    Trie() { root = new TrieNode(); }

    // Delete a word
    void remove(const string& key) {
        deleteHelper(root, key, 0);
    }
};

int main() {

    return 0;
}
