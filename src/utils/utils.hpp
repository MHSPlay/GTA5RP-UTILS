#pragma once

#include "shadowsyscall.hpp"
namespace utils
{
    HWND window;

    struct Point {
        int x;
        int y;
    };

	inline std::string random_str(size_t length)
	{
		auto randchar = []() -> char
		{
			const char charset[] =
			{
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz"
			};

			const size_t max_index = (sizeof(charset) - 1);
			return charset[rand() % max_index];
		};
		std::string str(length, 0);
		std::generate_n(str.begin(), length, randchar);
		return str;
	}

	inline std::string randomLowerString( size_t length ){
		auto randchar = [ ]( ) -> char {
			const char charset[ ] = {
				"0123456789"
				"abcdefghijklmnopqrstuvwxyz"
			};

			const size_t max_index = ( sizeof( charset ) - 1 );
			return charset[ rand( ) % max_index ];
		};
		std::string str( length, 0 );
		std::generate_n( str.begin( ), length, randchar );
		return str;
	}

	inline int randomInt( int min, int max ) {
		static bool first = true;
		if ( first ) {
			srand( ( unsigned int )time( NULL ) );
			first = false;
		}
		return min + rand( ) % ( ( max + 1 ) - min );
	}

    DWORD GetProcessId(LPCSTR ProcessName) {
        PROCESSENTRY32 pt;
        HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        pt.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hsnap, &pt)) {
            do {
                if (!lstrcmpi(pt.szExeFile, ProcessName)) {
                    CloseHandle(hsnap);
                    return pt.th32ProcessID;
                }
            } while (Process32Next(hsnap, &pt));
        }
        CloseHandle(hsnap);
        return 0;
    }

	inline bool ActivateWindow( ) {

		if ( !window )
			return false;

		SetForegroundWindow( window );
		return true;
	}

	inline void shadowSendKey( WORD virtualKey ) {
		INPUT input = { 0 };
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = virtualKey;

		shadowcall< UINT >( "SendInput", 1, &input, sizeof( INPUT ) );
		input.ki.dwFlags = KEYEVENTF_KEYUP;
		shadowcall< UINT >( "SendInput", 1, &input, sizeof( INPUT ) );
	}

    inline void shadowSendKeyCode( WORD virtualKey, bool hold = false ) {
        INPUT input = { 0 };

        input.type = INPUT_KEYBOARD;
        input.ki.time = 0;
        input.ki.wVk = 0;
        input.ki.dwExtraInfo = 0;
        input.ki.dwFlags = KEYEVENTF_SCANCODE;
        input.ki.wScan = virtualKey;

        shadowcall< UINT >( "SendInput", 1, &input, sizeof( INPUT ) );

        if ( !hold ) {
            input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
            shadowcall< UINT >( "SendInput", 1, &input, sizeof( INPUT ) );
        }
    }

	inline void shadowClickMouseAt( int x, int y, bool doubleClick = false ) {
		shadowcall< BOOL >( "SetCursorPos", x, y );

		INPUT input = { 0 };
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		shadowcall< UINT >( "SendInput", 1, &input, sizeof( INPUT ) );

		input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		shadowcall< UINT >( "SendInput", 1, &input, sizeof( INPUT ) );

        if ( doubleClick ) {
            input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		    shadowcall< UINT >( "SendInput", 1, &input, sizeof( INPUT ) );

		    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		    shadowcall< UINT >( "SendInput", 1, &input, sizeof( INPUT ) );
        }
	}

    inline bool PixelSearch(COLORREF targetColor, int startX, int startY, int width, int height, int variation = 0) {
        HDC hdcScreen = GetDC( utils::window );
        if (!hdcScreen)
            return false;

        HDC hdcMem = CreateCompatibleDC(hdcScreen);
        if (!hdcMem) {
            ReleaseDC(utils::window, hdcScreen);
            return false;
        }

        HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, width, height);
        if (!hBitmap) {
            DeleteDC(hdcMem);
            ReleaseDC(utils::window, hdcScreen);
            return false;
        }

        HGDIOBJ hOldObj = SelectObject(hdcMem, hBitmap);
        if (!BitBlt(hdcMem, 0, 0, width, height, hdcScreen, startX, startY, SRCCOPY)) {
            SelectObject(hdcMem, hOldObj);
            DeleteObject(hBitmap);
            DeleteDC(hdcMem);
            ReleaseDC(utils::window, hdcScreen);
            return false;
        }

        BITMAPINFO bmpInfo = {};
        bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmpInfo.bmiHeader.biWidth = width;
        bmpInfo.bmiHeader.biHeight = -height; // Negative to indicate top-down bitmap
        bmpInfo.bmiHeader.biPlanes = 1;
        bmpInfo.bmiHeader.biBitCount = 24;
        bmpInfo.bmiHeader.biCompression = BI_RGB;

        std::unique_ptr<BYTE[]> pixels(new BYTE[width * height * 3]);

        if (!GetDIBits(hdcMem, hBitmap, 0, height, pixels.get(), &bmpInfo, DIB_RGB_COLORS)) {
            SelectObject(hdcMem, hOldObj);
            DeleteObject(hBitmap);
            DeleteDC(hdcMem);
            ReleaseDC(utils::window, hdcScreen);
            return false;
        }

        BYTE targetRed = GetRValue(targetColor);
        BYTE targetGreen = GetGValue(targetColor);
        BYTE targetBlue = GetBValue(targetColor);

        bool found = false;
        for (int y = 0; y < height && !found; ++y) {
            for (int x = 0; x < width; ++x) {
                int i = (y * width + x) * 3;

                BYTE red = pixels[i + 2];    // Red is the third byte
                BYTE green = pixels[i + 1];  // Green is the second byte
                BYTE blue = pixels[i];       // Blue is the first byte

                if (std::abs(targetRed - red) <= variation &&
                    std::abs(targetGreen - green) <= variation &&
                    std::abs(targetBlue - blue) <= variation) {
                    found = true;
                    break;
                }
            }
        }

        SelectObject(hdcMem, hOldObj);
        DeleteObject(hBitmap);
        DeleteDC(hdcMem);
        ReleaseDC(utils::window, hdcScreen);

        return found;
    }

    inline bool ComparePixels(const BYTE* screenPixel, const BYTE* templatePixel, int variation) {
        return (std::abs(screenPixel[0] - templatePixel[0]) <= variation &&
            std::abs(screenPixel[1] - templatePixel[1]) <= variation &&
            std::abs(screenPixel[2] - templatePixel[2]) <= variation);
    }

    inline bool CompareRegion(const BYTE* screenPixels, int screenWidth, int screenHeight,
        const BYTE* templatePixels, int templateWidth, int templateHeight, int variation) {
        for (int y = 0; y < templateHeight; ++y) {
            for (int x = 0; x < templateWidth; ++x) {
                int screenIndex = ((y * screenWidth) + x) * 3;
                int templateIndex = ((y * templateWidth) + x) * 3;
                if (!ComparePixels(&screenPixels[screenIndex], &templatePixels[templateIndex], variation))
                    return false;
            }
        }
        return true;
    }

    inline Point ImageSearch(HBITMAP hTemplate, int startX, int startY, int searchWidth, int searchHeight, int variation = 0) {
        HDC hdcScreen = GetDC(NULL);
        if (!hdcScreen)
            return { -1, -1 };

        HDC hdcMem = CreateCompatibleDC(hdcScreen);
        if (!hdcMem) {
            ReleaseDC(NULL, hdcScreen);
            return { -1, -1 };
        }

        HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, searchWidth, searchHeight);
        if (!hBitmap) {
            DeleteDC(hdcMem);
            ReleaseDC(NULL, hdcScreen);
            return { -1, -1 };
        }

        HGDIOBJ hOldObj = SelectObject(hdcMem, hBitmap);
        if (!BitBlt(hdcMem, 0, 0, searchWidth, searchHeight, hdcScreen, startX, startY, SRCCOPY)) {
            SelectObject(hdcMem, hOldObj);
            DeleteObject(hBitmap);
            DeleteDC(hdcMem);
            ReleaseDC(NULL, hdcScreen);
            return { -1, -1 };
        }

        BITMAP templateInfo = {};
        GetObject(hTemplate, sizeof(templateInfo), &templateInfo);

        int templateWidth = templateInfo.bmWidth;
        int templateHeight = templateInfo.bmHeight;
        BITMAPINFO bmpInfo = {};
        bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmpInfo.bmiHeader.biWidth = searchWidth;
        bmpInfo.bmiHeader.biHeight = -searchHeight;  // Top-down
        bmpInfo.bmiHeader.biPlanes = 1;
        bmpInfo.bmiHeader.biBitCount = 24;
        bmpInfo.bmiHeader.biCompression = BI_RGB;

        std::vector<BYTE> screenPixels(searchWidth * searchHeight * 3);
        if (!GetDIBits(hdcMem, hBitmap, 0, searchHeight, screenPixels.data(), &bmpInfo, DIB_RGB_COLORS)) {
            SelectObject(hdcMem, hOldObj);
            DeleteObject(hBitmap);
            DeleteDC(hdcMem);
            ReleaseDC(NULL, hdcScreen);
            return { -1, -1 };
        }

        bmpInfo.bmiHeader.biWidth = templateWidth;
        bmpInfo.bmiHeader.biHeight = -templateHeight;  // Top-down
        std::vector<BYTE> templatePixels(templateWidth * templateHeight * 3);
        if (!GetDIBits(hdcScreen, hTemplate, 0, templateHeight, templatePixels.data(), &bmpInfo, DIB_RGB_COLORS)) {
            SelectObject(hdcMem, hOldObj);
            DeleteObject(hBitmap);
            DeleteDC(hdcMem);
            ReleaseDC(NULL, hdcScreen);
            return { -1, -1 };
        }

        Point foundPosition = { -1, -1 };
        for (int y = 0; y <= searchHeight - templateHeight; ++y) {
            for (int x = 0; x <= searchWidth - templateWidth; ++x) {
                int offset = (y * searchWidth + x) * 3;
                if (CompareRegion(&screenPixels[offset], searchWidth, searchHeight,
                    templatePixels.data(), templateWidth, templateHeight, variation)) {
                    foundPosition = { startX + x, startY + y };
                    break;
                }
            }
            if (foundPosition.x != -1)
                break;
        }

        SelectObject(hdcMem, hOldObj);
        DeleteObject(hBitmap);
        DeleteDC(hdcMem);
        ReleaseDC(NULL, hdcScreen);

        return foundPosition;
    }


}