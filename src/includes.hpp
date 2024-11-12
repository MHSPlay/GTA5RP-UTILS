#pragma once

// 0-9
#define VK_0              0x30
#define VK_1              0x31
#define VK_2              0x32
#define VK_3              0x33
#define VK_4              0x34
#define VK_5              0x35
#define VK_6              0x36
#define VK_7              0x37
#define VK_8              0x38
#define VK_9              0x39

// A-Z
#define VK_A              0x41
#define VK_B              0x42
#define VK_C              0x43
#define VK_D              0x44
#define VK_E              0x45
#define VK_F              0x46
#define VK_G              0x47
#define VK_H              0x48
#define VK_I              0x49
#define VK_J              0x4A
#define VK_K              0x4B
#define VK_L              0x4C
#define VK_M              0x4D
#define VK_N              0x4E
#define VK_O              0x4F
#define VK_P              0x50
#define VK_Q              0x51
#define VK_R              0x52
#define VK_S              0x53
#define VK_T              0x54
#define VK_U              0x55
#define VK_V              0x56
#define VK_W              0x57
#define VK_X              0x58
#define VK_Y              0x59
#define VK_Z              0x5A

// windows / stl includes.
#include <Windows.h>
#include <WinUser.h>
#include <cstdint>
#include <intrin.h>
#include <xmmintrin.h>
#include <array>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <chrono>
#include <thread>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <deque>
#include <functional>
#include <map>
#include <shlobj.h>
#include <filesystem>
#include <streambuf>
#include <TlHelp32.h>
#include <dwmapi.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include "config/config.hpp"
#include "security/auth.hpp"

// fonts
#include "..\third-party\fonts\fa_solid_900.h"
#include "..\third-party\fonts\tahoma.h"
#include "..\third-party\fonts\font_awesome_5.h"
#include "..\third-party\fonts\04B03.h"

// IMGUI
static ID3D11Device*           g_pd3dDevice;
static ID3D11DeviceContext*    g_pd3dDeviceContext;
static IDXGISwapChain*         g_pSwapChain;
static ID3D11RenderTargetView* g_mainRenderTargetView;
static UINT                    g_ResizeWidth = 0, 
							   g_ResizeHeight = 0;
#include "..\third-party\imgui\imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "..\third-party\imgui\imgui_internal.h"
#include "..\third-party\imgui\imgui_impl_dx11.h"
#include "..\third-party\imgui\imgui_impl_win32.h"

// GUI
#include "..\third-party\imgui\custom\notify\imgui_notify.hpp"
#include "ui/impl/impl.hpp"
#include "ui/ui.hpp"

// other stuff
#include "utils/shadowsyscall.hpp"
#include "utils/utils.hpp"
#include "features/features.hpp"

