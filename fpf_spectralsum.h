// * * fpf_spectralsum.h * *
// 
// Lukah Dykes - Flinders Proteomics Facility - 2016
// 
// * * * * *
 
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

	const value_type FILTER_PION_RT = 0;
	//
	//

	const value_type FILTER_FION_INTENSITY = 10;
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
			value_type vt_inputstream;
			value_type vt_fragment_ion_mz_inputstream;
			size_type st_inputstream;
			size_type st_fragment_ion_intensity_inputstream;
			value_type vt_precursor_mass_inputstream;
			value_type vt_precursor_rt_inputstream;
			fpf_scan::scan::fion_data_type dt_ion_inputstream = new fpf_fion::fion();
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
					std::istringstream(s_inputstream) >> vt_inputstream;
					//long double?
					vt_precursor_rt_inputstream = vt_inputstream;
					//switch_inputstream = 4;
					s_inputstream.clear();
				}
				if ((switch_inputstream == 4) && (c_inputstream == ' ')) {
					std::istringstream(s_inputstream) >> vt_inputstream;
					//long double?
					vt_fragment_ion_mz_inputstream = vt_inputstream;
					switch_inputstream = 5;
					c_inputstream = '0';
					s_inputstream.clear();
				}
				if (s_inputstream == "PEPMASS=") {
					switch_inputstream = 3;
					s_inputstream.clear();
				}
				if ((switch_inputstream == 3) && (c_inputstream == '\n')) {
					std::istringstream(s_inputstream) >> vt_inputstream;
					vt_precursor_mass_inputstream = vt_inputstream;

					switch_inputstream = 4;
					s_inputstream.clear();
				}
				if ((switch_inputstream == 5) && ((c_inputstream == '\n') || (c_inputstream == ' '))) {
					std::istringstream(s_inputstream) >> st_inputstream;
					//long double?
					st_fragment_ion_intensity_inputstream = st_inputstream;
					if (st_fragment_ion_intensity_inputstream >= FILTER_FION_INTENSITY) {
						dt_ion_inputstream->set_fragment_ion_mz(vt_fragment_ion_mz_inputstream);
						dt_ion_inputstream->set_fragment_ion_intensity(st_fragment_ion_intensity_inputstream);
						fpf_node::list_insert_tail<fpf_scan::scan::fion_data_type>(dt_ion_inputstream, dt_scan_inputstream->nt_return_fion_head_ptr(), dt_scan_inputstream->nt_return_fion_tail_ptr());
						dt_ion_inputstream = new fpf_fion::fion();
					}
					switch_inputstream = 4;
					s_inputstream.clear();
				}
				if (s_inputstream == "END") {
					switch_inputstream = 0;
					if (vt_precursor_rt_inputstream >= FILTER_PION_RT) {
						dt_scan_inputstream->set_pion_mass(vt_precursor_mass_inputstream);
						dt_scan_inputstream->set_pion_rt(vt_precursor_rt_inputstream);
						fpf_node::list_insert_tail<scan_data_type>(dt_scan_inputstream, c_mgf_ptr->nt_return_scan_head_ptr(), c_mgf_ptr->nt_return_scan_tail_ptr());
						++count_mgf_scan;
						dt_scan_inputstream = new fpf_scan::scan();
					}
					if ((count_mgf_scan > 0) && (count_mgf_scan % OUTPUT_INTERVAL == 0)) {
						std::cout << "\nscan - " << count_mgf_scan << "   retention time - " << ((c_mgf_ptr->nt_return_scan_tail_ptr()->dt_return_data()->nt_return_precursor_rt()) / 60);
						if (count_mgf_scan > 2 * OUTPUT_INTERVAL - 1) {
							scan_node_type nt_delta_itr = c_mgf_ptr->nt_return_scan_tail_ptr();
							for (size_type i = 0; i < OUTPUT_INTERVAL; ++i) {
								nt_delta_itr = nt_delta_itr->nt_return_down_node();
							}
							//std::cout << "   delta - " << ((c_mgf_ptr->nt_return_scan_tail_ptr()->dt_return_data()->nt_return_precursor_rt()) / 60) - ((nt_delta_itr->dt_return_data()->nt_return_precursor_rt()) / 60);
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
						nt_delta_itr = nt_delta_itr->nt_return_down_node();
					}
					//std::cout << "   delta - " << ((c_mgf_ptr->nt_return_scan_tail_ptr()->dt_return_data()->nt_return_precursor_rt()) / 60) - ((nt_delta_itr->dt_return_data()->nt_return_precursor_rt()) / 60);
				}
			}
		};
		//
		//

		void mgf_scan_ion_sum(mgf*& c_mgf) {
			size_type count_mgf_scan_ion_sum = size_type();
			const size_type st_output_interval = 100;
			std::cout << "\n\n\nSumming fragment fion spectra...\n";
			for (scan_node_type scan_ptr_itr = c_mgf->nt_return_scan_head_ptr(); scan_ptr_itr != NULL; scan_ptr_itr = scan_ptr_itr->nt_return_up_node()) {
				size_type scan_union_sum_count = fpf_scan::scan_fion_sum(scan_ptr_itr->dt_return_data());
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
			const size_type st_output_interval = 100;
			std::cout << "\n\n\nSumming precursor fion spectra...\n";
			for (scan_node_type nt_scan_itr = c_mgf->nt_return_scan_head_ptr(); nt_scan_itr != NULL; nt_scan_itr = nt_scan_itr->nt_return_up_node()) {
				++count_scan_1;
				if ((count_scan_1 > 0) && (count_scan_1 % st_output_interval == 0)) {
					if (fpf_spectralsum_DEBUG_MODE == 0) {
						std::cout << "\nscan - " << count_scan_1 << "   summed - " << count_scan_2;
					}
				}
				for (scan_node_type nt_scan_itr_2 = c_mgf->nt_return_scan_head_ptr(); nt_scan_itr_2 != NULL; nt_scan_itr_2 = nt_scan_itr_2->nt_return_up_node()) {
					if ((nt_scan_itr != nt_scan_itr_2) && fpf_scan::union_precursor_mass(nt_scan_itr->dt_return_data(), nt_scan_itr_2->dt_return_data()) && fpf_scan::union_precursor_rt(nt_scan_itr->dt_return_data(), nt_scan_itr_2->dt_return_data())) {
						if (union_fragment_ion_sup_intensities(nt_scan_itr->dt_return_data(), nt_scan_itr_2->dt_return_data())) {
							++count_scan_1;
							++count_scan_2;
							dt_scan_union->set_pion_mass(fpf_scan::return_mean_scan_mass_vt(nt_scan_itr->dt_return_data(), nt_scan_itr_2->dt_return_data()));
							dt_scan_union->set_pion_rt(fpf_scan::return_mean_scan_rt_vt(nt_scan_itr->dt_return_data(), nt_scan_itr_2->dt_return_data()));
							dt_scan_union->set_scan_union_count(fpf_scan::return_sum_scan_union_count_st(nt_scan_itr->dt_return_data(), nt_scan_itr_2->dt_return_data()));
							fpf_scan::set_scan_fion_union(dt_scan_union, nt_scan_itr->dt_return_data(), nt_scan_itr_2->dt_return_data());
							fpf_node::list_insert_up<scan_data_type>(dt_scan_union, nt_scan_itr_2, c_mgf->nt_return_scan_head_ptr(), c_mgf->nt_return_scan_tail_ptr());
							dt_scan_union = new fpf_scan::scan();
							if (fpf_spectralsum_DEBUG_MODE >= 6) {
								// not correct count
								std::cout << "\nMatch for scan " << count_scan_1 << " with scan " << count_scan_1 + count_scan_2 << "\n\n";
								std::cout << "   ! " << nt_scan_itr->dt_return_data()->nt_return_precursor_rt() << " " << nt_scan_itr->dt_return_data()->nt_return_precursor_mass();
								std::cout << "  " << nt_scan_itr_2->dt_return_data()->nt_return_precursor_rt() << " " << nt_scan_itr_2->dt_return_data()->nt_return_precursor_mass();
								std::cout << "   ! " << fpf_scan::return_mean_scan_rt_vt(nt_scan_itr->dt_return_data(), nt_scan_itr_2->dt_return_data());
								std::cout << "  " << fpf_scan::return_mean_scan_mass_vt(nt_scan_itr->dt_return_data(), nt_scan_itr_2->dt_return_data());
							}
							if ((count_scan_1 > 0) && (count_scan_1 % st_output_interval == 0)) {
								if (fpf_spectralsum_DEBUG_MODE == 0) {
									std::cout << "\nscan - " << count_scan_1 << "   summed - " << count_scan_2;
								}
							}
							if (nt_scan_itr != nt_hold_scan_head_ptr) {
								if (nt_scan_itr->nt_return_up_node() == nt_scan_itr_2) {
									if (fpf_spectralsum_DEBUG_MODE >= 6) {
										std::cout << "   (nt_ion_itr != nt_hold_ion_head_ptr)  (nt_ion_itr->nt_return_up_node() == nt_ion_itr_2)\n";
									}
									nt_hold_scan = nt_scan_itr;
									nt_scan_itr = nt_scan_itr->nt_return_up_node()->nt_return_up_node();
									fpf_node::list_remove<scan_data_type>(nt_hold_scan);
									nt_hold_scan = nt_scan_itr_2;
									fpf_node::list_remove<scan_data_type>(nt_hold_scan);
									nt_scan_itr_2 = c_mgf->nt_return_scan_head_ptr();
								}
								else {
									if (fpf_spectralsum_DEBUG_MODE >= 6) {
										std::cout << "   (nt_ion_itr != nt_hold_ion_head_ptr)  !(nt_ion_itr->nt_return_up_node() == nt_ion_itr_2)\n";
									}
									nt_hold_scan = nt_scan_itr;
									nt_scan_itr = nt_scan_itr->nt_return_up_node();
									fpf_node::list_remove<scan_data_type>(nt_hold_scan);
									nt_hold_scan = nt_scan_itr_2;
									fpf_node::list_remove<scan_data_type>(nt_hold_scan);
									nt_scan_itr_2 = c_mgf->nt_return_scan_head_ptr();
								}
							}
							else {
								if (nt_scan_itr->nt_return_up_node() == nt_scan_itr_2) {
									if (fpf_spectralsum_DEBUG_MODE >= 6) {
										std::cout << "   !(nt_ion_itr != nt_hold_ion_head_ptr)  (nt_ion_itr->nt_return_up_node() == nt_ion_itr_2)\n";
									}
									nt_scan_itr = nt_scan_itr->nt_return_up_node()->nt_return_up_node();
									fpf_node::list_remove_head<scan_data_type>(c_mgf->nt_return_scan_head_ptr());
									fpf_node::list_remove_head<scan_data_type>(c_mgf->nt_return_scan_head_ptr());
									nt_hold_scan_head_ptr = nt_scan_itr;
									nt_scan_itr_2 = c_mgf->nt_return_scan_head_ptr();
								}
								else {
									if (fpf_spectralsum_DEBUG_MODE >= 6) {
										std::cout << "   !(nt_ion_itr != nt_hold_ion_head_ptr)  !(nt_ion_itr->nt_return_up_node() == nt_ion_itr_2)\n";
									}
									nt_scan_itr = nt_scan_itr->nt_return_up_node();
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
								std::cout << "\nPartial match for scan " << count_scan_1 << " with scan " << count_scan_2 << "\n\n";
								std::cout << "   ! " << nt_scan_itr->dt_return_data()->nt_return_precursor_rt() << " " << nt_scan_itr->dt_return_data()->nt_return_precursor_mass();
								std::cout << "  " << nt_scan_itr_2->dt_return_data()->nt_return_precursor_rt() << " " << nt_scan_itr_2->dt_return_data()->nt_return_precursor_mass();
								std::cout << "   ! " << fpf_scan::return_mean_scan_rt_vt(nt_scan_itr->dt_return_data(), nt_scan_itr_2->dt_return_data());
								std::cout << "  " << fpf_scan::return_mean_scan_mass_vt(nt_scan_itr->dt_return_data(), nt_scan_itr_2->dt_return_data()) << "\n";
							}
						}
					}
				}
				if (nt_scan_itr->nt_return_up_node() == NULL) {
					if (fpf_spectralsum_DEBUG_MODE == 0) {
						std::cout << "\nscan - " << count_scan_1 << "   summed - " << count_scan_2;
					}
				}
			}
		};
		//
		//

		//void mgf_scan_ion_reset() {
		//    for (size_type i = size_type(); i < count_mgf_scan; ++i) {
		//        nt_scan[i].set_union_n(false);
		//        for (fpf_scan::scan::fion_node_type scan_ptr_itr = nt_scan[i].nt_return_fion_head_ptr(); scan_ptr_itr != NULL; scan_ptr_itr = scan_ptr_itr->nt_return_up_node()) {
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
			for (scan_node_type nt_scan_itr = c_mgf.nt_return_scan_head_ptr(); nt_scan_itr != NULL; nt_scan_itr = nt_scan_itr->nt_return_up_node()) {
				if (count_mgf_scan_cout > 1) {
					std::cout << "\nBEGIN IONS";
				}
				else {
					std::cout << "BEGIN IONS";
				}
				std::cout << "\nTITLE=" << "NULL";
				std::cout << "\nRTINSECONDS=" << nt_scan_itr->dt_return_data()->nt_return_precursor_rt();
				std::cout << "\nPEPMASS=" << nt_scan_itr->dt_return_data()->nt_return_precursor_mass();
				for (fpf_scan::scan::fion_node_type nt_ion_ptr = nt_scan_itr->dt_return_data()->nt_return_fion_head_ptr(); nt_ion_ptr != NULL; nt_ion_ptr = nt_ion_ptr->nt_return_up_node()) {
					std::cout << "\n" << nt_ion_ptr->dt_return_data()->vt_return_fion_mz() << "   " << nt_ion_ptr->dt_return_data()->return_fion_intensity() << "   " << nt_ion_ptr->dt_return_data()->st_return_union_count();
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
			for (scan_node_type nt_scan_ptr_itr = c_mgf->nt_return_scan_head_ptr(); nt_scan_ptr_itr != NULL; nt_scan_ptr_itr = nt_scan_ptr_itr->nt_return_up_node()) {
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
					fout << "   ! nt_scan[i].return_scan_union_count() " << nt_scan_ptr_itr->dt_return_data()->return_scan_union_count();
				}
				for (fpf_scan::scan::fion_node_type nt_ion_ptr_itr = nt_scan_ptr_itr->dt_return_data()->nt_return_fion_head_ptr(); nt_ion_ptr_itr != NULL; nt_ion_ptr_itr = nt_ion_ptr_itr->nt_return_up_node()) {
					fout << "\n" << nt_ion_ptr_itr->dt_return_data()->vt_return_fion_mz();
					fout << "  " << nt_ion_ptr_itr->dt_return_data()->return_fion_intensity();
					if (fpf_spectralsum_DEBUG_MODE >= 1) {
						fout << "  ! dt_scan_inputstream->dt_return_data()->st_return_union_count() " << nt_ion_ptr_itr->dt_return_data()->st_return_union_count();
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
	//
	// * * NAMESPACE FUNCTIONS * *
	//
	//

	inline void display_interface() {
		const size_type display_width = 75;
		const std::string display_version = "v0.7.5.0";
		std::string display_title = "-- IgCompose " + display_version + " --";
		std::string display_fpf = "Flinders Proteomics Facility - 2016";
		//
		//
		//wrap this effectively
		std::string display_intro = "   ";
		std::string display_default = "Default settings:";
		std::string display_menu_precursor_mass = "Precursor mass window - ";
		std::string display_menu_precursor_rt = "Precursor retention time window - ";
		std::string display_menu_fragment_ion_mz = "Fragment fion mass-to-charge ratio window - ";
		std::string display_menu_fragment_ion_sup_intensities = "Fragment fion intensity maxima count - ";
		std::string display_menu_set_conditions = "Menu options:\n\n    0 - Use default settings\n\n    S - Define custom settings\n\n    D - Debug mode";
		std::string display_menu_set_precursor_mass = "Set precursor mass window [ M ]";
		std::string display_menu_set_precursor_rt = "Set precursor retention time window [ R ]";
		std::string display_menu_set_fragment_ion_mz = "Set fragment fion mass-to-charge ratio window [ Z ]";
		std::string display_menu_set_fragment_ion_sup_intensities = "Set fragment fion intensity maxima count [ I ]";
		std::cout << "\n\n\n";
		for (size_type i = 0; i < ((display_width - display_title.length()) / 2); ++i) {
			std::cout << " ";
		}
		std::cout << display_title;
		for (size_type i = 0; i < ((display_width - display_title.length()) / 2); ++i) {
			std::cout << " ";
		}
		std::cout << "\n\n";
		for (size_type i = 0; i < ((display_width - display_fpf.length()) / 2); ++i) {
			std::cout << " ";
		}
		std::cout << display_fpf;
		for (size_type i = 0; i < ((display_width - display_fpf.length()) / 2); ++i) {
			std::cout << " ";
		}
		std::cout << "\n\n\n";
		for (size_type i = 0; i < 4; ++i) {
			std::cout << " ";
		}
		std::cout << display_intro;
		for (size_type i = 0; i < (display_width - display_intro.length() - 4); ++i) {
			std::cout << " ";
		}
		std::cout << "\n\n\n";
		for (size_type i = 0; i < 2; ++i) {
			std::cout << " ";
		}
		std::cout << display_default;
		std::cout << "\n\n";
		for (size_type i = 0; i < 4; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_precursor_mass << (fpf_scan::CONDITION_PION_MASS * 2);
		for (size_type i = 0; i < (display_width - display_menu_precursor_mass.length() - 4); ++i) {
			std::cout << " ";
		}
		std::cout << "\n\n";
		for (size_type i = 0; i < 4; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_precursor_rt << (fpf_scan::CONDITION_PION_RT * 2);
		for (size_type i = 0; i < (display_width - display_menu_precursor_rt.length() - 4); ++i) {
			std::cout << " ";
		}
		std::cout << "\n\n";
		for (size_type i = 0; i < 4; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_fragment_ion_mz << (fpf_fion::vt_CONDITION_FION_MZ * 2);
		for (size_type i = 0; i < (display_width - display_menu_fragment_ion_mz.length() - 4); ++i) {
			std::cout << " ";
		}
		std::cout << "\n\n";
		for (size_type i = 0; i < 4; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_fragment_ion_sup_intensities << fpf_fion::st_CONDITION_FION_SUP << " of " << fpf_fion::st_CONDITION_COUNT_FION_SUP;
		for (size_type i = 0; i < (display_width - display_menu_fragment_ion_sup_intensities.length() - 4); ++i) {
			std::cout << " ";
		}
		std::cout << "\n\n\n";
		for (size_type i = 0; i < 2; ++i) {
			std::cout << " ";
		}
		std::cout << display_menu_set_conditions;
		std::cout << "\n\n\n";
	}

	inline void set_debug(int set_fpf_spectralsum_DEBUG_MODE) {
		fpf_spectralsum_DEBUG_MODE = set_fpf_spectralsum_DEBUG_MODE;
	}

	//void debug_parse(mgf& c_mgf_ptr) {
	//	mgf::size_type st_count_itr = mgf::size_type();
	//	for (mgf::scan_node_type nt_scan_itr_ptr = c_mgf_ptr.nt_return_scan_head_ptr(); nt_scan_itr_ptr != NULL; nt_scan_itr_ptr = nt_scan_itr_ptr->nt_return_up_node()) {
	//		std::cout << "\n" << st_count_itr;
	//		std::cout << "\nnt_scan[i].nt_return_precursor_rt() " << nt_scan_itr_ptr->dt_return_data()->nt_return_precursor_rt;
	//		std::cout << "\nnt_scan[i].nt_return_precursor_mass() " << nt_scan_itr_ptr->dt_return_data()->nt_return_precursor_mz;
	//		for (fpf_scan::scan::fion_node_type nt_ion_ptr_itr = nt_scan_itr_ptr->dt_return_data()->nt_return_fion_head_ptr; nt_ion_ptr_itr != NULL; nt_ion_ptr_itr = nt_ion_ptr_itr->nt_return_up_node()) {
	//			std::cout << "\n" << nt_ion_ptr_itr->dt_return_data()->vt_return_fion_mz() << "  " << nt_ion_ptr_itr->dt_return_data()->return_fion_intensity();
	//		}
	//		++st_count_itr;
	//	}
	//	if (st_count_itr == 0) {
	//		std::cout << "\n\nNo members!";
	//	}
	//};
}

#endif
