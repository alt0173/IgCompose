// * * IgCompose v0.7.5.0 * *
// 
// Lukah Dykes - Flinders Proteomics Facility - 2016
// 
// * * * * *

#include <cstdlib> // provides - EXIT_SUCCESS, size_t, NULL
#include <iostream> // provides - std::cin, std::cout, std::ofstream::open
#include <string> // provides - std::string
#include <iomanip> // provides - std::setw
#include "fpf_spectralsum.h"

static int DEBUG_MODE = int();

int main() {
	typedef size_t size_type;

	fpf_spectralsum::display_interface();

	char c_main_input = '1';

	while (c_main_input != '0') {
		std::cout << "\n\nInput?\n\n> ";
		std::cin >> c_main_input;
		if (c_main_input == 'D') {
			std::cout << "\n\ndebug mode?\n\n> ";
			std::cin >> DEBUG_MODE;
			fpf_spectralsum::set_debug(DEBUG_MODE);
			fpf_scan::set_debug(DEBUG_MODE);
		}
		if (c_main_input != 0) {
			std::cin.clear();
			std::cin.ignore(256, '\n');
		}
	}

	std::cout << "\n\n# of input files?\n\n> ";
	int i_input_count;
	std::cin >> i_input_count;
	while (std::cin.fail()) {
		std::cout << "\n\n";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "# of input files?\n\n> ";
		std::cin >> i_input_count;
	}

	std::string* sa_input_file = new std::string[i_input_count];
	for (size_type i = 0; i < i_input_count; ++i) {
		std::cout << "\n\nInput file";
		if (i_input_count > 1) {
			std::cout << " " << (i + 1);
		}
		std::cout << "?\n\n> ";
		std::cin >> sa_input_file[i];
	}

	fpf_spectralsum::mgf* init_mgf = new fpf_spectralsum::mgf();
	for (size_type i = 0; i < i_input_count; ++i) {
		std::ifstream fin_input(sa_input_file[i]);
		init_mgf->input_parse(fin_input, init_mgf);
	}

	init_mgf->mgf_scan_ion_sum(init_mgf);
	init_mgf->mgf_scan_sum(init_mgf);

	std::string s_output_file = "output.mgf";
	std::ofstream output_fout;
	output_fout.open(s_output_file);
	init_mgf->fout_mgf(output_fout, init_mgf);

	std::string pong;
	std::cout << "\n\n - \n - \n - ";
	std::cin >> pong;
	std::cout << "\n\n\nCheck count? - ";
	std::cout << "\n\ninput files - " << i_input_count;
	std::cout << "\nprecursor ion mass window - " << (fpf_scan::CONDITION_PION_MASS * 2);
	std::cout << "\nprecursor ion rt window - " << (fpf_scan::CONDITION_PION_RT * 2);
	std::cout << "\nfragment ion maxima peak similarity - " << (fpf_fion::st_CONDITION_FION_SUP) << " of " << fpf_fion::st_CONDITION_COUNT_FION_SUP;
	std::cout << "\nfragment ion mz window - " << (fpf_fion::vt_CONDITION_FION_MZ * 2);
	std::cout << "\nnoise floor - " << fpf_spectralsum::FILTER_FION_INTENSITY;
	std::cout << "\n\n\nEnter any key to exit...\n\n> ";
	std::cin >> pong;

	return EXIT_SUCCESS;
}
