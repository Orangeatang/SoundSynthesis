
//////////////////////////////////////////////////////////////////////////
/// Includes
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WavFile.h"


//////////////////////////////////////////////////////////////////////////
/// SWavHeader
//////////////////////////////////////////////////////////////////////////

SWavHeader::SWavHeader() :
    m_fileLength( 0 ),
    m_blockSize( 0 ),
    m_formatTag( 0 ),
    m_channelCount( 0 ),
    m_samplesPerSecond( 0 ),
    m_bytesPerSecond( 0 ),
    m_bytesPerSample( 0 ),
    m_bitsPerSample( 0 ),
    m_dataLength( 0 )
{
    memset( &m_riff, 0, sizeof(char) * WAV_HEADER_BLOCK_LENGTH );
    memset( &m_wave, 0, sizeof(char) * WAV_HEADER_BLOCK_LENGTH );
    memset( &m_format, 0, sizeof(char) * WAV_HEADER_BLOCK_LENGTH );
    memset( &m_dataLength, 0, sizeof(char) * WAV_HEADER_BLOCK_LENGTH );
}


//////////////////////////////////////////////////////////////////////////
/// CWavFile
//////////////////////////////////////////////////////////////////////////

CWavFile::CWavFile() :
    m_wavData( nullptr ),
    m_isValid( false )
{
}

//////////////////////////////////////////////////////////////////////////

CWavFile::~CWavFile()
{
    delete m_wavData;
    m_isValid = false;
}

//////////////////////////////////////////////////////////////////////////

bool CWavFile::Open( const char* aFileName )
{
    FILE* inputFile;

    errno_t errorCode = fopen_s( &inputFile, aFileName, "rb" );
    if( errorCode != 0 )
    {
        return false;
    }

    // read in the .wav header
    size_t dataRead = fread( &m_wavHeader, 1, sizeof(SWavHeader), inputFile );
    if( m_wavHeader.m_dataLength == 0 || dataRead != sizeof(SWavHeader) )
    {
        return false;
    }

    // read in the .wav data
    m_sampleCount       = m_wavHeader.m_dataLength / m_wavHeader.m_bytesPerSample;
    m_wavData           = new short[m_sampleCount];
    dataRead            = fread( m_wavData, sizeof(short), m_sampleCount, inputFile );
    if( dataRead != m_sampleCount )
    {
        return false;
    }

    // close the input file
    fclose( inputFile );

    m_isValid = true;
    return true;
}

//////////////////////////////////////////////////////////////////////////

bool CWavFile::Save( const char* aFileName )
{
    FILE* outputFile;

    errno_t errorCode = fopen_s( &outputFile, aFileName, "wb" );
    if( errorCode != 0 )  
    {
        return false;
    }

    // output the header
    fwrite( &m_wavHeader, 1, sizeof(SWavHeader), outputFile );

    // output the wav data
    fwrite( m_wavData, sizeof(short), GetSampleCount(), outputFile );

    // close the output file
    fclose( outputFile );

    return true;
}

//////////////////////////////////////////////////////////////////////////

void CWavFile::SetWavData( const std::vector<short>& someSamples )
{
    if( m_wavData != nullptr )
    {
        delete m_wavData;
    }

    // set the number of samples in the .wav header
    m_wavHeader.m_dataLength = (long)someSamples.size() * m_wavHeader.m_bytesPerSample;
    m_wavHeader.m_fileLength = m_wavHeader.m_dataLength + 36; // 36 is header (44) minus RIFF & file length

    // initialize the wav data and copy the supplied samples
    m_wavData = new short[someSamples.size()];
    std::copy( someSamples.begin(), someSamples.end(), m_wavData );
}

//////////////////////////////////////////////////////////////////////////

long CWavFile::GetSampleCount() const
{
    if( m_isValid )
    {
        return m_sampleCount;
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////

short CWavFile::GetSample( const long& anIndex ) const
{
    if( anIndex < m_sampleCount )
    {
        return m_wavData[anIndex];
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////

short& CWavFile::operator []( const long& anIndex )
{
    assert( anIndex < m_sampleCount );
    return m_wavData[anIndex];
}

//////////////////////////////////////////////////////////////////////////