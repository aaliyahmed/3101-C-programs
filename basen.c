/* basen.c -- prints integer in base 2–16 */

#include <stdio.h>


void to_base_n(unsigned long n, int base);

int main(void)
{
    unsigned long number;
    int base;

    printf("Enter a number and base (2-16) (q to quit):\n");

    while (scanf("%lu %d", &number, &base) == 2)
    {
        if (base < 2 || base > 16)
        {
            printf("Base must be between 2 and 16.\n");
        }
        else
        {
            printf("Base-%d : ", base);

            if (base == 8)
                printf("0");
            else if (base == 16)
                printf("0x");

            to_base_n(number, base);
            putchar('\n');
        }

        printf("Enter an integer and base (2-16) (q to quit):\n");
    }

    printf("Done.\n");

    return 0;
}

void to_base_n(unsigned long n, int base)
{
    int r;
    char values[] = "0123456789ABCDEF";

    r = n % base;

    if (n >= base)
        to_base_n(n / base, base);

    putchar(values[r]);
}