#pragma once

//////////////////////////////////////////////////////////////////////////
/// CRenderContext
//////////////////////////////////////////////////////////////////////////

class CRenderContext
{
public :

    CRenderContext();
    ~CRenderContext();

    //////////////////////////////////////////////////////////////////////////

    bool Initialize( HWND aWindowHandle, int aWindowWidth, int aWindowHeight );

    //////////////////////////////////////////////////////////////////////////


private :

    //////////////////////////////////////////////////////////////////////////

    IDXGISwapChain*         m_swapChain;
    ID3D11Device*           m_device;
    ID3D11DeviceContext*    m_deviceContext;
    ID3D11RenderTargetView* m_renderTarget;
};

//////////////////////////////////////////////////////////////////////////