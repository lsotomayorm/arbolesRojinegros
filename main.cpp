#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>
#include "AVL.h"
#include "RedBlackTree.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char** argv){

  // ... CÓDIGO A MEDIR (ej. el bucle de inserción) ...
  // Pruebas con propias mediciones por tipo de arbol
  ifstream in(argv[1]);
  std::vector<int> data;
  data.reserve(1000000);
  for (int x; in >> x; ) data.push_back(x);
  cout << "Leidos: " << data.size() << " numeros\n";
  
  auto start = high_resolution_clock::now();

  AVLTree<int> avl;
  auto t0 = high_resolution_clock::now();
  for (int x : data) avl.insert(x);
  auto t1 = high_resolution_clock::now();
  auto avl_ms = duration_cast<milliseconds>(t1 - t0).count();

  cout << ">> AVLTree <<"<< endl;
  cout << "Tiempo: " << avl_ms << " ms" << endl;
  cout << "Rotaciones = " << avl.getRotationCount() << endl;
  cout << "Altura = " << avl.getTreeHeight() << endl;

  RedBlackTree<int> rb;
  auto r0 = high_resolution_clock::now();
  for (int x : data) rb.insert(x);
  auto r1 = high_resolution_clock::now();
  auto rb_ms = duration_cast<milliseconds>(r1 - r0).count();

  cout << ">> RedBlackTree <<"<< endl;
  cout << "Tiempo: " << rb_ms << " ms" << endl;
  cout << "Rotaciones = " << rb.getRotationCount() << endl;
  cout << "Altura = " << rb.getTreeHeight() << endl;

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);

  std::cout << "Tiempo de ejecución: " << duration.count() << " ms" << std::endl;

  return 0;
}