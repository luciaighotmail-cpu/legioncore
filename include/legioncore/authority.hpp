#pragma once

#include "legioncore/types.hpp"
#include <optional>
#include <string>
#include <unordered_map>

namespace legioncore {

// Public key material only. Private keys never appear here or in any repository.
struct PublicKeyRecord {
  KeyID     key_id;
  Digest32  fingerprint;          // BLAKE3 of public key bytes
  bool      active{true};
  // revocation / rotation metadata can be extended later
};

struct AuthorityRecord {
  AuthorityID authority_id;       // e.g. "RAHMAEL-ROOT-001"
  std::string governance_role;    // "SovereignPrincipal"
  std::string scope;              // "FederationRoot"
  KeyID       root_key_id;        // reference only
  bool        active{true};
};

// In-memory authority registry for the substrate.
// Production systems will load from signed policy stores.
class AuthorityRegistry {
public:
  void register_authority(AuthorityRecord rec);
  void register_key(PublicKeyRecord rec);

  std::optional<AuthorityRecord> lookup_authority(const AuthorityID& id) const;
  std::optional<PublicKeyRecord> lookup_key(const KeyID& id) const;

  bool is_authority_active(const AuthorityID& id) const;
  bool is_key_active(const KeyID& id) const;

private:
  std::unordered_map<AuthorityID, AuthorityRecord> authorities_;
  std::unordered_map<KeyID, PublicKeyRecord> keys_;
};

} // namespace legioncore
