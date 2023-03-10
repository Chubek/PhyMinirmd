#ifndef AC_MAIN_H
#define AC_MAIN_H

# include "bseq.h"
# include "kvec.h"
# include <string>
# include <cstring>

typedef struct mm128_t {
 	uint64_t x, y;

 	mm128_t() {}
 	mm128_t(uint64_t _x, uint64_t _y): x(_x), y(_y) {}

 	bool operator < (const mm128_t a) const {
 		// return x < a.x && y < a.y;
 		return y < a.y || (y == a.y && x < a.x);
 	}

 	bool operator == (const mm128_t a) const {
 		return x == a.x && y == a.y;
 	}

 	bool operator != (const mm128_t a) const {
 		return x != a.x || y != a.y;
 	}
} mm128_t;

typedef struct mm192_t {
	mm128_t x;
 	uint64_t y;

 	mm192_t() {}
 	mm192_t(mm128_t _x, uint64_t _y): x(_x), y(_y) {}
 	mm192_t(uint64_t _x1, uint64_t _x2, uint64_t _y): x(_x1, _x2), y(_y) {}
} mm192_t;
typedef struct { size_t n, m; mm192_t *a; } mm192_v;

typedef struct {
	size_t x, y, z;
} mmrec_t;

typedef struct {
	size_t a, b;
} segmemt_t;

typedef struct { size_t n, m; mm128_t *a; } mm128_v;
typedef struct { size_t n, m; uint64_t *a; } uint64_v;
typedef struct { size_t n, m; mmrec_t *a; } mmrec_v;
typedef struct { size_t n, m; segmemt_t *a; } segmemt_v;

extern unsigned char seq_nt4_table[256];

// void mm_sketch(const char *str, int len, int k, uint32_t rid, mm128_t *p);
// void mm_sketch_rc(const char *str, int len, int k, uint32_t rid, mm128_t *p);
// void mm_sketch(const char *str, const int &len, const int &k, const uint32_t &rid, mm128_t *p);
// void mm_large_sketch(const char *str, int len, int k, uint32_t rid, mm192_t *p);
// void mm_sketch_rc(const char *str, const int &len, const int &k, const uint32_t &rid, mm128_t *p);
void radix_sort_128x(mm128_t *beg, mm128_t *end);

# define ROTATE_RIGHT_16(x, d) x = (x >> d) | (x << (16 - d))

# define REALLOC_DYNAMIC_MEM(ty, arr, new_size) 						\
do { 																	\
	void *nnptr = realloc(arr, new_size * sizeof(ty));					\
																		\
	if (!nnptr) {														\
		cerr << "\033[1;31mError:\033[0m Reallocating dynamic memory";	\
		exit(1);														\
	}																	\
																		\
	arr = (ty*)nnptr;													\
																		\
} while(0)


typedef struct SizeClusterSolo {
	bseq1_t *this_cluster;
	uint16_t this_size;
	uint8_t set_one;
} size_cluster_t;


typedef struct SizeClusterCollective {
	size_cluster_t *clusters;
	uint16_t no_clusters;
	uint16_t curr_index;
} size_cluster_collective_t;

# define SZ_CLST_S sizeof(size_cluster_t)
# define SZ_CLST_C sizeof(size_cluster_collective_t)
# define ROT_NUM 2


#endif