# Op-codes

## Op-code sheet

|  | 00 | 04 | 08 | 0C |
|--|----|----|----|----|
| 00 | **LDA m** | **LDX m** | **LDL m** | **STA m** |
| 10 | **STX m** | **STL m** | **ADD m** | **SUB m** |
| 20 | **MUL m** | **DIV m** | **COMP m** | **TIX m** |
| 30 | **JEQ m** | **JGT m** | **JLT m** | **J m** |
| 40 | **AND m** | **OR m** | **JSUB m** | **RSUB m** |
| 50 | **LDCH m** | **STCH m** | ADDF m | SUBF m |
| 60 | MULF m | DIVF m | LDB m | LDS m |
| 70 | LDF m | LDT m | STB m | STS m |
| 80 | STF m | STT m | COMPF m |  |
| 90 | ADDR r1,r2 | SUBR r1,r2 | MULR r1,r2 | DIVR r1,r2 |
| A0 | COMPR r1,r2 | SHIFTL r1,n | SHIFTR r1,n | RMO r1,r2 |
| B0 | SVC an | CLEAR r1 | TIXR r1 |  |
| C0 | FLOAT | FLOAT | NORM |  |
| D0 | LPS m | STI m | **RD m** | **WD m** |
| E0 | **TD m** |  | **STSW m** | SSK m |
| F0 | SIO | HIO | TIO |  |

> **BOLD OP-CODE** are SIC compatible instructions, which both works on SIC and SIC/XE.