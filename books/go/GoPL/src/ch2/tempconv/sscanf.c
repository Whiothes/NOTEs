#include <stdio.h>

int main()
{
    char date[] = "20180606";

    int total_date;
    int total_mon;
    int total_year;

    sscanf(date, "%04d%02d", &total_year, &total_mon);
    total_date = atoi(date);

    printf("%d\n%d\n%d\n", total_date, total_year, total_mon);
}


