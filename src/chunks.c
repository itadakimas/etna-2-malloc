#include "headers/malloc.h"


void                *_internal_malloc_chunk_create(t_malloc_bins *bin)
{
  t_malloc_chunks   *current_chunk;
  t_malloc_chunks   *new_chunk;

  new_chunk = NULL;
  // @note: we allocate memory for the chunk and meta data at the same time
  new_chunk = sbrk((sizeof(t_malloc_chunks) + bin->size));
  if (new_chunk == NULL)
  {
    return (NULL);
  }
  new_chunk->bin = bin;
  new_chunk->is_free = false;
  new_chunk->next = NULL;
  new_chunk->ptr = (new_chunk + 1);
  if (bin->chunks == NULL)
  {
    bin->chunks = new_chunk;
  }
  else
  {
    current_chunk = bin->chunks;
    while (current_chunk->next != NULL)
    {
      current_chunk = current_chunk->next;
    }
    current_chunk->next = new_chunk;
  }
  return (new_chunk->ptr);
}

t_malloc_chunks     *_internal_malloc_chunk_find(void *addr)
{
  t_malloc_bins     *current_bin;
  t_malloc_chunks   *current_chunk;
  t_malloc_chunks   *target_chunk;
  t_malloc_data     *malloc_data;

  malloc_data = _internal_malloc_get_data();
  current_bin = malloc_data->bins;
  current_chunk = NULL;
  target_chunk = NULL;
  while (target_chunk == NULL && current_bin != NULL)
  {
    current_chunk = current_bin->chunks;
    while (target_chunk == NULL && current_chunk != NULL)
    {
      if (current_chunk->ptr == addr)
      {
        target_chunk = current_chunk;
      }
      current_chunk = current_chunk->next;
    }
    current_bin = current_bin->next;
  }
  return (target_chunk);
}

void                _internal_malloc_chunk_free(t_malloc_chunks *chunk)
{
  t_malloc_bins     *bin;

  bin = chunk->bin;
  memset(chunk->ptr, 0, bin->size);
  chunk->is_free = true;
  bin->free_chunks++;
  return;
}

void                *_internal_malloc_chunk_use_free(t_malloc_bins *bin)
{
  t_malloc_chunks   *current_chunk;
  void              *ptr;

  current_chunk = bin->chunks;
  ptr = NULL;
  while (current_chunk != NULL)
  {
    if (current_chunk->is_free)
    {
      ptr = current_chunk->ptr;
      current_chunk->is_free = false;
      break;
    }
    current_chunk = current_chunk->next;
  }
  return (ptr);
}
