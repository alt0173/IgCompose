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


        //
        //   * * TYPEDEFS * *
        //

        typedef long double value_type;
        typedef size_t size_type;
        typedef bool bool_type;


        //
        //   * * CONSTRUCTORS * *
        //

        ion(const value_type& vt_init_fragment_ion_mz = value_type(), const value_type& vt_init_fragment_ion_int = value_type(), size_type st_init_union_count = 1, bool bt_init_union_init = bool_type()) {
            vt_fragment_ion_mz = vt_init_fragment_ion_mz;
            vt_fragment_ion_intensity = vt_init_fragment_ion_int;
            st_union_count = st_init_union_count;
            bt_union_init = bt_init_union_init;
        };


        //
        //   * * MODIFICATION MEMBER FUNCTIONS * *
        //

        inline void set_fragment_ion_mz_vt(const value_type& vt_new_fragment_ion_mz) {
            vt_fragment_ion_mz = vt_new_fragment_ion_mz;
        };

        inline void set_fragment_ion_intensity_st(const value_type& vt_new_fragment_ion_int) {
            vt_fragment_ion_intensity = vt_new_fragment_ion_int;
        };

        inline void set_union_count_st(size_type st_new_union_count) {
            st_union_count = st_new_union_count;
        };

        inline void set_init_fragment_ion_union_b(bool b_new_union_init) {
            bt_union_init = b_new_union_init;
        };


        //
        //   * * PRIVATE MEMBER ACCESS FUNCTIONS * *
        //

        inline value_type return_fragment_ion_mz() const {
            return vt_fragment_ion_mz;
        };

        inline value_type return_fragment_ion_intensity() const {
            return vt_fragment_ion_intensity;
        };

        inline size_type return_union_count_st() const {
            return st_union_count;
        };

        inline bool_type return_union_init_b() const {
            return bt_union_init;
        };

    private:
        value_type vt_fragment_ion_mz;
        value_type vt_fragment_ion_intensity;
        size_type st_union_count;
        bool_type bt_union_init;
    };


    //
    //   * * FUNCTIONS * *
    //

    inline ion::value_type return_mean_ion_mz_vt(ion* ion_1, ion* ion_2) {
        return (((ion_1->return_union_count_st() * (ion_1->return_fragment_ion_mz())) + ((ion_2->return_union_count_st()) * (ion_2->return_fragment_ion_mz()))) / (ion_1->return_union_count_st() + (ion_2->return_union_count_st())));
    };

    inline ion::value_type return_sum_ion_intensity_st(ion* ion_1, ion* ion_2) {
        return (ion_1->return_fragment_ion_intensity() + ion_2->return_fragment_ion_intensity());
    };

    inline ion::size_type return_sum_ion_union_count_st(ion* ion_1, ion* ion_2) {
        return (ion_1->return_union_count_st() + ion_2->return_union_count_st());
    };
}

#endif
 
