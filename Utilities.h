#ifndef Utilities__H_
#define Utilities__H_

#define SET(reg,val)    reg|=val
#define CLR(reg,val)    reg&=~val
#define Read(reg,val)    reg&=val
#define SETBit(REG,P) (REG |= (1<<P))
#define CLRBit(REG,P) (REG &= ~(1<<P))
#define ReadBit(reg,p) (reg&(1<<p))

#endif
