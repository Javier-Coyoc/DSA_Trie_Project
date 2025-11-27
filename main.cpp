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

//Trie Class
class Trie {
private:
    TrieNode* root;

   // Check if node has zero children
    bool isEmpty(TrieNode* node) {
        for (int i = 0; i < 26; i++)
            if (node->children[i])
                return false;
        return true;
    }

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

    // collect all words starting from a node
    void collect(TrieNode* node, string prefix, vector<string>& out) {
        if (!node) return;
        if (node->isEndOfWord) out.push_back(prefix);

        for (int i = 0; i < 26; i++)
            if (node->children[i])
                collect(node->children[i], prefix + char(i + 'a'), out);
    }

public:
    Trie() { root = new TrieNode(); }

    //Inserts a string individually by each of its characters into the trie
    void insert(const string& word) {
        TrieNode* cur = root;
        for (char c : word) {
            int i = c - 'a';
            if (!cur->children[i])
                cur->children[i] = new TrieNode();
            cur = cur->children[i];
        }
        cur->isEndOfWord = true;
    }

    // Search a full word
    bool search(const string& word) {
        TrieNode* cur = root;
        for (char c : word) {
            int i = c - 'a';
            if (!cur->children[i]) return false;
            cur = cur->children[i];
        }
        return cur->isEndOfWord;
    }

    //Remove - Calls the delete helper function to delete a characters in the trie
    void remove(const string& word) {
        deleteHelper(root, word, 0);
    }

    //Prefix search - Searches through the trie to see if the prefix inserted matches any of the 
    //word's prefixes inside the trie
    vector<string> prefixSearch(const string& prefix) {
        TrieNode* cur = root;

        for (char c : prefix) {
            int i = c - 'a';
            if (!cur->children[i])
                return {}; 
            cur = cur->children[i];
        }

        vector<string> results;
        collect(cur, prefix, results);
        return results;
    }
};

int main() {

    return 0;
}
