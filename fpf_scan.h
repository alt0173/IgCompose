// * * fpf_scan.h * *
//
// Lukah Dykes - Flinders Proteomics Facility - 2016
//
// * * * * *

// --- namespace fpf_scan class scan
// 
// namespace fpf_scan contains object definitions for the scan class. A scan
// class declares private members to store the values of a precursor ion
// mass, retention time, pointers to the first and last element of a doubly linked link containing 
// associated fragment ion data as fion classes, and an integer count of the
// quantity of scan classes the scan class is composed of (initially 1). 
//
// The fpf_scan function union_pion_mass() and union_pion_rt() boolean tests if two scan class
// precursor ion masses and retention times are suitable for spectral summing.
// The fpf_scan function union_fion_sup_intensities() boolean tests if a defined many
// of the most intense associated fragment ions are within a mass-to-charge ratio
// range as boolean tested by the fpf_fion function union_fion_mz() - A true boolean
// value for all such functions calls vt_return_mean_pion_mass() and vt_return_mean_pion_rt() to
// calculate the mean mass and mean retention time of the two scan
// classes, taking into consideration previous summing through st_scan_union_count, and the doubly linked list of
// fragment ions pointed to by nt_fion_head_ptr and nt_fion_tail_ptr are summed through scan_fion_sum().

#ifndef FPF_SCAN
#define	FPF_SCAN
#include <cstdlib> // provides - size_t, NULL
#include <iostream> // provides - std::cin, std::cout
#include "fpf_node.h"
#include "fpf_fion.h"

namespace fpf_scan {

	class scan;
	// Forward declaration for class scan.

	typedef double value_type;
	// Defines value_type as any standard C++ data type.

	typedef size_t size_type;
	// Defines size_type as a size_t type. Requires <cstdlib>.

	typedef fpf_node::node<fpf_fion::fion*>* fion_node_type;
	// Defines fion_node_type as a pointer to a doubly linked list templated as
	// a pointer to a fion class.

	typedef fpf_fion::fion* fion_data_type;
	// Defines fion_data_type as a pointer to a fion class.

	typedef bool bool_type;
	// Defines fpf_scan::scan::bool_type as a bool type.

	//
	//
	//
	//   * * NAMESPACE VARIABLES * *
	//
	//
	//

	size_type fpf_scan_DEBUG_MODE;
	// fpf_scan_DEBUG_MODE is a size_type with a run-time initialised value that
	// determines the relevant debug mode to implement. The default value is 0.
	// Debug mode values relevant to fpf_scan are:
	// 0. Default value for fpf_spectralsum_DEBUG_MODE. The program will execute
	//    standard functionality.
	// 3. Displays fion class spectral sum boolean tests on the console.
	//    Compared fragment ion mass-to-charge ratios are shown, successful and
	//    unsuccessful comparisons are annotated, and the doubly linked lists of
	//    fion classes are displayed post-hoc.

	value_type vt_CONDITION_PION_MASS = 0.05;
	// vt_CONDITION_PION_MASS is a value_type with a compile-time or run-time
	// initialised value that defines the scan class precursor ion mass range
	// for spectral summing.

	value_type vt_CONDITION_PION_RT = 600;
	// vt_CONDITION_PION_RT is a value_type with a compile-time or run-time
	// initialised value that defines the scan class precursor ion retention
	// time range for spectral summing.



	class scan {
	public:

		scan() {
			// scan() defines the default constructor for the scan class. It
			// initialises member values as ISO type defaults (0 for standard
			// C++ data types, NULL for pointer types) and a value of 1 for
			// st_scan_union_count (representing an unsummed scan class).
			vt_pion_mass = value_type();
			vt_pion_rt = value_type();
			nt_fion_head_ptr = fion_node_type();
			nt_fion_tail_ptr = fion_node_type();
			st_scan_union_count = 1;
		};

		~scan() {
			// ~scan() defines the default destructor for the scan class.
			fpf_node::list_remove_all<fion_data_type>(nt_fion_head_ptr);
		};

		//
		//
		//
		// * * MEMBER MODIFICATION FUNCTIONS * *
		//
		//
		//

		inline void set_pion_mass(value_type vt_set_precursor_mass) {
			// set_pion_mass() assigns a value_type to vt_pion_mass.
			vt_pion_mass = vt_set_precursor_mass;
		};

