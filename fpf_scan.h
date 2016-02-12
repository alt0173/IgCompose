// * * fpf_scan.h * *
// 
// Lukah Dykes - Flinders Proteomics Facility - 2016
// 
// * * * * *

#ifndef FPF_SCAN
#define	FPF_SCAN
#include <cstdlib> // provides - size_t, NULL
#include <iostream> // provides - std::cin, std::cout
#include "fpf_node.h"
#include "fpf_fion.h"

namespace fpf_scan {
	class scan {
	public:

		typedef double value_type;
		// Defines value_type as a standard C++ data type.

		typedef size_t size_type;
		// Defines size_type as a size_t type. Requires <cstdlib>.

		typedef fpf_node::node<fpf_fion::fion*>* fion_node_type;
		/*
		*
		*
		*/
		// Defines fion_node_type as a pointer to a doubly linked list
		// templated as a pointer to a fion class.

		typedef fpf_fion::fion* fion_data_type;
		// Defines fion_data_type as a pointer to a fion class.

		typedef bool bool_type;
		// Defines fpf_scan::scan::bool_type as a bool type.

		scan() {
			vt_pion_mass = value_type();
			vt_pion_rt = value_type();
			nt_fion_head_ptr = NULL;
			nt_fion_tail_ptr = NULL;
			st_scan_union_count = 1;
		};
		// scan() defines the default constructor for the scan class. It
		// initialises member values as ISO type defaults and a value of 1 for
		// st_scan_union_count (representing an unsummed scan class).

		~scan() {
			fpf_node::list_remove_all<fion_data_type>(nt_fion_head_ptr);
		};
		// ~scan() defines the default destructor for the scan class.

		//
		//
		// * * MEMBER FUNCTIONS * *
		//
		//

		inline void set_pion_mass(value_type vt_set_precursor_mass) {
			vt_pion_mass = vt_set_precursor_mass;
		};
		// set_pion_mass() assigns a value_type to vt_pion_mass.

		inline void set_pion_rt(value_type vt_set_precursor_rt) {
			vt_pion_rt = vt_set_precursor_rt;
		};
		// set_pion_rt() assigns a value_type to vt_pion_rt.

		inline void set_scan_union_count(size_type st_scan_union_cout) {
			st_scan_union_count = st_scan_union_cout;
		};
		// set_scan_union_count() assigns a value_type to st_scan_union_count.

		//
		//
		// * * CONSTANT MEMBER FUNCTIONS * *
		//
		//

		inline const value_type nt_return_precursor_mass() const {
			return vt_pion_mass;
		};
		/*
		*
		*
		*
		*/
		// nt_return_precursor_mass() references(does it?) the value_type vt_pion_mass, the precursor
		// mass of the referenced scan class.

		inline const value_type nt_return_precursor_rt() const {
			return vt_pion_rt;
		};
		// nt_return_precursor_rt() returns vt_pion_rt, the precursor
		// retention time of the referenced scan class.

		inline fion_node_type& nt_return_fion_head_ptr() {
			return nt_fion_head_ptr;
		};
		// nt_return_fion_head_ptr() returns nt_fion_head_ptr, a pointer to the
		// first fpf_fion::fion class in a doubly linked list as defined in
		// fpf_node. Collectively the nodes of the list represent the fragment
		// ions of a scan.

		inline fion_node_type& nt_return_fion_tail_ptr() {
			return nt_fion_tail_ptr;
		};
		// nt_return_fion_tail_ptr() returns nt_fion_tail_ptr, a pointer to the
		// last fpf_fion::fion class in a doubly linked list as defined in
		// fpf_node. Collectively the nodes of the list represent the fragment
		// ions of a scan.

		inline size_type return_scan_union_count() {
			return st_scan_union_count;
		};
		// return_scan_union_count() returns st_scan_union_count, the count of
		// how scan classes have been combined into the referenced scan class.
		// An unsummed scan class has a value of 1, a scan class having
		// undergone one iteration of summing has a value 2, and onwards.

	private:
		value_type vt_pion_mass;
		// vt_pion_mass is a value_type that stores the value of the
		// precursor ion mass for the referenced scan class.

		value_type vt_pion_rt;
		// vt_pion_rt is a value_type that stores the value of the
		// precursor ion retention time for the referenced scan class.

