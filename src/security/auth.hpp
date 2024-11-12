#pragma once

class AuthSystem {
private:
    std::unordered_map<std::string, std::string> users;

public:
    AuthSystem( ) {
        users[ "1" ] = "1";
    }

    bool login( const std::string& username, const std::string& password ) {
        if ( users.find( username ) != users.end( ) && users[ username ] == password ) 
            return true;
        
        return false;
    }

};