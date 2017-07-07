
//////////////////////////////////////////////////////////////////////////
/// Includes
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SoundSystem.h"
#include "AudioObject.h"


//////////////////////////////////////////////////////////////////////////
/// CSoundSystem
//////////////////////////////////////////////////////////////////////////

CSoundSystem::CSoundSystem() :
    myAudioInterface( nullptr ),
    myMasteringVoice( nullptr ),
    myInitialised( false )
{
}

//////////////////////////////////////////////////////////////////////////

CSoundSystem::~CSoundSystem()
{
	if( myInitialised )
	{
		myMasteringVoice->DestroyVoice();
		myAudioInterface->Release();
		myInitialised = false;
	}
}

//////////////////////////////////////////////////////////////////////////

bool CSoundSystem::Initialise()
{
    if( myInitialised )
    {
        return true;
    }

    // initialize the audio interface
    HRESULT result = XAudio2Create( &myAudioInterface, 0, XAUDIO2_DEFAULT_PROCESSOR );
    if( result != S_OK )
    {
        return false;
    }
 
    // create the mastering voice
    result = myAudioInterface->CreateMasteringVoice( &myMasteringVoice );
    if( result != S_OK )
    {
        return false;
    }

    myInitialised = true;
    return true;
}

//////////////////////////////////////////////////////////////////////////

IXAudio2* CSoundSystem::GetInterface() const
{
    return myAudioInterface;
}

//////////////////////////////////////////////////////////////////////////