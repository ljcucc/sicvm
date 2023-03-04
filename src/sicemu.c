#include "sicemu.h"
#include "sic.h"

#include <stdio.h>
#include <stdlib.h>

/* uncomment for switching to SICXE */
#define SICXE

#define PROG_START 0x10

const Uint8 test_rom[0x100] = {0x00};

int emu_boot(Sic *s) {
  Uint16 n;
  for (n = 0x100; --n; s->ram[PROG_START + n] = test_rom[n])
    ;
  return 1;
}

int emu_err(char *msg, char *err) {
  fprintf(stderr, "Error %s: %s\n", msg, err);
  return 1;
}

int main(int argc, char **argv) {
  Sic s;

  if (argc < 2)
    return emu_err("Usage", "sicemu test.rom args");

  if (!sic_init(&s, (Uint8 *)calloc(RAM_SIZE, sizeof(Uint8))))
    return emu_err("Init", "Failed");

  if (!emu_boot(&s))
    return emu_err("Boot", "Failed");

  sic_eval(&s, PROG_START);

  return 0;
}
