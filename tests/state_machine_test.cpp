#include "legioncore/command.hpp"
#include "legioncore/state_machine.hpp"
#include <cassert>
#include <iostream>

using namespace legioncore;

static Command make_valid_command() {
  Digest32 d{};
  Nonce n{};
  Signature64 s{};
  return *Command::try_create(
      "cmd-sm-001", "intent-sm", "RAHMAEL-ROOT-001", "key-001",
      d, d, n, 1'700'000'000'000, 60'000,
      "node-1", "capability.test", s);
}

int main() {
  int failures = 0;

  // Happy path
  {
    StateMachine sm(make_valid_command());
    if (sm.state() != CommandState::PROPOSED) { ++failures; std::cerr << "initial state\n"; }
    if (!sm.transition_to(CommandState::VALIDATING)) { ++failures; }
    if (!sm.transition_to(CommandState::AUTHORIZED)) { ++failures; }
    if (!sm.transition_to(CommandState::ADMITTED)) { ++failures; }
    if (!sm.transition_to(CommandState::EXECUTING)) { ++failures; }
    if (!sm.transition_to(CommandState::COMPLETED)) { ++failures; }
    if (!sm.is_accepted()) { ++failures; std::cerr << "not accepted\n"; }
  }

  // Illegal transition from PROPOSED directly to COMPLETED
  {
    StateMachine sm(make_valid_command());
    if (sm.transition_to(CommandState::COMPLETED)) {
      ++failures;
      std::cerr << "illegal PROPOSED	oCOMPLETED accepted\n";
    }
    if (!sm.is_rejected()) {
      ++failures;
      std::cerr << "should have moved to REJECTED\n";
    }
  }

  // Rejection path
  {
    StateMachine sm(make_valid_command());
    sm.transition_to(CommandState::VALIDATING);
    if (!sm.transition_to(CommandState::SIGNATURE_INVALID)) { ++failures; }
    if (!sm.is_rejected()) { ++failures; }
    if (sm.is_accepted()) { ++failures; }
  }

  // Terminal states cannot transition further
  {
    StateMachine sm(make_valid_command());
    sm.transition_to(CommandState::VALIDATING);
    sm.transition_to(CommandState::UNAUTHORIZED);
    if (sm.transition_to(CommandState::AUTHORIZED)) {
      ++failures;
      std::cerr << "transition out of UNAUTHORIZED allowed\n";
    }
  }

  if (failures == 0) {
    std::cout << "PASS: state_machine_test\n";
    return 0;
  }
  std::cerr << "FAILED: " << failures << " assertion(s)\n";
  return 1;
}
