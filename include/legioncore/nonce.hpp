#pragma once

#include "legioncore/types.hpp"
#include <mutex>
#include <unordered_set>

namespace legioncore {

// Simple in-memory nonce store. Production will use durable, partitioned storage.
// Fail-closed: unknown / already-seen nonce → reject.
class NonceStore {
public:
  // Returns true if the nonce was not previously seen and is now recorded.
  // Concurrent calls for the same nonce: at most one returns true.
  bool try_consume(const Nonce& nonce);

  bool has_seen(const Nonce& nonce) const;

private:
  mutable std::mutex mu_;
  std::unordered_set<Nonce> seen_;  // requires hash specialization
};

// Hash for Nonce so it can live in unordered_set
struct NonceHash {
  std::size_t operator()(const Nonce& n) const noexcept;
};

} // namespace legioncore

// Specialization must be visible to unordered_set
namespace std {
template <>
struct hash<legioncore::Nonce> {
  std::size_t operator()(const legioncore::Nonce& n) const noexcept {
    // Simple FNV-1a over the 32 bytes
    std::size_t h = 14695981039346656037ull;
    for (uint8_t b : n) {
      h ^= b;
      h *= 1099511628211ull;
    }
    return h;
  }
};
} // namespace std
