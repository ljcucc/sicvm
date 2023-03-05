#include <stdio.h>
#include <stdlib.h>

/* uncomment for switching to SICXE */
// #define SICXE

#include "sicemu.h"
#include "sic.h"


#define PROG_START 0x10

const Uint8 test_rom[0x100] = {
  0x50, 0x00, 0x19,  /* LDCH 0016 */
  0xDC, 0x00, 0x01,  /* 13 WD 0001 */
  0x3C, 0x00, 0x10,  /* 16 JUMP 0010 */
  0x41               /* 19 'A' */
};

int emu_boot(Sic *s) {
  Uint16 n;
  for (n = 0x100; n-- ; s->ram[PROG_START + n] = test_rom[n]){
    printf("[%02X]%02X;",n, test_rom[n]);
  }
  puts("boot!");
  return 1;
}

int emu_err(char *msg, char *err) {
  fprintf(stderr, "Error %s: %s\n", msg, err);
  return 1;
}

Uint8 sic_dei (Uint8 id) {
  switch(id){
    case 0x01: return getc(stdin);
  }
  return 0;
}

void sic_deo (Uint8 id, Uint8 val){
  // printf("output: %02X, %02X\n", id, val);
  switch(id){
    case 0x01: putc(val, stdout); break;
  }
  return 0;
}

int main(int argc, char **argv) {
  Sic s;

  if (argc < 2)
    return emu_err("Usage", "sicemu test.rom args");

  if (!sic_init(&s, (Uint8 *)calloc(RAM_SIZE, sizeof(Uint8)), PROG_START))
    return emu_err("Init", "Failed");

  if (!emu_boot(&s))
    return emu_err("Boot", "Failed");

  sic_eval(&s);

  return 0;
}
