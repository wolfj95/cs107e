static volatile unsigned int *FSEL2 = (unsigned int *)0x20200008;
static volatile unsigned int *SET0  = (unsigned int *)0x2020001C;
static volatile unsigned int *CLR0  = (unsigned int *)0x20200028;

void main(void)
{
   *FSEL2 = 1;

   while (1) {
      *SET0 = 1 << 20;
      for (int i = 0; i < 0x3f0000; i++) ;
      *CLR0 = 1 << 20;
      for (int i = 0; i < 0x3f0000; i++) ;
   }
}