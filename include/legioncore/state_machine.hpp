#pragma once

#include "legioncore/command.hpp"
#include <string>

namespace legioncore {

enum class CommandState {
  PROPOSED,
  VALIDATING,
  AUTHORIZED,
  ADMITTED,
  EXECUTING,
  COMPLETED,
  // Terminal rejection states
  REJECTED,
  EXPIRED,
  REPLAYED,
  UNAUTHORIZED,
  INVALID,
  POLICY_DENIED,
  SIGNATURE_INVALID,
  INTERLOCK_BLOCKED
};

std::string_view to_string(CommandState s) noexcept;

// Returns true only for explicit legal transitions.
// Everything else is illegal and must produce a rejection state.
bool is_legal_transition(CommandState from, CommandState to) noexcept;

// State machine instance bound to a single Command.
class StateMachine {
public:
  explicit StateMachine(Command cmd);

  CommandState state() const noexcept { return state_; }
  const Command& command() const noexcept { return command_; }

  // Attempt transition. Returns false and moves to a rejection state on failure.
  bool transition_to(CommandState target);

  bool is_terminal() const noexcept;
  bool is_accepted() const noexcept;  // COMPLETED only
  bool is_rejected() const noexcept;

private:
  Command command_;
  CommandState state_{CommandState::PROPOSED};
};

} // namespace legioncore
