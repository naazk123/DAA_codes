#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <bitset>
using namespace std;
class MinHeapNode {
public:
    char data;  // Character
    int freq;   // Frequency of the character
    MinHeapNode* left;   // Left child
    MinHeapNode* right;  // Right child
    MinHeapNode(char data, int freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};
struct compare {
    bool operator()(MinHeapNode* left, MinHeapNode* right) {
        return left->freq > right->freq;  // Min-heap (smallest freq has highest priority)
    }
};
void generateCodes(MinHeapNode* root, string str, unordered_map<char, string> &huffmanCode) {
    if (root == nullptr)
        return;
    if (root->data != '$') {
        huffmanCode[root->data] = str;
    }
    generateCodes(root->left, str + "0", huffmanCode);
    generateCodes(root->right, str + "1", huffmanCode);
}
void buildHuffmanTree(const string &text, unordered_map<char, string> &huffmanCode, MinHeapNode* &root) {
    unordered_map<char, int> freq_map;
    for (char ch : text) {
        freq_map[ch]++;
    }
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
    for (auto pair : freq_map) {
        minHeap.push(new MinHeapNode(pair.first, pair.second));
    }
    while (minHeap.size() > 1) {
        MinHeapNode* left = minHeap.top();
        minHeap.pop();
        MinHeapNode* right = minHeap.top();
        minHeap.pop();
        MinHeapNode* internalNode = new MinHeapNode('$', left->freq + right->freq);
        internalNode->left = left;
        internalNode->right = right;
        minHeap.push(internalNode);
    }
    root = minHeap.top();    // Step 5: Generate the Huffman codes by traversing the tree
    string str = "";
    generateCodes(root, str, huffmanCode);
}
string encode(const string &text, const unordered_map<char, string> &huffmanCode) {
    string encodedString = "";
    for (char ch : text) {
        encodedString += huffmanCode.at(ch);
    }
    return encodedString;
}
string decode(const string &encodedString, MinHeapNode* root) {
    string decodedString = "";
    MinHeapNode* current = root;

    // Traverse the encoded string bit by bit
    for (char bit : encodedString) {
        // Move left if bit is '0', and right if bit is '1'
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        // If we reach a leaf node, append the character to the result
        if (current->left == nullptr && current->right == nullptr) {
            decodedString += current->data;
            current = root;  // Reset to the root of the tree
        }
    }

    return decodedString;
}

int main() {
    string text = "this is an example for huffman encoding";
   
    // Step 1: Build the Huffman Tree and generate Huffman codes
    unordered_map<char, string> huffmanCode;
    MinHeapNode* root = nullptr;
    buildHuffmanTree(text, huffmanCode, root);

    // Step 2: Encode the input text
    string encodedText = encode(text, huffmanCode);
    cout << "Encoded text: " << encodedText << endl;

    // Step 3: Decode the encoded text
    string decodedText = decode(encodedText, root);
    cout << "Decoded text: " << decodedText << endl;

    return 0;
}
