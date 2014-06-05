#pragma once
#include "includes.h"
class RiffChunk
{
private:
	int size;
	e::unique_ptr<char[]> data;

	RiffChunk(const RiffChunk& other);

public:
	RiffChunk(int size, const char* data);
	RiffChunk(RiffChunk&& other);
	~RiffChunk();

	inline int GetSize() const { return size; }
	inline const char* GetData() const { return data.get(); }
	inline e::unique_ptr<char[]>& GetDataBuffer() { return data; }
};