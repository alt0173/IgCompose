/*
 *	File:   fpf_ion.h
 *	Author: Lukah Dykes
 */

 // --- namespace fpf_ion class fpf_ion::ion
 //
 // namespace fpf_node contains object definitions for the fpf_node::node class.
 // fpf_node::node provides functionality for a doubly linked list, which is
 // templated for any standard C++ data type or an object with a copy
 // constructor and assignment operator.

#ifndef FPF_ION
#define	FPF_ION
#include <cstdlib> // provides - size_t, NULL

namespace fpf_ion {

	class ion {
	public:

		typedef ion* data_type;
		// Defines fpf_ion::ion::data_type as a pointer to a fpf_ion::ion class.

		typedef double value_type;
		// Defines fpf_ion::ion::value_type as any standard C++ data type.

		typedef size_t size_type;
		// Defines fpf_ion::ion::size_type as a size_t type. Requires <cstdlib>.

		typedef bool bool_type;
		// Defines fpf_ion::ion::bool_type as a bool type.

		ion(const value_type& vt_init_fragment_ion_mz = value_type(), const size_type& st_init_fragment_ion_int = size_type(), size_type st_init_union_count = 1, bool bt_init_union_init = bool_type()) {
			vt_fragment_ion_mz = vt_init_fragment_ion_mz;
			st_fragment_ion_intensity = st_init_fragment_ion_int;
			st_union_count = st_init_union_count;
			bt_union_init = bt_init_union_init;
		};
		// Defines a constructor call for fpf_ion::ion that assigns declared
		// parameters as initial values or calls default values as ISO type defaults.

		//
		//
		//   * * MODIFICATION MEMBER FUNCTIONS * *
		//
		//

		inline void set_fragment_ion_mz_vt(const value_type& vt_new_fragment_ion_mz) {
			vt_fragment_ion_mz = vt_new_fragment_ion_mz;
		};
		// Assigns a fpf_ion::ion::value_type to fpf_ion::ion::vt_fragment_ion_mz.

		inline void set_fragment_ion_intensity_st(const size_type& st_new_fragment_ion_int) {
			st_fragment_ion_intensity = st_new_fragment_ion_int;
		};
		// Assigns a fpf_ion::ion::size_type to fpf_ion::ion::st_fragment_ion_intensity.

		inline void set_union_count_st(size_type st_new_union_count) {
			st_union_count = st_new_union_count;
		};
		// Assigns a fpf_ion::ion::size_type to fpf_ion::ion::st_union_count.

		inline void set_init_fragment_ion_union_b(bool_type b_new_union_init) {
			bt_union_init = b_new_union_init;
		};
		// Assigns a fpf_ion::ion::bool_type to fpf_ion::ion::bt_union_init.

		//
		//
		//   * * PRIVATE MEMBER ACCESS FUNCTIONS * *
		//
		//

		inline value_type return_fragment_ion_mz() const {
			return vt_fragment_ion_mz;
		};
		// Returns fpf_ion::ion::vt_fragment_ion_mz.

		inline size_type return_fragment_ion_intensity() const {
			return st_fragment_ion_intensity;
		};
		// Returns fpf_ion::ion::st_fragment_ion_intensity.

		inline size_type return_union_count_st() const {
			return st_union_count;
		};
		// Returns fpf_ion::ion::st_union_count.

		inline bool_type return_union_init_b() const {
			return bt_union_init;
		};
		// Returns fpf_ion::ion::bt_union_init.

	private:
		value_type vt_fragment_ion_mz;
		// fpf_ion::ion::vt_fragment_ion_mz is a fpf_ion::ion::value_type data
		// type. It can be any standard C++ data type. vt_fragment_ion_mz stores
		// the value of a fragment ion mass-to-charge ratio in a fpf_ion::ion class.

		size_type st_fragment_ion_intensity;
		// fpf_ion::ion::st_fragment_ion_intensity is a fpf_ion::ion::size_type
		// data type. st_fragment_ion_intensity stores the value of a fragment
		// ion detected intensity in a fpf_ion::ion class.

