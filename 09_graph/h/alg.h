#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "graph.h"
#include "node.h"
#include <vector>

class BFS {
  const Graph &graph;

public:
  BFS(const Graph &agraph);
  bool connected(Node *begin, Node *end);
};

class DFS {
  const Graph &graph;
  std::set<Node *> visited;
  bool connected(Node *begin, Node *end, int depth);

public:
  DFS(const Graph &agraph) : graph(agraph) {}
  bool connected(Node *begin, Node *end);
};
void writeDisjointoGraphs(const Graph &graph);

struct MarkedNode {
  Node *node;
  int mark;
  Node *prev;
  MarkedNode(Node *anode = 0, int amark = 0, Node *aprev = 0);
};

class PriorityQueue {
  std::vector<MarkedNode> nodes;

public:
  MarkedNode pop();
  void push(Node *node, int mark, Node *prev);
  bool empty() const;
};

class Way {
  std::vector<Node> nodes;
  int length;
  Way() : length(-1) {};
};

#endif
