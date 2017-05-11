#pragma once

//////////////////////////////////////////////////////////////////////////
/// Forward Declarations
//////////////////////////////////////////////////////////////////////////

class Quantization;


//////////////////////////////////////////////////////////////////////////
/// Using
//////////////////////////////////////////////////////////////////////////

using namespace System;


//////////////////////////////////////////////////////////////////////////
/// SoundSynthesisInterface
//////////////////////////////////////////////////////////////////////////

// SoundSynthesisInterface follows the singleton design pattern and is designed to provide
// an interface between the C++ audio effects and C# user interface
public ref class SoundSynthesisInterface
{
public :

    //////////////////////////////////////////////////////////////////////////

    ~SoundSynthesisInterface();
    !SoundSynthesisInterface();

    //////////////////////////////////////////////////////////////////////////

    void QuantizeAudioFile( String^ anInputFileName, String^ anOutputFileName, int aSampleRate );

    void PitchShiftAudioFile( String^ anInputFileName, String^ anOutputFileName, double aPitchShiftFactor );

    //////////////////////////////////////////////////////////////////////////

    // singleton accessor
    static property SoundSynthesisInterface^ Instance
    {
        SoundSynthesisInterface^ get()
        {
            if( ourInstance == nullptr )
            {
                ourInstance = gcnew SoundSynthesisInterface();
            }

            return ourInstance;
        }
    }


private :

    //////////////////////////////////////////////////////////////////////////

    SoundSynthesisInterface();

    //////////////////////////////////////////////////////////////////////////

    static SoundSynthesisInterface^ ourInstance = nullptr;
};


//////////////////////////////////////////////////////////////////////////