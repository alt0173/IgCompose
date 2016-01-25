/*
 *	File:   fpf_spectralsum_h.h
 *	Author: Lukah Dykes
 */


 //
 //	typedef _____ node_type
 //
 //		scan::node_type is the data type of a pointer that is assigned to
 //		point to a programmer-defined data type. In practice, a node_type
 //		assignment is used to create an association between a SCAN class object
 //		and the corresponding IONS class object.
 //
 //	static const size_type SCAN_DEFAULT_ALLOCATION = _____
 //	value_type CONDITION_RETENTION_TIME = _____
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



 //


 //



#ifndef FPF_SPECTRALSUM_H
#define	FPF_SPECTRALSUM_H
#include <cstdlib> // provides - size_t, NULL
#include <fstream> // provides - std::ifstream
#include <istream> // provides - std::istream::get
#include <sstream> // provides - std::istringstream
#include <string> // provides - std::string
#include <iostream> // provides - std::cin, std::cout
#include "fpf_ion_h.h"
#include "fpf_node_h.h"

namespace fpf_spectralsum {

	static double CONDITION_PRECURSOR_MASS = 0.02;
	static double CONDITION_PRECURSOR_MZ = 0.05;
	//
	//		scan::CONDITION_PRECURSOR_MZ defines the delta-range of precursor
	//		mass-to-charge ratio to determine if two classes are suitable for
	//		spectral summing.

	static double CONDITION_PRECURSOR_RT = 60;
	//
	//		scan::CONDITION_PRECURSOR_RT defines the delta-range of retention
	//		time to determine if two classes are suitable for spectral summing. 
	//		It can be program-defined, or called from an external source.

	static double CONDITION_FRAGMENT_ION = 95;
	//
	//		scan::CONDITION_FRAGMENT_ION defines the score limit-value of fragment
	//		ion distribution similarity to determine if two classes are suitable for
	//		for spectral summing. Fragment ion distribution is scored on the basis
	//		of peak intensity and fragment ion mass-to-charge ratio. Scoring is 
	//		controlled by the ION class type as defined in FPF_ION_H.H.

	static double CONDITION_FRAGMENT_ION_MZ = 0.02;

	typedef double value_type;
	//
	//		scan::value_type is the data type of elements of the SCAN class. It may 
	//		be any C++ built-in type, or an object with a default constructor,
	//		assignment operator, and equality operators.

	typedef size_t size_type;
	//
	//		scan::size_type is the data type of any variable that is assigned to
	//		enumerate quantity at run-time.

	typedef fpf_node::node::node_type data_type;
	//
	//

	/*
	 *
	 */

	class scan {
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

	public:

		scan() {
			vt_precursor_mass = value_type();
			vt_precursor_mz = value_type();
			vt_precursor_rt = value_type();
			st_precursor_charge = size_type();
			nt_head_ptr = NULL;
			nt_tail_ptr = NULL;
		};

		~scan() {
		};


		/*
		*
		*	MODIFICATION MEMBER FUNCTIONS
		*
		*/

		void set_precursor_mass(value_type parse_precursor_mass) {
			vt_precursor_mass = parse_precursor_mass;
		};

		void set_precursor_mz(value_type parse_precursor_mz) {
			vt_precursor_mz = parse_precursor_mz;
		};

		void set_precursor_rt(value_type parse_precursor_rt) {
			vt_precursor_rt = parse_precursor_rt;
		};

		void set_precursor_charge(size_type parse_precursor_charge) {
			st_precursor_charge = parse_precursor_charge;
		};
		void scan_union_created();

		scan operator+(const scan& scan_1);

		/*
		*
		*	CONSTANT MEMBER FUNCTIONS
		*
		*/

		const value_type return_precursor_mass() const {
			return vt_precursor_mass;
		};
		//		Returns the precursor mass of a SCAN class.

		const value_type return_precursor_mz() const {
			return vt_precursor_mz;
		};
		//		Returns the precursor mass-to-charge ratio of a SCAN class.

		const value_type return_precursor_rt() const {
			return vt_precursor_rt;
		};
		//		Returns the precursor retention time of a SCAN class.

		const size_type return_precursor_charge() const {
			return st_precursor_charge;
		};
		//		Returns the precursor charge of a SCAN class.

		data_type& return_head_ptr() {
			return nt_head_ptr;
		};
		//		Returns a head pointer to a linked lift of ION classes for the 
		//		associated SCAN class. The pointer directs to the head node of 
		//		a linked list.

