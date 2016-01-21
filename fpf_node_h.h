/*
 * File:   fpf_node_h.h
 * Author: Lukah Dykes
 */



#ifndef FPF_NODE_H
#define	FPF_NODE_H
#include <cstdlib> // provides - size_t, NULL
#include <iostream> // provides - std::cout
#include "fpf_ion_h.h"

namespace fpf_node {
    
    class node {      
    public:
        
        // TYPEDEFS              
        typedef fpf_ion::ion* value_type;
        typedef node* node_type;

        // CONSTRUCTORS
        node(const value_type& vt_init_data = value_type(), node_type nt_init_node = NULL) {
            vt_data = vt_init_data;
            nt_node = nt_init_node;
        };

        // MODIFICATION MEMBER FUNCTIONS
        void set_data(const value_type& vt_new_data) {
            vt_data = vt_new_data;
        };
        
        void set_node(node_type nt_new_link) {
            nt_node = nt_new_link;
        };

        void insert_head(const node::value_type& vt_new_data, node::node_type& nt_head_ptr, node::node_type& nt_tail_ptr) {
            nt_head_ptr = new node(vt_new_data, nt_head_ptr);
            if (nt_tail_ptr == NULL) {
                nt_tail_ptr = nt_head_ptr;
            }
        };
        
        void insert_tail(const node::value_type& vt_new_data, node::node_type& nt_head_ptr, node::node_type& nt_tail_ptr) {
            node::node_type nt_new_ptr;           
            nt_new_ptr = new node;
            if (nt_head_ptr == NULL) {
                nt_head_ptr = nt_new_ptr;
            }
            if (nt_tail_ptr == NULL) {
                nt_tail_ptr = nt_new_ptr;
            }
            nt_new_ptr->set_data(vt_new_data);
            nt_tail_ptr->set_node(nt_new_ptr);
            nt_tail_ptr = nt_tail_ptr->return_node();
        };

        void insert(const node::value_type& vt_new_data, node::node_type& nt_prev_ptr) {
            node::node_type nt_new_ptr;
            nt_new_ptr = new node;
            nt_new_ptr->set_data(vt_new_data);
            nt_new_ptr->set_node(nt_prev_ptr->return_node());
            nt_prev_ptr->set_node(nt_new_ptr);
        };

        // PRIVATE MEMBER ACCESS FUNCTIONS       
        value_type return_data() const {
            return vt_data;
        };

        node_type return_node() {
            return nt_node;
        };

        const node_type return_node() const {
            return nt_node;
        };
        
        void cout_all_data(node::node_type& nt_head_ptr) const {
            for (node::node_type link = nt_head_ptr; link != NULL; link = link->return_node()) {
                std::cout << "\n" << link->return_data()->return_fragment_ion_mz() << "  " << link->return_data()->return_fragment_ion_int();
            }
        };

    private:
        value_type vt_data;
        node_type nt_node;
    };
}

#endif
