#pragma once

//////////////////////////////////////////////////////////////////////////
/// Forward Declarations
//////////////////////////////////////////////////////////////////////////

class CRenderContext;
class CSoundSystem;


//////////////////////////////////////////////////////////////////////////
/// CEngine
//////////////////////////////////////////////////////////////////////////

class CEngine
{
public :

    //////////////////////////////////////////////////////////////////////////

    CEngine();
    ~CEngine();

    //////////////////////////////////////////////////////////////////////////

    bool Initialise( HWND aWindowHandle, int aWindowWidth, int aWindowHeight );
    
    void Update();

    //////////////////////////////////////////////////////////////////////////

    bool IsInitialized() const;


private :

    //////////////////////////////////////////////////////////////////////////

    void Render();
    
    //////////////////////////////////////////////////////////////////////////

    CRenderContext* myRenderContext;
    CSoundSystem*   mySoundSystem;
    bool            myInitialised;
};

//////////////////////////////////////////////////////////////////////////