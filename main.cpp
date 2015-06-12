#include <iostream>
#include "stdio.h"
#include <sstream>

using namespace std;

struct Node
{
    Node(Node* left, Node* right, Node* parrent, unsigned long key, unsigned long value) : _left(left), _right(right), _parrent(parrent), _key(key), _value(value) { }

    ~Node()
    {
        if (_left)
            delete _left;
        if (_right)
            delete _right;
    }
    unsigned long _key;
    unsigned long _value;
    Node* _left = nullptr;
    Node* _right = nullptr;
    Node* _parrent = nullptr;
    void Invert()
    {
        Node* temp = _left;
        _left = _right;
        _right = temp;
        if (_left)
            _left->Invert();
        if (_right)
            _right->Invert();
    }

    std::string ToString()
    {
        stringstream ss;
        ss << "Key: " << _key << " Value: " << _value;
        if (_left || _right)
        {
            ss << "     (";
            if (_left)
                ss << "Left key: " << _left->_key;
            if (_left && _right)
                ss << " | ";
            if (_right)
                ss << "Right key: " << _right->_key;
            ss << ")";
        }
        return ss.str().c_str();
    }

    void Insert(unsigned long key, unsigned long value)
    {
        if (key > _key)
        {
            if (_right)
                _right->Insert(key, value);
            else
                _right = new Node(nullptr, nullptr, this, key, value);
        }
        else
        {
            if (_left)
                _left->Insert(key, value);
            else
                _left = new Node(nullptr, nullptr, this, key, value);
        }
    }

};

struct Tree
{
    Tree() { }
    ~Tree()
    {
        if (root)
            delete root;
    }

    void Insert(unsigned long key, unsigned long value)
    {
        if (root)
            root->Insert(key, value);
        else
            root = new Node(nullptr, nullptr, nullptr, key, value);
    }

    void Invert()
    {
        if (root)
            root->Invert();
    }

    Node* root = nullptr;

};

int main()
{
    srand(time(nullptr));
    Tree* tree = new Tree();
    for (unsigned short i = 0; i < 50; ++i)
        tree->Insert(rand() % 1000 + 1, rand() % 1000 + 1);
    cout << "Tree is now filled with 50 random keys and values" << endl;
    cout << "Press W,A,D to move up, left, right Or press I to invert the tree Or X to exit" << endl;

    char c;
    Node* current = tree->root;
    cout << current->ToString() << endl;
    while (true)
    {
        do
            c = getchar();
        while (isspace(c));
        switch (tolower(c))
        {
            case 'w':
                if (current->_parrent)
                    current = current->_parrent;
                break;
            case 'a':
                if (current->_left)
                    current = current->_left;
                break;
            case 'd':
                if (current->_right)
                    current = current->_right;
                break;
            case 'i':
                tree->Invert();
                break;
            case 'x':
                delete tree;
                return 0;
            default:
                break;
        }

        if (current)
            cout << current->ToString() << endl;
    }

    delete tree;

    return 0;
}
