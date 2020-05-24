#include "sys.h"
#include <math.h>

u8 ascii2bcd(u8 *asciibuff)
{
    static u8 i;
    u8 bcd = 0, cap;
    
    for (i = 0; i < 3; i++)
    {
        if (asciibuff[i] >= 'A' && asciibuff[i] <= 'F')
        {
            cap = asciibuff[i]-'A' + 10;
        }
        else if (asciibuff[i] >= '0' && asciibuff[i] <= '9')
        {
            cap = asciibuff[i]-'0';
        }
        cap *= pow(10, (2-i));
        bcd += cap;
    }
    return bcd;
}
