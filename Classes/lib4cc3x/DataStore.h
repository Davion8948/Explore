
#include <map>
#include <string>

namespace lib4cc3x
{
	class DataStore
	{
	public:

		typedef int KeyType;
		typedef int QueryKey;

		void setInt(QueryKey tag, int value);
		int getInt(QueryKey tag, int def = 0);

		void setFloat(QueryKey tag, float value);
		float getFloat(QueryKey tag, float def = 0);

		void setString(QueryKey tag, const std::string& value);
		std::string getString(QueryKey tag, const std::string& def = std::string());

		void setBool(QueryKey tag, bool value);
		bool getBool(QueryKey tag, bool def = false);

	private:
		std::map<KeyType, int> m_key2int;
		std::map<KeyType, float> m_key2float;
		std::map<KeyType, std::string> m_key2str;
		std::map<KeyType, bool> m_key2bool;
	};

}

