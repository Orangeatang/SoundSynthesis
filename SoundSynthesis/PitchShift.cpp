
//////////////////////////////////////////////////////////////////////////
/// Includes
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PitchShift.h"


//////////////////////////////////////////////////////////////////////////
/// Defines
//////////////////////////////////////////////////////////////////////////

#define WINDOW_WIDTH	64
#define DELAY_SIZE		140
#define PI              3.14159263


//////////////////////////////////////////////////////////////////////////
/// CPitchShift
//////////////////////////////////////////////////////////////////////////

CPitchShift::CPitchShift( double aPitchShiftFactor ) :
    m_pitchShiftFactor( aPitchShiftFactor )
{
	m_delayBuffer = new int[3 * WINDOW_WIDTH];
	memset(m_delayBuffer, 0, sizeof(int) * (3 * WINDOW_WIDTH));
}

//////////////////////////////////////////////////////////////////////////

CPitchShift::~CPitchShift()
{
}

//////////////////////////////////////////////////////////////////////////

bool CPitchShift::ProcessAudio( const char* anInputFile, const char* anOutputFile )
{
    /*
	CWavFile wavFile;
	if (!wavFile.Open(anInputFile))
	{
		return false;
	}

    std::vector<short> outputSamples;

    long sampleCount        = wavFile.GetSampleCount();

	double finalfactor      = m_pitchShiftFactor;
	double currentFactor    = m_pitchShiftFactor;
    double deltaFactor      = (finalfactor - m_pitchShiftFactor) / sampleCount; 
    double oneOverFactor    = 0;
    double tempData         = 0;
    double currentTime      = 0;
    
    long intTime            = 0;
    long leftLimit          = 0;
    long rightLimit         = 0;
    long lastTime           = 0;

    short  inputData        = 0;
    short  outputData       = 0;

    int    currentSample    = 0;

    bool pitchShiftComplete = false;
    while( !pitchShiftComplete )
    {
        tempData = 0.0;

        // calculate the bounds for the current window
        leftLimit   = (long)(currentTime - WINDOW_WIDTH + 1);
        rightLimit  = (long)(currentTime + WINDOW_WIDTH);

        // clamp the window 
        if( leftLimit < 0 )
        {
            leftLimit = 0;
        }

        if( rightLimit > sampleCount )
        {
            rightLimit = sampleCount;
        }

        // if we're pitch shifting down
        if( currentFactor < 1.0 )
        {
            for( int j = leftLimit; j < rightLimit; ++j )
            {
                tempData += GetDelayData( j - intTime ) * SinC( currentTime - (double)j );
            }

            outputData = (short)tempData;
        }
        // otherwise if shifting up
        else
        {
            oneOverFactor = 1.0 / currentFactor;

            for( int j = leftLimit; j < rightLimit; ++j )
            {
                tempData += GetDelayData( j - intTime ) * oneOverFactor * SinC( oneOverFactor * (currentTime - (double)j) );
            }

            outputData = (short)tempData;
        }

        outputSamples.push_back( outputData );
        currentTime += currentFactor;
        lastTime    = intTime;
        intTime     = (long)currentTime;

        // increment time
        while( lastTime < intTime )
        {
            inputData = wavFile.GetSample( ++currentSample );
            if( currentSample == sampleCount )
            {
                pitchShiftComplete = true;
            }

            SetDelayData( inputData );
            ++lastTime;
        }

        currentFactor = m_pitchShiftFactor + (currentTime * deltaFactor);
    }

    wavFile.SetWavData( outputSamples );
    wavFile.Save( anOutputFile );
    */

    return true;
}

//////////////////////////////////////////////////////////////////////////

int CPitchShift::GetDelayData( long aTime )
{
    return m_delayBuffer[(int)aTime + WINDOW_WIDTH];
}

//////////////////////////////////////////////////////////////////////////

// the delayed data is a shifting window of the original wav form
void CPitchShift::SetDelayData( int aValue )
{
    for( int i = 0, e = DELAY_SIZE - 5; i < e; ++i )
    {
        m_delayBuffer[i] = m_delayBuffer[i + 1];
    }

    m_delayBuffer[DELAY_SIZE - 5] = aValue;
}

//////////////////////////////////////////////////////////////////////////

// sinc - sin(pi * x) / x
double CPitchShift::SinC( double aValue )
{
    if( aValue == 0.0 )
    {
        return 1.0;
    }

    double temp = PI * aValue;
    return sin(temp) / temp;
}

//////////////////////////////////////////////////////////////////////////