		data_type& return_tail_ptr() {
			return nt_tail_ptr;
		};
		//		Returns a tail pointer to a linked lift of ION classes for the 
		//		associated SCAN class. The pointer directs to the head node of 
		//		a linked list.


	private:
		value_type vt_precursor_mass;
		value_type vt_precursor_mz;
		value_type vt_precursor_rt;
		size_type st_precursor_charge;
		data_type nt_head_ptr;
		data_type nt_tail_ptr;
	};

	/*
	*
	* FUNCTIONS
	*
	*/

	bool union_precursor_mass(const scan& scan_1, const scan& scan_2) {
		return ((scan_1.return_precursor_mass() < scan_2.return_precursor_mass() + CONDITION_PRECURSOR_MASS) && (scan_1.return_precursor_mass() > scan_2.return_precursor_mass() - CONDITION_PRECURSOR_MASS));
	};
	//		Returns TRUE if the precursor masses of two SCAN classes 
	//		are within the delta-value range defined by CONDITION_PRECURSOR_MASS.

	bool union_precursor_rt(const scan& scan_1, const scan& scan_2) {
		return ((scan_1.return_precursor_mass() < scan_2.return_precursor_rt() + CONDITION_PRECURSOR_RT) && (scan_1.return_precursor_rt() > scan_2.return_precursor_rt() - CONDITION_PRECURSOR_RT));
	};
	//		Returns TRUE if the retention times of two SCAN classes are within the 
	//		delta-value range defined by CONDITION_RETENTION_TIME.

	bool union_fragment_ion_mz(const fpf_ion::ion* ion_1, const fpf_ion::ion* ion_2) {
		return ((ion_1->return_fragment_ion_mz() < ion_2->return_fragment_ion_mz() + CONDITION_FRAGMENT_ION_MZ) && (ion_1->return_fragment_ion_mz() > ion_2->return_fragment_ion_mz() - CONDITION_FRAGMENT_ION_MZ));
	};

	scan scan_union(scan& scan_1, scan& scan_2) {
		// overload + operator...
		scan scan_3 = scan();
		fpf_ion::ion* ion_union;
		size_type ion_count = 0;
		scan_3.set_precursor_mass((scan_1.return_precursor_mass() + scan_2.return_precursor_mass()) / 2);
		scan_3.set_precursor_rt((scan_1.return_precursor_rt() + scan_2.return_precursor_rt()) / 2);
		for (fpf_node::node::node_type scan_1_head_ptr = scan_1.return_head_ptr(); scan_1_head_ptr != NULL; scan_1_head_ptr = scan_1_head_ptr->return_node()) {
			for (fpf_node::node::node_type scan_2_head_ptr = scan_2.return_head_ptr(); scan_2_head_ptr != NULL; scan_2_head_ptr = scan_2_head_ptr->return_node()) {
				if ((scan_1_head_ptr->return_data()->return_fragment_ion_mz() > scan_2_head_ptr->return_data()->return_fragment_ion_mz() - CONDITION_FRAGMENT_ION_MZ)) {
					if (union_precursor_mass(scan_1, scan_2) && union_precursor_rt(scan_1, scan_2)) {
						if (union_fragment_ion_mz(scan_1_head_ptr->return_data(), scan_2_head_ptr->return_data())) {
							ion_union = new fpf_ion::ion();
							ion_union->set_fragment_ion_mz((scan_1_head_ptr->return_data()->return_fragment_ion_mz() + scan_2_head_ptr->return_data()->return_fragment_ion_mz()) / 2);
							ion_union->set_fragment_ion_int(scan_1_head_ptr->return_data()->return_fragment_ion_int() + scan_2_head_ptr->return_data()->return_fragment_ion_int());
							ion_union->set_union();
							fpf_node::insert_tail(ion_union, scan_3.return_head_ptr(), scan_3.return_tail_ptr());
						}
						//else {
						//	ion_union = new fpf_ion::ion();
						//	ion_union->set_fragment_ion_mz(scan_1_head_ptr->return_data()->return_fragment_ion_mz());
						//	ion_union->set_fragment_ion_int(scan_1_head_ptr->return_data()->return_fragment_ion_int());
						//	fpf_node::insert_tail(ion_union, scan_3.return_head_ptr(), scan_3.return_tail_ptr());
						//}
					}
				}
			}
		}
		return scan_3;
	};
	//		Returns a SCAN class that is the union of two SCAN classes. Refenced 
	//		scan_1 and scan_2 are required to be within the conditional definition
	// 		for spectral summing. Conditional selection is determined by -
	//
	//			1a - Precursor mass
	//			1b - Retention time
	//			2 - Fragment ion distribution
	//			- - ?
	//
	//		Conditional selection is bool tested with the corresponding member functions -
	//
	//			1a - bool union_precursor_mass(const scan& scan_1, const scan& scan_2)
	//			1b - bool union_precursor_rt(const scan& scan_1, const scan& scan_2)
	//			2 - bool union_fragment_ion(const scan& scan_1, const scan & scan_2)
	//			- - ?
	//
	//		Should two
	//		fragment ions be suitable for spectral summing, the average fragment ion
	//		mass-to-charge ratio and the summation of intensities is calculated for
	//		the resulting SCAN class. Union SCAN classes are assigned to the PARSE_UNION
	//		class and at program completion are	exported to a .mgf file for downstream 
	//		analysis.