		inline void set_pion_rt(value_type vt_set_precursor_rt) {
			// set_pion_rt() assigns a value_type to vt_pion_rt.
			vt_pion_rt = vt_set_precursor_rt;
		};

		inline void set_scan_union_count(size_type st_scan_union_cout) {
			// set_scan_union_count() assigns a value_type to st_scan_union_count.
			st_scan_union_count = st_scan_union_cout;
		};

		//
		//
		//
		//   * * MEMBER ACCESS FUNCTIONS * *
		//
		//
		//

		inline const value_type vt_return_pion_mass() const {
			// vt_return_pion_mass() returns vt_pion_mass, the precursor
			// mass of the referenced scan class.
			return vt_pion_mass;
		};

		inline const value_type vt_return_pion_rt() const {
			// vt_return_pion_rt() returns vt_pion_rt, the precursor
			// retention time of the referenced scan class.
			return vt_pion_rt;
		};

		inline fion_node_type& nt_return_fion_head_ptr() {
			// nt_return_fion_head_ptr() returns nt_fion_head_ptr, a pointer to the
			// first fpf_fion::fion class in a doubly linked list as defined in
			// fpf_node. Collectively the nodes of the list represent the fragment
			// ions of a associated to a precursor ion.
			return nt_fion_head_ptr;
		};

		inline fion_node_type& nt_return_fion_tail_ptr() {
			// nt_return_fion_tail_ptr() returns nt_fion_tail_ptr, a pointer to the
			// last fpf_fion::fion class in a doubly linked list as defined in
			// fpf_node. Collectively the nodes of the list represent the fragment
			// ions associated to a precursor ion.
			return nt_fion_tail_ptr;
		};

		inline size_type return_scan_union_count() {
			// return_scan_union_count() returns st_scan_union_count, the quantity of
			// scan classes that have been combined into the referenced scan class.
			// An unsummed scan class has a value of 1, a scan class having
			// undergone one iteration of summing has a value 2, and onwards.
			return st_scan_union_count;
		};

	private:
		value_type vt_pion_mass;
		// vt_pion_mass is a value_type that stores the value of the precursor ion mass for the
		// referenced scan class.

		value_type vt_pion_rt;
		// vt_pion_rt is a value_type that stores the value of the precursor ion retention time for
		// the referenced scan class.

		fion_node_type nt_fion_head_ptr;
		// nt_fion_head_ptr is an fion_node_type that stores a pointer to the first fpf_fion::fion class
		// in a doubly linked list as defined in fpf_node. Collectively the nodes of the list
		// represent the fragment ions of a scan.

		fion_node_type nt_fion_tail_ptr;
		// nt_fion_tail_ptr is an fion_node_type that stores a pointer to the last fpf_fion::fion class in
		// a doubly linked list as defined in fpf_node. Collectively the nodes of the list represent
		// the fragment ions of a scan.

		size_type st_scan_union_count;
		// st_scan_union_count is a size_type that stores the quantity of scan classes
		// that have been combined to create the referenced scan class. An unsummed scan class has a
		// value of 1, a scan class having undergone one iteration of summing has a value 2, and onwards.
	};

	//
	//
	//
	// * * NAMESPACE FUNCTIONS * *
	//
	//
	//

	void set_debug(size_type set_fpf_scan_DEBUG_MODE) {
		// set_debug() assigns a integer value to fpf_scan_DEBUG_MODE. The value of
		// global DEBUG_MODE determines fpf_scan_DEBUG_MODE in the main namespace.
		// The default value is 0. Debug mode values relevant to fpf_scan are:
		// 6. output fion class test for spectral summing
		// 7. output fion class test for spectral summing with explicit boolean test
		// *** Small (<5 scan class) test files are recommended.
		fpf_scan_DEBUG_MODE = set_fpf_scan_DEBUG_MODE;
	}

	void set_CONDITION_PION_MASS(value_type vt_set_CONDITION_PION_MASS) {
		// set_CONDITION_PION_MASS() assigns a value_type to vt_CONDITION_PION_MASS. 
		vt_CONDITION_PION_MASS = vt_set_CONDITION_PION_MASS;
	}

	void set_CONDITION_PION_RT(value_type vt_set_CONDITION_PION_RT) {
		// set_CONDITION_PION_RT() assigns a value_type to vt_CONDITION_PION_RT.  
		vt_CONDITION_PION_RT = vt_set_CONDITION_PION_RT;
	}

