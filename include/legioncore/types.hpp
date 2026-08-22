#pragma once

#include <array>
Introductory
#include <cstdint>
#include <string>
#include <string_view>

namespace legioncore {

// Fixed-size digests (BLAKE3-256 = 32 bytes)
using Digest32 = std::array<uint8_t, 32>;

// Opaque identifiers (hex or raw bytes in real builds)
using CommandID     = std::string;
using IntentID      = std::string;
using AuthorityID   = std::string;
using KeyID         = std::string;
using NodeID        = std::string;
using CapabilityID  = std::string;
using Nonce         = std::array<uint8_t, 32>;

// Ed25519 signature = 64 bytes
using Signature64   = std::array<uint8_t, 64>;

// Timestamps in Unix milliseconds
using TimestampMs   = int64_t;
using DurationMs    = int64_t;

} // namespace legioncore
