
#ifndef H_SICASM
#define H_SICASM

typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef unsigned int Uint32;

#define LDA 0x4C4441
#define LDX 0x4C4458
#define LDL 0x4C444C

#define STA 0x535441
#define STX 0x535458
#define STL 0x53544C

#define ADD 0x414444
#define SUB 0x535542
#define MUL 0x4D554C
#define DIV 0x444956

#define COMP 0x434F4D50
#define TIX 0x544958
#define JEQ 0x4A4551
#define JGT 0x4A4754
#define JLT 0x4A4C54
#define __J 0x4A

#define AND 0x414E44
#define _OR 0x4F52
#define JSUB 0x4A535542
#define RSUB 0x52535542
#define LDCH 0x4C444348
#define STCH 0x53544348

#define _RD 0x5244
#define _WD 0x5744
#define _TD 0x5444
#define STSW 0x53545357

/* mode: MSB [is_padd] [is_hex] >LSB*/

#define MODE_HEX_MASK 0x01

#define MODE_LIT 0x1
#define MODE_ABSP 0x3

#endif