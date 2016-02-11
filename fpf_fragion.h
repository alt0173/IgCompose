/*
 *	File:   fpf_fragion.h
 *	Author: Lukah Dykes
 */

 // --- namespace fpf_fragion class fragion
 // 
 // namespace fpf_fragion contains object definitions for the fragion class. An fragion
 // class declares private members to store the values of a fragment fragion
 // mass-to-charge ratio, detected intensity, and an integer count of the
 // quantity of fragion classes an fragion class is composed of (initially 1). The
 // fpf_fragion function union_fragment_ion_mz() boolean tests if two fragion class
 // mass-to-charge ratios are suitable for spectral summing - A true boolean
 // value calls return_mean_ion_mz_vt() and return_sum_ion_intensity_st() to
 // calculate the mean mass-to-charge ratio and summed intensity of the two fragion
 // classes, taking into consideration previous summing through st_union_count.

#ifndef FPF_FRAGION
#define	FPF_FRAGION
#include <cstdlib> // provides - size_t, NULL

namespace fpf_fragion {
	class fragion {
	public:

		typedef fragion* data_type;
		// Defines fpf_fragion::fragion::data_type as a pointer to a fpf_fragion::fragion class.

		typedef double value_type;
		// Defines fpf_fragion::fragion::value_type as a standard C++ data type.

		typedef size_t size_type;
		// Defines fpf_fragion::fragion::size_type as a size_t type. Requires <cstdlib>.

		typedef bool bool_type;
		// Defines fpf_fragion::fragion::bool_type as a bool type.

		fragion() {
			vt_fragment_ion_mz = value_type();
			st_fragment_ion_intensity = size_type();
			st_union_count = 1;
		};
		// fragion() defines the default constructor for the
		// fpf_fragion::fragion class that initialises member values as ISO type
		// defaults and the value 1 for st_scan_union_count - representing an
		// unsummed scan class.

		~fragion() {
		};
		// ~fragion() defines the default destructor for the
		// fpf_fragion::fragion class.

		//
		//
		//   * * MODIFICATION MEMBER FUNCTIONS * *
		//
		//

		inline void set_fragment_ion_mz(const value_type& vt_new_fragment_ion_mz) {
			vt_fragment_ion_mz = vt_new_fragment_ion_mz;
		};
		// set_fragment_ion_mz() assigns a value_type to vt_fragment_ion_mz.

		inline void set_fragment_ion_intensity(const size_type& st_new_fragment_ion_int) {
			st_fragment_ion_intensity = st_new_fragment_ion_int;
		};
		// set_fragment_ion_intensity() assigns a size_type to st_fragment_ion_intensity.

		inline void set_union_count(size_type st_new_union_count) {
			st_union_count = st_new_union_count;
		};
		// set_union_count() assigns a size_type to st_union_count.

		//
		//
		//   * * PRIVATE MEMBER ACCESS FUNCTIONS * *
		//
		//

		inline value_type vt_return_fragment_ion_mz() const {
			return vt_fragment_ion_mz;
		};
		// vt_return_fragment_ion_mz() returns vt_fragment_ion_mz, the fragment
		// fragion mass-to-charge ratio of the referenced fragion class.

		inline size_type return_fragment_ion_intensity() const {
			return st_fragment_ion_intensity;
		};
		// vt_return_fragment_ion_mz() returns st_fragment_ion_intensity, the
		// fragment fragion detected intensity of the referenced fragion class.

		inline size_type st_return_union_count() const {
			return st_union_count;
		};
		// vt_return_fragment_ion_mz() returns st_union_count, the count of
		// fragment fragion spectra that have been combined into the referenced fragion class.

	private:
		value_type vt_fragment_ion_mz;
		// vt_fragment_ion_mz is a value_type data type. vt_fragment_ion_mz
		// stores the value of a fragment fragion mass-to-charge ratio in an fragion class.

		size_type st_fragment_ion_intensity;
		// st_fragment_ion_intensity is a size_type data type.
		// st_fragment_ion_intensity stores the value of a fragment fragion detected
		// intensity in an fragion class.

		size_type st_union_count;
		// st_union_count is a size_type data type. st_union_count counts the
		// quantity of fragion classes that have been combined to create the current
		// fragion class - an unsummed fragion class has a value of 1, an fragion class
		// having undergone one iteration of summing has a value 2, and onwards.
	};

	//
	//
	//   * * SCOPE VARIABLES * *
	//
	//

	const fragion::value_type vt_CONDITION_FRAGMENT_ION_MZ = 0.025;
	// vt_CONDITION_FRAGMENT_ION_MZ is a value_type with a compile-time or
	// run-time initialised value that defines the fragment fragion mass-to-charge
	// ratio range for spectral summing.

	//
	//
	//   * * FUNCTIONS * *
	//
	//

	inline static fragion::bool_type union_fragment_ion_mz(const fragion::data_type& d_ion_itr_1, const fragion::data_type& d_ion_itr_2) {
		return ((d_ion_itr_1->vt_return_fragment_ion_mz() <= d_ion_itr_2->vt_return_fragment_ion_mz() + vt_CONDITION_FRAGMENT_ION_MZ) && (d_ion_itr_1->vt_return_fragment_ion_mz() >= d_ion_itr_2->vt_return_fragment_ion_mz() - vt_CONDITION_FRAGMENT_ION_MZ));
	};
	// union_fragment_ion_mz() is a bool_type return function that returns true if
	// two compared fragion classes have vt_fragment_ion_mz values within a range of
	// vt_CONDITION_FRAGMENT_ION_MZ. A return of true is indicative that two
	// fragment fragion mass-to-charge ratios are suitable for spectral summing.

	inline fragion::value_type return_mean_ion_mz_vt(fragion* ion_1, fragion* ion_2) {
		return (((ion_1->st_return_union_count() * (ion_1->vt_return_fragment_ion_mz())) + ((ion_2->st_return_union_count()) * (ion_2->vt_return_fragment_ion_mz()))) / (ion_1->st_return_union_count() + (ion_2->st_return_union_count())));
	};
	// return_mean_ion_mz_vt() is a value_type return function that returns the
	// mean mass-to-charge ratio of two fragion classes. This function is called
	// when assigning value to a combined fragion class from two fragion classes
	// suitable for spectral summing. Previous summing is taken into
	// consideration through st_union_count.

	inline fragion::size_type return_sum_ion_intensity_st(fragion* ion_1, fragion* ion_2) {
		return (ion_1->return_fragment_ion_intensity() + ion_2->return_fragment_ion_intensity());
	};
	// return_sum_ion_intensity_st() is a size_type return function that returns
	// the sum of the intensity of two fragion classes. This function is called when
	// assigning value to a combined fragion class from two fragion classes suitable for
	// spectral summing. Previous summing is taken into consideration through st_union_count.

	inline fragion::size_type return_sum_ion_union_count_st(fragion* ion_1, fragion* ion_2) {
		return (ion_1->st_return_union_count() + ion_2->st_return_union_count());
	};
	// return_sum_ion_union_count_st() is a size_type return function that
	// returns the sum of the union count of two fragion classes. This function is
	// called when assigning value to a combined fragion class from two fragion classes
	// suitable for spectral summing. The cumulative value of st_union_count
	// represents the total number of fragion classes that have been combined into
	// the new combined fragion class.
}

#endif
