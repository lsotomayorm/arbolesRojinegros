#include <iostream>
#include <chrono>
#include "AVL.h"
#include "RedBlackTree.h"

using namespace std::chrono;

int main(){
  auto start = high_resolution_clock::now();

  // ... CÓDIGO A MEDIR (ej. el bucle de inserción) ...
  AVLTree<int>* avltree = new AVLTree<int>;
  avltree->insert(4);
  avltree->insert(2);
  avltree->insert(6);
  avltree->insert(1);
  avltree->insert(3);
  avltree->insert(5);
  avltree->insert(7);

  std::cout<< "Contador de Rotaciones: " << avltree->getRotationCount() <<std::endl;

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);

  std::cout << "Tiempo de ejecución: " << duration.count() << " ms" << std::endl;

  return 0;
}