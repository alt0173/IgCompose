/*
 *	File:   fpf_node.h
 *	Author: Lukah Dykes
 */



#ifndef FPF_NODE
#define	FPF_NODE
#include <cstdlib> // provides - size_t, NULL
#include <iostream> // provides - std::cout

namespace fpf_node {

	template <class element>
	class node {

	public:

		typedef element data_type;
		typedef node<element>* node_type;


		//
		// * * CONSTRUCTORS * * 
		//


		node(const data_type& d_init_data = data_type(), node_type nt_init_up_node = NULL, node_type nt_init_down_node = NULL) {
			d_data = d_init_data;
			nt_up_node = nt_init_up_node;
			nt_down_node = nt_init_down_node;
		};
		//
		//


		//
		// * * MODIFICATION MEMBER FUNCTIONS * * 
		//


		void set_data_dt(const data_type& d_new_data) {
			d_data = d_new_data;
		};
		//
		//

		void set_up_node_nt(node_type nt_new_link) {
			nt_up_node = nt_new_link;
		};
		//
		//

		void set_down_node_nt(node_type nt_new_link) {
			nt_down_node = nt_new_link;
		};
		//
		//


		//
		// * * PRIVATE MEMBER ACCESS FUNCTIONS * * 
		//


		data_type dt_return_data() const {
			return d_data;
		};
		//
		//

		node_type return_up_node_nt() {
			return nt_up_node;
		};
		//
		//

		node_type return_down_node_nt() {
			return nt_down_node;
		};
		//
		//

		const node_type return_up_node_nt() const {
			return nt_up_node;
		};
		//
		//

		const node_type return_down_node_nt() const {
			return nt_down_node;
		};
		//
		//

	private:
		data_type d_data;
		node_type nt_up_node;
		node_type nt_down_node;
	};
	//
	//


	//
	// * * FUNCTIONS * * 
	//


	template <class element>
	void list_insert_head(const typename node<element>::data_type dt_new_data, typename node<element>::node_type& nt_node_head_ptr, typename node<element>::node_type& nt_node_tail_ptr) {
		node<element>::node_type nt_new_ptr = new node;
		nt_new_ptr->set_data_dt(dt_new_data);
		if (nt_node_head_ptr == NULL) {
			nt_node_head_ptr = nt_new_ptr;
		}
		if (nt_node_tail_ptr == NULL) {
			nt_node_tail_ptr = nt_new_ptr;
		}
		nt_new_ptr->set_up_node_nt(nt_node_head_ptr);
		nt_node_head_ptr->set_down_node_nt(nt_new_ptr);
		nt_node_head_ptr = nt_node_head_ptr->return_down_node_nt();
	};
	//
	//

	template <class element>
	void list_insert_tail(const typename node<element>::data_type& dt_new_data, typename node<element>::node_type& nt_node_head_ptr, typename node<element>::node_type& nt_node_tail_ptr) {
		node<element>::node_type nt_new_ptr = new node<element>;
		nt_new_ptr->set_data_dt(dt_new_data);
		if (nt_node_head_ptr == NULL) {
			nt_node_head_ptr = nt_new_ptr;
		}
		if (nt_node_tail_ptr == NULL) {
			nt_node_tail_ptr = nt_new_ptr;
		}
		else {
			nt_new_ptr->set_down_node_nt(nt_node_tail_ptr);
			nt_node_tail_ptr->set_up_node_nt(nt_new_ptr);
			nt_node_tail_ptr = nt_new_ptr;
		}
	};
	//
	//

	template <class element>
	void list_insert_up(const typename node<element>::data_type& dt_new_data, typename node<element>::node_type& nt_current_ptr, typename node<element>::node_type& nt_node_head_ptr, typename node<element>::node_type& nt_node_tail_ptr) {
		if (nt_current_ptr != nt_node_tail_ptr) {
			node<element>::node_type nt_new_ptr = new node<element>;
			nt_new_ptr->set_data_dt(dt_new_data);
			nt_current_ptr->return_up_node_nt()->set_down_node_nt(nt_new_ptr);
			nt_new_ptr->set_up_node_nt(nt_current_ptr->return_up_node_nt());
			nt_new_ptr->set_down_node_nt(nt_current_ptr);
			nt_current_ptr->set_up_node_nt(nt_new_ptr);
		}
		else {
			list_insert_tail<element>(dt_new_data, nt_node_head_ptr, nt_node_tail_ptr);
		}
	};
	//
	//

	//template <class element>
	//void list_copy(typename node<element>::node_type nt_call_ptr,  typename node<element>::node_type& nt_new_head_ptr,  typename node<element>::node_type& nt_new_tail_ptr) {
	//	if (nt_call_ptr == NULL) {
	//		return;
	//	}
	//	nt_new_head_ptr = NULL;
	//	nt_new_tail_ptr = NULL;
	//	list_insert_head(nt_call_ptr->dt_return_data(), nt_new_head_ptr, nt_new_tail_ptr);
	//	nt_call_ptr = nt_call_ptr->return_up_node_nt();
	//	while (nt_call_ptr != NULL) {
	//		list_insert_tail(nt_call_ptr->dt_return_data(), nt_new_head_ptr, nt_new_tail_ptr);
	//		nt_new_tail_ptr = nt_new_tail_ptr->return_up_node_nt();
	//		nt_call_ptr = nt_call_ptr->return_up_node_nt();
	//	}
	//};

	template <class element>
	void list_remove_head(typename node<element>::node_type& nt_ion_head_ptr) {
		node<element>::node_type nt_del_ptr;
		nt_del_ptr = nt_ion_head_ptr;
		nt_ion_head_ptr = nt_ion_head_ptr->return_up_node_nt();
		nt_ion_head_ptr->set_down_node_nt(NULL);
		delete nt_del_ptr;
	}
	//
	//

	template <class element>
	void list_remove(typename node<element>::node_type& nt_ptr) {
		node<element>::node_type nt_del_ptr;
		nt_del_ptr = nt_ptr;
		nt_ptr->return_down_node_nt()->set_up_node_nt(nt_del_ptr->return_up_node_nt());
		nt_ptr->return_up_node_nt()->set_down_node_nt(nt_del_ptr->return_down_node_nt());
		delete nt_del_ptr;
	}
	//
	//
}

#endif
