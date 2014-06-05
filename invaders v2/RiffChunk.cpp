#include "includes.h"
#include "RiffChunk.h"


RiffChunk::RiffChunk(int size, const char* data) :
size(size), data(new char[size])
{
	memcpy(this->data.get(), data, size);
}

RiffChunk::RiffChunk(RiffChunk&& other) :
size(other.size),
data(std::move(other.data))
{
}

RiffChunk::~RiffChunk()
{
}
