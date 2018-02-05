#pragma once  
  
#include <string>  
#include <map>  
#include <iostream>  
#include <fstream>  
#include <sstream>
#include "log.h"

using MAP_ITERATOR=std::map<std::string, std::string>::iterator;
using CONST_MAP_ITERATOR=std::map<std::string, std::string>::const_iterator;

class Config{
protected:
    std::string _delimiter;
    std::string _comment;
    std::map<std::string,std::string> _contents;
    template<class T>
    static std::string to_string(const T& t);
    template<class T>
    static T to_t(const std::string& s);
    static void trim(std::string& inout_s);

public:
    Config(std::string filename,std::string delimiter = "=",std::string comment = "#");
    Config();
    template<class T>
    T read(const std::string& in_key) const;
    template<class T>
    T read(const std::string& in_key, const T& in_value) const;
    template<class T>
    bool read_to(T& out_var, const std::string& in_key) const;
    template<class T>
    bool read_to(T& out_var, const std::string& in_key, const T& in_value) const;
    bool is_exist(std::string filename);
    void read_file(std::string filename,std::string delimiter = "=",std::string comment = "#");
    bool is_key_exist(const std::string& in_key) const;
    template<class T>
    void add(const std::string& in_key, const T& in_value);
    void remove(const std::string& in_key);
    std::string get_delimiter() const {
        return _delimiter;}  
    std::string get_comment() const {
        return _comment;}
    std::string set_delimiter(const std::string& in_s){
        std::string old = _delimiter;
        _delimiter = in_s;
        return old;}    
    std::string set_comment(const std::string& in_s){ 
        std::string old = _comment;
        _comment =  in_s;
        return old;}
    friend std::ostream& operator<<(std::ostream& os, const Config& cf);
    friend std::istream& operator>>(std::istream& is, Config& cf);
};

template<class T>  
std::string Config::to_string(const T& t)  
{
    std::ostringstream ost;
    ost << t;
    return ost.str();
}

template<class T>  
T Config::to_t(const std::string& s)  
{
    T t;
    std::istringstream ist(s);
    ist >> t;
    return t;
}

template<>  
inline std::string Config::to_t<std::string>(const std::string& s)  
{
    return s;
}

template<>  
inline bool Config::to_t<bool>(const std::string& s)  
{ 
    bool b = true;
    std::string sup = s;
    for(std::string::iterator p = sup.begin(); p != sup.end(); ++p){ 
        *p = toupper(*p);}
    if(sup==std::string("FALSE") || sup==std::string("F") ||  
        sup==std::string("NO") || sup==std::string("N") ||  
        sup==std::string("0") || sup==std::string("NONE")){
        b = false;}
    return b;
}

template<class T>  
T Config::read(const std::string& key) const  
{
    CONST_MAP_ITERATOR p = _contents.find(key);
    if(p == _contents.end()) THROW_SYSTEM_ERROR();
    return to_t<T>(p->second);
}

template<class T>  
T Config::read(const std::string& key, const T& value) const  
{
    CONST_MAP_ITERATOR p = _contents.find(key);
    if(p == _contents.end()) return value;
    return to_t<T>(p->second);
}

template<class T>  
bool Config::read_to(T& var, const std::string& key) const  
{
    CONST_MAP_ITERATOR p = _contents.find(key);
    bool found = (p != _contents.end());
    if(found) var = to_t<T>(p->second);
    return found;
}
  
  
template<class T>  
bool Config::read_to(T& var, const std::string& key, const T& value) const  
{
    CONST_MAP_ITERATOR p = _contents.find(key);
    bool found = (p != _contents.end());
    if(found)  
        var = to_t<T>(p->second);
    else  
        var = value;
    return found;
}

template<class T>  
void Config::add(const std::string& in_key, const T& value)  
{
    std::string v = to_string(value);
    std::string key=in_key;
    trim(key);
    trim(v);
    _contents[key] = v;
    return;
}