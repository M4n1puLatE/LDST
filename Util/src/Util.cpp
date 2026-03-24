#include <Util.h>
#include <istream>
#include <sstream>
namespace Util { 
	Util::indexes Util::IndexSplitString(const string& str, char delim)
	{
		if(str.empty())
			return {};
		indexes positions;
		IndexSplitString(positions, str, delim);
		return positions;
	}
	Util::substring Util::SplitString(const string& str, char delim)
	{
		substring result;
		SplitString(result, str, delim);
		return result;
	}
	void Util::IndexSplitString(indexes& result, const string& str, char delim)
	{
		for (size_t i = 0; i < str.size(); ++i)
		{
			if (str[i] == delim)
				result.push_back(i);
		}
	}
	void Util::SplitString(substring& result, const string& str, char delim)
	{
		if (!str.empty())
		{
			string token;
			std::istringstream tokenStream(str);
			while (std::getline(tokenStream, token, delim))
			{
				result.push_back(token);
			}
		}
	}


	std::string Util::InterpretString(const string& str, const indexes& indexes, size_t position)
	{
		//如果候选分隔符位置列表不为空，且给定索引短于索引列表长度，则返回索引位置后第一个分隔符之前的子串
		if (!indexes.empty() && position <= indexes.size())
		{
			if (position == 0)
			{
				return str.substr(0,indexes[position]);
			}
			else
			{
				size_t begin = indexes[position-1];
				size_t end = position == indexes.size() 
				? str.size() 
				: indexes[position];
				return str.substr(begin+1, end - begin-1);
			}
		}
		return "";
	}
}