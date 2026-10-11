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
| L-03 Empirical evidence | **SUPPORTED** — internal unit-level |
| L-06 Merkle evidence | **SUPPORTED** — tree + inclusion proofs over current artefacts |

### L-03 Evidence (SUPPORTED — not PROVEN)

| Field | Value |
|-------|-------|
| Evidence ID | `L03-EVIDENCE-20261011T073749Z` |
| Content digest (SHA-256) | `ce7cfc0931b5d6ac228755a502421ca8519e2b061c61827da55eed698a8e36c1` |
| Evidence commit | `c0ff444c8ca5176fb046c5290d302b5a4121cf64` |
| Source commit | `87eb9f1fde3e46a881708434b975cf2519911eff` |
| Claim | SUPPORTED (internal unit-level only) |

### L-06 Merkle Tree (SUPPORTED — not PROVEN)

| Field | Value |
|-------|-------|
| Tree ID | `L06-MERKLE-TREE-20261011` |
| Root (SHA-256) | `88f7474c419c03fd63dbf9b9fdd64a3db549c45d9cf0730e140082ff0397c022` |
| Leaves | 4 (L-03 package artefacts) |
| Depth | 2 |
| Inclusion proofs | All verified at construction |
| Claim | SUPPORTED (tree + proofs exist) |

Location: [`evidence/generated/`](evidence/generated/)  
Independent verification of L-03 performed 2026-10-11. Merkle tree constructed and proofs verified the same day.

**Status machine note:** Neither claim is PROVEN. No independent certification or CI-signed provenance is present yet.

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
