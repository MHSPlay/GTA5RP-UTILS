#pragma once

#include "custom/custom.hpp"

namespace ui {
	bool menuOpened = true;

	auto GUI( ) -> void
	{
        static int state = 0;
        static float alpha = 0.0f;
        static float fadeSpeed = 0.02f;

		//static bool once = false;
		//if ( !once ) {
		//	ImGui::InsertNotification( { ImGuiToastType_Success, 3000, "ImGui Render Initialization Successfully!" } );
		//	once = true;
		//}

        static char login[16] = "";
        static char password[32] = "";

        ImGui::SetNextWindowSize( ImVec2( 200, 200 ), ImGuiCond_Once );
        ImGui::SetNextWindowPos( ImVec2(
            ( ImGui::GetIO( ).DisplaySize.x - 200 ) * 0.5f,
            ( ImGui::GetIO( ).DisplaySize.y - 200 ) * 0.5f
        ), ImGuiCond_Once );

        if ( alpha < 1.0f )
            alpha += fadeSpeed;

        ImGui::PushStyleVar( ImGuiStyleVar_Alpha, alpha );
        ImGui::Begin( "mighty", nullptr,
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_HorizontalScrollbar| 
			ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoScrollWithMouse);

        {

            switch ( state )
            {
                // update
                case 0:
                {
                    ImVec2 window_size = ImGui::GetWindowSize( );
                    ImVec2 window_pos = ImGui::GetWindowPos( );
                    const float spinner_radius = 20.0f;
                    const float spinner_thickness = 5.0f;

                    auto DisplayCenteredSpinnerAndText = [ & ]( const char* spinner_id, const char* text, const ImColor& color ) {
                        ImVec2 center(
                            window_pos.x + ( window_size.x - spinner_radius * 2 ) * 0.5f,
                            window_pos.y + ( window_size.y - spinner_radius * 2 - spinner_thickness ) * 0.5f
                        );

                        ImGui::SetCursorScreenPos( center );
                        ui_custom::Spinner( spinner_id, spinner_radius, spinner_thickness, color );

                        ImVec2 text_size = ImGui::CalcTextSize( text );
                        ImVec2 text_pos( ( window_size.x - text_size.x ) * 0.5f, ImGui::GetCursorPosY( ) + 45 );
                        ImGui::SetCursorPos( text_pos );
                        ImGui::Text( text );
                        };

                    if ( security_update::isCheckingUpdates ) 
                    {
                        DisplayCenteredSpinnerAndText( "##updates", "Checking for updates...", ImColor( 255, 255, 255 ) );

                        std::string latestVersion = security_update::getLatestVersion( security_update::versionURL );
                        if ( latestVersion != security_update::currentVersion ) {
                            security_update::updateAvailable = true;
                            security_update::isCheckingUpdates = false;
                        }
                        else 
                        {
                            security_update::isCheckingUpdates = false;
                            state = 1;
                        }
                    }
                    else if ( security_update::updateAvailable ) 
                    {
                        DisplayCenteredSpinnerAndText( "##updates_available", "Update available!", ImColor( 255, 255, 255 ) );

                        std::string new_filename = utils::random_str( utils::randomInt( 16, 28 ) ) + ".exe";
                        if ( security_update::DownloadAndReplaceFile( security_update::applicationURL, new_filename ) )
                        {
                            ImGui::InsertNotification( { ImGuiToastType_Success, 5000, "Update successful!" } );
                            std::exit( EXIT_SUCCESS );
                        }
                    }
                    else 
                        state = 1;
                    
                }
                break;

                // auth
                case 1:
                {
                    AuthSystem auth;
                    ImVec2 window_size = ImGui::GetWindowSize( );

                    ImVec2 text_size = ImGui::CalcTextSize( "login:" );
                    ImVec2 text_pos( ( window_size.x - text_size.x ) * 0.5f, ImGui::GetCursorPosY( ) );
                    ImGui::SetCursorPos( text_pos );
                    ImGui::Text("login:");
                    ui_custom::InputTextCentered( "##login", login, IM_ARRAYSIZE( login ) );

                    ImGui::Spacing( );

                    text_size = ImGui::CalcTextSize( "password:" );
                    text_pos = ImVec2( ( window_size.x - text_size.x ) * 0.5f, ImGui::GetCursorPosY( ) );
                    ImGui::SetCursorPos( text_pos );
                    ImGui::Text( "password:" );
                    ui_custom::InputTextCentered( "##password", password, IM_ARRAYSIZE( password ), ImGuiInputTextFlags_Password );

                    ImGui::Spacing( );

                    ImVec2 button_size = ImVec2( 100, 30 );
                    ImVec2 button_pos( ( window_size.x - button_size.x ) * 0.5f, ImGui::GetCursorPosY( ) );

                    ImGui::SetCursorPos( button_pos );
                    if ( ImGui::Button( "Login", button_size ) ) {
                        
                        if ( auth.login( login, password ) ) {
                            ImGui::InsertNotification( { ImGuiToastType_Success, 3000, "Login Successfully!" } );
							ImGui::InsertNotification( { ImGuiToastType_Info, 10000, "Work only on 1920x1080 - 16:9!" } );
                            state = 2;
                        }
                        else
                            ImGui::InsertNotification( { ImGuiToastType_Error, 3000, "Incorrect username or password!" } );

                    }

                }
                break;

                // main
                case 2:
                {
                    static bool showMenu = false;
                    static bool buttonsVisible = false;
                    static float buttonAlpha = 0.0f;

                    // form setup
                    {
                        static ImVec2 targetSize( 635, 400 );
                        static ImVec2 currentSize = ImGui::GetWindowSize( );
                        static float animationSpeed = 10.0f;

                        if ( currentSize.x < targetSize.x )
                            currentSize.x = ImClamp( currentSize.x + animationSpeed + 17.0f, 0.0f, targetSize.x );

                        if ( currentSize.y < targetSize.y )
                            currentSize.y = ImClamp( currentSize.y + animationSpeed, 0.0f, targetSize.y );

                        if ( currentSize.x == targetSize.x && currentSize.y == targetSize.y )
                            showMenu = true;

                        ImGui::SetWindowSize( currentSize );
                        ImGui::SetWindowPos( ImVec2(
                            ( ImGui::GetIO( ).DisplaySize.x - targetSize.x ) * 0.5f,
                            ( ImGui::GetIO( ).DisplaySize.y - targetSize.y ) * 0.5f
                        ));
                    }

                    if ( showMenu ) 
                    {
                        if ( buttonAlpha < 1.0f )
                            buttonAlpha = ImMin( buttonAlpha + ImGui::GetIO( ).DeltaTime * 2.0f, 1.0f );

                        ImGui::PushStyleVar( ImGuiStyleVar_Alpha, buttonAlpha );

                        ImGui::BeginChild( "antiAFK", ImVec2( 150, 175 ), true );
                        {
                            ImVec2 text_size = ImGui::CalcTextSize( "anti-afk bypass:" );
                            ImVec2 text_pos( ( 150 - text_size.x ) * 0.5f, ImGui::GetCursorPosY( ) );
                            ImGui::SetCursorPos( text_pos );
                            ImGui::Text( "anti-afk bypass:" );
                        
                            ImGui::Checkbox( "enable", &config::afk_bypass::bEnabled );
                            ImGui::Checkbox( "spin wheel", &config::afk_bypass::bAutoWheel );

                        }
                        ImGui::EndChild( );

                        // next
                        ImGui::SameLine( );

                        ImGui::BeginChild( "fastLoot", ImVec2( 150, 175 ), true );
                        {
                            ImVec2 text_size = ImGui::CalcTextSize( "fast loot:" );
                            ImVec2 text_pos( ( 150 - text_size.x ) * 0.5f, ImGui::GetCursorPosY( ) );
                            ImGui::SetCursorPos( text_pos );
                            ImGui::Text( "fast loot:" );
                        
                            ImGui::Checkbox( "enable", &config::fast_loot::bEnabled );
                            ui_custom::HotKey( "HotKey:", config::fast_loot::iKey );

                        }
                        ImGui::EndChild( );

                        // next
                        ImGui::SameLine( );

                        ImGui::BeginChild( "harbor", ImVec2( 150, 175 ), true );
                        {
                            ImVec2 text_size = ImGui::CalcTextSize( "harbor bot:" );
                            ImVec2 text_pos( ( 150 - text_size.x ) * 0.5f, ImGui::GetCursorPosY( ) );
                            ImGui::SetCursorPos( text_pos );
                            ImGui::Text( "harbor bot:" );
                        
                            ImGui::Checkbox( "enable", &config::harbor::bEnabled );
                            ui_custom::HotKey( "HotKey:", config::harbor::iKey );
                            ImGui::Combo( "##harbor", &config::harbor::iKeyMode, "Hold\0Toggle\0" );

                        }
                        ImGui::EndChild( );

                        // next
                        ImGui::SameLine( );

                        ImGui::BeginChild( "sewing", ImVec2( 150, 175 ), true );
                        {
                            ImVec2 text_size = ImGui::CalcTextSize( "sewing bot:" );
                            ImVec2 text_pos( ( 150 - text_size.x ) * 0.5f, ImGui::GetCursorPosY( ) );
                            ImGui::SetCursorPos( text_pos );
                            ImGui::Text( "sewing bot:" );
                        
                            ImGui::Checkbox( "enable", &config::sewing::bEnabled );
                            ui_custom::HotKey( "HotKey:", config::sewing::iKey );
                            ImGui::Combo( "##sewing", &config::sewing::iKeyMode, "Hold\0Toggle\0" );

                            ImGui::SliderInt( "ms.##delay", &config::sewing::iDelay, 0, 2500 );
                            ImGui::SliderInt( "ms.##delay2", &config::sewing::iDelay2, 0, 2500 );
                            ImGui::SliderInt( "ms.##delay3", &config::sewing::iDelay3, 0, 2500 );

                        }
                        ImGui::EndChild( );

                        // go down
                        ImGui::Separator( );

                        ImGui::Button( "n1", ImVec2( 150, 175 ) );

                        // next
                        ImGui::SameLine( );

                        ImGui::Button( "n2", ImVec2( 150, 175 ) );

                        // next
                        ImGui::SameLine( );

                        ImGui::Button( "n3", ImVec2( 150, 175 ) );

                        // next
                        ImGui::SameLine( );

                        ImGui::Button( "n4", ImVec2( 150, 175 ) );

                        ImGui::PopStyleVar( );

                    }
                    //ui_custom::CheckboxWithTooltip( "AntiAFK", &config::bAntiAfkEnabled, "just turn off the monitor and enjoy it. ( wheel of fortune included )" );
					
                    //ui_custom::HotKey( "fast loot key:", config::iFastLootKey);

                    // OSIRIS HOTKEY BETTER!!!
					//if (config.aimbot[weaponIndex].onKey) {
					//	if (!config.aimbot[weaponIndex].keyMode) {
					//		if (!GetAsyncKeyState(config.aimbot[weaponIndex].key))
					//			return;
					//	}
					//	else {
					//		static bool toggle = true;
					//		if (GetAsyncKeyState(config.aimbot[weaponIndex].key) & 1)
					//			toggle = !toggle;
					//		if (!toggle)
					//			return;
					//	}
					//}





                    // todo:
                    // - fix font on notify 
                    // - maybe add auth & HWID
                    // - make menu looks like better
                    // - more custom settings

                    // rework anti-afk 
                    // add more checks to make sure it doesn't break











                }
                break;


            }

        }   
        ImGui::End( );
        ImGui::PopStyleVar( );

	}

