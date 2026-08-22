# LegionCore

Distributed computational substrate for the Sealie Federation.

## Responsibilities

- Authority state machine (fail-closed)
- CommandInterlockService
- Hardware interlock layer
- Telemetry & evidence integration

## Current Status

| Item | Status |
|------|--------|
| Architecture | ESTABLISHED |
| L-02 Command contract | DEFINED (see sealie-architecture) |
| L-02 State machine | DEFINED (fail-closed) |
| Implementation | IN PROGRESS |
| L-03 Empirical PASS | **NOT YET** |

## L-03 Authority Tests (Required before any PASS claim)

- State transition tests
- Concurrency tests
- Stale-authority tests
- Race conditions
- Replay attempts
- Invalid transitions
- Authorization boundary tests

## Related

- [luci](https://github.com/luciaighotmail-cpu/luci)
- [sealie-architecture](https://github.com/luciaighotmail-cpu/sealie-architecture)
- [sealie-os](https://github.com/luciaighotmail-cpu/sealie-os)
- [evidence-ledger](https://github.com/luciaighotmail-cpu/evidence-ledger)
