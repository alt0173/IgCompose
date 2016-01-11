/* 
 * File:   main.cpp
 * Author: Lukah Dykes
 */


/* IgCompose v.0.0.1
 *
 *
 *
 */

#include <iostream> //provides - cin, cout
#include "fpf_scan_h.h"

using namespace scan_class;

const std::string version = "v.0.0.1";

// namespace scan_class defines object elements for fpf_scan_h

namespace scan_class {
    // TYPEDEFS and MEMBER CONSTANTS
    const scan::size_type scan::SCAN_DEFAULT_ALLOCATION;
    const parse::size_type parse::PARSE_DEFAULT_ALLOCATION;

    // CONSTRUCTORS and DESTRUCTOR

    scan::scan(size_type class_size) {
        vt_precursor_mass = 0;
        vt_precursor_charge = 0;
        vt_precursor_mz = 0;
        vt_precursor_rt = 0;
        nt_ions = NULL;
    }

    scan::~scan() {
    }

    parse::parse(size_type class_size) {
        ct_scan = new scan[class_size];
        st_capacity = class_size;
        st_used = 0;
    }

    parse::~parse() {
        delete [] ct_scan;
    }

    // MODIFICATION MEMBER FUNCTIONS

    void parse::input_parse(std::ifstream& fin, parse& parse_class) {
        char constructor_input;
        while (fin.std::istream::get(constructor_input)) {

        }
    }
}

int main() {

    std::cout << "-- IgCompose " << version << " --\n\n\n";
    std::cout << "Input file?\n\n";

    std::string input_file;
    std::cin >> input_file;
    std::ifstream fin_input(input_file);
   
    parse main_parse = parse();
    main_parse.input_parse(fin_input, main_parse);

    return 0;
}

