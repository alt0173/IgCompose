// * * fpf_node.h * * 
// 
// Lukah Dykes - Flinders Proteomics Facility - 2016
// 
// * * * * *

 // --- namespace fpf_node class node
 // 
 // namespace fpf_node contains object definitions for the node class. node provides functionality
 // for a doubly linked list, which is templated for a standard C++ data type or an object with a
 // copy constructor and assignment operator.

#ifndef FPF_NODE
#define	FPF_NODE
#include <cstdlib> // provides - size_t, NULL

namespace fpf_node {
	template <class element>
	class node {
	public:

		typedef element data_type;
		// Defines data_type as a template type. It may be a standard C++ data type or an object
		// with a copy constructor and assignment operator.

		typedef node<element>* node_type;
		// Defines node_type as a pointer to a node class of template type.

		node(data_type d_init_data = data_type(), node_type nt_init_up_node = node_type(), node_type nt_init_down_node = node_type()) {
			// node() defines a constructor call for a node class that assigns
			// declared parameters as initial values or calls default values as
			// ISO type defaults (0 for standard C++ data types, NULL for
			// pointer types).
			d_data = d_init_data;
			nt_up_node = nt_init_up_node;
			nt_down_node = nt_init_down_node;
		};

		//
		//
		//
		//   * * MEMBER MODIFICATION FUNCTIONS * *
		//
		//
		//

		void set_data_dt(const data_type& d_new_data) {
			// set_data_dt() assigns a data_type to d_data.
			d_data = d_new_data;
		};

		void set_up_node_nt(node_type nt_new_link) {
			// set_up_node_nt() assigns a node_type to nt_up_node.
			nt_up_node = nt_new_link;
		};

		void set_down_node_nt(node_type nt_new_link) {
			// set_down_node_nt() assigns a node_type to nt_down_node.
			nt_down_node = nt_new_link;
		};

		//
		//
		//
		// * * MEMBER ACCESS FUNCTIONS * *
		//
		//
		//

		data_type dt_return_data() {
			// dt_return_data() returns d_data.
			return d_data;
		};

		node_type nt_return_up_node() {
			// nt_return_up_node() returns nt_up_node.
			return nt_up_node;
		};

		node_type nt_return_down_node() {
			// nt_return_down_node() returns nt_down_node.
			return nt_down_node;
		};

		const node_type nt_return_up_node() const {
			// nt_return_up_node() returns a constant nt_up_node.
			return nt_up_node;
		};

		const node_type nt_return_down_node() const {
			// nt_return_down_node() returns a constant nt_down_node.
			return nt_down_node;
		};

	private:
		data_type d_data;
		// d_data is a data_type. It can be a standard C++ data type or an
		// object with a copy constructor and assignment operator

		node_type nt_up_node;
		// nt_up_node is a node_type. Through functional assignment nt_up_node
		// points to the subsequent node_type in the doubly linked list. Should
		// nt_up_node be the last node_type in the list, it points to NULL.

		node_type nt_down_node;
		// nt_down_node is a node_type. Through functional assignment
		// nt_down_node points to the antecedent node_type in the doubly linked
		// list. Should nt_down_node be the first node_type in the list, it
		// points to NULL.
	};

	//
	//
	//
	//   * * NAMESPACE FUNCTIONS * *
	//
	//
	//

	template <class element>
	void list_insert_head(const typename node<element>::data_type dt_new_data, typename node<element>::node_type& nt_node_head_ptr, typename node<element>::node_type& nt_node_tail_ptr) {
		// list_insert_head() initialises a node_type, assigns data_type through
		// a called parameter, and assigns this node as the first node in a
		// referenced doubly linked list. If the called list is empty the created
		// node is declared as both the first and last node.
		node<element>::node_type nt_new_ptr = new node;
		nt_new_ptr->set_data_dt(dt_new_data);
		if (nt_node_head_ptr == NULL) {
			nt_node_head_ptr = nt_new_ptr;
		}
		else {
			nt_new_ptr->set_up_node_nt(nt_node_head_ptr);
			nt_node_head_ptr->set_down_node_nt(nt_new_ptr);
			nt_node_head_ptr = nt_node_head_ptr->nt_return_down_node();
		}
		if (nt_node_tail_ptr == NULL) {
			nt_node_tail_ptr = nt_new_ptr;
		}
	};

