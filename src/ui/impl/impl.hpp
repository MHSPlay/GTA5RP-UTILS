#pragma once

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace ui
{
    inline void CreateRenderTarget( ) {
        ID3D11Texture2D* pBackBuffer;
        g_pSwapChain->GetBuffer( 0, IID_PPV_ARGS( &pBackBuffer ) );
        g_pd3dDevice->CreateRenderTargetView( pBackBuffer, nullptr, &g_mainRenderTargetView );
        pBackBuffer->Release( );
    }

    inline void CleanupRenderTarget( ) {
        if ( g_mainRenderTargetView ) { 
            g_mainRenderTargetView->Release( ); 
            g_mainRenderTargetView = nullptr;
        }
    }

    inline bool CreateDeviceD3D( HWND hWnd ) {
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory( &sd, sizeof( sd ) );
        sd.BufferCount = 2; // double buff
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        UINT createDeviceFlags = 0;
        D3D_FEATURE_LEVEL featureLevel;
        const D3D_FEATURE_LEVEL featureLevelArray[ 2 ] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

        HRESULT res = D3D11CreateDeviceAndSwapChain( nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext );

        if ( res == DXGI_ERROR_UNSUPPORTED )
            res = D3D11CreateDeviceAndSwapChain( nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext );

        if ( res != S_OK )
            return false;

        CreateRenderTarget( );
        return true;
    }

    inline void CleanupDeviceD3D( ) {
        CleanupRenderTarget( );
        if ( g_pSwapChain ) { 
            g_pSwapChain->Release( );
            g_pSwapChain = nullptr;
        }

        if ( g_pd3dDeviceContext ) { 
            g_pd3dDeviceContext->Release( ); 
            g_pd3dDeviceContext = nullptr; 
        }

        if ( g_pd3dDevice ) { 
            g_pd3dDevice->Release( ); 
            g_pd3dDevice = nullptr;
        }
    }

    LRESULT WINAPI WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
    {
        if ( ImGui_ImplWin32_WndProcHandler( hWnd, msg, wParam, lParam ) )
            return true;
        
        switch (msg)
        {
        case WM_SIZE:
            if (wParam == SIZE_MINIMIZED)
                return 0;
            g_ResizeWidth = (UINT)LOWORD(lParam);
            g_ResizeHeight = (UINT)HIWORD(lParam);
            return 0;
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU)
                return 0;
            break;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;
        }

        return ::DefWindowProcW(hWnd, msg, wParam, lParam);
    }

};