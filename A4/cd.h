#ifndef CD_H
#define CD_H

#include <string>

#include "table.h"

class CD : public Table {
	private:
		int id;
		std::string title;
		int artist_id;
		std::string catalogue;
		int length;

	public:
	CD(int id_parameter, const char *title_parameter, int artist_id_parameter, const char *catalogue_parameter);
	std::string output();
	int get_length();
};

#endif
