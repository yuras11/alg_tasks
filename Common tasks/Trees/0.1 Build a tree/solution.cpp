#include <iostream>
#include <fstream>


std::ofstream fout;
std::ifstream fin;

class BTree {
public:
    BTree() : root_(nullptr), nodes_count_(0) {}

    bool Add(int value) {
        if (root_ == nullptr) {
            root_ = new Node(value);
            ++nodes_count_;
            return true;
        }

        Node* current = root_;

        while (current != nullptr) {
            if (current->value == value) {
                return false;
            }

            if (value < current->value) { // left
                if (current->left == nullptr) {
                    current->left = new Node(value);
                    ++nodes_count_;
                    return true;
                }
                current = current->left;
                continue;
            }

            if (value > current->value) { // right
                if (current->right == nullptr) {
                    current->right = new Node(value);
                    ++nodes_count_;
                    return true;
                }
                current = current->right;
                continue;
            }
        }

        return false;
    }

    void Print_Direct() { //INFIX -> left, root, right
        Print_Direct_(root_); // call recursion
    }

    bool Find(int value)  {
        return Find_(root_, value) != nullptr;
    }

    bool Remove(int value) {
        return Remove_Left(root_, value);
    }

//    void Print_Reverse();
//    void Find_Recursion();
private:
    class Node {
    public:
        int value;
        Node* left;
        Node* right;

        Node(int value_): value(value_), left(nullptr), right(nullptr) {}
    };

    void Print_Direct_(Node* current) {
        if (current == nullptr) {
            return;
        }

        fout << current->value << '\n'; // handle current element
        Print_Direct_(current->left); // handle left subtree
        Print_Direct_(current->right); // handle right subtree
    }

    Node* Find_(Node* current, int value)  {
        while (current != nullptr) {
            if (current->value == value) {
                return current;
            }

            if (value < current->value) { // left
                current = current->left;
                continue;
            }

            if (value > current->value) { // right
                current = current->right;
                continue;
            }
        }

        return nullptr;
    }


    bool Remove_Left(Node* current, int value) {
        Node* toRemove = Find_(current, value);

        if (toRemove->left == nullptr && toRemove->right == nullptr) {
            Node* parent = current;
            while (parent->right != toRemove && parent->left != toRemove) {
                if (toRemove->value < parent->value) { // left
                    parent = parent->left;
                    continue;
                }
                if (toRemove->value > parent->value) { // left
                    parent = parent->right;
                    continue;
                }
            }

            if (parent->left == toRemove) {
                parent->left = nullptr;
            }
            if (parent->right == toRemove) {
                parent->right = nullptr;
            }

            delete toRemove;
            return true;
        }

        if (toRemove->left != nullptr && toRemove->right == nullptr) {
            Node* left = toRemove->left;
            toRemove->value = left->value;
            toRemove->left = left->left;
            toRemove->right = left->right;
            delete left;
            return true;
        }

        if (toRemove->left == nullptr && toRemove->right != nullptr) {
            Node* right = toRemove->right;
            toRemove->value = right->value;
            toRemove->left = right->left;
            toRemove->right = right->right;
            delete right;
            return true;
        }


        Node* toReplace = toRemove->left;

        while (toReplace->right != nullptr) {
            toReplace = toReplace->right;
        }

        toRemove->value = toReplace->value;

        return Remove_Left(toRemove->left, toReplace->value);
    }

    Node* root_;
    size_t nodes_count_;
};

int main() {

    BTree tree;
    fin.open("input.txt");
    int value;
    while(!fin.eof())
    {
        fin >> value;
        tree.Add(value);
    }
    fin.close();
    fout.open("output.txt");
    tree.Print_Direct();
    fout.close();
    return 0;
}
