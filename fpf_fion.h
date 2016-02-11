/*
 *	File:   fpf_fion.h
 *	Author: Lukah Dykes
 */

 // --- namespace fpf_fion class fion
 // 
 // namespace fpf_fion contains object definitions for the fion class. An fion
 // class declares private members to store the values of a fragment fion
 // mass-to-charge ratio, detected intensity, and an integer count of the
 // quantity of fion classes an fion class is composed of (initially 1). The
 // fpf_fion function union_fragment_ion_mz() boolean tests if two fion class
 // mass-to-charge ratios are suitable for spectral summing - A true boolean
 // value calls return_mean_ion_mz_vt() and return_sum_ion_intensity_st() to
 // calculate the mean mass-to-charge ratio and summed intensity of the two fion
 // classes, taking into consideration previous summing through st_union_count.

#ifndef FPF_FION
#define	FPF_FION
#include <cstdlib> // provides - size_t, NULL

namespace fpf_fion {
	class fion {
	public:

		typedef fion* data_type;
		// Defines fpf_fion::fion::data_type as a pointer to a fpf_fion::fion class.

		typedef double value_type;
		// Defines fpf_fion::fion::value_type as a standard C++ data type.

		typedef size_t size_type;
		// Defines fpf_fion::fion::size_type as a size_t type. Requires <cstdlib>.

		typedef bool bool_type;
		// Defines fpf_fion::fion::bool_type as a bool type.

		fion() {
			vt_fragment_ion_mz = value_type();
			st_fragment_ion_intensity = size_type();
			st_union_count = 1;
		};
		// fion() defines the default constructor for the
		// fpf_fion::fion class that initialises member values as ISO type
		// defaults and the value 1 for st_scan_union_count - representing an
		// unsummed scan class.

		~fion() {
		};
		// ~fion() defines the default destructor for the
		// fpf_fion::fion class.

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
		// fion mass-to-charge ratio of the referenced fion class.

		inline size_type return_fragment_ion_intensity() const {
			return st_fragment_ion_intensity;
		};
		// vt_return_fragment_ion_mz() returns st_fragment_ion_intensity, the
		// fragment fion detected intensity of the referenced fion class.

		inline size_type st_return_union_count() const {
			return st_union_count;
		};
		// vt_return_fragment_ion_mz() returns st_union_count, the count of
		// fragment fion spectra that have been combined into the referenced fion class.

	private:
		value_type vt_fragment_ion_mz;
		// vt_fragment_ion_mz is a value_type data type. vt_fragment_ion_mz
		// stores the value of a fragment fion mass-to-charge ratio in an fion class.

		size_type st_fragment_ion_intensity;
		// st_fragment_ion_intensity is a size_type data type.
		// st_fragment_ion_intensity stores the value of a fragment fion detected
		// intensity in an fion class.

		size_type st_union_count;
		// st_union_count is a size_type data type. st_union_count counts the
		// quantity of fion classes that have been combined to create the current
		// fion class - an unsummed fion class has a value of 1, an fion class
		// having undergone one iteration of summing has a value 2, and onwards.
	};

	//
	//
	//   * * SCOPE VARIABLES * *
	//
	//

	const fion::value_type vt_CONDITION_FRAGMENT_ION_MZ = 0.025;
	// vt_CONDITION_FRAGMENT_ION_MZ is a value_type with a compile-time or
	// run-time initialised value that defines the fragment fion mass-to-charge
	// ratio range for spectral summing.

	//
	//
	//   * * FUNCTIONS * *
	//
	//

	inline static fion::bool_type union_fragment_ion_mz(const fion::data_type& d_ion_itr_1, const fion::data_type& d_ion_itr_2) {
		return ((d_ion_itr_1->vt_return_fragment_ion_mz() <= d_ion_itr_2->vt_return_fragment_ion_mz() + vt_CONDITION_FRAGMENT_ION_MZ) && (d_ion_itr_1->vt_return_fragment_ion_mz() >= d_ion_itr_2->vt_return_fragment_ion_mz() - vt_CONDITION_FRAGMENT_ION_MZ));
	};
	// union_fragment_ion_mz() is a bool_type return function that returns true if
	// two compared fion classes have vt_fragment_ion_mz values within a range of
	// vt_CONDITION_FRAGMENT_ION_MZ. A return of true is indicative that two
	// fragment fion mass-to-charge ratios are suitable for spectral summing.

	inline fion::value_type return_mean_ion_mz_vt(fion* ion_1, fion* ion_2) {
		return (((ion_1->st_return_union_count() * (ion_1->vt_return_fragment_ion_mz())) + ((ion_2->st_return_union_count()) * (ion_2->vt_return_fragment_ion_mz()))) / (ion_1->st_return_union_count() + (ion_2->st_return_union_count())));
	};
	// return_mean_ion_mz_vt() is a value_type return function that returns the
	// mean mass-to-charge ratio of two fion classes. This function is called
	// when assigning value to a combined fion class from two fion classes
	// suitable for spectral summing. Previous summing is taken into
	// consideration through st_union_count.

	inline fion::size_type return_sum_ion_intensity_st(fion* ion_1, fion* ion_2) {
		return (ion_1->return_fragment_ion_intensity() + ion_2->return_fragment_ion_intensity());
	};
	// return_sum_ion_intensity_st() is a size_type return function that returns
	// the sum of the intensity of two fion classes. This function is called when
	// assigning value to a combined fion class from two fion classes suitable for
	// spectral summing. Previous summing is taken into consideration through st_union_count.

	inline fion::size_type return_sum_ion_union_count_st(fion* ion_1, fion* ion_2) {
		return (ion_1->st_return_union_count() + ion_2->st_return_union_count());
	};
	// return_sum_ion_union_count_st() is a size_type return function that
	// returns the sum of the union count of two fion classes. This function is
	// called when assigning value to a combined fion class from two fion classes
	// suitable for spectral summing. The cumulative value of st_union_count
	// represents the total number of fion classes that have been combined into
	// the new combined fion class.
}

#endif
