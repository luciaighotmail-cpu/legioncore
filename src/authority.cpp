#include "legioncore/authority.hpp"

namespace legioncore {

void AuthorityRegistry::register_authority(AuthorityRecord rec) {
  authorities_[rec.authority_id] = std::move(rec);
}

void AuthorityRegistry::register_key(PublicKeyRecord rec) {
  keys_[rec.key_id] = std::move(rec);
}

std::optional<AuthorityRecord> AuthorityRegistry::lookup_authority(
    const AuthorityID& id) const {
  auto it = authorities_.find(id);
  if (it == authorities_.end()) return std::nullopt;
  return it->second;
}

std::optional<PublicKeyRecord> AuthorityRegistry::lookup_key(
    const KeyID& id) const {
  auto it = keys_.find(id);
  if (it == keys_.end()) return std::nullopt;
  return it->second;
}

bool AuthorityRegistry::is_authority_active(const AuthorityID& id) const {
  auto rec = lookup_authority(id);
  return rec && rec->active;
}

bool AuthorityRegistry::is_key_active(const KeyID& id) const {
  auto rec = lookup_key(id);
  return rec && rec->active;
}

} // namespace legioncore
