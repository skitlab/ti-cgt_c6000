/*****************************************************************************/
/* MAIN.C - defines main() and static function local() for Cache Layout      */
/*          Tool Tutorial.                                                   */
/*****************************************************************************/
#include <stdio.h>

void lots(int i);
void rare();
static void local();

/*****************************************************************************/
/* MAIN() - calls rare() once; calls main.c:local() 4 times.                 */
/*****************************************************************************/
void main()
{
   int i;
   rare();
   for (i = 1; i < 5; i++)
      local();
   printf("\n"); 
   fflush(stdout);
}

/*****************************************************************************/
/* LOCAL() - calls lots() 80 times.                                          */
/*****************************************************************************/
static void local()
{
   int i;
   printf("-"); 
   for (i = 0; i < 20; ++i)
      lots(i);
}
