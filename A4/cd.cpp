#include <sstream>
#include <iostream>
#include <string>
#include "cd.h"

CD::CD(int id_parameter, const char *title_parameter, int artist_id_parameter, const char *catalogue_parameter) {
	id = id_parameter;
	title = title_parameter;
	artist_id = artist_id_parameter;
	catalogue = catalogue_parameter;
}

std::string CD::output() {
	std::string resultant_string;
	resultant_string += "\nID: " + std::to_string(id); 
	resultant_string += "\nTitle: " + title;
	resultant_string += "\nArtist id: " + std::to_string(artist_id);
	resultant_string += "\nCatalogue: " + catalogue; 
	length = resultant_string.length();
	return resultant_string;
}

int CD::get_length() {
	return length;
}
