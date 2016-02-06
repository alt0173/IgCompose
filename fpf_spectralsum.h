/*
 *	File:   fpf_spectralsum.h
 *	Author: Lukah Dykes
 */



#ifndef FPF_SPECTRALSUM
#define	FPF_SPECTRALSUM
#include <cstdlib> // provides - size_t, NULL
#include <fstream> // provides - std::ifstream
#include <istream> // provides - std::istream::get, std::istream::peek
#include <sstream> // provides - std::istringstream
#include <string> // provides - std::string
#include <iostream> // provides - std::cin, std::cout
#include "fpf_node.h"
#include "fpf_scan.h"



namespace fpf_spectralsum {


	//
	// * * SCOPE VARIABLES * * 
	//

	typedef double value_type;
	//
	//

	typedef size_t size_type;
	//
	//

	typedef fpf_node::node<fpf_scan::scan*>* scan_node_type;
	//
	//

	typedef fpf_scan::scan* scan_data_type;
	//
	//

	int fpf_spectralsum_DEBUG_MODE;
	//
	//

	size_type count_mgf_scan = size_type();
	//
	//

	const value_type FILTER_PRECURSOR_RT = 0;
	//
	//

	const value_type FILTER_FRAGMENT_ION_INTENSITY = 8;
	//
	//

	class mgf {

	public:


		//
		// * * CONSTRUCTORS * * 
		//


		mgf() {
			nt_scan_head_ptr = NULL;
			nt_scan_tail_ptr = NULL;
			st_union_itr = 1;
		};

		~mgf() {
		};

		// OPERATORS

		void operator=(const mgf parse_0) {
			//mgf* tail_ptr;
		};

		// MODIFICATION MEMBER FUNCTIONS


