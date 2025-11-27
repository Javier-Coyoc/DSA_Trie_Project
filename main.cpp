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

    // Insert a word into the trie
    void insert(const string& key) {
        TrieNode* current = root;

        for (char c : key) {
            int index = c - 'a';
            if (!current->children[index])
                current->children[index] = new TrieNode();
            current = current->children[index];
        }

        current->isEndOfWord = true;
    }

    // Search for a word
    bool search(const string& key) {
        TrieNode* current = root;

        for (char c : key) {
            int index = c - 'a';
            if (!current->children[index])
                return false;
            current = current->children[index];
        }

        return current->isEndOfWord;
    }

    // Delete a word
    void remove(const string& key) {
        deleteHelper(root, key, 0);
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
