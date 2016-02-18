// * * IgCompose v0.8.2.0 * *
// 
// Lukah Dykes - Flinders Proteomics Facility - 2016
// 
// * * * * *

#include <cstdlib> // provides - EXIT_SUCCESS, size_t, NULL
#include <iostream> // provides - std::cin, std::cout, std::ofstream::open
#include <string> // provides - std::string
#include <iomanip> // provides - std::setw
#include <sstream> // provides - std::ostringstream
#include "fpf_spectralsum.h"

int main() {

	typedef size_t size_type;

	fpf_spectralsum::display_introduction();
	fpf_spectralsum::display_interface();
	size_type st_input_count = fpf_spectralsum::input_file_count();

	std::string* sa_input_file = new std::string[st_input_count];
	fpf_spectralsum::mgf* init_mgf = new fpf_spectralsum::mgf();

	fpf_spectralsum::input_file_assign(st_input_count, sa_input_file);

	for (size_type i = 0; i < st_input_count; ++i) {
		std::ifstream fin_input(sa_input_file[i]);
		init_mgf->input_parse(fin_input, init_mgf);
	}

	init_mgf->mgf_scan_fion_sum(init_mgf);
	init_mgf->mgf_scan_sum(init_mgf);

	std::ofstream output_fout;
	output_fout.open(fpf_spectralsum::output_file_name_parameters(st_input_count, sa_input_file));
	init_mgf->fout_mgf(output_fout, init_mgf);

	fpf_spectralsum::display_program_exit(st_input_count);

	return EXIT_SUCCESS;
}
