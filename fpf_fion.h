// * * fpf_fion.h * *
// 
// Lukah Dykes - Flinders Proteomics Facility - 2016
// 
// * * * * *

 // --- namespace fpf_fion class fion
 // 
 // namespace fpf_fion contains object definitions for the fion class. An fion
 // class declares private members to store the values of a fragment ion
 // mass-to-charge ratio, detected intensity, and integer count of the
 // quantity of fion classes the fion class is composed of (initially 1). 
 //
 // The fpf_fion function union_fion_mz() boolean tests if two fion class fragment ion
 // mass-to-charge ratios are suitable for spectral summing - A true boolean
 // value calls vt_return_mean_fion_mz() and st_return_sum_fion_intensity() to
 // calculate the mean mass-to-charge ratio and summed intensity of the two fion
 // classes, taking into consideration previous summing through st_fion_union_count.
 // Fragment ion spectral summing is called from the parent fpf_scan scan class function scan_fion_sum().

#ifndef FPF_FION
#define	FPF_FION
#include <cstdlib> // provides - size_t, NULL

namespace fpf_fion {

	class fion;
	// Forward declaration for class fion.

	typedef double value_type;
	// Defines fpf_fion::fion::value_type as any standard C++ data type.

	typedef size_t size_type;
	// Defines fpf_fion::fion::size_type as a size_t type. Requires <cstdlib>.

	typedef fion* data_type;
	// Defines fpf_fion::fion::data_type as a pointer to a fpf_fion::fion class.

	typedef bool bool_type;
	// Defines fpf_fion::fion::bool_type as a bool type.

	//
	//
	//
	//   * * NAMESPACE VARIABLES * *
	//
	//
	//

	value_type vt_CONDITION_FION_MZ = 0.050;
	// vt_CONDITION_FION_MZ is a value_type with a compile-time or
	// run-time initialised value that defines the fragment ion mass-to-charge
	// ratio range for spectral summing.

	size_type st_CONDITION_FION_SUP = 4;
	// st_CONDITION_FION_SUP is a size_type with a compile-time or run-time
	// initialised value that defines the required quantity of the
	// st_CONDITION_COUNT_FION_SUP most intense fragment ions in a
	// fpf_scan::scan class that match the st_CONDITION_COUNT_FION_SUP most
	// intense fragment ions of a compared fpf_scan::scan class to be suitable
	// for spectral summing. Fragment ions are tested to be within a
	// mass-to-charge ratio range as initialised by vt_CONDITION_FION_MZ.

	const size_type st_CONDITION_COUNT_FION_SUP = 10;
	// st_CONDITION_COUNT_FION_SUP is a size_type with compile-time or run-time
	// initialised value that defines the quantity of the most intense fragment
	// ions for consideration of fragment ion distribution similarity between
	// two fpf_scan::scan classes. Should st_CONDITION_FION_SUP many of such
	// intense fragment ions be within a mass-to-range range as initialised by
	// vt_CONDITION_FION_MZ the two scan classes are considered to have
	// the required fragment ion distribution for spectral summing.

	class fion {
	public:

		fion() {
			// fion() defines the default constructor for the fpf_fion::fion class that initialises
			// member values as ISO type defaults (0 for standard C++ data types) and the value 1 for
			// st_scan_union_count - representing an unsummed scan class.
			vt_fion_mz = value_type();
			st_fion_intensity = size_type();
			st_fion_union_count = 1;
		};

		~fion() {
			// ~fion() defines the default destructor for the
			// fpf_fion::fion class.
		};

		//
		//
		//
		//   * * MEMBER MODIFICATION FUNCTIONS * *
		//
		//
		//

		inline void set_fragment_ion_mz(const value_type& vt_new_fion_mz) {
			// set_fragment_ion_mz() assigns a value_type to vt_fion_mz.
			vt_fion_mz = vt_new_fion_mz;
		};

		inline void set_fragment_ion_intensity(const size_type& st_new_fion_int) {
			// set_fragment_ion_intensity() assigns a size_type to st_fion_intensity.
			st_fion_intensity = st_new_fion_int;
		};

		inline void set_union_count(size_type st_new_union_count) {
			// set_union_count() assigns a size_type to st_fion_union_count.
			st_fion_union_count = st_new_union_count;
		};

		//
		//
		//
		//   * * MEMBER ACCESS FUNCTIONS * *
		//
		//
		//

