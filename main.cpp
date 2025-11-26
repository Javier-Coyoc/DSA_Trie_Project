#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Trie Node
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

      // Recursive delete helper
    bool deleteHelper(TrieNode* node, const string& word, int depth) {
        if (!node) return false;

        if (depth == word.size()) {
            if (!node->isEndOfWord) return false;  
            node->isEndOfWord = false;
            return isEmpty(node);
        }

        int i = word[depth] - 'a';

        if (!deleteHelper(node->children[i], word, depth + 1))
            return false;

        delete node->children[i];
        node->children[i] = nullptr;

        return (!node->isEndOfWord && isEmpty(node));
    }

    bool isEmpty(TrieNode* node) {
        for (int i = 0; i < 26; i++)
            if (node->children[i] != nullptr)
                return false;
        return true;
    }

public:
    Trie() { root = new TrieNode(); }

    //Remove - Calls the delete helper function to delete a characters in the trie
    void remove(const string& word) {
        deleteHelper(root, word, 0);
    }
};

int main() {

    return 0;
}
