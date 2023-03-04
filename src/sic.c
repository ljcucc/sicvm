#include <stdio.h>
#include "sic.h"

/*	a,b,c, i, j, k: general use. 
    rs: for registers A, indeX, Linkage, StatusWord
    iflags: instrction flags
*/

#define M24 0x00FFFFFF

#define ST(addr, val) { for(a=val, i=3; i--; s->ram[addr+i]=0xFF&a,a>>=8); }
#define LD(addr)      ({ for(a=0, i=3; i--; a=(s->ram[addr+i] << (i<<3))); a;})

#define RA rs[0]
#define RX rs[1]
#define RL rs[2]
#define RSW rs[3]

#define SW_EQL (1<<3)
#define SW_GTH (1<<1)
#define SW_LTH (1<<2)

int sic_eval(Sic *s, Uint16 pc)
{
  Uint8 opcode, disp, iflags=0, opseek, i, j, k;
  Uint32 a, b, c, rs[0xF];

  for (;;)
  {
    opcode = (s->ram[pc + 1] & 0xFC); /* only looking for valid opcode for sicxe  */
    disp = (s->ram[pc + 2] << 8) | s->ram[pc + 3];
    iflags |= (disp >> 12);

    opseek = LD(disp);

    switch (opcode)
    {
    case 0x00: /* LDA: 00 */
    case 0x04: /* LDX: 01 */
    case 0x08: /* LDL: 10 */
      rs[0x0F & opcode >> 2] = opseek;
      break;

    case 0x0C: /* STA: 11 + 01 = 00 */
    case 0x10: /* STX: 00 + 01 = 01 */
    case 0x14: /* STL: 01 + 01 = 10 */
      ST(disp, rs[(0x0F & opcode >> 2) + 1]);
      break;

    case 0x18: /* ADD */ RA += opseek << 8; RA&=M24; break;
    case 0x1C: /* SUB */ RA -= opseek << 8; RA&=M24; break;
    case 0x20: /* MUL */ RA *= opseek << 8; RA&=M24; break;
    case 0x24: /* DIV */ RA /= opseek << 8; RA&=M24; break;

    case 0x28: /* COMP */ a=opseek; RSW=(a>RA&SW_GTH)|(a<RA&SW_LTH)|(a==RA&SW_EQL); break;
    case 0x2C: /* TIX */ break;

    case 0x30: /*JEQ*/ if(RSW & SW_EQL) pc=disp; break;
    case 0x34: /*JGT*/ if(RSW & SW_GTH) pc=disp; break;
    case 0x38: /*JLT*/ if(RSW & SW_LTH) pc=disp; break;
    case 0x3C: /*J*/ pc=disp; break;

    case 0x40: /* AND */ RA&=opseek; break;
    case 0x44: /* OR */ RA|=opseek; break;
    case 0x48: /* JSUB */ RL=pc; pc=opseek; break;
    case 0x4C: /* RSUB*/ pc=RL; break;

    case 0x50: /* LDCH */ break;
    case 0x54: /* STCH */ break;

    case 0xD8: /* RD */ break;
    case 0xDC: /* WD */ break;
    case 0xE0: /* TD */ break;
    case 0xE8: /* STSW */ break;

    default:
      return -1;
    }

    if ((pc += 3) & 0xF8000) /* if over page one, then break */
      break;
  }
  return 1;
}

int sic_init(Sic *s, Uint8 *ram)
{
  Uint16 i;
  s->ram = ram;
  for(i = RAM_SIZE; --i; s->ram[i]=0);
  return 1;
}