/*
 * File:   main.cpp
 * Author: Lukah Dykes
 */


/* IgCompose v.0.0.1
 *
 *
 *
 */

#include <iostream> // provides - std::cin, std::cout
#include <string> // provides - std::string
#include "fpf_scan_h.h"

using namespace scan_class;

const std::string version = "v.0.0.1";

// namespace scan_class defines object elements for fpf_scan_h

namespace scan_class {
    // TYPEDEFS and MEMBER CONSTANTS
    scan::value_type CONDITION_PRECURSOR_MASS = 0.05;

    scan::value_type CONDITION_PRECURSOR_MZ = 0.05;

    scan::value_type CONDITION_PRECURSOR_RT = 120;

    scan::value_type CONDITION_FRAGMENT_ION = 95;

    const parse::size_type parse::PARSE_DEFAULT_ALLOCATION;

    // CONSTRUCTORS and DESTRUCTOR

    scan::scan() {
        vt_precursor_mass = 0;
        vt_precursor_charge = 0;
        vt_precursor_mz = 0;
        vt_precursor_rt = 0;
        nt_ions = NULL;
        b_union_created = false;
    }

    scan::~scan() {
    }

    parse::parse(size_type class_size) {
        ct_scan = new scan[class_size];
        st_capacity = class_size;
        st_used = 0;
    }

    parse::~parse() {
        delete[] ct_scan;
    }

    // MODIFICATION MEMBER FUNCTIONS

    void scan::scan_modify_precursor_mass(scan& scan_1, value_type parse_precursor_mass) {
        scan_1.vt_precursor_mass = parse_precursor_mass;
    };

    void scan::scan_modify_precursor_mz(scan& scan_1, value_type parse_precursor_mz) {
        scan_1.vt_precursor_mz = parse_precursor_mz;
    };

    void scan::scan_modify_precursor_rt(scan& scan_1, value_type parse_precursor_rt) {
        scan_1.vt_precursor_rt = parse_precursor_rt;
    };

    void scan::scan_modify_precursor_charge(scan& scan_1, size_type parse_precursor_charge) {
        scan_1.vt_precursor_charge = parse_precursor_charge;
    };

    void scan::scan_union_created(scan& scan_1) {
        scan_1.b_union_created = true;
    };

    void parse::input_parse(std::ifstream& fin, parse& parse_class) {
        char c_inputstream;
        std::string s_inputstream = "";
        int switch_inputstream = 0;
        int subswitch_inputstream = 0;
        value_type ss_inputstream;
        while (fin.std::istream::get(c_inputstream)) {
            if (c_inputstream != '\n') {
                s_inputstream += c_inputstream;
            }
            if (s_inputstream == "BEGIN IONS") {
                switch_inputstream = 1;
                s_inputstream.clear();
            }
            if (s_inputstream == "RTINSECONDS: ") {
                switch_inputstream = 2;
                subswitch_inputstream = 1;
                s_inputstream.clear();
            }
            if ((switch_inputstream == 2) && (subswitch_inputstream == 1) && (c_inputstream == '\n')) {
                std::istringstream(s_inputstream) >> ss_inputstream;
                //typecov to value_type??
                //ct_scan[st_used].scan_modify_precursor_mass(ss_inputstream);
                subswitch_inputstream = 0;
            }
            if (s_inputstream == "END IONS") {
                //++count;
            }
        }
    }

    // CONSTANT MEMBER FUNCTIONS

    const scan::value_type scan::precursor_mass(const scan& scan_1) const {
        return scan_1.vt_precursor_mass;
    };

    const scan::value_type scan::precursor_charge(const scan& scan_1) const {
        return scan_1.vt_precursor_mz;
    };

    const scan::value_type scan::precursor_mz(const scan& scan_1) const {
        return scan_1.vt_precursor_rt;
    };

    const scan::size_type scan::precursor_rt(const scan& scan_1) const {
        return scan_1.vt_precursor_charge;
    };

    const scan::node_type scan::ions(const scan& scan_1) const {
        return scan_1.nt_ions;
    };

    const bool scan::union_created(const scan& scan_1) const {
        return scan_1.b_union_created;
    };

    const scan* parse::scan_link(const parse& parse_1) const {
        return parse_1.ct_scan;
    };

    const parse::size_type parse::used(const parse& parse_1) const {
        return parse_1.st_used;
    };

    const parse::size_type parse::capacity(const parse& parse_1) const {
        return parse_1.st_capacity;
    };
}

int main() {

    std::cout << "-- IgCompose " << version << " --\n\n\n";
    std::cout << "Input file?\n\n";

    std::string input_file;
    std::cin >> input_file;
    std::ifstream fin_input(input_file);

    parse main_parse = parse();
    main_parse.input_parse(fin_input, main_parse);
    for (unsigned i = 0; i < main_parse.used(main_parse); ++i) {
        //if (main_parse->scan_link(main_parse).precursor_mass(main_parse.scan_link(main_parse)) < CONDITION_PRECURSOR_MASS) {
        //&& (main_parse.scan_link[i].precursor_mz < CONDITION_PRECURSOR_MZ)
        //&& (main_parse.scan_link[i].precursor_rt < CONDITION_PRECURSOR_RT)) 
        //std::cout << "test";
        //}
    }

    return 0;
}

