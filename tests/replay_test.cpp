#include "legioncore/nonce.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

using namespace legioncore;

int main() {
  int failures = 0;
  NonceStore store;
  Nonce n{};
  n[0] = 0x42;

  // First consumption succeeds
  if (!store.try_consume(n)) {
    std::cerr << "FAIL: first consume failed\n";
    ++failures;
  }
  // Second must fail
  if (store.try_consume(n)) {
    std::cerr << "FAIL: replay accepted\n";
    ++failures;
  }
  if (!store.has_seen(n)) {
    std::cerr << "FAIL: has_seen false after consume\n";
    ++failures;
  }

  // Concurrent: same nonce, N threads — at most one success
  {
    NonceStore concurrent;
    Nonce shared{};
    shared[1] = 0x99;
    std::atomic<int> successes{0};
    constexpr int N = 32;
    std::vector<std::thread> threads;
    for (int i = 0; i < N; ++i) {
      threads.emplace_back([&]() {
        if (concurrent.try_consume(shared)) {
          successes.fetch_add(1);
        }
      });
    }
    for (auto& t : threads) t.join();
    if (successes.load() != 1) {
      std::cerr << "FAIL: concurrent successes = " << successes.load() << " (expected 1)\n";
      ++failures;
    }
  }

  if (failures == 0) {
    std::cout << "PASS: replay_test\n";
    return 0;
  }
  std::cerr << "FAILED: " << failures << " assertion(s)\n";
  return 1;
}
