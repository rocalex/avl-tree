// AVL tree implementation in C++

#include <iostream>
using namespace std;

struct Cell
{
    int key;
    Cell *refs[4];
    int height;
};

int max(int a, int b);

// Calculate height
int height(Cell *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

// New node creation
Cell *new_node(int key)
{
    Cell *node = new Cell();
    node->key = key;
    node->refs[0] = NULL;
    node->refs[1] = NULL;
    node->height = 1;
    return (node);
}

// Rotate right
Cell *right_rotate(Cell *y)
{
    Cell *x = y->refs[0];
    Cell *T2 = x->refs[1];
    x->refs[1] = y;
    y->refs[0] = T2;
    y->height = max(height(y->refs[0]),
                    height(y->refs[1])) +
                1;
    x->height = max(height(x->refs[0]),
                    height(x->refs[1])) +
                1;
    return x;
}

// Rotate left
Cell *left_rotate(Cell *x)
{
    Cell *y = x->refs[1];
    Cell *T2 = y->refs[0];
    y->refs[0] = x;
    x->refs[1] = T2;
    x->height = max(height(x->refs[0]),
                    height(x->refs[1])) +
                1;
    y->height = max(height(y->refs[0]),
                    height(y->refs[1])) +
                1;
    return y;
}

// Get the balance factor of each node
int get_balance_factor(Cell *N)
{
    if (N == NULL)
        return 0;
    return height(N->refs[0]) -
           height(N->refs[1]);
}

// Insert a node
Cell *insert_node(Cell *node, int key)
{
    // Find the correct postion and insert the node
    if (node == NULL)
        return (new_node(key));
    if (key < node->key)
        node->refs[0] = insert_node(node->refs[0], key);
    else if (key > node->key)
        node->refs[1] = insert_node(node->refs[1], key);
    else
        return node;

    // Update the balance factor of each node and
    // balance the tree
    node->height = 1 + max(height(node->refs[0]),
                           height(node->refs[1]));
    int balanceFactor = get_balance_factor(node);
    if (balanceFactor > 1)
    {
        if (key < node->refs[0]->key)
        {
            return right_rotate(node);
        }
        else if (key > node->refs[0]->key)
        {
            node->refs[0] = left_rotate(node->refs[0]);
            return right_rotate(node);
        }
    }
    if (balanceFactor < -1)
    {
        if (key > node->refs[1]->key)
        {
            return left_rotate(node);
        }
        else if (key < node->refs[1]->key)
        {
            node->refs[1] = right_rotate(node->refs[1]);
            return left_rotate(node);
        }
    }
    return node;
}

// Node with minimum value
Cell *node_with_mimum_value(Cell *node)
{
    Cell *current = node;
    while (current->refs[0] != NULL)
        current = current->refs[0];
    return current;
}

// Delete a node
Cell *delete_node(Cell *root, int key)
{
    // Find the node and delete it
    if (root == NULL)
        return root;
    if (key < root->key)
        root->refs[0] = delete_node(root->refs[0], key);
    else if (key > root->key)
        root->refs[1] = delete_node(root->refs[1], key);
    else
    {
        if ((root->refs[0] == NULL) ||
            (root->refs[1] == NULL))
        {
            Cell *temp = root->refs[0] ? root->refs[0] : root->refs[1];
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            Cell *temp = node_with_mimum_value(root->refs[1]);
            root->key = temp->key;
            root->refs[1] = delete_node(root->refs[1],
                                     temp->key);
        }
    }

    if (root == NULL)
        return root;

    // Update the balance factor of each node and
    // balance the tree
    root->height = 1 + max(height(root->refs[0]),
                           height(root->refs[1]));
    int balanceFactor = get_balance_factor(root);
    if (balanceFactor > 1)
    {
        if (get_balance_factor(root->refs[0]) >= 0)
        {
            return right_rotate(root);
        }
        else
        {
            root->refs[0] = left_rotate(root->refs[0]);
            return right_rotate(root);
        }
    }
    if (balanceFactor < -1)
    {
        if (get_balance_factor(root->refs[1]) <= 0)
        {
            return left_rotate(root);
        }
        else
        {
            root->refs[1] = right_rotate(root->refs[1]);
            return left_rotate(root);
        }
    }
    return root;
}

// Print the tree
void print_tree(Cell *root, string indent, bool last)
{
    if (root != nullptr)
    {
        cout << indent;
        if (last)
        {
            cout << "R----";
            indent += "   ";
        }
        else
        {
            cout << "L----";
            indent += "|  ";
        }
        cout << root->key << endl;
        print_tree(root->refs[0], indent, false);
        print_tree(root->refs[1], indent, true);
    }
}

int main()
{
    Cell *root = NULL;
    root = insert_node(root, 33);
    root = insert_node(root, 13);
    root = insert_node(root, 53);
    root = insert_node(root, 9);
    root = insert_node(root, 21);
    root = insert_node(root, 61);
    root = insert_node(root, 8);
    root = insert_node(root, 11);
    print_tree(root, "", true);
    root = delete_node(root, 13);
    cout << "After deleting " << endl;
    print_tree(root, "", true);
    return 0;
}
