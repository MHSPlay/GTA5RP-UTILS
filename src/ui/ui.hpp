#pragma once

bool InputTextCentered(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL) {
    const float input_width = ImGui::CalcItemWidth( );
    ImGui::SetCursorPosX( ( ( ImGui::GetWindowContentRegionMax().x - input_width ) + 6.f ) / 2.f );
    return ImGui::InputText( label, buf, buf_size, flags, callback, user_data );
}

void HotKey( int& key ) noexcept
{
	key ? ImGui::Text( "[ 0x%x ]", key ) 
		: ImGui::TextUnformatted( "[ key ]" );

	if ( ImGui::IsItemHovered( ) ) 
	{
		ImGui::SetTooltip("Press any key to change keybind");

		ImGuiIO& io = ImGui::GetIO( );
		for ( int i = 0; i < IM_ARRAYSIZE( io.KeysDown ); i++)
			if ( ImGui::IsKeyPressed( i ) && i != 0x2D )
				key = i != VK_ESCAPE ? i : 0;

		for ( int i = 0; i < IM_ARRAYSIZE( io.MouseDown ); i++ )
			if ( ImGui::IsMouseDown( i ) && i + ( i > 1 ? 2 : 1 ) != 0x2D )
				key = i + ( i > 1 ? 2 : 1 );
	}
}

void CheckboxWithTooltip( const char* label, bool* value, const char* tooltip ) {
	if ( ImGui::Checkbox( label, value ) )
    {
    
    }
	if ( ImGui::IsItemHovered( ) )
		ImGui::SetTooltip( "%s", tooltip );
}

namespace ui {
	bool menuOpened = true;

	auto GUI( ) -> void
	{
        static int state = 0;
        static float alpha = 0.0f;
        static float fadeSpeed = 0.02f;

		static bool once = false;
		if ( !once ) {
			ImGui::InsertNotification( { ImGuiToastType_Success, 3000, "ImGui Render Initialization Successfully!" } );
			once = true;
		}

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
			ImGuiWindowFlags_NoMove );

        {

            switch ( state )
            {
                // auth
                case 0:
                {
                    AuthSystem auth;
                    ImVec2 window_size = ImGui::GetWindowSize( );

                    ImVec2 text_size = ImGui::CalcTextSize( "login:" );
                    ImVec2 text_pos( ( window_size.x - text_size.x ) * 0.5f, ImGui::GetCursorPosY( ) );
                    ImGui::SetCursorPos( text_pos );
                    ImGui::Text("login:");
                    InputTextCentered( "##login", login, IM_ARRAYSIZE( login ) );

                    ImGui::Spacing( );

                    text_size = ImGui::CalcTextSize( "password:" );
                    text_pos = ImVec2( ( window_size.x - text_size.x ) * 0.5f, ImGui::GetCursorPosY( ) );
                    ImGui::SetCursorPos( text_pos );
                    ImGui::Text( "password:" );
                    InputTextCentered( "##password", password, IM_ARRAYSIZE( password ), ImGuiInputTextFlags_Password );

                    ImGui::Spacing( );

                    ImVec2 button_size = ImVec2( 100, 30 );
                    ImVec2 button_pos( ( window_size.x - button_size.x ) * 0.5f, ImGui::GetCursorPosY( ) );

                    ImGui::SetCursorPos( button_pos );
                    if ( ImGui::Button( "Login", button_size ) ) {
                        
                        if ( auth.login( login, password ) ) {
                            ImGui::InsertNotification( { ImGuiToastType_Success, 3000, "Login Successfully!" } );
							ImGui::InsertNotification( { ImGuiToastType_Info, 10000, "Work only on 1920x1080 - 16:9!" } );
                            state = 1;
                        }
                        else
                            ImGui::InsertNotification( { ImGuiToastType_Error, 3000, "Incorrect username or password!" } );

                    }

                }
                break;

                // main
                case 1:
                {
                    static ImVec2 targetSize( 700, 400 );
                    static ImVec2 currentSize = ImGui::GetWindowSize( );
                    static float animationSpeed = 10.0f;

                    if ( currentSize.x < targetSize.x )
                        currentSize.x += animationSpeed + 17.0f;

                    if ( currentSize.y < targetSize.y )
                        currentSize.y += animationSpeed;

                    ImGui::SetWindowSize( currentSize );
                    ImGui::SetWindowPos( ImVec2(
                        ( ImGui::GetIO( ).DisplaySize.x - 700 ) * 0.5f,
                        ( ImGui::GetIO( ).DisplaySize.y - 400 ) * 0.5f
                    ) );


                    CheckboxWithTooltip( "AntiAFK", &config::bAntiAfkEnabled, "just turn off the monitor and enjoy it. ( wheel of fortune included )" );
					
					HotKey( config::iFastLootKey );

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
        style.FramePadding                      = ImVec2(5.00f, 2.00f);
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
        style.WindowRounding                    = 7;
        style.ChildRounding                     = 4;
        style.FrameRounding                     = 3;
        style.PopupRounding                     = 4;
        style.ScrollbarRounding                 = 9;
        style.GrabRounding                      = 3;
        style.LogSliderDeadzone                 = 4;
        style.TabRounding                       = 4;
    }

};