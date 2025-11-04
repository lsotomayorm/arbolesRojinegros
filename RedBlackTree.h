#include <iostream>
#include <string>

enum Color { RED, BLACK };

template <typename T>
struct NodeRBT{
  T key;
  NodeRBT *parent;
  NodeRBT *left;
  NodeRBT *right;
  Color color;
};

template <typename T>
class RedBlackTree{
private:
  NodeRBT<T> *root;
  NodeRBT<T> *NIL; // Centinela

  void leftRotate(NodeRBT<T> *x){
    NodeRBT<T> *y = x->right;
    x->right = y->left;
    
    if(y->left != NIL){
      y->left->parent = x;
    }
    
    y->parent = x->parent;
    
    if(!x->parent) // Modificado
      this->root = y;
    else if(x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
    
    y->left = x;
    x->parent = y;
  }

  void rightRotate(NodeRBT<T> *x){
    NodeRBT<T> *y = x->left;
    x->left = y->right;
    
    if(y->right != NIL){
      y->right->parent = x;
    }
    
    y->parent = x->parent;
    
    if(!x->parent) // Modificado
      this->root = y;
    else if(x == x->parent->right)
      x->parent->right = y;
    else
      x->parent->left = y;
    
    y->right = x;
    x->parent = y;
  }

  void insertFixup(NodeRBT<T> *k){
    NodeRBT<T> *u; 
    
    while(k->parent->color == RED){
      if(k->parent == k->parent->parent->right){ 
        u = k->parent->parent->left; 
        
        if(u->color == RED){
          u->color = BLACK;
          k->parent->color = BLACK;
          k->parent->parent->color = RED;
          k = k->parent->parent;
        } else {
          if(k == k->parent->left){
            k = k->parent;
            rightRotate(k);
          }
          k->parent->color = BLACK;
          k->parent->parent->color = RED;
          leftRotate(k->parent->parent);
        }
      } else {
        u = k->parent->parent->right; 

        if(u->color == RED){
          u->color = BLACK;
          k->parent->color = BLACK;
          k->parent->parent->color = RED;
          k = k->parent->parent;
        } else {
          if(k == k->parent->right){
            k = k->parent;
            leftRotate(k);
          }
          k->parent->color = BLACK;
          k->parent->parent->color = RED;
          rightRotate(k->parent->parent);
        }
      }
      if(k == root)
        break;
    }
    root->color = BLACK;
  }

  bool search(NodeRBT<T> *node, T key) const {
    if(node == NIL) // Debe ser NIL
      return false;

    if(key == node->key)
      return true;
    
    if(key < node->key)
      return search(node->left, key);
    else
      return search(node->right, key);
  }

  void freeTree(NodeRBT<T> *node){
    if(node != NIL){ // Debe ser NIL
      freeTree(node->left);
      freeTree(node->right);
      delete node;
    }
  }

public:
  RedBlackTree(){
    NIL = new NodeRBT<T>;
    NIL->color = BLACK;
    NIL->left = nullptr;
    NIL->right = nullptr;
    NIL->parent = nullptr;
    root = NIL;
  }

  ~RedBlackTree(){
    freeTree(this->root);
    delete NIL;
  }

  void insert(T key){
    NodeRBT<T> *node = new NodeRBT<T>;
    node->key = key;
    node->left = NIL;
    node->right = NIL;
    node->parent = nullptr;
    node->color = RED; 

    NodeRBT<T> *y = nullptr;
    NodeRBT<T> *x = this->root;

    while(x != NIL){ // Debe ser NIL
      y = x;
      if(node->key < x->key)
        x = x->left;
      else
        x = x->right;
    }

    node->parent = y;
    if(!y) // Modificado
      root = node;
    else if(node->key < y->key)
      y->left = node;
    else
      y->right = node;

    if(!node->parent){ // Modificado
      node->color = BLACK;
      return;
    }

    if(!node->parent->parent) // Modificado
      return;

    insertFixup(node);
  }

  bool search(T key) const {
    return search(this->root, key);
  }
};
