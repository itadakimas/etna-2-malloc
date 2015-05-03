#include "headers/malloc.h"

static t_malloc_data g_malloc_data;

void                *malloc(size_t size)
{
  t_malloc_bins     *best_bin;

  if (size > MALLOC_BIN_MAX_SIZE)
  {
    return (NULL);
  }
  if (g_malloc_data.is_initialized != true)
  {
    g_malloc_data.base_data_segment_addr = sbrk(0);
    if (MALLOC_SBRK_FAILED(g_malloc_data.base_data_segment_addr))
    {
      return (NULL);
    }
    if (!_internal_malloc_bins_init())
    {
      return (NULL);
    }
    g_malloc_data.last_chunk = NULL;
    g_malloc_data.is_initialized = true;
  }
  best_bin = _internal_malloc_bin_find_best(size);
  if (best_bin->free_chunks == 0)
  {
    return (_internal_malloc_chunk_create(best_bin));
  }
  else
  {
    return (_internal_malloc_chunk_use_free(best_bin));
  }
}

void                free(void *ptr)
{
  t_malloc_chunks   *chunk;

  chunk = _internal_malloc_chunk_find(ptr);
  if (chunk == NULL || chunk->is_free)
  {
    return;
  }
  if (chunk == g_malloc_data.last_chunk)
  {
    _internal_malloc_chunk_destroy(chunk);
  }
  else
  {
    _internal_malloc_chunk_free(chunk);
  }
  return;
}

t_malloc_data *_internal_malloc_get_data()
{
  return &g_malloc_data;
}
