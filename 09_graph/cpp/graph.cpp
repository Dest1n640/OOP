#include "../h/graph.h"
#include "../h/node.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

Graph::Graph() {};

Graph::Graph(std::string filename) {
  std::ifstream in(filename);

  if (in.is_open()) {
    std::string col1, col2;
    in >> col1 >> col2;
    while (in >> col1 >> col2) {
      addEdge(col1, col2);
    }
  } else
    throw GraphException();
}

Graph::Graph(std::set<Node *> anodes) {
  for (Node *node : anodes) {
    Node *copy = new Node(node->getName());
    for (Node *neighbour : node->neighbours)
      addEdge(copy->getName(), neighbour->getName());
  }
}

Node *Graph::findNode(std::string name) {
  for (Node::node_iterator it = nodes.begin(); it != nodes.end(); it++) {
    if (name == (*it)->getName())
      return (*it);
  }
  return nullptr;
}

Node::node_iterator Graph::begin() const { return nodes.begin(); }

Node::node_iterator Graph::end() const { return nodes.end(); }

void Graph::addNode(Node *node) {
  if (node == 0 || findNode(node->getName()) != nullptr) {
    throw GraphException();
  }
  nodes.insert(node);
}

void Graph::removeNode(Node *node) {
  if (nodes.find(node) == nodes.end())
    throw GraphException();

  nodes.erase(node);
  for (Node::node_iterator it = nodes.begin(); it != nodes.end(); it++)
    (*it)->removeNeighbour(node);
}

void Graph::addEdge(Node *begin, Node *end) {
  if (nodes.find(begin) == nodes.end() || nodes.find(end) == nodes.end())
    throw GraphException();
  begin->addNeighbour(end);
  end->addNeighbour(begin);
}

void Graph::addEdge(std::string begin, std::string end) {
  Node *n1 = new Node(begin);
  Node *n2 = new Node(end);
  try {
    addNode(n1);
  } catch (GraphException &e) {
    n1 = findNode(n1->getName());
  }
  try {
    addNode(n2);
  } catch (GraphException &e) {
    n2 = findNode(n2->getName());
  }
  addEdge(n1, n2);
}
void Graph::removeEdge(Node *begin, Node *end) {
  if (nodes.find(begin) == nodes.end() || nodes.find(end) == nodes.end())
    throw GraphException();
  begin->removeNeighbour(end);
  end->removeNeighbour(begin);
}

std::ostream &operator<<(std::ostream &out, const Graph &graph) {
  out << "Graph: " << std::endl;
  for (Node::node_iterator it = graph.begin(); it != graph.end(); it++) {
    out << "    " << (**it);
  }
  return out;
}

void Graph::writeGraphToFile(std::ostream &out) const {
  out << std::setw(7) << std::left << "Source" << std::setw(7) << std::left
      << "Target" << std::endl;
  for (Node *node : nodes) {
    for (Node *neighbour : node->neighbours) {
      out << std::setw(7) << std::left << node->getName() << std::setw(6)
          << std::left << neighbour->getName() << std::endl;
    }
  }
}
