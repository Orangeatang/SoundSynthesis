
//////////////////////////////////////////////////////////////////////////
/// Includes
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Quantization.h"
#include "WavFile.h"


//////////////////////////////////////////////////////////////////////////
/// Quantization
//////////////////////////////////////////////////////////////////////////

Quantization::Quantization( long aQuantizationFactor ) :
    m_quantizationFactor( aQuantizationFactor )
{
}

//////////////////////////////////////////////////////////////////////////

Quantization::~Quantization()
{
}

//////////////////////////////////////////////////////////////////////////

bool Quantization::ProcessAudio( const char* anInputFile, const char* anOutputFile )
{
    CWavFile wavFile;
    if( !wavFile.Open(anInputFile) )
    {
        return false;
    }

    // quantize the audio
    float tempData;
    short data;
    int   bitCount = 16 - m_quantizationFactor;
    float quantum  = (float)pow( 2.0f, bitCount );
    for( int i = 0, e = wavFile.GetSampleCount(); i < e; ++i )
    {
        data        = wavFile.GetSample( i );
        tempData    = (float)data / quantum;

        // round to nearest quantum
        tempData    += 0.5f;
        
        data        = (short)tempData;

        tempData    = (float)data * quantum;
        wavFile[i]  = (short)tempData;
    }

    // save the output
    wavFile.Save( anOutputFile );

    return true;
}

//////////////////////////////////////////////////////////////////////////