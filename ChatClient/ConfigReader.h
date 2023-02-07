#pragma once
#include<fstream>
#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>

using namespace std;

class ConfigReader
{
private:
    /* data */
    string file_name;
    ifstream read_file;
    unordered_map<string, string> dic; 
public:
    ConfigReader(string cfg_file);
    ~ConfigReader();
public:
    void readConfig();
    string getValue(const string& key);
    unordered_map<string, string> get_config_dic();
private:
    void Stringsplit(const string& str, const char split, vector<string>& res);
};

