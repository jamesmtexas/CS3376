#ifndef TABLE_H
#define TABLE_H

#include <string>

class Table {
	public:
		virtual std::string output();
		virtual int get_length();
};

#endif
