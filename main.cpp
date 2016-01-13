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
        vt_precursor_mz = 0;
        vt_precursor_rt = 0;
        st_precursor_charge = 0;
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
            if (s_inputstream == "RTINSECONDS=") {
                switch_inputstream = 2;
                s_inputstream.clear();
            }
            if ((switch_inputstream == 2) && (c_inputstream == '\n')) {
                std::istringstream(s_inputstream) >> ss_inputstream;
                parse::value_type vt_inputstream = ss_inputstream;
                ct_scan[st_used].scan_modify_precursor_rt(vt_inputstream);
                s_inputstream.clear();               
            }
            if (s_inputstream == "PEPMASS=") {
                switch_inputstream = 3;
                s_inputstream.clear();
            }
            if ((switch_inputstream == 3) && (c_inputstream == '\n')) {
                std::istringstream(s_inputstream) >> ss_inputstream;
                parse::value_type vt_inputstream = ss_inputstream;
                ct_scan[st_used].scan_modify_precursor_mass(vt_inputstream);
                switch_inputstream = 0;
                s_inputstream.clear();
                std::cout << "ping!";
                std::cout << ct_scan[st_used].precursor_rt();
            }
            if ((s_inputstream == "END IONS") && (c_inputstream != '\n')) {
                std::cout << "  " << st_used << "\n\n";
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

    const scan::node_type scan::ions() const {
        return nt_ions;
    };

    const bool scan::union_created() const {
        return b_union_created;
    };

    const scan* parse::scan_link() const {
        return ct_scan;
    };

    const parse::size_type parse::used() const {
        return st_used;
    };

    const parse::size_type parse::capacity() const {
        return st_capacity;
    };
    
    void parse::read_parse() const{
    for (unsigned i = 0; i < used(); ++i) {
        std::cout << i << "  ";
        std::cout << ct_scan[st_used].precursor_rt() << "\n\n";
        //if (main_parse->scan_link(main_parse).precursor_mass(main_parse.scan_link(main_parse)) < CONDITION_PRECURSOR_MASS) {
        //&& (main_parse.scan_link[i].precursor_mz < CONDITION_PRECURSOR_MZ)
        //&& (main_parse.scan_link[i].precursor_rt < CONDITION_PRECURSOR_RT)) 
        //std::cout << "test";
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

