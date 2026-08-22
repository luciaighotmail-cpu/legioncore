#include "legioncore/digest.hpp"
#include <cstring>

namespace legioncore {

// Deterministic stub. Replace with real BLAKE3 in production builds.
// Still fails closed on empty input by producing a distinct all-zero digest.
Digest32 blake3_256(std::span<const uint8_t> data) {
  Digest32 out{};
  if (data.empty()) {
    return out;  // all zeros
  }
  // Simple non-cryptographic mix for substrate scaffolding only.
  // DO NOT use this stub for any real security claim.
  uint64_t h = 0xcbf29ce484222325ull;
  for (uint8_t b : data) {
    h ^= b;
    h *= 0x100000001b3ull;
  }
  for (size_t i = 0; i < 32; ++i) {
    out[i] = static_cast<uint8_t>((h >> ((i % 8) * 8)) & 0xff);
    h = h * 0x9e3779b97f4a7c15ull + i;
  }
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
