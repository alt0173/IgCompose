/*
 *	File:   fpf_node_h.h
 *	Author: Lukah Dykes
 */



#ifndef FPF_NODE_H
#define	FPF_NODE_H
#include <cstdlib> // provides - size_t, NULL
#include <iostream> // provides - std::cout

namespace fpf_node {

	class node {
	public:

		// TYPEDEFS              
		typedef fpf_ion::ion* data_type;
		typedef fpf_ion::ion::value_type value_type;
		typedef node* node_type;

		// CONSTRUCTORS

		node(const data_type& vt_init_data = data_type(), node_type nt_init_node = NULL) {
			dt_data = vt_init_data;
			nt_node = nt_init_node;
		};

		// MODIFICATION MEMBER FUNCTIONS

		void set_data_dt(const data_type& vt_new_data) {
			dt_data = vt_new_data;
		};

		void set_node_nt(node_type nt_new_link) {
			nt_node = nt_new_link;
		};

		// PRIVATE MEMBER ACCESS FUNCTIONS       

		data_type return_data_dt() const {
			return dt_data;
		};

		node_type return_node_nt() {
			return nt_node;
		};

		const node_type return_node_nt() const {
			return nt_node;
		};

	private:
		data_type dt_data;
		node_type nt_node;
	};

	// FUNCTIONS

	void list_insert_head(const node::data_type& vt_new_data, node::node_type& nt_head_ptr, node::node_type& nt_tail_ptr) {
		nt_head_ptr = new node(vt_new_data, nt_head_ptr);
		if (nt_tail_ptr == NULL) {
			nt_tail_ptr = nt_head_ptr;
		}
	};

	void list_insert_tail(const node::data_type& vt_new_data, node::node_type& nt_head_ptr, node::node_type& nt_tail_ptr) {
		node::node_type nt_new_ptr;
		nt_new_ptr = new node;
		if (nt_head_ptr == NULL) {
			nt_head_ptr = nt_tail_ptr;
		}
		if (nt_tail_ptr == NULL) {
			nt_tail_ptr = nt_new_ptr;
		}
		nt_new_ptr->set_data_dt(vt_new_data);
		nt_tail_ptr->set_node_nt(nt_new_ptr);
		nt_tail_ptr = nt_tail_ptr->return_node_nt();
	};

	//void list_insert(const node::data_type& vt_new_data, node::node_type& nt_prev_ptr) {
	//    // case of empty list?
	//    node::node_type nt_new_ptr;
	//    nt_new_ptr = new node;
	//    nt_new_ptr->set_data_dt(vt_new_data);
	//    nt_new_ptr->set_node_nt(nt_prev_ptr->return_node_nt());
	//    nt_prev_ptr->set_node_nt(nt_new_ptr);
	//};

	//void list_copy(node::node_type nt_call_ptr, node::node_type& nt_new_head_ptr, node::node_type& nt_new_tail_ptr) {
	//	if (nt_call_ptr == NULL) {
	//		return;
	//	}
	//	nt_new_head_ptr = NULL;
	//	nt_new_tail_ptr = NULL;
	//	list_insert_head(nt_call_ptr->return_data_dt(), nt_new_head_ptr, nt_new_tail_ptr);
	//	nt_call_ptr = nt_call_ptr->return_node_nt();
	//	while (nt_call_ptr != NULL) {
	//		list_insert_tail(nt_call_ptr->return_data_dt(), nt_new_head_ptr, nt_new_tail_ptr);
	//		nt_new_tail_ptr = nt_new_tail_ptr->return_node_nt();
	//		nt_call_ptr = nt_call_ptr->return_node_nt();
	//	}
	//};

	void list_remove_head(node::node_type& nt_head_ptr) {
		node::node_type nt_del_ptr;
		nt_del_ptr = nt_head_ptr;
		nt_head_ptr = nt_head_ptr->return_node_nt();
		delete nt_del_ptr;
	}

	void list_remove(node::node_type& nt_prev_ptr) {
		node::node_type nt_del_ptr;
		nt_del_ptr = nt_prev_ptr->return_node_nt();
		nt_prev_ptr->set_node_nt(nt_del_ptr->return_node_nt());
		delete nt_del_ptr;
	}

	//void sort_sup(node::node_type nt_call_ptr, node::value_type vt_sort, node::node_type& nt_new_head_ptr, node::node_type& nt_new_tail_ptr) {
	//	
	//	// read through linked list
	//	// swap sup element with head_pointer
	//	// read from head_pointer->node()
	//	// swap (next) sup element with head_pointer->node();
	//	// etc
	//	
	//	

}

#endif
