#if defined(SICXE)
#define RAM_SIZE 0x100000
#else
#define RAM_SIZE 0x8000
#endif

typedef unsigned char Uint8;
typedef signed char Sint8;
typedef unsigned short Uint16;
typedef signed short Sint16;
typedef unsigned int Uint32;

typedef struct Sic {
  Uint8 *ram;
} Sic;

int sic_init(Sic *s, Uint8 *ram);
int sic_eval(Sic *s, Uint16 pc);