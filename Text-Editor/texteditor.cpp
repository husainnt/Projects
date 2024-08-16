// A Text-Editor in C++ using the Stack Data Structure
#include <iostream>
#include <string>
#include <stack>
#include <fstream>

using namespace std;

class Instruction
{
public:
    string action;
    string text;

    Instruction(const string &a, const string &t)
        : action(a), text(t) {}
};

class TextEditor
{
private:
    string content;
    stack<Instruction> undoStack;
    stack<Instruction> redoStack;

public:
    TextEditor();

    void insertText(const string &text);
    void deleteText(int length);
    void undo();
    void redo();
    void saveToFile(const string &filename);
    void openFromFile(const string &filename);
    void displayContent() const;
};

TextEditor::TextEditor()
{
    content = "";
}

void TextEditor::insertText(const string &text)
{
    content += text;

    undoStack.push(Instruction("INSERT", text));

    while (!redoStack.empty())
        redoStack.pop();
}

void TextEditor::deleteText(int length)
{
    if (length < 0 || length > content.length())
    {
        cout << "Invalid length!" << endl;
        return;
    }

    string deletedText = content.substr(content.length() - length, length);
    content.erase(content.length() - length, length);

    undoStack.push(Instruction("DELETE", deletedText));

    while (!redoStack.empty())
        redoStack.pop();
}

void TextEditor::undo()
{
    if (undoStack.empty())
    {
        cout << "Nothing to undo!" << endl;
        return;
    }

    Instruction lastInstruction = undoStack.top();
    undoStack.pop();

    if (lastInstruction.action == "INSERT")
    {
        content.erase(content.length() - lastInstruction.text.length(), lastInstruction.text.length());
        redoStack.push(Instruction("DELETE", lastInstruction.text));
    }
    else if (lastInstruction.action == "DELETE")
    {
        content += lastInstruction.text;
        redoStack.push(Instruction("INSERT", lastInstruction.text));
    }
}

void TextEditor::redo()
{
    if (redoStack.empty())
    {
        cout << "Nothing to redo!" << endl;
        return;
    }

    Instruction lastInstruction = redoStack.top();
    redoStack.pop();

    if (lastInstruction.action == "INSERT")
    {
        content += lastInstruction.text;
        undoStack.push(Instruction("INSERT", lastInstruction.text));
    }
    else if (lastInstruction.action == "DELETE")
    {
        content.erase(content.length() - lastInstruction.text.length(), lastInstruction.text.length());
        undoStack.push(Instruction("DELETE", lastInstruction.text));
    }
}

void TextEditor::saveToFile(const string &filename)
{
    ofstream outFile(filename);
    if (outFile.is_open())
    {
        outFile << content;
        outFile.close();
        cout << "File saved successfully!" << endl;
    }
    else
    {
        cout << "Error opening file!" << endl;
    }
}

void TextEditor::openFromFile(const string &filename)
{
    ifstream inFile(filename);
    if (inFile.is_open())
    {
        content = "";
        inFile.seekg(0, ios::end);
        size_t size = inFile.tellg();
        inFile.seekg(0);
        content.resize(size);
        inFile.read(&content[0], size);
        inFile.close();
        cout << "File opened successfully!" << endl;
    }
    else
    {
        cout << "Error opening file!" << endl;
    }
}

void TextEditor::displayContent() const
{
    cout << "Current Content:\n"
         << content << endl;
}

int main()
{
    TextEditor editor;
    string command;

    while (true)
    {
        cout << "Enter a command (insert, delete, undo, redo, save, open, exit): ";
        cin >> command;

        if (command == "insert")
        {
            string text;
            cout << "Enter text to insert: ";
            cin.ignore();
            getline(cin, text);
            editor.insertText(text);
        }
        else if (command == "delete")
        {
            int length;
            cout << "Enter length to delete (including spaces): ";
            cin >> length;
            editor.deleteText(length);
        }
        else if (command == "undo")
        {
            editor.undo();
        }
        else if (command == "redo")
        {
            editor.redo();
        }
        else if (command == "save")
        {
            string filename;
            cout << "Enter filename: ";
            cin >> filename;
            editor.saveToFile(filename);
        }
        else if (command == "open")
        {
            string filename;
            cout << "Enter filename: ";
            cin >> filename;
            editor.openFromFile(filename);
        }
        else if (command == "exit")
        {
            break;
        }

        editor.displayContent();
    }

    return 0;
}
