// #undef DOG_DEBUG
#ifndef DOG_WHEEL_H_
#define DOG_WHEEL_H_
#include <stdarg.h>
#include <stdio.h>
#include <cctype>
// #ifdef DOG_USE_SYSTEM_IOSTREAM
// #include <cassert>
// #include <iostream>
// using std::cerr;
// using std::cin;
// using std::cout;
// using std::endl;

// #else  // DOG_USE_SYSTEM_IOSTREAM
// namespace dog_util {
// class InputStream {
//  public:
//   void redirect(const char *filename) {
// #ifdef DOG_DEBUG
//     freopen(filename, "r", stdin);
// #endif
//   }
//   long long getInt() {
//     int ch = getchar();
//     while (!isdigit(ch)) {
//       ch = getchar();
//     }
//     long long result = ch - '0';
//     ch = getchar();
//     while (isdigit(ch)) {
//       result *= 10;
//       result += ch - '0';
//       ch = getchar();
//     }
//     return result;
//   }
//   // easy to make mistake
//   // if insist, use getchar() instead
//   // InputStream &operator>>(char &k) { scanf("%c", k); }

//   // better
//   InputStream &operator>>(char &k) {
//     do {
//       k = getchar();
//     } while (k == ' ' || k == '\n');
//     return *this;
//   }

// #ifdef HIGH_IO_PERFORMANCE
//   InputStream &operator>>(int &k) {
//     k = getInt();
//     return *this;
//   }
//   InputStream &operator>>(long long &k) {
//     k = getInt();
//     return *this;
//   }
//   InputStream &operator>>(unsigned &k) {
//     k = getInt();
//     return *this;
//   }
//   InputStream &operator>>(unsigned long long &k) {
//     k = getInt();
//     return *this;
//   }
// #else   // HIGH_IO_PERFORMANCE
//   InputStream &operator>>(int &k) {
//     scanf("%d", &k);
//     return *this;
//   }
//   InputStream &operator>>(long long &k) {
//     scanf("%lld", &k);
//     return *this;
//   }
//   InputStream &operator>>(unsigned &k) {
//     scanf("%u", &k);
//     return *this;
//   }
//   InputStream &operator>>(unsigned long long &k) {
//     scanf("%llu", &k);
//     return *this;
//   }
// #endif  // HIGH_IO_PERFORMANCE

//   InputStream &operator>>(char *str) {
//     scanf("%s", str);
//     return *this;
//   }
//   InputStream &operator>>(double &k) {
//     scanf("%lf", &k);
//     return *this;
//   }
//   template <class Container>
//   void getstring(Container &vec) {
//     int ch;
//     do {
//       ch = getchar();
//     } while (ch == ' ' || ch == '\n');
//     vec.push_back(ch);

//     while (true) {
//       int ch = getchar();
//       if (ch == EOF || ch == ' ' || ch == '\n') {
//         break;
//       }
//       vec.push_back(ch);
//     }
//   }

//   template <class Container>
//   void getline(Container &vec) {
//     int ch;
//     do {
//       ch = getchar();
//     } while (ch == '\n');
//     vec.push_back(ch);

//     while (true) {
//       int ch = getchar();
//       if (ch == EOF || ch == '\n') {
//         break;
//       }
//       vec.push_back(ch);
//     }
//   }

//   void skipline() {
//     while (true) {
//       int ch = getchar();
//       if (ch == EOF || ch == '\n') {
//         break;
//       }
//     }
//   }
// } cin;
// void poj_throw() {
//   int *fuck = NULL;
//   scanf("%d", fuck);
// }

// class OutputStream {
//  public:
//   // OutputStream(){
//   // char buffer[1 << 19];
//   // setvbuf(stdout, buffer, _IOFBF, sizeof(buffer));
//   // };
//   OutputStream &operator<<(char k) {
//     printf("%c", k);
//     return *this;
//   }
//   OutputStream &operator<<(unsigned long k) {
//     printf("%lu", k);
//     return *this;
//   }
//   OutputStream &operator<<(int k) {
//     printf("%d", k);
//     return *this;
//   }
//   OutputStream &operator<<(long long k) {
//     printf("%lld", k);
//     return *this;
//   }
//   OutputStream &operator<<(unsigned k) {
//     printf("%u", k);
//     return *this;
//   }
//   OutputStream &operator<<(unsigned long long k) {
//     printf("%llu", k);
//     return *this;
//   }
//   OutputStream &operator<<(const char *str) {
//     printf("%s", str);
//     return *this;
//   }
//   OutputStream &operator<<(double k) {
//     printf("%f", k);
//     return *this;
//   }
//   //  setHP{

//   // }
// } cout;

// class DebugStream {
//  public:
//   int errprintf(const char *str, ...) {
// #ifdef DOG_DEBUG
//     va_list argptr;
//     va_start(argptr, str);
//     vfprintf(stderr, str, argptr);
//     va_end(argptr);
// #endif
//     return 0;
//   }
//   DebugStream &operator<<(char k) {
//     errprintf("%c", k);
//     return *this;
//   }
//   DebugStream &operator<<(int k) {
//     errprintf("%d", k);
//     return *this;
//   }
//   DebugStream &operator<<(long long k) {
//     errprintf("%lld", k);
//     return *this;
//   }
//   DebugStream &operator<<(unsigned long k) {
//     errprintf("%lu", k);
//     return *this;
//   }
//   DebugStream &operator<<(unsigned k) {
//     errprintf("%u", k);
//     return *this;
//   }
//   DebugStream &operator<<(unsigned long long k) {
//     errprintf("%llu", k);
//     return *this;
//   }
//   DebugStream &operator<<(const char *str) {
//     errprintf("%s", str);
//     return *this;
//   }
//   DebugStream &operator<<(double k) {
//     errprintf("%f", k);
//     return *this;
//   }
// } cerr;
// const char *endl = "\n";
// }  // namespace dog_util
// using dog_util::cerr;
// using dog_util::cin;
// using dog_util::cout;
// using dog_util::endl;
// using dog_util::poj_throw;

typedef long long ll;
typedef long long ull;

#include <stdio.h>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
using std::make_pair;
using std::map;
using std::pair;
using std::set;
using std::vector;

#endif  // DOG_WHEEL_H_ 