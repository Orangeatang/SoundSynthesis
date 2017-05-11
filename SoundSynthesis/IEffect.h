#pragma once

//////////////////////////////////////////////////////////////////////////
/// Inculdes
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
/// IEffect
//////////////////////////////////////////////////////////////////////////

class IEffect
{
public:

    virtual bool ProcessAudio( const char* anInputFile, const char* anOutputFile ) = 0;
};