		fion_node_type nt_fion_head_ptr;
		// vt_pion_rt is an fion_node_type that stores a pointer to the first
		// fpf_fion::fion class in a doubly linked list as defined in fpf_node.
		// Collectively the nodes of the list represent the fragment ions of a scan.

		fion_node_type nt_fion_tail_ptr;
		// vt_pion_rt is an fion_node_type that stores a pointer to the last
		// fpf_fion::fion class in a doubly linked list as defined in fpf_node.
		// Collectively the nodes of the list represent the fragment ions of a scan.

		size_type st_scan_union_count;
		// st_union_count is a size_type data type that stores the quantity of
		// fion classes that have been combined to create the referenced fion
		// class. An unsummed fion class has a value of 1, a fion class having
		// undergone one iteration of summing has a value 2, and onwards.
	};

	//
	//
	//   * * NAMESPACE VARIABLES * *
	//
	//

	int fpf_scan_DEBUG_MODE;
	//
	//

	const scan::value_type CONDITION_PION_MASS = 0.025;
	//
	//

	const scan::value_type CONDITION_PION_RT = 300;
	//
	//		scan::CONDITION_PION_RT defines the delta-range of retention
	//		time to determine if two classes are suitable for spectral summing.
	//		It can be program-defined, or called from an external source.

	//
	//
	// * * NAMESPACE FUNCTIONS * *
	//
	//

	void set_debug(int set_fpf_scan_DEBUG_MODE) {
		fpf_scan_DEBUG_MODE = set_fpf_scan_DEBUG_MODE;
	}
	// set_debug() assigns a integer value to fpf_scan_DEBUG_MODE. The value of
	// fpf_scan_DEBUG_MODE determines output for the debug mode. The default
	// value is 0. Debug mode values for fpf_scan are:
	// 6. output fion class test for spectral summing
	// 7. output fion class test for spectral summing with explicit boolean test
	// * Small (<5 scan class) test files are recommended.

	inline scan::bool_type union_precursor_mass(const scan* scan_1, const scan* scan_2) {
		return ((scan_1->nt_return_precursor_mass() <= scan_2->nt_return_precursor_mass() + CONDITION_PION_MASS) && (scan_1->nt_return_precursor_mass() >= scan_2->nt_return_precursor_mass() - CONDITION_PION_MASS) || scan_1->nt_return_precursor_mass() == scan_2->nt_return_precursor_mass());
	};
	// union_precursor_mass() is a boolean 

	inline scan::bool_type union_precursor_rt(const scan* scan_1, const scan* scan_2) {
		return ((scan_1->nt_return_precursor_rt() <= scan_2->nt_return_precursor_rt() + CONDITION_PION_RT) && (scan_1->nt_return_precursor_rt() >= scan_2->nt_return_precursor_rt() - CONDITION_PION_RT));
	};
	//		Returns TRUE if the retention times of two SCAN classes are within the
	//		delta-value range defined by CONDITION_RETENTION_TIME.

