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

} // namespace legioncore
