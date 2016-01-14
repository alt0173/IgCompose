/*
 * File:   main.cpp
 * Author: Lukah Dykes
 */


/* IgCompose v.0.0.5
 *
 *
 *
 */

#include <iostream> // provides - std::cin, std::cout
#include <string> // provides - std::string
#include "fpf_spectralsum_h.h"

using namespace fpf_spectralsum;

const std::string version = "v.0.0.5";

// namespace scan_class defines object elements for fpf_scan_h

namespace fpf_spectralsum {

    // TYPEDEFS and MEMBER CONSTANTS

    scan::value_type CONDITION_PRECURSOR_MASS = 0.05;

    scan::value_type CONDITION_PRECURSOR_MZ = 0.05;

    scan::value_type CONDITION_PRECURSOR_RT = 120;

    scan::value_type CONDITION_FRAGMENT_ION = 95;

    const parse::size_type parse::PARSE_DEFAULT_ALLOCATION;

    // CONSTRUCTORS and DESTRUCTOR
    
    ions::ions(size_type class_size) {
        value_type vt_ion_mz[class_size];
        vt_ion_intensity = alue_type[class_size];
    }
    
    ions::~ions() {
    }

    scan::scan() {
        vt_precursor_mass = 0;
        vt_precursor_mz = 0;
        vt_precursor_rt = 0;
        st_precursor_charge = 0;
        nt_ions = NULL;
        b_union_created = false;
    }

    scan::~scan() {
    }

    parse::parse(size_type class_size) {
        nt_scan = new scan[class_size];
        st_capacity = class_size;
        st_used = 0;
    }

    parse::~parse() {
        delete[] nt_scan;
    }

    // MODIFICATION MEMBER FUNCTIONS

    void scan::scan_modify_precursor_mass(value_type parse_precursor_mass) {
        vt_precursor_mass = parse_precursor_mass;
    };

    void scan::scan_modify_precursor_mz(value_type parse_precursor_mz) {
        vt_precursor_mz = parse_precursor_mz;
    };

    void scan::scan_modify_precursor_rt(value_type parse_precursor_rt) {
        vt_precursor_rt = parse_precursor_rt;
    };

    void scan::scan_modify_precursor_charge(size_type parse_precursor_charge) {
        st_precursor_charge = parse_precursor_charge;
    };

    scan::ions_node_type scan::link_ions() {
        return nt_ions;
    }

    void scan::scan_union_created() {
        b_union_created = true;
    };

    void parse::input_parse(std::ifstream& fin, parse& parse_1) {
        char c_inputstream;
        std::string s_inputstream = "";
        int switch_inputstream = 0;
        value_type ss_inputstream;
        while (fin.std::istream::get(c_inputstream)) {
            if (c_inputstream != '\n') {
                s_inputstream += c_inputstream;
            }
            if (s_inputstream == "PEPMASS=") {
                switch_inputstream = 2;
                s_inputstream.clear();
            }
            if ((switch_inputstream == 2) && (c_inputstream == '\n')) {
                std::istringstream(s_inputstream) >> ss_inputstream;
                parse::value_type vt_inputstream = ss_inputstream;
                nt_scan[st_used].scan_modify_precursor_mass(vt_inputstream);
                switch_inputstream = 0;
                s_inputstream.clear();
            }
            if (s_inputstream == "RTINSECONDS=") {
                switch_inputstream = 3;
                s_inputstream.clear();
            }
            if ((switch_inputstream == 3) && (c_inputstream == '\n')) {
                std::istringstream(s_inputstream) >> ss_inputstream;
                parse::value_type vt_inputstream = ss_inputstream;
                nt_scan[st_used].scan_modify_precursor_rt(vt_inputstream);
                switch_inputstream = 4;
                s_inputstream.clear();
            }
            if (switch_inputstream == 4) {
                
                nt_scan[st_used].link_ions() = new ions;
            }
            if ((s_inputstream == "END IONS") && (c_inputstream != '\n')) {
                ++parse_1.st_used;
            }
            if (c_inputstream == '\n') {
                s_inputstream.clear();
            }
        }
    }

    // CONSTANT MEMBER FUNCTIONS

    const scan::value_type scan::precursor_mass() const {
        return vt_precursor_mass;
    };

    const scan::value_type scan::precursor_mz() const {
        return vt_precursor_mz;
    };

    const scan::value_type scan::precursor_rt() const {
        return vt_precursor_rt;
    };

    const scan::size_type scan::precursor_charge() const {
        return st_precursor_charge;
    };

    const bool scan::union_created() const {
        return b_union_created;
    };

    const parse::scan_node_type parse::scan_link() const {
        return nt_scan;
    };

    const parse::size_type parse::used() const {
        return st_used;
    };

    const parse::size_type parse::capacity() const {
        return st_capacity;
    };

    void parse::read_parse() const {
        for (unsigned i = 0; i < used(); ++i) {
            std::cout << "\n\n" << i;
            std::cout << "  " << nt_scan[i].precursor_rt();
            std::cout << "  " << nt_scan[i].precursor_mass();
            //}
        }
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
    main_parse.read_parse();


    std::string pong;
    std::cout << "\n\nping..\n\n";
    std::cin >> pong;

    return 0;
}

