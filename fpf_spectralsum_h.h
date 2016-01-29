/*
 *	File:   fpf_spectralsum_h.h
 *	Author: Lukah Dykes
 */



#ifndef FPF_SPECTRALSUM_H
#define	FPF_SPECTRALSUM_H
#include <cstdlib> // provides - size_t, NULL
#include <fstream> // provides - std::ifstream
#include <istream> // provides - std::istream::get, std::istream::peek
#include <sstream> // provides - std::istringstream
#include <string> // provides - std::string
#include <iostream> // provides - std::cin, std::cout
#include "fpf_ion_h.h"
#include "fpf_node_h.h"

namespace fpf_spectralsum {

	static int fpf_spectralsum_DEBUG_MODE = int();

	typedef fpf_ion::ion::value_type value_type;
	//
	//		scan::value_type is the data type of elements of the SCAN class. It may 
	//		be any C++ built-in type, or an object with a default constructor,
	//		assignment operator, and equality operators.

	typedef size_t size_type;
	//
	//		scan::size_type is the data type of any variable that is assigned to
	//		enumerate quantity at run-time.

	typedef fpf_node::node::node_type node_type;
	//
	//

	typedef fpf_node::node::data_type data_type;

	static value_type CONDITION_PRECURSOR_MASS = 0.03;
	//
	//

	static value_type CONDITION_PRECURSOR_MZ = 0.05;
	//
	//		scan::CONDITION_PRECURSOR_MZ defines the delta-range of precursor
	//		mass-to-charge ratio to determine if two classes are suitable for
	//		spectral summing.

	static value_type CONDITION_PRECURSOR_RT = 60;
	//
	//		scan::CONDITION_PRECURSOR_RT defines the delta-range of retention
	//		time to determine if two classes are suitable for spectral summing. 
	//		It can be program-defined, or called from an external source.

	static value_type CONDITION_FRAGMENT_ION_INTENSITY = 5;
	//
	//

	static value_type CONDITION_FRAGMENT_ION = 95;
	//
	//		scan::CONDITION_FRAGMENT_ION defines the score limit-value of fragment
	//		ion distribution similarity to determine if two classes are suitable for
	//		for spectral summing. Fragment ion distribution is scored on the basis
	//		of peak intensity and fragment ion mass-to-charge ratio. Scoring is 
	//		controlled by the ION class type as defined in FPF_ION_H.H.

	static value_type CONDITION_FRAGMENT_ION_MZ = 0.03;
	//
	//

	static const size_t COUNT_FRAGMENT_SUP = 7;
	//
	//

	static const size_t CONDITION_FRAGMENT_ION_SUP = 4;
	//
	//

	/*
	 *
	 */

	class scan {
		//
		//		A SCAN class is a collection of doubles that contain the precursor mass,
		//		precursor charge, mass-to-charge ratio, and retention time. SCAN classes 
		//		are linked to the corresponding fragment ions through a pointer
		//		assignment to an IONS class. The associated IONS class contains as a 
		//		dynamic array of doubles the transition ions of the respective SCAN class 
		//		element(s). Should two or more SCAN classes be determined to be suitable
		//		for spectral summing, as tested by bool conditions, the union of 
		//		these classes is created in a new SCAN class. SCAN classes created 
		//		through the union process are identifiable by bool value. The 
		//		collection of union created SCAN classes are exported to a .mgf file at 
		//		program completion.

	public:

		scan() {
			vt_precursor_mass = value_type();
			vt_precursor_mz = value_type();
			vt_precursor_rt = value_type();
			st_precursor_charge = size_type();
			nt_head_ptr = NULL;
			nt_tail_ptr = NULL;
			b_union = bool();
		};

		~scan() {
		};

		/*
		 *
		 *	MEMBER FUNCTIONS
		 *
		 */

		inline void set_precursor_mass(value_type parse_precursor_mass) {
			vt_precursor_mass = parse_precursor_mass;
		};

		inline void set_precursor_mz(value_type parse_precursor_mz) {
			vt_precursor_mz = parse_precursor_mz;
		};

		inline void set_precursor_rt(value_type parse_precursor_rt) {
			vt_precursor_rt = parse_precursor_rt;
		};

