#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <stddef.h>

typedef struct c_buffer c_buffer_t;


c_buffer_t* CBCreate(size_t capacity);

void CBDestroy(c_buffer_t* cb);

size_t CBRead(void* buffer_dst, c_buffer_t* buffer_src, size_t num_bytes);

size_t CBWrite(c_buffer_t* buffer_dst, void* buffer_src, size_t num_bytes);

size_t CBGetFreeSpace(const c_buffer_t* cb);

size_t CBGetSize(const c_buffer_t* cb); /* How much is taken/ used */

int CBIsEmpty(const c_buffer_t* cb);

#endif /* end of header guard CIRCULAR_BUFFER_H */
