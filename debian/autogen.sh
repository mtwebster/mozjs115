#!/bin/sh

set -e
set -x

if [ "$WITH_SYSTEM_ICU" != yes ]; then
    ( cd ../../intl/icu/source; autoreconf -fi --verbose )
fi