	/*
	*
	*/


	class parse {

		typedef double value_type;
		//
		//		scan::value_type is the data type of elements of the SCAN class. It may 
		//		be any C++ built-in type, or an object with a default constructor,
		//		assignment operator, and equality operators.

		typedef size_t size_type;
		//
		//		scan::size_type is the data type of any variable that is assigned to
		//		enumerate quantity at run-time.

		typedef scan* scan_node_type;

		static const size_type PARSE_DEFAULT_ALLOCATION = 7000000;
		//
		//		scan::SCAN_DEFAULT_ALLOCATION is the initial memory allocation for the
		//		elements of the SCAN class. It assigns a program-defined initial
		//		allocation, and if this allocation is reached, assigns further memory
		//		as defined by the SCAN_ALLOCATE function. Note that the memory call
		//		process defines that greater efficiency is achieved through assigning
		//		memory as a group, rather than unit-wise.

	public:

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
			//parse* tail_ptr;
		};

		// MODIFICATION MEMBER FUNCTIONS

		void input_parse(std::ifstream& fin, parse& parse_0) {
			char c_inputstream;
			std::string s_inputstream = "";
			int switch_inputstream = 0;
			value_type ss_inputstream;
			fpf_ion::ion* ion_inputstream;
			static size_type output_interval = 100;
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
					nt_scan[st_used].set_precursor_rt(vt_inputstream);
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
					// W4 warns 'potentially uninitialized local pointer variable 'ion_inputstream' used' - note call to variable in if conditional? Functionality is okay.
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
					nt_scan[st_used].set_precursor_mass(vt_inputstream);
					switch_inputstream = 4;
					s_inputstream.clear();
				}
				if ((switch_inputstream == 4) && ((c_inputstream == 'E'))) {
					switch_inputstream = 0;					
					++parse_0.st_used;
					if (parse_0.st_used % output_interval == 0) {
						std::cout << "\n" << "scan - " << parse_0.st_used << "  retention time - " << ((nt_scan[st_used - 1].return_precursor_rt()) / 60);
						if (parse_0.st_used > 2 * output_interval - 1) {
							std::cout << "   delta - " << ((nt_scan[st_used - 1].return_precursor_rt()) / 60) - ((nt_scan[st_used - output_interval - 1].return_precursor_rt()) / 60);
						}
					}
				}
				if (c_inputstream == '\n') {
					s_inputstream.clear();
				}
			}
			std::cout << "\nscan - " << parse_0.st_used << "  retention time - " << ((nt_scan[st_used - 1].return_precursor_rt()) / 60);
			if (parse_0.st_used > 2 * output_interval - 1) {
				std::cout << "   delta - " << ((nt_scan[st_used - 1].return_precursor_rt()) / 60) - ((nt_scan[st_used - output_interval - 1].return_precursor_rt()) / 60);
			}
			std::cout << "\n\n\nSumming...\n";
		};

		void read_parse_union(const parse& parse_1, parse& union_parse) {
			size_type st_used_prev;
			static size_type st_output_interval = 100;
			for (parse::size_type i = 0; i < parse_1.return_used(); ++i) {				
				for (parse::size_type j = 1; i + j < parse_1.return_used(); ++j) {
					if (union_precursor_mass(parse_1.nt_scan[i], parse_1.nt_scan[i + j]) && union_precursor_rt(parse_1.nt_scan[i], parse_1.nt_scan[i + j])) {
						// copy constructor?
						union_parse.nt_scan[union_parse.st_used] = scan_union(parse_1.nt_scan[i], parse_1.nt_scan[i + j]);						
						++union_parse.st_used;
					}
				}
				if ((i > 0) && (i % st_output_interval == 0)) {				
					std::cout << "\nscan - " << i << "   union itr 0 - " << union_parse.st_used;
					// here?
					if (union_parse.st_used > 2 * st_output_interval - 1) {
						std::cout << "   delta - " << union_parse.st_used - st_used_prev;
					}
					st_used_prev = union_parse.st_used;
				}				
			}
			std::cout << "\nscan - " << parse_1.return_used() << "   union itr 0 - " << union_parse.st_used;
			if (union_parse.st_used > 2 * st_output_interval - 1) {
				std::cout << "   delta - " << union_parse.st_used - st_used_prev;
			}
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

		const int input_summary(std::ifstream& fin) {
			char c_inputstream;
			int scan_objects;
			while (fin.std::istream::get(c_inputstream)) {
				if ((fin.std::istream::peek() == 'E') && (c_inputstream == '\n')) {
					++scan_objects;
				}
			}
			return scan_objects;
		}

		void debug_parse() const {
			for (unsigned i = 0; i < return_used(); ++i) {
				std::cout << "\n" << i;
				std::cout << "\nnt_scan[i].return_precursor_rt() " << nt_scan[i].return_precursor_rt();
				std::cout << "\nnt_scan[i].return_precursor_mass() " << nt_scan[i].return_precursor_mass();
				for (data_type nt_scan_head_ptr = nt_scan[i].return_head_ptr(); nt_scan_head_ptr != NULL; nt_scan_head_ptr = nt_scan_head_ptr->return_node()) {
					std::cout << "\n" << nt_scan_head_ptr->return_data()->return_fragment_ion_mz() << "  " << nt_scan_head_ptr->return_data()->return_fragment_ion_int();
				}
			}
			if (return_used() == 0) {
				std::cout << "\n\nNo members!";
			}
		};

		void cout_mgf() const {
			for (unsigned i = 0; i < return_used(); ++i) {
				if (i > 0) {
					std::cout << "\nBEGIN IONS";
				}
				else {
					std::cout << "BEGIN IONS";
				}
				std::cout << "\nTITLE=" << "NULL";
				std::cout << "\nRTINSECONDS=" << nt_scan[i].return_precursor_rt();
				std::cout << "\nPEPMASS=" << nt_scan[i].return_precursor_mass();
				for (data_type nt_scan_head_ptr = nt_scan[i].return_head_ptr(); nt_scan_head_ptr != NULL; nt_scan_head_ptr = nt_scan_head_ptr->return_node()) {
					std::cout << "\n" << nt_scan_head_ptr->return_data()->return_fragment_ion_mz() << "  " << nt_scan_head_ptr->return_data()->return_fragment_ion_int();
				}
				std::cout << "\nEND IONS";
			}
			if (return_used() == 0) {
				std::cout << "\n\nNo members!";
			}
		};

		void fout_mgf(std::ofstream& fout) const {
			std::cout << "\n\n\nOutputting...";
			for (unsigned i = 0; i < return_used(); ++i) {
				if (i > 0) {
					fout << "\nBEGIN IONS";
				}
				else {
					fout << "BEGIN IONS";
				}
				fout << "\nTITLE=" << "NULL";
				fout << "\nRTINSECONDS=" << nt_scan[i].return_precursor_rt();
				fout << "\nPEPMASS=" << nt_scan[i].return_precursor_mass();
				for (data_type nt_scan_head_ptr = nt_scan[i].return_head_ptr(); nt_scan_head_ptr != NULL; nt_scan_head_ptr = nt_scan_head_ptr->return_node()) {
					fout << "\n" << nt_scan_head_ptr->return_data()->return_fragment_ion_mz() << "   " << nt_scan_head_ptr->return_data()->return_fragment_ion_int() << "   " << nt_scan_head_ptr->return_data()->return_union();
				}
				fout << "\nEND IONS";
			}
			if (return_used() == 0) {
				std::cout << "\n\nNo members!";
			}
		};

	private:
		scan_node_type nt_scan;
		size_type st_capacity;
		size_type st_used;
	};
}

#endif
