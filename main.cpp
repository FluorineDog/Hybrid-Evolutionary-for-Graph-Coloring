
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include "TabuSearch.h"
using std::cerr;
using std::cout;
using std::endl;
using std::vector;

static std::default_random_engine e(67);
std::pair<int, int> localSearch(TabuSearch& engine, int iterBase, int scale,
                                int ID);
using Clock = std::chrono::time_point<std::chrono::system_clock>;
struct {
  Clock begin_time;
  std::string filename;
  int color;
  int seed = 67;
} global;

int main(int argc, char* argv[]) {
#ifdef DOG_DEBUG
  // fake fin for I/O speed
  std::ifstream fin("data/DSJC500.9.col");
  int preset_color_count = 126;
  global.filename = "data/DSJC500.9.col";
#else
  if (argc < 3) {
    cerr << "usage: \n\t" << argv[0] << " <file> <color_count> [rand_seed]"
         << endl;
    exit(-1);
  }
  // fake fin for I/O speed
  std::ifstream fin(argv[1]);
  global.filename = argv[1];
  int preset_color_count = strtol(argv[2], nullptr, 10);
#endif
  if (argc >= 4) {
    global.seed = strtol(argv[3], nullptr, 10);
    e.seed(global.seed);
  }
  global.color = preset_color_count;

  if (global.color > MAX_COLOR_COUNT) {
    cerr << "color limiited exceeded. "  //
         << "Change MAX_COLOR_COUNT("    //
         << MAX_COLOR_COUNT              //
         << ") in CMakeLists.txt "       //
         << endl;
    exit(-1);
  }

  if (POPULATION < 2) {
    cerr << "population must be at least 2. "  //
         << "Change POPULATION("               //
         << MAX_COLOR_COUNT                    //
         << ") in CMakeLists.txt or run.sh"    //
         << endl;
    exit(-1);
  }

  int vertex_count = -1, edge_count;

  std::string line;
  while (std::getline(fin, line)) {
    // this fin will skip ' ' and '\n'
    // see wheel.h for reference

    if (line[0] == 'c') {
      // commnets
      continue;
    } else if (line[0] == 'p') {
      // property
      sscanf(line.c_str(), "%*s%*s%d%d", &vertex_count, &edge_count);
      break;
    } else {
      // not regnogizable
      continue;
    }
  }
  if (vertex_count == -1) {
    cerr << "edge info not found" << endl;
    exit(-1);
  }
  std::cerr << vertex_count;

  if (vertex_count > MAX_VERTEX_COUNT) {
    cerr << "vertex limiited exceeded. "  //
         << "Change MAX_VERTEX_COUNT("    //
         << MAX_VERTEX_COUNT              //
         << ") in CMakeLists.txt "        //
         << endl;
    exit(-1);
  }

  Graph graph(vertex_count, edge_count * 2);
  for (int i = 0; i < edge_count; ++i) {
    char tmp[10];
    int from, to;
    if (!(fin >> tmp >> from >> to)) {
      break;
    }
    --from;
    --to;
    graph.add_edge(from, to);
    graph.add_edge(to, from);
  }
  graph = graph.optimize();
  cerr << "searching " << preset_color_count << endl;
  {
    using namespace std::chrono;
    global.begin_time = system_clock::now();
  }
  vector<TabuSearch> citizens;
  for (int i = 0; i < POPULATION; ++i) {
    citizens.emplace_back(graph, preset_color_count, i);
  }

  int last_worstID = -1;
  for (int iter = 0; iter < 100000000; iter += STRIP) {
    int best[2] = {INF, INF}, worst = 0;
    int bestID[2] = {-1, -1}, worstID = -1;
    for (auto ctz_id : Range(POPULATION)) {
      auto& ctz = citizens[ctz_id];
      int scale = (last_worstID == ctz_id) ? SCALE : 1;
      auto [cost, hist] = localSearch(ctz, iter, scale, ctz_id);
      int best_finder = cost;  // encourage blood
      if (best_finder < best[1]) {
        best[1] = best_finder;
        bestID[1] = ctz_id;
      }
      if (best[1] < best[0]) {
        std::swap(best[1], best[0]);
        std::swap(bestID[1], bestID[0]);
      }
      int worst_finder = cost;
      if (worst_finder >= worst) {
        worst = worst_finder;
        worstID = ctz_id;
      }
    }
    auto& ctz1 = citizens[bestID[0]];
    auto& ctz2 = citizens[bestID[1]];
    citizens[worstID].acceptConfig(std::move(TabuSearch::GPX(ctz1, ctz2, e)));
    last_worstID = worstID;
  }

  return 0;
}

#include <iostream>
[[noreturn]] void output_answer(int iter_count, TabuSearch& eng) {
  using namespace std::chrono;
  Clock end_time = system_clock::now();
  duration<double> duration = end_time - global.begin_time;
  char date_buf[100];
  {
    auto tmp = system_clock::to_time_t(end_time);
    auto tmp_p = localtime(&tmp);
    strftime(date_buf, 100, "%Y-%M-%d %T", tmp_p);
  }
  std::cout                               //
      << date_buf << ", "                 // Date
      << global.filename << ", "          // Instance
      << "HEA(POPULATION=" << POPULATION  // Algorithm
      << "|STRIP=" << STRIP               // Algorithm
      << "|SCALE=" << SCALE               // Algorithm
      << "), "                            // Algorithm
                                          //
      << global.seed << ", "              // RandSeed
      << duration.count() << "s, "        // Duration
      << iter_count << ", "               // IterCount
      << eng.getHistoryCost() << ", "     // Optima
      ;
  auto& colors = eng.getColors();
  std::cout << "(" << global.color << ")";
  for (auto c : colors) {
    std::cout << c << " ";
  }
  std::cout << std::endl;
  exit(-1);
}

// return <curr_best, hist_best>
std::pair<int, int> localSearch(TabuSearch& engine, int iterBase, int scale,
                                int ctz_id) {
  int best = INF;
  for (int iterI = 0; iterI < scale * STRIP; ++iterI) {
    auto iter = iterBase + iterI;
    auto [v, c] = engine.pick_move(iter);
    int old_color = engine.shift(v, c);
    int cost = engine.getCurrentCost();
    best = std::min(cost, best);
    engine.tabu(v, old_color, iter + e() % 10 + cost);
    if (cost == 0) {
      std::cerr                                //
          << "iterBase: " << iterBase << endl  //
          << "iterI: " << iterI << endl        //
          << "success " << endl;
      output_answer(iterBase * POPULATION + ctz_id * STRIP + iterI, engine);
    }
  }
  int hist_best = engine.getHistoryCost();
  if (iterBase % STRIP_NOTIFY == 0) {
    std::cerr                  //
        << "" << ctz_id        //
        << ": " << best        //
        << "<=>" << hist_best  //
        << endl;
  }
  return std::make_pair(best, hist_best);
}


