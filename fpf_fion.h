// * * fpf_fion.h * *
// 
// Lukah Dykes - Flinders Proteomics Facility - 2016
// 
// * * * * *

 // --- namespace fpf_fion class fion
 // 
 // namespace fpf_fion contains object definitions for the fion class. An fion
 // class declares private members to store the values of a fragment fion
 // mass-to-charge ratio, detected intensity, and an integer count of the
 // quantity of fion classes an fion class is composed of (initially 1). The
 // fpf_fion function union_fragment_fion_mz() boolean tests if two fion class
 // mass-to-charge ratios are suitable for spectral summing - A true boolean
 // value calls return_mean_fion_mz_vt() and return_sum_ion_intensity_st() to
 // calculate the mean mass-to-charge ratio and summed intensity of the two fion
 // classes, taking into consideration previous summing through st_union_count.

#ifndef FPF_FION
#define	FPF_FION
#include <cstdlib> // provides - size_t, NULL

namespace fpf_fion {
	class fion {
	public:

		typedef double value_type;
		// Defines fpf_fion::fion::value_type as a standard C++ data type.

		typedef size_t size_type;
		// Defines fpf_fion::fion::size_type as a size_t type. Requires <cstdlib>.

		typedef fion* data_type;
		// Defines fpf_fion::fion::data_type as a pointer to a fpf_fion::fion class.

		typedef bool bool_type;
		// Defines fpf_fion::fion::bool_type as a bool type.

		fion() {
			vt_fion_mz = value_type();
			st_fion_intensity = size_type();
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

		inline void set_fragment_ion_mz(const value_type& vt_new_fion_mz) {
			vt_fion_mz = vt_new_fion_mz;
		};
		// set_fragment_ion_mz() assigns a value_type to vt_fion_mz.

		inline void set_fragment_ion_intensity(const size_type& st_new_fion_int) {
			st_fion_intensity = st_new_fion_int;
		};
		// set_fragment_ion_intensity() assigns a size_type to st_fion_intensity.

		inline void set_union_count(size_type st_new_union_count) {
			st_union_count = st_new_union_count;
		};
		// set_union_count() assigns a size_type to st_union_count.

		//
		//
		//   * * PRIVATE MEMBER ACCESS FUNCTIONS * *
		//
		//

		inline value_type vt_return_fion_mz() const {
			return vt_fion_mz;
		};
		// vt_return_fion_mz() returns vt_fion_mz, the fragment
		// fion mass-to-charge ratio of the referenced fion class.

		inline size_type return_fion_intensity() const {
			return st_fion_intensity;
		};
		// vt_return_fion_mz() returns st_fion_intensity, the
		// fragment fion detected intensity of the referenced fion class.

		inline size_type st_return_union_count() const {
			return st_union_count;
		};
		// vt_return_fion_mz() returns st_union_count, the count of
		// fragment ion spectra that have been combined into the referenced fion class.

	private:
		value_type vt_fion_mz;
		// vt_fion_mz is a value_type data type that stores the value of
		// a fragment ion mass-to-charge ratio in the referenced fion class.

		size_type st_fion_intensity;
		// st_fion_intensity is a size_type data type that stores the
		// value of a fragment ion detected intensity in the referenced fion class.

		size_type st_union_count;
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

	const fion::value_type vt_CONDITION_FION_MZ = 0.025;
	// vt_CONDITION_FION_MZ is a value_type with a compile-time or
	// run-time initialised value that defines the fragment ion mass-to-charge
	// ratio range for spectral summing.

	const fion::size_type st_CONDITION_FION_SUP = 5;
	// st_CONDITION_FION_SUP is a size_type with a compile-time or run-time
	// initialised value that defines the required quantity of the
	// st_CONDITION_COUNT_FION_SUP most intense fragment ions in a
	// fpf_scan::scan class that match the the st_CONDITION_COUNT_FION_SUP most
	// intense fragment ions of a compared fpf_scan::scan class to be suitable
	// for spectral summing. Fragment ions are tested to be within a
	// mass-to-charge ratio range as initialised by vt_CONDITION_FION_MZ.

	const fion::size_type st_CONDITION_COUNT_FION_SUP = 10;
	// st_CONDITION_COUNT_FION_SUP is a size_type with compile-time or run-time
	// initialised value that defines the quantity of the most intense fragment
	// ions for consideration of fragment ion distribution similarity between
	// two fpf_scan::scan classes. Should st_CONDITION_FION_SUP many of such
	// intense fragment ions be within a mass-to-range range as initialised by
	// vt_CONDITION_FION_MZ the two scan classes are considered to have
	// the required fragment ion distribution for spectral summing.

	//
	//
	//   * * NAMESPACE FUNCTIONS * *
	//
	//

	inline static fion::bool_type union_fragment_fion_mz(const fion::data_type& d_fion_itr_1, const fion::data_type& d_fion_itr_2) {
		return ((d_fion_itr_1->vt_return_fion_mz() <= d_fion_itr_2->vt_return_fion_mz() + vt_CONDITION_FION_MZ) && (d_fion_itr_1->vt_return_fion_mz() >= d_fion_itr_2->vt_return_fion_mz() - vt_CONDITION_FION_MZ));
	};
	// union_fragment_fion_mz() is a bool_type return function that returns true if
	// two compared fion classes have vt_fion_mz values within a range of
	// vt_CONDITION_FION_MZ. A return of true is indicative that two
	// fragment fion mass-to-charge ratios are suitable for spectral summing.

	inline fion::value_type return_mean_fion_mz_vt(fion* fion_1, fion* fion_2) {
		return (((fion_1->st_return_union_count() * (fion_1->vt_return_fion_mz())) + ((fion_2->st_return_union_count()) * (fion_2->vt_return_fion_mz()))) / (fion_1->st_return_union_count() + (fion_2->st_return_union_count())));
	};
	// return_mean_fion_mz_vt() is a value_type return function that returns the
	// mean mass-to-charge ratio of two fion classes. This function is called
	// when assigning value to a combined fion class from two fion classes
	// suitable for spectral summing. Previous summing is taken into
	// consideration through st_union_count.

	inline fion::size_type return_sum_ion_intensity_st(fion* fion_1, fion* fion_2) {
		return (fion_1->return_fion_intensity() + fion_2->return_fion_intensity());
	};
	// return_sum_ion_intensity_st() is a size_type return function that returns
	// the sum of the intensity of two fion classes. This function is called when
	// assigning value to a combined fion class from two fion classes suitable for
	// spectral summing. Previous summing is taken into consideration through st_union_count.

	inline fion::size_type return_sum_fion_union_count_st(fion* fion_1, fion* fion_2) {
		return (fion_1->st_return_union_count() + fion_2->st_return_union_count());
	};
	// return_sum_fion_union_count_st() is a size_type return function that
	// returns the sum of the union count of two fion classes. This function is
	// called when assigning value to a combined fion class from two fion classes
	// suitable for spectral summing. The cumulative value of st_union_count
	// represents the total number of fion classes that have been combined into
	// the new combined fion class.
}

#endif
