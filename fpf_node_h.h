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
        typedef node* node_type;

        // CONSTRUCTORS

        node(const data_type& vt_init_data = data_type(), node_type nt_init_node = NULL) {
            vt_data = vt_init_data;
            nt_node = nt_init_node;
        };

        // MODIFICATION MEMBER FUNCTIONS

        void set_data(const data_type& vt_new_data) {
            vt_data = vt_new_data;
        };

        void set_node(node_type nt_new_link) {
            nt_node = nt_new_link;
        };

        // PRIVATE MEMBER ACCESS FUNCTIONS       

        data_type return_data() const {
            return vt_data;
        };

        node_type return_node() {
            return nt_node;
        };

        const node_type return_node() const {
            return nt_node;
        };

    private:
        data_type vt_data;
        node_type nt_node;
    };
    
    // FUNCTIONS

    void insert_head(const node::data_type& vt_new_data, node::node_type& nt_head_ptr, node::node_type& nt_tail_ptr) {
        nt_head_ptr = new node(vt_new_data, nt_head_ptr);
        if (nt_tail_ptr == NULL) {
            nt_tail_ptr = nt_head_ptr;
        }
    };

    void insert_tail(const node::data_type& vt_new_data, node::node_type& nt_head_ptr, node::node_type& nt_tail_ptr) {
        node::node_type nt_new_ptr;
        nt_new_ptr = new node;
        if (nt_head_ptr == NULL) {
            nt_head_ptr = nt_tail_ptr;
        }
        if (nt_tail_ptr == NULL) {
            nt_tail_ptr = nt_new_ptr;
        }
        nt_new_ptr->set_data(vt_new_data);
        nt_tail_ptr->set_node(nt_new_ptr);
        nt_tail_ptr = nt_tail_ptr->return_node();
    };

    void insert(const node::data_type& vt_new_data, node::node_type& nt_prev_ptr) {
        // case of empty list?
        node::node_type nt_new_ptr;
        nt_new_ptr = new node;
        nt_new_ptr->set_data(vt_new_data);
        nt_new_ptr->set_node(nt_prev_ptr->return_node());
        nt_prev_ptr->set_node(nt_new_ptr);
    };

    void copy(node::node_type nt_call_ptr, node::node_type& nt_new_head_ptr, node::node_type& nt_new_tail_ptr) {
        nt_new_head_ptr = NULL;
        nt_new_tail_ptr = NULL;
        if (nt_call_ptr == NULL) {
            return;
        }
        insert_head(nt_call_ptr->return_data(), nt_new_head_ptr, nt_new_tail_ptr);
        nt_call_ptr = nt_call_ptr->return_node();
        while (nt_call_ptr != NULL) {
            insert_tail(nt_call_ptr->return_data(), nt_new_head_ptr, nt_new_tail_ptr);
            nt_new_tail_ptr = nt_new_tail_ptr->return_node();
            nt_call_ptr = nt_call_ptr->return_node();
        }
    };
}

#endif
