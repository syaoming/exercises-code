/*
 * mm-naive.c - The fastest, best memory-efficient malloc package.
 *
 * In this approach, a bunch of segregated free list of fixed size-range
 * is maintained by the allocator. This allow log-time free and constant
 * overhead for the segregated list structure.
 *
 * At the head region of the heap, we maitained a fixed size array of root
 * pointers for all size class.For a
 * SegList of size k, it store free blocks of size at least 2^k bytes.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    " ",
    /* First member's full name */
    " ",
    /* First member's email address */
    " ",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};


/************************************************************
 * Useful constant and macros for implementing the allocator
 ************************************************************/

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8
#define CHUNK (1 << 12)

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)

/* size of some general data type */
#define SIZE_T_SIZE sizeof(size_t)
#define POINTER_SIZE (sizeof(void *))

/* size of overheads */
#define SEGLIST_ROOT_SIZE  (SIZE_T_SIZE + POINTER_SIZE)  /* mimics a header */
#define HDR_SIZE           SIZE_T_SIZE   /* size for block header */
#define LINK_SIZE          (POINTER_SIZE + POINTER_SIZE)  /* bi-direction */
#define FTR_SIZE           SIZE_T_SIZE   /* size for free block footer */
#define EPIL_SIZE          HDR_SIZE         /* epilogue padding */
#define PROL_SIZE          (ALIGN(HDR_SIZE) - EPIL_SIZE)  /* prologue padding */
#define MIN_BLOCK_SIZE     ALIGN(HDR_SIZE + LINK_SIZE + FTR_SIZE)  /* free */

/* pack a size, a allocated bit and a prev-allocated bit into a word */
#define PACK(size, alloc_prev, alloc) ((size)|(alloc_prev)|(alloc))

/* read and write a word at address p */
#define GETW(p) (*(uint32 *) (p))  /* a word is 4 bytes */
#define GETD(p) (*(uint64 *) (p))  /* a dword is 8 bytes */
#define GETS(p) (*(size_t *) (p))  /* access as a size_t */
#define GETP(p) (*(char **)  (p))  /* access as a pointer */

/* access the size and allocaterd fileds from block header p */
#define GET_SIZE(p)       (GETS(p) & ~0x7)
#define GET_ALLOC(p)      (GETS(p) & 0x1)
#define GET_ALLOC_PREV(p) (GETS(p) & 0x2)

/* locate header and footer for a block address bp.
 * the footer locating is only safe for free block pointer ! */
#define HDRP(bp)  ((char *) (bp))
#define FTRP(fbp) ((char *) (fbp) + GET_SIZE(HDRP(fbp)) - SIZE_T_SIZE)

/* locate the slot for 'next' and 'prev' for a free block address fbp */
#define SUCCP(fbp) (HDRP(fbp) + SIZE_T_SIZE)
#define PREDP(fbp) (HDRP(fbp) + SIZE_T_SIZE + POINTER_SIZE)

/* access the slot of a list root */
#define GET_CLASS_SIZE(rp) GETS(rp)
#define LARGER_CLASS(rp)  ((char *)(rp) + SEGLIST_ROOT_SIZE)
#define SMALLER_CLASS(rp) ((char *)(rp) - SEGLIST_ROOT_SIZE)

/* get the address of successor or predecessor block in a list.
 * used for jumping around seglist for a free block address fbp */
#define SUCC_BLKP(fbp) GETP(SUCCP(fbp))
#define PRED_BLKP(fbp) GETP(PREDP(fbp))

/* get the address of next of prevous block in the memory.
 * used for moving around blocks for a block address bp.
 * The second command works only if the previous block is free
 * (check this by GET_ALLOC_PREV ) */
#define NEXT_BLKP(bp)  ((char *)(bp) + GET_SIZE(HDRP(bp)))
#define PREV_BLKP(fbp) ((char *)(fbp) - GET_SIZE(HDRP(fbp) - SIZE_T_SIZE))

/* size range of SegList as power of 2 */
#define SEGLIST_NUM  10

