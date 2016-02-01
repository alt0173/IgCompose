/*
 *	File:   mgf.cpp
 *	Author: Lukah Dykes
 */


/*	IgCompose v.2.5.0
 *
 *
 *
 */

#include <cstdlib> // provides - size_t, NULL
#include <iostream> // provides - std::cin, std::cout, std::ofstream::open
#include <string> // provides - std::string
#include <iomanip> // provides - std::setw
#include "fpf_spectralsum_h.h"


const std::string version = "v.2.5.0";

int main() {

    static int DEBUG_MODE = 0;
    static size_t UNION_MEM_ALLOC = 200000;

    typedef fpf_spectralsum::size_type size_type;

    std::cout << "-- IgCompose " << version << " --\n\n\n";

    std::cout << "Input file?\n\n";
    std::string s_input_file;
    std::cin >> s_input_file;
    std::ifstream fin_input(s_input_file);

    std::cout << "\n\ndebug mode for fpf_spectralsum_h.h?\n\n";
    std::cin >> fpf_spectralsum::fpf_spectralsum_DEBUG_MODE;

    fpf_spectralsum::mgf init_mgf = fpf_spectralsum::mgf();
    init_mgf.input_parse(fin_input, init_mgf);
    if (DEBUG_MODE >= 2) {
        init_mgf.debug_parse();
    }

    fpf_spectralsum::mgf union_parse = fpf_spectralsum::mgf(UNION_MEM_ALLOC);
    init_mgf.mgf_scan_ion_sum(init_mgf);
    init_mgf.mgf_scan_sum(init_mgf, union_parse);
    if (DEBUG_MODE >= 2) {
        union_parse.debug_parse();
    }
    if (DEBUG_MODE >= 1) {
        union_parse.cout_mgf();
    }
    union_parse.mgf_scan_ion_reset();
    init_mgf.~mgf();


    fpf_spectralsum::mgf union_parse2 = fpf_spectralsum::mgf(UNION_MEM_ALLOC);
    union_parse.mgf_scan_ion_sum(union_parse);
    union_parse.mgf_scan_sum(union_parse, union_parse2);
    if (DEBUG_MODE >= 2) {
        union_parse2.debug_parse();
    }
    if (DEBUG_MODE >= 1) {
        union_parse2.cout_mgf();
    }
    union_parse2.mgf_scan_ion_reset();
    union_parse.~mgf();

    fpf_spectralsum::mgf union_parse3 = fpf_spectralsum::mgf(UNION_MEM_ALLOC);
    union_parse2.mgf_scan_ion_sum(union_parse2);
    union_parse2.mgf_scan_sum(union_parse2, union_parse3);
    if (DEBUG_MODE >= 2) {
        union_parse3.debug_parse();
    }
    if (DEBUG_MODE >= 1) {
        union_parse3.cout_mgf();
    }
    union_parse3.mgf_scan_ion_reset();
    union_parse2.~mgf();

    fpf_spectralsum::mgf union_parse4 = fpf_spectralsum::mgf(UNION_MEM_ALLOC);
    union_parse3.mgf_scan_ion_sum(union_parse3);
    union_parse3.mgf_scan_sum(union_parse3, union_parse4);
    if (DEBUG_MODE >= 2) {
        union_parse4.debug_parse();
    }
    if (DEBUG_MODE >= 1) {
        union_parse4.cout_mgf();
    }
    union_parse4.mgf_scan_ion_reset();
    union_parse3.~mgf();

    fpf_spectralsum::mgf union_parse5 = fpf_spectralsum::mgf(UNION_MEM_ALLOC);
    union_parse4.mgf_scan_ion_sum(union_parse4);
    union_parse4.mgf_scan_sum(union_parse4, union_parse5);
    if (DEBUG_MODE >= 2) {
        union_parse5.debug_parse();
    }
    if (DEBUG_MODE >= 1) {
        union_parse5.cout_mgf();
    }
    union_parse5.mgf_scan_ion_reset();
    union_parse4.~mgf();

    fpf_spectralsum::mgf union_parse6 = fpf_spectralsum::mgf(UNION_MEM_ALLOC);
    union_parse5.mgf_scan_ion_sum(union_parse5);
    union_parse5.mgf_scan_sum(union_parse5, union_parse6);
    if (DEBUG_MODE >= 2) {
        union_parse6.debug_parse();
    }
    if (DEBUG_MODE >= 1) {
        union_parse6.cout_mgf();
    }
    union_parse6.mgf_scan_ion_reset();
    union_parse5.~mgf();

    fpf_spectralsum::mgf union_parse7 = fpf_spectralsum::mgf(UNION_MEM_ALLOC);
    union_parse6.mgf_scan_ion_sum(union_parse6);
    union_parse6.mgf_scan_sum(union_parse6, union_parse7);
    if (DEBUG_MODE >= 2) {
        union_parse7.debug_parse();
    }
    if (DEBUG_MODE >= 1) {
        union_parse7.cout_mgf();
    }
    union_parse7.mgf_scan_ion_reset();
    union_parse6.~mgf();

    fpf_spectralsum::mgf union_parse8 = fpf_spectralsum::mgf(UNION_MEM_ALLOC);
    union_parse7.mgf_scan_ion_sum(union_parse7);
    union_parse7.mgf_scan_sum(union_parse7, union_parse8);
    if (DEBUG_MODE >= 2) {
        union_parse8.debug_parse();
    }
    if (DEBUG_MODE >= 1) {
        union_parse8.cout_mgf();
    }
    union_parse8.mgf_scan_ion_reset();
    union_parse7.~mgf();

    fpf_spectralsum::mgf union_parse9 = fpf_spectralsum::mgf(UNION_MEM_ALLOC);
    union_parse8.mgf_scan_ion_sum(union_parse8);
    union_parse8.mgf_scan_sum(union_parse8, union_parse9);
    if (DEBUG_MODE >= 2) {
        union_parse9.debug_parse();
    }
    if (DEBUG_MODE >= 1) {
        union_parse9.cout_mgf();
    }
    union_parse9.mgf_scan_ion_reset();
    union_parse8.~mgf();

    fpf_spectralsum::mgf union_parse10 = fpf_spectralsum::mgf(UNION_MEM_ALLOC);
    union_parse9.mgf_scan_ion_sum(union_parse9);
    union_parse9.mgf_scan_sum(union_parse9, union_parse10);
    if (DEBUG_MODE >= 2) {
        union_parse10.debug_parse();
    }
    if (DEBUG_MODE >= 1) {
        union_parse10.cout_mgf();
    }
    //union_parse10.mgf_scan_ion_reset();

    std::string s_output_file = "output.mgf";
    std::ofstream output_fout;
    output_fout.open(s_output_file);
    union_parse10.fout_mgf(output_fout);

    std::string pong;
    std::cout << "\n\n - \n - \n - ";
    std::cin >> pong;

    return 0;
}
