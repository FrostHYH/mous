#ifndef MACDECODER_H
#define MACDECODER_H

#include <plugin/IDecoder.h>
#include <MACLib/Source/Shared/All.h>
#include <MACLib/Source/Shared/NoWindows.h>
#include <MACLib/Source/Shared/CharacterHelper.h>
#include <MACLib/Source/MACLib/APEDecompress.h>
using namespace std;
using namespace mous;

class MacDecoder: public IDecoder
{
public:
    MacDecoder() = default;
    virtual ~MacDecoder();

    virtual vector<string> FileSuffix() const;

    virtual ErrorCode Open(const string& url);
    virtual void Close();

    virtual bool IsFormatVaild() const;

    virtual ErrorCode DecodeUnit(char* data, uint32_t& used, uint32_t& unitCount);
    virtual ErrorCode SetUnitIndex(uint64_t index);
    virtual uint32_t MaxBytesPerUnit() const;
    virtual uint64_t UnitIndex() const;
    virtual uint64_t UnitCount() const;

    virtual enum AudioMode AudioMode() const;
    virtual int32_t Channels() const;
    virtual int32_t BitsPerSample() const;
    virtual int32_t SampleRate() const;
    virtual int32_t BitRate() const;
    virtual uint64_t Duration() const;

private:
    IAPEDecompress* m_pDecompress = nullptr;

    uint64_t m_BlockIndex;
    uint64_t m_BlockCount;

    uint32_t m_BlockAlign;
    uint32_t m_BlocksPerFrame;
    uint32_t m_BlocksPerRead;

    int32_t m_Channels;
    int32_t m_BitsPerSample;
    int32_t m_SampleRate;
    int32_t m_BitRate;
    uint64_t m_Duration;
};

#endif
