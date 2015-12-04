#ifndef ARTIST_H
#define ARTIST_H

#include "table.h"

class Artist : public Table {
	private:
		int id;
		std::string name;
		int length;

	public:
		Artist(int id_parameter, const char *name_parameter);	
		std::string output();
		int get_length();
};

#endif
