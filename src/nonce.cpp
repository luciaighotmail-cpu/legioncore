#include "legioncore/nonce.hpp"

namespace legioncore {

bool NonceStore::try_consume(const Nonce& nonce) {
  std::lock_guard lock(mu_);
  auto [it, inserted] = seen_.insert(nonce);
  return inserted;
}

bool NonceStore::has_seen(const Nonce& nonce) const {
  std::lock_guard lock(mu_);
  return seen_.count(nonce) > 0;
}

std::size_t NonceHash::operator()(const Nonce& n) const noexcept {
  return std::hash<Nonce>{}(n);
}

} // namespace legioncore
