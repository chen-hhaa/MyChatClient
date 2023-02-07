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
    // ע�⣺���cmake������build����ǰ·����build
    if (!read_file.is_open()){
        cout << file_name << "�ļ���ʧ�ܣ�" << endl;
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
	//���ַ���ĩβҲ����ָ����������ȡ���һ��
	string strs = str + split;
	size_t pos = strs.find(split);
 
	// ���Ҳ����������ַ��������������� npos
	while (pos != strs.npos)
	{
		string temp = strs.substr(0, pos);
		res.push_back(temp);
		//ȥ���ѷָ���ַ���,��ʣ�µ��ַ����н��зָ�
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find(split);
	}
}

string ConfigReader::getValue(const string& key){
        if(dic.find(key) == dic.end()){
            cout << "error: �����ļ���û�ж�Ӧ��key-value" << endl;
            return "";
        }
        return dic[key];
}

unordered_map<string, string> ConfigReader::get_config_dic()
{

    return dic;
}
