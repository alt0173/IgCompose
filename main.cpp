/*
 *	File:   main.cpp
 *	Author: Lukah Dykes
 */


/*	IgCompose v.2.2.0
 *
 *
 *
 */

#include <cstdlib> // provides - size_t, NULL
#include <iostream> // provides - std::cin, std::cout, std::ofstream::open
#include <string> // provides - std::string
#include <iomanip> // provides - std::setw
#include "fpf_spectralsum_h.h"


const std::string version = "v.2.2.0";

int main() {

    static int DEBUG_MODE = 0;
    static size_t UNION_MEM_ALLOC = 700000;

	typedef fpf_spectralsum::size_type size_type;

    std::cout << "-- IgCompose " << version << " --\n\n\n";

    std::cout << "Input file?\n\n";
    std::string s_input_file;
    std::cin >> s_input_file;
    std::ifstream fin_input(s_input_file);

	std::cout << "\n\ndebug mode for fpf_spectralsum_h.h?\n\n";
	std::cin >> fpf_spectralsum::fpf_spectralsum_DEBUG_MODE;

    fpf_spectralsum::main main_parse = fpf_spectralsum::main();
    main_parse.input_parse(fin_input, main_parse);
    if (DEBUG_MODE >= 2) {
        main_parse.debug_parse();
    }

    fpf_spectralsum::main union_parse = fpf_spectralsum::main(UNION_MEM_ALLOC);
    main_parse.main_scan_sum(main_parse, union_parse);
    if (DEBUG_MODE >= 2) {
        union_parse.debug_parse();
    }
    if (DEBUG_MODE >= 1) {
        union_parse.cout_mgf();
    }
    //union_parse.main_reset();

    //fpf_spectralsum::main union_parse2 = fpf_spectralsum::main(UNION_MEM_ALLOC);
    //union_parse.main_scan_sum(union_parse, union_parse2);
    //if (DEBUG_MODE >= 2) {
    //    union_parse2.debug_parse();
    //}
    //if (DEBUG_MODE >= 1) {
    //    union_parse2.cout_mgf();
    //}
    //union_parse2.main_reset();

    //fpf_spectralsum::main union_parse3 = fpf_spectralsum::main(UNION_MEM_ALLOC);
    //union_parse2.main_scan_sum(union_parse2, union_parse3);
    //if (DEBUG_MODE >= 2) {
    //    union_parse3.debug_parse();
    //}
    //if (DEBUG_MODE >= 1) {
    //    union_parse3.cout_mgf();
    //}
    //union_parse3.main_reset();

    std::string s_output_file = "output.mgf";
    std::ofstream output_fout;
    output_fout.open(s_output_file);
    union_parse.fout_mgf(output_fout);

    std::string pong;
    std::cout << "\n\n\nping..\n\n";
    std::cin >> pong;

    return 0;
}
