// Copyright 2024 Simon McVittie
// SPDX-License-Identifier: MIT

#include <cinttypes>
#include <cstdio>

#include <jsapi.h>
#include <js/Initialization.h>

int main(int argc, char** argv)
{
    // Smoke-test
    const char* reason = JS_InitWithFailureDiagnostic();
    if (reason) {
        std::fprintf(stderr, "Fatal error: %s\n", reason);
        return 1;
    }
    JSContext* cx = JS_NewContext(32 * 1024 * 1024);

    // https://bugs.debian.org/1063446
    uint64_t u64;
    double d = JS::CanonicalizeNaN(0.0/0.0);
    static_assert(sizeof(u64) == sizeof(d));
    memcpy(&u64, &d, sizeof(d));
    std::printf("Representation of a canonicalized NaN: %" PRIx64 "\n", u64);

    JS_DestroyContext(cx);
    JS_ShutDown();
    return 0;
}
