
//////////////////////////////////////////////////////////////////////////
/// Includes
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WavFile.h"
#include "SoundSystem.h"


//////////////////////////////////////////////////////////////////////////
/// Defines
//////////////////////////////////////////////////////////////////////////

#define RIFF    'RIFF'
#define DATA    'DATA'
#define FMT     'fmt'
#define WAVE    'WAVE'
#define DPDS    'dpds'


//////////////////////////////////////////////////////////////////////////
/// CWavFile
//////////////////////////////////////////////////////////////////////////

CWavFile::CWavFile( CSoundSystem* aSoundSystem ) : CAudioSource( aSoundSystem )
{
}

//////////////////////////////////////////////////////////////////////////

CWavFile::~CWavFile()
{
}

//////////////////////////////////////////////////////////////////////////

bool CWavFile::Load( const char* aFileName )
{
    // create a file handle
    const TCHAR* fileName = _TEXT(aFileName);

    HANDLE fileHandle = CreateFile( fileName, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr );
    if( fileHandle == INVALID_HANDLE_VALUE )
    {
        return false;
    }

    DWORD result = SetFilePointer( fileHandle, 0, nullptr, FILE_BEGIN );
    if( result == INVALID_SET_FILE_POINTER )
    {
        return false;
    }

    // locate the 'RIFF' chunk and load it in to the WAVEFORMATEXTENSIBLE structure
    DWORD chunkSize     = 0;
    DWORD chunkPosition = 0;
    if( !FindChunk(fileHandle, RIFF, chunkSize, chunkPosition) )
    {
        return false;
    }

    // read in the type of file from the 'RIFF' chunk
    DWORD fileType;
    if( !ReadChunkData(fileHandle, &fileType, sizeof(DWORD), chunkPosition) )
    {
        return false;
    }

    // make sure we're trying to read in a .wav file
    if( fileType != WAVE )
    {
        return false;
    }

    // locate and read the 'fmt' chunk, which contains all of the wav format data
    if( !FindChunk(fileHandle, FMT, chunkSize, chunkPosition) )
    {
        return false;
    }

    if( !ReadChunkData(fileHandle, &myWaveFormatEx, chunkSize, chunkPosition) )
    {
        return false;
    }

    // locate and read the 'data' chunk
    if( !FindChunk(fileHandle, DATA, chunkSize, chunkPosition) )
    {
        return false;
    }

    // create the audio buffer and read the chunk data in to it
    InitializeBuffer( chunkSize, XAUDIO2_END_OF_STREAM );
    if( !ReadChunkData( fileHandle, (void*)myAudioBuffer->pAudioData, chunkSize, chunkPosition) )
    {
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////

bool CWavFile::CreateVoice()
{
    IXAudio2* xaudio2 = mySoundSystem->GetInterface();
    assert( xaudio2 != nullptr );

    HRESULT result = xaudio2->CreateSourceVoice( &myVoice, &myWaveFormatEx.Format, myVoiceFlags );
    assert( result == S_OK );

    return (result == S_OK);
}

//////////////////////////////////////////////////////////////////////////

bool CWavFile::FindChunk( HANDLE aFileHandle, DWORD aChunk, DWORD& aChunkSize, DWORD& aChunkPosition ) const
{
    // set the file handle to point to the beggining of the file
    if( SetFilePointer(aFileHandle, 0, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER )
    {
        return false;
    }

    HRESULT result          = S_OK;
    DWORD   chunkType       = 0;
    DWORD   chunkSize       = 0;
    DWORD   currentOffset   = 0;
    DWORD   totalData       = 0;
    DWORD   fileType        = 0;
    
    // look through the file for the requested chunk
    while( result == S_OK )
    {
        // read in the chunk type
        DWORD dataRead;
        if( ReadFile(aFileHandle, &chunkType, sizeof(DWORD), &dataRead, nullptr) == FALSE )
        {
            result = HRESULT_FROM_WIN32( GetLastError() );
        }

        // read in the chunk size
        if( ReadFile(aFileHandle, &chunkSize, sizeof(DWORD), &dataRead, nullptr) == FALSE )
        {
            result = HRESULT_FROM_WIN32( GetLastError() );
        }

        // move the file pointer to the end of the chunk data
        switch( chunkType )
        {
            // the RIFF chunk hold the total data size for the file
        case RIFF:
            totalData = chunkSize;
            chunkSize = 4;
            if( ReadFile(aFileHandle, &fileType, sizeof(DWORD), &dataRead, nullptr) == FALSE )
            {
                result = HRESULT_FROM_WIN32( GetLastError() );
            }
            break;

            // otherwise just move the file pointer to the end of the chunk
        default:
            if( SetFilePointer(aFileHandle, chunkSize, NULL, FILE_CURRENT) == FALSE )
            {
                return false;
            }
            break;
        }
        currentOffset = sizeof(DWORD) * 2;

        // check to see if we've found the chunk we're looking for
        if( chunkType == aChunk )
        {
            aChunkSize      = chunkSize;
            aChunkPosition  = currentOffset;

            return true;
        }

        // move the current offset to the end of the chunk data
        currentOffset += chunkSize;
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////

bool CWavFile::ReadChunkData( HANDLE aFileHandle, void* aBuffer, DWORD aBufferSize, DWORD aBufferOffset ) const
{
    HRESULT result = S_OK;
    if( SetFilePointer(aFileHandle, aBufferOffset, NULL, FILE_BEGIN) == FALSE )
    {
        result = HRESULT_FROM_WIN32( GetLastError() );
        return false;
    }

    DWORD dataRead = 0;
    if( ReadFile(aFileHandle, aBuffer, aBufferSize, &dataRead, NULL) == FALSE )
    {
        result = HRESULT_FROM_WIN32( GetLastError() );
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////