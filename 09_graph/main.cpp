#include "./h/alg.h"
#include "./h/graph.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Запуск: FindDisjointoGraphs inf.txt" << endl;
  }
  string inFilename(argv[1]);
  try {
    Graph g(inFilename);
    cout << "Граф прочитанный из файла: \n" << g;
    cout << endl;
    writeDisjointoGraphs(g);
  } catch (GraphException &e) {
    cout << "Не удалось создать граф" << endl;
  }

  return 0;
}
