#pragma once
#include <algorithm>
#include <limits>
#include <map>
#include <set>
#include <vector>
#include "graph.h"
#include "defines.h"
using std::make_tuple;
using std::map;
using std::pair;
using std::set;
using std::tuple;
using std::vector;

constexpr int get2shift(int N) {
  int zeros = __builtin_clz(N - 1);
  return 32 - zeros;
}

constexpr int INF = std::numeric_limits<int>::max() / 4;

class EnemyTable {
 public:
  EnemyTable() = default;
  EnemyTable(const EnemyTable&) = delete;
  EnemyTable(EnemyTable&&) = default;
  const int& operator()(int vertex_id, int color_id) const {
    return table(vertex_id, color_id);
  }

  int& operator()(int vertex_id, int color_id) {
    return table(vertex_id, color_id);
  }

  int initBy(const Graph& graph, const vector<int>& colors) {
    m_table.clear();
    int v_count = graph.size();
    m_table.resize(MAX_VERTEX_COUNT * colors.size(), 0);
    int cost = 0;
    for (auto from : graph.vertex_ids()) {
      for (auto to : graph.edges(from)) {
        table(to, colors[from])++;
        if (colors[from] == colors[to]) cost++;
      }
    }
    return cost / 2;
  }

  bool check(const Graph& graph, const vector<int>& colors, int cost) const {
    EnemyTable eng;
    int new_cost = eng.initBy(graph, colors);
    bool tableEq = eng.m_table == this->m_table;
    bool costEq = cost == new_cost;
    return tableEq && costEq;
  }

 private:
  const int& table(int vertex_id, int color_id) const {
    // MAX_VERTEX_COUNT
    // used for cache
    return m_table[color_id * MAX_VERTEX_COUNT + vertex_id];
  }

  int& table(int vertex_id, int color_id) {
    // MAX_VERTEX_COUNT
    // used for cache
    return m_table[color_id * MAX_VERTEX_COUNT + vertex_id];
  }
  vector<int> m_table;
  // int vertex_shift;
};
