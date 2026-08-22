#include "legioncore/state_machine.hpp"

namespace legioncore {

std::string_view to_string(CommandState s) noexcept {
  switch (s) {
    case CommandState::PROPOSED:           return "PROPOSED";
    case CommandState::VALIDATING:         return "VALIDATING";
    case CommandState::AUTHORIZED:         return "AUTHORIZED";
    case CommandState::ADMITTED:           return "ADMITTED";
    case CommandState::EXECUTING:          return "EXECUTING";
    case CommandState::COMPLETED:          return "COMPLETED";
    case CommandState::REJECTED:           return "REJECTED";
    case CommandState::EXPIRED:            return "EXPIRED";
    case CommandState::REPLAYED:           return "REPLAYED";
    case CommandState::UNAUTHORIZED:       return "UNAUTHORIZED";
    case CommandState::INVALID:            return "INVALID";
    case CommandState::POLICY_DENIED:      return "POLICY_DENIED";
    case CommandState::SIGNATURE_INVALID:  return "SIGNATURE_INVALID";
    case CommandState::INTERLOCK_BLOCKED:  return "INTERLOCK_BLOCKED";
  }
  return "UNKNOWN";
}

bool is_legal_transition(CommandState from, CommandState to) noexcept {
  // Happy path
  if (from == CommandState::PROPOSED   && to == CommandState::VALIDATING) return true;
  if (from == CommandState::VALIDATING && to == CommandState::AUTHORIZED) return true;
  if (from == CommandState::AUTHORIZED && to == CommandState::ADMITTED)   return true;
  if (from == CommandState::ADMITTED   && to == CommandState::EXECUTING)  return true;
  if (from == CommandState::EXECUTING  && to == CommandState::COMPLETED)  return true;

  // From non-terminal states, any rejection state is legal
  const bool from_terminal =
      from == CommandState::COMPLETED ||
      from == CommandState::REJECTED ||
      from == CommandState::EXPIRED ||
      from == CommandState::REPLAYED ||
      from == CommandState::UNAUTHORIZED ||
      from == CommandState::INVALID ||
      from == CommandState::POLICY_DENIED ||
      from == CommandState::SIGNATURE_INVALID ||
      from == CommandState::INTERLOCK_BLOCKED;

  if (from_terminal) return false;

  switch (to) {
    case CommandState::REJECTED:
    case CommandState::EXPIRED:
    case CommandState::REPLAYED:
    case CommandState::UNAUTHORIZED:
    case CommandState::INVALID:
    case CommandState::POLICY_DENIED:
    case CommandState::SIGNATURE_INVALID:
    case CommandState::INTERLOCK_BLOCKED:
      return true;
    default:
      return false;
  }
}

StateMachine::StateMachine(Command cmd) : command_(std::move(cmd)) {}

bool StateMachine::transition_to(CommandState target) {
  if (!is_legal_transition(state_, target)) {
    // Illegal transition → force REJECTED if not already terminal
    if (!is_terminal()) {
      state_ = CommandState::REJECTED;
    }
    return false;
  }
  state_ = target;
  return true;
}

bool StateMachine::is_terminal() const noexcept {
  return state_ == CommandState::COMPLETED || is_rejected();
}

bool StateMachine::is_accepted() const noexcept {
  return state_ == CommandState::COMPLETED;
}

bool StateMachine::is_rejected() const noexcept {
  switch (state_) {
    case CommandState::REJECTED:
    case CommandState::EXPIRED:
    case CommandState::REPLAYED:
    case CommandState::UNAUTHORIZED:
    case CommandState::INVALID:
    case CommandState::POLICY_DENIED:
    case CommandState::SIGNATURE_INVALID:
    case CommandState::INTERLOCK_BLOCKED:
      return true;
    default:
      return false;
  }
}

} // namespace legioncore
