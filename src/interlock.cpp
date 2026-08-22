#include "legioncore/interlock.hpp"

namespace legioncore {

bool CommandInterlock::arm(const CommandID& command_id) {
  if (command_id.empty()) return false;
  if (state_ != InterlockState::BLOCKED) return false;
  armed_for_ = command_id;
  state_ = InterlockState::ARMED;
  return true;
}

bool CommandInterlock::fire(const CommandID& command_id) {
  if (state_ != InterlockState::ARMED) return false;
  if (armed_for_ != command_id) return false;
  state_ = InterlockState::FIRED;
  // Immediately return to BLOCKED after fire attempt
  state_ = InterlockState::BLOCKED;
  armed_for_.clear();
  return true;
}

void CommandInterlock::force_block() noexcept {
  state_ = InterlockState::BLOCKED;
  armed_for_.clear();
}

} // namespace legioncore
