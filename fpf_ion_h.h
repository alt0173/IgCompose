/*
 *	File:   fpf_ion_h.h
 *	Author: Lukah Dykes
 */



#ifndef FPF_ION_H
#define	FPF_ION_H
#include <cstdlib> // provides - size_t, NULL

namespace fpf_ion {

    class ion {
    public:
        // TYPEDEFS
        typedef long double value_type;
        typedef size_t size_type;
        typedef bool bool_type;

        // CONSTRUCTORS

        ion(const value_type& vt_init_fragment_ion_mz = value_type(), const value_type& vt_init_fragment_ion_int = value_type(), bool bt_init_union = bool_type(), bool bt_init_union_init = bool_type()) {
            vt_fragment_ion_mz = vt_init_fragment_ion_mz;
            vt_fragment_ion_intensity = vt_init_fragment_ion_int;
            bt_union = bt_init_union;
            bt_union_init = bt_init_union_init;
        };

        // MODIFICATION MEMBER FUNCTIONS

        inline void set_fragment_ion_mz_vt(const value_type& vt_new_fragment_ion_mz) {
            vt_fragment_ion_mz = vt_new_fragment_ion_mz;
        };

        inline void set_fragment_ion_intensity_vt(const value_type& vt_new_fragment_ion_int) {
            vt_fragment_ion_intensity = vt_new_fragment_ion_int;
        };

        inline void set_union_b(bool b_new_union) {
            bt_union = b_new_union;
        };
        
        inline void set_union_init_b(bool b_new_union_init) {
            bt_union_init = b_new_union_init;
        };

        // PRIVATE MEMBER ACCESS FUNCTIONS

        inline value_type return_fragment_ion_mz() const {
            return vt_fragment_ion_mz;
        };

        inline value_type return_fragment_ion_intensity() const {
            return vt_fragment_ion_intensity;
        };

        inline bool_type return_union() const {
            return bt_union;
        };
        
        inline bool_type return_union_init() const {
            return bt_union_init;
        };

    private:
        value_type vt_fragment_ion_mz;
        value_type vt_fragment_ion_intensity;
        bool_type bt_union;
        bool_type bt_union_init;
    };
}

#endif
