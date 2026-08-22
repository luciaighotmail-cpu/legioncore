#pragma once

#include "legioncore/command.hpp"

namespace legioncore {

// The final gate before any hardware / actuator action.
// Defaults to blocked. Must be explicitly armed for a specific command.
enum class InterlockState {
  BLOCKED,
  ARMED,
  FIRED
};

class CommandInterlock {
public:
  CommandInterlock() = default;

  InterlockState state() const noexcept { return state_; }

  // Arm only for a concrete CommandID that has already been ADMITTED.
  bool arm(const CommandID& command_id);

  // Fire only if currently ARMED for the matching command.
  // After fire (success or failure) the interlock returns to BLOCKED.
  bool fire(const CommandID& command_id);

  void force_block() noexcept;

private:
  InterlockState state_{InterlockState::BLOCKED};
  CommandID armed_for_;
};

} // namespace legioncore
