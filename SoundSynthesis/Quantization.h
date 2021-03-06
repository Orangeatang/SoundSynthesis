#pragma once

//////////////////////////////////////////////////////////////////////////
/// Inludes
//////////////////////////////////////////////////////////////////////////

#include "IEffect.h"


//////////////////////////////////////////////////////////////////////////
/// Quantization
//////////////////////////////////////////////////////////////////////////

// a utility class used to quantize audio input using a supplied quantization step
class Quantization : public IEffect
{
public:

    //////////////////////////////////////////////////////////////////////////

    Quantization( long aQuantizationFactor );
    ~Quantization();

    //////////////////////////////////////////////////////////////////////////

    bool ProcessAudio( const char* anInputFile, const char* anOutputFile ) override;


private:

    //////////////////////////////////////////////////////////////////////////

    long m_quantizationFactor;
};


//////////////////////////////////////////////////////////////////////////