		size_type st_union_count;
		// fpf_ion::ion::st_union_count is a fpf_ion::ion::size_type data type.
		// st_union_count counts the quantity of ion classes that have been
		// combined to create the current fpf_ion::ion class - an unsummed ion
		// class has a value of 1, an ion class having undergone one iteration
		// of summing has a value 2, and onwards.

		bool_type bt_union_init;
		// fpf_ion::ion::bt_union_init is a fpf_ion::ion::bool_type data type.
		// bt_union_init is true if the fpf_ion::ion class has undergone an
		// iteration of spectral summing. The default value of bt_union_init is false.
	};

	//
	//
	//   * * FUNCTIONS * *
	//
	//

	const ion::value_type CONDITION_FRAGMENT_ION_MZ = 0.025;
	// fpf_ion::CONDITION_FRAGMENT_ION_MZ is a const ion::value_type with a
	// compile-time or run-time initialised value that defines the fragment ion
	// mass-to-charge ratio range for spectral summing.

	inline static ion::bool_type union_fragment_ion_mz(const ion::data_type& d_ion_itr_1, const ion::data_type& d_ion_itr_2) {
		return ((d_ion_itr_1->return_fragment_ion_mz() <= d_ion_itr_2->return_fragment_ion_mz() + CONDITION_FRAGMENT_ION_MZ) && (d_ion_itr_1->return_fragment_ion_mz() >= d_ion_itr_2->return_fragment_ion_mz() - CONDITION_FRAGMENT_ION_MZ));
	};
	// fpf_ion::union_fragment_ion_mz is a fpf_ion::ion::bool_type return
	// function that returns true if two compared fpf_ion::ion classes have
	// fpf_ion::ion::vt_fragment_ion_mz values within a range of
	// fpf_ion::CONDITION_FRAGMENT_ION_MZ. This function has two primary roles - A return of true is indicative that
	// 1. two fragment ions are consitwo fragment ion mass-to-charge ratios are suitable for spectral summing.

	inline ion::value_type return_mean_ion_mz_vt(ion* ion_1, ion* ion_2) {
		return (((ion_1->return_union_count_st() * (ion_1->return_fragment_ion_mz())) + ((ion_2->return_union_count_st()) * (ion_2->return_fragment_ion_mz()))) / (ion_1->return_union_count_st() + (ion_2->return_union_count_st())));
	};
	//
	//

	inline ion::size_type return_sum_ion_intensity_st(ion* ion_1, ion* ion_2) {
		return (ion_1->return_fragment_ion_intensity() + ion_2->return_fragment_ion_intensity());
	};
	//
	//

	inline ion::size_type return_sum_ion_union_count_st(ion* ion_1, ion* ion_2) {
		return (ion_1->return_union_count_st() + ion_2->return_union_count_st());
	};
	//
	//
}

#endif


//inline static ion::bool_type union_fragment_ion_mz_boundconst(const ion::data_type& d_ion_itr_1, const ion::data_type& d_ion_itr_2) {
//	return (d_ion_itr_1->return_fragment_ion_mz() <= d_ion_itr_2->return_fragment_ion_mz() + (CONDITION_FRAGMENT_ION_MZ * 1.1) && (d_ion_itr_1->return_fragment_ion_mz() >= d_ion_itr_2->return_fragment_ion_mz() - (CONDITION_FRAGMENT_ION_MZ * 1.1)));
//};
//// fpf_ion::union_fragment_ion_mz is a fpf_ion::ion::bool_type return
//// function that returns true if two compared fpf_ion::ion classes have
//// fpf_ion::ion::vt_fragment_ion_mz values within a range of
//// fpf_ion::CONDITION_FRAGMENT_ION_MZ * 1.1. A return of true is indicative that
//// two fragment ion mass-to-charge ratios are suitable for spectral summing.
