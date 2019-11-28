//
// Created by Grayson Cox on 11/20/19.
//

#include <string>
#include "linked_list_node.h"

linked_list_node::linked_list_node(int key) : key(key) {
	next = nullptr;
	s = sem_open(std::to_string(key).c_str(), O_CREAT, 0644, 1);
}

linked_list_node::~linked_list_node() {
	sem_close(s);
	sem_unlink(std::to_string(key).c_str());
}