/* some general purpose macro */
#define MIN(i, j) ((i) < (j) ? (i) : (j))
#define MAX(i, j) ((i) > (j) ? (i) : (j))


/**************************************
 * Implementing the interface alocator
 **************************************/

/*
 * Private variables and functions
 */
static char *mm_seglist_root;  /* points to root of the smallest SegList */
static char *mm_listp;         /* points to prologue block */
void mm_distribute(char *);    /* distribute a free block to seg lists */
void mm_check(void);           /* debug checking */
void mm_insert(char *, char *);/* insert the new block into a list */

/*
 * mm_init - Initialize the malloc package.
 */
int mm_init(void)
{
  /* total initial break */
  size_t seglist_region = ALIGN(SEGLIST_ROOT_SIZE * SEGLIST_NUM);
  size_t padding_region = PROL_SIZE + EPIL_SIZE;
  assert(padding_region == ALIGN(padding_region));
  mm_seglist_root = mem_sbrk(seglist_region + padding_region);
  mm_listp = mm_seglist_root + seglist_region;

  if (mm_seglist_root == (void *)-1) {
    printf("Failled to initialize mm ... \n");
    return -1;
  }

  /* initialize all SegList root with a null pointer.
   * the first slot in a root node is the class-size */
  for (size_t i = 0; i < SEGLIST_NUM; i++) {
    char *root_p = mm_seglist_root + i * SEGLIST_ROOT_SIZE;
    GETS(root_p) = MIN_BLOCK_SIZE << i;
    GETP(root_p + SIZE_T_SIZE) = 0;
  }

  /* padding consists of two allocated blocks. Both marked with a 0 size-bit.
   *   one is a prologue block with unaligned size (reserved for epilogue).
   *   the other one is epilogue block with a size equal to header. */
  GETS(mm_listp) = PACK(0, 0x2, 0x1);
  GETS(mm_listp + PROL_SIZE) = PACK(0, 0x2, 0x1);

  printf(">>> Finished initialization <<< \n");
  printf("mm_listp is %lx \n", (unsigned long) mm_listp);

  return 0;
}

/*
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
  printf("malloc(%zu) requested.\n", size);

  size_t blocksize = ALIGN(SIZE_T_SIZE + size);

  /* debug check: blocksize must larger than the small class */
  assert(blocksize >= GET_CLASS_SIZE(mm_seglist_root));

  /* find a size class k that fits blocksize.
   * that is, find the the largest class such that blocksize >= class_min. */
  size_t target_class;
  for (target_class = 0; target_class < SEGLIST_NUM; target_class++)
    if (blocksize < GET_CLASS_SIZE(mm_seglist_root + target_class * SEGLIST_ROOT_SIZE)) {
      target_class--;
      break;
    }

  printf("\t fit to class %zu (min %lu)\n", target_class, MIN_BLOCK_SIZE << target_class);

  /* search the segList for a free block. */
  char *targer_root = mm_seglist_root + SEGLIST_ROOT_SIZE * target_class;
  char *node_p = targer_root;
  while (target_class < SEGLIST_NUM) {

    /* follow the link */
    node_p = SUCC_BLKP(node_p);

    /* if reach the end of list, use a larger-size-class */
    if (node_p == 0) {
      target_class++;
      node_p = (mm_seglist_root + SEGLIST_ROOT_SIZE * target_class);
      continue;
    }

    /* if hit a free block that is big enough, allocated it. */
    if (GET_SIZE(HDRP(node_p)) >= blocksize) {
      /* TODO: split the block if more than 1/4 of the space is wasted.
       * this must happend if the block comes from a larger-size-class. */
      /* TODO: mark this block as allocated */
      /* TODO: remove it from the list */
      /* TODO: return the propieary address */
    }

  } /* end while */

  /* even the biggest-size-class have no space,
   * so we have to expand the heap */

  printf("\t no space in any class! ");

  /* ask memlib for a new chunk.
   * we add MIN_BLOCK_SIZE to ensure that brk_size > blocksize */
  size_t brk_size = MAX(CHUNK, blocksize + MIN_BLOCK_SIZE);
  printf("trying to break for %i \n", (int) brk_size);
  void *p = mem_sbrk(brk_size);
  if (p == (void *)-1) {
    return NULL;
  } else {

    printf("\t expand the heap to 0x%lx + %i = 0x%lx, \n", (unsigned long)p, (int) brk_size, (unsigned long)p + brk_size);

    /* read prev_alloc from the epilogue block before allocating */
    size_t prev_alloc = GET_ALLOC_PREV((char *)p - EPIL_SIZE);

    /* divide the new chunk into two pieces */
    char *p_retn_hdr = (char *)p - EPIL_SIZE;
    char *p_free_hdr = p_retn_hdr + blocksize;
    char *p_epil_hdr = p_retn_hdr + brk_size;
    GETS(p_retn_hdr) = PACK(blocksize, prev_alloc, 0x1);  /* return block */
    GETS(p_free_hdr) = PACK(brk_size - blocksize, 0x2, 0x0); /* new free block */
    GETS(p_epil_hdr) = PACK(0, 0x0, 0x1);  /* recover the epilogue */

    /* TODO: distribute the new free space to seg lists */
    mm_distribute(p_free_hdr);

    /* return the payload address */
    return p_retn_hdr + HDR_SIZE;

  } /* end if */
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;

    newptr = mm_malloc(size);
    if (newptr == NULL)
      return NULL;
    copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
    if (size < copySize)
      copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}

