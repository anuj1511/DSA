#include <iostream>
#include <queue>
using namespace std;

class node {
public:
    int data;
    node* left;
    node* right;
    int height;

    node(int val) {
        data = val;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

int height(node* root) {
    if (root == NULL) {
        return 0;
    }
    return root->height;
}

int getBalanceFactor(node* n) {
    if (n == NULL) {
        return 0;
    }
    return height(n->left) - height(n->right);
}

node* leftRotate(node* root) {
    cout << "Left rotate: " << root->data << endl;
    node* newMid = root->right;
    node* temp = newMid->left;

    // rotation
    newMid->left = root;
    root->right = temp;

    // updating height
    root->height = max(height(root->left), height(root->right)) + 1;
    newMid->height = max(height(newMid->left), height(newMid->right)) + 1;

    // return new root after rotation
    return newMid;
}

node* rightRotate(node* root) {
    cout << "Right rotate: " << root->data << endl;
    node* newMid = root->left;
    node* temp = newMid->right;

    // rotation
    newMid->right = root;
    root->left = temp;

    // updating height
    root->height = max(height(root->left), height(root->right)) + 1;
    newMid->height = max(height(newMid->left), height(newMid->right)) + 1;

    // return new root after rotation
    return newMid;
}

node* insert(node* root, int val) {
    // 1. Normal BST insertion
    if (root == NULL) {
        root = new node(val);
        return root;
    } else if (val < root->data) {
        root->left = insert(root->left, val);
    } else if (val > root->data) {
        root->right = insert(root->right, val);
    } else {
        return root;
    }

    // 2. Updata height of ancestor nodes
    root->height = 1 + max(height(root->left), height(root->right));

    // 3. Get the balance factor of the ancestor
    int balance = getBalanceFactor(root);

    // if balanced then simply return
    if (balance <= 1 && balance >= -1) {
        return root;
    }

    // if current node is unbalanced, then
    // check for 4 cases

    // Left Left case
    if (balance > 1 && val < root->left->data) {
        return rightRotate(root);
    }

    // Right Right case
    if (balance < -1 && val > root->right->data) {
        return leftRotate(root);
    }

    // Left Right case
    if (balance > 1 && val > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left case
    if (balance < -1 && val < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
}

node* inorderSucc(node* root) {
    node* curr = root;
    while (curr && curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}

node* deleteAVL(node* root, int val) {
    // Normal BST deletion
    if (root == NULL) {
        return NULL;
    }

    if (val < root->data) {
        root->left = deleteAVL(root->left, val);
    } else if (val > root->data) {
        root->right = deleteAVL(root->right, val);
    } else {
        // node has no child
        if (root->left == NULL and root->right == NULL) {
            return NULL;
        }

        // node with only one child or no child
        else if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        // node with two children: Get the inorder successor
        // (smallest in the right subtree)
        node* temp = inorderSucc(root->right);

        // Copy the inorder successor's content to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteAVL(root->right, temp->data);
    }

    if (root == NULL) {
        return root;
    }

    // 2. Update height of ancestor node
    root->height = max(height(root->left), height(root->right)) + 1;

    // 3. Get the balance factor of the ancestor
    int balance = getBalanceFactor(root);

    // if balanced then simply return
    if (balance <= 1 && balance >= -1) {
        return root;
    }

    // if current node is unbalanced, then
    // check for 4 cases

    // Left Left case
    if (balance > 1 && getBalanceFactor(root->left) >= 0) {
        return rightRotate(root);
    }

    // Left Right Case
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalanceFactor(root->right) <= 0) {
        return leftRotate(root);
    }

    // Right Left Case
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
}

void levelOrderTraversal(node* root) {
    if (root == NULL) {
        return;
    }

    queue<node*> q;
    q.push(root);
    q.push(NULL);

    while (!q.empty()) {
        node* curr = q.front();
        q.pop();

        if (curr) {
            cout << curr->data << " ";
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        } else if (!q.empty()) {
            q.push(NULL);
            cout << endl;
        }
    }
}

/*
    input: 14 17 11 7 53 4 13 12 8 60 19 16 20

    AVL Tree:
                             14
                        /         \
                    11                19
                 /      \           /      \
                7        12       17        53
              /   \        \     /        /   \
             4     8        13  16       20    60
 */

void inorder(node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(node* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);
    fflush(stdout);
    preorder(root->left);
    preorder(root->right);
}

int main() {
    node* root = NULL;

    int arr[] = { 14, 17, 11, 7, 53, 4, 13, 12, 8, 60, 19, 16, 20 };
    // int arr[] = {9, 27, 50, 15, 2, 21, 36}; 

    // char str[5];
    // scanf("%s", &str);
    // // fflush(stdin);

    // int n;
    // scanf("%d", &n);

    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
    }
    cout << "here" << endl;

    levelOrderTraversal(root);

    printf("preorder\n\n");
    preorder(root);
    printf("\n\n");

    printf("inorder\n\n");
    inorder(root);
    printf("\n\n");

    // deleteAVL(root, 12);
    // deleteAVL(root, 13);

    levelOrderTraversal(root);

    // printf("here\n\n");
    // preorder(root);
    // printf("\n\n");

    return 0;
}