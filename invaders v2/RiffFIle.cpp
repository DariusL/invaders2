#include "includes.h"
#include "RiffFile.h"
#include "Utils.h"

RiffFile::RiffFile(int format) :
fileFormat(format)
{
}

RiffFile::~RiffFile()
{
}

RiffFile::RiffFile(RiffFile&& other) :
fileFormat(other.fileFormat),
chunks(std::move(other.chunks))
{
}

void RiffFile::AddChunk(int fourCC, int size, const char* data)
{
	using namespace e;
	AssertBool(chunks.find(*reinterpret_cast<FourCCWrapper*>(&fourCC)) == chunks.end(), L"something");
	chunks.emplace(fourCC, RiffChunk(size, data));
}

RiffFile RiffFile::Create(const e::wstring& filePath)
{
	using namespace e;
	unsigned int dataSize, fileType;
	const auto riffData = Utils::ReadFileToVector(filePath);
#if _DEBUG
	unsigned int bufferPosition = 0;
	auto fileFourCC = Utils::ReadUint(riffData, bufferPosition);
	AssertBool((fileFourCC = RiffFourCC::RIFF) != 0, L"dafuq");
#else
	unsigned int bufferPosition = 4;
#endif

	dataSize = Utils::ReadUint(riffData, bufferPosition);
	fileType = Utils::ReadUint(riffData, bufferPosition);

	RiffFile riff(fileType);

	while (bufferPosition < dataSize + 8)
	{
		auto chunkFourCC = Utils::ReadUint(riffData, bufferPosition);
		//Assert(chunkFourCC != RiffFourCC::LIST);	// Lists currently not supported

		auto chunkSize = Utils::ReadUint(riffData, bufferPosition);

		riff.AddChunk(chunkFourCC, chunkSize, &riffData[bufferPosition]);
		bufferPosition += chunkSize + (chunkSize % 2);
	}

	return riff;
}


RiffChunk& RiffFile::GetChunk(int fourCC)
{
	using namespace e;
	auto chunk = chunks.find(*reinterpret_cast<FourCCWrapper*>(&fourCC));
	AssertBool(chunk != chunks.end(), L"something");

	return chunk->second;
}