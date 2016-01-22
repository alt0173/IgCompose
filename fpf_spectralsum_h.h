/*
 * File:   fpf_spectralsum_h.h
 * Author: Lukah Dykes
 */


//!!
//
//	class scan
//
//		A SCAN class is a collection of doubles that contain the precursor mass,
//		precursor charge, mass-to-charge ratio, and retention time. SCAN classes 
//		are linked to the corresponding fragment ions through a pointer
//		assignment to an IONS class. The associated IONS class contains as a 
//		dynamic array of doubles the transition ions of the respective SCAN class 
//		element(s). Should two or more SCAN classes be determined to be suitable
//		for spectral summing, as tested by bool conditions, the union of 
//		these classes is created in a new SCAN class. SCAN classes created 
//		through the union process are identifiable by bool value. The 
//		collection of union created SCAN classes are exported to a .mgf file at 
//		program completion.
//
//TYPEDEFS and MEMBER CONSTANTS
//
//	typedef _____ value_type
//
//		scan::value_type is the data type of elements of the SCAN class. It may 
//		be any C++ built-in type, or an object with a default constructor,
//		assignment operator, and equality operators.
//
//	typedef _____ size_type
//
//		scan::size_type is the data type of any variable that is assigned to
//		enumerate quantity at run-time.
//
//	typedef _____ node_type
//
//		scan::node_type is the data type of a pointer that is assigned to
//		point to a programmer-defined data type. In practice, a node_type
//		assignment is used to create an association between a SCAN class object
//		and the corresponding IONS class object.
//
//	static const size_type SCAN_DEFAULT_ALLOCATION = _____
//
//		scan::SCAN_DEFAULT_ALLOCATION is the initial memory allocation for the
//		elements of the SCAN class. It assigns a program-defined initial
//		allocation, and if this allocation is reached, assigns further memory
//		as defined by the SCAN_ALLOCATE function. Note that the memory call
//		process defines that greater efficiency is achieved through assigning
//		memory as a group, rather than unit-wise.
//
//	value_type CONDITION_PRECURSOR_MZ = _____
//
//		scan::CONDITION_PRECURSOR_MZ defines the delta-range of precursor
//		mass-to-charge ratio to determine if two classes are suitable for
//		spectral summing. It can be program-defined, or called from an
//		external source.
//
//	value_type CONDITION_FRAGMENT_ION = _____
//
//		scan::CONDITION_FRAGMENT_ION defines the score limit-value of fragment
//		ion distribution similarity to determine if two classes are suitable for
//		for spectral summing. Fragment ion distribution is scored on the basis
//		of peak intensity and fragment ion mass-to-charge ratio. Scoring is 
//		controlled by the IONS class type as defined in FPF_IONS.H. It can be 
//		program-defined or called from an external source.
//
//	value_type CONDITION_RETENTION_TIME = _____
//
//		scan::CONDITION_RETENTION_TIME defines the delta-range of retention
//		time to determine if two classes are suitable for spectral summing. 
//		It can be program-defined, or called from an external source.
//
//CONSTRUCTORS and DESTRUCTOR
//
//	scan(size_type class_size = SCAN_DEFAULT_ALLOCATION)
//
//		Constructs an empty SCAN class with memory allocation as defined by 
//		SCAN_DEFAULT_ALLOCATION. Should the SCAN class reach its allocated
// 		memory, further allocation can be assigned with the SCAN_ALLOCATE
//		function.
//
//	scan(const scan& scan_1)
//
//		Assigns an explicit copy constructor for copying a SCAN class. This
//		constructor is called implicitly when calling SCAN classes by value.
//
//	~scan()
//
//		Removes a SCAN class and clears memory allocation.
//
//MODIFICATION MEMBER FUNCTIONS
//
//	scan scan_union(const scan& scan_1, const scan& scan_2)
//
//		Returns a SCAN class that is the union of two SCAN classes. Refenced 
//		scan_1 and scan_2 are required to be within the conditional definition
// 		for spectral summing. Conditional selection is determined by -
//
//			1 - Precursor mass-over-charge ratio
//			2 - Fragment ion distribution
//			3 - Retention time
//			4 - ?
//
//		Conditional selection is bool tested with the corresponding functions
//		(prototyped below with CONSTANT MEMBER FUNCTIONS) -
//
//			1 - bool union_precursor_mz(const scan& scan_1, const scan& scan_2)
//			2 - bool union_fragment_ion(const scan& scan_1, const scan& scan_2)
//			3 - bool union_retention_time(const scan& scan_1, const scan& scan_2)
//			4 - ?
//
//		Fragment ion similarity is determined by the IONS class. Should two
//		fragment ions be suitable for spectral summing, the average fragment ion
//		mass-to-charge ratio and the summation of intensities is calculated for
//		the resulting SCAN class. Union SCAN classes are bool TRUE for being
//		created through the SCAN_UNION member function and at program completion are
//		exported to a .mgf file for downstream analysis.
//
//	scan operator +(const scan& scan_1, const scan& scan_2)
//
//		Overloads a + operator assignment to create the union of two SCAN classes.
//
//	bool scan_union_created(scan& scan_1)
//
//		Returns TRUE if the SCAN class was created through the SCAN_UNION member
//		member function. The default value for SCAN classes created through the
//		constructor is FALSE.
//
//	node_type link_ions()
//
//		Returns a pointer to the IONS class for the associated SCAN class. The 
//		pointer	directs to the node of the head of a linked list which is read 
//		by order of fragmentation ion mass-to-charge ratio.
//
//CONSTANT MEMBER FUNCTIONS
//
//	value_type precursor_mass() const
//
//		Returns the precursor mass of a SCAN class.
//
//	value_type precursor_charge() const
//
//		Returns the precursor charge of a SCAN class.
//
//	value_type precursor_mz() const
//
//		Returns the precursor mass-to-charge ratio of a SCAN class.
//
//	value_type precursor_rt() const
//
//		Returns the precursor retention time of a SCAN class.
//
//	const node_type link_ions() const
//
//		Returns a pointer to the IONS class for the associated SCAN class. The 
//		pointer	directs to the node of the head of a linked list which is read 
//		by order of fragmentation ion mass-to-charge ratio.
//
//	bool union_precursor_mz(const scan& scan_1, const scan& scan_2)
//
//		Returns TRUE if the precursor mass-to-charge ratios of two SCAN classes 
//		are within the delta-value range defined by CONDITION_PRECURSOR_MZ.
//
//	bool union_fragment_ion(const scan& scan_1, const scan& scan_2)
//
//		Returns TRUE if the fragment ion similarity score is within the
//		limit-value as defined by CONDITION_FRAGMENT_ION.
//
//	bool union_retention_time(const scan& scan_1, const scan& scan_2)
//
//		Returns TRUE if the retention times of two SCAN classes are within the 
//		delta-value range defined by CONDITION_RETENTION_TIME.


