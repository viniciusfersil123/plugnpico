#!/usr/bin/env bash
set -eu

cd "$(dirname "$0")"

# Generate runtime component configuration from components.json.
python3 ./generate_components.py

# Always regenerate the Heavy output from a clean state.
rm -rf hv_generated
hvcc test.pd -o hv_generated -n testpatch -g c

# Reconfigure and rebuild the Pico project after the generated sources change.
cmake -S . -B build
cmake --build build -- -j4

# Flash the built firmware to the Pico board using the default Pico toolchain.
${HOME}/.pico-sdk/picotool/2.3.1/picotool/picotool load build/blink_any.elf -fx

echo "Heavy + Pico rebuild and flash complete."

