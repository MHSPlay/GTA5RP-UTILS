#pragma once

namespace ui_custom
{
	inline bool InputTextCentered(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL) {
		const float input_width = ImGui::CalcItemWidth( );
		ImGui::SetCursorPosX( ( ( ImGui::GetWindowContentRegionMax().x - input_width ) + 6.f ) / 2.f );
		return ImGui::InputText( label, buf, buf_size, flags, callback, user_data );
	}

	inline void HotKey( const char* label, int& key ) noexcept
	{
		ImGui::Text( label );

		ImGui::SameLine( );

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

	inline void CheckboxWithTooltip( const char* label, bool* value, const char* tooltip ) {
		if ( ImGui::Checkbox( label, value ) )
		{
    
		}
		if ( ImGui::IsItemHovered( ) )
			ImGui::SetTooltip( "%s", tooltip );
	}

    constexpr
    static auto lerp(float x0, float x1) {
        return [=](float t){
            return (1-t) * x0 + t * x1;
        };
    }

    constexpr
    static float lerp(float x0, float x1, float t) {
        return lerp(x0, x1)(t);
    }

    static auto interval(float T0, float T1, std::function<float(float)> tween = lerp(0.0, 1.0)) {
        return [=](float t){
            return t < T0 ? 0.0f : t > T1 ? 1.0f : tween((t-T0) / (T1-T0));
        };
    }

    template <int T>
    float sawtooth(float t) {
        return ImFmod(((float)T)*t, 1.0f);
    }

    static float cubic_bezier( float t, float p0, float p1, float p2, float p3 ) {
        float u = 1 - t;
        return u * u * u * p0 + 3 * u * u * t * p1 + 3 * u * t * t * p2 + t * t * t * p3;
    }

    static float fast_out_slow_in( float t ) {
        return cubic_bezier( t, 0.0f, 0.4f, 0.2f, 1.0f );
    }

    static float bezier( float t ) {
       return fast_out_slow_in( t );
    }

    bool Spinner( const char* label, float radius, int thickness, const ImU32& color ) {
        ImGuiWindow* window = ImGui::GetCurrentWindow( );
        if ( window->SkipItems )
            return false;
        
        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID( label );
        
        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size ( ( radius )*2, ( radius + style.FramePadding.y ) * 2 );
        
        const ImRect bb ( pos, ImVec2( pos.x + size.x, pos.y + size.y ) );
        ImGui::ItemSize( bb, style.FramePadding.y );
        if ( !ImGui::ItemAdd( bb, id ) )
            return false;
        
        // Render
        const ImVec2 center = ImVec2( pos.x + radius, pos.y + radius + thickness + style.FramePadding.y );

        const float start_angle = -IM_PI / 2.0f;         // Start at the top
        const int num_detents = 5;                       // how many rotations we want before a repeat
        const int skip_detents = 3;                      // how many steps we skip each rotation
        const float period = 5.0f;                       // in seconds
        const float t = ImFmod( g.Time, period ) / period; // map period into [0, 1]

        // Tweening functions for each part of the spinner
        auto stroke_head_tween = [ ]( float t ){
            t = sawtooth< num_detents >( t );
            return interval (0.0, 0.5, bezier )( t );
        };

        auto stroke_tail_tween = [](float t){
            t = sawtooth<num_detents>(t);
            return interval(0.5, 1.0, bezier)(t);
        };

        auto step_tween = [=](float t){
            return floor(lerp(0.0, (float)num_detents, t));
        };

        auto rotation_tween = sawtooth<num_detents>;

        const float head_value = stroke_head_tween(t);
        const float tail_value = stroke_tail_tween(t);
        const float step_value = step_tween(t);
        const float rotation_value = rotation_tween(t);

        const float min_arc =  30.0f / 360.0f * 2.0f * IM_PI;
        const float max_arc = 270.0f / 360.0f * 2.0f * IM_PI;
        const float step_offset = skip_detents * 2.0f * IM_PI / num_detents;
        const float rotation_compensation = ImFmod(4.0*IM_PI - step_offset - max_arc, 2*IM_PI);

        const float a_min = start_angle + tail_value * max_arc + rotation_value * rotation_compensation - step_value * step_offset;
        const float a_max = a_min + (head_value - tail_value) * max_arc + min_arc;

        window->DrawList->PathClear();

        int num_segments = 24;
        for (int i = 0; i < num_segments; i++) {
            const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
            window->DrawList->PathLineTo(ImVec2(center.x + ImCos(a) * radius,
                                                center.y + ImSin(a) * radius));
        }

        window->DrawList->PathStroke(color, false, thickness);

        return true;
    }

};