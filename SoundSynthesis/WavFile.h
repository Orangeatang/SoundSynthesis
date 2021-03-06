#pragma once

//////////////////////////////////////////////////////////////////////////
/// Includes
//////////////////////////////////////////////////////////////////////////

#include "IAudioSource.h"


//////////////////////////////////////////////////////////////////////////
/// CWavFile
//////////////////////////////////////////////////////////////////////////

class CWavFile : public IAudioSource
{
public :

    //////////////////////////////////////////////////////////////////////////

    CWavFile( CSoundSystem* aSoundSystem );
    ~CWavFile();

    //////////////////////////////////////////////////////////////////////////

    bool Load( const char* aFileName );


protected :

    //////////////////////////////////////////////////////////////////////////

    bool CreateVoice() override;


private :

    //////////////////////////////////////////////////////////////////////////

    bool FindChunk( HANDLE aFileHandle, DWORD aChunk, DWORD& aChunkSize, DWORD& aChunkPosition ) const;
    bool ReadChunkData( HANDLE aFileHandle, void* aBuffer, DWORD aBufferSize, DWORD aBufferOffset ) const;

    //////////////////////////////////////////////////////////////////////////

    WAVEFORMATEXTENSIBLE myWaveFormatEx;
};

//////////////////////////////////////////////////////////////////////////
