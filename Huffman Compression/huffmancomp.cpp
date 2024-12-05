#include <bits/stdc++.h>
using namespace std;
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
class TreeNode
{
public:
    char data;
    int freq;
    TreeNode *left;
    TreeNode *right;

    TreeNode(char d, int f)
    {
        this->data = d;
        this->freq = f;
        this->left = nullptr;
        this->right = nullptr;
    }
};
class Compare
{
public:
    bool operator()(TreeNode *a, TreeNode *b)
    {
        return a->freq > b->freq;
    }
};

class Huffman
{
public:
    unordered_map<char, string> E_map;
    unordered_map<string, char> D_map;
    void generateCodes(TreeNode *root, string code);
    void Encode(const string &inp_Fname, const string &op_Fname);
    void Decode(const string &inp_Fname, const string &op_Fname);
};
void Huffman::generateCodes(TreeNode *root, string code)
{
    if (!root)
        return;
    if (!root->left && !root->right)
    {
        E_map[root->data] = code;
        D_map[code] = root->data;
    }

    generateCodes(root->left, code + "0");
    generateCodes(root->right, code + "1");
}
void Huffman::Encode(const string &inp_Fname, const string &op_Fname)
{
    ifstream input(inp_Fname, ios::binary);
    ofstream output(op_Fname, ios::binary);

    if (!input.is_open() || !output.is_open())
    {
        cerr << "Error: Unable to open files." << endl;
        return;
    }
    input.seekg(0, ios::end);
    int originalSize = input.tellg();
    input.seekg(0, ios::beg);
    unordered_map<char, int> freq;
    char ch;
    while (input.get(ch))
    {
        freq[ch]++;
    }
    input.clear();
    input.seekg(0);
    priority_queue<TreeNode *, vector<TreeNode *>, Compare> pq;
    for (auto &pair : freq)
    {
        pq.push(new TreeNode(pair.first, pair.second));
    }

    while (pq.size() > 1)
    {
        TreeNode *left = pq.top();
        pq.pop();
        TreeNode *right = pq.top();
        pq.pop();
        TreeNode *parent = new TreeNode('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }
    TreeNode *root = pq.top();
    generateCodes(root, "");
    int freqSize = freq.size();
    output.write((char *)&freqSize, sizeof(int));
    for (auto &pair : E_map)
    {
        output.write((char *)&pair.first, sizeof(char));
        int codeLength = pair.second.size();
        output.write((char *)&codeLength, sizeof(int));
        output.write(pair.second.c_str(), codeLength);
    }
    string encodedData = "";
    while (input.get(ch))
    {
        encodedData += E_map[ch];
    }
    int extraBits = (8 - (encodedData.size() % 8)) % 8;
    for (int i = 0; i < extraBits; i++)
    {
        encodedData += "0";
    }
    output.write((char *)&extraBits, sizeof(int));
    for (size_t i = 0; i < encodedData.size(); i += 8)
    {
        string byte = encodedData.substr(i, 8);
        char byteChar = stoi(byte, nullptr, 2);
        output.write(&byteChar, sizeof(char));
    }
    output.close();
    input.close();

    ifstream compressedFile(op_Fname, ios::binary);
    compressedFile.seekg(0, ios::end);
    int compressedSize = compressedFile.tellg();
    compressedFile.close();
    double compressionRatio = static_cast<double>(compressedSize) / originalSize;
    double compressionPercentage = (1.0 - compressionRatio) * 100;

    cout << "\nCompression Analysis:" << endl;
    cout << "Original File Size: " << originalSize << " bytes" << endl;
    cout << "Compressed File Size: " << compressedSize << " bytes" << endl;
    cout << fixed << setprecision(2);
    cout << "Compression Ratio: " << compressionRatio << endl;
    cout << "Compression Percentage: " << compressionPercentage << "%" << endl;
}
void Huffman::Decode(const string &inp_Fname, const string &op_Fname)
{
    ifstream input(inp_Fname, ios::binary);
    ofstream output(op_Fname, ios::binary);

    if (!input.is_open() || !output.is_open())
    {
        cerr << "Error: Unable to open files." << endl;
        return;
    }
    int uniqueChars;
    input.read((char *)&uniqueChars, sizeof(int));
    D_map.clear();
    for (int i = 0; i < uniqueChars; i++)
    {
        char character;
        int codeLength;
        input.read(&character, sizeof(char));
        input.read((char *)&codeLength, sizeof(int));
        char *code = new char[codeLength + 1];
        input.read(code, codeLength);
        code[codeLength] = '\0';
        D_map[string(code)] = character;
        delete[] code;
    }
    int extraBits;
    input.read((char *)&extraBits, sizeof(int));
    string binaryData = "";
    char byte;
    while (input.read(&byte, sizeof(char)))
    {
        binaryData += bitset<8>(static_cast<unsigned char>(byte)).to_string();
    }
    binaryData = binaryData.substr(0, binaryData.size() - extraBits);
    string code = "";
    for (char bit : binaryData)
    {
        code += bit;
        if (D_map.count(code))
        {
            output.put(D_map[code]);
            code = "";
        }
    }

    input.close();
    output.close();
}

int main()
{
    int n;
    string inp_Fname, op_Fname;
    Huffman h;

    do
    {

        cout << CYAN << "\nHuffman Coding Menu:" << RESET;
        cout << YELLOW << "\n1. Compress a File" << RESET;
        cout << GREEN << "\n2. Decompress a File" << RESET;
        cout << MAGENTA << "\n3. Exit" << RESET;
        cout << BLUE << "\nEnter your choice: " << RESET;
        cin >> n;

        switch (n)
        {
        case 1:
            cout << BLUE << "Enter input file name: " << RESET;
            cin >> inp_Fname;
            cout << BLUE << "Provide a name for the file to be saved as output: " << RESET;
            cin >> op_Fname;
            h.Encode(inp_Fname, op_Fname);
            break;
        case 2:
            cout << BLUE << "Enter compressed file name: " << RESET;
            cin >> inp_Fname;
            cout << BLUE << "Provide a name for the file to be saved as output: " << RESET;
            cin >> op_Fname;
            h.Decode(inp_Fname, op_Fname);
            break;
        case 3:
            cout << RED << "Exiting program. Goodbye!" << RESET << endl;
            break;
        default:
            cout << RED << "Invalid choice. Please try again." << RESET << endl;
        }
    } while (n != 3);

    return 0;
}