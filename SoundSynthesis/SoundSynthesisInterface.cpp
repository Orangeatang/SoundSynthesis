
//////////////////////////////////////////////////////////////////////////
/// Includes
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SoundSynthesisInterface.h"
#include "Engine.h"

#include "Quantization.h"
#include "PitchShift.h"
#include "Helpers.h"


//////////////////////////////////////////////////////////////////////////
/// SoundSynthesisInterface
//////////////////////////////////////////////////////////////////////////

SoundSynthesisInterface::SoundSynthesisInterface() :
    myEngine( nullptr )
{
}

//////////////////////////////////////////////////////////////////////////

SoundSynthesisInterface::~SoundSynthesisInterface()
{
}

//////////////////////////////////////////////////////////////////////////

SoundSynthesisInterface::!SoundSynthesisInterface()
{
}

//////////////////////////////////////////////////////////////////////////

bool SoundSynthesisInterface::Initialise( IntPtr aWindowHandle, int aWindowWidth, int aWindowHeight )
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

void SoundSynthesisInterface::Uninitialise()
{
	delete myEngine;
	ourInstance = nullptr;
}

//////////////////////////////////////////////////////////////////////////

void SoundSynthesisInterface::Update()
{
    if( !myEngine->IsInitialized() )
    {
        return;
    }

    myEngine->Update();
}

//////////////////////////////////////////////////////////////////////////

void SoundSynthesisInterface::QuantizeAudioFile( String^ anInputFileName, String^ anOutputFileName, int aSampleRate )
{
    std::shared_ptr<Quantization> quantizer( new Quantization(aSampleRate) );

    quantizer->ProcessAudio( StringToChar(anInputFileName).myString, StringToChar(anOutputFileName).myString );
}

//////////////////////////////////////////////////////////////////////////

void SoundSynthesisInterface::PitchShiftAudioFile( String^ anInputFileName, String^ anOutputFileName, double aPitchShiftFactor )
{
    std::shared_ptr<CPitchShift> pitchShifter( new CPitchShift(aPitchShiftFactor) );

    pitchShifter->ProcessAudio( StringToChar(anInputFileName).myString, StringToChar(anOutputFileName).myString );
}

//////////////////////////////////////////////////////////////////////////