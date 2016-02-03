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

	typedef long double value_type;
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

	const value_type FILTER_PRECURSOR_RT = 600;
	//
	//

	const value_type FILTER_FRAGMENT_ION_INTENSITY = 3;
	//
	//

	class mgf {

	public:


		//
		// * * CONSTRUCTORS * * 
		//


		mgf() {
			scan_node_type nt_scan_head_ptr = NULL;
			scan_node_type nt_scan_tail_ptr = NULL;
			size_type st_union_itr = size_type();
		};

		~mgf() {
		};

		// OPERATORS

		void operator=(const mgf parse_0) {
			//mgf* tail_ptr;
		};

		// MODIFICATION MEMBER FUNCTIONS


		void input_parse(std::ifstream& fin, mgf& c_mgf) {
			char c_inputstream;
			std::string s_inputstream = "";
			int switch_inputstream = int();
			scan_data_type nt_scan_itr = new fpf_scan::scan();
			value_type ss_inputstream;
			value_type vt_inputstream;
			value_type vt_inputstream_2;
			fpf_scan::ion_data_type ion_inputstream;
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
					vt_inputstream = ss_inputstream;
					nt_scan_itr->set_precursor_rt(vt_inputstream);
					s_inputstream.clear();
				}
				if ((switch_inputstream == 4) && (c_inputstream == ' ')) {
					std::istringstream(s_inputstream) >> ss_inputstream;
					//long double?
					vt_inputstream = ss_inputstream;
					switch_inputstream = 5;
					s_inputstream.clear();
				}
				if ((switch_inputstream == 5) && (c_inputstream == '\n')) {
					std::istringstream(s_inputstream) >> ss_inputstream;
					//long double?
					vt_inputstream_2 = ss_inputstream;
					if (vt_inputstream_2 >= FILTER_FRAGMENT_ION_INTENSITY) {
						ion_inputstream = new fpf_ion::ion();
						ion_inputstream->set_fragment_ion_mz_vt(vt_inputstream);
						ion_inputstream->set_fragment_ion_intensity_st(vt_inputstream_2);
						fpf_node::list_insert_tail<fpf_scan::ion_data_type>(ion_inputstream, nt_scan_itr->nt_return_ion_head_ptr(), nt_scan_itr->nt_return_ion_tail_ptr());
					}
					switch_inputstream = 4;
					s_inputstream.clear();
				}
				if (s_inputstream == "PEPMASS=") {
					switch_inputstream = 3;
					s_inputstream.clear();
				}
				if ((switch_inputstream == 3) && (c_inputstream == '\n')) {
					std::istringstream(s_inputstream) >> ss_inputstream;
					vt_inputstream = ss_inputstream;
					nt_scan_itr->set_precursor_mass(vt_inputstream);
					switch_inputstream = 4;
					s_inputstream.clear();
				}
				if ((switch_inputstream == 4) && ((c_inputstream == 'E'))) {
					switch_inputstream = 0;
					if (nt_scan_itr->nt_return_precursor_rt() >= FILTER_PRECURSOR_RT) {
						fpf_node::list_insert_tail<scan_data_type>(nt_scan_itr, c_mgf.nt_return_scan_head_ptr(), c_mgf.nt_return_scan_tail_ptr());
						nt_scan_itr = new fpf_scan::scan();
						++count_mgf_scan;
					}
					if ((count_mgf_scan > 0) && (count_mgf_scan % OUTPUT_INTERVAL == 0)) {
						std::cout << "\nscan - " << count_mgf_scan << "   retention time - " << ((c_mgf.nt_return_scan_tail_ptr()->return_down_node_nt()->return_data_dt()->nt_return_precursor_rt()) / 60);
						if (count_mgf_scan > 2 * OUTPUT_INTERVAL - 1) {
							scan_node_type nt_delta_itr = c_mgf.nt_return_scan_tail_ptr();
							for (size_type i = 0; i < OUTPUT_INTERVAL; ++i) {
								nt_delta_itr = nt_delta_itr->return_down_node_nt();
							}
							std::cout << "   delta - " << ((c_mgf.nt_return_scan_tail_ptr()->return_down_node_nt()->return_data_dt()->nt_return_precursor_rt()) / 60) - ((nt_delta_itr->return_down_node_nt()->return_data_dt()->nt_return_precursor_rt()) / 60);
						}
					}
				}
				if (c_inputstream == '\n') {
					s_inputstream.clear();
				}
			}
			if (count_mgf_scan % OUTPUT_INTERVAL != 0) {
				std::cout << "\nscan - " << count_mgf_scan << "   retention time - " << ((c_mgf.nt_return_scan_tail_ptr()->return_down_node_nt()->return_data_dt()->nt_return_precursor_rt()) / 60);
				if (count_mgf_scan > 2 * OUTPUT_INTERVAL - 1) {
					scan_node_type nt_delta_itr = c_mgf.nt_return_scan_tail_ptr();
					for (size_type i = 0; i < OUTPUT_INTERVAL; ++i) {
						nt_delta_itr = nt_delta_itr->return_down_node_nt();
					}
					std::cout << "   delta - " << ((c_mgf.nt_return_scan_tail_ptr()->return_down_node_nt()->return_data_dt()->nt_return_precursor_rt()) / 60) - ((nt_delta_itr->return_down_node_nt()->return_data_dt()->nt_return_precursor_rt()) / 60);
				}
			}
		};
		//
		//

		void mgf_scan_ion_sum(mgf& c_mgf) {
			size_type count_mgf_scan_ion_sum = size_type();
			const size_type st_output_interval = 100;
			std::cout << "\n\n\nSumming fragment ion spectra...\n";
			for (scan_node_type scan_ptr_itr = c_mgf.nt_return_scan_head_ptr(); scan_ptr_itr != NULL; scan_ptr_itr = scan_ptr_itr->return_up_node_nt()) {
				fpf_scan::scan_ion_sum(scan_ptr_itr->return_data_dt());
				++count_mgf_scan_ion_sum;
				if (fpf_spectralsum_DEBUG_MODE == 0) {
					if ((count_mgf_scan_ion_sum > 0) && (count_mgf_scan_ion_sum % st_output_interval == 0)) {
						std::cout << "\nscan - " << count_mgf_scan_ion_sum;
					}
					if ((count_mgf_scan_ion_sum + 1 == count_mgf_scan) && !((count_mgf_scan_ion_sum > 0) && (count_mgf_scan_ion_sum % st_output_interval == 0))) {
						std::cout << "\nscan - " << count_mgf_scan_ion_sum;
					}
				}
			}
		};

		void mgf_scan_sum(mgf& c_mgf) {
			// sup intensities
			scan_node_type nt_hold_scan = scan_node_type();
			scan_node_type nt_hold_scan_head_ptr = c_mgf.nt_return_scan_head_ptr();
			scan_data_type d_scan_union;
			size_type count_scan_1 = size_type();
			size_type count_scan_2 = size_type();
			for (scan_node_type nt_scan_itr = c_mgf.nt_return_scan_head_ptr(); nt_scan_itr != NULL; nt_scan_itr = nt_scan_itr->return_up_node_nt()) {
				++count_scan_1;
				for (scan_node_type nt_scan_itr_2 = c_mgf.nt_return_scan_head_ptr(); nt_scan_itr_2 != NULL; nt_scan_itr_2 = nt_scan_itr_2->return_up_node_nt()) {
					++count_scan_2;
					if ((nt_scan_itr != nt_scan_itr_2) && fpf_scan::union_precursor_rt(nt_scan_itr->return_data_dt(), nt_scan_itr_2->return_data_dt()) && fpf_scan::union_precursor_rt(nt_scan_itr->return_data_dt(), nt_scan_itr_2->return_data_dt())) {
						d_scan_union = new fpf_scan::scan();
						d_scan_union->set_precursor_mass(fpf_scan::return_mean_scan_mass_vt(nt_scan_itr->return_data_dt(), nt_scan_itr_2->return_data_dt()));
						d_scan_union->set_precursor_rt(fpf_scan::return_mean_scan_rt_vt(nt_scan_itr->return_data_dt(), nt_scan_itr_2->return_data_dt()));
						d_scan_union->set_scan_union_count(fpf_scan::return_sum_scan_union_count_st(nt_scan_itr->return_data_dt(), nt_scan_itr_2->return_data_dt()));
						fpf_node::list_insert_up<scan_data_type>(d_scan_union, nt_scan_itr_2, c_mgf.nt_return_scan_head_ptr(), c_mgf.nt_return_scan_tail_ptr());
						if (fpf_spectralsum_DEBUG_MODE == 6) {
							std::cout << "\n Match for scan " << count_scan_1 << " with scan " << count_scan_2;
							std::cout << "   ! nt_return_precursor_mass() " << nt_scan_itr->return_data_dt()->nt_return_precursor_mass() << " nt_return_precursor_rt() " << nt_scan_itr->return_data_dt()->nt_return_precursor_rt();
							std::cout << "  nt_return_precursor_mass() " << nt_scan_itr_2->return_data_dt()->nt_return_precursor_mass() << " nt_return_precursor_rt() " << nt_scan_itr_2->return_data_dt()->nt_return_precursor_rt();
							std::cout << "   ! return_mean_scan_mass_vt() " << fpf_scan::return_mean_scan_mass_vt(nt_scan_itr->return_data_dt(), nt_scan_itr_2->return_data_dt());
							std::cout << " return_mean_scan_rt_vt() " << fpf_scan::return_mean_scan_rt_vt(nt_scan_itr->return_data_dt(), nt_scan_itr_2->return_data_dt());
						}

						if (nt_scan_itr != nt_hold_scan_head_ptr) {
							if (nt_scan_itr->return_up_node_nt() == nt_scan_itr_2) {
								if (fpf_spectralsum_DEBUG_MODE == 6) {
									std::cout << "   (nt_ion_itr != nt_hold_ion_head_ptr) (nt_ion_itr->return_up_node_nt() == nt_ion_itr_2)";
								}
								nt_hold_scan = nt_scan_itr;
								nt_scan_itr = nt_scan_itr->return_up_node_nt()->return_up_node_nt();
								fpf_node::list_remove<scan_data_type>(nt_hold_scan);
								nt_scan_itr = nt_scan_itr_2;
								nt_scan_itr_2 = nt_scan_itr_2->return_up_node_nt();
								fpf_node::list_remove<scan_data_type>(nt_hold_scan);
							}
							else {
								if (fpf_spectralsum_DEBUG_MODE == 6) {
									std::cout << "   (nt_ion_itr != nt_hold_ion_head_ptr) !(nt_ion_itr->return_up_node_nt() == nt_ion_itr_2)";
								}
								nt_hold_scan = nt_scan_itr;
								nt_scan_itr = nt_scan_itr->return_up_node_nt();
								fpf_node::list_remove<scan_data_type>(nt_hold_scan);
								nt_hold_scan = nt_scan_itr_2;
								fpf_node::list_remove<scan_data_type>(nt_hold_scan);
								nt_scan_itr_2 = c_mgf.nt_return_scan_head_ptr();
							}
						}
						else {
							if (nt_scan_itr->return_up_node_nt() == nt_scan_itr_2) {
								if (fpf_spectralsum_DEBUG_MODE == 6) {
									std::cout << "   !(nt_ion_itr != nt_hold_ion_head_ptr) (nt_ion_itr->return_up_node_nt() == nt_ion_itr_2)";
								}
								nt_scan_itr = nt_scan_itr->return_up_node_nt()->return_up_node_nt();
								fpf_node::list_remove_head<scan_data_type>(c_mgf.nt_return_scan_head_ptr());
								fpf_node::list_remove_head<scan_data_type>(c_mgf.nt_return_scan_head_ptr());
								nt_hold_scan_head_ptr = c_mgf.nt_return_scan_head_ptr();
							}
							else {
								if (fpf_spectralsum_DEBUG_MODE == 6) {
									std::cout << "   !(nt_ion_itr != nt_hold_ion_head_ptr) !(nt_ion_itr->return_up_node_nt() == nt_ion_itr_2)";
								}
								fpf_node::list_remove_head<scan_data_type>(c_mgf.nt_return_scan_head_ptr());
								nt_hold_scan_head_ptr = c_mgf.nt_return_scan_head_ptr();
								nt_hold_scan = nt_scan_itr_2;
								nt_scan_itr_2 = nt_scan_itr_2->return_up_node_nt();
								fpf_node::list_remove<scan_data_type>(nt_hold_scan);
							}
						}
					}
				}
			}
		};
		//
		//

		//void mgf_scan_sum(const mgf& c_main, mgf& c_union) {
		//    size_type st_used_prev = size_type();
		//    static size_type st_output_interval = 100;
		//    bool union_condition = bool();
		//    size_type forward_match_false = size_type();
		//    size_type forward_match_true = size_type();
		//    size_type forward_match_false_matched = size_type();
		//    size_type union_false_count = size_type();
		//    size_type union_true_count = size_type();
		//    c_union.st_union_itr = c_main.st_union_itr + 1;
		//    std::cout << "\n\n\nSumming precursor ion spectra...\n";
		//    for (size_type i = 0; i < c_main.return_used(); ++i) {
		//        for (size_type j = i; j < c_main.return_used(); j) {
		//            if ((i != j) && (union_precursor_mass(c_main.nt_scan[i], c_main.nt_scan[j])) && union_precursor_rt(c_main.nt_scan[i], c_main.nt_scan[j])) {
		//                if (union_fragment_ion_sup_intensities(c_main.nt_scan[i], c_main.nt_scan[j])) {
		//                    if (fpf_spectralsum_DEBUG_MODE == 2) {
		//                        ++forward_match_true;
		//                        std::cout << "\nscan_1 -  mass " << nt_scan[i].nt_return_precursor_mass() << "  retention time " << (nt_scan[i].nt_return_precursor_rt() / 60);
		//                        std::cout << " -  scan_2 mass " << nt_scan[j].nt_return_precursor_mass() << "  retention time " << (nt_scan[j].nt_return_precursor_rt() / 60)
		//                                << "   ! scan_1.return_union_b() " << c_main.nt_scan[i].return_union_b() << "  scan_2.return_union_b() " << c_main.nt_scan[j].return_union_b()
		//                                << "  union_precursor_mass() " << union_precursor_mass(c_main.nt_scan[i], c_main.nt_scan[j]) << "  union_precursor_rt() " << union_precursor_rt(c_main.nt_scan[i], c_main.nt_scan[j]);
		//                        std::cout << "\n\n--- forward match for scan " << i << " with scan " << j << "   ! forward_match_true " << forward_match_true << "\n\n";
		//                    }
		//                    c_main.nt_scan[i].set_union_n(true);
		//                    c_main.nt_scan[j].set_union_n(true);
		//                    c_union.nt_scan[c_union.st_used] = scan_union(c_main.nt_scan[i], c_main.nt_scan[j]);
		//                    ++c_union.st_used;
		//                    ++union_true_count;
		//                    union_condition = true;
		//                } else {
		//                    if (fpf_spectralsum_DEBUG_MODE == 2) {
		//                        std::cout << "\nscan_1 -  mass " << nt_scan[i].nt_return_precursor_mass() << "  retention time " << (nt_scan[i].nt_return_precursor_rt() / 60);
		//                        std::cout << " -  scan_2 mass " << nt_scan[j].nt_return_precursor_mass() << "  retention time " << (nt_scan[j].nt_return_precursor_rt() / 60)
		//                                << "   ! scan_1.return_union_b() " << c_main.nt_scan[i].return_union_b() << "  scan_2.return_union_b() " << c_main.nt_scan[j].return_union_b()
		//                                << "  union_precursor_mass() " << union_precursor_mass(c_main.nt_scan[i], c_main.nt_scan[j]) << "  union_precursor_rt() " << union_precursor_rt(c_main.nt_scan[i], c_main.nt_scan[j]);
		//                        std::cout << "\n\n--- partial forward match for scan " << i << " with scan " << j << "  * below fragment ion condition * " << "  ! forward_match_false " << forward_match_false << "\n\n";
		//                    }
		//                }
		//            }
		//            if (j + 1 == c_main.return_used()) {
		//                if (!(c_main.nt_scan[i].return_union_b())) {
		//                    c_union.nt_scan[c_union.st_used] = c_main.nt_scan[i];
		//                    ++c_union.st_used;
		//                    ++union_false_count;
		//                    ++forward_match_false_matched;
		//                }
		//                ++forward_match_false;
		//                if (fpf_spectralsum_DEBUG_MODE == 2) {
		//                    std::cout << "\n--- no forward match for scan " << i << "   ! c_main.nt_scan[i].return_union_b() " << (c_main.nt_scan[i].return_union_b()) << "  forward_match_false " << forward_match_false << "  forward_match_false_matched " << forward_match_false_matched << "\n";
		//                }
		//            }
		//            if (union_condition) {
		//                if (fpf_spectralsum_DEBUG_MODE == 0) {
		//                    if ((i > 0) && (i % st_output_interval == 0)) {
		//                        std::cout << "\nscan - " << i << "   union itr" << c_union.return_union_itr() << " - matched " << union_true_count;
		//                        if (c_main.st_used > 2 * st_output_interval - 1) {
		//                            std::cout << " - delta " << union_true_count - st_used_prev;
		//                        }
		//                        std::cout << " - unmatched " << union_false_count << " - total " << c_union.st_used;
		//                        std::cout << "   retention time - " << ((c_main.nt_scan[i].nt_return_precursor_rt()) / 60);
		//                        st_used_prev = union_true_count;
		//                    }
		//                    if (i + 1 == c_main.return_used() && !((i > 0) && (i % st_output_interval == 0))) {
		//                        std::cout << "\nscan - " << c_main.return_used() << "   union itr" << c_union.return_union_itr() << " -  matched " << union_true_count;
		//                        if (c_union.st_used > 2 * st_output_interval - 1) {
		//                            std::cout << " - delta " << union_true_count - st_used_prev;
		//                        }
		//                        std::cout << " - unmatched " << union_false_count << " - total " << c_union.st_used;
		//                        if (c_union.st_used > 2 * st_output_interval - 1) {
		//                            std::cout << "   retention time - " << ((c_main.nt_scan[i].nt_return_precursor_rt()) / 60);
		//                        }
		//                    }
		//                }
		//                ++i;
		//                ++j;
		//                union_condition = false;
		//            } else {
		//                ++j;
		//            }
		//        }
		//        if (!union_condition) {
		//            if (fpf_spectralsum_DEBUG_MODE == 0) {
		//                if ((i > 0) && (i % st_output_interval == 0)) {
		//                    std::cout << "\nscan - " << i << "   union itr" << c_union.return_union_itr() << " - " << union_true_count;
		//                    // here?
		//                    if (c_main.st_used > 2 * st_output_interval - 1) {
		//                        std::cout << " - delta " << union_true_count - st_used_prev;
		//                    }
		//                    std::cout << " - unmatched " << union_false_count << " - total " << c_union.st_used;
		//                    std::cout << "   retention time - " << ((c_main.nt_scan[i].nt_return_precursor_rt()) / 60);
		//                    st_used_prev = union_true_count;
		//                }
		//                if (i + 1 == c_main.return_used() && !((i > 0) && (i % st_output_interval == 0))) {
		//                    std::cout << "\nscan - " << c_main.return_used() << "   union itr" << c_union.return_union_itr() << " - " << union_true_count;
		//                    if (c_union.st_used > 2 * st_output_interval - 1) {
		//                        std::cout << " - delta " << union_true_count - st_used_prev;
		//                    }
		//                    std::cout << " - unmatched " << union_false_count << " - total " << c_union.st_used;
		//                    if (c_union.st_used > 2 * st_output_interval - 1) {
		//                        std::cout << "   retention time - " << ((c_main.nt_scan[i].nt_return_precursor_rt()) / 60);
		//                    }
		//                }
		//            }
		//        }
		//    }
		//};
		////
		////

		//void mgf_scan_ion_reset() {
		//    for (size_type i = size_type(); i < count_mgf_scan; ++i) {
		//        nt_scan[i].set_union_n(false);
		//        for (fpf_scan::scan::ion_node_type scan_ptr_itr = nt_scan[i].nt_return_ion_head_ptr(); scan_ptr_itr != NULL; scan_ptr_itr = scan_ptr_itr->return_up_node_nt()) {
		//            scan_ptr_itr->return_data_dt()->set_init_fragment_ion_union_b(false);
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
				std::cout << "\nRTINSECONDS=" << nt_scan_itr->return_data_dt()->nt_return_precursor_rt();
				std::cout << "\nPEPMASS=" << nt_scan_itr->return_data_dt()->nt_return_precursor_mass();
				for (fpf_scan::ion_node_type nt_ion_ptr = nt_scan_itr->return_data_dt()->nt_return_ion_head_ptr(); nt_ion_ptr != NULL; nt_ion_ptr = nt_ion_ptr->return_up_node_nt()) {
					std::cout << "\n" << nt_ion_ptr->return_data_dt()->return_fragment_ion_mz() << "   " << nt_ion_ptr->return_data_dt()->return_fragment_ion_intensity() << "   " << nt_ion_ptr->return_data_dt()->return_union_count_st();
				}
				std::cout << "\nEND IONS";
				++count_mgf_scan_cout;
			}
			if (count_mgf_scan_cout == 1) {
				std::cout << "\n\nNo members!";
			}
		};

		void fout_mgf(std::ofstream& fout, mgf& c_mgf) const {
			size_type count_mgf_scan_fout = 1;
			std::cout << "\n\n\nOutputting...";
			for (scan_node_type nt_scan_itr = c_mgf.nt_return_scan_head_ptr(); nt_scan_itr != NULL; nt_scan_itr = nt_scan_itr->return_up_node_nt()) {
				if (count_mgf_scan_fout > 1) {
					fout << "\nBEGIN IONS";
				}
				else {
					fout << "BEGIN IONS";
				}
				fout << "\nTITLE=" << "NULL";
				fout << "\nRTINSECONDS=" << nt_scan_itr->return_data_dt()->nt_return_precursor_rt();
				fout << "\nPEPMASS=" << nt_scan_itr->return_data_dt()->nt_return_precursor_mass();
				if (fpf_spectralsum_DEBUG_MODE >= 1) {
					fout << " # " << count_mgf_scan_fout << "   ! nt_scan[i].return_union_b() " << nt_scan_itr->return_data_dt()->return_union_b() << " nt_scan[i].return_scan_union_count() " << nt_scan_itr->return_data_dt()->return_scan_union_count();
				}
				for (fpf_scan::ion_node_type nt_ion_ptr = nt_scan_itr->return_data_dt()->nt_return_ion_head_ptr(); nt_ion_ptr != NULL; nt_ion_ptr = nt_ion_ptr->return_up_node_nt()) {
					fout << "\n" << nt_ion_ptr->return_data_dt()->return_fragment_ion_mz() << "   " << nt_ion_ptr->return_data_dt()->return_fragment_ion_intensity() << "   " << nt_ion_ptr->return_data_dt()->return_union_count_st();
					if (fpf_spectralsum_DEBUG_MODE >= 1) {
						fout << "  ! nt_scan_itr->return_data_dt()->return_union_init_b() " << nt_ion_ptr->return_data_dt()->return_union_init_b() << "  nt_scan_itr->return_data_dt()->return_union_count_st() " << nt_ion_ptr->return_data_dt()->return_union_count_st();
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

	//void debug_parse(mgf& c_mgf) {
	//	mgf::size_type st_count_itr = mgf::size_type();
	//	for (mgf::scan_node_type nt_scan_itr_ptr = c_mgf.nt_return_scan_head_ptr(); nt_scan_itr_ptr != NULL; nt_scan_itr_ptr = nt_scan_itr_ptr->return_up_node_nt()) {
	//		std::cout << "\n" << st_count_itr;
	//		std::cout << "\nnt_scan[i].nt_return_precursor_rt() " << nt_scan_itr_ptr->return_data_dt()->nt_return_precursor_rt;
	//		std::cout << "\nnt_scan[i].nt_return_precursor_mass() " << nt_scan_itr_ptr->return_data_dt()->nt_return_precursor_mz;
	//		for (fpf_scan::scan::ion_node_type nt_ion_ptr_itr = nt_scan_itr_ptr->return_data_dt()->nt_return_ion_head_ptr; nt_ion_ptr_itr != NULL; nt_ion_ptr_itr = nt_ion_ptr_itr->return_up_node_nt()) {
	//			std::cout << "\n" << nt_ion_ptr_itr->return_data_dt()->return_fragment_ion_mz() << "  " << nt_ion_ptr_itr->return_data_dt()->return_fragment_ion_intensity();
	//		}
	//		++st_count_itr;
	//	}
	//	if (st_count_itr == 0) {
	//		std::cout << "\n\nNo members!";
	//	}
	//};
}

#endif
