#ifndef CD_H
#define CD_H

#include <string>

class CD {
	private:
		int id;
		std::string title;
		int artist_id;
		std::string catalogue;

	public:
	CD(int id_parameter, const char *title_parameter, int artist_id_parameter, const char *catalogue_parameter);
};

#endif
