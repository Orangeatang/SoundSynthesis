#pragma once

//////////////////////////////////////////////////////////////////////////
/// Forward Declarations
//////////////////////////////////////////////////////////////////////////

class Quantization;
class CEngine;


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

    bool InitialiseEngine( IntPtr aWindowHandle, int aWindowWidth, int aWindowHeight );

    void Update();

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

    CEngine* myEngine;

    //////////////////////////////////////////////////////////////////////////

    static SoundSynthesisInterface^ ourInstance = nullptr;
};


//////////////////////////////////////////////////////////////////////////