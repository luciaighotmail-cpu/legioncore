#include "legioncore/command.hpp"
#include <cassert>
#include <iostream>

using namespace legioncore;

static Digest32 zero_digest{};
static Nonce zero_nonce{};
static Signature64 zero_sig{};

int main() {
  int failures = 0;

  // Positive: well-formed command
  {
    auto cmd = Command::try_create(
        "cmd-001", "intent-001", "RAHMAEL-ROOT-001", "key-001",
        zero_digest, zero_digest, zero_nonce,
        1'700'000'000'000, 60'000,
        "node-1", "capability.actuator",
        zero_sig);
    if (!cmd) {
      std::cerr << "FAIL: valid command rejected\n";
      ++failures;
    } else if (!cmd->is_fresh(1'700'000'000'000)) {
      std::cerr << "FAIL: command should be fresh at timestamp\n";
      ++failures;
    } else if (cmd->is_fresh(1'700'000'060'001)) {
      std::cerr << "FAIL: command should be expired after window\n";
      ++failures;
    }
  }

  // Negative: empty command_id
  {
    auto cmd = Command::try_create(
        "", "intent-001", "RAHMAEL-ROOT-001", "key-001",
        zero_digest, zero_digest, zero_nonce,
        1'700'000'000'000, 60'000,
        "node-1", "capability.actuator", zero_sig);
    if (cmd) {
      std::cerr << "FAIL: empty command_id accepted\n";
      ++failures;
    }
  }

  // Negative: zero freshness window
  {
    auto cmd = Command::try_create(
        "cmd-002", "intent-001", "RAHMAEL-ROOT-001", "key-001",
        zero_digest, zero_digest, zero_nonce,
        1'700'000'000'000, 0,
        "node-1", "capability.actuator", zero_sig);
    if (cmd) {
      std::cerr << "FAIL: zero freshness accepted\n";
      ++failures;
    }
  }

  // Negative: empty authority
  {
    auto cmd = Command::try_create(
        "cmd-003", "intent-001", "", "key-001",
        zero_digest, zero_digest, zero_nonce,
        1'700'000'000'000, 60'000,
        "node-1", "capability.actuator", zero_sig);
    if (cmd) {
      std::cerr << "FAIL: empty authority accepted\n";
      ++failures;
    }
  }

  if (failures == 0) {
    std::cout << "PASS: command_contract_test\n";
    return 0;
  }
  std::cerr << "FAILED: " << failures << " assertion(s)\n";
  return 1;
}
