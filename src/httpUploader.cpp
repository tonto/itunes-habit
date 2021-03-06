#include "httpUploader.hpp"

#include <iostream>

using namespace std;

Uploader::Uploader()
{
    cout << __FUNCTION__ << "\n";

    curl = curl_easy_init();
    if(!curl)
    {
        cout << "Curl initialization failure";
    }
}

Uploader::~Uploader()
{
    cout << __FUNCTION__ << "\n";

    curl_easy_cleanup(curl);
}

void Uploader::setScriptBackend(const string & s)
{
    backend = s;
}

void Uploader::setFormElement(const string & s)
{
    element = s;
}

void Uploader::setFormElementName(const string & s)
{
    element_name = s;
}

int Uploader::uploadFile(const string & s)
{
    cout << __FUNCTION__ << "\n";

    curl_httppost * post = 0;
    curl_httppost * last = 0;

    curl_formadd(&post, &last,
        CURLFORM_COPYNAME, "file",
        CURLFORM_FILE, s.c_str(),
        CURLFORM_END);

    curl_formadd(&post, &last,
        CURLFORM_COPYNAME, element.c_str(),
        CURLFORM_COPYCONTENTS, element_name.c_str(),
        CURLFORM_END);

    curl_easy_setopt(curl, CURLOPT_URL, backend.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);

    if(curl_easy_perform(curl))
    {
        return 0;
    }

    curl_formfree(post);
    return 1;
}
