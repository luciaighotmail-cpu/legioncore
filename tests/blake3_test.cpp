#include "legioncore/digest.hpp"
#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace legioncore;

static int failures = 0;

static void check(bool cond, const char* msg) {
  if (!cond) {
    std::fprintf(stderr, "FAIL: %s\n", msg);
    ++failures;
  }
}

static std::string to_hex(const Digest32& d) {
  static const char* hex = "0123456789abcdef";
  std::string s;
  s.reserve(64);
  for (uint8_t b : d) {
    s.push_back(hex[b >> 4]);
    s.push_back(hex[b & 0xf]);
  }
  return s;
}

// Official BLAKE3 empty-input digest (BLAKE3-team test vectors)
static const char* EMPTY_HEX =
    "af1349b9f5f9a1a6a0404dea36dcc9499bcb25c9adc112b7cc9a93cae41f3262";

int main() {
  // 1. Empty input known-answer
  {
    Digest32 d = blake3_256(std::span<const uint8_t>{});
    std::string h = to_hex(d);
    check(h == EMPTY_HEX, "empty input known-answer");
    if (h != EMPTY_HEX) {
      std::fprintf(stderr, "  got: %s\n  exp: %s\n", h.c_str(), EMPTY_HEX);
    }
  }

  // 2. Single byte non-zero
  {
    uint8_t a = 'a';
    Digest32 d = blake3_256(std::span<const uint8_t>(&a, 1));
    check(!digest_equal(d, Digest32{}), "single-byte non-zero");
  }

  // 3. Determinism
  {
    std::string msg = "LegionCore REV02 BLAKE3 integration test";
    Digest32 a = blake3_256(msg);
    Digest32 b = blake3_256(msg);
    check(digest_equal(a, b), "determinism");
  }

  // 4. One-shot equivalence over 10k bytes
  {
    std::vector<uint8_t> data(10000);
    for (size_t i = 0; i < data.size(); ++i) data[i] = static_cast<uint8_t>(i & 0xff);
    Digest32 one = blake3_256(std::span<const uint8_t>(data));
    Digest32 two = blake3_256(std::span<const uint8_t>(data.data(), data.size()));
    check(digest_equal(one, two), "one-shot equivalence over 10k bytes");
  }

  // 5. Boundary lengths produce distinct digests
  {
    std::vector<size_t> lens = {0, 1, 63, 64, 65, 1023, 1024, 1025, 2048, 10000};
    Digest32 prev{};
    bool first = true;
    for (size_t len : lens) {
      std::vector<uint8_t> buf(len, 0x42);
      Digest32 d = blake3_256(std::span<const uint8_t>(buf));
      if (!first) {
        check(!digest_equal(d, prev), "different length produces different digest");
      }
      prev = d;
      first = false;
    }
  }

  // 6. Constant-time equal
  {
    Digest32 a = blake3_256("x");
    Digest32 b = a;
    Digest32 c = blake3_256("y");
    check(digest_equal(a, b), "equal digests");
    check(!digest_equal(a, c), "unequal digests");
  }

  if (failures == 0) {
    std::printf("blake3_test: ALL PASS\n");
    return 0;
  }
  std::fprintf(stderr, "blake3_test: %d failure(s)\n", failures);
  return 1;
}