	scan::bool_type union_fragment_ion_sup_intensities(scan* scan_1, scan* scan_2) {
		scan::fion_data_type default_ion = new fpf_fion::fion();
		scan::fion_data_type scan_1_fion_sup[fpf_fion::st_CONDITION_COUNT_FION_SUP];
		scan::fion_data_type scan_2_fion_sup[fpf_fion::st_CONDITION_COUNT_FION_SUP];
		scan::fion_data_type hold_fion_sup_intensity = new fpf_fion::fion();
		scan::size_type count_ion_sup_intensity = scan::size_type();
		for (size_t i = 0; i < fpf_fion::st_CONDITION_COUNT_FION_SUP; ++i) {
			for (scan::fion_node_type scan_1_ptr_itr = scan_1->nt_return_fion_head_ptr(); scan_1_ptr_itr != NULL; scan_1_ptr_itr = scan_1_ptr_itr->nt_return_up_node()) {
				if ((i > 0) && (scan_1_ptr_itr->dt_return_data()->return_fion_intensity() <= scan_1_fion_sup[i - 1]->return_fion_intensity()) && (scan_1_ptr_itr->dt_return_data()->return_fion_intensity() >= hold_fion_sup_intensity->return_fion_intensity()) && (scan_1_ptr_itr->dt_return_data()->vt_return_fion_mz() != scan_1_fion_sup[i - 1]->vt_return_fion_mz())) {
					hold_fion_sup_intensity = scan_1_ptr_itr->dt_return_data();
				}
				if ((i == 0) && (scan_1_ptr_itr->dt_return_data()->return_fion_intensity() >= hold_fion_sup_intensity->return_fion_intensity())) {
					hold_fion_sup_intensity = scan_1_ptr_itr->dt_return_data();
				}
			}
			scan_1_fion_sup[i] = hold_fion_sup_intensity;
			hold_fion_sup_intensity = default_ion;
		}
		for (size_t i = 0; i < fpf_fion::st_CONDITION_COUNT_FION_SUP; ++i) {
			for (scan::fion_node_type scan_2_ptr_itr = scan_2->nt_return_fion_head_ptr(); scan_2_ptr_itr != NULL; scan_2_ptr_itr = scan_2_ptr_itr->nt_return_up_node()) {
				if ((i > 0) && (scan_2_ptr_itr->dt_return_data()->return_fion_intensity() <= scan_2_fion_sup[i - 1]->return_fion_intensity()) && (scan_2_ptr_itr->dt_return_data()->return_fion_intensity() >= hold_fion_sup_intensity->return_fion_intensity()) && (scan_2_ptr_itr->dt_return_data()->vt_return_fion_mz() != scan_2_fion_sup[i - 1]->vt_return_fion_mz())) {
					hold_fion_sup_intensity = scan_2_ptr_itr->dt_return_data();
				}
				if ((i == 0) && (scan_2_ptr_itr->dt_return_data()->return_fion_intensity() >= hold_fion_sup_intensity->return_fion_intensity())) {
					hold_fion_sup_intensity = scan_2_ptr_itr->dt_return_data();
				}
			}
			scan_2_fion_sup[i] = hold_fion_sup_intensity;
			hold_fion_sup_intensity = default_ion;
		}
		if (fpf_scan_DEBUG_MODE == 6) {
			std::cout << "\n\n";
		}
		for (size_t i = 0; i < fpf_fion::st_CONDITION_COUNT_FION_SUP; ++i) {
			if (fpf_scan_DEBUG_MODE == 6) {
				std::cout << " " << scan_1_fion_sup[i]->return_fion_intensity() << " " << scan_1_fion_sup[i]->vt_return_fion_mz() << "   ";
			}
			for (size_t j = 0; j < fpf_fion::st_CONDITION_COUNT_FION_SUP; ++j) {
				if (fpf_fion::union_fragment_fion_mz(scan_1_fion_sup[i], scan_2_fion_sup[j]) && (scan_1_fion_sup[i]->vt_return_fion_mz() != 0) && (scan_1_fion_sup[j]->vt_return_fion_mz() != 0)) {
					++count_ion_sup_intensity;
				}
			}
		}
		if (fpf_scan_DEBUG_MODE == 6) {
			std::cout << "\n\n";
			for (size_t j = 0; j < fpf_fion::st_CONDITION_COUNT_FION_SUP; ++j) {
				std::cout << " " << scan_2_fion_sup[j]->return_fion_intensity() << " " << scan_2_fion_sup[j]->vt_return_fion_mz() << "   ";
			}
			std::cout << "! count_ion_sup_intensity " << count_ion_sup_intensity << "\n";
			// << "  (count_ion_sup_intensity >= st_CONDITION_FION_SUP) " << (count_ion_sup_intensity >= st_CONDITION_FION_SUP) << "\n";
		}
		return (count_ion_sup_intensity >= fpf_fion::st_CONDITION_FION_SUP);
	};
	//
	//

