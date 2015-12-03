#include <string>
#include "cd.h"

CD::CD(int id_parameter, const char *title_parameter, int artist_id_parameter, const char *catalogue_parameter) {
	id = id_parameter;
	title = title_parameter;
	artist_id = artist_id_parameter;
	catalogue = catalogue_parameter;
}

