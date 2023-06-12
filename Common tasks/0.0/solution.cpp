#include <iostream>
#include <fstream>

class BTree {
public:
    class Node {
    public:
        long long value;
        Node* left;
        Node* right;

        Node(long long value_): value(value_), left(nullptr), right(nullptr) {}
    };

    Node* root_;
    size_t nodes_count_;
    BTree() : root_(nullptr), nodes_count_(0) {}

    bool Add(long long value) {
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
        std::cout << std::endl;
    }

    bool Find(int value)  {
        return Find_(root_, value) != nullptr;
    }

    long long FindSum(Node* root)
    {
        if (root == nullptr)
        {
            return 0;
        }
        return (root->value + FindSum(root->left) + FindSum(root->right));
    }


private:
    void Print_Direct_(Node* current) {
        if (current == nullptr) {
            return;
        }

        Print_Direct_(current->left); // handle left subtree
        std::cout << current->value << " "; // handle current element
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
};

int main()
{
    BTree tree;
    std::ifstream fin;
    std::ofstream fout;
    std::string inputPath = "input.txt";
    std::string outputPath = "output.txt";
    fin.open(inputPath);
    if (fin.is_open())
    {
        long long a = 0;
        while (!fin.eof())
        {
            fin >> a;
            tree.Add(a);
        }
    }
    fin.close();
    fout.open(outputPath);
    if(fout.is_open())
    {
        fout << tree.FindSum(tree.root_);
    }
    fout.close();
    return 0;
}
