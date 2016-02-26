// * * fpf_spectralsum.h * *
// 
// Lukah Dykes - Flinders Proteomics Facility - 2016
// 
// * * * * *

// --- namespace fpf_spectralsum class mgf
// 
// namespace fpf_spectralsum contains object definitions for the mgf class. A
// mgf class declares private members to store pointers to the first and last
// element of a doubly linked link containing precursor ion data as fpf_scan
// scan classes. The scan class precursor ion data is precursor ion mass in
// daltons, retention time in seconds, and the list of associated fragment ion
// data as fpf_fion fion classes. An additional run-time variable stores a value
// of how many scan classes a scan class is composed of (initially 1). A fion
// class stores a fragment ion mass-to-charge ratio in daltons and intensity in
// detected counts. The fion class also stores a value representing fion class
// composition.
// 
// Initally, the function mgf_input_parse() reads user-inputted mgf files and
// stores data in scan and fion classes. Precursor ion summing is determined
// with the function mgf_scan_sum(). Fragment ion summing is also performed
// through mgf_scan_sum() as the subfunction fpf_scan scan_fion_sum(). Following
// precursor ion spectral summing, the function mgf_scan_fion_sum() calls the
// created data structures and performs fragment ion spectral summing through
// scan_fion_sum() for those scans that were not subject to any spectral
// summing. The modified data structures are outputted as a new mgf file through
// the function fout_mgf().

#ifndef FPF_SPECTRALSUM
#define	FPF_SPECTRALSUM
#include <cstdlib> // provides - size_t, NULL
#include <fstream> // provides - std::ifstream
#include <istream> // provides - std::istream::get
#include <sstream> // provides - std::istringstream, std::ostringstream
#include <string> // provides - std::string
#include <iostream> // provides - std::cin, std::cout
#include "fpf_node.h"
#include "fpf_scan.h"

namespace fpf_spectralsum {

	class mgf;
	// Forward declaration for class mgf.

	typedef double value_type;
	// Defines value_type as any standard C++ data type.

	typedef size_t size_type;
	// Defines size_type as a size_t type. Requires <cstdlib>.

	typedef fpf_node::node<fpf_scan::scan*>* scan_node_type;
	// Defines scan_node_type as a pointer to a doubly linked list templated as
	// a pointer to a scan class.

	typedef fpf_scan::scan* scan_data_type;
	// Defines scan_data_type as a pointer to a scan class.

	size_type fpf_spectralsum_DEBUG_MODE = size_type();
	// fpf_spectralsum_DEBUG_MODE is a size_type with a run-time initialised
	// value that determines the relevant debug mode to implement. This value
	// also sets fpf_scan_DEBUG_MODE. The default value is 0. Debug mode values
	// relevant to fpf_spectralsum are:
	// 0. Default value for fpf_spectralsum_DEBUG_MODE. The program will execute
	//    standard functionality.
	// 1. Creates debug information for outputted file. Values for
	//    count_mgf_scan_fout, return_scan_union_count(), and
	//    st_return_union_count() are explicitly included.
	// 2. Displays scan class spectral sum boolean tests on the console.
	//    Compared precursor ion masses, retention times and fragment ion maxima
	//    successful and unsuccessful comparisons are annotated.

	size_type st_count_mgf_scan = size_type();
	// st_count_mgf_scan is a size_type that stores the quantity of scan classes
	// that have been parsed from the input mgf file(s). The value of
	// st_count_mgf_scan is dynamically increased as the input mgf file(s) are
	// read through mgf_input_parse().

	size_type st_count_mgf_scan_summed = size_type();
	// st_count_mgf_scan_summed is a size_type that stores the quantity of scan
	// classes that have been spectral summed. The value of
	// st_count_mgf_scan_summed is dynamically increased as the scan classes are
	// read through mgf_scan_sum().

	value_type vt_FILTER_PION_RT = 0;
	// vt_FILTER_PION_RT is a value_type with a compile-time or run-time
	// initialised value that defines the mininum precursor ion retention time
	// for a parsed scan class to be included in the associated mgf class. For
	// example, a relevant minimum precursor ion retention time can restrict
	// included scan classes to only those that are known to be elutions of the
	// sample.

	value_type vt_FILTER_FION_INTENSITY = 10;
	// vt_FILTER_FION_INTENSITY is a value_type with a compile-time or run-time
	// initialised value that defines the mininum fragment ion intensity for a
	// parsed fion class to be included in the associated scan class.

	class mgf {
	public:

		mgf() {
			// mgf() defines the default constructor for the mgf class. It
			// initialises member values as ISO type defaults (NULL for pointer
			// types).
			nt_scan_head_ptr = scan_node_type();
			nt_scan_tail_ptr = scan_node_type();
		};

		~mgf() {
		};

		//
		//
		//
		//   * * MEMBER ACCESS FUNCTIONS * *
		//
		//
		//

		inline scan_node_type& nt_return_scan_head_ptr() {
			// nt_return_scan_head_ptr() returns nt_scan_head_ptr, a pointer to
			// the first fpf_scan::scan class in a doubly linked list as defined
			// in fpf_node. Collectively the nodes of the list represent the
			// detected precursor ions of the sample(s).
			return nt_scan_head_ptr;
		};

		inline scan_node_type& nt_return_scan_tail_ptr() {
			// nt_return_scan_tail_ptr() returns nt_scan_tail_ptr, a pointer to
			// the last fpf_scan::scan class in a doubly linked list as defined
			// in fpf_node. Collectively the nodes of the list represent the
			// detected precursor ions of the sample(s).
			return nt_scan_tail_ptr;
		};

	private:
		scan_node_type nt_scan_head_ptr;
		// nt_scan_head_ptr is an scan_node_type that stores a pointer to the
		// first fpf_scan::scan class in a doubly linked list as defined in
		// fpf_node. Collectively the nodes of the list represent the precursor
		// ions of the sample(s).

