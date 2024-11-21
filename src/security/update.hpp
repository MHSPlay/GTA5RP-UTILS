#pragma once

namespace security_update {
    const std::string currentVersion = "0.1.1\n";
    const std::string versionURL = "https://raw.githubusercontent.com/MHSPlay/something/main/version.txt";
    const std::string applicationURL = "https://raw.githubusercontent.com/MHSPlay/something/main/GTA5RP-UTILS.exe";

    std::atomic<bool> isCheckingUpdates = true;
    std::atomic<bool> updateAvailable = false;

    size_t WriteCallback( void* contents, size_t size, size_t nmemb, std::string* output ) {
        size_t totalSize = size * nmemb;
        output->append( ( char* )contents, totalSize );
        return totalSize;
    }

    size_t WriteToFile( void* ptr, size_t size, size_t nmemb, std::ofstream* stream ) {
        stream->write( static_cast< char* >( ptr ), size * nmemb );
        return size * nmemb;
    }

    std::string getLatestVersion( const std::string& url ) {
        CURL* curl;
        CURLcode res;
        std::string response;

        curl = curl_easy_init( );
        if ( curl ) 
        {
            curl_easy_setopt( curl, CURLOPT_URL, url.c_str( ) );
            curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, WriteCallback );
            curl_easy_setopt( curl, CURLOPT_WRITEDATA, &response );
            res = curl_easy_perform( curl );
            curl_easy_cleanup( curl );
        }

        return response;
    }

    bool DownloadAndReplaceFile( const std::string& url, const std::string& output_file_path ) {
        CURL* curl = curl_easy_init( );
        if ( !curl ) 
            return false;
        
        std::ofstream output_file( output_file_path, std::ios::binary );
        if ( !output_file.is_open( ) ) 
        {
            curl_easy_cleanup( curl );
            return false;
        }

        curl_easy_setopt( curl, CURLOPT_URL, url.c_str( ) );
        curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, WriteToFile );
        curl_easy_setopt( curl, CURLOPT_WRITEDATA, &output_file );
        curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L );

        CURLcode res = curl_easy_perform( curl );
        if ( res != CURLE_OK ) 
        {
            output_file.close( );
            curl_easy_cleanup( curl );
            return false;
        }

        output_file.close( );
        curl_easy_cleanup( curl );

        return true;
    }

};


