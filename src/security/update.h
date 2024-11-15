#pragma once

namespace security_update {
    const std::string currentVersion = "1.0.0";
    const std::string versionURL = "https://github.com/MHSPlay/something/blob/main/version.txt";

    std::atomic<bool> isCheckingUpdates = true;
    std::atomic<bool> updateAvailable = false;

    size_t WriteCallback( void* contents, size_t size, size_t nmemb, std::string* output ) {
        size_t totalSize = size * nmemb;
        output->append( ( char* )contents, totalSize );
        return totalSize;
    }

    //std::string getLatestVersion( const std::string& url ) {
    //    CURL* curl;
    //    CURLcode res;
    //    std::string response;

    //    curl = curl_easy_init( );
    //    if ( curl ) {
    //        curl_easy_setopt( curl, CURLOPT_URL, url.c_str( ) );
    //        curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, WriteCallback );
    //        curl_easy_setopt( curl, CURLOPT_WRITEDATA, &response );
    //        res = curl_easy_perform( curl );
    //        curl_easy_cleanup( curl );
    //    }

    //    return response;
    //}

};


