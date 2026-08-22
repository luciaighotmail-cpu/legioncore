#include "legioncore/authority.hpp"
#include <iostream>

using namespace legioncore;

int main() {
  int failures = 0;
  AuthorityRegistry reg;

  AuthorityRecord root;
  root.authority_id    = "RAHMAEL-ROOT-001";
  root.governance_role = "SovereignPrincipal";
  root.scope           = "FederationRoot";
  root.root_key_id     = "key-root-001";
  root.active          = true;
  reg.register_authority(root);

  PublicKeyRecord key;
  key.key_id      = "key-root-001";
  key.fingerprint = {};
  key.active      = true;
  reg.register_key(key);

  if (!reg.is_authority_active("RAHMAEL-ROOT-001")) {
    std::cerr << "FAIL: root authority not active\n";
    ++failures;
  }
  if (!reg.is_key_active("key-root-001")) {
    std::cerr << "FAIL: root key not active\n";
    ++failures;
  }
  if (reg.is_authority_active("UNKNOWN-AUTH")) {
    std::cerr << "FAIL: unknown authority accepted\n";
    ++failures;
  }
  if (reg.is_key_active("UNKNOWN-KEY")) {
    std::cerr << "FAIL: unknown key accepted\n";
    ++failures;
  }

  // Revocation
  root.active = false;
  reg.register_authority(root);
  if (reg.is_authority_active("RAHMAEL-ROOT-001")) {
    std::cerr << "FAIL: revoked authority still active\n";
    ++failures;
  }

  if (failures == 0) {
    std::cout << "PASS: authority_test\n";
    return 0;
  }
  std::cerr << "FAILED: " << failures << " assertion(s)\n";
  return 1;
}
