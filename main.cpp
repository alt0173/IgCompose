/* 
 * File:   main.cpp
 * Author: Lukah Dykes
 */


/* IgCompose v.0.0.1
 *
 *
 *
 */

#include <iostream> //provides - cin, cout
#include "fpf_scan_h.h"

const std::string version = "v.0.0.1";

// namespace scan_class defines object elements for fpf_scan_h

namespace scan_class {
    // TYPEDEFS and MEMBER CONSTANTS
    const scan::size_type scan::SCAN_DEFAULT_ALLOCATION;
    
    // CONSTRUCTORS and DESTRUCTOR   
}





int main() {
    
    std::cout << "-- IgCompose " << version << " --\n\n\n";      
    std::cout << "Input file?\n\n";
    
    std::string input_file;
    std::cin >> input_file;       
    std::ifstream fin_input(input_file);
    return 0;
}

