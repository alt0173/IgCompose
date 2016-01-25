/*
 *	File:   main.cpp
 *	Author: Lukah Dykes
 */


 /*	IgCompose v.0.1.5
  *
  *
  *
  */

#include <iostream> // provides - std::cin, std::cout, std::ofstream::open
#include <string> // provides - std::string
#include "fpf_spectralsum_h.h"


const std::string version = "v.0.1.5";

int main() {

	static int DEBUG_MODE = 0;

	std::cout << "-- IgCompose " << version << " --\n\n\n";

	std::cout << "Input file?\n\n";
	std::string s_input_file;
	std::cin >> s_input_file;
	std::ifstream fin_input(s_input_file);

	fpf_spectralsum::parse main_parse = fpf_spectralsum::parse();
	main_parse.input_parse(fin_input, main_parse);
	if (DEBUG_MODE >= 2) {
		main_parse.debug_parse();
	}

	fpf_spectralsum::parse union_parse;
	main_parse.read_parse_union(main_parse, union_parse);
	if (DEBUG_MODE >= 2) {
		union_parse.debug_parse();
	}
	if (DEBUG_MODE >= 1) {
		union_parse.cout_mgf();
	}

	std::string s_output_file = "output.mgf";
	std::ofstream output_fout;
	output_fout.open(s_output_file);
	union_parse.fout_mgf(output_fout);

	std::string pong;
	std::cout << "\n\n\nping..\n\n";
	std::cin >> pong;

	return 0;
}

//	the struggle is real ->
//
//	ion_union->set_fragment_ion_mz((i->return_data()->return_fragment_ion_mz());
