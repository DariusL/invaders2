#pragma once

#include "FourCCWrapper.h"
#include "RiffChunk.h"

enum RiffFourCC
{
	RIFF = 'FFIR',
	DATA = 'atad',
	FMT = ' tmf',
	WAVE = 'EVAW',
	LIST = 'TSIL'
};

class RiffFile
{
private:
	FourCCWrapper fileFormat;
	e::unordered_map<FourCCWrapper, RiffChunk> chunks;

	RiffFile(int fileFormat);
	RiffFile(const RiffFile& other);

	void AddChunk(int fourCC, int size, const char* data);

public:
	RiffFile(RiffFile&& other);
	~RiffFile();

	static RiffFile Create(const e::wstring& filePath);

	inline const FourCCWrapper& GetFormat() const { return fileFormat; }
	RiffChunk& GetChunk(int fourCC);
};