#include <stdio.h>
#include <stdlib.h>

struct AVLNode{
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
};
static inline int max(int a, int b)
{
    return a > b ? a: b;
}
int getHeight(struct AVLNode *node)
{
    if (!node)
        return 0;
    return node->height;
}
struct AVLNode* newNode(int key)
{
    struct AVLNode *new_node = malloc(sizeof(struct AVLNode));
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    return new_node;
}
struct AVLNode * rightRotate(struct AVLNode *y)
{
    struct AVLNode *x = y->left;
    struct AVLNode *x_right_child = x->right;
    x->right = y;
    y->left = x_right_child;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}
struct AVLNode * leftRotate(struct AVLNode *x)
{
    struct AVLNode *y = x->right;
    struct AVLNode *y_left_child = y->left;
    y->left = x;
    x->right = y_left_child;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}
int balanceFactor(struct AVLNode *node)
{
    if (!node)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

struct AVLNode *insertNode(struct AVLNode *node, int key)
{
    if (!node)
        return newNode(key);
    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    int bf = balanceFactor(node);
    if (bf > 1 && key < node->left->key)
        return rightRotate(node);
    else if (bf < - 1 && key > node->right->key)
        return leftRotate(node);
    else if (bf > 1 && key > node->left->key){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }else if (bf < -1 && key > node->right->key){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}
struct AVLNode *getMin(struct AVLNode *root)
{
    while (root->left)
        root = root->left;
    return root;
}
struct AVLNode *deleteNode(struct AVLNode *root, int key)
{
    if (!root)
        return NULL;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else{
        if (!(root->left) || !(root->right)){
            struct AVLNode *tmp = root->left ? root->left: root->right;
            if (!tmp){
                tmp = root;
                root = NULL;
            } else
                *root = *tmp;
            free(tmp);
        }else{
            struct AVLNode *tmp = getMin(root->right);
            root->key = tmp->key;
            root->right = deleteNode(root->right, tmp->key);
            free(tmp);
        }
    }
    if (!root)
        return root;
    root->height = max(getHeight(root->right), getHeight(root->left)) + 1;
    int balance = balanceFactor(root);
    if (balance > 1 && balanceFactor(root->left) >= 0)
        return rightRotate(root);
    else if (balance > 1 && balanceFactor(root->left) < 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }else if (balance < - 1 && balanceFactor(root->right) >= 0){
        return leftRotate(root);
    }else if (balance < -1 && balanceFactor(root->right) < 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
void preOrderOutput(struct AVLNode *root)
{
    if (root){
        printf("%d ", root->key);
        preOrderOutput(root->left);
        preOrderOutput(root->right);
    }
}


int main(void)
{
    return 0;
}