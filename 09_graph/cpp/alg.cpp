#include "../h/alg.h"
#include "../h/graph.h"
#include "../h/node.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

BFS::BFS(const Graph &agraph) : graph(agraph) {};

bool BFS::connected(Node *begin, Node *end) {
  std::queue<Node *> nodes;
  nodes.push(begin);
  std::set<Node *> visited;

  while (!nodes.empty()) {
    Node *next = nodes.front();
    nodes.pop();
    if (end == next) {
      return true;
    }
    visited.insert(next);
    for (Node::node_iterator it = next->nb_begin(); it != next->nb_end(); it++)
      if (visited.find(*it) == visited.end())
        nodes.push(*it);
  }
  return false;
}

void writeDisjointoGraphs(const Graph &graph) {
  BFS bfs(graph);

  std::vector<Graph> disjointGraphs;

  std::set<Node *> visited;
  for (Node::node_iterator s_it = graph.begin(); s_it != graph.end(); s_it++) {
    std::set<Node *> new_graph;
    for (Node::node_iterator e_it = graph.begin(); e_it != graph.end();
         e_it++) {
      if (visited.find(*e_it) == visited.end() &&
          bfs.connected((*s_it), (*e_it))) {
        new_graph.insert((*e_it));
        visited.insert(*e_it);
      }
    }
    if (new_graph.empty())
      continue;
    else
      disjointGraphs.push_back(Graph(new_graph));
  }

  for (int i = 0; i < disjointGraphs.size(); i++) {
    std::string filename("File" + std::to_string(i + 1));
    std::ofstream out(filename);

    if (!out.is_open()) {
      throw GraphException();
    }
    std::cout << "Запись подграфа в файл " << filename << std::endl;
    disjointGraphs[i].writeGraphToFile(out);
  }
  std::cout << "Было найдено " << disjointGraphs.size()
            << " не пересекающихся подграфов" << std::endl;
}

bool DFS::connected(Node *begin, Node *end) {
  visited.clear();
  return connected(begin, end, 0);
}

bool DFS::connected(Node *begin, Node *end, int depth) {
  if (begin == end)
    return true;
  visited.insert(begin);
  for (Node::node_iterator it = begin->nb_begin(); it != begin->nb_end();
       it++) {
    if (visited.find(*it) == visited.end())
      if (connected(*it, end, depth + 1))
        return true;
  }
  return false;
}

MarkedNode::MarkedNode(Node *anode, int amark, Node *aprev)
    : node(anode), mark(amark), prev(aprev) {};

bool PriorityQueue::empty() const { return nodes.empty(); }

MarkedNode PriorityQueue::pop() {
  MarkedNode mn = nodes.back();
  nodes.pop_back();
  return mn;
}

void PriorityQueue::push(Node *node, int mark, Node *prev) {
  std::vector<MarkedNode>::iterator it = nodes.begin();
  MarkedNode mn(node, mark, prev);
  while (it != nodes.end() && mark < it->mark)
    it++;
  if (it == nodes.end())
    nodes.push_back(mn);
  else
    nodes.insert(it, mn);
}
