#include"ConfigReader.h"

ConfigReader::ConfigReader(string cfg_file)
{
    file_name = cfg_file;
}

ConfigReader::~ConfigReader()
{
    
}

void ConfigReader::readConfig()
{
    read_file.open(file_name, ios::in);
    // 注意：如果cmake创建了build，则当前路径是build
    if (!read_file.is_open()){
        cout << file_name << "文件打开失败！" << endl;
        return;
    }
    string str;
    while(getline(read_file, str)){
        vector<string> key_value;
        Stringsplit(str, '=', key_value);
        dic[key_value[0]] = key_value[1];
    }
    read_file.close();
}

void ConfigReader::Stringsplit(const string &str, const char split, vector<string> &res)
{
    if (str == "")		return;
	//在字符串末尾也加入分隔符，方便截取最后一段
	string strs = str + split;
	size_t pos = strs.find(split);
 
	// 若找不到内容则字符串搜索函数返回 npos
	while (pos != strs.npos)
	{
		string temp = strs.substr(0, pos);
		res.push_back(temp);
		//去掉已分割的字符串,在剩下的字符串中进行分割
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find(split);
	}
}

string ConfigReader::getValue(const string& key){
        if(dic.find(key) == dic.end()){
            cout << "error: 配置文件中没有对应的key-value" << endl;
            return "";
        }
        return dic[key];
}

unordered_map<string, string> ConfigReader::get_config_dic()
{

    return dic;
}
