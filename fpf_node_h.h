/*
 * File:   fpf_node_h.h
 * Author: Lukah Dykes
 */



#ifndef FPF_NODE_H
#define	FPF_NODE_H
#include <cstdlib> // provides - size_t, NULL

namespace fpf_node {

    class node {
    public:
        // TYPEDEFS
        typedef double value_type;
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

        void insert_head(const node::value_type& vt_new_data, node::node_type& nt_head_ptr) {
            nt_head_ptr = new node(vt_new_data, nt_head_ptr);
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

    private:
        value_type vt_data;
        node_type nt_node;
    };
}

#endif