#ifndef FPF_SPECTRALSUM_H
#define	FPF_SPECTRALSUM_H
#include <cstdlib> // provides - size_t, NULL
#include <fstream> // provides - std::ifstream
#include <istream> // provides - std::istream::get
#include <sstream> // provides - std::istringstream
#include <string> // provides - std::string
#include <iostream> // provides - std::cin, std::cout

namespace fpf_spectralsum {

    class scan {
    public:
        // TYPEDEFS and MEMBER CONSTANTS
        typedef double value_type;
        typedef size_t size_type;
        value_type CONDITION_PRECURSOR_MASS = 0.05;
        value_type CONDITION_PRECURSOR_MZ = 0.05;
        value_type CONDITION_PRECURSOR_RT = 120;
        value_type CONDITION_FRAGMENT_ION = 95;

        // CONSTRUCTORS and DESTRUCTOR

        scan() {
            vt_precursor_mass = value_type();
            vt_precursor_mz = value_type();
            vt_precursor_rt = value_type();
            st_precursor_charge = size_type();
            nt_head_ptr = NULL;
            nt_tail_ptr = NULL;
        };

        //scan() {}

        ~scan() {
        };

        // MODIFICATION MEMBER FUNCTIONS

        void scan_modify_precursor_mass(value_type parse_precursor_mass) {
            vt_precursor_mass = parse_precursor_mass;
        };

        void scan_modify_precursor_mz(value_type parse_precursor_mz) {
            vt_precursor_mz = parse_precursor_mz;
        };

        void scan_modify_precursor_rt(value_type parse_precursor_rt) {
            vt_precursor_rt = parse_precursor_rt;
        };

        void scan_modify_precursor_charge(size_type parse_precursor_charge) {
            st_precursor_charge = parse_precursor_charge;
        };
        void scan_union_created();

        scan operator+(const scan& scan_1);

        // CONSTANT MEMBER FUNCTIONS

        const value_type return_precursor_mass() const {
            return vt_precursor_mass;
        };

        const value_type return_precursor_mz() const {
            return vt_precursor_mz;
        };

        const value_type return_precursor_rt() const {
            return vt_precursor_rt;
        };

        const size_type return_precursor_charge() const {
            return st_precursor_charge;
        };

        fpf_node::node::node_type& return_head_ptr() {
            return nt_head_ptr;
        };

        fpf_node::node::node_type& return_tail_ptr() {
            return nt_tail_ptr;
        };

        bool union_precursor_mass(const scan& scan_1, const scan& scan_2) {
            return ((scan_1.return_precursor_mass() < scan_2.return_precursor_mass() + CONDITION_PRECURSOR_MASS) && (scan_1.return_precursor_mass() > scan_2.return_precursor_mass() - CONDITION_PRECURSOR_MASS));
        };
        bool union_retention_time(const scan& scan_1, const scan & scan_2);
        bool union_fragment_ion(const scan& scan_1, const scan & scan_2);

