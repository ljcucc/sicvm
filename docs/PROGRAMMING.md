# Programming in binary

You can using any hex editor you want. Here's an example of outputing 'A' all the time:

```
50 00 19  ; 10  LDCH 19 
DC 00 01  ; 13  WD   01
3C 00 10  ; 16  J    10
41 00 00  ; 19
```