		scan_node_type nt_scan_tail_ptr;
		// nt_scan_tail_ptr is an scan_node_type that stores a pointer to the
		// last fpf_scan::scan class in a doubly linked list as defined in
		// fpf_node. Collectively the nodes of the list represent the precursor
		// ions of the sample(s).
	};

	//
	//
	//
	// * * NAMESPACE FUNCTIONS * *
	//
	//
	//

	inline void set_FILTER_FION_INTENSITY(value_type vt_set_FILTER_FION_INTENSITY) {
		// set_FILTER_FION_INTENSITY() assigns a value_type to
		// vt_FILTER_FION_INTENSITY.
		vt_FILTER_FION_INTENSITY = vt_set_FILTER_FION_INTENSITY;
	}

	inline void set_debug(size_type set_fpf_spectralsum_DEBUG_MODE) {
		// set_debug() assigns a size_type to fpf_spectralsum_DEBUG_MODE.
		fpf_spectralsum_DEBUG_MODE = set_fpf_spectralsum_DEBUG_MODE;
	}

	inline void display_interface_settings() {
		// display_interface_settings() displays to the console the initialised
		// values of various run-time parameters relating to parsing conditions
		// of the input file(s) and parametric conditions of spectral summing.
		const size_type st_indent_1 = 2;
		const size_type st_indent_2 = 4;
		std::string display_default = "Spectral summing parameters:";
		std::string display_menu_precursor_mass = "Precursor mass range - ";
		std::string display_menu_precursor_rt = "Precursor retention time range - ";
		std::string display_menu_fragment_ion_mz = "Fragment ion mass-to-charge ratio range - ";
		std::string display_menu_fragment_ion_sup_intensities = "Fragment ion intensity maxima count - ";
		std::string display_menu_fion_noise_floor = "Fragment ion noise floor - ";
		std::cout << "\n\n\n";
		for (size_type i = 0; i < st_indent_1; ++i) {
			std::cout << " ";
		}
		std::cout << display_default;
		std::cout << "\n\n";
		for (size_type i = 0; i < st_indent_2; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_precursor_mass << fpf_scan::vt_CONDITION_PION_MASS;
		std::cout << "\n\n";
		for (size_type i = 0; i < st_indent_2; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_precursor_rt << fpf_scan::vt_CONDITION_PION_RT;
		std::cout << "\n\n";
		for (size_type i = 0; i < st_indent_2; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_fragment_ion_mz << fpf_fion::vt_CONDITION_FION_MZ;
		std::cout << "\n\n";
		for (size_type i = 0; i < st_indent_2; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_fragment_ion_sup_intensities << fpf_fion::st_CONDITION_FION_SUP << " of " << fpf_fion::st_CONDITION_COUNT_FION_SUP;
		std::cout << "\n\n";
		for (size_type i = 0; i < st_indent_2; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_fion_noise_floor << vt_FILTER_FION_INTENSITY;
	}

	inline void display_main_menu() {
		// display_main_menu() displays to the console the main menu options.
		const size_type st_indent_1 = 2;
		const size_type st_indent_2 = 4;
		std::string display_menu_set_header = "Menu options:";
		std::string display_menu_set_continue = "0 - Continue to input file selection";
		std::string display_menu_set_parameters = "P - Modify parameters";
		std::string display_menu_set_debug = "D - Debug mode";
		std::cout << "\n\n\n";
		for (size_type i = 0; i < st_indent_1; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_set_header;
		std::cout << "\n\n";
		for (size_type i = 0; i < st_indent_2; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_set_parameters;
		std::cout << "\n\n";
		for (size_type i = 0; i < st_indent_2; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_set_debug;
		std::cout << "\n\n";
		for (size_type i = 0; i < st_indent_2; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_set_continue;
		std::cout << "\n\n";
	}

	inline void display_introduction() {
		// display_introduction() displays to the console the header and
		// introduction.
		const size_type display_width = 75;
		const size_type st_indent = 4;
		const std::string display_version = "v0.8.5.0";
		std::string display_title = "-- IgCompose " + display_version + " --";
		std::string display_fpf = "Flinders Proteomics Facility - 2016";
		std::string display_intro = " ";
		std::cout << "\n\n\n";
		for (size_type i = 0; i < ((display_width - display_title.length()) / 2); ++i) {
			std::cout << " ";
		}
		std::cout << display_title;
		std::cout << "\n\n";
		for (size_type i = 0; i < ((display_width - display_fpf.length()) / 2); ++i) {
			std::cout << " ";
		}
		std::cout << display_fpf;
		std::cout << "\n\n\n";
		for (size_type i = 0; i < st_indent; ++i) {
			std::cout << " ";
		}
		std::cout << display_intro;
		display_interface_settings();
		display_main_menu();
	}

	inline void display_interface_set_settings() {
		// display_interface_set_settings() displays to the console the run-time parameter modification options.
		const size_type display_width = 75;
		const size_type st_indent_1 = 2;
		const size_type st_indent_2 = 4;
		std::string display_menu_set_header = "Input to modify parameter:";
		std::string display_menu_set_precursor_mass = "M - Set precursor mass range";
		std::string display_menu_set_precursor_rt = "R - Set precursor retention time range";
		std::string display_menu_set_fragment_ion_mz = "Z - Set fragment ion mass-to-charge ratio range";
		std::string display_menu_set_fragment_ion_sup_intensities = "I - Set fragment ion intensity maxima count";
		std::string display_menu_set_fragment_ion_sup_count_intensities = "C - Set fragment ion intensity maxima comp [not available, please wait]";
		std::string display_menu_set_noise_floor = "N - Set fragment ion noise floor";
		std::string display_menu_return_main = "0 - Return to main menu";
		std::cout << "\n\n\n";
		for (size_type i = 0; i < st_indent_1; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_set_header;
		std::cout << "\n\n";
		for (size_type i = 0; i < st_indent_2; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_set_precursor_mass;
		std::cout << "\n\n";
		for (size_type i = 0; i < st_indent_2; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_set_precursor_rt;
		std::cout << "\n\n";
		for (size_type i = 0; i < st_indent_2; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_set_fragment_ion_mz;
		std::cout << "\n\n";
		for (size_type i = 0; i < st_indent_2; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_set_fragment_ion_sup_intensities;
		std::cout << "\n\n";
		for (size_type i = 0; i < st_indent_2; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_set_noise_floor;
		std::cout << "\n\n";
		for (size_type i = 0; i < st_indent_2; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_return_main;
		std::cout << "\n\n";
	}

	inline void display_interface() {
		// display_interface() displays to the console various prompts dependent on user-inputted values that guide the user
		// through the menus.
		char c_main_input = '1';
		while (c_main_input != '0') {
			std::cout << "\n\nInput?\n\n> ";
			std::cin >> c_main_input;
			if (c_main_input == 'P') {
				char c_settings_input = '1';
				display_interface_settings();
				display_interface_set_settings();
				while (c_settings_input != '0') {
					std::cout << "\n\nInput?\n\n> ";
					std::cin >> c_settings_input;
					if (c_settings_input == 'M') {
						fpf_scan::value_type new_CONDITION_PION_MASS;
						std::cout << "\n\nNew value for the precursor ion mass range?\n\n> ";
						std::cin >> new_CONDITION_PION_MASS;
						while (std::cin.fail()) {
							std::cout << "\n\n";
							std::cin.clear();
							std::cin.ignore(256, '\n');
							std::cout << "\n\nNew value for the precursor ion mass range?\n\n> ";
							std::cin >> new_CONDITION_PION_MASS;
						}
						std::cout << "\n";
						fpf_scan::set_CONDITION_PION_MASS(new_CONDITION_PION_MASS);
						display_interface_settings();
						display_interface_set_settings();
					}
					if (c_settings_input == 'R') {
						fpf_scan::value_type new_CONDITION_PION_RT;
						std::cout << "\n\nNew value for the precursor ion retention time range?\n\n> ";
						std::cin >> new_CONDITION_PION_RT;
						while (std::cin.fail()) {
							std::cout << "\n\n";
							std::cin.clear();
							std::cin.ignore(256, '\n');
							std::cout << "\n\nNew value for the precursor ion retention time range?\n\n> ";
							std::cin >> new_CONDITION_PION_RT;
						}
						std::cout << "\n";
						fpf_scan::set_CONDITION_PION_RT(new_CONDITION_PION_RT);
						display_interface_settings();
						display_interface_set_settings();
					}
					if (c_settings_input == 'Z') {
						fpf_scan::value_type new_FILTER_FION_MZ;
						std::cout << "\n\nNew value for the fragment ion mass-to-charge ratio range?\n\n> ";
						std::cin >> new_FILTER_FION_MZ;
						while (std::cin.fail()) {
							std::cout << "\n\n";
							std::cin.clear();
							std::cin.ignore(256, '\n');
							std::cout << "\n\nNew value for the fragment ion mass-to-charge ratio range?\n\n> ";
							std::cin >> new_FILTER_FION_MZ;
						}
						std::cout << "\n";
						fpf_fion::set_CONDITION_FION_MZ(new_FILTER_FION_MZ);
						display_interface_settings();
						display_interface_set_settings();
					}
					if (c_settings_input == 'I') {
						fpf_scan::size_type new_CONDITION_FION_SUP;
						std::cout << "\n\nNew value for the fragment ion maxima comparison count?\n\n> ";
						std::cin >> new_CONDITION_FION_SUP;
						while (std::cin.fail()) {
							std::cout << "\n\n";
							std::cin.clear();
							std::cin.ignore(256, '\n');
							std::cout << "\n\nNew value for the fragment ion maxima comparison count?\n\n> ";
							std::cin >> new_CONDITION_FION_SUP;
						}
						std::cout << "\n";
						fpf_fion::set_CONDITION_FION_SUP(new_CONDITION_FION_SUP);
						display_interface_settings();
						display_interface_set_settings();
					}
					
					if (c_settings_input == 'N') {
						fpf_scan::value_type new_FILTER_FION_INTENSITY;
						std::cout << "\n\nNew value for the fragment ion noise floor?\n\n> ";
						std::cin >> new_FILTER_FION_INTENSITY;
						while (std::cin.fail()) {
							std::cout << "\n\n";
							std::cin.clear();
							std::cin.ignore(256, '\n');
							std::cout << "\n\nNew value for the fragment ion noise floor?\n\n> ";
							std::cin >> new_FILTER_FION_INTENSITY;
						}
						std::cout << "\n";
						set_FILTER_FION_INTENSITY(new_FILTER_FION_INTENSITY);
						display_interface_settings();
						display_interface_set_settings();
					}
					if (c_settings_input != '0') {
						std::cin.clear();
						std::cin.ignore(256, '\n');
					}
					else {
						display_interface_settings();
						display_main_menu();
					}
				}
			}
			if (c_main_input == 'D') {
				std::cout << "\n\n 0 - Default value for the debug mode. The program will execute";
				std::cout << "\n     standard functionality.";
				std::cout << "\n\n 1 - Creates debug information for outputted file. Values for ";
				std::cout << "\n     return_scan_union_count(), and st_return_union_count() are";
				std::cout << "\n     explicitly included.";
				std::cout << "\n\n 2 - Displays scan class spectral sum boolean tests on the console.";
				std::cout << "\n     Compared precursor ion masses, retention times and fragment ion";
				std::cout << "\n     maxima successful and unsuccessful comparisons are annotated.";
				std::cout << "\n\n 3 - Displays fion class spectral sum boolean tests on the console.";
				std::cout << "\n     Compared fragment ion mass-to-charge ratios are shown, successful";
				std::cout << "\n     and unsuccessful comparisons are annotated, and the doubly linked";
				std::cout << "\n     lists of fion classes are displayed post-hoc.";
				std::cout << "\n\n\nDebug mode?\n\n> ";
				std::cin >> fpf_spectralsum_DEBUG_MODE;
				set_debug(fpf_spectralsum_DEBUG_MODE);
				fpf_scan::set_debug(fpf_spectralsum_DEBUG_MODE);
				display_interface_settings();
				display_main_menu();
			}
			if (c_main_input != 0) {
				std::cin.clear();
				std::cin.ignore(256, '\n');
			}
		}
	}

	inline size_type input_file_count() {
		// input_file_count() prompts the user to assign a run-time initialised
		// size_type that determines the quantity of input mgf files.
		std::cout << "\n\n# of input files?\n\n> ";
		int i_input_count;
		std::cin >> i_input_count;
		while (std::cin.fail()) {
			std::cout << "\n\n";
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cout << "# of input files?\n\n> ";
			std::cin >> i_input_count;
		}
		return (i_input_count);
	}

	inline void input_file_assign(size_type st_input_count, std::string sa_input_file[]) {
		// input_file_assign() prompts the user to assign run-time initialised
		// std::string(s) that determines the filenames of input mfg files. Such
		// files are parsed and assigned to data structures through
		// mgf_input_parse().
		for (size_type i = 0; i < st_input_count; ++i) {
			std::cout << "\n\nInput file";
			if (st_input_count > 1) {
				std::cout << " " << (i + 1);
			}
			std::cout << "?\n\n> ";
			std::cin >> sa_input_file[i];
		}
	}

	void mgf_input_parse(std::ifstream& fin, mgf*& c_mgf_ptr) {
		// mgf_input_parse() is a void type return function that reads an
		// input stream from a mgf file and stores read data into a data
		// structure. The data elements of interest are:
		// 
		// 1. Retention time in seconds 'RTINSECONDS='.
		// 2. Precursor ion mass in daltons 'PEPMASS='. 
		// 3. Fragment ion mass-to-charge ratio. 
		// 4. Fragment ion intensity in detected counts.
		char c_inputstream;
		std::string s_inputstream = "";
		int switch_inputstream = int();
		scan_data_type dt_scan_inputstream = new fpf_scan::scan();
		value_type vt_inputstream;
		value_type vt_fragment_ion_mz_inputstream;
		size_type st_inputstream;
		size_type st_fragment_ion_intensity_inputstream;
		value_type vt_precursor_mass_inputstream;
		value_type vt_precursor_rt_inputstream;
		fpf_scan::fion_data_type dt_ion_inputstream = new fpf_fion::fion();
		const size_type OUTPUT_INTERVAL = 100;
		std::cout << "\n\nParsing...\n";
		while (fin.std::istream::get(c_inputstream)) {
			if (c_inputstream != '\n') {
				s_inputstream += c_inputstream;
			}
			if (s_inputstream == "RTINSECONDS=") {
				switch_inputstream = 2;
				s_inputstream.clear();
			}
			if ((switch_inputstream == 2) && (c_inputstream == '\n')) {
				std::istringstream(s_inputstream) >> vt_inputstream;
				vt_precursor_rt_inputstream = vt_inputstream;
				// For Protein Pilot peak lists -
				//switch_inputstream = 4;
				// here.
				s_inputstream.clear();
			}
			if ((switch_inputstream == 4) && (c_inputstream == ' ')) {
				std::istringstream(s_inputstream) >> vt_inputstream;
				vt_fragment_ion_mz_inputstream = vt_inputstream;
				switch_inputstream = 5;
				c_inputstream = '0';
				s_inputstream.clear();
			}
			if (s_inputstream == "PEPMASS=") {
				switch_inputstream = 3;
				s_inputstream.clear();
			}
			if ((switch_inputstream == 3) && (c_inputstream == '\n')) {
				std::istringstream(s_inputstream) >> vt_inputstream;
				vt_precursor_mass_inputstream = vt_inputstream;

				switch_inputstream = 4;
				// ^ Although not here.
				s_inputstream.clear();
			}
			if ((switch_inputstream == 5) && ((c_inputstream == '\n') || (c_inputstream == ' '))) {
				std::istringstream(s_inputstream) >> st_inputstream;
				st_fragment_ion_intensity_inputstream = st_inputstream;
				if (st_fragment_ion_intensity_inputstream >= vt_FILTER_FION_INTENSITY) {
					dt_ion_inputstream->set_fragment_ion_mz(vt_fragment_ion_mz_inputstream);
					dt_ion_inputstream->set_fragment_ion_intensity(st_fragment_ion_intensity_inputstream);
					fpf_node::list_insert_tail<fpf_scan::fion_data_type>(dt_ion_inputstream, dt_scan_inputstream->nt_return_fion_head_ptr(), dt_scan_inputstream->nt_return_fion_tail_ptr());
					dt_ion_inputstream = new fpf_fion::fion();
				}
				switch_inputstream = 4;
				s_inputstream.clear();
			}
			if (s_inputstream == "END") {
				switch_inputstream = 0;
				if (vt_precursor_rt_inputstream >= vt_FILTER_PION_RT) {
					dt_scan_inputstream->set_pion_mass(vt_precursor_mass_inputstream);
					dt_scan_inputstream->set_pion_rt(vt_precursor_rt_inputstream);
					fpf_node::list_insert_tail<scan_data_type>(dt_scan_inputstream, c_mgf_ptr->nt_return_scan_head_ptr(), c_mgf_ptr->nt_return_scan_tail_ptr());
					++st_count_mgf_scan;
					dt_scan_inputstream = new fpf_scan::scan();
				}
				if ((st_count_mgf_scan > 0) && (st_count_mgf_scan % OUTPUT_INTERVAL == 0)) {
					std::cout << "\nscan - " << st_count_mgf_scan << "   retention time - " << ((c_mgf_ptr->nt_return_scan_tail_ptr()->dt_return_data()->vt_return_pion_rt()) / 60);
				}
			}
			if (c_inputstream == '\n') {
				s_inputstream.clear();
			}
		}
		if (st_count_mgf_scan % OUTPUT_INTERVAL != 0) {
			std::cout << "\nscan - " << st_count_mgf_scan << "   retention time - " << ((c_mgf_ptr->nt_return_scan_tail_ptr()->dt_return_data()->vt_return_pion_rt()) / 60);
		}
	};

	void mgf_scan_fion_sum(mgf*& c_mgf) {
		// mgf_scan_fion_sum() is a void type function that performs intra-scan
		// class summing of fion classes for all scan classes in a doubly linked
		// list of a mgf class that have not been combined (st_scan_union_count
		// == 1). The scan classes of an mgf class are iterated with
		// scan_ptr_itr, for which fpf_scan::scan_fion_sum() is called.
		size_type count_mgf_fion_summed = size_type();
		const size_type st_output_interval = 100;
		std::cout << "\n\n\nSumming fragment fion spectra...\n";
		for (scan_node_type scan_ptr_itr = c_mgf->nt_return_scan_head_ptr(); scan_ptr_itr != NULL; scan_ptr_itr = scan_ptr_itr->nt_return_up_node()) {
			if (scan_ptr_itr->dt_return_data()->return_scan_union_count() == 1) {
				size_type scan_union_sum_count = fpf_scan::scan_fion_sum(scan_ptr_itr->dt_return_data());
				++count_mgf_fion_summed;
				if (fpf_spectralsum_DEBUG_MODE == 0) {
					if ((count_mgf_fion_summed > 0) && (count_mgf_fion_summed % st_output_interval == 0)) {
						std::cout << "\nscan - " << count_mgf_fion_summed;
						if (fpf_spectralsum_DEBUG_MODE == 1) {
							std::cout << " " << scan_ptr_itr->dt_return_data()->vt_return_pion_rt() << " " << scan_ptr_itr->dt_return_data()->vt_return_pion_mass() << "  " << scan_union_sum_count;
						}
					}
					if ((count_mgf_fion_summed == st_count_mgf_scan) && !((count_mgf_fion_summed > 0) && (count_mgf_fion_summed % st_output_interval == 0))) {
						std::cout << "\nscan - " << count_mgf_fion_summed;
						if (fpf_spectralsum_DEBUG_MODE == 1) {
							std::cout << " " << scan_ptr_itr->dt_return_data()->vt_return_pion_rt() << " " << scan_ptr_itr->dt_return_data()->vt_return_pion_mass() << "  " << scan_union_sum_count;
						}
					}
				}
			}
		}
	};

	void mgf_scan_sum(mgf*& c_mgf) {
		// mgf_scan_sum() is a void type function that performs the primary role
		// of scan class summing. The declared iterators nt_scan_ptr_itr_1 and
		// nt_scan_ptr_itr_2 iterate through the doubly linked list of scan
		// classes of the mgf class pointed to by c_mgf. Two scan classes
		// pointed to by the iterators are compared and are determined suitable
		// for spectral summing if -
		// 
		// 1. The iterators are not pointing to the same scan class.
		// 2. The precursor ion masses, fpf_scan::vt_pion_mass, are within a
		//    delta-range of fpf_scan::vt_CONDITION_PION_MASS.
		// 3. The precursor retention times, fpf_scan::vt_pion_rt, are within a
		//    delta-range of fpf_scan::vt_CONDITION_PION_RT.
		// 4. fpf_ion::st_CONDITION_FION_SUP of the
		//    fpf_ion::st_CONDITION_COUNT_FION_SUP most intense fragment ions
		//    are within a mass-to-charge ratio range of
		//    fpf_ion::vt_CONDITION_FION_MZ.
		// 
		// Two scan classes meeting these conditions will be summed through the
		// following process -
		// 
		// 1. A new scan class is created.
		// 2. The mass-to-charge ratio of the new scan class precursor ion is
		//    determined with vt_return_mean_pion_mass().
		// 3. The retention time of the new scan class precursor ion is
		//    determined with vt_return_mean_pion_rt().
		// 4. The total quantity of scan classes that have been combined into
		//    the new scan class is determined with
		//    st_return_sum_scan_union_count().
		// 5. The new scan class is inserted after the second compared scan
		//    class, pointed to by nt_scan_ptr_itr_2.
		// 6. The two compared scan classes are removed
		// 
		// The summing process continues through c_mgf, such that all possible
		// scan class summation is completed.
		scan_node_type nt_hold_scan = scan_node_type();
		scan_node_type nt_hold_scan_head_ptr = c_mgf->nt_return_scan_head_ptr();
		scan_data_type dt_scan_union = new fpf_scan::scan();
		size_type count_scan = size_type();
		const size_type st_output_interval = 100;
		std::cout << "\n\n\nSumming scans...\n";
		for (scan_node_type nt_scan_ptr_itr_1 = c_mgf->nt_return_scan_head_ptr(); nt_scan_ptr_itr_1 != NULL; nt_scan_ptr_itr_1 = nt_scan_ptr_itr_1->nt_return_up_node()) {
			// nt_scan_ptr_itr_1 iterates through the scan classes of the doubly
			// linked list of the mgf class pointed to by c_mgf. It corresponds
			// to the first scan being compared.
			++count_scan;
			if ((count_scan > 0) && (count_scan % st_output_interval == 0)) {
				if (fpf_spectralsum_DEBUG_MODE == 0) {
					std::cout << "\nscan - " << count_scan << "   summed - " << st_count_mgf_scan_summed;
				}
			}
			for (scan_node_type nt_scan_ptr_itr_2 = c_mgf->nt_return_scan_head_ptr(); nt_scan_ptr_itr_2 != NULL; nt_scan_ptr_itr_2 = nt_scan_ptr_itr_2->nt_return_up_node()) {
				// nt_scan_ptr_itr_2 iterates through the scan classes of the
				// doubly linked list of the mgf class pointed to by c_mgf. It
				// corresponds to the second scan being compared.
				if ((nt_scan_ptr_itr_1 != nt_scan_ptr_itr_2)
					&& fpf_scan::union_pion_mass(nt_scan_ptr_itr_1->dt_return_data(), nt_scan_ptr_itr_2->dt_return_data())
					&& fpf_scan::union_pion_rt(nt_scan_ptr_itr_1->dt_return_data(), nt_scan_ptr_itr_2->dt_return_data())) {
					// Tests if the two compared scan classes are -
					//
					// 1. Not the same scan class.
					// 2. Within a mass delta-range defined by
					//    fpf_scan::vt_CONDITION_PION_MASS.
					// 3. Within a retention time delta-range defined by
					//    fpf_scan::vt_CONDITION_PION_RT.
					if (union_fion_sup_intensities(nt_scan_ptr_itr_1->dt_return_data(), nt_scan_ptr_itr_2->dt_return_data())) {
						++count_scan;
						++st_count_mgf_scan_summed;
						dt_scan_union->set_pion_mass(fpf_scan::vt_return_mean_pion_mass(nt_scan_ptr_itr_1->dt_return_data(), nt_scan_ptr_itr_2->dt_return_data()));
						dt_scan_union->set_pion_rt(fpf_scan::vt_return_mean_pion_rt(nt_scan_ptr_itr_1->dt_return_data(), nt_scan_ptr_itr_2->dt_return_data()));
						dt_scan_union->set_scan_union_count(fpf_scan::st_return_sum_scan_union_count(nt_scan_ptr_itr_1->dt_return_data(), nt_scan_ptr_itr_2->dt_return_data()));
						fpf_scan::set_scan_fion_union(dt_scan_union, nt_scan_ptr_itr_1->dt_return_data(), nt_scan_ptr_itr_2->dt_return_data());
						fpf_node::list_insert_up<scan_data_type>(dt_scan_union, nt_scan_ptr_itr_2, c_mgf->nt_return_scan_head_ptr(), c_mgf->nt_return_scan_tail_ptr());
						// Creates a new scan class with values determined by
						// vt_return_mean_fion_mz(),
						// st_return_sum_fion_intensity(), and
						// st_return_sum_fion_union_count().
						dt_scan_union = new fpf_scan::scan();
						if (fpf_spectralsum_DEBUG_MODE == 2) {
							// ! not correct count here
							std::cout << "\nMatch for scan " << count_scan << " with scan " << count_scan + st_count_mgf_scan_summed << "\n\n";
							std::cout << "   ! " << nt_scan_ptr_itr_1->dt_return_data()->vt_return_pion_rt() << " " << nt_scan_ptr_itr_1->dt_return_data()->vt_return_pion_mass();
							std::cout << "  " << nt_scan_ptr_itr_2->dt_return_data()->vt_return_pion_rt() << " " << nt_scan_ptr_itr_2->dt_return_data()->vt_return_pion_mass();
							std::cout << "   ! " << fpf_scan::vt_return_mean_pion_rt(nt_scan_ptr_itr_1->dt_return_data(), nt_scan_ptr_itr_2->dt_return_data());
							std::cout << "  " << fpf_scan::vt_return_mean_pion_mass(nt_scan_ptr_itr_1->dt_return_data(), nt_scan_ptr_itr_2->dt_return_data());
						}
						if ((count_scan > 0) && (count_scan % st_output_interval == 0)) {
							if (fpf_spectralsum_DEBUG_MODE == 0) {
								std::cout << "\nscan - " << count_scan << "   summed - " << st_count_mgf_scan_summed;
							}
						}
						if (nt_scan_ptr_itr_1 != nt_hold_scan_head_ptr) {
							// Removes the compared scan classes after creation
							// of the new scan class. The four permutative
							// algorithmic conditions are:
							// 
							// 1. nt_scan_ptr_itr_1 is the first scan class of
							//    the doubly linked list and nt_scan_ptr_itr_2
							//    subsequently follows.
							// 2. nt_scan_ptr_itr_1 is the first scan class of
							//    the doubly linked list and nt_scan_ptr_itr_2
							//    does not subsequently follow.
							// 3. nt_scan_ptr_itr_1 is not the first scan class
							//    of the doubly linked list and
							//    nt_scan_ptr_itr_2 subsequently follows.
							// 4. nt_scan_ptr_itr_1 is not the first scan class
							//    of the doubly linked list and
							//    nt_scan_ptr_itr_2 does not subsequently
							//    follow.
							// 
							// During, nt_scan_ptr_itr_1 is pointed to the scan
							// class following the first removed scan class,
							// while nt_scan_ptr_itr_2 is pointed to the first
							// scan class of the doubly linked list (or
							// alternatively, to nt_scan_ptr_itr_1, such that
							// the for loop directive nt_scan_ptr_itr_2 =
							// nt_scan_ptr_itr_2->nt_return_up_node() iterates
							// it to the subsequent scan class). The compared
							// scan classes are removed from memory.
							if (nt_scan_ptr_itr_1->nt_return_up_node() == nt_scan_ptr_itr_2) {
								if (fpf_spectralsum_DEBUG_MODE == 2) {
									std::cout << "   (nt_ion_itr != nt_hold_ion_head_ptr)  (nt_ion_itr->nt_return_up_node() == nt_ion_itr_2)\n";
								}
								nt_hold_scan = nt_scan_ptr_itr_1;
								nt_scan_ptr_itr_1 = nt_scan_ptr_itr_1->nt_return_up_node()->nt_return_up_node();
								fpf_node::list_remove<scan_data_type>(nt_hold_scan);
								nt_hold_scan = nt_scan_ptr_itr_2;
								fpf_node::list_remove<scan_data_type>(nt_hold_scan);
								nt_scan_ptr_itr_2 = c_mgf->nt_return_scan_head_ptr();
							}
							else {
								if (fpf_spectralsum_DEBUG_MODE == 2) {
									std::cout << "   (nt_ion_itr != nt_hold_ion_head_ptr)  !(nt_ion_itr->nt_return_up_node() == nt_ion_itr_2)\n";
								}
								nt_hold_scan = nt_scan_ptr_itr_1;
								nt_scan_ptr_itr_1 = nt_scan_ptr_itr_1->nt_return_up_node();
								fpf_node::list_remove<scan_data_type>(nt_hold_scan);
								nt_hold_scan = nt_scan_ptr_itr_2;
								fpf_node::list_remove<scan_data_type>(nt_hold_scan);
								nt_scan_ptr_itr_2 = c_mgf->nt_return_scan_head_ptr();
							}
						}
						else {
							if (nt_scan_ptr_itr_1->nt_return_up_node() == nt_scan_ptr_itr_2) {
								if (fpf_spectralsum_DEBUG_MODE == 2) {
									std::cout << "   !(nt_ion_itr != nt_hold_ion_head_ptr)  (nt_ion_itr->nt_return_up_node() == nt_ion_itr_2)\n";
								}
								nt_scan_ptr_itr_1 = nt_scan_ptr_itr_1->nt_return_up_node()->nt_return_up_node();
								fpf_node::list_remove_head<scan_data_type>(c_mgf->nt_return_scan_head_ptr());
								fpf_node::list_remove_head<scan_data_type>(c_mgf->nt_return_scan_head_ptr());
								nt_hold_scan_head_ptr = nt_scan_ptr_itr_1;
								nt_scan_ptr_itr_2 = c_mgf->nt_return_scan_head_ptr();
							}
							else {
								if (fpf_spectralsum_DEBUG_MODE == 2) {
									std::cout << "   !(nt_ion_itr != nt_hold_ion_head_ptr)  !(nt_ion_itr->nt_return_up_node() == nt_ion_itr_2)\n";
								}
								nt_scan_ptr_itr_1 = nt_scan_ptr_itr_1->nt_return_up_node();
								fpf_node::list_remove_head<scan_data_type>(c_mgf->nt_return_scan_head_ptr());
								nt_hold_scan_head_ptr = nt_scan_ptr_itr_1;
								nt_hold_scan = nt_scan_ptr_itr_2;
								fpf_node::list_remove<scan_data_type>(nt_hold_scan);
								nt_scan_ptr_itr_2 = c_mgf->nt_return_scan_head_ptr();
							}
						}
					}
					else {
						if (fpf_spectralsum_DEBUG_MODE == 2) {
							std::cout << "\nPartial match for scan " << count_scan << " with scan " << st_count_mgf_scan_summed << "\n\n";
							std::cout << "   ! " << nt_scan_ptr_itr_1->dt_return_data()->vt_return_pion_rt() << " " << nt_scan_ptr_itr_1->dt_return_data()->vt_return_pion_mass();
							std::cout << "  " << nt_scan_ptr_itr_2->dt_return_data()->vt_return_pion_rt() << " " << nt_scan_ptr_itr_2->dt_return_data()->vt_return_pion_mass();
							std::cout << "   ! " << fpf_scan::vt_return_mean_pion_rt(nt_scan_ptr_itr_1->dt_return_data(), nt_scan_ptr_itr_2->dt_return_data());
							std::cout << "  " << fpf_scan::vt_return_mean_pion_mass(nt_scan_ptr_itr_1->dt_return_data(), nt_scan_ptr_itr_2->dt_return_data()) << "\n";
						}
					}
				}
			}
			if (nt_scan_ptr_itr_1->nt_return_up_node() == NULL) {
				if (fpf_spectralsum_DEBUG_MODE == 0) {
					std::cout << "\nscan - " << count_scan << "   summed - " << st_count_mgf_scan_summed;
				}
			}
		}
	};

	inline std::string output_file_assign(size_type st_input_count, std::string sa_input_file[]) {
		// output_file_assign() dynamically creates an output file name as a
		// std::string composed of the input file(s) and various compile-time
		// and run-time determined parameters.
		std::string s_output_file;
		for (size_type i = 0; i < st_input_count; ++i) {
			s_output_file += sa_input_file[i];
			if ((i + 1) < st_input_count) {
				s_output_file += "-";
			}
		}
		std::ostringstream ss_CONDITION_PION_MASS;
		ss_CONDITION_PION_MASS << fpf_scan::vt_CONDITION_PION_MASS;
		std::string s_CONDITION_PION_MASS = ss_CONDITION_PION_MASS.str();
		s_output_file += "_pionmass-" + s_CONDITION_PION_MASS;
		std::ostringstream ss_CONDITION_PION_RT;
		ss_CONDITION_PION_RT << fpf_scan::vt_CONDITION_PION_RT;
		std::string s_CONDITION_PION_RT = ss_CONDITION_PION_RT.str();
		s_output_file += "_pionrt-" + s_CONDITION_PION_RT;
		std::ostringstream ss_CONDITION_FION_SUP;
		ss_CONDITION_FION_SUP << fpf_fion::st_CONDITION_FION_SUP;
		std::string s_CONDITION_FION_SUP = ss_CONDITION_FION_SUP.str();
		s_output_file += "_fionsup-" + s_CONDITION_FION_SUP;
		std::ostringstream ss_CONDITION_COUNT_FION_SUP;
		ss_CONDITION_COUNT_FION_SUP << fpf_fion::st_CONDITION_COUNT_FION_SUP;
		std::string s_CONDITION_COUNT_FION_SUP = ss_CONDITION_COUNT_FION_SUP.str();
		s_output_file += "-" + s_CONDITION_COUNT_FION_SUP;
		std::ostringstream ss_CONDITION_FION_MZ;
		ss_CONDITION_FION_MZ << fpf_fion::vt_CONDITION_FION_MZ;
		std::string s_CONDITION_FION_MZ = ss_CONDITION_FION_MZ.str();
		s_output_file += "_fionmz-" + s_CONDITION_FION_MZ;
		std::ostringstream ss_FILTER_FION_INTENSITY;
		ss_FILTER_FION_INTENSITY << fpf_spectralsum::vt_FILTER_FION_INTENSITY;
		std::string s_FILTER_FION_INTENSITY = ss_FILTER_FION_INTENSITY.str();
		s_output_file += "_fionnf-" + s_FILTER_FION_INTENSITY;
		std::ostringstream ss_count_mgf_scan;
		ss_count_mgf_scan << fpf_spectralsum::st_count_mgf_scan;
		std::string s_count_mgf_scan = ss_count_mgf_scan.str();
		s_output_file += "_scaninit-" + s_count_mgf_scan;
		std::ostringstream ss_count_mgf_scan_summed;
		ss_count_mgf_scan_summed << fpf_spectralsum::st_count_mgf_scan_summed;
		std::string s_count_mgf_scan_summed = ss_count_mgf_scan_summed.str();
		s_output_file += "_scansum-" + s_count_mgf_scan_summed;
		s_output_file += ".mgf";
		return (s_output_file);
	}

	void const cout_mgf(mgf*& c_mgf) {
		// cout_mgf() outputs the modified data structures to the console in the
		// standard mgf format.
		size_type count_mgf_scan_cout = 1;
		for (scan_node_type nt_scan_ptr_itr = c_mgf->nt_return_scan_head_ptr(); nt_scan_ptr_itr != NULL; nt_scan_ptr_itr = nt_scan_ptr_itr->nt_return_up_node()) {
			if (c_mgf->nt_return_scan_head_ptr() == NULL) {
				std::cout << "\n\nException: No scan data found. Refer to fpf_spectralsum::mgf_input_parse().";
				break;
			}
			if (count_mgf_scan_cout > 1) {
				std::cout << "\nBEGIN IONS";
			}
			else {
				std::cout << "BEGIN IONS";
			}
			//
			//std::cout << "\nTITLE=" << "NULL";
			std::cout << "\nRTINSECONDS=" << nt_scan_ptr_itr->dt_return_data()->vt_return_pion_rt();
			std::cout << "\nPEPMASS=" << nt_scan_ptr_itr->dt_return_data()->vt_return_pion_mass();
			for (fpf_scan::fion_node_type nt_ion_ptr = nt_scan_ptr_itr->dt_return_data()->nt_return_fion_head_ptr(); nt_ion_ptr != NULL; nt_ion_ptr = nt_ion_ptr->nt_return_up_node()) {
				std::cout << "\n" << nt_ion_ptr->dt_return_data()->vt_return_fion_mz() << "   " << nt_ion_ptr->dt_return_data()->return_fion_intensity() << "   " << nt_ion_ptr->dt_return_data()->st_return_union_count();
			}
			std::cout << "\nEND IONS";
			++count_mgf_scan_cout;
		}
		if (count_mgf_scan_cout == 1) {
			std::cout << "\n\nNo members!";
		}
	};

	void const fout_mgf(std::ofstream& fout, mgf*& c_mgf) {
		// fout_mgf() outputs the modified data structures to a new file of the
		// standard mgf format.
		size_type count_mgf_scan_fout = 1;
		std::cout << "\n\n\nOutputting...";
		for (scan_node_type nt_scan_ptr_itr = c_mgf->nt_return_scan_head_ptr(); nt_scan_ptr_itr != NULL; nt_scan_ptr_itr = nt_scan_ptr_itr->nt_return_up_node()) {
			if (nt_scan_ptr_itr->dt_return_data()->nt_return_fion_head_ptr() != NULL) {
				if (c_mgf->nt_return_scan_head_ptr() == NULL) {
					std::cout << "\n\nException: No scan data found. Refer to fpf_spectralsum::mgf_input_parse().";
					break;
				}
				if (count_mgf_scan_fout > 1) {
					fout << "\nBEGIN IONS";
				}
				else {
					fout << "BEGIN IONS";
				}
				//
				//fout << "\nTITLE=" << "NULL";
				fout << "\nRTINSECONDS=" << nt_scan_ptr_itr->dt_return_data()->vt_return_pion_rt();
				fout << "\nPEPMASS=" << nt_scan_ptr_itr->dt_return_data()->vt_return_pion_mass();
				if (fpf_spectralsum_DEBUG_MODE == 1) {
					fout << " # " << count_mgf_scan_fout;
					fout << "   ! nt_scan[i].return_scan_union_count() " << nt_scan_ptr_itr->dt_return_data()->return_scan_union_count();
				}
				for (fpf_scan::fion_node_type nt_ion_ptr_itr = nt_scan_ptr_itr->dt_return_data()->nt_return_fion_head_ptr(); nt_ion_ptr_itr != NULL; nt_ion_ptr_itr = nt_ion_ptr_itr->nt_return_up_node()) {
					fout << "\n" << nt_ion_ptr_itr->dt_return_data()->vt_return_fion_mz();
					fout << "  " << nt_ion_ptr_itr->dt_return_data()->return_fion_intensity();
					if (fpf_spectralsum_DEBUG_MODE == 1) {
						fout << "  ! dt_scan_inputstream->dt_return_data()->st_return_union_count() " << nt_ion_ptr_itr->dt_return_data()->st_return_union_count();
					}
				}
				fout << "\nEND IONS";
				++count_mgf_scan_fout;
			}
		}
		if (count_mgf_scan_fout == 1) {
			std::cout << "\n\nNo members!";
		}
	};

	inline void display_program_exit(size_type st_input_count) {
		// display_program_exit() displays summary information from program
		// execution to the console and prompts the user to enter a key to
		// terminate run-time.
		std::string pong;
		std::cout << "\n\n - \n - \n - ";
		std::cout << "\n\ninput files - " << st_input_count;
		std::cout << "\nscans - " << fpf_spectralsum::st_count_mgf_scan;
		std::cout << "\nsummed scans - " << fpf_spectralsum::st_count_mgf_scan_summed;
		std::cout << "\nprecursor ion mass window - " << fpf_scan::vt_CONDITION_PION_MASS;
		std::cout << "\nprecursor ion rt window - " << fpf_scan::vt_CONDITION_PION_RT;
		std::cout << "\nfragment ion maxima peak similarity - " << (fpf_fion::st_CONDITION_FION_SUP) << " of " << fpf_fion::st_CONDITION_COUNT_FION_SUP;
		std::cout << "\nfragment ion mz window - " << fpf_fion::vt_CONDITION_FION_MZ;
		std::cout << "\nnoise floor - " << fpf_spectralsum::vt_FILTER_FION_INTENSITY;
		std::cout << "\n\n\nEnter any key to exit...\n\n";
		std::cin >> pong;
	}
}

#endif