
//////////////////////////////////////////////////////////////////////////
/// Includes
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SoundInterface.h"
#include "Helpers.h"

#include <SoundSynthesis/Engine.h>
#include <SoundSynthesis/Quantization.h>
#include <SoundSynthesis/PitchShift.h>


//////////////////////////////////////////////////////////////////////////
/// SoundSynthesisInterface
//////////////////////////////////////////////////////////////////////////

SoundInterface::SoundInterface() :
    myEngine( nullptr )
{
}

//////////////////////////////////////////////////////////////////////////

SoundInterface::~SoundInterface()
{
}

//////////////////////////////////////////////////////////////////////////

SoundInterface::!SoundInterface()
{
}

//////////////////////////////////////////////////////////////////////////

bool SoundInterface::Initialise( IntPtr aWindowHandle, int aWindowWidth, int aWindowHeight )
{
    if( myEngine != nullptr )
    {
        return myEngine->IsInitialized();
    }

    myEngine = new CEngine();
    if( !myEngine->Initialise((HWND)aWindowHandle.ToPointer(), aWindowWidth, aWindowHeight) )
    {
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////

void SoundInterface::Uninitialise()
{
	delete myEngine;
	ourInstance = nullptr;
}

//////////////////////////////////////////////////////////////////////////

void SoundInterface::Update()
{
    if( !myEngine->IsInitialized() )
    {
        return;
    }

    myEngine->Update();
}

//////////////////////////////////////////////////////////////////////////

void SoundInterface::QuantizeAudioFile( String^ anInputFileName, String^ anOutputFileName, int aSampleRate )
{
    std::shared_ptr<Quantization> quantizer( new Quantization(aSampleRate) );

    quantizer->ProcessAudio( StringToChar(anInputFileName).myString, StringToChar(anOutputFileName).myString );
}

//////////////////////////////////////////////////////////////////////////

void SoundInterface::PitchShiftAudioFile( String^ anInputFileName, String^ anOutputFileName, double aPitchShiftFactor )
{
    std::shared_ptr<CPitchShift> pitchShifter( new CPitchShift(aPitchShiftFactor) );

    pitchShifter->ProcessAudio( StringToChar(anInputFileName).myString, StringToChar(anOutputFileName).myString );
}

//////////////////////////////////////////////////////////////////////////