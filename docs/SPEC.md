# Spec

### SIC

* arch: RISC-like
* address space: `0x0000~0x7FFF` (32K)
* Registers:
  * A, X, L, PC, SW

### SIC/XE

* arch: CISC-like
* address space: `0x00000~0xFFFFF` (1M)
* Registers:
  * A, X, L, PC, SW and extra: B, S, F, T
* Extra floating point support (48-bits)


> I assume that the CPU will load all ROM to RAM on boot.