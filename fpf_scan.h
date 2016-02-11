/*
*	File:   fpf_spectralsum.h
*	Author: Lukah Dykes
*/

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

		typedef fpf_node::node<fpf_fion::fion*>* ion_node_type;
		// Defines ion_node_type as a pointer to a node doubly linked list
		// templated as a pointer to a fion class.

		typedef fpf_fion::fion* ion_data_type;
		// Defines ion_data_type as a pointer to a fion class.

		scan() {
			vt_precursor_mass = value_type();
			vt_precursor_rt = value_type();
			nt_ion_head_ptr = NULL;
			nt_ion_tail_ptr = NULL;
			b_union = bool();
			st_scan_union_count = 1;
		};
		// scan() defines the default constructor for the scan class. It
		// initialises member values as ISO type defaults and a value of 1 for
		// st_scan_union_count (representing an unsummed scan class).

		~scan() {
		};
		// ~scan() defines the default destructor for the scan class.

		//
		//
		// * * MEMBER FUNCTIONS * *
		//
		//

		inline void set_precursor_mass(value_type vt_set_precursor_mass) {
			vt_precursor_mass = vt_set_precursor_mass;
		};
		// set_precursor_mass() assigns a value_type to vt_precursor_mass.

		inline void set_precursor_rt(value_type vt_set_precursor_rt) {
			vt_precursor_rt = vt_set_precursor_rt;
		};
		// set_precursor_rt() assigns a value_type to vt_precursor_rt.

		inline void set_union_n(bool b_new_union) {
			b_union = b_new_union;
		};
		// set_union_n() assigns a value_type to b_union.

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
			return vt_precursor_mass;
		};
		// nt_return_precursor_mass() returns vt_precursor_mass, the precursor
		// mass of the referenced scan class.

		inline const value_type nt_return_precursor_rt() const {
			return vt_precursor_rt;
		};
		// nt_return_precursor_rt() returns vt_precursor_rt, the precursor
		// retention time of the referenced scan class.

		inline ion_node_type& nt_return_ion_head_ptr() {
			return nt_ion_head_ptr;
		};
		// nt_return_ion_head_ptr() returns nt_ion_head_ptr, a pointer to the first fpf_fion::fion class in a doubly linked list. The first fion class contains a pointer to the subsequent 

		inline ion_node_type& nt_return_ion_tail_ptr() {
			return nt_ion_tail_ptr;
		};
		//		Returns a tail pointer to a linked lift of ION classes for the
		//		associated SCAN class. The pointer directs to the head node of
		//		a linked list.

		inline bool& return_union_b() {
			return b_union;
		};
		//
		//

		inline size_type return_scan_union_count() {
			return st_scan_union_count;
		};
		//
		//

	private:
		value_type vt_precursor_mass;
		value_type vt_precursor_rt;
		ion_node_type nt_ion_head_ptr;
		ion_node_type nt_ion_tail_ptr;
		bool b_union;
		size_type st_scan_union_count;
	};

	//
	//
	//   * * SCOPE VARIABLES * *
	//
	//

	int fpf_scan_DEBUG_MODE;
	//
	//

	const scan::size_type CONDITION_FRAGMENT_ION_SUP = 5;
	//
	//

	const scan::value_type CONDITION_PRECURSOR_MASS = 0.025;
	//
	//

	const scan::value_type CONDITION_PRECURSOR_RT = 300;
	//
	//		scan::CONDITION_PRECURSOR_RT defines the delta-range of retention
	//		time to determine if two classes are suitable for spectral summing.
	//		It can be program-defined, or called from an external source.

	const scan::size_type CONDITION_COUNT_FRAGMENT_SUP = 10;
	//
	//

	//
	//
	// * * FUNCTIONS * *
	//
	//

	void set_debug(int set_fpf_scan_DEBUG_MODE) {
		fpf_scan_DEBUG_MODE = set_fpf_scan_DEBUG_MODE;
	}

	inline bool union_precursor_mass(const scan* scan_1, const scan* scan_2) {
		return ((scan_1->nt_return_precursor_mass() <= scan_2->nt_return_precursor_mass() + CONDITION_PRECURSOR_MASS) && (scan_1->nt_return_precursor_mass() >= scan_2->nt_return_precursor_mass() - CONDITION_PRECURSOR_MASS) || scan_1->nt_return_precursor_mass() == scan_2->nt_return_precursor_mass());
	};
	//		Returns TRUE if the precursor masses of two SCAN classes
	//		are within the delta-value range defined by CONDITION_PRECURSOR_MASS.

	inline bool union_precursor_rt(const scan* scan_1, const scan* scan_2) {
		return ((scan_1->nt_return_precursor_rt() <= scan_2->nt_return_precursor_rt() + CONDITION_PRECURSOR_RT) && (scan_1->nt_return_precursor_rt() >= scan_2->nt_return_precursor_rt() - CONDITION_PRECURSOR_RT));
	};
	//		Returns TRUE if the retention times of two SCAN classes are within the
	//		delta-value range defined by CONDITION_RETENTION_TIME.

	bool union_fragment_ion_sup_intensities(scan* scan_1, scan* scan_2) {
		scan::ion_data_type default_ion = new fpf_fion::fion();
		scan::ion_data_type scan_1_fragment_ion_sup[CONDITION_COUNT_FRAGMENT_SUP];
		scan::ion_data_type scan_2_fragment_ion_sup[CONDITION_COUNT_FRAGMENT_SUP];
		scan::ion_data_type hold_fragment_ion_sup_intensity = new fpf_fion::fion();
		scan::size_type count_ion_sup_intensity = scan::size_type();
		for (size_t i = 0; i < CONDITION_COUNT_FRAGMENT_SUP; ++i) {
			for (scan::ion_node_type scan_1_ptr_itr = scan_1->nt_return_ion_head_ptr(); scan_1_ptr_itr != NULL; scan_1_ptr_itr = scan_1_ptr_itr->nt_return_up_node()) {
				if ((i > 0) && (scan_1_ptr_itr->dt_return_data()->return_fragment_ion_intensity() <= scan_1_fragment_ion_sup[i - 1]->return_fragment_ion_intensity()) && (scan_1_ptr_itr->dt_return_data()->return_fragment_ion_intensity() >= hold_fragment_ion_sup_intensity->return_fragment_ion_intensity()) && (scan_1_ptr_itr->dt_return_data()->vt_return_fragment_ion_mz() != scan_1_fragment_ion_sup[i - 1]->vt_return_fragment_ion_mz())) {
					hold_fragment_ion_sup_intensity = scan_1_ptr_itr->dt_return_data();
				}
				if ((i == 0) && (scan_1_ptr_itr->dt_return_data()->return_fragment_ion_intensity() >= hold_fragment_ion_sup_intensity->return_fragment_ion_intensity())) {
					hold_fragment_ion_sup_intensity = scan_1_ptr_itr->dt_return_data();
				}
			}
			scan_1_fragment_ion_sup[i] = hold_fragment_ion_sup_intensity;
			hold_fragment_ion_sup_intensity = default_ion;
		}
		for (size_t i = 0; i < CONDITION_COUNT_FRAGMENT_SUP; ++i) {
			for (scan::ion_node_type scan_2_ptr_itr = scan_2->nt_return_ion_head_ptr(); scan_2_ptr_itr != NULL; scan_2_ptr_itr = scan_2_ptr_itr->nt_return_up_node()) {
				if ((i > 0) && (scan_2_ptr_itr->dt_return_data()->return_fragment_ion_intensity() <= scan_2_fragment_ion_sup[i - 1]->return_fragment_ion_intensity()) && (scan_2_ptr_itr->dt_return_data()->return_fragment_ion_intensity() >= hold_fragment_ion_sup_intensity->return_fragment_ion_intensity()) && (scan_2_ptr_itr->dt_return_data()->vt_return_fragment_ion_mz() != scan_2_fragment_ion_sup[i - 1]->vt_return_fragment_ion_mz())) {
					hold_fragment_ion_sup_intensity = scan_2_ptr_itr->dt_return_data();
				}
				if ((i == 0) && (scan_2_ptr_itr->dt_return_data()->return_fragment_ion_intensity() >= hold_fragment_ion_sup_intensity->return_fragment_ion_intensity())) {
					hold_fragment_ion_sup_intensity = scan_2_ptr_itr->dt_return_data();
				}
			}
			scan_2_fragment_ion_sup[i] = hold_fragment_ion_sup_intensity;
			hold_fragment_ion_sup_intensity = default_ion;
		}
		if (fpf_scan_DEBUG_MODE == 6) {
			std::cout << "\n\n";
		}
		for (size_t i = 0; i < CONDITION_COUNT_FRAGMENT_SUP; ++i) {
			if (fpf_scan_DEBUG_MODE == 6) {
				std::cout << " " << scan_1_fragment_ion_sup[i]->return_fragment_ion_intensity() << " " << scan_1_fragment_ion_sup[i]->vt_return_fragment_ion_mz() << "   ";
			}
			for (size_t j = 0; j < CONDITION_COUNT_FRAGMENT_SUP; ++j) {
				if (fpf_fion::union_fragment_ion_mz(scan_1_fragment_ion_sup[i], scan_2_fragment_ion_sup[j]) && (scan_1_fragment_ion_sup[i]->vt_return_fragment_ion_mz() != 0) && (scan_1_fragment_ion_sup[j]->vt_return_fragment_ion_mz() != 0)) {
					++count_ion_sup_intensity;
				}
			}
		}
		if (fpf_scan_DEBUG_MODE == 6) {
			std::cout << "\n\n";
			for (size_t j = 0; j < CONDITION_COUNT_FRAGMENT_SUP; ++j) {
				std::cout << " " << scan_2_fragment_ion_sup[j]->return_fragment_ion_intensity() << " " << scan_2_fragment_ion_sup[j]->vt_return_fragment_ion_mz() << "   ";
			}
			std::cout << "! count_ion_sup_intensity " << count_ion_sup_intensity << "\n";
			// << "  (count_ion_sup_intensity >= CONDITION_FRAGMENT_ION_SUP) " << (count_ion_sup_intensity >= CONDITION_FRAGMENT_ION_SUP) << "\n";
		}
		return (count_ion_sup_intensity >= CONDITION_FRAGMENT_ION_SUP);
	};
	//
	//

	scan::size_type scan_ion_sum(scan* c_scan_ptr) {
		scan::ion_node_type nt_hold_ion = scan::ion_node_type();
		scan::ion_node_type nt_hold_ion_head_ptr = c_scan_ptr->nt_return_ion_head_ptr();
		scan::ion_data_type d_ion_union = new fpf_fion::fion();
		scan::size_type count_scan_ion_sum = scan::size_type();
		for (scan::ion_node_type nt_ion_itr_1 = c_scan_ptr->nt_return_ion_head_ptr(); nt_ion_itr_1 != NULL; nt_ion_itr_1 = nt_ion_itr_1->nt_return_up_node()) {
			for (scan::ion_node_type nt_ion_itr_2 = c_scan_ptr->nt_return_ion_head_ptr(); nt_ion_itr_2 != NULL; nt_ion_itr_2 = nt_ion_itr_2->nt_return_up_node()) {
				if ((nt_ion_itr_1 != nt_ion_itr_2) && fpf_fion::union_fragment_ion_mz(nt_ion_itr_1->dt_return_data(), nt_ion_itr_2->dt_return_data())) {
					d_ion_union->set_fragment_ion_mz(fpf_fion::return_mean_ion_mz_vt(nt_ion_itr_1->dt_return_data(), nt_ion_itr_2->dt_return_data()));
					d_ion_union->set_fragment_ion_intensity(fpf_fion::return_sum_ion_intensity_st(nt_ion_itr_1->dt_return_data(), nt_ion_itr_2->dt_return_data()));
					d_ion_union->set_union_count(fpf_fion::return_sum_ion_union_count_st(nt_ion_itr_1->dt_return_data(), nt_ion_itr_2->dt_return_data()));
					if (fpf_scan_DEBUG_MODE == 2) {
						std::cout << "\n" << nt_ion_itr_1->dt_return_data()->vt_return_fragment_ion_mz() << " " << nt_ion_itr_2->dt_return_data()->vt_return_fragment_ion_mz() << " " << fpf_fion::return_mean_ion_mz_vt(nt_ion_itr_1->dt_return_data(), nt_ion_itr_2->dt_return_data());
						std::cout << "   ! ";
						for (scan::ion_node_type nt_output_ion_itr = c_scan_ptr->nt_return_ion_head_ptr(); nt_output_ion_itr != NULL; nt_output_ion_itr = nt_output_ion_itr->nt_return_up_node()) {
							std::cout << " " << nt_output_ion_itr->dt_return_data()->vt_return_fragment_ion_mz();
						}
					}
					fpf_node::list_insert_up<scan::ion_data_type>(d_ion_union, nt_ion_itr_2, c_scan_ptr->nt_return_ion_head_ptr(), c_scan_ptr->nt_return_ion_tail_ptr());
					++count_scan_ion_sum;
					d_ion_union = new fpf_fion::fion();
					if (nt_ion_itr_1 != nt_hold_ion_head_ptr) {
						if (nt_ion_itr_1->nt_return_up_node() == nt_ion_itr_2) {
							if (fpf_scan_DEBUG_MODE == 3) {
								std::cout << "   (nt_ion_itr != nt_hold_ion_head_ptr)  (nt_ion_itr->nt_return_up_node() == nt_ion_itr_2)";
							}
							nt_hold_ion = nt_ion_itr_1;
							nt_ion_itr_1 = nt_ion_itr_1->nt_return_up_node()->nt_return_up_node();
							fpf_node::list_remove<scan::ion_data_type>(nt_hold_ion);
							nt_hold_ion = nt_ion_itr_2;
							fpf_node::list_remove<scan::ion_data_type>(nt_hold_ion);
							nt_ion_itr_2 = c_scan_ptr->nt_return_ion_head_ptr();
						}
						else {
							if (fpf_scan_DEBUG_MODE == 3) {
								std::cout << "   (nt_ion_itr != nt_hold_ion_head_ptr)  !(nt_ion_itr->nt_return_up_node() == nt_ion_itr_2)";
							}
							nt_hold_ion = nt_ion_itr_1;
							nt_ion_itr_1 = nt_ion_itr_1->nt_return_up_node();
							fpf_node::list_remove<scan::ion_data_type>(nt_hold_ion);
							nt_hold_ion = nt_ion_itr_2;
							fpf_node::list_remove<scan::ion_data_type>(nt_hold_ion);
							nt_ion_itr_2 = c_scan_ptr->nt_return_ion_head_ptr();
						}
					}
					else {
						if (nt_ion_itr_1->nt_return_up_node() == nt_ion_itr_2) {
							if (fpf_scan_DEBUG_MODE == 3) {
								std::cout << "   !(nt_ion_itr != nt_hold_ion_head_ptr)  (nt_ion_itr->nt_return_up_node() == nt_ion_itr_2)";
							}
							nt_ion_itr_1 = nt_ion_itr_1->nt_return_up_node()->nt_return_up_node();
							fpf_node::list_remove_head<scan::ion_data_type>(c_scan_ptr->nt_return_ion_head_ptr());
							fpf_node::list_remove_head<scan::ion_data_type>(c_scan_ptr->nt_return_ion_head_ptr());
							nt_hold_ion_head_ptr = nt_ion_itr_1;
							nt_ion_itr_2 = c_scan_ptr->nt_return_ion_head_ptr();
						}
						else {
							if (fpf_scan_DEBUG_MODE == 3) {
								std::cout << "   !(nt_ion_itr != nt_hold_ion_head_ptr)  !(nt_ion_itr->nt_return_up_node() == nt_ion_itr_2)";
							}
							nt_ion_itr_1 = nt_ion_itr_1->nt_return_up_node();
							fpf_node::list_remove_head<scan::ion_data_type>(c_scan_ptr->nt_return_ion_head_ptr());
							nt_hold_ion_head_ptr = nt_ion_itr_1;
							nt_hold_ion = nt_ion_itr_2;
							fpf_node::list_remove<scan::ion_data_type>(nt_hold_ion);
							nt_ion_itr_2 = c_scan_ptr->nt_return_ion_head_ptr();
						}
					}
				}
				else {
					if (fpf_scan_DEBUG_MODE == 2) {
						std::cout << "\n" << nt_ion_itr_1->dt_return_data()->vt_return_fragment_ion_mz() << " " << nt_ion_itr_2->dt_return_data()->vt_return_fragment_ion_mz() << " NULL";
						std::cout << "   ! ";
						for (scan::ion_node_type nt_ion_itr = c_scan_ptr->nt_return_ion_head_ptr(); nt_ion_itr != NULL; nt_ion_itr = nt_ion_itr->nt_return_up_node()) {
							std::cout << " " << nt_ion_itr->dt_return_data()->vt_return_fragment_ion_mz();
						}
					}
				}
			}
		}
		if (fpf_scan_DEBUG_MODE == 2) {
			std::cout << "\n* * * * *\n";
			for (scan::ion_node_type nt_ion_itr = c_scan_ptr->nt_return_ion_head_ptr(); nt_ion_itr != NULL; nt_ion_itr = nt_ion_itr->nt_return_up_node()) {
				std::cout << " " << nt_ion_itr->dt_return_data()->vt_return_fragment_ion_mz();
			}
			std::cout << "\n";
		}
		return (count_scan_ion_sum);
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

	inline void set_scan_ion_union(scan*& scan_union, scan* scan_1, scan* scan_2) {
		scan::ion_data_type dt_new_ion_head_ptr = new fpf_fion::fion;
		for (scan::ion_node_type ion_ptr_itr = scan_1->nt_return_ion_head_ptr(); ion_ptr_itr != NULL; ion_ptr_itr = ion_ptr_itr->nt_return_up_node()) {
			dt_new_ion_head_ptr = ion_ptr_itr->dt_return_data();
			fpf_node::list_insert_tail<scan::ion_data_type>(dt_new_ion_head_ptr, scan_union->nt_return_ion_head_ptr(), scan_union->nt_return_ion_tail_ptr());
			dt_new_ion_head_ptr = new fpf_fion::fion;
		}
		for (scan::ion_node_type ion_ptr_itr = scan_2->nt_return_ion_head_ptr(); ion_ptr_itr != NULL; ion_ptr_itr = ion_ptr_itr->nt_return_up_node()) {
			dt_new_ion_head_ptr = ion_ptr_itr->dt_return_data();
			fpf_node::list_insert_tail<scan::ion_data_type>(dt_new_ion_head_ptr, scan_union->nt_return_ion_head_ptr(), scan_union->nt_return_ion_tail_ptr());
			if (ion_ptr_itr->nt_return_up_node() != NULL) {
				dt_new_ion_head_ptr = new fpf_fion::fion;
			}
		}
		scan_ion_sum(scan_union);
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