	inline bool_type union_pion_mass(const scan* scan_1, const scan* scan_2) {
		// union_pion_mass() is a bool_type return function that returns true if two compared scan
		// classes have vt_pion_mass values within a range of vt_CONDITION_PION_MASS. A return of
		// true is indicative that two precursor ion mass-to-charge ratios are suitable for spectral summing.
		return ((scan_1->vt_return_pion_mass() <= scan_2->vt_return_pion_mass() + (vt_CONDITION_PION_MASS / 2))
			&& (scan_1->vt_return_pion_mass() >= scan_2->vt_return_pion_mass() - (vt_CONDITION_PION_MASS / 2)) || scan_1->vt_return_pion_mass() == scan_2->vt_return_pion_mass());
	};

	inline bool_type union_pion_rt(const scan* scan_1, const scan* scan_2) {
		// union_pion_mass() is a bool_type return function that returns true if two
		// compared scan classes have vt_pion_rt values within a range of
		// vt_CONDITION_PION_RT. A return of true is indicative that two precursor
		// ion retention times are suitable for spectral summing.
		return ((scan_1->vt_return_pion_rt() <= scan_2->vt_return_pion_rt() + (vt_CONDITION_PION_RT / 2))
			&& (scan_1->vt_return_pion_rt() >= scan_2->vt_return_pion_rt() - (vt_CONDITION_PION_RT / 2)) || scan_1->vt_return_pion_rt() == scan_2->vt_return_pion_rt());
	};

