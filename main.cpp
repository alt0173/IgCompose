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
	const scan::size_type scan::SCAN_DEFAULT_ALLOCATION;
	const parse::size_type parse::PARSE_DEFAULT_ALLOCATION;

	// CONSTRUCTORS and DESTRUCTOR
	scan::scan(size_type class_size) {
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
		scan_1.vt_precursor_charge  = parse_precursor_charge;
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
                                value_type vt_inputstream = ss_inputstream;
				parse_class.ct_scan[st_used].scan_modify_precursor_mass(parse_class.ct_scan[st_used], vt_inputstream);
				subswitch_inputstream = 0;
			}
			if (s_inputstream == "END IONS") {
				//++count;
			}
		}
	}

	// CONSTANT MEMBER FUNCTIONS
	const scan::value_type precursor_mass(const scan& scan_1) {
		return scan_1.vt_precursor_mass;
	};

	const scan::value_type precursor_charge(const scan& scan_1) {
	};

	const scan::value_type precursor_mz(const scan& scan_1) {
	};

	const scan::size_type precursor_rt(const scan& scan_1) {
	};

	const scan::node_type ions(const scan& scan_1) {
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

	return 0;
}