	scan::size_type scan_fion_sum(scan* c_scan_ptr) {
		scan::fion_node_type nt_hold_fion = scan::fion_node_type();
		scan::fion_node_type nt_hold_fion_head_ptr = c_scan_ptr->nt_return_fion_head_ptr();
		scan::fion_data_type d_fion_union = new fpf_fion::fion();
		scan::size_type count_scan_fion_sum = scan::size_type();
		for (scan::fion_node_type nt_fion_itr_1 = c_scan_ptr->nt_return_fion_head_ptr(); nt_fion_itr_1 != NULL; nt_fion_itr_1 = nt_fion_itr_1->nt_return_up_node()) {
			for (scan::fion_node_type nt_fion_itr_2 = c_scan_ptr->nt_return_fion_head_ptr(); nt_fion_itr_2 != NULL; nt_fion_itr_2 = nt_fion_itr_2->nt_return_up_node()) {
				if ((nt_fion_itr_1 != nt_fion_itr_2) && fpf_fion::union_fragment_fion_mz(nt_fion_itr_1->dt_return_data(), nt_fion_itr_2->dt_return_data())) {
					d_fion_union->set_fragment_ion_mz(fpf_fion::return_mean_fion_mz_vt(nt_fion_itr_1->dt_return_data(), nt_fion_itr_2->dt_return_data()));
					d_fion_union->set_fragment_ion_intensity(fpf_fion::return_sum_ion_intensity_st(nt_fion_itr_1->dt_return_data(), nt_fion_itr_2->dt_return_data()));
					d_fion_union->set_union_count(fpf_fion::return_sum_fion_union_count_st(nt_fion_itr_1->dt_return_data(), nt_fion_itr_2->dt_return_data()));
					if (fpf_scan_DEBUG_MODE == 2) {
						std::cout << "\n" << nt_fion_itr_1->dt_return_data()->vt_return_fion_mz() << " " << nt_fion_itr_2->dt_return_data()->vt_return_fion_mz() << " " << fpf_fion::return_mean_fion_mz_vt(nt_fion_itr_1->dt_return_data(), nt_fion_itr_2->dt_return_data());
						std::cout << "   ! ";
						for (scan::fion_node_type nt_output_ion_itr = c_scan_ptr->nt_return_fion_head_ptr(); nt_output_ion_itr != NULL; nt_output_ion_itr = nt_output_ion_itr->nt_return_up_node()) {
							std::cout << " " << nt_output_ion_itr->dt_return_data()->vt_return_fion_mz();
						}
					}
					fpf_node::list_insert_up<scan::fion_data_type>(d_fion_union, nt_fion_itr_2, c_scan_ptr->nt_return_fion_head_ptr(), c_scan_ptr->nt_return_fion_tail_ptr());
					++count_scan_fion_sum;
					d_fion_union = new fpf_fion::fion();
					if (nt_fion_itr_1 != nt_hold_fion_head_ptr) {
						if (nt_fion_itr_1->nt_return_up_node() == nt_fion_itr_2) {
							if (fpf_scan_DEBUG_MODE == 3) {
								std::cout << "   (nt_ion_itr != nt_hold_fion_head_ptr)  (nt_ion_itr->nt_return_up_node() == nt_fion_itr_2)";
							}
							nt_hold_fion = nt_fion_itr_1;
							nt_fion_itr_1 = nt_fion_itr_1->nt_return_up_node()->nt_return_up_node();
							fpf_node::list_remove<scan::fion_data_type>(nt_hold_fion);
							nt_hold_fion = nt_fion_itr_2;
							fpf_node::list_remove<scan::fion_data_type>(nt_hold_fion);
							nt_fion_itr_2 = c_scan_ptr->nt_return_fion_head_ptr();
						}
						else {
							if (fpf_scan_DEBUG_MODE == 3) {
								std::cout << "   (nt_ion_itr != nt_hold_fion_head_ptr)  !(nt_ion_itr->nt_return_up_node() == nt_fion_itr_2)";
							}
							nt_hold_fion = nt_fion_itr_1;
							nt_fion_itr_1 = nt_fion_itr_1->nt_return_up_node();
							fpf_node::list_remove<scan::fion_data_type>(nt_hold_fion);
							nt_hold_fion = nt_fion_itr_2;
							fpf_node::list_remove<scan::fion_data_type>(nt_hold_fion);
							nt_fion_itr_2 = c_scan_ptr->nt_return_fion_head_ptr();
						}
					}
					else {
						if (nt_fion_itr_1->nt_return_up_node() == nt_fion_itr_2) {
							if (fpf_scan_DEBUG_MODE == 3) {
								std::cout << "   !(nt_ion_itr != nt_hold_fion_head_ptr)  (nt_ion_itr->nt_return_up_node() == nt_fion_itr_2)";
							}
							nt_fion_itr_1 = nt_fion_itr_1->nt_return_up_node()->nt_return_up_node();
							fpf_node::list_remove_head<scan::fion_data_type>(c_scan_ptr->nt_return_fion_head_ptr());
							fpf_node::list_remove_head<scan::fion_data_type>(c_scan_ptr->nt_return_fion_head_ptr());
							nt_hold_fion_head_ptr = nt_fion_itr_1;
							nt_fion_itr_2 = c_scan_ptr->nt_return_fion_head_ptr();
						}
						else {
							if (fpf_scan_DEBUG_MODE == 3) {
								std::cout << "   !(nt_ion_itr != nt_hold_fion_head_ptr)  !(nt_ion_itr->nt_return_up_node() == nt_fion_itr_2)";
							}
							nt_fion_itr_1 = nt_fion_itr_1->nt_return_up_node();
							fpf_node::list_remove_head<scan::fion_data_type>(c_scan_ptr->nt_return_fion_head_ptr());
							nt_hold_fion_head_ptr = nt_fion_itr_1;
							nt_hold_fion = nt_fion_itr_2;
							fpf_node::list_remove<scan::fion_data_type>(nt_hold_fion);
							nt_fion_itr_2 = c_scan_ptr->nt_return_fion_head_ptr();
						}
					}
				}
				else {
					if (fpf_scan_DEBUG_MODE == 2) {
						std::cout << "\n" << nt_fion_itr_1->dt_return_data()->vt_return_fion_mz() << " " << nt_fion_itr_2->dt_return_data()->vt_return_fion_mz() << " NULL";
						std::cout << "   ! ";
						for (scan::fion_node_type nt_ion_itr = c_scan_ptr->nt_return_fion_head_ptr(); nt_ion_itr != NULL; nt_ion_itr = nt_ion_itr->nt_return_up_node()) {
							std::cout << " " << nt_ion_itr->dt_return_data()->vt_return_fion_mz();
						}
					}
				}
			}
		}
		if (fpf_scan_DEBUG_MODE == 2) {
			std::cout << "\n* * * * *\n";
			for (scan::fion_node_type nt_ion_itr = c_scan_ptr->nt_return_fion_head_ptr(); nt_ion_itr != NULL; nt_ion_itr = nt_ion_itr->nt_return_up_node()) {
				std::cout << " " << nt_ion_itr->dt_return_data()->vt_return_fion_mz();
			}
			std::cout << "\n";
		}
		return (count_scan_fion_sum);
	};
	//
	//

