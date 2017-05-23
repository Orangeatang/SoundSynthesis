
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
    m_engine( nullptr )
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

bool SoundSynthesisInterface::InitializeEngine( IntPtr aWindowHandle, int aWindowWidth, int aWindowHeight )
{
    if( m_engine != nullptr )
    {
        return m_engine->IsInitialized();
    }

    m_engine = new CEngine();
    if( !m_engine->Initialize((HWND)aWindowHandle.ToPointer(), aWindowWidth, aWindowHeight) )
    {
        return false;
    }

    return true;
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