#include "../h/node.h"
#include <iostream>

const std::string &Node::getName() const { return name; }

Node::node_iterator Node::nb_begin() const { return neighbours.begin(); }

Node::node_iterator Node::nb_end() const { return neighbours.end(); }

void Node::addNeighbour(Node *neighbour) {
  if (neighbour == 0)
    throw NodeException();
  neighbours.insert(neighbour);
}

void Node::removeNeighbour(Node *neighbour) {
  if (neighbour == 0)
    throw NodeException();
  neighbours.erase(neighbour);
}

std::ostream &operator<<(std::ostream &out, const Node &node) {
  out << "Node {" << node.getName() << "} : {";
  for (Node::node_iterator it = node.nb_begin(); it != node.nb_end(); it++)
    out << (*it)->getName() << ", ";
  out << '}' << std::endl;
  return out;
}