		inline value_type vt_return_fion_mz() const {
			// vt_return_fion_mz() returns vt_fion_mz, the fragment
			// fion mass-to-charge ratio of the referenced fion class.
			return vt_fion_mz;
		};

		inline size_type return_fion_intensity() const {
			// vt_return_fion_mz() returns st_fion_intensity, the
			// fragment fion detected intensity of the referenced fion class.
			return st_fion_intensity;
		};

		inline size_type st_return_union_count() const {
			// vt_return_fion_mz() returns st_fion_union_count, the count of
			// fragment ion spectra that have been combined into the referenced fion class.
			return st_fion_union_count;
		};

	private:
		value_type vt_fion_mz;
		// vt_fion_mz is a value_type data type that stores the value of
		// a fragment ion mass-to-charge ratio in the referenced fion class.

		size_type st_fion_intensity;
		// st_fion_intensity is a size_type data type that stores the
		// value of a fragment ion detected intensity in the referenced fion class.

		size_type st_fion_union_count;
		// st_fion_union_count is a size_type data type that stores the quantity of
		// fion classes that have been combined to create the referenced fion
		// class. An unsummed fion class has a value of 1, a fion class having
		// undergone one iteration of summing has a value 2, and onwards.
	};

	//
	//
	//
	//   * * NAMESPACE FUNCTIONS * *
	//
	//
	//

	void set_CONDITION_FION_MZ(value_type vt_set_CONDITION_FION_MZ) {
		// set_CONDITION_FION_MZ() assigns a value_type to vt_CONDITION_FION_MZ.  
		vt_CONDITION_FION_MZ = vt_set_CONDITION_FION_MZ;
	}

	void set_CONDITION_FION_SUP(size_type st_set_CONDITION_FION_SUP) {
		// set_CONDITION_FION_SUP() assigns a size_type to st_CONDITION_FION_SUP. 
		st_CONDITION_FION_SUP = st_set_CONDITION_FION_SUP;
	}

	inline bool_type union_fion_mz(const data_type& d_fion_itr_1, const data_type& d_fion_itr_2) {
		// union_fion_mz() is a bool_type return function that returns true if
		// two compared fion classes have vt_fion_mz values within a range of
		// vt_CONDITION_FION_MZ. A return of true is indicative that two
		// fragment fion mass-to-charge ratios are suitable for spectral summing.
		return ((d_fion_itr_1->vt_return_fion_mz() <= d_fion_itr_2->vt_return_fion_mz() + (vt_CONDITION_FION_MZ / 2)) && (d_fion_itr_1->vt_return_fion_mz() >= d_fion_itr_2->vt_return_fion_mz() - (vt_CONDITION_FION_MZ / 2)));
	};

	inline value_type vt_return_mean_fion_mz(fion* fion_1, fion* fion_2) {
		// vt_return_mean_fion_mz() is a value_type return function that returns the
		// mean mass-to-charge ratio of two fion classes. This function is called
		// when assigning value to a combined fion class from two fion classes
		// suitable for spectral summing. Previous summing is taken into
		// consideration through st_fion_union_count.
		return (((fion_1->st_return_union_count() * (fion_1->vt_return_fion_mz())) + ((fion_2->st_return_union_count()) * (fion_2->vt_return_fion_mz()))) / (fion_1->st_return_union_count() + (fion_2->st_return_union_count())));
	};

	inline size_type st_return_sum_fion_intensity(fion* fion_1, fion* fion_2) {
		// st_return_sum_fion_intensity() is a size_type return function that returns
		// the sum of the intensity of two fion classes. This function is called when
		// assigning value to a combined fion class from two fion classes suitable for
		// spectral summing. Previous summing is taken into consideration through st_fion_union_count.
		return (fion_1->return_fion_intensity() + fion_2->return_fion_intensity());
	};

	inline size_type st_return_sum_fion_union_count(fion* fion_1, fion* fion_2) {
		// st_return_sum_fion_union_count() is a size_type return function that
		// returns the sum of the union count of two fion classes. This function is
		// called when assigning value to a combined fion class from two fion classes
		// suitable for spectral summing. The cumulative value of st_fion_union_count
		// represents the total number of fion classes that have been combined into
		// the new combined fion class.
		return (fion_1->st_return_union_count() + fion_2->st_return_union_count());
	};
}

#endif
