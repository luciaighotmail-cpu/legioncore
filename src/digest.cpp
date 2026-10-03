#include "legioncore/digest.hpp"

#include "blake3.h"

#include <cstring>

namespace legioncore {

Digest32 blake3_256(std::span<const uint8_t> data) {
  Digest32 out{};
  blake3_hasher hasher;
  blake3_hasher_init(&hasher);
  if (!data.empty()) {
    blake3_hasher_update(&hasher, data.data(), data.size());
  }
  blake3_hasher_finalize(&hasher, out.data(), out.size());
  return out;
}

Digest32 blake3_256(std::string_view data) {
  return blake3_256(std::span<const uint8_t>(
      reinterpret_cast<const uint8_t*>(data.data()), data.size()));
}

bool digest_equal(const Digest32& a, const Digest32& b) noexcept {
  // Constant-time comparison
  uint8_t diff = 0;
  for (size_t i = 0; i < 32; ++i) {
    diff |= a[i] ^ b[i];
  }
  return diff == 0;
}

} // namespace legioncore