	inline bool_type union_fion_sup_intensities(scan* scan_1, scan* scan_2) {
		// union_fion_sup_intensities() is a bool_type return function that returns
		// true if two compared scan classes have fpf_fion::st_CONDITION_FION_SUP of
		// the fpf_fion::st_CONDITION_COUNT_FION_SUP most intense fragment ions
		// within a mass-to-charge ratio range of fpf_fion::vt_CONDITION_FION_MZ.
		// Initially, the st_CONDITION_COUNT_FION_SUP most intense ions for compared
		// scan classes are stored in scan_1_fion_sup[] and scan_2_fion_sup[]
		// respectively and the array elements are boolean tested through
		// fpf_fion::union_fion_mz(). A return of true indicates that the
		// fragment ion distribution of the two scan classes is suitable for
		// spectral summing.
		fion_data_type default_fion = new fpf_fion::fion();
		fion_data_type scan_1_fion_sup[fpf_fion::st_CONDITION_COUNT_FION_SUP];
		fion_data_type scan_2_fion_sup[fpf_fion::st_CONDITION_COUNT_FION_SUP];
		fion_data_type hold_fion_sup_intensity = new fpf_fion::fion();
		size_type count_ion_sup_intensity = size_type();
		for (size_t i = 0; i < fpf_fion::st_CONDITION_COUNT_FION_SUP; ++i) {
			// Determines the fpf_fion::st_CONDITION_COUNT_FION_SUP most intense fragment ions in scan_1 and stores in scan_1_fion_sup[].
			for (fion_node_type scan_1_ptr_itr = scan_1->nt_return_fion_head_ptr(); scan_1_ptr_itr != NULL; scan_1_ptr_itr = scan_1_ptr_itr->nt_return_up_node()) {
				if ((i > 0)
					&& (scan_1_ptr_itr->dt_return_data()->return_fion_intensity() <= scan_1_fion_sup[i - 1]->return_fion_intensity())
					&& (scan_1_ptr_itr->dt_return_data()->return_fion_intensity() >= hold_fion_sup_intensity->return_fion_intensity())
					&& (scan_1_ptr_itr->dt_return_data()->vt_return_fion_mz() != scan_1_fion_sup[i - 1]->vt_return_fion_mz())) {
					hold_fion_sup_intensity = scan_1_ptr_itr->dt_return_data();
				}
				if ((i == 0)
					&& (scan_1_ptr_itr->dt_return_data()->return_fion_intensity() >= hold_fion_sup_intensity->return_fion_intensity())) {
					hold_fion_sup_intensity = scan_1_ptr_itr->dt_return_data();
				}
			}
			scan_1_fion_sup[i] = hold_fion_sup_intensity;
			hold_fion_sup_intensity = default_fion;
		}
		for (size_t i = 0; i < fpf_fion::st_CONDITION_COUNT_FION_SUP; ++i) {
			// Determines the fpf_fion::st_CONDITION_COUNT_FION_SUP most intense fragment ions in scan_2 and stores in scan_2_fion_sup[].
			for (fion_node_type scan_2_ptr_itr = scan_2->nt_return_fion_head_ptr(); scan_2_ptr_itr != NULL; scan_2_ptr_itr = scan_2_ptr_itr->nt_return_up_node()) {
				if ((i > 0)
					&& (scan_2_ptr_itr->dt_return_data()->return_fion_intensity() <= scan_2_fion_sup[i - 1]->return_fion_intensity())
					&& (scan_2_ptr_itr->dt_return_data()->return_fion_intensity() >= hold_fion_sup_intensity->return_fion_intensity())
					&& (scan_2_ptr_itr->dt_return_data()->vt_return_fion_mz() != scan_2_fion_sup[i - 1]->vt_return_fion_mz())) {
					hold_fion_sup_intensity = scan_2_ptr_itr->dt_return_data();
				}
				if ((i == 0)
					&& (scan_2_ptr_itr->dt_return_data()->return_fion_intensity() >= hold_fion_sup_intensity->return_fion_intensity())) {
					hold_fion_sup_intensity = scan_2_ptr_itr->dt_return_data();
				}
			}
			scan_2_fion_sup[i] = hold_fion_sup_intensity;
			hold_fion_sup_intensity = default_fion;
		}
		if (fpf_scan_DEBUG_MODE == 2) {
			std::cout << "\n\n";
		}
		for (size_t i = 0; i < fpf_fion::st_CONDITION_COUNT_FION_SUP; ++i) {
			// Compares mass-to-charge ratio values in scan_1_fion_sup[] and scan_2_fion_sup[].
			// union_fion_sup_intensities() returns true if st_CONDITION_FION_SUP are within a
			// mass-to-charge ratio range of vt_CONDITION_FION_MZ as determined by union_fion_mz().
			if (fpf_scan_DEBUG_MODE == 2) {
				std::cout << " " << scan_1_fion_sup[i]->return_fion_intensity();
				std::cout << " " << scan_1_fion_sup[i]->vt_return_fion_mz();
				std::cout << "   ";
			}
			for (size_t j = 0; j < fpf_fion::st_CONDITION_COUNT_FION_SUP; ++j) {
				if (fpf_fion::union_fion_mz(scan_1_fion_sup[i], scan_2_fion_sup[j])
					&& (scan_1_fion_sup[i]->vt_return_fion_mz() != 0)
					&& (scan_1_fion_sup[j]->vt_return_fion_mz() != 0)) {
					++count_ion_sup_intensity;
				}
			}
		}
		if (fpf_scan_DEBUG_MODE == 2) {
			std::cout << "\n\n";
			for (size_t j = 0; j < fpf_fion::st_CONDITION_COUNT_FION_SUP; ++j) {
				std::cout << " " << scan_2_fion_sup[j]->return_fion_intensity();
				std::cout << " " << scan_2_fion_sup[j]->vt_return_fion_mz();
				std::cout << "   ";
			}
			std::cout << "! count_ion_sup_intensity " << count_ion_sup_intensity << "\n";
		}
		return (count_ion_sup_intensity >= fpf_fion::st_CONDITION_FION_SUP);
	};

