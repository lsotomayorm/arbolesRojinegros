#include <iostream>
#include <algorithm> // Para std::max
#include <string>

template <typename T>
struct NodeAVL{
  T key;
  NodeAVL *left;
  NodeAVL *right;
  int height;
};

template <typename T>
class AVLTree{
private:
  NodeAVL<T> *root;
  long long rotation_count = 0;

  int height(NodeAVL<T> *N){
    if(!N) // Modificado
      return 0;
    return N->height;
  }

  NodeAVL<T> *newNode(T key){
    NodeAVL<T> *node = new NodeAVL<T>();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1; 
    return (node);
  }

  NodeAVL<T> *rightRotate(NodeAVL<T> *y){
    NodeAVL<T> *x = y->left;
    NodeAVL<T> *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    rotation_count++;

    return x;
  }

  NodeAVL<T> *leftRotate(NodeAVL<T> *x){
    NodeAVL<T> *y = x->right;
    NodeAVL<T> *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    rotation_count++;

    return y;
  }

  int getBalance(NodeAVL<T> *N){
    if(!N) // Modificado
      return 0;
    return height(N->left) - height(N->right);
  }

  NodeAVL<T> *insert(NodeAVL<T> *node, T key){
    if(!node) // Modificado
      return (newNode(key));

    if(key < node->key)
      node->left = insert(node->left, key);
    else if(key > node->key)
      node->right = insert(node->right, key);
    else
      return node;

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Caso LL
    if(balance > 1 && key < node->left->key)
      return rightRotate(node);

    // Caso RR
    if(balance < -1 && key > node->right->key)
      return leftRotate(node);

    // Caso LR
    if(balance > 1 && key > node->left->key){
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }

    // Caso RL
    if(balance < -1 && key < node->right->key){
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }

    return node;
  }

  bool search(NodeAVL<T> *node, T key) const {
    if(!node) // Modificado
      return false;
    
    if(node->key == key)
      return true;
    
    if(key < node->key)
      return search(node->left, key);
    else
      return search(node->right, key);
  }

  void freeTree(NodeAVL<T> *node){
    if(node){ // Modificado
      freeTree(node->left);
      freeTree(node->right);
      delete node;
    }
  }

public:
  AVLTree() : root(nullptr) {}
  
  ~AVLTree(){ 
    freeTree(root); 
  }

  void insert(T key){
    root = insert(root, key);
  }

  bool search(T key) const {
    return search(root, key);
  }

  long long getRotationCount() const {
    return rotation_count;
  }

  int getTreeHeight() const {
    return root->height;
  }
};
