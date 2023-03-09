#include <stdio.h>
#include <stdlib.h>

/* upward compatible instruction set */

#include "sicasm.h"

#define OPC(op, bc) case op: w=bc; goto push_to_rom;

/* OPC: opcode to bytecode macro, which is easy to switch to jump table
      op: Opcode
      bc: Bytecode

  opbuf: the char that script typed. 
         or enabled for "buffer final jump" when a grammer statement ended by set to 0xFF.
*/

int emu_asm(char *filename) {
  Uint32 n, opbuf=0, w=0;
  Uint8 ch;
  FILE *f;
  Uint8 rom[0x10000];

  void *buf_final = 0;

  if((f = fopen(filename, "r")) == NULL) return 0;

  for(n=0; (ch=fgetc(f)) != 0xFF; ){
    if (ch == ' ' || ch == '\n' || ch == '\t')  /* reset scan */
    {
      if(buf_final) goto *buf_final;
      opbuf = 0;
      continue;
    }

    if (ch == '|') /* aboslute padding */
    {
      opbuf = 0xFF;
      buf_final = &&abs_padding__final;
      continue;
    }

    if (ch == '#')
    {
      opbuf = 0xFF;
      buf_final = &&push_to_rom;
      continue;
    }

    if (opbuf&0xFF == 0xFF)
    {
      w <<= 4;
      if (ch & '_' < 'G') /* case of HEX A~F */ w |= (0x0F & ch) + 9;
      else if (ch >= '0' && ch <= '9') w |= (0x0F & ch);
      else return 1;
      continue; /* skip pushing */
    }

    /* default */
    opbuf <<= 0x8;
    opbuf |= ch;

    /*opbuf should never be 0xFF. that value never be able to typed, or whether it isn't a ASCII code*/
    if(opbuf == 0xFF) return 1; 

    switch(opbuf)
    {
      OPC(LDA, 0x00)
      OPC(LDX, 0x04)
      OPC(LDL, 0x08)
      OPC(STA, 0x0c)
      OPC(STX, 0x10)
      OPC(STL, 0x14)
      OPC(ADD, 0x18)
      OPC(SUB, 0x1c)
      OPC(MUL, 0x20)
      OPC(DIV, 0x24)
      OPC(COMP,0x28)
      OPC(TIX, 0x2c)
      OPC(JEQ, 0x30)
      OPC(JGT, 0x34)
      OPC(JLT, 0x38)
      OPC(__J, 0x3c)
      OPC(AND, 0x40)
      OPC(_OR, 0x44)
      OPC(JSUB, 0x48)
      OPC(RSUB, 0x4c)
      OPC(STCH, 0x54)
      OPC(LDCH, 0x50)
      OPC(_RD, 0xd8)
      OPC(_WD, 0xdc)
      OPC(_TD, 0xe0)
      OPC(STSW,0xe4)
      default: w=0;
    }

    continue;

  /* set w to n (the position that rom will written)  */
  abs_padding__final:
    printf("pos: %02x\n",w);
    n = w;
    buf_final = 0;
    continue;

  push_to_rom:
    opbuf = 0;
    buf_final = 0;
    rom[n++] = w;
    printf("> %02x\n", w);
    w=0;
  }

  fclose(f);
  return 1;
}

int emu_err(char *msg, char *err) {
  fprintf(stderr, "Error %s: %s\n", msg, err);
  return 1;
}

int main(int argc, char**argv){
  if(argc < 2)
    emu_err("Usage", "sicasm prog.sic");
  
  if(!emu_asm(argv[1]))
    emu_err("File", "Cannot open file.");

  printf("done\n");
  
  return 0;
}