	size_type scan_fion_sum(scan* c_scan_ptr) {
		// scan_fion_sum() is a size_type return function that performs the primary role of fragment
		// ion summing. The declared iterators nt_fion_ptr_itr_1 and nt_fion_ptr_itr_2 iterate
		// through the fion classes of the scan class pointed to by c_scan_ptr. Should the two
		// iterators not point to the same fion class and have compared fpf_ion::vt_fion_mz, the
		// fragment ion mass-to-charge ratio, within a range of fpf_ion::vt_CONDITION_FION_MZ, the
		// fragment ions are considered suitable for spectral summing. Through spectral summing, the
		// mean mass-to-charge ratio is determined by fpf_ion::vt_return_mean_fion_mz(), the summed
		// intensity by fpf_ion::st_return_sum_fion_intensity(), and the cumulative count of how
		// many fion classes the new fion class is composed of by
		// fpf_ion::st_return_sum_fion_union_count(). These values are stored in a new fion class
		// which is inserted subsequent to the second compared fion class, nt_fion_ptr_itr_2.
		// Following, the compared fion classes are removed from memory. This process continues until all
		// possible fragment ion summations have been completed.
		fion_node_type nt_hold_fion = fion_node_type();
		fion_node_type nt_hold_fion_head_ptr = c_scan_ptr->nt_return_fion_head_ptr();
		fion_data_type d_fion_union = new fpf_fion::fion();
		size_type count_scan_fion_sum = size_type();
		for (fion_node_type nt_fion_ptr_itr_1 = c_scan_ptr->nt_return_fion_head_ptr(); nt_fion_ptr_itr_1 != NULL; nt_fion_ptr_itr_1 = nt_fion_ptr_itr_1->nt_return_up_node()) {
			// nt_fion_ptr_itr_1 iterates through the fion classes of the scan class pointed to by
			// c_scan_ptr. It corresponds to the first fragment ion being compared.
			for (fion_node_type nt_fion_ptr_itr_2 = c_scan_ptr->nt_return_fion_head_ptr(); nt_fion_ptr_itr_2 != NULL; nt_fion_ptr_itr_2 = nt_fion_ptr_itr_2->nt_return_up_node()) {
				// nt_fion_ptr_itr_2 iterates through the fion classes of the scan class pointed to by
				// c_scan_ptr. It corresponds to the second fragment ion being compared.
				if ((nt_fion_ptr_itr_1 != nt_fion_ptr_itr_2) 
					&& fpf_fion::union_fion_mz(nt_fion_ptr_itr_1->dt_return_data(), nt_fion_ptr_itr_2->dt_return_data())) {
					// Tests if the two compared fion classes are -
					// 1. Not the same fion class.
					// 2. Within a mass delta-range defined by fpf_ion::vt_CONDITION_FION_MZ.
					d_fion_union->set_fragment_ion_mz(fpf_fion::vt_return_mean_fion_mz(nt_fion_ptr_itr_1->dt_return_data(), nt_fion_ptr_itr_2->dt_return_data()));
					d_fion_union->set_fragment_ion_intensity(fpf_fion::st_return_sum_fion_intensity(nt_fion_ptr_itr_1->dt_return_data(), nt_fion_ptr_itr_2->dt_return_data()));
					d_fion_union->set_union_count(fpf_fion::st_return_sum_fion_union_count(nt_fion_ptr_itr_1->dt_return_data(), nt_fion_ptr_itr_2->dt_return_data()));
					// Creates a new fion class with values determined by vt_return_mean_fion_mz(),
					// st_return_sum_fion_intensity(), and st_return_sum_fion_union_count().
					if (fpf_scan_DEBUG_MODE == 3) {
						std::cout << "\n" << nt_fion_ptr_itr_1->dt_return_data()->vt_return_fion_mz();
						std::cout << " " << nt_fion_ptr_itr_2->dt_return_data()->vt_return_fion_mz();
						std::cout << " " << fpf_fion::vt_return_mean_fion_mz(nt_fion_ptr_itr_1->dt_return_data(), nt_fion_ptr_itr_2->dt_return_data());
						std::cout << "   ! ";
						for (fion_node_type nt_output_ion_itr = c_scan_ptr->nt_return_fion_head_ptr(); nt_output_ion_itr != NULL; nt_output_ion_itr = nt_output_ion_itr->nt_return_up_node()) {
							std::cout << " " << nt_output_ion_itr->dt_return_data()->vt_return_fion_mz();
						}
					}
					fpf_node::list_insert_up<fion_data_type>(d_fion_union, nt_fion_ptr_itr_2, c_scan_ptr->nt_return_fion_head_ptr(), c_scan_ptr->nt_return_fion_tail_ptr());
					// Inserts new fion class after nt_fion_ptr_itr_2, the second compared fragment ion.
					++count_scan_fion_sum;
					d_fion_union = new fpf_fion::fion();
					if (nt_fion_ptr_itr_1 != nt_hold_fion_head_ptr) {
						// Removes the compared fion classes after creation of
						// the new fion class. The four permutative algorithmic
						// conditions are:
						// 
						// 1. nt_fion_ptr_itr_1 is the first fion class of the
						//    doubly linked list and nt_fion_ptr_itr_2
						//    subsequently follows.
						// 2. nt_fion_ptr_itr_1 is the first fion class of the
						//    doubly linked list and nt_fion_ptr_itr_2 does not
						//    subsequently follow.
						// 3. nt_fion_ptr_itr_1 is not the first fion class of
						//    the doubly linked list and nt_fion_ptr_itr_2
						//    subsequently follows.
						// 4. nt_fion_ptr_itr_1 is not the first fion class of
						//    the doubly linked list and nt_fion_ptr_itr_2 does
						//    not subsequently follow.
						// 
						// During, nt_fion_ptr_itr_1 is pointed to the fion
						// class following the first removed fion class, while
						// nt_fion_ptr_itr_2 is pointed to the first fion class
						// of the doubly linked list (or alternatively, to
						// nt_fion_ptr_itr_1, such that the for loop directive
						// nt_fion_ptr_itr_2 =
						// nt_fion_ptr_itr_2->nt_return_up_node() iterates it to
						// the subsequent fion class). The compared fion classes
						// are removed from memory.
						if (nt_fion_ptr_itr_1->nt_return_up_node() == nt_fion_ptr_itr_2) {
							if (fpf_scan_DEBUG_MODE == 3) {
								std::cout << "   (nt_ion_itr != nt_hold_fion_head_ptr)  (nt_ion_itr->nt_return_up_node() == nt_fion_ptr_itr_2)";
							}
							nt_hold_fion = nt_fion_ptr_itr_1;
							nt_fion_ptr_itr_1 = nt_fion_ptr_itr_1->nt_return_up_node()->nt_return_up_node();
							fpf_node::list_remove<fion_data_type>(nt_hold_fion);
							nt_hold_fion = nt_fion_ptr_itr_2;
							fpf_node::list_remove<fion_data_type>(nt_hold_fion);
							nt_fion_ptr_itr_2 = c_scan_ptr->nt_return_fion_head_ptr();
						}
						else {
							if (fpf_scan_DEBUG_MODE == 3) {
								std::cout << "   (nt_ion_itr != nt_hold_fion_head_ptr)  !(nt_ion_itr->nt_return_up_node() == nt_fion_ptr_itr_2)";
							}
							nt_hold_fion = nt_fion_ptr_itr_1;
							nt_fion_ptr_itr_1 = nt_fion_ptr_itr_1->nt_return_up_node();
							fpf_node::list_remove<fion_data_type>(nt_hold_fion);
							nt_hold_fion = nt_fion_ptr_itr_2;
							fpf_node::list_remove<fion_data_type>(nt_hold_fion);
							nt_fion_ptr_itr_2 = c_scan_ptr->nt_return_fion_head_ptr();
						}
					}
					else {
						if (nt_fion_ptr_itr_1->nt_return_up_node() == nt_fion_ptr_itr_2) {
							if (fpf_scan_DEBUG_MODE == 3) {
								std::cout << "   !(nt_ion_itr != nt_hold_fion_head_ptr)  (nt_ion_itr->nt_return_up_node() == nt_fion_ptr_itr_2)";
							}
							nt_fion_ptr_itr_1 = nt_fion_ptr_itr_1->nt_return_up_node()->nt_return_up_node();
							fpf_node::list_remove_head<fion_data_type>(c_scan_ptr->nt_return_fion_head_ptr());
							fpf_node::list_remove_head<fion_data_type>(c_scan_ptr->nt_return_fion_head_ptr());
							nt_hold_fion_head_ptr = nt_fion_ptr_itr_1;
							nt_fion_ptr_itr_2 = c_scan_ptr->nt_return_fion_head_ptr();
						}
						else {
							if (fpf_scan_DEBUG_MODE == 3) {
								std::cout << "   !(nt_ion_itr != nt_hold_fion_head_ptr)  !(nt_ion_itr->nt_return_up_node() == nt_fion_ptr_itr_2)";
							}
							nt_fion_ptr_itr_1 = nt_fion_ptr_itr_1->nt_return_up_node();
							fpf_node::list_remove_head<fion_data_type>(c_scan_ptr->nt_return_fion_head_ptr());
							// copy constructor here?
							//
							//
							//
							//
							// * * * * *
							//
							//
							//
							//
							nt_hold_fion_head_ptr = nt_fion_ptr_itr_1;
							nt_hold_fion = nt_fion_ptr_itr_2;
							fpf_node::list_remove<fion_data_type>(nt_hold_fion);
							nt_fion_ptr_itr_2 = c_scan_ptr->nt_return_fion_head_ptr();
						}
					}
				}
				else {
					if (fpf_scan_DEBUG_MODE == 3) {
						std::cout << "\n" << nt_fion_ptr_itr_1->dt_return_data()->vt_return_fion_mz() << " " << nt_fion_ptr_itr_2->dt_return_data()->vt_return_fion_mz() << " NULL";
						std::cout << "   ! ";
						for (fion_node_type nt_ion_itr = c_scan_ptr->nt_return_fion_head_ptr(); nt_ion_itr != NULL; nt_ion_itr = nt_ion_itr->nt_return_up_node()) {
							std::cout << " " << nt_ion_itr->dt_return_data()->vt_return_fion_mz();
						}
					}
				}
			}
		}
		if (fpf_scan_DEBUG_MODE == 3) {
			std::cout << "\n* * * * *\n";
			for (fion_node_type nt_ion_itr = c_scan_ptr->nt_return_fion_head_ptr(); nt_ion_itr != NULL; nt_ion_itr = nt_ion_itr->nt_return_up_node()) {
				std::cout << " " << nt_ion_itr->dt_return_data()->vt_return_fion_mz();
			}
			std::cout << "\n";
		}
		return (count_scan_fion_sum);
	};