		void input_parse(std::ifstream& fin, mgf*& c_mgf_ptr) {
			char c_inputstream;
			std::string s_inputstream = "";
			int switch_inputstream = int();
			scan_data_type dt_scan_inputstream = new fpf_scan::scan();
			value_type ss_inputstream;
			value_type vt_fragment_ion_mz_inputstream;
			value_type vt_fragment_ion_intensity_inputstream;
			value_type vt_precursor_mass_inputstream;
			value_type vt_precursor_rt_inputstream;
			fpf_scan::ion_data_type dt_ion_inputstream = new fpf_ion::ion();
			const size_type OUTPUT_INTERVAL = 100;
			std::cout << "\n\nParsing...\n";
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
					//long double?
					vt_precursor_rt_inputstream = ss_inputstream;
					s_inputstream.clear();
				}
				if ((switch_inputstream == 4) && (c_inputstream == ' ')) {
					std::istringstream(s_inputstream) >> ss_inputstream;
					//long double?
					vt_fragment_ion_mz_inputstream = ss_inputstream;
					switch_inputstream = 5;
					s_inputstream.clear();
				}
				if (s_inputstream == "PEPMASS=") {
					switch_inputstream = 3;
					s_inputstream.clear();
				}
				if ((switch_inputstream == 3) && (c_inputstream == '\n')) {
					std::istringstream(s_inputstream) >> ss_inputstream;
					vt_precursor_mass_inputstream = ss_inputstream;

					switch_inputstream = 4;
					s_inputstream.clear();
				}
				if ((switch_inputstream == 5) && (c_inputstream == '\n')) {
					std::istringstream(s_inputstream) >> ss_inputstream;
					//long double?
					vt_fragment_ion_intensity_inputstream = ss_inputstream;
					if (vt_fragment_ion_intensity_inputstream >= FILTER_FRAGMENT_ION_INTENSITY) {
						dt_ion_inputstream->set_fragment_ion_mz_vt(vt_fragment_ion_mz_inputstream);
						dt_ion_inputstream->set_fragment_ion_intensity_st(vt_fragment_ion_intensity_inputstream);
						fpf_node::list_insert_tail<fpf_scan::ion_data_type>(dt_ion_inputstream, dt_scan_inputstream->nt_return_ion_head_ptr(), dt_scan_inputstream->nt_return_ion_tail_ptr());
						dt_ion_inputstream = new fpf_ion::ion();
					}
					switch_inputstream = 4;
					s_inputstream.clear();
				}
				if ((switch_inputstream == 4) && ((c_inputstream == 'E'))) {
					switch_inputstream = 0;
					if (vt_precursor_rt_inputstream >= FILTER_PRECURSOR_RT) {
						dt_scan_inputstream->set_precursor_mass(vt_precursor_mass_inputstream);
						dt_scan_inputstream->set_precursor_rt(vt_precursor_rt_inputstream);
						fpf_node::list_insert_tail<scan_data_type>(dt_scan_inputstream, c_mgf_ptr->nt_return_scan_head_ptr(), c_mgf_ptr->nt_return_scan_tail_ptr());
						++count_mgf_scan;
						dt_scan_inputstream = new fpf_scan::scan();
					}
					if ((count_mgf_scan > 0) && (count_mgf_scan % OUTPUT_INTERVAL == 0)) {
						std::cout << "\nscan - " << count_mgf_scan << "   retention time - " << ((c_mgf_ptr->nt_return_scan_tail_ptr()->dt_return_data()->nt_return_precursor_rt()) / 60);
						if (count_mgf_scan > 2 * OUTPUT_INTERVAL - 1) {
							scan_node_type nt_delta_itr = c_mgf_ptr->nt_return_scan_tail_ptr();
							for (size_type i = 0; i < OUTPUT_INTERVAL; ++i) {
								nt_delta_itr = nt_delta_itr->return_down_node_nt();
							}
							std::cout << "   delta - " << ((c_mgf_ptr->nt_return_scan_tail_ptr()->dt_return_data()->nt_return_precursor_rt()) / 60) - ((nt_delta_itr->dt_return_data()->nt_return_precursor_rt()) / 60);
						}
					}
				}
				if (c_inputstream == '\n') {
					s_inputstream.clear();
				}
			}
			if (count_mgf_scan % OUTPUT_INTERVAL != 0) {
				std::cout << "\nscan - " << count_mgf_scan << "   retention time - " << ((c_mgf_ptr->nt_return_scan_tail_ptr()->dt_return_data()->nt_return_precursor_rt()) / 60);
				if (count_mgf_scan > 2 * OUTPUT_INTERVAL - 1) {
					scan_node_type nt_delta_itr = c_mgf_ptr->nt_return_scan_tail_ptr();
					for (size_type i = 0; i < OUTPUT_INTERVAL; ++i) {
						nt_delta_itr = nt_delta_itr->return_down_node_nt();
					}
					std::cout << "   delta - " << ((c_mgf_ptr->nt_return_scan_tail_ptr()->dt_return_data()->nt_return_precursor_rt()) / 60) - ((nt_delta_itr->dt_return_data()->nt_return_precursor_rt()) / 60);
				}
			}
		};
		//
		//

		void mgf_scan_ion_sum(mgf*& c_mgf) {
			size_type count_mgf_scan_ion_sum = size_type();
			const size_type st_output_interval = 100;
			std::cout << "\n\n\nSumming fragment ion spectra...\n";
			for (scan_node_type scan_ptr_itr = c_mgf->nt_return_scan_head_ptr(); scan_ptr_itr != NULL; scan_ptr_itr = scan_ptr_itr->return_up_node_nt()) {
				size_type scan_union_sum_count = fpf_scan::scan_ion_sum(scan_ptr_itr->dt_return_data());
				++count_mgf_scan_ion_sum;
				if (fpf_spectralsum_DEBUG_MODE == 0) {
					if ((count_mgf_scan_ion_sum > 0) && (count_mgf_scan_ion_sum % st_output_interval == 0)) {
						std::cout << "\nscan - " << count_mgf_scan_ion_sum;
						if (fpf_spectralsum_DEBUG_MODE == 1) {
							std::cout << " " << scan_ptr_itr->dt_return_data()->nt_return_precursor_rt() << " " << scan_ptr_itr->dt_return_data()->nt_return_precursor_mass() << "  " << scan_union_sum_count;
						}
					}
					if ((count_mgf_scan_ion_sum == count_mgf_scan) && !((count_mgf_scan_ion_sum > 0) && (count_mgf_scan_ion_sum % st_output_interval == 0))) {
						std::cout << "\nscan - " << count_mgf_scan_ion_sum;
						if (fpf_spectralsum_DEBUG_MODE == 1) {
							std::cout << " " << scan_ptr_itr->dt_return_data()->nt_return_precursor_rt() << " " << scan_ptr_itr->dt_return_data()->nt_return_precursor_mass() << "  " << scan_union_sum_count;
						}
					}
				}
			}
		};

		void mgf_scan_sum(mgf*& c_mgf) {
			scan_node_type nt_hold_scan = scan_node_type();
			scan_node_type nt_hold_scan_head_ptr = c_mgf->nt_return_scan_head_ptr();
			scan_data_type dt_scan_union = new fpf_scan::scan();
			size_type count_scan_1 = size_type();
			size_type count_scan_2 = size_type();
			static size_type st_output_interval = 100;
			std::cout << "\n\n\nSumming precursor ion spectra...\n";
			for (scan_node_type nt_scan_itr = c_mgf->nt_return_scan_head_ptr(); nt_scan_itr != NULL; nt_scan_itr = nt_scan_itr->return_up_node_nt()) {
				++count_scan_1;
				for (scan_node_type nt_scan_itr_2 = c_mgf->nt_return_scan_head_ptr(); nt_scan_itr_2 != NULL; nt_scan_itr_2 = nt_scan_itr_2->return_up_node_nt()) {				
					if ((nt_scan_itr != nt_scan_itr_2) && fpf_scan::union_precursor_mass(nt_scan_itr->dt_return_data(), nt_scan_itr_2->dt_return_data()) && fpf_scan::union_precursor_rt(nt_scan_itr->dt_return_data(), nt_scan_itr_2->dt_return_data())) {
						if (union_fragment_ion_sup_intensities(nt_scan_itr->dt_return_data(), nt_scan_itr_2->dt_return_data())) {
							dt_scan_union->set_precursor_mass(fpf_scan::return_mean_scan_mass_vt(nt_scan_itr->dt_return_data(), nt_scan_itr_2->dt_return_data()));
							dt_scan_union->set_precursor_rt(fpf_scan::return_mean_scan_rt_vt(nt_scan_itr->dt_return_data(), nt_scan_itr_2->dt_return_data()));
							dt_scan_union->set_scan_union_count(fpf_scan::return_sum_scan_union_count_st(nt_scan_itr->dt_return_data(), nt_scan_itr_2->dt_return_data()));
							fpf_scan::set_scan_ion_union(dt_scan_union, nt_scan_itr->dt_return_data(), nt_scan_itr_2->dt_return_data());
							fpf_node::list_insert_up<scan_data_type>(dt_scan_union, nt_scan_itr_2, c_mgf->nt_return_scan_head_ptr(), c_mgf->nt_return_scan_tail_ptr());							
							dt_scan_union = new fpf_scan::scan();
							if (fpf_spectralsum_DEBUG_MODE >= 6) {
								// not correct count
								std::cout << "\n\nMatch for scan " << count_scan_1 << " with scan " << count_scan_1 + count_scan_2;
								std::cout << "  " << nt_scan_itr_2->dt_return_data()->nt_return_precursor_rt() << " " << nt_scan_itr_2->dt_return_data()->nt_return_precursor_mass();
							}
							if (nt_scan_itr != nt_hold_scan_head_ptr) {
								if (nt_scan_itr->return_up_node_nt() == nt_scan_itr_2) {
									if (fpf_spectralsum_DEBUG_MODE >= 6) {
										std::cout << "   (nt_ion_itr != nt_hold_ion_head_ptr)  (nt_ion_itr->return_up_node_nt() == nt_ion_itr_2)";
									}
									nt_hold_scan = nt_scan_itr;
									nt_scan_itr = nt_scan_itr->return_up_node_nt()->return_up_node_nt();
									fpf_node::list_remove<scan_data_type>(nt_hold_scan);
									nt_hold_scan = nt_scan_itr_2;
									fpf_node::list_remove<scan_data_type>(nt_hold_scan);
									nt_scan_itr_2 = c_mgf->nt_return_scan_head_ptr();
								}
								else {
									if (fpf_spectralsum_DEBUG_MODE >= 6) {
										std::cout << "   (nt_ion_itr != nt_hold_ion_head_ptr)  !(nt_ion_itr->return_up_node_nt() == nt_ion_itr_2)";
									}
									nt_hold_scan = nt_scan_itr;
									nt_scan_itr = nt_scan_itr->return_up_node_nt();
									fpf_node::list_remove<scan_data_type>(nt_hold_scan);
									nt_hold_scan = nt_scan_itr_2;
									fpf_node::list_remove<scan_data_type>(nt_hold_scan);									
									nt_scan_itr_2 = c_mgf->nt_return_scan_head_ptr();
								}
							}
							else {
								if (nt_scan_itr->return_up_node_nt() == nt_scan_itr_2) {
									if (fpf_spectralsum_DEBUG_MODE >= 6) {
										std::cout << "   !(nt_ion_itr != nt_hold_ion_head_ptr)  (nt_ion_itr->return_up_node_nt() == nt_ion_itr_2)";
									}
									nt_scan_itr = nt_scan_itr->return_up_node_nt()->return_up_node_nt();
									fpf_node::list_remove_head<scan_data_type>(c_mgf->nt_return_scan_head_ptr());
									fpf_node::list_remove_head<scan_data_type>(c_mgf->nt_return_scan_head_ptr());
									nt_hold_scan_head_ptr = nt_scan_itr;
									nt_scan_itr_2 = c_mgf->nt_return_scan_head_ptr();
								}
								else {
									if (fpf_spectralsum_DEBUG_MODE >= 6) {
										std::cout << "   !(nt_ion_itr != nt_hold_ion_head_ptr)  !(nt_ion_itr->return_up_node_nt() == nt_ion_itr_2)";
									}
									nt_scan_itr = nt_scan_itr->return_up_node_nt();
									fpf_node::list_remove_head<scan_data_type>(c_mgf->nt_return_scan_head_ptr());
									nt_hold_scan_head_ptr = nt_scan_itr;
									nt_hold_scan = nt_scan_itr_2;
									fpf_node::list_remove<scan_data_type>(nt_hold_scan);
									nt_scan_itr_2 = c_mgf->nt_return_scan_head_ptr();
								}
							}
						}
						else {
							if (fpf_spectralsum_DEBUG_MODE == 6) {
								std::cout << "\n\nPartial match for scan " << count_scan_1 << " with scan " << count_scan_2;
								std::cout << "   ! " << nt_scan_itr->dt_return_data()->nt_return_precursor_rt() << " " << nt_scan_itr->dt_return_data()->nt_return_precursor_mass();
								std::cout << "  " << nt_scan_itr_2->dt_return_data()->nt_return_precursor_rt() << " " << nt_scan_itr_2->dt_return_data()->nt_return_precursor_mass();
								std::cout << "   ! " << fpf_scan::return_mean_scan_rt_vt(nt_scan_itr->dt_return_data(), nt_scan_itr_2->dt_return_data());
								std::cout << "  " << fpf_scan::return_mean_scan_mass_vt(nt_scan_itr->dt_return_data(), nt_scan_itr_2->dt_return_data());
							}
						}
					}
				}
			}
		};
		//
		//

		//void mgf_scan_ion_reset() {
		//    for (size_type i = size_type(); i < count_mgf_scan; ++i) {
		//        nt_scan[i].set_union_n(false);
		//        for (fpf_scan::scan::ion_node_type scan_ptr_itr = nt_scan[i].nt_return_ion_head_ptr(); scan_ptr_itr != NULL; scan_ptr_itr = scan_ptr_itr->return_up_node_nt()) {
		//            scan_ptr_itr->dt_return_data()->set_init_fragment_ion_union_b(false);
		//        }
		//    }
		//}


		//
		// * * CONSTANT MEMBER FUNCTIONS * * 
		//


		inline const size_type return_union_itr() const {
			return st_union_itr;
		};

		inline scan_node_type& nt_return_scan_head_ptr() {
			return nt_scan_head_ptr;
		};
		//		Returns a head pointer to a linked lift of ION classes for the 
		//		associated SCAN class. The pointer directs to the head node of 
		//		a linked list.

		inline scan_node_type& nt_return_scan_tail_ptr() {
			return nt_scan_tail_ptr;
		};
		//		Returns a tail pointer to a linked lift of ION classes for the 
		//		associated SCAN class. The pointer directs to the head node of 
		//		a linked list.

		void cout_mgf(mgf& c_mgf) const {
			size_type count_mgf_scan_cout = 1;
			for (scan_node_type nt_scan_itr = c_mgf.nt_return_scan_head_ptr(); nt_scan_itr != NULL; nt_scan_itr = nt_scan_itr->return_up_node_nt()) {
				if (count_mgf_scan_cout > 1) {
					std::cout << "\nBEGIN IONS";
				}
				else {
					std::cout << "BEGIN IONS";
				}
				std::cout << "\nTITLE=" << "NULL";
				std::cout << "\nRTINSECONDS=" << nt_scan_itr->dt_return_data()->nt_return_precursor_rt();
				std::cout << "\nPEPMASS=" << nt_scan_itr->dt_return_data()->nt_return_precursor_mass();
				for (fpf_scan::ion_node_type nt_ion_ptr = nt_scan_itr->dt_return_data()->nt_return_ion_head_ptr(); nt_ion_ptr != NULL; nt_ion_ptr = nt_ion_ptr->return_up_node_nt()) {
					std::cout << "\n" << nt_ion_ptr->dt_return_data()->return_fragment_ion_mz() << "   " << nt_ion_ptr->dt_return_data()->return_fragment_ion_intensity() << "   " << nt_ion_ptr->dt_return_data()->return_union_count_st();
				}
				std::cout << "\nEND IONS";
				++count_mgf_scan_cout;
			}
			if (count_mgf_scan_cout == 1) {
				std::cout << "\n\nNo members!";
			}
		};

		void fout_mgf(std::ofstream& fout, mgf*& c_mgf) const {
			if (c_mgf->nt_return_scan_head_ptr() == NULL) {
				//
				// break?
			}
			size_type count_mgf_scan_fout = 1;
			std::cout << "\n\n\nOutputting...";
			for (scan_node_type nt_scan_ptr_itr = c_mgf->nt_return_scan_head_ptr(); nt_scan_ptr_itr != NULL; nt_scan_ptr_itr = nt_scan_ptr_itr->return_up_node_nt()) {
				if (count_mgf_scan_fout > 1) {
					fout << "\nBEGIN IONS";
				}
				else {
					fout << "BEGIN IONS";
				}
				fout << "\nTITLE=" << "NULL";
				fout << "\nRTINSECONDS=" << nt_scan_ptr_itr->dt_return_data()->nt_return_precursor_rt();
				fout << "\nPEPMASS=" << nt_scan_ptr_itr->dt_return_data()->nt_return_precursor_mass();
				if (fpf_spectralsum_DEBUG_MODE >= 1) {
					fout << " # " << count_mgf_scan_fout;
					fout << "   ! nt_scan[i].return_union_b() " << nt_scan_ptr_itr->dt_return_data()->return_union_b();
					fout << " nt_scan[i].return_scan_union_count() " << nt_scan_ptr_itr->dt_return_data()->return_scan_union_count();
				}
				for (fpf_scan::ion_node_type nt_ion_ptr_itr = nt_scan_ptr_itr->dt_return_data()->nt_return_ion_head_ptr(); nt_ion_ptr_itr != NULL; nt_ion_ptr_itr = nt_ion_ptr_itr->return_up_node_nt()) {
					fout << "\n" << nt_ion_ptr_itr->dt_return_data()->return_fragment_ion_mz();
					fout << "  " << nt_ion_ptr_itr->dt_return_data()->return_fragment_ion_intensity();
					if (fpf_spectralsum_DEBUG_MODE >= 1) {
						fout << "  ! return_union_init_b() " << nt_ion_ptr_itr->dt_return_data()->return_union_init_b();
						fout << " " << nt_ion_ptr_itr->dt_return_data()->return_union_count_st();
						fout << "  dt_scan_inputstream->dt_return_data()->return_union_count_st() " << nt_ion_ptr_itr->dt_return_data()->return_union_count_st();
					}
				}
				fout << "\nEND IONS";
				++count_mgf_scan_fout;
			}
			if (count_mgf_scan_fout == 1) {
				std::cout << "\n\nNo members!";
			}
		};

	private:
		scan_node_type nt_scan_head_ptr;
		scan_node_type nt_scan_tail_ptr;
		size_type st_union_itr;
	};


	//
	// * * FUNCTIONS * * 
	//


	void set_debug(int set_fpf_spectralsum_DEBUG_MODE) {
		fpf_spectralsum_DEBUG_MODE = set_fpf_spectralsum_DEBUG_MODE;
	}

	//void debug_parse(mgf& c_mgf_ptr) {
	//	mgf::size_type st_count_itr = mgf::size_type();
	//	for (mgf::scan_node_type nt_scan_itr_ptr = c_mgf_ptr.nt_return_scan_head_ptr(); nt_scan_itr_ptr != NULL; nt_scan_itr_ptr = nt_scan_itr_ptr->return_up_node_nt()) {
	//		std::cout << "\n" << st_count_itr;
	//		std::cout << "\nnt_scan[i].nt_return_precursor_rt() " << nt_scan_itr_ptr->dt_return_data()->nt_return_precursor_rt;
	//		std::cout << "\nnt_scan[i].nt_return_precursor_mass() " << nt_scan_itr_ptr->dt_return_data()->nt_return_precursor_mz;
	//		for (fpf_scan::scan::ion_node_type nt_ion_ptr_itr = nt_scan_itr_ptr->dt_return_data()->nt_return_ion_head_ptr; nt_ion_ptr_itr != NULL; nt_ion_ptr_itr = nt_ion_ptr_itr->return_up_node_nt()) {
	//			std::cout << "\n" << nt_ion_ptr_itr->dt_return_data()->return_fragment_ion_mz() << "  " << nt_ion_ptr_itr->dt_return_data()->return_fragment_ion_intensity();
	//		}
	//		++st_count_itr;
	//	}
	//	if (st_count_itr == 0) {
	//		std::cout << "\n\nNo members!";
	//	}
	//};
}

#endif