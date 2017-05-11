#pragma once

//////////////////////////////////////////////////////////////////////////
/// Defines
//////////////////////////////////////////////////////////////////////////

#define WAV_HEADER_BLOCK_LENGTH 4


//////////////////////////////////////////////////////////////////////////
/// Structures
//////////////////////////////////////////////////////////////////////////

struct SWavHeader 
{
    SWavHeader();

    char  m_riff[WAV_HEADER_BLOCK_LENGTH];              // "RIFF"                                  
    long  m_fileLength;                                 // file length in bytes                    
    char  m_wave[WAV_HEADER_BLOCK_LENGTH];              // "WAVE"                                  
    char  m_format[WAV_HEADER_BLOCK_LENGTH];            // "fmt "                                  
    long  m_blockSize;                                  // in bytes (generally 16)                 
    short m_formatTag;                                  // 1=PCM, 257=Mu-Law, 258=A-Law, 259=ADPCM 
    short m_channelCount;                               // 1=mono, 2=stereo                        
    long  m_samplesPerSecond;                           // Sampling rate in samples per second     
    long  m_bytesPerSecond;                             // bytes per second                        
    short m_bytesPerSample;                             // 2=16-bit mono, 4=16-bit stereo          
    short m_bitsPerSample;                              // Number of bits per sample               
    char  m_rawData[WAV_HEADER_BLOCK_LENGTH];           // "data"                                  
    long  m_dataLength;                                 // data length in bytes (filelength - 44)  
};


//////////////////////////////////////////////////////////////////////////
/// CWavFile
//////////////////////////////////////////////////////////////////////////

// a class for reading in .wav files. 
// NOTE: at the moment this only supports mono .wav files @ 2 bytes per sample
class CWavFile
{
public :

    //////////////////////////////////////////////////////////////////////////

    CWavFile();
    ~CWavFile();

    //////////////////////////////////////////////////////////////////////////

    bool Open( const char* aFileName );
    bool Save( const char* aFileName );
    void SetWavData( const std::vector<short>& someSamples );

    //////////////////////////////////////////////////////////////////////////

    long    GetSampleCount() const;
    short   GetSample( const long& anIndex ) const;
    short&  operator[]( const long& anIndex );


private :

    //////////////////////////////////////////////////////////////////////////

    SWavHeader  m_wavHeader;
    short*      m_wavData;
    long        m_sampleCount;

    bool        m_isValid;
};

//////////////////////////////////////////////////////////////////////////