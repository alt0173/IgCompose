/*
 * File:   main.cpp
 * Author: Lukah Dykes
 */


/* IgCompose v.0.0.7
 *
 *
 *
 */

#include <iostream> // provides - std::cin, std::cout
#include <string> // provides - std::string
#include "fpf_node_h.h"
#include "fpf_spectralsum_h.h"

const std::string version = "v.0.0.7";

int main() {

    std::cout << "-- IgCompose " << version << " --\n\n\n";
    std::cout << "Input file?\n\n";

    std::string input_file;
    std::cin >> input_file;
    std::ifstream fin_input(input_file);

    fpf_spectralsum::parse main_parse = fpf_spectralsum::parse();
    main_parse.input_parse(fin_input, main_parse);
    main_parse.read_parse();

    fpf_spectralsum::parse union_parse = main_parse.read_parse_union(main_parse);
    union_parse.read_parse();




    std::string pong;
    std::cout << "\n\nping..\n\n";
    std::cin >> pong;

    return 0;
}

// namespace scan_class defines object elements for fpf_scan_h 

namespace fpf_spectralsum {

    // TYPEDEFS and MEMBER CONSTANTS

    const parse::size_type parse::PARSE_DEFAULT_ALLOCATION;

    // CONSTANT MEMBER FUNCTIONS

    void parse::read_parse() const {
        for (unsigned i = 0; i < return_used(); ++i) {
            std::cout << "\n\n" << i;
            std::cout << "  " << nt_scan[i].return_precursor_rt();
            std::cout << "  " << nt_scan[i].return_precursor_mass();
            std::cout << "\n\npong!\n\n";
            nt_scan[i].return_head_ptr()->cout_all_data(nt_scan[i].return_head_ptr());
        }
        if (return_used() == 0) {
            std::cout << "\n\nNo members!";
        }
    };
}

