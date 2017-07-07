#pragma once

/////////////////////////////////////////////////////////////////////
/// Forward Declarations
//////////////////////////////////////////////////////////////////////////

class CSoundSystem;


//////////////////////////////////////////////////////////////////////////
/// CAudioSource
//////////////////////////////////////////////////////////////////////////

class IAudioSource
{
public:

    //////////////////////////////////////////////////////////////////////////

    IAudioSource( CSoundSystem* aSoundSystem, UINT32 someFlags = 0 );
    virtual ~IAudioSource();

    //////////////////////////////////////////////////////////////////////////

    bool                    Play();

    //////////////////////////////////////////////////////////////////////////

    IXAudio2SourceVoice*    GetVoice() const;
    XAUDIO2_BUFFER*         GetBuffer() const;


protected :

    //////////////////////////////////////////////////////////////////////////

    void                    InitializeBuffer( UINT32 aByteCount, UINT32 someFlags );
    virtual bool            CreateVoice();

    //////////////////////////////////////////////////////////////////////////

    IXAudio2SourceVoice*    myVoice;
    XAUDIO2_BUFFER*         myAudioBuffer;
    WAVEFORMATEX            myWaveFormat;
    UINT32                  myVoiceFlags;

    CSoundSystem*           mySoundSystem;

    bool                    myCanPlay;
    bool                    myIsPlaying;
};

//////////////////////////////////////////////////////////////////////////