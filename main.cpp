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

//CLI interface
int main() {
    Trie trie;

    //Dataset filled with Programming keywords
    vector<string> keywords = {
        "int","float","double","char","class","struct",
        "switch","case","for","while","do","break","continue",
        "return","public","private","protected","this","static",
        "new","delete","include","using","namespace",
        "void","bool","true","false","default"
    };

    for (string kw : keywords) trie.insert(kw);

    int choice;
    string input;

    while (true) {
        cout << "\n---- TRIE PREFIX ANALYTICS ----\n";
        cout << "1. Insert word\n";
        cout << "2. Search word\n";
        cout << "3. Delete word\n";
        cout << "4. Prefix Search\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter word to insert: ";
            cin >> input;
            trie.insert(input);
            cout << "Inserted.\n";
            break;

        case 2:
            cout << "Enter word to search: ";
            cin >> input;
            cout << (trie.search(input) ? "FOUND\n" : "NOT FOUND\n");
            break;

        case 3:
            cout << "Enter word to delete: ";
            cin >> input;
            trie.remove(input);
            cout << "Deleted (if existed).\n";
            break;

        case 4:
            cout << "Enter prefix: ";
            cin >> input;
            {
                vector<string> results = trie.prefixSearch(input);

                cout << "\nMatches: " << results.size() << "\n";
                for (const string& w : results)
                    cout << " - " << w << "\n";
            }
            break;

        case 5:
            return 0;

        default:
            cout << "Invalid option.\n";
        }
    }
}