		inline void set_precursor_charge(size_type parse_precursor_charge) {
			st_precursor_charge = parse_precursor_charge;
		};

		inline void set_union_n(bool b_new_union) {
			b_union = b_new_union;
		};

		scan operator+(const scan& scan_1);

		/*
		 *
		 *	CONSTANT MEMBER FUNCTIONS
		 *
		 */

		inline const value_type return_precursor_mass() const {
			return vt_precursor_mass;
		};
		//		Returns the precursor mass of a SCAN class.

		inline const value_type return_precursor_mz() const {
			return vt_precursor_mz;
		};
		//		Returns the precursor mass-to-charge ratio of a SCAN class.

		inline const value_type return_precursor_rt() const {
			return vt_precursor_rt;
		};
		//		Returns the precursor retention time of a SCAN class.

		inline const size_type return_precursor_charge() const {
			return st_precursor_charge;
		};
		//		Returns the precursor charge of a SCAN class.

		inline node_type& return_ion_head_ptr() {
			return nt_head_ptr;
		};
		//		Returns a head pointer to a linked lift of ION classes for the 
		//		associated SCAN class. The pointer directs to the head node of 
		//		a linked list.

		inline node_type& return_ion_tail_ptr() {
			return nt_tail_ptr;
		};
		//		Returns a tail pointer to a linked lift of ION classes for the 
		//		associated SCAN class. The pointer directs to the head node of 
		//		a linked list.

		inline bool& return_union_b() {
			return b_union;
		};
		//
		//

		inline value_type* return_fragment_ion_sup_intensities() {
		};
		//
		//

	private:
		value_type vt_precursor_mass;
		value_type vt_precursor_mz;
		value_type vt_precursor_rt;
		size_type st_precursor_charge;
		node_type nt_head_ptr;
		node_type nt_tail_ptr;
		bool b_union;
	};

	/*
	 *
	 * FUNCTIONS
	 *
	 */

	inline bool union_precursor_mass(const scan& scan_1, const scan& scan_2) {
		return ((scan_1.return_precursor_mass() < scan_2.return_precursor_mass() + CONDITION_PRECURSOR_MASS) && (scan_1.return_precursor_mass() > scan_2.return_precursor_mass() - CONDITION_PRECURSOR_MASS));
	};
	//		Returns TRUE if the precursor masses of two SCAN classes 
	//		are within the delta-value range defined by CONDITION_PRECURSOR_MASS.

	inline bool union_precursor_rt(const scan& scan_1, const scan& scan_2) {
		return ((scan_1.return_precursor_rt() < scan_2.return_precursor_rt() + CONDITION_PRECURSOR_RT) && (scan_1.return_precursor_rt() > scan_2.return_precursor_rt() - CONDITION_PRECURSOR_RT));
	};
	//		Returns TRUE if the retention times of two SCAN classes are within the 
	//		delta-value range defined by CONDITION_RETENTION_TIME.

	inline bool union_fragment_ion_mz(const data_type d_ion_itr_1, const data_type d_ion_itr_2) {
		return ((d_ion_itr_1->return_fragment_ion_mz() < d_ion_itr_2->return_fragment_ion_mz() + CONDITION_FRAGMENT_ION_MZ) && (d_ion_itr_1->return_fragment_ion_mz() > d_ion_itr_2->return_fragment_ion_mz() - CONDITION_FRAGMENT_ION_MZ));
	};
	//
	//

	inline bool union_fragment_ion_mz_boundconst(const data_type d_ion_itr_1, const data_type d_ion_itr_1_hold) {
		return (d_ion_itr_1->return_fragment_ion_mz() < d_ion_itr_1_hold->return_fragment_ion_mz() + (CONDITION_FRAGMENT_ION_MZ * 1.1) && (d_ion_itr_1->return_fragment_ion_mz() > d_ion_itr_1_hold->return_fragment_ion_mz() - (CONDITION_FRAGMENT_ION_MZ * 1.1)));
	};