/*
 * mm_check - A debug function to check a bunch of conditions to make sure the
 *     program is working (written) correctly.
 */
 void mm_check(void)
 {
   printf("(mm_check) Checks nothing.\n");
 }

 /*
  * mm_distribute - Split and add the free block to seg lists.
  */
 void mm_distribute(char *free_hdr)
 {
   /* DEBUG: make sure the block is free */
   assert(GET_ALLOC(free_hdr) == 0x0);
   printf("\t distributing a free block at 0x%lx ", (unsigned long) free_hdr);

   size_t fb_size = GET_SIZE(free_hdr);

    printf("with size %i \n", (int) fb_size);

   /* DEBUG check: the block size must larger than the smallest class-size */
   assert(fb_size >= GET_CLASS_SIZE(mm_seglist_root));
   assert(fb_size >= MIN_BLOCK_SIZE);

   /* find the largest seglist that can populate this free block.
    * then insert it */
   char *last_list = mm_seglist_root + SEGLIST_ROOT_SIZE * (SEGLIST_NUM - 1);
   /* get a small enough class */
   while (fb_size < GET_CLASS_SIZE(last_list))
     last_list = SMALLER_CLASS(last_list);
   printf("\t target list is %lu with size %lu\n", (last_list - mm_seglist_root)/SEGLIST_ROOT_SIZE, GET_CLASS_SIZE(last_list));
   /* insert the block */
   mm_insert(free_hdr, last_list);

 }

 /*
  * mm_insert - Insert a new free block into a seg list.
  * Currently implementation just put the block at the head
  */
void mm_insert(char *free_bp, char *target_list)
{
  // DEBUG checks
  printf("\t inserting at target list %lu \n", ((char *)target_list - mm_seglist_root)/SEGLIST_ROOT_SIZE);

  /* debug checks */
  assert((unsigned long) target_list >= (unsigned long) mm_seglist_root);
  assert((unsigned long) target_list <= (unsigned long) mm_seglist_root + SEGLIST_NUM * SEGLIST_ROOT_SIZE);
  assert(GET_SIZE(HDRP(free_bp)) >= GET_CLASS_SIZE(target_list));

  /* currently we just put it at the head */
  char *first_node = SUCC_BLKP(target_list);  /* address to first node */
  SUCC_BLKP(target_list) = (char *)free_bp; /* root -> new  */
  PRED_BLKP(free_bp) = target_list;         /* new  -> root */
  SUCC_BLKP(free_bp) = first_node;          /* new -> old */
  if (first_node != 0)
    PRED_BLKP(first_node) = free_bp;        /* old -> new (optional) */

}