	inline value_type vt_return_mean_pion_mass(scan* scan_1, scan* scan_2) {
		// vt_return_mean_pion_mass() is a value_type return function that returns the mean mass of
		// two scan classes. This function is called when assigning value to a combined scan class
		// from two scan classes suitable for spectral summing. Previous summing is taken into
		// consideration through st_scan_union_count.
		return (((scan_1->return_scan_union_count() * scan_1->vt_return_pion_mass()) + (scan_2->return_scan_union_count() * scan_2->vt_return_pion_mass())) / (scan_1->return_scan_union_count() + (scan_2->return_scan_union_count())));
	};

	inline value_type vt_return_mean_pion_rt(scan* scan_1, scan* scan_2) {
		// vt_return_mean_pion_rt() is a value_type return function that returns the mean retention time of
		// two scan classes. This function is called when assigning value to a combined scan class
		// from two scan classes suitable for spectral summing. Previous summing is taken into
		// consideration through st_scan_union_count.
		return (((scan_1->return_scan_union_count() * scan_1->vt_return_pion_rt()) + (scan_2->return_scan_union_count() * scan_2->vt_return_pion_rt())) / (scan_1->return_scan_union_count() + (scan_2->return_scan_union_count())));
	};

	inline size_type st_return_sum_scan_union_count(scan* scan_1, scan* scan_2) {
		// st_return_sum_scan_union_count() is a size_type return function that
		// returns the sum of the union count of two scan classes. This function is
		// called when assigning value to a combined scan class from two scan classes
		// suitable for spectral summing. The cumulative value of st_scan_union_count
		// represents the total number of scan classes that have been combined into
		// the new combined scan class.
		return (scan_1->return_scan_union_count() + scan_2->return_scan_union_count());
	};