	bool union_fragment_ion_sup_intensities(scan& scan_1, scan& scan_2) {
		fpf_ion::ion* default_ion = new fpf_ion::ion();
		fpf_ion::ion* scan_1_fragment_ion_sup[COUNT_FRAGMENT_SUP];
		fpf_ion::ion* scan_2_fragment_ion_sup[COUNT_FRAGMENT_SUP];
		fpf_ion::ion* hold_fragment_ion_sup_intensity = new fpf_ion::ion();
		fpf_ion::ion* hold_prev_fragment_ion_sup_intensity = new fpf_ion::ion();
		size_type count_ion_sup_intensity = size_type();
		for (size_t i = 0; i < COUNT_FRAGMENT_SUP; ++i) {
			for (node_type scan_1_ptr_itr = scan_1.return_ion_head_ptr(); scan_1_ptr_itr != NULL; scan_1_ptr_itr = scan_1_ptr_itr->return_node_nt()) {
				if ((i > 0) && (scan_1_ptr_itr->return_data_dt()->return_fragment_ion_intensity() < scan_1_fragment_ion_sup[i - 1]->return_fragment_ion_intensity()) && (scan_1_ptr_itr->return_data_dt()->return_fragment_ion_intensity() > hold_prev_fragment_ion_sup_intensity->return_fragment_ion_intensity())) {
					hold_fragment_ion_sup_intensity = scan_1_ptr_itr->return_data_dt();
					hold_prev_fragment_ion_sup_intensity = scan_1_ptr_itr->return_data_dt();
				}
				if ((i == 0) && (scan_1_ptr_itr->return_data_dt()->return_fragment_ion_intensity() > hold_prev_fragment_ion_sup_intensity->return_fragment_ion_intensity())) {
					hold_fragment_ion_sup_intensity = scan_1_ptr_itr->return_data_dt();
					hold_prev_fragment_ion_sup_intensity = scan_1_ptr_itr->return_data_dt();
				}
			}
			scan_1_fragment_ion_sup[i] = hold_fragment_ion_sup_intensity;
			hold_prev_fragment_ion_sup_intensity = default_ion;
		}
		for (size_t i = 0; i < COUNT_FRAGMENT_SUP; ++i) {
			for (node_type scan_2_ptr_itr = scan_2.return_ion_head_ptr(); scan_2_ptr_itr != NULL; scan_2_ptr_itr = scan_2_ptr_itr->return_node_nt()) {
				if ((i > 0) && (scan_2_ptr_itr->return_data_dt()->return_fragment_ion_intensity() < scan_2_fragment_ion_sup[i - 1]->return_fragment_ion_intensity()) && (scan_2_ptr_itr->return_data_dt()->return_fragment_ion_intensity() > hold_prev_fragment_ion_sup_intensity->return_fragment_ion_intensity())) {
					hold_fragment_ion_sup_intensity = scan_2_ptr_itr->return_data_dt();
					hold_prev_fragment_ion_sup_intensity = scan_2_ptr_itr->return_data_dt();
				}
				if ((i == 0) && (scan_2_ptr_itr->return_data_dt()->return_fragment_ion_intensity() > hold_prev_fragment_ion_sup_intensity->return_fragment_ion_intensity())) {
					hold_fragment_ion_sup_intensity = scan_2_ptr_itr->return_data_dt();
					hold_prev_fragment_ion_sup_intensity = scan_2_ptr_itr->return_data_dt();
				}
			}
			scan_2_fragment_ion_sup[i] = hold_fragment_ion_sup_intensity;
			hold_prev_fragment_ion_sup_intensity = default_ion;
		}
		if (fpf_spectralsum_DEBUG_MODE == 2) {
			std::cout << "\n\n";
		}
		for (size_t i = 0; i < COUNT_FRAGMENT_SUP; ++i) {
			if (fpf_spectralsum_DEBUG_MODE == 2) {
				std::cout << scan_1_fragment_ion_sup[i]->return_fragment_ion_intensity() << " " << scan_1_fragment_ion_sup[i]->return_fragment_ion_mz() << "   ";
			}
			for (size_t j = 0; j < COUNT_FRAGMENT_SUP; ++j) {
				if (union_fragment_ion_mz(scan_1_fragment_ion_sup[i], scan_2_fragment_ion_sup[j])) {
					++count_ion_sup_intensity;
				}
			}
		}
		if (fpf_spectralsum_DEBUG_MODE == 2) {
			std::cout << "\n\n";
			for (size_t j = 0; j < COUNT_FRAGMENT_SUP; ++j) {
				std::cout << scan_2_fragment_ion_sup[j]->return_fragment_ion_intensity() << " " << scan_2_fragment_ion_sup[j]->return_fragment_ion_mz() << "   ";
			}
			std::cout << "! count_ion_sup_intensity " << count_ion_sup_intensity << "\n";
			// << "  (count_ion_sup_intensity >= CONDITION_FRAGMENT_ION_SUP) " << (count_ion_sup_intensity >= CONDITION_FRAGMENT_ION_SUP) << "\n";
		}
		return (count_ion_sup_intensity >= CONDITION_FRAGMENT_ION_SUP);
	};
	//
	//

