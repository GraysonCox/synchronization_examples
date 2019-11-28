//
// Created by Grayson Cox on 11/20/19.
//

#ifndef SYNCHRONIZATION_EXAMPLES_LINKED_LIST_NODE_H
#define SYNCHRONIZATION_EXAMPLES_LINKED_LIST_NODE_H


#include <semaphore.h>

class linked_list_node {
public:
	explicit linked_list_node(int key);

	virtual ~linked_list_node();

	const int key;
	linked_list_node *next;
	sem_t *s;
};


#endif //SYNCHRONIZATION_EXAMPLES_LINKED_LIST_NODE_H
