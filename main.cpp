#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <json/json.h>

using std::string;

#define CHECK_JSON(obj, str, fun) (obj.isMember(str) && obj[str].fun())

template<typename T1, typename T2>
using HashMap = std::unordered_map<T1, T2>;
template<typename T>
using HashSet = std::unordered_set<T>;

typedef struct _PriceData {
	HashMap<string, string> routine_price_key2value;
	HashSet<string> routine_delete_price_key;
}PriceData;   

int ParseJson(const string &origin_data, PriceData * price_data)
{
	Json::Value data_json;
	Json::Reader reader;
	if (!reader.parse(origin_data, data_json)) 
	{
		std::cout << "Parse Faild" << std::endl;;
		return 0;
	}
	Json::Value my_data = data_json["msg"]["response"]["data"];
	if (!CHECK_JSON(my_data, "checkin", isString) || 
	    !CHECK_JSON(my_data, "checkout", isString) || 
	    !CHECK_JSON(my_data, "room_num", isInt) ||
	    !CHECK_JSON(my_data, "list", isArray))
		std::cout << "TYPE ERROR!" << std::endl;
	else
		std::cout << "TYPE OK!" << std::endl;
	
	std::cout << my_data["checkin"].asString() << std::endl;
	std::cout << my_data["checkout"].asString() << std::endl;
	std::cout << my_data["room_num"].asInt() << std::endl;

	Json::Value my_list = my_data["list"];
	int list_size = my_list.size();	
	for(int i = 0; i < list_size; i++)
	{
		Json::Value price = my_list[i]["price"];
		std::cout << price["tax"].asInt() + price["val"].asInt() << std::endl;
	}

	return 0;
}

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		std::cout << "Less of params!" << std::endl;
		return -1;
	}	
	std::cout << "Json test!" << std::endl;

	string callback_str;
	PriceData price_data;

	std::ifstream file(argv[2]);	
	file >> callback_str;

	std::cout << "callback_str.size() = " << callback_str.size() << std::endl;
	
	ParseJson(callback_str, &price_data);

	return 0;
}