	scan scan_union(scan& scan_1, scan & scan_2) {
		scan scan_3 = scan();
		fpf_ion::ion* ion_union;
		scan_3.set_precursor_mass((scan_1.return_precursor_mass() + scan_2.return_precursor_mass()) / 2);
		scan_3.set_precursor_rt((scan_1.return_precursor_rt() + scan_2.return_precursor_rt()) / 2);
		scan_3.set_union_n(true);
		for (node_type scan_1_ptr_itr = scan_1.return_ion_head_ptr(); scan_1_ptr_itr != NULL; scan_1_ptr_itr = scan_1_ptr_itr->return_node_nt()) {
			for (node_type scan_2_ptr_itr = scan_2.return_ion_head_ptr(); scan_2_ptr_itr != NULL; scan_2_ptr_itr = scan_2_ptr_itr->return_node_nt()) {
				if (union_fragment_ion_mz(scan_1_ptr_itr->return_data_dt(), scan_2_ptr_itr->return_data_dt())) {
					ion_union = new fpf_ion::ion();
					// here!
					ion_union->set_fragment_ion_mz_vt((scan_1_ptr_itr->return_data_dt()->return_fragment_ion_mz() + scan_2_ptr_itr->return_data_dt()->return_fragment_ion_mz()) / 2);
					ion_union->set_fragment_ion_intensity_st(scan_1_ptr_itr->return_data_dt()->return_fragment_ion_intensity() + scan_2_ptr_itr->return_data_dt()->return_fragment_ion_intensity());
					ion_union->set_union_init_b(true);
					scan_1_ptr_itr->return_data_dt()->set_union_init_b(true);
					scan_2_ptr_itr->return_data_dt()->set_union_init_b(true);
					fpf_node::list_insert_tail(ion_union, scan_3.return_ion_head_ptr(), scan_3.return_ion_tail_ptr());
				}
				if ((scan_1_ptr_itr == scan_1.return_ion_tail_ptr()) && !scan_2_ptr_itr->return_data_dt()->return_union_init_b()) {
					ion_union = new fpf_ion::ion();
					ion_union->set_fragment_ion_mz_vt(scan_2_ptr_itr->return_data_dt()->return_fragment_ion_mz());
					ion_union->set_fragment_ion_intensity_st(scan_2_ptr_itr->return_data_dt()->return_fragment_ion_intensity());
					fpf_node::list_insert_tail(ion_union, scan_3.return_ion_head_ptr(), scan_3.return_ion_tail_ptr());
				}
			}
			if (!scan_1_ptr_itr->return_data_dt()->return_union_init_b()) {
				ion_union = new fpf_ion::ion();
				ion_union->set_fragment_ion_mz_vt(scan_1_ptr_itr->return_data_dt()->return_fragment_ion_mz());
				ion_union->set_fragment_ion_intensity_st(scan_1_ptr_itr->return_data_dt()->return_fragment_ion_intensity());
				fpf_node::list_insert_tail(ion_union, scan_3.return_ion_head_ptr(), scan_3.return_ion_tail_ptr());
			}
		}
		return scan_3;
	};
	//		Returns a SCAN class that is the union of two SCAN classes. Referenced 
	//		scan_1 and scan_2 are required to be within the conditional definition
	// 		for spectral summing. Conditional selection is determined by -
	//
	//			1a - Precursor mass
	//			1b - Retention time
	//			2 - Fragment ion distribution
	//			- - ?
	//
	//		Conditional selection is bool tested with the corresponding member functions -
	//
	//			1a - bool union_precursor_mass(const scan& scan_1, const scan& scan_2)
	//			1b - bool union_precursor_rt(const scan& scan_1, const scan& scan_2)
	//			2 - bool union_fragment_ion(const scan& scan_1, const scan & scan_2)
	//			- - ?
	//
	//		Should two
	//		fragment ions be suitable for spectral summing, the average fragment ion
	//		mass-to-charge ratio and the summation of intensities is calculated for
	//		the resulting SCAN class. Union SCAN classes are assigned to the PARSE_UNION
	//		class and at program completion are	exported to a .mgf file for downstream 
	//		analysis.



