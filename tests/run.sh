#!/bin/sh
set -eu

cd "$(dirname "$0")/.."
build_dir=$(mktemp -d)
trap 'rm -rf "$build_dir"' EXIT HUP INT TERM

"${CC:-cc}" -std=c11 -Wall -Wextra -Werror -pedantic -Isrc \
    tests/test_ti84fb.c src/ti84fb.c -o "$build_dir/test_ti84fb"
"$build_dir/test_ti84fb"

"${CC:-cc}" -std=c11 -Wall -Wextra -Werror -pedantic -Isrc \
    tests/test_demo.c src/ti84fb.c src/demo.c -o "$build_dir/test_demo"
"$build_dir/test_demo"
