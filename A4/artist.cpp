#include <sstream>
#include <iostream>
#include <string>
#include "artist.h"

Artist::Artist(int id_parameter, const char *name_parameter) {
	id = id_parameter;
	name = name_parameter;
}

std::string Artist::output() {
	std::string resultant_string;
	resultant_string += "\nID: " + std::to_string(id); 
	resultant_string += "\nName: " + name; 
	length = resultant_string.length();
	return resultant_string;
}

int Artist::get_length() {
	return length;
}
