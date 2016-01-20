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


    std::string pong;
    std::cout << "\n\nping..\n\n";
    std::cin >> pong;

    return 0;
}

// namespace scan_class defines object elements for fpf_scan_h 

namespace fpf_spectralsum {

    // TYPEDEFS and MEMBER CONSTANTS

    scan::value_type CONDITION_PRECURSOR_MASS = 0.05;

    scan::value_type CONDITION_PRECURSOR_MZ = 0.05;

    scan::value_type CONDITION_PRECURSOR_RT = 120;

    scan::value_type CONDITION_FRAGMENT_ION = 95;

    const parse::size_type parse::PARSE_DEFAULT_ALLOCATION;

    // CONSTRUCTORS and DESTRUCTOR

    ions::ions(const value_type& init_vt_ion_mz, const value_type& init_vt_ion_intensity, ions_node_type init_nt_ions) {
        vt_ion_mz = init_vt_ion_mz;
        vt_ion_intensity = init_vt_ion_intensity;
        nt_ions = init_nt_ions;
    }

    ions::~ions() {
    }

    scan::scan() {
        vt_precursor_mass = value_type();
        vt_precursor_mz = value_type();
        vt_precursor_rt = value_type();
        st_precursor_charge = size_type();
        nt_head_ptr = NULL;
        nt_tail_ptr = NULL;
    }

    scan::~scan() {
    }

    parse::parse(size_type class_size) {
        nt_scan = new scan[class_size];
        st_capacity = class_size;
        st_used = size_type();
    }

    parse::~parse() {
        delete[] nt_scan;
    }

    // MODIFICATION MEMBER FUNCTIONS

    void ions::set_ion_mz(const value_type& parse_ion_mz) {
        vt_ion_mz = parse_ion_mz;
    };

    void ions::set_ion_intensity(const value_type& parse_ion_intensity) {
        vt_ion_intensity = parse_ion_intensity;
    };

    void ions::set_data(const value_type& parse_ion_mz, const value_type& parse_ion_intensity) {
        ions::set_ion_mz(parse_ion_mz);
        ions::set_ion_intensity(parse_ion_intensity);
    };
    
    void ions::set_ions(ions_node_type nt_link) {
        nt_ions = nt_link;
    }

    void ions::list_head_insert(const ions::value_type& set_vt_ion_mz, const ions::value_type& set_vt_ion_intensity, ions*& head_ptr) {
        head_ptr = new ions(set_vt_ion_mz, set_vt_ion_intensity, head_ptr);
    };

    void ions::list_tail_insert(const ions::value_type& set_vt_ion_mz, const ions::value_type& set_vt_ion_intensity, ions*& tail_ptr) {
        ions* prev_ptr;
        prev_ptr = new ions;
        prev_ptr->set_ion_mz(set_vt_ion_mz);
        tail_ptr->set_ions(prev_ptr);
        tail_ptr = prev_ptr;
    };

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
                nt_scan[st_used].scan_modify_precursor_rt(vt_inputstream);
                s_inputstream.clear();
            }
            if (s_inputstream == "PEPMASS=") {
                switch_inputstream = 3;
                s_inputstream.clear();
            }
            if ((switch_inputstream == 3) && (c_inputstream == '\n')) {
                std::istringstream(s_inputstream) >> ss_inputstream;
                parse::value_type vt_inputstream = ss_inputstream;
                nt_scan[st_used].scan_modify_precursor_mass(vt_inputstream);
                switch_inputstream = 4;
                s_inputstream.clear();
            }
            if ((switch_inputstream == 4) && (c_inputstream == '\n')) {
                std::istringstream(s_inputstream) >> ss_inputstream;
                parse::value_type vt_inputstream = ss_inputstream;
                nt_scan[st_used].return_head_ptr()->insert_tail(vt_inputstream, nt_scan[st_used].return_head_ptr(), nt_scan[st_used].return_tail_ptr());
                s_inputstream.clear();
            }
            if ((switch_inputstream == 4) && ((c_inputstream == '\n'))) {

            }
            if ((switch_inputstream == 4) && ((c_inputstream == 'E'))) {
                switch_inputstream = 0;
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

    void parse::read_parse() const {
        for (unsigned i = 0; i < return_used(); ++i) {
            std::cout << "\n\n" << i;
            std::cout << "  " << nt_scan[i].return_precursor_rt();
            std::cout << "  " << nt_scan[i].return_precursor_mass();
            std::cout << "\n\npong!\n\n";
            nt_scan[i].return_head_ptr()->cout_all_data(nt_scan[i].return_head_ptr());
            std::cout << " ! " << nt_scan[i].return_head_ptr()->return_data();
            //}
        }
    };
}