	inline void set_scan_fion_union(scan*& scan_union, scan* scan_1, scan* scan_2) {
		// set_scan_fion_union() is a void type function that concaternates the doubly linked lists
		// of two fion classes pointed to by two scan classes determined to be suitable for spectral
		// summing. The list from the first scan class is assigned to a new list and the list from
		// the second scan class is concaternated onto this list. Following, the new doubly linked
		// list is summed through a call to scan_fion_sum().
		fion_data_type dt_union_fion_ptr_itr = new fpf_fion::fion;
		for (fion_node_type fion_ptr_itr = scan_1->nt_return_fion_head_ptr(); fion_ptr_itr != NULL; fion_ptr_itr = fion_ptr_itr->nt_return_up_node()) {
			dt_union_fion_ptr_itr = fion_ptr_itr->dt_return_data();
			fpf_node::list_insert_tail<fion_data_type>(dt_union_fion_ptr_itr, scan_union->nt_return_fion_head_ptr(), scan_union->nt_return_fion_tail_ptr());
			dt_union_fion_ptr_itr = new fpf_fion::fion;
		}
		for (fion_node_type fion_ptr_itr = scan_2->nt_return_fion_head_ptr(); fion_ptr_itr != NULL; fion_ptr_itr = fion_ptr_itr->nt_return_up_node()) {
			dt_union_fion_ptr_itr = fion_ptr_itr->dt_return_data();
			fpf_node::list_insert_tail<fion_data_type>(dt_union_fion_ptr_itr, scan_union->nt_return_fion_head_ptr(), scan_union->nt_return_fion_tail_ptr());
			if (fion_ptr_itr->nt_return_up_node() != NULL) {
				dt_union_fion_ptr_itr = new fpf_fion::fion;
			}
		}
		scan_fion_sum(scan_union);
	};
}

#endif