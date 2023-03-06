#include <stdio.h>
#include <stdlib.h>

/* uncomment for switching to SICXE */
// #define SICXE

#include "sicemu.h"
#include "sic.h"


#define PROG_START 0x10

int emu_boot(Sic *s, char *filename) {
  Uint16 n;
  Uint8 c;
  FILE *f;

  if((f = fopen(filename, "r")) == NULL) return 0;
  for(n=PROG_START; (c=fgetc(f)) != 0xFF; s->ram[n++] = c);
  fclose(f);
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
}

void sic_deo (Uint8 id, Uint8 val){
  switch(id){
    case 0x01: putc(val, stdout); break;
  }
}

int main(int argc, char **argv) {
  Sic s;

  if (argc < 2)
    return emu_err("Usage", "sicemu test.rom args");

  if (!sic_init(&s, (Uint8 *)calloc(RAM_SIZE, sizeof(Uint8)), PROG_START))
    return emu_err("Init", "Failed");

  if (!emu_boot(&s, argv[1]))
    return emu_err("Boot", "Failed");

  sic_eval(&s);

  return 0;
}
