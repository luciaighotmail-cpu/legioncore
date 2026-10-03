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
| L-03 test harness | **PRESENT** (command, state, authority, replay + blake3) |
| L-03 Empirical PASS | **SUPPORTED locally** — see evidence/rev02/MANIFEST.md |

## Build

```bash
cmake -B build -S .
cmake --build build
ctest --test-dir build --output-on-failure
```

## L-03 Harness

- `command_contract_test` — structural validation positive/negative
- `state_machine_test` — legal + illegal transitions
- `authority_test` — registry accept/reject/revoke
- `replay_test` — nonce at-most-once + concurrent single-winner
- `blake3_test` — empty-input known-answer, boundaries, equivalence

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

## REV 02 (2026-10-03)

Digest layer rebuilt against official BLAKE3 1.8.7 (portable).

- `third_party/blake3/` contains the C sources.
- Known-answer empty-input vector matches official.
- All unit tests + sanitizer matrix PASS locally.
