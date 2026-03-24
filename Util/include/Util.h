#pragma once
#include <vector>
#include <string>
namespace Util
{
	class Util
	{
		using indexes = std::vector<size_t>;
		using string = std::string;
		using substring = std::vector<string>;
	public:
		// 参数说明
        // str:待分割的字符串
        // delim:分隔符
		// 返回值说明
        // 返回一个索引列表（indexes），索引列表中的元素表示分隔符的位置
		static indexes IndexSplitString(const string& str, char delim);
		// 参数说明
        // str:待分割的字符串
        // delim:分隔符
        // 返回值说明
		// 返回一个子串列表（substring），子串列表中的元素表示分隔后的子串
		static substring SplitString(const string& str, char delim);
		// 参数说明
// result:返回值列表，用于返回所有的分隔符位置
// str:待分割的字符串
// delim:分隔符
		static void IndexSplitString(indexes& result, const string& str, char delim);
		// 参数说明
		// result:返回值列表，用于返回所有的子串
// str:待分割的字符串
// delim:分隔符

		static void SplitString(substring& result,const string& str, char delim);
		// 参数说明
		// //////////////////////
		// str:待解释的字符串
		// indexes:分隔符位置列表(需要与str配对)
		// position:子串索引
		static std::string InterpretString(const string& str,const indexes& , size_t);
	};
	static const auto FalseFunction = []() {return false; };
}
