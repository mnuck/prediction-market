#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <string>

#include <boost/property_tree/ptree.hpp>

class Preferences : public boost::property_tree::ptree
{
public:
    Preferences();
    ~Preferences();
    
    void ReadINI(const std::string& filename);

    template <typename T>
    const T Get(const std::string& key, T defaultValue)
    {
        return get(key, defaultValue);
    }
};

extern Preferences prefs;

#endif // PREFERENCES_H