	inline scan::value_type return_mean_scan_mass_vt(scan* scan_1, scan* scan_2) {
		return (((scan_1->return_scan_union_count() * scan_1->nt_return_precursor_mass()) + (scan_2->return_scan_union_count() * scan_2->nt_return_precursor_mass())) / (scan_1->return_scan_union_count() + (scan_2->return_scan_union_count())));
	};
	//
	//

	inline scan::value_type return_mean_scan_rt_vt(scan* scan_1, scan* scan_2) {
		return (((scan_1->return_scan_union_count() * scan_1->nt_return_precursor_rt()) + (scan_2->return_scan_union_count() * scan_2->nt_return_precursor_rt())) / (scan_1->return_scan_union_count() + (scan_2->return_scan_union_count())));
	};
	//
	//

	inline void set_scan_fion_union(scan*& scan_union, scan* scan_1, scan* scan_2) {
		scan::fion_data_type dt_union_fion_ptr_itr = new fpf_fion::fion;
		for (scan::fion_node_type fion_ptr_itr = scan_1->nt_return_fion_head_ptr(); fion_ptr_itr != NULL; fion_ptr_itr = fion_ptr_itr->nt_return_up_node()) {
			dt_union_fion_ptr_itr = fion_ptr_itr->dt_return_data();
			fpf_node::list_insert_tail<scan::fion_data_type>(dt_union_fion_ptr_itr, scan_union->nt_return_fion_head_ptr(), scan_union->nt_return_fion_tail_ptr());
			dt_union_fion_ptr_itr = new fpf_fion::fion;
		}
		for (scan::fion_node_type fion_ptr_itr = scan_2->nt_return_fion_head_ptr(); fion_ptr_itr != NULL; fion_ptr_itr = fion_ptr_itr->nt_return_up_node()) {
			dt_union_fion_ptr_itr = fion_ptr_itr->dt_return_data();
			fpf_node::list_insert_tail<scan::fion_data_type>(dt_union_fion_ptr_itr, scan_union->nt_return_fion_head_ptr(), scan_union->nt_return_fion_tail_ptr());
			if (fion_ptr_itr->nt_return_up_node() != NULL) {
				dt_union_fion_ptr_itr = new fpf_fion::fion;
			}
		}
		scan_fion_sum(scan_union);
	};
	//
	//

	inline scan::size_type return_sum_scan_union_count_st(scan* scan_1, scan* scan_2) {
		return (scan_1->return_scan_union_count() + scan_2->return_scan_union_count());
	};
	//
	//
}

#endif
