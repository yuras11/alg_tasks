#include <iostream>
#include <fstream>

std::ifstream fin;
std::ofstream fout;


class BinaryTree
{
private:
    class Node
    {
    public:
        long long value;
        Node* right;
        Node* left;

        Node (long long value)
        {
            this->value = value;
            this->right = nullptr;
            this->left = nullptr;
        }
    };
    Node* root;
    size_t amountOfNodes;

    void DirectLeftBypass(Node* current)
    {
        if (current == nullptr)
        {
            return;
        }
        fout << current->value << '\n';
        DirectLeftBypass(current->left);
        DirectLeftBypass(current->right);
    }

    bool RemoveRight(Node* current, long long value)
    {
        Node* toDelete = Search(current, value);

        if (toDelete == nullptr)
        {
            return false;
        }

        if (toDelete == root && amountOfNodes == 1)
        {
            root = nullptr;
            delete toDelete;
            return true;
        }

        if (toDelete->left == nullptr && toDelete->right == nullptr)
        {
            Node* parent = current;
            while (parent->right != toDelete && parent->left != toDelete)
            {
                if (value < parent->value)
                {
                    parent = parent->left;
                    continue;
                }
                if (value > parent->value)
                {
                    parent = parent->right;
                    continue;
                }
            }

            if (parent->left == toDelete)
            {
                parent->left = nullptr;
            }
            if (parent->right == toDelete)
            {
                parent->right = nullptr;
            }
            delete toDelete;
            return true;
        }

        if (toDelete->left != nullptr && toDelete->right == nullptr)
        {
            Node* left = toDelete->left;
            toDelete->value = left->value;
            toDelete->left = left->left;
            toDelete->right = left->right;
            delete left;
            return true;
        }

        if (toDelete->left == nullptr && toDelete->right != nullptr)
        {
            Node* right = toDelete->right;
            toDelete->value = right->value;
            toDelete->left = right->left;
            toDelete->right = right->right;
            delete right;
            return true;
        }

        Node* toReplace = toDelete->right;

        if (toReplace->left == nullptr)
        {
            toDelete->value = toReplace->value;
            toDelete->right = toReplace->right;
            delete toReplace;
            return true;
        }

        Node* parentOfReplacement = toDelete->right;

        while (toReplace->left != nullptr)
        {
            toReplace = toReplace->left;
        }

        while (parentOfReplacement->left != toReplace)
        {
            parentOfReplacement = parentOfReplacement->left;
        }

        toDelete->value = toReplace->value;
        parentOfReplacement->left = nullptr;
        if (toReplace->right != nullptr)
        {
            parentOfReplacement->left = toReplace->right;
        }
        delete toReplace;

        return true;
    }

public:
    BinaryTree()
    {
        this->root = nullptr;
        this->amountOfNodes = 0;
    }

    bool Add(long long value)
    {
        if (root == nullptr)
        {
            root = new Node(value);
            amountOfNodes++;
            return true;
        }

        Node* current = root;
        while(current != nullptr)
        {
            if (current->value == value)
            {
                return false;
            }
            if (current->value > value)
            {
                if (current->left == nullptr)
                {
                    current->left = new Node(value);
                    amountOfNodes++;
                    return true;
                }
                current = current->left;
                continue;
            }
            if (current->value < value)
            {
                if (current->right == nullptr)
                {
                    current->right = new Node(value);
                    amountOfNodes++;
                    return true;
                }
                current = current->right;
                continue;
            }
        }
        return false;
    }

    Node* Search(Node* current, long long value)
    {
        while (current != nullptr)
        {
            if (current->value == value)
            {
                return current;
            }
            else if (value < current->value)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        return nullptr;
    }


    void DirectLeftBypass()
    {
        DirectLeftBypass(root);
    }

    bool Delete(long long value)
    {
        return RemoveRight(root, value);
    }

};

int main()
{
    BinaryTree tree;
    fin.open("input.txt");
    long long value;
    long long toDelete;
    fin >> toDelete;
    while (!fin.eof())
    {
        fin >> value;
        tree.Add(value);
    }
    fin.close();
    fout.open("output.txt");
    tree.Delete(toDelete);
    tree.DirectLeftBypass();
    fout.close();
    return 0;
}
