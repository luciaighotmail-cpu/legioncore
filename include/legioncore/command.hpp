#pragma once

#include "legioncore/types.hpp"
#include <optional>
#include <string>

namespace legioncore {

// Command is immutable after construction.
// Construction itself performs structural validation.
// Cryptographic and policy checks happen later in the state machine.
struct Command {
  CommandID      command_id;
  IntentID       intent_id;
  AuthorityID    authority_id;
  KeyID          key_id;
  Digest32       policy_digest;
  Digest32       payload_digest;
  Nonce          nonce;
  TimestampMs    timestamp;
  DurationMs     freshness_window;
  NodeID         target_node;
  CapabilityID   target_capability;
  Signature64    signature;

  // Factory: returns nullopt if any required field is empty / zero-window.
  // Does NOT verify signature or policy — that is the Authority Evaluator.
  static std::optional<Command> try_create(
      CommandID command_id,
      IntentID intent_id,
      AuthorityID authority_id,
      KeyID key_id,
      Digest32 policy_digest,
      Digest32 payload_digest,
      Nonce nonce,
      TimestampMs timestamp,
      DurationMs freshness_window,
      NodeID target_node,
      CapabilityID target_capability,
      Signature64 signature);

  // True if now is within [timestamp, timestamp + freshness_window]
  bool is_fresh(TimestampMs now) const noexcept;
};

} // namespace legioncore
