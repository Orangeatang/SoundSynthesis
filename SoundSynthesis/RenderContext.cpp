
//////////////////////////////////////////////////////////////////////////
/// Includes
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RenderContext.h"


//////////////////////////////////////////////////////////////////////////
/// CRenderContext
//////////////////////////////////////////////////////////////////////////

CRenderContext::CRenderContext() :
    m_device( nullptr ),
    m_deviceContext( nullptr ),
    m_swapChain( nullptr ),
    m_renderTarget( nullptr )
{
}

//////////////////////////////////////////////////////////////////////////

CRenderContext::~CRenderContext()
{
}

//////////////////////////////////////////////////////////////////////////

bool CRenderContext::Initialize( HWND aWindowHandle, int aWindowWidth, int aWindowHeight )
{
    // create a structure to hold information about the swap chain
    DXGI_SWAP_CHAIN_DESC swapChainDescription;
    ZeroMemory( &swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC) );

    HRESULT result = S_OK;

    // fill in the swap chain structure
    swapChainDescription.BufferCount        = 2;
    swapChainDescription.BufferDesc.Format  = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDescription.BufferUsage        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDescription.OutputWindow       = aWindowHandle;
    swapChainDescription.SampleDesc.Count   = 8;
    swapChainDescription.SampleDesc.Quality = 1;
    swapChainDescription.Windowed           = TRUE;
    swapChainDescription.Flags              = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    // create the context
    result = D3D11CreateDeviceAndSwapChain(
        NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        NULL,
        NULL,
        NULL,
        D3D11_SDK_VERSION,
        &swapChainDescription,
        &m_swapChain,
        &m_device,
        NULL,
        &m_deviceContext
    );

    // bail out if we are unable to initialize the directx context
    if( result != S_OK )
    {
        return false;
    }

    // get the address of the back buffer and use that as the render target
    ID3D11Texture2D* backBuffer = nullptr;
    result = m_swapChain->GetBuffer( 0, __uuidof(ID3D11Texture2D), (LPVOID*)m_renderTarget );
    if( result != S_OK )
    {
        return false;
    }
    backBuffer->Release();

    // set the render target as the back buffer
    m_deviceContext->OMSetRenderTargets( 1, &m_renderTarget, nullptr );

    // set the viewport
    D3D11_VIEWPORT viewport;
    ZeroMemory( &viewport, sizeof(D3D11_VIEWPORT) );

    viewport.TopLeftX   = 0;
    viewport.TopLeftY   = 0;
    viewport.Width      = (FLOAT)aWindowWidth;
    viewport.Height     = (FLOAT)aWindowHeight;

    m_deviceContext->RSSetViewports( 1, &viewport );

    return false;
}

//////////////////////////////////////////////////////////////////////////
