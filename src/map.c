#include <assert.h>
#include <stddef.h>
#include <tc.h>
#include "../include/stl/map.h"
#include "../include/stl/linked.h"
#include "../include/stl/gen.h"
#include "../include/stl/except.h"
#include "../include/stl/def.h"

static int __stl_map_keycmp(__stl_pair_t *pair, unsigned char *key, size_t pair_size)
{
	assert(key != NULL);
	assert(pair != NULL);
	
	(void) pair_size;
	for (size_t i = 0; i < pair->size_first; i++) {
		int cmp = pair->addr_first[i] - key[i];
		if (cmp)
			return cmp;
	}
	return 0;
}

static size_t default_hash_map_func(unsigned char *key, size_t key_size)
{
	size_t h = 1;

	assert(key != NULL);
	assert(key_size > 0);

	for (size_t i = 0; i < key_size; i++)
		h += h * key[i];
	
	return h;
}

static void __stl_dmap_realloc(__stl_map_t *map)
{
	assert(map != NULL);

	for (size_t i = 0; i < st_capacity(*map); i++) {
		__stl_linked_t *l = (__stl_linked_t *) (map->con.addr
							+ i * map->con.dtype_size);
		__stl_iter_t iter;
		for (linked_begin(*l, iter); iter_index(iter) < (int) st_size(*l); iter_next(iter)) {
			
		}
	}
}

size_t __stl_map_map_key(__stl_map_t *map, unsigned char *key, size_t key_size)
{
	assert(key != NULL);
	assert(map != NULL);
	assert(key_size > 0);
	
	__stl_linked_t *l = (__stl_linked_t *) (map->con.addr);
	size_t m;
	
	if (key_size >= l->con.dtype_size)
		throw(InvalidKey);

	m = default_hash_map_func(key, key_size) % map->con.capacity;
	return m;
}


unsigned char *__stl_map_ins(__stl_map_t *map, size_t ibucket, unsigned char *key)
{
	assert(map != NULL);
	assert(key != NULL);
	assert(ibucket < map->con.capacity);

	__stl_linked_t *l = (__stl_linked_t *) (map->con.addr
						+ ibucket * map->con.dtype_size);

	int index = linked_find(*l, key,
				(int (*)(unsigned char *, unsigned char *, unsigned long))
				__stl_map_keycmp);
	if (index == -1 && st_size(*l) > 0)
		throw(KeyAlreadyExist);
	
	return __stl_linked_ins_after_byindex(l, (l->con.size == 0) ? -1 : __stl_linked_back(l));
}

unsigned char *__stl_map_get(__stl_map_t *map, size_t ibucket, unsigned char *key)
{
	assert(map != NULL);
	assert(key != NULL);
	assert(ibucket < st_capacity(*map));

	
	__stl_linked_t *l = (__stl_linked_t *) (map->con.addr
						+ ibucket * map->con.dtype_size);
	if (st_size(*l) == 0)
		throw(KeyNotFound);

	int index = linked_find(*l, key[0],
				(int (*)(unsigned char *, unsigned char *, unsigned long))
				__stl_map_keycmp);
	
	if (index == -1)
		throw(KeyNotFound);
	return ((__stl_pair_t *) (l->con.addr + __stl_linked_at(l, index) * l->con.dtype_size))->addr_second;
}

unsigned char *__stl_map_rep(__stl_map_t *map, size_t ibucket, unsigned char *key)
{
	assert(map != NULL);
	assert(key != NULL);
	assert(ibucket < st_capacity(*map));

	__stl_linked_t *l = (__stl_linked_t *) (map->con.addr
						+ ibucket * map->con.dtype_size);

	if (st_size(*l) == 0)
		throw(KeyNotFound);

	int index = linked_find(*l, key[0],
				(int (*)(unsigned char *, unsigned char *, unsigned long))
				__stl_map_keycmp);

	if (index == -1)
		throw(KeyNotFound);

	return l->con.addr + __stl_linked_at(l, index) * l->con.dtype_size;
}

unsigned char *__stl_map_rem(__stl_map_t *map, size_t ibucket, unsigned char *key)
{
	assert(map != NULL);
	assert(key != NULL);
	assert(ibucket < st_capacity(*map));

	__stl_linked_t *l = (__stl_linked_t *) (map->con.addr
						+ ibucket * map->con.dtype_size);

	if (st_size(*l) == 0)
		throw(KeyNotFound);

	int index = linked_find(*l, key[0],
				(int (*)(unsigned char *, unsigned char *, unsigned long))
				__stl_map_keycmp);
	if (index == -1)
		throw(KeyNotFound);

	return ((__stl_pair_t *) __stl_linked_rem_byindex(l, index))->addr_second;
}