	template <class element>
	void list_insert_tail(const typename node<element>::data_type& dt_new_data, typename node<element>::node_type& nt_node_head_ptr, typename node<element>::node_type& nt_node_tail_ptr) {
		// list_insert_tail() initialises a node_type, assigns data_type through
		// a referenced parameter, and assigns this node_type as the last
		// node_type in a referenced doubly linked list. If the list is empty
		// the created node is declared as both the first and last node_type.
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

	template <class element>
	void list_insert_up(const typename node<element>::data_type& dt_new_data, typename node<element>::node_type& nt_current_ptr, typename node<element>::node_type& nt_head_ptr, typename node<element>::node_type& nt_tail_ptr) {
		// list_insert_up() initialises a node_type, assigns data_type through a
		// referenced parameter, and assigns this node_type as the subsequent
		// node_type to a referenced node_type in a doubly linked list. If the
		// referenced node_type is the last in the list, list_insert_tail is
		// called in place.
		if (nt_current_ptr != nt_tail_ptr) {
			node<element>::node_type nt_new_ptr = new node<element>;
			nt_new_ptr->set_data_dt(dt_new_data);
			nt_current_ptr->nt_return_up_node()->set_down_node_nt(nt_new_ptr);
			nt_new_ptr->set_up_node_nt(nt_current_ptr->nt_return_up_node());
			nt_new_ptr->set_down_node_nt(nt_current_ptr);
			nt_current_ptr->set_up_node_nt(nt_new_ptr);
		}
		else {
			list_insert_tail<element>(dt_new_data, nt_head_ptr, nt_tail_ptr);
		}
	};

	template <class element>
	void list_remove_head(typename node<element>::node_type& nt_head_ptr) {
		// list_remove_head() deletes the first node_type in a doubly linked
		// list and assigns the subsequent node_type as the new first node_type
		// in the list. If there is no subsequent node_type the first node_type
		// is set as NULL.
		if (nt_head_ptr != NULL) {
			node<element>::node_type nt_del_ptr;
			nt_del_ptr = nt_head_ptr;
			nt_head_ptr = nt_head_ptr->nt_return_up_node();
			nt_head_ptr->set_down_node_nt(NULL);
			delete nt_del_ptr;
		}
	}

	template <class element>
	void list_remove_tail(typename node<element>::node_type& nt_tail_ptr) {
		// list_remove_tail() deletes the last node_type in a doubly linked
		// list and assigns the antecedent node_type as the new last node_type
		// in the list. If there is no subsequent node_type the last node_type
		// is set as NULL.
		if (nt_tail_ptr != NULL) {
			node<element>::node_type nt_del_ptr;
			nt_del_ptr = nt_tail_ptr;
			nt_tail_ptr = nt_tail_ptr->nt_return_down_node();
			nt_tail_ptr->set_up_node_nt(NULL);
			delete nt_del_ptr;
		}
	}

	template <class element>
	void list_remove(typename node<element>::node_type& nt_ptr) {
		// list_remove() deletes a node_type in a doubly linked list.
		if ((nt_ptr->nt_return_down_node() == NULL) || (nt_ptr->nt_return_up_node() == NULL)) {
			if (nt_ptr->nt_return_down_node() == NULL) {
				list_remove_head<element>(nt_ptr);
			}
			if (nt_ptr->nt_return_up_node() == NULL) {
				list_remove_tail<element>(nt_ptr);
			}
		}
		else {
			node<element>::node_type nt_del_ptr;
			nt_del_ptr = nt_ptr;
			nt_ptr->nt_return_down_node()->set_up_node_nt(nt_del_ptr->nt_return_up_node());
			nt_ptr->nt_return_up_node()->set_down_node_nt(nt_del_ptr->nt_return_down_node());
			delete nt_del_ptr;
		}
	}

	template <class element>
	void list_remove_all(typename node<element>::node_type& nt_head_ptr) {
		// list_remove_all() deletes all node_types in a doubly linked list.
		for (typename node<element>::node_type nt_ptr_itr = nt_head_ptr; nt_ptr_itr->nt_return_up_node() != NULL; nt_ptr_itr) {
			typename node<element>::node_type nt_hold_ptr = nt_ptr_itr;
			nt_ptr_itr = nt_ptr_itr->nt_return_up_node();
			delete nt_hold_ptr;
		}
	}
}

#endif

//template <class element>
//void list_copy(typename node<element>::node_type nt_call_ptr,  typename node<element>::node_type& nt_new_head_ptr,  typename node<element>::node_type& nt_new_tail_ptr) {
//	if (nt_call_ptr == NULL) {
//		return;
//	}
//	nt_new_head_ptr = NULL;
//	nt_new_tail_ptr = NULL;
//	list_insert_head(nt_call_ptr->dt_return_data(), nt_new_head_ptr, nt_new_tail_ptr);
//	nt_call_ptr = nt_call_ptr->nt_return_up_node();
//	while (nt_call_ptr != NULL) {
//		list_insert_tail(nt_call_ptr->dt_return_data(), nt_new_head_ptr, nt_new_tail_ptr);
//		nt_new_tail_ptr = nt_new_tail_ptr->nt_return_up_node();
//		nt_call_ptr = nt_call_ptr->nt_return_up_node();
//	}
//};
