//
// Created by Grayson Cox on 11/20/19.
//

#ifndef SYNCHRONIZATION_EXAMPLES_LINKED_LIST_H
#define SYNCHRONIZATION_EXAMPLES_LINKED_LIST_H

#include <semaphore.h>
#include "linked_list_node.h"

class linked_list {
public:
	linked_list();
	void insert(int key); // Note: This cannot be done concurrently.
	void remove(int key);
private:
	linked_list_node *head;
};


#endif //SYNCHRONIZATION_EXAMPLES_LINKED_LIST_H
