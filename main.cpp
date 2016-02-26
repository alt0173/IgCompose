// * * IgCompose v0.8.5.0 * *
// 
// Lukah Dykes - Flinders Proteomics Facility - 2016
// 
// * * * * *

// IgCompose is a utility program for mass spectrometry data of the mgf file
// type. The primary role of the program is to determine spectra that are
// suitable for combination into a single spectrum, a function referred to as
// spectral summing. The mgf file contains spectral data as a standardised
// character array. Data stored in the mgf file is the precursor ion mass,
// precursor ion retention time, and the associated fragment ion mass-to-charge
// ratios and intensities.
// 
// Multiple mgf files may be input. From these, the relevant data is assigned to
// data structures through a parsing function. To determine suitability for
// spectral summing, initially the precursor ion mass is compared among
// precursor ions. If this value is within a compile-time (default 0.05 Da) or
// run-time (user input) initialised range, the program next tests if the
// precursor retention time is within a compile-time (default 600 s) or
// run-time initialised range. Should these two tests return true, the
// (default 10) most intense fragment ions are compared between the two
// precursor ions. Should (default 4) of these be within a mass-to-charge ratio
// range (default 0.05 Da) the two scans are combined. Note that, from a
// physical perspective, the precursor ion and associated fragment ions are
// measured by first taking a time-of-flight detection of the precursor ion, and
// then taking one or several TOF detections. In this way, the mgf file type
// lists spectral data of the type A,B_1 A,B_2 A,B_3... where A is a precursor
// ion and B_n is the n-many retention times and TOF fragment ion scans.
// 
// The summing process combines two scans as follows -
// 
// 1. A new scan class is created.
// 2. The precursor ion mass of the new scan class is assigned the mean
//    precursor ion mass of the two compared scan classes, taking into
//    consideration prior summing.
// 3. The precursor ion retention time of the new scan class is assigned the
//    mean precursor ion retention time of the two compared scan classes, taking
//    into consideration prior summing.
// 4. The fragment ion doubly linked lists of the two compared scan classes are
//    combined into a new doubly linked list.
// 5. The fragment ions of the new list are compared. If two compared fragment
//    ions are within the spectral summing range, the mean mass-to-charge ratio
//    and summed detected intensity is determined and stored in a new fion
//    class.
// 
// 
// This process continues through the entirety of the created data structures.
// Those scan classes that do not undergo any spectral summing are subjected to
// fragment ion summing (as a correction and compression measure). Upon
// completion the modified data is output as a new mgf file.

#include <cstdlib> // provides - EXIT_SUCCESS, size_t
#include <iostream> // provides - std::cin, std::cout, std::ofstream::open
#include <string> // provides - std::string
#include "fpf_spectralsum.h"

int main() {

	typedef size_t size_type;

	fpf_spectralsum::display_introduction();
	fpf_spectralsum::display_interface();
	size_type st_input_count = fpf_spectralsum::input_file_count();

	std::string* sa_input_file = new std::string[st_input_count];
	fpf_spectralsum::mgf* init_mgf = new fpf_spectralsum::mgf();

	fpf_spectralsum::input_file_assign(st_input_count, sa_input_file);

	for (size_type i = 0; i < st_input_count; ++i) {
		std::ifstream fin_input(sa_input_file[i]);
		fpf_spectralsum::mgf_input_parse(fin_input, init_mgf);
	}

	fpf_spectralsum::mgf_scan_sum(init_mgf);
	fpf_spectralsum::mgf_scan_fion_sum(init_mgf);

	std::ofstream output_fout;
	output_fout.open(fpf_spectralsum::output_file_assign(st_input_count, sa_input_file));
	fpf_spectralsum::fout_mgf(output_fout, init_mgf);

	fpf_spectralsum::display_program_exit(st_input_count);

	return EXIT_SUCCESS;
}