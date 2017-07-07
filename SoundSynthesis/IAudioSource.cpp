
//////////////////////////////////////////////////////////////////////////
/// Inculdes
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IAudioSource.h"
#include "SoundSystem.h"


//////////////////////////////////////////////////////////////////////////
/// CAudioSource
//////////////////////////////////////////////////////////////////////////

IAudioSource::IAudioSource( CSoundSystem* aSoundSystem, UINT32 someFlags ) : IAudioVoice( aSoundSystem, someFlags ),
    myVoice( nullptr ),
    myCanPlay( false ),
    myIsPlaying( false )
{
}

//////////////////////////////////////////////////////////////////////////

IAudioSource::~IAudioSource()
{
    delete myAudioBuffer;
}

//////////////////////////////////////////////////////////////////////////

bool IAudioSource::Play()
{
    if( !myCanPlay )
    {
        return false;
    }

    // submit the source buffer using the voice
    HRESULT result = myVoice->SubmitSourceBuffer( myAudioBuffer );
    if( FAILED(result) )
    {
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////

IXAudio2SourceVoice* IAudioSource::GetVoice() const
{
    return myVoice;
}

//////////////////////////////////////////////////////////////////////////

XAUDIO2_BUFFER* IAudioSource::GetBuffer() const
{
    return myAudioBuffer;
}

//////////////////////////////////////////////////////////////////////////

void IAudioSource::InitializeBuffer( UINT32 aByteCount, UINT32 someFlags )
{
    myAudioBuffer = new XAUDIO2_BUFFER();
    myAudioBuffer->AudioBytes   = aByteCount;
    myAudioBuffer->Flags        = someFlags;
    myAudioBuffer->pAudioData   = new BYTE[myAudioBuffer->AudioBytes];
}

//////////////////////////////////////////////////////////////////////////

bool IAudioSource::CreateVoice()
{
    IXAudio2* xaudio2 = mySoundSystem->GetInterface();
    assert( xaudio2 != nullptr );

    // create the voice for the audio source
    HRESULT result = xaudio2->CreateSourceVoice( &myVoice, &myWaveFormat, myVoiceFlags );
    assert( result == S_OK );

    // make sure the voice was successfully created, and indicate that the source is ready to play
    if( result == S_OK )
    {
        myCanPlay = true;
        return true;
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////