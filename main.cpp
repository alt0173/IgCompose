// * * IgCompose v0.8.5.0 * *
// 
// Lukah Dykes - Flinders Proteomics Facility - 2016
// 
// * * * * *

// IgCompose is a utility program for mass spectrometry data of the mgf file type. The primary role of the
// program is to determine spectra that are suitable for combination into a single spectrum, a function
// referred to as spectral summing. The mgf file contains spectral data as a standardised character array.
// Data stored in the mgf file is the precursor ion mass, precursor ion retention time, and the associated fragment ion
// mass-to-charge ratios and intensities.
//
// Multiple mgf files may be input. From these, the relevant data is assigned to data structures through a parsing function.
// To determine suitability for spectral summing, initially the precursor ion mass is compared among precursor ions. If this
// value is within a compile-time (default 0.05 Da) or run-time (user input) initialised range, the program next tests if the precursor retention time is
// compared to be within a compile-time (default 600 s) or run-time initialised range. Should these two tests return true,
// the (default 10) most intense fragment ions are compared between the two precursor ions. Should (default 4) of these be within
// a mass-to-charge ratio range (default 0.05 Da) the two scans are combined. Note that, from a physical perspective, the precursor
// ion and associated fragment ions are measured by first taking a (TOF?) detection of the precursor ion, and then taking one or several
// time-of-flight detections
//
// The summing process combines two scans as follows -
//
// 1. The mean of the [Bayesian (?)] two precursor ions
//
// This process continues through the entirety of the created data structures and upon completion the modified data
// is output as a new mgf file.

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