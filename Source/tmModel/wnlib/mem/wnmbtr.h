/****************************************************************************

COPYRIGHT NOTICE:

  The source code in this file is provided free of charge
  to the author's consulting clients.  It is in the
  public domain and therefore may be used by anybody for
  any purpose.

AUTHOR:

  Bill Chapman

****************************************************************************

    This module is intended to be called by modules wnmbtr.c and wnmemg.c
  for a specific purpose.  Using it for anything else could cause problems.
  Ideally, this .h file should not be published outside of the mem
  directory.

****************************************************************************/
#ifndef wnmbtrH
#define wnmbtrH


#if !defined(wnmbtrC) && !defined(wnmemgC) && !defined(wnmbtsC)
# error wnmbtr.h included by file other than wnmbtr.c, wnmemg.c, and wnmbts.c
#endif


#include "wnlib.h"
#include "wnmem.h"
#include <stddef.h>  /* For size_t and max_align_t */

/* Get max alignment requirement for the platform */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
  #include <stdalign.h>
  #define WN_MAX_ALIGN alignof(max_align_t)
#else
  #define WN_MAX_ALIGN (sizeof(void*) * 2)
#endif

#define WN_MB_MIN    (-3)
#define WN_MB_MAX    3
#define WN_MB_LT     (-2)
#define WN_MB_GT     2
#define WN_MB_LE     (-1)
#define WN_MB_GE     1
#define WN_MB_EQ     0

/* Forward declarations */
struct wn_mbnode_struct;
struct wn_mbhandle_struct;
struct wn_mbtree_struct;
struct wn_free_block_struct;

/* Type definitions */
typedef struct wn_mbnode_struct* wn_mbnode;
typedef struct wn_mbhandle_struct* wn_mbhandle;
typedef struct wn_mbtree_struct* wn_mbtree;
typedef struct wn_free_block_struct* wn_free_block;

/* Node structure definition */
struct wn_mbnode_struct {
    wn_mbnode left;
    wn_mbnode right;
    void* key;
};

/* Handle structure definition */
struct wn_mbhandle_struct {
    wn_mbnode node;
    wn_free_block next_free_block;  /* it is imperative that this
  **  be the 1st field, small free blocks will use this field but
  **  not the rest of the struct */

  wn_free_block free_block_list;  /* This is a header of a list
  **  of all the free blocks of this exact size, not including this one */

  void* key;  /* size of the segment.  Redundant with the free_block_size
  **  field in the *wn_free_block, easier to leave it in */

  int level, count;

  wn_mbhandle left_child, right_child, parent;
};

/* Tree structure definition */
struct wn_mbtree_struct
{
  wn_mbhandle handle_tree;

  int (*pcompare_keys_func)(ptr key1,ptr key2);
};

/* A free block consists of a size field and a handle pointer. We ensure proper
** alignment by using explicit padding. */
struct wn_free_block_struct {
    size_t free_block_size;  /* Changed from int to size_t for 64-bit safety */
    char _padding[((sizeof(size_t) + WN_MAX_ALIGN - 1) & ~(WN_MAX_ALIGN - 1)) - sizeof(size_t)];
};

/* Macros for memory block tree handling */
#define WN_MBHANDLE_TO_MBNODE(handle) ((handle)->node)
#define WN_FREE_BLOCK_TO_MBHANDLE(free_block) ((wn_mbhandle)(free_block))
#define WN_MBHANDLE_TO_FREE_BLOCK(mbhandle) ((wn_free_block)(void*)((char*)(mbhandle) - sizeof(struct wn_free_block_struct)))

/* Calculate the size of the free block struct accounting for alignment */
#define WN_SIZEOF_FREE_BLOCK_STRUCT \
    sizeof(struct wn_free_block_struct)

EXTERN void wn_mmkptrbtree(wn_mbtree tree);
EXTERN void wn_mbget(wn_mbhandle *phandle,wn_mbtree tree,ptr key,int compare);
EXTERN void wn_mbins(wn_mbhandle   handle,wn_mbtree tree, ptr key);
EXTERN void wn_mbdel(wn_mbhandle handle,wn_mbtree tree);
EXTERN int wn_mbcount(wn_mbtree tree);

/* don't EXTERN this one - it confuses some (but not all) sparc compilers */
#if !defined(sparc)
  EXTERN void wn_mbact(wn_mbtree tree, void (*paction)(wn_mbhandle handle),
      ptr low_key,int low_compare,ptr high_key,int high_compare);
#else
   void wn_mbact(wn_mbtree tree, void (*paction)(wn_mbhandle handle),
      ptr low_key,int low_compare,ptr high_key,int high_compare);
#endif

EXTERN void wn_mbverify(wn_mbtree tree);

#endif /* wnmbtrH */
