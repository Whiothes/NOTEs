#ifndef MALLOC_H
#define MALLOC_H


typedef long Align;
union header {
  struct {
    union header *ptr;
    unsigned size;
  } s;
  Align x;
};
typedef union header Header;

#define NALLOC 1024

#endif /* MALLOC_H */
