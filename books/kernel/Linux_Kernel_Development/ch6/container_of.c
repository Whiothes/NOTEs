#include <stdio.h>
#include <stdlib.h>

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member)                                        \
    ({                                                                         \
        const typeof(((type *)0)->member) *__mptr = (ptr);                     \
        (type *)((char *)__mptr - offsetof(type, member));                     \
    })


struct test{
    int num;
};

int main()
{
    struct test t = {8};
    int *p_n = &t.num;

    struct test *p_t = container_of(p_n, struct test, num);
    printf("%p\n", p_t);
    printf("%d\n", p_t->num);
}
