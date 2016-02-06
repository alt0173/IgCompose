/*
 *	File:   mgf.cpp
 *	Author: Lukah Dykes
 */


 /*	IgCompose v.6.4.0
  *
  *
  *
  */
 
#include <cstdlib> // provides - EXIT_SUCCESS, size_t, NULL
#include <iostream> // provides - std::cin, std::cout, std::ofstream::open
#include <string> // provides - std::string
#include <iomanip> // provides - std::setw
#include "fpf_spectralsum.h"


const std::string version = "v.6.4.0";

static int DEBUG_MODE = int();

int main() {

	std::cout << "-- IgCompose " << version << " --\n\n\n";

	std::cout << "Input file?\n\n";
	std::string s_input_file;
	std::cin >> s_input_file;
	std::ifstream fin_input(s_input_file);

	std::cout << "\n\nInput file?\n\n";
	std::string s_input_file_2;
	std::cin >> s_input_file_2;
	std::ifstream fin_input_2(s_input_file_2);

	std::cout << "\n\nInput file?\n\n";
	std::string s_input_file_3;
	std::cin >> s_input_file_3;
	std::ifstream fin_input_3(s_input_file_3);

	std::cout << "\n\nInput file?\n\n";
	std::string s_input_file_4;
	std::cin >> s_input_file_4;
	std::ifstream fin_input_4(s_input_file_4);

	std::cout << "\n\ndebug mode?\n\n";
	std::cin >> DEBUG_MODE;
	fpf_spectralsum::set_debug(DEBUG_MODE);
	fpf_scan::set_debug(DEBUG_MODE);

	fpf_spectralsum::mgf* init_mgf = new fpf_spectralsum::mgf();
	init_mgf->input_parse(fin_input, init_mgf);
	init_mgf->input_parse(fin_input_2, init_mgf);
	//init_mgf->input_parse(fin_input_3, init_mgf);
	//init_mgf->input_parse(fin_input_4, init_mgf);
	if (DEBUG_MODE == 4) {
		//init_mgf.debug_parse();
	}

	init_mgf->mgf_scan_ion_sum(init_mgf);
	init_mgf->mgf_scan_sum(init_mgf);
	if (DEBUG_MODE == 4) {
		//union_parse.debug_parse();
	}
	if (DEBUG_MODE == 5) {
		//union_parse.cout_mgf();
	}
	//union_parse.mgf_scan_ion_reset();

	std::string s_output_file = "output.mgf";
	std::ofstream output_fout;
	output_fout.open(s_output_file);
	init_mgf->fout_mgf(output_fout, init_mgf);

	std::string pong;
	std::cout << "\n\n - \n - \n - ";
	std::cin >> pong;

	return EXIT_SUCCESS;
}
