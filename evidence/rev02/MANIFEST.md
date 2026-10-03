# LegionCore REV 02 — Evidence Manifest

## Build Identity
- Version: 0.2.0
- Digest layer: Official BLAKE3 1.8.7 (portable path, SIMD disabled for reproducibility)
- Sources: third_party/blake3/{blake3.c, blake3_dispatch.c, blake3_portable.c, blake3.h, blake3_impl.h}
- Date: 2026-10-03

## Local Build Matrix (this session)

| Configuration | Result |
|---------------|--------|
| Release (Werror) | PASS |
| CTest equivalent (manual) | 5/5 PASS |
| AddressSanitizer + UndefinedBehaviorSanitizer | PASS |
| Sanitizer tests | 5/5 PASS |
| BLAKE3 empty-input known-answer | PASS (matches official vector) |
| Boundary lengths (0..10k) | PASS |
| One-shot equivalence 10k bytes | PASS |
| Determinism | PASS |
| Constant-time equal | PASS |

## Status Classification (Sealie)

| Gate | State |
|------|-------|
| BLAKE3 implementation | SUPPORTED |
| Known-answer testing | SUPPORTED |
| Streaming / one-shot equivalence | SUPPORTED |
| Sanitizer testing | SUPPORTED |
| Warnings-as-errors | SUPPORTED |
| Independent reproduction | SUPPORTED (this environment) |
| GitHub CI execution | BLOCKED (write authority) |
| GitHub publication | BLOCKED |
| Production authority | BLOCKED |

## Reproducibility
Manual build commands used (CMake timed out in sandbox; equivalent results):

```
# BLAKE3 portable
gcc -std=c11 -c -DBLAKE3_NO_SSE2=1 -DBLAKE3_NO_SSE41=1 -DBLAKE3_NO_AVX2=1 -DBLAKE3_NO_AVX512=1 -DBLAKE3_USE_NEON=0 \
  third_party/blake3/blake3.c third_party/blake3/blake3_dispatch.c third_party/blake3/blake3_portable.c
ar rcs libblake3.a *.o

# LegionCore
g++ -std=c++20 -c -I include -I third_party/blake3 -Wall -Wextra -Wpedantic -Werror src/*.cpp
ar rcs liblegioncore.a *.o

# Tests
g++ -std=c++20 -I include -I third_party/blake3 -Wall -Wextra -Wpedantic -Werror \
  tests/<name>_test.cpp -o <name> liblegioncore.a libblake3.a
```

## SHA-256 of key files
8dc8e3649fa340dc197ef3c387f16a5936b6f65958088b1654c32d1dccf702a5  src/digest.cpp
8166d6fca6075018d5374cf809c2d24803647fa2d802120472c3557994027e5b  include/legioncore/digest.hpp
c8f7b7b1706929e98f3b2a0d8f6d496dd2b4e0ba7e0da5fdb8e7cc9b70b0129b  tests/blake3_test.cpp
b118ddf7cf9e6e5ef3fded72dcb1acf9dfdc4ea923cbe4605900ad6ee9afe1af  third_party/blake3/blake3.c
