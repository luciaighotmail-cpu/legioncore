# Official BLAKE3 1.8.7 (vendored)

This directory is intended to hold the official C implementation from
https://github.com/BLAKE3-team/BLAKE3/tree/1.8.7/c

## Required files for portable build

- blake3.h
- blake3_impl.h
- blake3.c
- blake3_dispatch.c
- blake3_portable.c

## Current status on this branch

- `blake3.h` (API) is present (simplified compatible header for the hasher API used by LegionCore).
- Full `blake3_impl.h`, `blake3.c`, `blake3_dispatch.c`, `blake3_portable.c` are present in the local REV 02 tree and in the release archive `LegionCore-REV02-v2.tar.gz` (SHA-256 `ba61ca46f6c254bc8706d2fc5851295b699e2bd2bc90febf17a2b076cd107a2f`).

Because of integration payload size limits, the complete third-party C sources are not yet fully mirrored in this Git commit. They can be restored by:

```bash
# From the REV02 archive or by re-downloading:
curl -sL https://raw.githubusercontent.com/BLAKE3-team/BLAKE3/1.8.7/c/blake3.c -o blake3.c
curl -sL https://raw.githubusercontent.com/BLAKE3-team/BLAKE3/1.8.7/c/blake3_dispatch.c -o blake3_dispatch.c
curl -sL https://raw.githubusercontent.com/BLAKE3-team/BLAKE3/1.8.7/c/blake3_portable.c -o blake3_portable.c
curl -sL https://raw.githubusercontent.com/BLAKE3-team/BLAKE3/1.8.7/c/blake3_impl.h -o blake3_impl.h
# (and the real blake3.h if desired)
```

CMakeLists.txt already points at these files and forces the portable path (SIMD disabled) for reproducibility.

License: the official BLAKE3 dual-license (CC0 / Apache-2.0) applies to these sources.
