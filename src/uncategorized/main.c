#include <stdio.h>

int main(void)
{
    float a, b, h;

    printf("a:");
    scanf("%f", &a);

    printf("b:");
    scanf("%f", &b);

    printf("h:");
    scanf("%f", &h);

    printf("Area is %.1f", (a + b) * h / 2);

    return 0;
}