/*
 * File:   fpf_ions_h.h
 * Author: Lukah Dykes
 */


//!!
//
//	class ions
//
//
//
//TYPEDEFS and MEMBER CONSTANTS
//
//	typedef _____ value_type
//
//		scan::value_type is the data type of elements of the IONS class. It may 
//		be any C++ built-in type, or an object with a default constructor,
//		assignment operator, and equality operators.
//
//	typedef _____ size_type
//
//		scan::size_type is the data type of any variable that is assigned to
//		enumerate quanity at run-time.
//
//	static const size_type IONS_DEFAULT_ALLOCATION = _____
//
//		ions::IONS_DEFAULT_ALLOCATION is the initial memory allocation for the
//		elements of the IONS class. It assigns a program-defined initial
//		allocation, and if this allocation is reached, assigns further memory
//		as defined by the IONS_ALLOCATE function. Note that the memory call
//		process defines that greater efficiency is achieved through assigning
//		memory as a group, rather than unit-wise.
//
//CONSTRUCTORS and DESTRUCTOR
//
//	ions()
//
//		Constructs an empty IONS class with memory allocation as defined by 
//		IONS_DEFAULT_ALLOCATION. Should the SCAN class reach its allocated
// 		memory, further allocation can be assigned with the IONS_ALLOCATE
//		function.
//
//	ions(const ions& ions_1)
//
//		Assigns an explicit copy constructor for copying a IONS class. This
//		constructor is called implicitly when calling IONS classes by value.
//
//	~ions()
//
//		Removes an IONS class and clears memory allocation.
//
//MODIFICATION MEMBER FUNCTIONS
//
//
//CONSTANT MEMBER FUNCTIONS
//
//	value_type ion_mz() const
//
//		Returns the fragment ion mass-to-charge ratio of an IONS class.
//
//	value_type ion_intensity() const
//
//		Returns the fragment ion intensity of an IONS class.


#ifndef FPF_IONS_H
#define	FPF_IONS_H
#include <cstdlib> // provides - size_t

namespace ions_class {

    class ions {
    public:
        // TYPEDEFS and MEMBER CONSTANTS
        typedef double value_type;
        typedef unsigned int size_type;
        static const size_type IONS_DEFAULT_ALLOCATION = 200;

        // CONSTRUCTORS and DESTRUCTOR
        ions();
        ~ions();

        // MODIFICATION MEMBER FUNCTIONS
        void ions_modify_ion_mz(value_type parse_ion_mz);
        void ions_modify_ion_intensity(value_type parse_ion_intensity);

        // CONSTANT MEMBER FUNCTIONS
        const value_type ion_mz() const;
        const value_type ion_intensity() const;

    private:
        value_type vt_ion_mz;
        value_type vt_ion_intensity;
    };
}

#endif