    auto notify() -> void 
    {
        // Render toasts on top of everything, at the end of your code!
		// You should push style vars here
        ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, 0.f ); // Disable round borders
        ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.f ); // Disable borders
        // Notifications color setup
        ImGui::PushStyleColor( ImGuiCol_WindowBg, ImVec4( 0.10f, 0.10f, 0.10f, 1.00f ) ); // Background color

		ImGui::RenderNotifications( );

		ImGui::PopStyleVar( 2 ); // Don't forget to Pop()
		ImGui::PopStyleColor( 1 );

    }

	// ImGui Theme by janekb04(https://github.com/janekb04), Find more themes at https://github.com/ocornut/imgui/issues/707
    void EmbraceTheDarkness()
    {
        ImVec4* colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_WindowBg]               = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
        colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg]                = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
        colors[ImGuiCol_Border]                 = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
        colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
        colors[ImGuiCol_FrameBg]                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        colors[ImGuiCol_FrameBgActive]          = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_TitleBg]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TitleBgActive]          = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
        colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        colors[ImGuiCol_CheckMark]              = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        colors[ImGuiCol_SliderGrab]             = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        colors[ImGuiCol_Button]                 = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_ButtonHovered]          = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        colors[ImGuiCol_ButtonActive]           = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_HeaderHovered]          = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
        colors[ImGuiCol_HeaderActive]           = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
        colors[ImGuiCol_Separator]              = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        colors[ImGuiCol_SeparatorActive]        = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        colors[ImGuiCol_ResizeGrip]             = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        colors[ImGuiCol_Tab]                    = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TabHovered]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_TabActive]              = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
        colors[ImGuiCol_TabUnfocused]           = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        //colors[ImGuiCol_DockingPreview]         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        //colors[ImGuiCol_DockingEmptyBg]         = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotLines]              = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogram]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TableBorderLight]       = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
        colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_DragDropTarget]         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        colors[ImGuiCol_NavHighlight]           = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowTitleAlign                  = ImVec2( 0.5f, 0.5f );
        style.WindowPadding                     = ImVec2(8.00f, 8.00f);
        style.FramePadding                      = ImVec2(4.00f, 2.00f);
        style.CellPadding                       = ImVec2(6.00f, 6.00f);
        style.ItemSpacing                       = ImVec2(6.00f, 6.00f);
        style.ItemInnerSpacing                  = ImVec2(6.00f, 6.00f);
        style.TouchExtraPadding                 = ImVec2(0.00f, 0.00f);
        style.IndentSpacing                     = 25;
        style.ScrollbarSize                     = 15;
        style.GrabMinSize                       = 10;
        style.WindowBorderSize                  = 1;
        style.ChildBorderSize                   = 1;
        style.PopupBorderSize                   = 1;
        style.FrameBorderSize                   = 1;
        style.TabBorderSize                     = 1;
        style.WindowRounding                    = 0;
        style.ChildRounding                     = 0;
        style.FrameRounding                     = 0;
        style.PopupRounding                     = 0;
        style.ScrollbarRounding                 = 0;
        style.GrabRounding                      = 0;
        style.LogSliderDeadzone                 = 4;
        style.TabRounding                       = 0;
    }

};