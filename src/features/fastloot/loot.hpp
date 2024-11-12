#pragma once

namespace fastloot
{
    auto run( ) -> void
    {
	    utils::ActivateWindow( );

	    auto getLoot = [ & ]( ) 
		{
			ImGui::InsertNotification( { ImGuiToastType_Info, 1500, "Trying loot..." } );

	        // press "E"
	        utils::shadowSendKey( 0x45 );

	        // click "MAX"
	        utils::shadowClickMouseAt( 1100, 575 );

			// just in case
			//std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );

	        // click "OK"
	        utils::shadowClickMouseAt( 860, 655 );
	    };

	    getLoot( );
		
	}
};