#include <sstream>
#include <iostream>
#include <string>
#include "track.h"

Track::Track(int id_parameter, int track_id_parameter, const char *title_parameter) {
	id = id_parameter;
	track_id = track_id_parameter;
	title = title_parameter;
}

std::string Track::output() {
	std::string resultant_string;
	resultant_string += "\nID: " + std::to_string(static_cast<long long>(id)); 
	resultant_string += "\nTrack id: " + std::to_string(static_cast<long long>(track_id));
	resultant_string += "\nTitle: " + title; 
	length = resultant_string.length();
	return resultant_string;
}

int Track::get_length() {
	return length;
}
