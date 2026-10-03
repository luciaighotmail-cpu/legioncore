#pragma once

#include "legioncore/types.hpp"
#include <span>
#include <string_view>

namespace legioncore {

// BLAKE3-256 digest (32 bytes). Backed by official BLAKE3 1.8.7 C implementation.
// Fail-closed: empty input produces the official empty-input digest (not an error).
Digest32 blake3_256(std::span<const uint8_t> data);
Digest32 blake3_256(std::string_view data);

// Constant-time comparison
bool digest_equal(const Digest32& a, const Digest32& b) noexcept;

} // namespace legioncore
