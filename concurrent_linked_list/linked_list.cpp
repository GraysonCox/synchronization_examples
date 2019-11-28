//
// Created by Grayson Cox on 11/20/19.
//

#include "linked_list.h"

linked_list::linked_list() {
	head = new linked_list_node(-1);
}

void linked_list::insert(int key) { // TODO: Make this concurrent-safe.
	linked_list_node *n = head;
	while (n != nullptr) {
		if (key < n->next->key) {
			linked_list_node *new_node = new linked_list_node(key);
			new_node->next = n->next;
			n->next = new_node;
			break;
		} else {
			n = n->next;
		}
	}
}

void linked_list::remove(int key) {
	linked_list_node *pred, *curr;
	pred = head;
	sem_wait(pred->s);
	curr = pred->next;
	sem_wait(curr->s);
	while (curr->key <= key) {
		if (key == curr->key) {
			pred->next = curr->next;
			break;
		} else {
			sem_post(pred->s);
			pred = curr;
			curr = curr->next;
			sem_wait(curr->s);
		}
	}
	sem_post(pred->s);
	sem_post(curr->s);
}
