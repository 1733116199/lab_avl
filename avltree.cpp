/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file. IMPORTANT: read avltree.h to understand
 * what to do in this lab.
 */
#include "avltree.h"

template<class K, class V>
V AVLTree<K, V>::find(const K &key) const {
    return find(root, key);
}

template<class K, class V>
V AVLTree<K, V>::find(Node *subtree, const K &key) const {
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template<class K, class V>
void AVLTree<K, V>::insert(const K &key, const V &value) {
    insert(root, key, value);
}

template<class K, class V>
void AVLTree<K, V>::insert(Node *&subtree, const K &key, const V &value) {
    /** 
     * TODO: your code here. Make sure the following cases are included:
     * Case 1: subtree is NULL
     * Case 2: (key, value) pair should be inserted into left subtree
     * Case 3: (key, value) pair should be inserted into right subtree
     */
    if (subtree == NULL) {
        subtree = new Node(key, value);
    } else {
        if (key < subtree->key) {
            insert(subtree->left, key, value);
        } else {
            insert(subtree->right, key, value);
        }
    }


    // Rebalance tree after insertion (don't remove this)
    rebalance(subtree);
}

template<class K, class V>
void AVLTree<K, V>::updateHeight(Node *node) {
    // TODO: your code here
    int l = (node->left) ? node->left->height : -1;
    int r = (node->right) ? node->right->height : -1;
    node->height = ((l > r) ? l : r) + 1;
}

template<class K, class V>
void AVLTree<K, V>::rotateLeft(Node *&t) {
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

    Node *newSubRoot = t->right;
    t->right = newSubRoot->left;
    newSubRoot->left = t;
    t = newSubRoot;
    updateHeight(t->left);
    updateHeight(t);
    // TODO: update the heights for t->left and t (in that order)
}

template<class K, class V>
void AVLTree<K, V>::rotateRight(Node *&t) {
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    Node *newSubRoot = t->left;
    t->left = newSubRoot->right;
    newSubRoot->right = t;
    t = newSubRoot;
    updateHeight(t->right);
    updateHeight(t);

    // TODO: your code here
}

template<class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node *&t) {
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

    rotateLeft(t->left);
    rotateRight(t);
    // TODO: your code here
    // HINT: you should make use of the other functions defined in this file,
    // instead of manually changing the pointers again
}

template<class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node *&t) {
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
    // TODO: your code here
}

template<class K, class V>
void AVLTree<K, V>::rebalance(Node *&subtree) {
    /** 
      * TODO: your code here. Make sure the following cases are included:
      * Cases 1-4: the four cases of tree imbalance as discussed in lecture
      * Case 5: the tree is already balanced. You MUST still correctly update
      * subtree's height 
      */
    int l = (subtree->left) ? subtree->left->height : -1;
    int r = (subtree->right) ? subtree->right->height : -1;
    if (r - l > -2 && r - l < 2) {
        return updateHeight(subtree);
    }
    if (r - l >= 2) {
        l = (subtree->right->left) ? subtree->right->left->height : -1;
        r = (subtree->right->right) ? subtree->right->right->height : -1;
        if (r - l < 0) {
            return rotateRightLeft(subtree);
        } else {
            return rotateLeft(subtree);
        }
    } else if (r - l <= -2) {
        l = (subtree->left->left) ? subtree->left->left->height : -1;
        r = (subtree->left->right) ? subtree->left->right->height : -1;
        if (r - l > 0) {
            return rotateLeftRight(subtree);
        } else {
            return rotateRight(subtree);
        }
    }
}

template<class K, class V>
void AVLTree<K, V>::remove(const K &key) {
    remove(root, key);
}

template<class K, class V>
void AVLTree<K, V>::remove(Node *&subtree, const K &key) {
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        /* Reached the node that we need to delete */
        if (subtree->left == NULL && subtree->right == NULL) {
            /* Case 1: Node to remove has no children */
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /**
             * Case 2: Node to remove has two children
             * TODO: your code here. For testing purposes, you
             * should use the PREDECESSOR.
             */
            Node *pred = NULL;
            Node *predParent = subtree;
            for (pred = subtree->left; (pred->right)!=NULL; predParent = pred, pred = pred->right);
            if(pred!=subtree->left){
                predParent->right = pred->left;
            }else{
                predParent->left = pred->left;
            }
            subtree->key = pred->key;
            subtree->value = pred->value;
            delete(pred);

        } else {
            /* Case 3: Node to remove has one child */
            Node *curr = subtree;
            subtree = max(subtree->left, subtree->right);
            delete curr;
        }
        rebalance(subtree);
    }
}

template<class K, class V>
vector<K> AVLTree<K, V>::heap(){
    vector<K> v;
    toHeap(root, 1, v);
    return v;
}

template<class K, class V>
void AVLTree<K, V>::toHeap(AVLTree<K, V>::Node* n, unsigned long rootIndex, vector<K>& v){
    if(n) {
        if (v.size() < rootIndex + 2)
            v.resize(rootIndex + 2, K());
        v[rootIndex] = n->key;
        toHeap(n->left, 2 * rootIndex, v);
        toHeap(n->right, 2 * rootIndex + 1, v);
    }
}