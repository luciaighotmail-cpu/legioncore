# LegionCore

Distributed computational substrate for the Sealie Federation.

**Language:** C++20  
**Invariant:** Fail closed. No default authorization. Private keys never in this repository.

## Responsibilities

- Authority state machine (fail-closed)
- CommandInterlockService
- Hardware interlock layer
- Telemetry & evidence integration

## Current Status

| Item | Status |
|------|--------|
| Architecture | ESTABLISHED |
| L-02 Command contract | **IMPLEMENTED** (`include/legioncore/command.hpp`) |
| L-02 State machine | **IMPLEMENTED** (fail-closed) |
| L-02 Authority registry | **IMPLEMENTED** (RAHMAEL-ROOT-001 as identity) |
| L-02 Nonce / freshness | **IMPLEMENTED** |
| L-02 Interlock | **IMPLEMENTED** (default BLOCKED) |
| L-03 test harness | **PRESENT** (command, state, authority, replay) |
| L-03 Empirical PASS | **NOT YET CLAIMED** — requires reproducible build + machine-generated evidence |

## Build

```bash
cmake -B build -S .
cmake --build build
ctest --test-dir build --output-on-failure
```

## L-03 Harness (first targets)

- `command_contract_test` — structural validation positive/negative
- `state_machine_test` — legal + illegal transitions
- `authority_test` — registry accept/reject/revoke
- `replay_test` — nonce at-most-once + concurrent single-winner

## Critical Rule

```
RAHMAEL-ROOT-001  ≠  private key
```

RAHMAEL-ROOT-001 is a governance identity. Cryptographic keys prove authority. Private material never enters GitHub.

## Related

- [luci](https://github.com/luciaighotmail-cpu/luci)
- [sealie-architecture](https://github.com/luciaighotmail-cpu/sealie-architecture)
- [sealie-federation](https://github.com/luciaighotmail-cpu/sealie-federation)
- [evidence-ledger](https://github.com/luciaighotmail-cpu/evidence-ledger)
