#ifndef TRACK_H
#define TRACK_H

#include "table.h"

class Track : public Table {
	private:
		int id;
		int track_id;
		std::string title;
		int length;

	public:
		Track(int id_parameter, int track_id_parameter, const char *title_parameter);	
		std::string output();
		int get_length();
};

#endif
