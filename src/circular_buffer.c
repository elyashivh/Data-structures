#include <assert.h>		/*use assert*/
#include <stdlib.h>		/*use malloc & free*/

/*author: Elyashiv Horden
date: 7/12/24
CR: Roy Goldhar*/

	
#include "circular_buffer.h"

#define MIN(a, b) ((a < b) ? (a) : (b))

static size_t ReadData(void* buffer_dst, c_buffer_t* buffer_src, size_t bytes_to_copy);
static size_t WriteData(c_buffer_t* buffer_dst, void* buffer_src, size_t num_bytes);


struct c_buffer
{
	size_t read_index;
	size_t write_index;
	size_t capacity;
	char buffer[1]; 
};


c_buffer_t* CBCreate(size_t capacity)
{
	c_buffer_t* c_buffer = (c_buffer_t*)malloc(sizeof(c_buffer_t) + (capacity));
	{
		if (NULL == c_buffer)
		{
			return NULL;
		}
	}
	c_buffer->read_index = 0;
	c_buffer->write_index = 0;
	c_buffer->capacity = capacity + 1;
	
	return c_buffer;
}


void CBDestroy(c_buffer_t* cb)
{
	assert(NULL != cb);
	free(cb);
}


size_t CBRead(void* buffer_dst, c_buffer_t* buffer_src, size_t num_bytes)
{
	size_t bytes_to_copy = 0;

	assert(NULL != buffer_dst);
	assert(NULL != buffer_src);
	
	bytes_to_copy = MIN(num_bytes, CBGetSize(buffer_src));
	
	return ReadData(buffer_dst, buffer_src, bytes_to_copy);
}


size_t CBWrite(c_buffer_t* buffer_dst, void* buffer_src, size_t num_bytes)
{
	size_t bytes_to_write = 0;
	
	assert(NULL != buffer_dst);
	assert(NULL != buffer_src);
	
	bytes_to_write = MIN(num_bytes, CBGetFreeSpace(buffer_dst));
	
	return WriteData(buffer_dst, buffer_src, bytes_to_write);	
}


size_t CBGetFreeSpace(const c_buffer_t* cb)
{
	assert (NULL != cb);
	return (cb->capacity - CBGetSize(cb) - 1); 
}


size_t CBGetSize(const c_buffer_t* cb) 
{
	assert (NULL != cb);
	return ((cb->write_index - cb->read_index) % (cb->capacity));
}


int CBIsEmpty(const c_buffer_t* cb)
{
	assert (NULL != cb);
	return cb->read_index == cb->write_index;
}


static size_t ReadData(void* buffer_dst, c_buffer_t* buffer_src, size_t bytes_to_copy)
{
	size_t copied_bytes = 0;
	while (bytes_to_copy > 0)
	{
		*(char*)buffer_dst = *(buffer_src->buffer + buffer_src->read_index);
		buffer_dst = (char*)buffer_dst + 1; 
		buffer_src->read_index = (buffer_src->read_index + 1) % buffer_src->capacity;
		--bytes_to_copy;
		++copied_bytes;
	}
	return copied_bytes;
}


static size_t WriteData(c_buffer_t* buffer_dst, void* buffer_src, size_t bytes_to_write)
{
	size_t writed_bytes = 0;
	char* temp = NULL;
	temp = (char*)buffer_src;
	
	while (bytes_to_write > 0)
	{
		*(buffer_dst->buffer + buffer_dst->write_index) = *temp;
		++temp;
		buffer_dst->write_index = (buffer_dst->write_index + 1) % buffer_dst->capacity;
		--bytes_to_write;
		++writed_bytes;
	}
	return writed_bytes;
}





