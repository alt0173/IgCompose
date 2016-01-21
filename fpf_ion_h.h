/*
 * File:   fpf_ion_h.h
 * Author: Lukah Dykes
 */



#ifndef FPF_ION_H
#define	FPF_ION_H
#include <cstdlib> // provides - size_t, NULL

namespace fpf_ion {

    class ion {
    public:
        // TYPEDEFS
        typedef double value_type;

        // CONSTRUCTORS

        ion(const value_type& vt_init_fragment_ion_mz = value_type(), const value_type& vt_init_fragment_ion_int = value_type()) {
            vt_fragment_ion_mz = vt_init_fragment_ion_mz;
            vt_fragment_ion_int = vt_init_fragment_ion_int;
        };

        // MODIFICATION MEMBER FUNCTIONS

        void set_fragment_ion_mz(const value_type& vt_new_fragment_ion_mz) {
            vt_fragment_ion_mz = vt_new_fragment_ion_mz;
        };

        void set_fragment_ion_int(const value_type& vt_new_fragment_ion_int) {
            vt_fragment_ion_int = vt_new_fragment_ion_int;
        };

        // PRIVATE MEMBER ACCESS FUNCTIONS

        value_type return_fragment_ion_mz() const {
            return vt_fragment_ion_mz;
        };

        value_type return_fragment_ion_int() const {
            return vt_fragment_ion_int;
        };

    private:
        value_type vt_fragment_ion_mz;
        value_type vt_fragment_ion_int;
    };
}

#endif