	/*
	 *
	 */



	class main {
		typedef long double value_type;
		//
		//

		typedef size_t size_type;
		//
		//

		typedef scan* scan_node_type;
		//
		//

		static const size_type PARSE_DEFAULT_ALLOCATION = 200000;
		//
		//

	public:

		main(size_type class_size = PARSE_DEFAULT_ALLOCATION) {
			nt_scan = new scan[class_size];
			st_capacity = class_size;
			st_used = size_type();
			st_union_itr = size_type();
		};

		main(const main& main);

		~main() {
			delete[] nt_scan;
		};

		// OPERATORS

		void operator=(const main parse_0) {
			//main* tail_ptr;
		};

		// MODIFICATION MEMBER FUNCTIONS

		void input_parse(std::ifstream& fin, main& parse_0) {
			char c_inputstream;
			std::string s_inputstream = "";
			int switch_inputstream = 0;
			value_type ss_inputstream;
			value_type vt_inputstream;
			value_type vt_inputstream_2;
			fpf_ion::ion* ion_inputstream;
			static size_type output_interval = 100;
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
					std::istringstream(s_inputstream) >> ss_inputstream;
					//long double?
					vt_inputstream = ss_inputstream;
					nt_scan[st_used].set_precursor_rt(vt_inputstream);
					s_inputstream.clear();
				}
				if ((switch_inputstream == 4) && (c_inputstream == ' ')) {
					std::istringstream(s_inputstream) >> ss_inputstream;
					//long double?
					vt_inputstream = ss_inputstream;
					switch_inputstream = 5;
					s_inputstream.clear();
				}
				if ((switch_inputstream == 5) && (c_inputstream == '\n')) {
					// W4 warns 'potentially uninitialized local pointer variable 'ion_inputstream' used' - note call to variable in if conditional? Functionality is okay.
					std::istringstream(s_inputstream) >> ss_inputstream;
					//long double?
					vt_inputstream_2 = ss_inputstream;
					if (vt_inputstream_2 >= CONDITION_FRAGMENT_ION_INTENSITY) {
						ion_inputstream = new fpf_ion::ion();
						ion_inputstream->set_fragment_ion_mz_vt(vt_inputstream);
						ion_inputstream->set_fragment_ion_intensity_st(vt_inputstream_2);
						fpf_node::list_insert_tail(ion_inputstream, nt_scan[st_used].return_ion_head_ptr(), nt_scan[st_used].return_ion_tail_ptr());
					}
					switch_inputstream = 4;
					s_inputstream.clear();
				}
				if (s_inputstream == "PEPMASS=") {
					switch_inputstream = 3;
					s_inputstream.clear();
				}
				if ((switch_inputstream == 3) && (c_inputstream == '\n')) {
					std::istringstream(s_inputstream) >> ss_inputstream;
					vt_inputstream = ss_inputstream;
					nt_scan[st_used].set_precursor_mass(vt_inputstream);
					switch_inputstream = 4;
					s_inputstream.clear();
				}
				if ((switch_inputstream == 4) && ((c_inputstream == 'E'))) {
					switch_inputstream = 0;
					++parse_0.st_used;
					if (parse_0.st_used % output_interval == 0) {
						std::cout << "\nscan - " << parse_0.st_used << "   retention time - " << ((nt_scan[st_used - 1].return_precursor_rt()) / 60);
						if (parse_0.st_used > 2 * output_interval - 1) {
							std::cout << "   delta - " << ((nt_scan[st_used - 1].return_precursor_rt()) / 60) - ((nt_scan[st_used - output_interval - 1].return_precursor_rt()) / 60);
						}
					}
				}
				if (c_inputstream == '\n') {
					s_inputstream.clear();
				}
			}
			std::cout << "\nscan - " << parse_0.st_used << "   retention time - " << ((nt_scan[st_used - 1].return_precursor_rt()) / 60);
			if (parse_0.st_used > 2 * output_interval - 1) {
				std::cout << "   delta - " << ((nt_scan[st_used - 1].return_precursor_rt()) / 60) - ((nt_scan[st_used - output_interval - 1].return_precursor_rt()) / 60);
			}
		};
		//
		//

		void main_scan_ion_sum(main& union_parse) {
			node_type nt_ion_itr_hold = node_type();
			node_type nt_ion_itr_hold_2 = node_type();
			for (size_type i = 0; i < union_parse.return_used(); ++i) {
				for (node_type nt_ion_itr = union_parse.nt_scan[i].return_ion_head_ptr(); nt_ion_itr != NULL; nt_ion_itr->return_node_nt()) {				
					if ((i > 0) && union_fragment_ion_mz_boundconst(nt_ion_itr->return_data_dt(), nt_ion_itr_hold->return_data_dt())) {
						nt_ion_itr->return_data_dt()->set_fragment_ion_intensity_st(fpf_ion::return_ion_mean(nt_ion_itr->return_data_dt(), nt_ion_itr_hold->return_data_dt()));
						nt_ion_itr_hold_2->set_node_nt(nt_ion_itr);
						nt_ion_itr_hold_2 = nt_ion_itr_hold;
						nt_ion_itr_hold = nt_ion_itr;
					}
				}
			}
		};
		//
		//

		void main_scan_sum(const main& c_main, main& c_union) {
			size_type st_used_prev = size_type();
			static size_type st_output_interval = 100;
			bool union_condition = bool();
			size_type forward_match_false = size_type();
			size_type forward_match_true = size_type();
			size_type forward_match_false_matched = size_type();
			size_type union_false_count = size_type();
			size_type union_true_count = size_type();
			c_union.st_union_itr = c_main.st_union_itr + 1;
			std::cout << "\n\n\nSumming...\n";
			for (size_type i = 0; i < c_main.return_used(); ++i) {
				for (size_type j = i; j < c_main.return_used(); j) {
					if ((i != j) && (union_precursor_mass(c_main.nt_scan[i], c_main.nt_scan[j])) && union_precursor_rt(c_main.nt_scan[i], c_main.nt_scan[j]) && union_fragment_ion_sup_intensities(c_main.nt_scan[i], c_main.nt_scan[j])) {               
						if (fpf_spectralsum_DEBUG_MODE == 2) {
							++forward_match_true;
							std::cout << "\nscan_1 mass " << nt_scan[i].return_precursor_mass() << "  retention time " << (nt_scan[i].return_precursor_rt() / 60) << "   scan_2 mass " << nt_scan[j].return_precursor_mass() << "  retention time " << (nt_scan[j].return_precursor_rt() / 60)
								<< "   ! scan_1.return_union_b() " << c_main.nt_scan[i].return_union_b() << "  scan_2.return_union_b() " << c_main.nt_scan[j].return_union_b()
								<< "  union_precursor_mass() " << union_precursor_mass(c_main.nt_scan[i], c_main.nt_scan[j]) << "  union_precursor_rt() " << union_precursor_rt(c_main.nt_scan[i], c_main.nt_scan[j]);
							std::cout << "\n\n--- forward match for scan " << i << " with scan " << j << "   ! forward_match_true " << forward_match_true << "\n\n";
						}
						c_main.nt_scan[i].set_union_n(true);
						c_main.nt_scan[j].set_union_n(true);
						c_union.nt_scan[c_union.st_used] = scan_union(c_main.nt_scan[i], c_main.nt_scan[j]);
						++c_union.st_used;
						++union_true_count;
						union_condition = true;
					}
					if (j + 1 == c_main.return_used()) {
						if (!(c_main.nt_scan[i].return_union_b())) {
							c_union.nt_scan[c_union.st_used] = c_main.nt_scan[i];
							++c_union.st_used;
							++union_false_count;
							++forward_match_false_matched;
						}
						++forward_match_false;
						if (fpf_spectralsum_DEBUG_MODE == 2) {
							std::cout << "\n--- no forward match for scan " << i << "   ! c_main.nt_scan[i].return_union_b() " << (c_main.nt_scan[i].return_union_b()) << "  forward_match_false " << forward_match_false << "  forward_match_false_matched " << forward_match_false_matched << "\n";
						}
					}
					if (union_condition) {
						if (fpf_spectralsum_DEBUG_MODE == 0) {
							if ((i > 0) && (i % st_output_interval == 0)) {
								std::cout << "\nscan - " << i << "   union itr" << c_union.return_union_itr() << " - " << union_true_count;
								if (c_main.st_used > 2 * st_output_interval - 1) {
									std::cout << " - delta " << union_true_count - st_used_prev;
								}
								std::cout << " - unmatched " << union_false_count << " - total " << c_union.st_used;
								std::cout << "   retention time - " << ((c_main.nt_scan[i].return_precursor_rt()) / 60);
								st_used_prev = union_true_count;
							}
							if (i + 1 == c_main.return_used() && !((i > 0) && (i % st_output_interval == 0))) {
								std::cout << "\nscan - " << c_main.return_used() << "   union itr" << c_union.return_union_itr() << " - " << union_true_count;
								if (c_union.st_used > 2 * st_output_interval - 1) {
									std::cout << " - delta " << union_true_count - st_used_prev;
								}
								std::cout << " - unmatched " << union_false_count << " - total " << c_union.st_used;
								if (c_union.st_used > 2 * st_output_interval - 1) {
									std::cout << "   retention time - " << ((c_main.nt_scan[i].return_precursor_rt()) / 60);
								}
							}
						}
						++i;
						++j;
						union_condition = false;
					}
					else {
						++j;
					}
				}
				if (!union_condition) {
					if (fpf_spectralsum_DEBUG_MODE == 0) {
						if ((i > 0) && (i % st_output_interval == 0)) {
							std::cout << "\nscan - " << i << "   union itr" << c_union.return_union_itr() << " - " << union_true_count;
							// here?
							if (c_main.st_used > 2 * st_output_interval - 1) {
								std::cout << " - delta " << union_true_count - st_used_prev;
							}
							std::cout << " - unmatched " << union_false_count << " - total " << c_union.st_used;
							std::cout << "   retention time - " << ((c_main.nt_scan[i].return_precursor_rt()) / 60);
							st_used_prev = union_true_count;
						}
						if (i + 1 == c_main.return_used() && !((i > 0) && (i % st_output_interval == 0))) {
							std::cout << "\nscan - " << c_main.return_used() << "   union itr" << c_union.return_union_itr() << " - " << union_true_count;
							if (c_union.st_used > 2 * st_output_interval - 1) {
								std::cout << " - delta " << union_true_count - st_used_prev;
							}
							std::cout << " - unmatched " << union_false_count << " - total " << c_union.st_used;
							if (c_union.st_used > 2 * st_output_interval - 1) {
								std::cout << "   retention time - " << ((c_main.nt_scan[i].return_precursor_rt()) / 60);
							}
						}
					}
				}
			}
		};
		//
		//

		void main_reset() {
			for (size_type i = size_type(); i < return_used(); ++i) {
				nt_scan[i].set_union_n(false);
				for (node_type scan_ptr_itr = nt_scan[i].return_ion_head_ptr(); scan_ptr_itr != NULL; scan_ptr_itr = scan_ptr_itr->return_node_nt()) {
					scan_ptr_itr->return_data_dt()->set_union_init_b(false);
				}
			}
		}

		// CONSTANT MEMBER FUNCTIONS

		inline const scan_node_type return_scan() const {
			return nt_scan;
		};

		inline const size_type return_capacity() const {
			return st_capacity;
		};

		inline const size_type return_used() const {
			return st_used;
		};

		inline const size_type return_union_itr() const {
			return st_union_itr;
		};

		const int input_summary(std::ifstream& fin) {
			char c_inputstream;
			int scan_objects;
			while (fin.std::istream::get(c_inputstream)) {
				if ((fin.std::istream::peek() == 'E') && (c_inputstream == '\n')) {
					++scan_objects;
				}
			}
			return scan_objects;
		}

		void debug_parse() const {
			for (size_type i = size_type(); i < return_used(); ++i) {
				std::cout << "\n" << i;
				std::cout << "\nnt_scan[i].return_precursor_rt() " << nt_scan[i].return_precursor_rt();
				std::cout << "\nnt_scan[i].return_precursor_mass() " << nt_scan[i].return_precursor_mass();
				for (node_type nt_scan_head_ptr = nt_scan[i].return_ion_head_ptr(); nt_scan_head_ptr != NULL; nt_scan_head_ptr = nt_scan_head_ptr->return_node_nt()) {
					std::cout << "\n" << nt_scan_head_ptr->return_data_dt()->return_fragment_ion_mz() << "  " << nt_scan_head_ptr->return_data_dt()->return_fragment_ion_intensity();
				}
			}
			if (return_used() == 0) {
				std::cout << "\n\nNo members!";
			}
		};

		void cout_mgf() const {
			for (unsigned i = 0; i < return_used(); ++i) {
				if (i > 0) {
					std::cout << "\nBEGIN IONS";
				}
				else {
					std::cout << "BEGIN IONS";
				}
				std::cout << "\nTITLE=" << "NULL";
				std::cout << "\nRTINSECONDS=" << nt_scan[i].return_precursor_rt();
				std::cout << "\nPEPMASS=" << nt_scan[i].return_precursor_mass();
				for (node_type nt_scan_head_ptr = nt_scan[i].return_ion_head_ptr(); nt_scan_head_ptr != NULL; nt_scan_head_ptr = nt_scan_head_ptr->return_node_nt()) {
					std::cout << "\n" << nt_scan_head_ptr->return_data_dt()->return_fragment_ion_mz() << "   " << nt_scan_head_ptr->return_data_dt()->return_fragment_ion_intensity() << "   " << nt_scan_head_ptr->return_data_dt()->return_union_count_st();
				}
				std::cout << "\nEND IONS";
			}
			if (return_used() == 0) {
				std::cout << "\n\nNo members!";
			}
		};

		void fout_mgf(std::ofstream& fout) const {
			size_type union_false_count = size_type();
			size_type union_true_count = size_type();
			std::cout << "\n\n\nOutputting...";
			for (unsigned i = 0; i < return_used(); ++i) {
				if (i > 0) {
					fout << "\nBEGIN IONS";
				}
				else {
					fout << "BEGIN IONS";
				}
				fout << "\nTITLE=" << "NULL";
				fout << "\nRTINSECONDS=" << nt_scan[i].return_precursor_rt();
				fout << "\nPEPMASS=" << nt_scan[i].return_precursor_mass();
				if (fpf_spectralsum_DEBUG_MODE >= 1) {
					if (!nt_scan[i].return_union_b()) {
						++union_false_count;
					}
					if (nt_scan[i].return_union_b()) {
						++union_true_count;
					}
					fout << " # " << i << "   ! nt_scan[i].return_union_b() " << nt_scan[i].return_union_b() << "   ! union_false_count " << union_false_count << "  union_true_count " << union_true_count;
				}
				for (node_type nt_scan_head_ptr = nt_scan[i].return_ion_head_ptr(); nt_scan_head_ptr != NULL; nt_scan_head_ptr = nt_scan_head_ptr->return_node_nt()) {
					fout << "\n" << nt_scan_head_ptr->return_data_dt()->return_fragment_ion_mz() << " " << nt_scan_head_ptr->return_data_dt()->return_fragment_ion_intensity();
					if (fpf_spectralsum_DEBUG_MODE >= 1) {
						fout << "  ! nt_scan_head_ptr->return_data_dt()->return_union_init_b() " << nt_scan_head_ptr->return_data_dt()->return_union_init_b() << "  nt_scan_head_ptr->return_data_dt()->return_union_count_st() " << nt_scan_head_ptr->return_data_dt()->return_union_count_st();
					}
				}
				fout << "\nEND IONS";
			}
			if (return_used() == 0) {
				std::cout << "\n\nNo members!";
			}
		};

	private:
		scan_node_type nt_scan;
		size_type st_capacity;
		size_type st_used;
		size_type st_union_itr;
	};
}

#endif
