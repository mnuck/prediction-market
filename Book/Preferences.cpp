#include "Logger.h"
#include "Preferences.h"

#include <boost/property_tree/ini_parser.hpp>

Preferences::Preferences()
{
}

Preferences::~Preferences()
{
    
}

void Preferences::ReadINI(const std::string& filename)
{   
    try
    {
        boost::property_tree::ini_parser::read_ini
        (
            filename,
            static_cast
            <
                boost::property_tree::basic_ptree
                <
                    std::basic_string<char>, std::basic_string<char> 
                >&
            >(*this)
        );
        LOG(info) << "Loaded prefs from " << filename;
    }
    catch (const boost::property_tree::ini_parser::ini_parser_error& e)
    {
        LOG(error) << "Could not load prefs: " << e.what();
    }
}


Preferences prefs;
