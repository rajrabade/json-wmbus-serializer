# Embedded JSON Serializer for w-M-Bus Data

## Overview

This project implements a compact C library that serializes structured meter data into
an exact JSON structure required by the assignment. The serializer is dependency-free
and designed with embedded constraints in mind (fixed buffers, no dynamic allocation).

## Platform & Language

- Language: C (C99-compatible)
- Platform: Generic / PC build (justified as portable C that can be compiled for STM32/ESP32)

## Build & Run

From the repository root:

```bash
make
./demo
```

Or compile directly:

```bash
gcc src/serializer.c examples/main.c -Iinclude -o demo
./demo
```

## Public API

`serialize_to_json(const GatewayData *input, char *output, size_t output_size)`

- Caller provides output buffer
- Prevents buffer overflow
- Returns explicit error codes

## Example JSON output

The produced JSON strictly matches the structure required in the assignment.

## Design decisions

- `snprintf` based serialization avoids external JSON dependencies
- Fixed-size arrays (`MAX_DEVICES`, `MAX_DATAPOINTS`) keep memory deterministic
- API is transport-agnostic; logic is independent of UART/MQTT/etc.

## Extensions

- Dynamic sizing / streaming serialization
- Compile-time maximum-size calculator
- Add unit tests and CI