    private:
        value_type vt_precursor_mass;
        value_type vt_precursor_mz;
        value_type vt_precursor_rt;
        size_type st_precursor_charge;
        fpf_node::node::node_type nt_head_ptr;
        fpf_node::node::node_type nt_tail_ptr;
    };
    
    // FUNCTIONS

    scan scan_union(const scan& scan_1, const scan& scan_2) {
        // overload + operator...
        scan scan_3 = scan();
        scan_3.scan_modify_precursor_mass((scan_1.return_precursor_mass() + scan_2.return_precursor_mass()) / 2);
        return scan_3;
    };

    class parse {
    public:
        // TYPEDEFS and MEMBER CONSTANTS
        typedef double value_type;
        typedef size_t size_type;
        typedef scan* scan_node_type;
        static const size_type PARSE_DEFAULT_ALLOCATION = 10000;

        // CONSTRUCTORS and DESTRUCTOR

        parse(size_type class_size = PARSE_DEFAULT_ALLOCATION) {
            nt_scan = new scan[class_size];
            st_capacity = class_size;
            st_used = size_type();
        };
        parse(const parse& parse);

        ~parse() {
            delete[] nt_scan;
        };

        // OPERATORS

        void operator=(const parse parse_0) {
            parse* tail_ptr;
        };

        // MODIFICATION MEMBER FUNCTIONS

        void input_parse(std::ifstream& fin, parse& parse_0) {
            char c_inputstream;
            std::string s_inputstream = "";
            int switch_inputstream = 0;
            value_type ss_inputstream;
            fpf_ion::ion* ion_inputstream;
            while (fin.std::istream::get(c_inputstream)) {
                if (c_inputstream != '\n') {
                    s_inputstream += c_inputstream;
                }
                if (s_inputstream == "RTINSECONDS=") {
                    switch_inputstream = 2;
                    s_inputstream.clear();
                }
                if ((switch_inputstream == 2) && (c_inputstream == '\n')) {
                    std::istringstream(s_inputstream) >> ss_inputstream;
                    parse::value_type vt_inputstream = ss_inputstream;
                    nt_scan[st_used].scan_modify_precursor_rt(vt_inputstream);
                    s_inputstream.clear();
                }
                if ((switch_inputstream == 4) && (c_inputstream == ' ')) {
                    std::istringstream(s_inputstream) >> ss_inputstream;
                    parse::value_type vt_inputstream = ss_inputstream;
                    ion_inputstream = new fpf_ion::ion();
                    ion_inputstream->set_fragment_ion_mz(vt_inputstream);
                    switch_inputstream = 5;
                    s_inputstream.clear();
                }
                if ((switch_inputstream == 5) && (c_inputstream == '\n')) {
                    std::istringstream(s_inputstream) >> ss_inputstream;
                    parse::value_type vt_inputstream = ss_inputstream;
                    ion_inputstream->set_fragment_ion_int(vt_inputstream);
                    fpf_node::insert_tail(ion_inputstream, nt_scan[st_used].return_head_ptr(), nt_scan[st_used].return_tail_ptr());
                    switch_inputstream = 4;
                    s_inputstream.clear();
                }
                if (s_inputstream == "PEPMASS=") {
                    switch_inputstream = 3;
                    s_inputstream.clear();
                }
                if ((switch_inputstream == 3) && (c_inputstream == '\n')) {
                    std::istringstream(s_inputstream) >> ss_inputstream;
                    parse::value_type vt_inputstream = ss_inputstream;
                    nt_scan[st_used].scan_modify_precursor_mass(vt_inputstream);
                    switch_inputstream = 4;
                    s_inputstream.clear();
                }
                if ((switch_inputstream == 4) && ((c_inputstream == 'E'))) {
                    switch_inputstream = 0;
                    ++parse_0.st_used;
                }
                if (c_inputstream == '\n') {
                    s_inputstream.clear();
                }
            }
        };

        parse read_parse_union(parse& parse_1) {
            parse union_parse = parse();
            for (size_type i = 0; i < return_used(); ++i) {
                for (size_type j = 1; i + j < return_used(); ++j) {
                    if ((nt_scan[i].return_precursor_mass() < nt_scan[i + j].return_precursor_mass() + 10) && (nt_scan[i].return_precursor_mass() > nt_scan[i + j].return_precursor_mass() - 10)) {
                        // copy constructor?
                        union_parse.nt_scan[union_parse.st_used] = scan_union(nt_scan[i], nt_scan[i + j]);
                        ++union_parse.st_used;
                        std::cout << "\nzing!" << union_parse.st_used;
                    }
                }
            }
            return union_parse;
        };

        // CONSTANT MEMBER FUNCTIONS

        const scan_node_type return_scan() const {
            return nt_scan;
        };

        const size_type return_capacity() const {
            return st_capacity;
        };

        const size_type return_used() const {
            return st_used;
        };
        void read_parse() const;

    private:
        scan_node_type nt_scan;
        size_type st_capacity;
        size_type st_used;
    };
}

#endif
