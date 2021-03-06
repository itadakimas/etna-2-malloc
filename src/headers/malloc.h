#ifndef _MALLOC_H
#define _MALLOC_H

  //////////////////////////////////////////////////////////////
  // PREPROCESSOR CONSTANTS
  //////////////////////////////////////////////////////////////
  #define _BSD_SOURCE // @note: fixes "implicit declaration of function ‘sbrk’" error

  //////////////////////////////////////////////////////////////
  // MACROS
  //////////////////////////////////////////////////////////////
  #define MALLOC_SBRK_FAILED(SBRK_RETURN) ((SBRK_RETURN) == ((void *)-1))

  //////////////////////////////////////////////////////////////
  // INCLUDES
  //////////////////////////////////////////////////////////////
  #include <stdbool.h>
  #include <stddef.h>
  #include <string.h>
  #include <sys/types.h>
  #include <unistd.h>
  #include "structures.h"
  #include "types.h"
  #include "chunks.h"
  #include "bins.h"


  //////////////////////////////////////////////////////////////
  // PROTOTYPES
  //////////////////////////////////////////////////////////////
  void          free(void *);
  void          *calloc(size_t, size_t);
  void          *malloc(size_t);
  t_malloc_data *_internal_malloc_get_data();

#endif
