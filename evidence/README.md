# Evidence

This directory is reserved for **machine-generated** evidence records produced by the test harness and CI.

Manual narrative files do not constitute evidence.

## Current artefacts

| Evidence ID / Tree | Gate | Claim | Timestamp (UTC) |
|--------------------|------|-------|-----------------|
| L03-EVIDENCE-20261011T073749Z | L-03 | SUPPORTED (internal unit-level) | 2026-10-11T07:37:49Z |
| L06-MERKLE-TREE-20261011 | L-06 | SUPPORTED (tree + proofs) | 2026-10-11T07:47:18Z |

### L-03 package
- `generated/L03-EVIDENCE-20261011T073749Z.json`
- `generated/L03-EVIDENCE-20261011T073749Z.sha256`
- `generated/L03-SUMMARY-20261011.md`
- `generated/L03-MERKLE-LEAF-20261011.json` (single-leaf precursor)

### L-06 Merkle tree
- `generated/L06-MERKLE-TREE-20261011.json` — full tree, root, inclusion proofs
- `generated/L06-MERKLE-SUMMARY-20261011.md`

**Root:** `88f7474c419c03fd63dbf9b9fdd64a3db549c45d9cf0730e140082ff0397c022`

**Status machine note:** Both claims are SUPPORTED. Neither is PROVEN. No independent certification or CI-signed provenance is present yet.

Expected future artefacts for higher assurance:
- CI-attested build identities
- Independent verification records
- Updated tree versions when new evidence is added
