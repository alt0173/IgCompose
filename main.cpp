/* 
 * File:   main.cpp
 * Author: Lukah Dykes
 */

#include "fpf_scan_h.h"
#include <cstdlib>


namespace scan_class {
    const scan::size_type scan::SCAN_DEFAULT_ALLOCATION;
    scan::scan(size_type class_size = SCAN_DEFAULT_ALLOCATION){
        vt_precursor_mass = new value_type;
        vt_precursor_charge = new value_type;
        vt_precursor_mz = new value_type;
        vt_precursor_rt = new value_type;
    }
}





int main() {

    return 0;
}

