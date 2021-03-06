#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <random>

using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXK = 100 + 5;
const int MAXN = 500 + 5;
int tabuTenure[MAXN][MAXK];
int colorTable[MAXN][MAXK];
int c[MAXN];
int K, n;
int conflict;
int step;
int hisBest;

struct Edge {
  int to;
  int next;
};
Edge edge[(MAXN + 1) * MAXN];
int head[MAXN];
int eCnt;
void addEdge(int u, int v) {
  edge[++eCnt].next = head[u];
  edge[eCnt].to = v;
  head[u] = eCnt;
}

void getInput();
void init();
void makeColorTable();
bool checkRes();

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);
  freopen(argv[1], "r", stdin);
  sscanf(argv[2], "%d", &K);

  getInput();
  init();
  makeColorTable();
  random_device rd;
  default_random_engine R(rd());

  hisBest = INF;

  int mc, mv;
  int tabuMc, tabuMv;
  int tabuBest, nTabuBest;
  int delta, cnt, tabuCnt;

  clock_t begin = clock();
  while (step++ != 900000000) {
    tabuBest = nTabuBest = INF;
    for (int u = 1; u <= n; ++u) {
      if (!colorTable[u][c[u]]) continue;
      for (int k = 0; k < K; ++k) {
        if (k == c[u]) continue;
        delta = colorTable[u][k] - colorTable[u][c[u]];
        if (tabuTenure[u][k] > step) {
          // tabu best
          if (delta < tabuBest) {
            tabuBest = delta;
            tabuMv = u;
            tabuMc = k;
            tabuCnt = 2;
          } else if (delta == tabuBest && !(R() % tabuCnt)) {
            tabuMv = u;
            tabuMc = k;
            ++tabuCnt;
          }
        } else {
          // no_tabu best
          if (delta < nTabuBest) {
            nTabuBest = delta;
            mv = u;
            mc = k;
            cnt = 2;
          } else if (delta == nTabuBest && !(R() % cnt)) {
            mv = u;
            mc = k;
            ++cnt;
          }
        }
      }
    }

    if (nTabuBest == INF) cout << "hehe" << endl;
    // if (tabuBest == INF && nTabuBest == INF) break;
    if (tabuBest < nTabuBest && conflict + tabuBest < hisBest) {
      mc = tabuMc;
      mv = tabuMv;
      nTabuBest = tabuBest;
    }
    // update
    // cout << nTabuBest << endl;
    conflict += nTabuBest;
    hisBest = min(hisBest, conflict);
    for (int e = head[mv]; e != 0; e = edge[e].next) {
      --colorTable[edge[e].to][c[mv]];
      ++colorTable[edge[e].to][mc];
    }
    tabuTenure[mv][c[mv]] = conflict + R() % 7 + step;
    c[mv] = mc;
    if (!conflict) break;
    if (step % 100000UL == 0) {
      cout << step << ": " << conflict << "(" << hisBest << ")" << endl;
    }
  }
  clock_t end = clock();
  double timeCost = (double)(end - begin) / CLOCKS_PER_SEC;

  if (checkRes()) {
    cout << "Finish" << endl;
  } else {
    cout << conflict << endl;
    cout << "Failure" << endl;
  }
  printf("step: %d\ttime: %lf\n", step, timeCost);
  return 0;
}

void getInput() {
  char buf[100 + 2];
  while (fgets(buf, 100, stdin) && buf[0] != 'p')
    ;
  char tmpC, tmpS[10];
  int m, u, v;
  sscanf(buf, "%c %s %d %d", &tmpC, tmpS, &n, &m);
  while (m--) {
    scanf("%c %d %d", &tmpC, &u, &v);
    getchar();
    addEdge(u, v);
    addEdge(v, u);
  }
}
void init() {
  random_device rd;
  default_random_engine R(rd());
  for (int i = 1; i <= n; ++i) {
    c[i] = R() % K;
  }
}

void makeColorTable() {
  for (int u = 1; u <= n; ++u) {
    for (int k = 0; k < K; ++k) {
      int clash = 0;
      for (int e = head[u]; e != 0; e = edge[e].next) {
        if (k == c[edge[e].to]) ++clash;
      }
      if (k == c[u]) conflict += clash;
      colorTable[u][k] = clash;
    }
  }
  conflict >>= 1;
}

bool checkRes() {
  for (int u = 1; u <= n; ++u) {
    for (int e = head[u]; e != 0; e = edge[e].next) {
      if (c[u] == c[edge[e].to]) return false;
    }
  }
  return true;
}