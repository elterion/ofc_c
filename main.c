#include "./kev/kev_eval.h"
#include <stdio.h>
#include <time.h>

int main()
{

    int res = kev_eval_5cards(28, 33, 26, 37, 40);

    printf("%d\n", res);

    return 0;
}