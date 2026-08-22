#include "legioncore/command.hpp"

namespace legioncore {

std::optional<Command> Command::try_create(
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
    Signature64 signature) {

  // Fail closed on empty / zero structural fields
  if (command_id.empty() || intent_id.empty() || authority_id.empty() ||
      key_id.empty() || target_node.empty() || target_capability.empty()) {
    return std::nullopt;
  }
  if (freshness_window <= 0) {
    return std::nullopt;
  }
  if (timestamp < 0) {
    return std::nullopt;
  }

  Command c;
  c.command_id         = std::move(command_id);
  c.intent_id          = std::move(intent_id);
  c.authority_id       = std::move(authority_id);
  c.key_id             = std::move(key_id);
  c.policy_digest      = policy_digest;
  c.payload_digest     = payload_digest;
  c.nonce              = nonce;
  c.timestamp          = timestamp;
  c.freshness_window   = freshness_window;
  c.target_node        = std::move(target_node);
  c.target_capability  = std::move(target_capability);
  c.signature          = signature;
  return c;
}

bool Command::is_fresh(TimestampMs now) const noexcept {
  if (now < timestamp) return false;
  return (now - timestamp) <= freshness_window;
}

} // namespace legioncore
