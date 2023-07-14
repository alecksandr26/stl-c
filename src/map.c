#include <assert.h>
#include <tc.h>
#include "../include/stl/map.h"
#include "../include/stl/linked.h"
#include "../include/stl/gen.h"
#include "../include/stl/ex.h"

size_t default_hash_map_func(unsigned char *key, size_t key_size)
{
	size_t h = 1;

	for (size_t i = 0; i < key_size; i++)
		h += h * key[i];
	
	return h;
}

size_t __stl_map_map_key(__stl_map_t *map, unsigned char *key, size_t key_size)
{
	assert(key != 0);
	__stl_linked_t *l = (__stl_linked_t *) (map->con.addr);
	size_t m;
	
	if (key_size >= l->con.dtype_size)
		throw(InvalidKey);

	m = default_hash_map_func(key, key_size) % map->con.capacity;
	return m;
}

__stl_link_node_t *__stl_map_ins(__stl_map_t *map, size_t ibucket)
{
	assert(map != NULL);
	assert(ibucket < map->con.capacity);

	__stl_linked_t *l = (__stl_linked_t *) (map->con.addr
						+ ibucket * map->con.dtype_size);

	return __stl_linked_ins_after_byindex(l, (l->con.size == 0) ? -1 : __stl_linked_back(l));
}



__stl_link_node_t *__stl_map_get(__stl_map_t *map, size_t ibucket)
{
	assert(map != NULL);
	assert(ibucket < map->con.capacity);


	__stl_linked_t *l = (__stl_linked_t *) (map->con.addr
						+ ibucket * map->con.dtype_size);

	
}


