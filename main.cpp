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
		if (c_main_input == 'P') {
			char c_settings_input = '1';
			fpf_spectralsum::display_interface_settings();
			fpf_spectralsum::display_interface_set_settings();
			while (c_settings_input != '0') {
				std::cout << "\n\nInput?\n\n> ";
				std::cin >> c_settings_input;
				if (c_settings_input == 'M') {
					fpf_scan::scan::value_type new_CONDITION_PION_MASS;
					std::cout << "\n\nNew value for precursor mass window?\n\n> ";
					std::cin >> new_CONDITION_PION_MASS;
					while (std::cin.fail()) {
						std::cout << "\n\n";
						std::cin.clear();
						std::cin.ignore(256, '\n');
						std::cout << "\n\nNew value for precursor mass window?\n\n> ";
						std::cin >> new_CONDITION_PION_MASS;
					}
					std::cout << "\n";
					fpf_scan::set_CONDITION_PION_MASS(new_CONDITION_PION_MASS);
					fpf_spectralsum::display_interface_settings();
					fpf_spectralsum::display_interface_set_settings();
				}
				if (c_settings_input == 'R') {
					fpf_scan::scan::value_type new_CONDITION_PION_RT;
					std::cout << "\n\nNew value for precursor retention time window?\n\n> ";
					std::cin >> new_CONDITION_PION_RT;
					while (std::cin.fail()) {
						std::cout << "\n\n";
						std::cin.clear();
						std::cin.ignore(256, '\n');
						std::cout << "\n\nNew value for precursor retention time window?\n\n> ";
						std::cin >> new_CONDITION_PION_RT;
					}
					std::cout << "\n";
					fpf_scan::set_CONDITION_PION_RT(new_CONDITION_PION_RT);
					fpf_spectralsum::display_interface_settings();
					fpf_spectralsum::display_interface_set_settings();
				}
				if (c_settings_input == 'N') {
					fpf_scan::scan::value_type new_FILTER_FION_INTENSITY;
					std::cout << "\n\nNew value for the fragment ion noise floor?\n\n> ";
					std::cin >> new_FILTER_FION_INTENSITY;
					while (std::cin.fail()) {
						std::cout << "\n\n";
						std::cin.clear();
						std::cin.ignore(256, '\n');
						std::cout << "\n\nNew value for the fragment ion noise floor?\n\n> ";
						std::cin >> new_FILTER_FION_INTENSITY;
					}
					std::cout << "\n";
					fpf_spectralsum::set_FILTER_FION_INTENSITY(new_FILTER_FION_INTENSITY);
					fpf_spectralsum::display_interface_settings();
					fpf_spectralsum::display_interface_set_settings();
				}
				if (c_settings_input != '0') {
					std::cin.clear();
					std::cin.ignore(256, '\n');
				}
				else {
					fpf_spectralsum::display_interface_settings();
					fpf_spectralsum::display_main_menu();
				}
			}
		}
		if (c_main_input == 'D') {
			std::cout << "\n\nDebug mode?\n\n> ";
			std::cin >> DEBUG_MODE;
			fpf_spectralsum::set_debug(DEBUG_MODE);
			fpf_scan::set_debug(DEBUG_MODE);
			fpf_spectralsum::display_interface_settings();
			fpf_spectralsum::display_interface_set_settings();
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
	std::cout << "\nprecursor ion mass window - " << fpf_scan::vt_CONDITION_PION_MASS;
	std::cout << "\nprecursor ion rt window - " << fpf_scan::vt_CONDITION_PION_RT;
	std::cout << "\nfragment ion maxima peak similarity - " << (fpf_fion::st_CONDITION_FION_SUP) << " of " << fpf_fion::st_CONDITION_COUNT_FION_SUP;
	std::cout << "\nfragment ion mz window - " << fpf_fion::vt_CONDITION_FION_MZ;
	std::cout << "\nnoise floor - " << fpf_spectralsum::FILTER_FION_INTENSITY;
	std::cout << "\n\n\nEnter any key to exit...\n\n> ";
	std::cin >> pong;

	return EXIT_SUCCESS;
}
