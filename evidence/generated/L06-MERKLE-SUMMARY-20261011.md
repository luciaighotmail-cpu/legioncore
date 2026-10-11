# L-06 Merkle Tree — 2026-10-11

**Schema:** sealie-merkle-tree-v1  
**Root (SHA-256):** `88f7474c419c03fd63dbf9b9fdd64a3db549c45d9cf0730e140082ff0397c022`  
**Claim:** SUPPORTED (tree + verified inclusion proofs over current evidence artefacts)  
**Not claimed:** Independent attestation, CI-signed provenance, or PROVEN status.

## Covered Leaves (4)

| Label | Content Digest | Leaf Hash |
|-------|----------------|-----------|
| L03-EVIDENCE-20261011T073749Z.json | ce7cfc09… | 975d04af… |
| L03-EVIDENCE-20261011T073749Z.sha256 | d4a820e7… | 122e7a9d… |
| L03-MERKLE-LEAF-20261011.json | eefa396f… | 6b1719b7… |
| L03-SUMMARY-20261011.md | 9e614c92… | 7d7a44eb… |

## Construction
- Leaf: `SHA-256(SEALIE-MERKLE-LEAF-v1 || label || 0x00 || content_digest)`
- Node: `SHA-256(SEALIE-MERKLE-NODE-v1 || left || right)`
- Odd-node policy: hash with domain-separated empty leaf

All four inclusion proofs re-verified at construction time.

Full machine record: `L06-MERKLE-TREE-20261011.json`
