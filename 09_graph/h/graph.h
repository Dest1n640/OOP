#ifndef _GRAPH_H
#define _GRAPH_H

#include "./node.h"

class GraphException {};

class Graph {
  std::set<Node *> nodes;

public:
  Graph();
  Graph(std::string filename);
  Graph(std::set<Node *> anodes);
  void addNode(Node *node);
  Node *findNode(std::string name);
  void removeNode(Node *node);
  void addEdge(Node *begin, Node *end);
  void addEdge(std::string begin, std::string end);
  void removeEdge(Node *begin, Node *end);
  Node::node_iterator begin() const;
  Node::node_iterator end() const;
  friend std::ostream &operator<<(std::ostream &out, const Graph &graph);
  void writeGraphToFile(std::ostream &out) const;
};

#endif
