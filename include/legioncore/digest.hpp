#pragma once

#include "legioncore/types.hpp"
#include <span>
#include <string_view>

namespace legioncore {

// Placeholder interface. Production builds link against a real BLAKE3 implementation.
// For the first substrate we provide a deterministic stub that is still fail-closed
// for empty inputs and produces a fixed-size digest.
Digest32 blake3_256(std::span<const uint8_t> data);
Digest32 blake3_256(std::string_view data);

// Constant-time comparison
bool digest_equal(const Digest32& a, const Digest32& b) noexcept;

} // namespace legioncore
