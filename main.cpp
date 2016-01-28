/*
 *	File:   main.cpp
 *	Author: Lukah Dykes
 */


/*	IgCompose v.1.7.0
 *
 *
 *
 */

#include <cstdlib> // provides - size_t, NULL
#include <iostream> // provides - std::cin, std::cout, std::ofstream::open
#include <string> // provides - std::string
#include <iomanip> // provides - std::setw
#include "fpf_spectralsum_h.h"


const std::string version = "v.1.7.0";

int main() {

    static int DEBUG_MODE = 0;
    static size_t UNION_MEM_ALLOC = 700000;

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

    fpf_spectralsum::parse union_parse = fpf_spectralsum::parse(UNION_MEM_ALLOC);
    main_parse.read_parse_union(main_parse, union_parse);
    if (DEBUG_MODE >= 2) {
        union_parse.debug_parse();
    }
    if (DEBUG_MODE >= 1) {
        union_parse.cout_mgf();
    }
    union_parse.main_reset();

    fpf_spectralsum::parse union_parse2 = fpf_spectralsum::parse(UNION_MEM_ALLOC);
    union_parse.read_parse_union(union_parse, union_parse2);
    if (DEBUG_MODE >= 2) {
        union_parse2.debug_parse();
    }
    if (DEBUG_MODE >= 1) {
        union_parse2.cout_mgf();
    }
    union_parse2.main_reset();

    fpf_spectralsum::parse union_parse3 = fpf_spectralsum::parse(UNION_MEM_ALLOC);
    union_parse2.read_parse_union(union_parse2, union_parse3);
    if (DEBUG_MODE >= 2) {
        union_parse3.debug_parse();
    }
    if (DEBUG_MODE >= 1) {
        union_parse3.cout_mgf();
    }
    //union_parse3.main_reset();

    std::string s_output_file = "output.mgf";
    std::ofstream output_fout;
    output_fout.open(s_output_file);
    union_parse3.fout_mgf(output_fout);

    std::string pong;
    std::cout << "\n\n\nping..\n\n";
    std::cin >> pong;

    return 0;
}
