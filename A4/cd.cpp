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
	resultant_string = "ID: " + id;
	resultant_string += "Title: " + title;
	resultant_string += "Artist id: " + artist_id;
	resultant_string += "Catalogue: " + catalogue; 
	return resultant_string;
}
