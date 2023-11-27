/********************************************
	Class: Data Structure and Algorithms, KECE208_02
		   2nd semester, 2022

	1st Project: List

	linked_list.c

	Name: Ahn Jin mo
	StudentID: 2017160111

**********************************************/

#include "linked_list.h"
#include "string.h"
int list_exist;

/*
	@Function name: create_list
	@Parameters: number_of_nodes, list_type
	@Returns: new_list
	@Descriptions: This function creates list.
	@Error cases: number_of_nodes <1. / list_exist == 1. / list_type != 0 && 1.
 */

struct linked_list* create_list (int number_of_nodes, int list_type)
{
	int a[number_of_nodes];
	int i, j;
	int bFound;

	if (number_of_nodes < 1)
	{
		printf("Function create_list: the number of nodes is not specified correctly\n");
		return NULL;
	}
	if(list_exist == 1)
	{
		printf("Function create_list: a list already exists\nRestart a Program\n");
		exit(0);
	}
	if(list_type != 0 && list_type != 1)
	{
		printf("Function create_list: the list type is wrong\n");
		exit(0);
	}
	struct linked_list * new_list = (struct linked_list*)malloc(sizeof(struct linked_list));
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->number_of_nodes = 0;
	new_list->type_of_list = list_type;

	//now put nodes into the list with random numbers.
	srand((unsigned int)time(NULL));
	if(list_type == 0)
	{
		for ( i = 0; i < number_of_nodes; ++i )
		{
			while ( 1 )
			{

				a[i] = rand() % number_of_nodes + 1;
				bFound = 0;
				for ( j = 0; j < i; ++j )
				{
					if ( a[j] == a[i] )
					{
						bFound = 1;
						break;
					}
				}
				if ( !bFound )
					break;
			}
			struct linked_node* new_node = create_node(a[i]);
			insert_node(new_list, new_node);
		}
	}
	else if(list_type == 1)
	{
		for ( i = 0; i < number_of_nodes; ++i )
		{
			while ( 1 )
			{

				a[i] = rand() % number_of_nodes + 1;
				bFound = 0;
				for ( j = 0; j < i; ++j )
				{
					if ( a[j] == a[i] )
					{
						bFound = 1;
						break;
					}
				}
				if ( !bFound )
					break;
			}
			struct linked_node* new_node = create_node(a[i]);
			push_Stack(new_list, new_node);
		}
	}
	list_exist = 1;
	printf("List is created!\n");
	return new_list;
}

/*
	@Function name: remove_list
	@Parameters: list
	@Returns: none
	@Descriptions: This function removes a total list.
	@Error cases: none
 */

void remove_list(struct linked_list* list)
{
	struct linked_node* current = list->head; // The operation starts in the head of a list.
	struct linked_node* new_pointer;
	int deleted_node_value;
	int number_of_deletion = 0;

	while (current != NULL)
	{
		new_pointer = current->next; 
		current->prev = NULL;
		current->next = NULL;
		deleted_node_value = current->value;
		free(current);
		
		printf("The node with value %d is deleted!\n", deleted_node_value);

		list->head = new_pointer; // After delete current, make new_pointer as head node.
		current = new_pointer; 
		number_of_deletion++; 
	}

	free(new_pointer); // After delete all nodes, new_pointer will be free.
	list->head = NULL;
	list->tail = NULL;
	free(list); // After delete head and tail, the list will be free.
	printf("The list is completely deleted : %d nodes are deleted.\n", number_of_deletion);
	list_exist = 0;
}

/*
	@Function name: create_node
	@Parameters: node_value
	@Returns: node
	@Descriptions: This function create new node but this node is not in a list.
	@Error cases: none
 */

struct linked_node* create_node (int node_value)
{
	struct linked_node* node = (struct linked_node*)malloc(sizeof(struct linked_node));
	node->value = node_value;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

/*
	@Function name: insert_node
	@Parameters: list, node
	@Returns: none
	@Descriptions: This function insert a node in head of the list.
	@Error cases: If there is no list, operating insert_node makes core dump because of duplication with create_list function.
 */

void insert_node(struct linked_list* list, struct linked_node* node)
{
	node->next = NULL;
	node->prev = NULL;

    if(list->head == NULL)		//if head is NULL, tail is also NULL.
	{
		list->head = node;
		list->tail = node;
		list_exist = 1;
	}
	else if(list->head == list->tail)
	{
		node->next = list->head;
		list->head->prev = node;
		list->head = node;
	}
	else if(list->head != list->tail)
	{
		node->next = list->head;
		list->head->prev = node;
		list->head = node;
	}
	(list->number_of_nodes)++;
	list->type_of_list = 0;
}


/*
	@Function name: remove_node
	@Parameters: list, rm_node_value
	@Returns: none
	@Descriptions: This function removes a node which has rm_node_value. 
	@Error cases: list type is stack. / rm_node_value is not in a list.
 */


void remove_node(struct linked_list* list, int rm_node_value)
{
	struct linked_node* target; // The function uses *target to find a node whose value is rm_node_value.
	target = list->head; 

	if(list->type_of_list == 1) // If the list is stack, print error message.
	{
		printf("Function remove_node: The list type is not normal. Removal is not allowed.\n");
		return;
	}

	int i = 0;
	if(list->head->value == rm_node_value) // rm_node_value is head's value.
	{
		if(list->head == list->tail) // If there is only one node in a list, the list will be free.
		{
			target->prev = NULL;
			target->next = NULL;
			free(target);
			
			list->head = NULL;
			list->tail = NULL;
			free(list);
			list_exist = 0;
			i = 1;
		}
		else // If there is more than one node in a list, the head of list will be removed.
		{
			list->head = target->next;
			list->head->prev = NULL;

			target->prev = NULL;
			target->next = NULL;
			free(target);
			(list->number_of_nodes)--;
			i = 1;
		}
	}
	else if(list->head->value != rm_node_value) // rm_node_value is not head's value.
	{
		while(target != list->tail) // rm_node_value is not tail's value.
		{
			if(target->value == rm_node_value) // The function found a node whose value is rm_node_value between head and tail.
			{
				target->next->prev = target->prev;
				target->prev->next = target->next;
				target->next = NULL;
				target->prev = NULL;
				free(target);
				(list->number_of_nodes)--;
				i = 1;
				break;
			}
			else if(target->value != rm_node_value)
			{
			target = target->next; // If target is not equal to rm_node_value, target moves to the next node.
			}
		}
		if(target == list->tail && target->value == rm_node_value) // rm_node_value is tail's value.
		{
			list->tail = list->tail->prev;
			list->tail->next = NULL;
			target->prev = NULL;
			target->next = NULL;
			free(target);
			(list->number_of_nodes)--;
			i=1;
		}
	}

	if(i == 0) // There is no rm_node_value in a list.
	{
		printf("Function remove_node: There is no such node to remove.\n");
		return;
	}
}

/*
	@Function name: delete_range
	@Parameters: list, id_1, id_2
	@Returns: none
	@Descriptions: This function deletes a range of nodes form id_1 to id_2.
	@Error cases: id_1 or id_2 is not a node value in the list. / order of id_1 >= order of id_2.
 */
void delete_range(struct linked_list* list, int id_1, int id_2)
{
	struct linked_node* node_1 = list->head;
	struct linked_node* node_2 = list->head;
	struct linked_node* next_1;
	struct linked_node* next_2;
	int order1 = 1, order2 = 1;
	int i;

	while(node_1 != NULL) // Finding node whose value is id_1.
	{
		if(node_1->value == id_1) 
		{
			break;
		}
		else if(node_1->value != id_1)
		{
		    node_1 = node_1->next; 
		    order1++;
		}
	}

	while(node_2 != NULL)  // Finding node whose value is id_2.
	{
		if(node_2->value == id_2) 
		{
			break;
		}
		else if(node_2->value != id_2)
		{
		    node_2 = node_2->next; 
		    order2++;
		}
	}

	if(order1 == 1 && order2 != 1 && order2 != list->number_of_nodes && node_2 != NULL && order1 != order2) // id_1 is head value, id_2 is not tail value.
	{
		next_2 = node_2->next;

		for(i = 0; i < (order2-order1); i++)
		{
			next_1 = node_1->next;
			node_1->next->prev = NULL;
			list->head = node_1->next;  // Whenever for statement is run, head is changed to the next node of original head.
			node_1->next = NULL;
			free(node_1);
			list->number_of_nodes--;
			node_1 = next_1;
		}
		node_2->next->prev = NULL;
		list->head = next_2;
		node_2->next = NULL;
		node_2->prev = NULL;
		free(node_2);
		list->number_of_nodes--;

	}

	if(order1 != 1 && node_1 != NULL && order2 == list->number_of_nodes && order1 != order2) // id_1 is not head value, id_2 is tail value.
	{
		for(i = 0; i <= (order2-order1); i++)
		{
			next_1 = node_1->next;
			remove_node(list, node_1->value);  // This if statement is run by using remove_node function.
			if(next_1 != NULL)
			{
				node_1 = next_1;
			}
			if(next_1 == NULL)
			{
				return;
			}
		}
	}

	if(order1 == 1 && order2 == list->number_of_nodes && order1 != order2) // id_1 is head value, id_2 is tail value.
	{
		for(i = 0; i < (order2-order1); i++)
		{
			next_1 = node_1->next;
			node_1->next->prev = NULL;
			list->head = node_1->next;
			node_1->next = NULL;
			free(node_1);
			list->number_of_nodes--;
			node_1 = next_1;
		}
		node_2->next = NULL;
		node_2->prev = NULL;
		free(node_2);

		list->head = NULL;
		list->tail = NULL;
		free(list); // In this if statement, list will be freed.
		list_exist = 0;
	}

	if(order1 != 1 && node_1 != NULL && order2 != list->number_of_nodes && node_2 != NULL && order1 < order2) // id_1 is not head value, id_2 is not tail value.
	{
		for(i = 0; i < (order2-order1); i++)
	    {
		    next_1 = node_1->next;
		    node_1->next->prev = node_1->prev;
		    node_1->prev->next = node_1->next;
		    node_1->next = NULL;
		    node_1->prev = NULL;
		    free(node_1);
		    list->number_of_nodes--;
		    node_1 = next_1;
	    }

	    node_2->prev->next = node_2->next;
	    node_2->next->prev = node_2->prev;
	    node_2->next = NULL;
	    node_2->prev = NULL;
	    free(node_2);
	    list->number_of_nodes--;
	}

	if(node_1 == NULL || node_2 == NULL) 
	{
		printf("Function delete_range: the node dose not exist.\n");
	}

	if(order1 >= order2 && order1 <= list->number_of_nodes && order2 <= list->number_of_nodes)
	{
		printf("Function delelte_range: the selected range of nodes is not in order.");
	}
}
/*
	@Function name: push_Stack
	@Parameters: list, node
	@Returns: none
	@Descriptions: This function insert a node in stack manner. Whenever function is run, tail of the list change.
	@Error cases: If there is no stack, operating push_Stack makes core dump because of duplication with create_list function.
	              list->type_of_list is 0.
 */
void push_Stack(struct linked_list* list, struct linked_node* node)
{
	node->prev = NULL;
	node->next = NULL;

	if(list->type_of_list == 0)
	{
		printf("Function push_Stack: The list type is not a stack.\n"); // If the type of list isn't stack, error message will be printed.
		return;
	}

	if(list->head == NULL) // There is no list.
	{
		list->head = node;
		list->tail = node;
		list_exist = 1;
		list->type_of_list = 1;
	}

	else if(list->head != NULL)
	{
		node->prev = list->tail; 
		list->tail->next = node;
		list->tail = node; // Tail of the list is changed.
	}
	(list->number_of_nodes)++;
}

/*
	@Function name: pop_Stack
	@Parameters: list, number
	@Returns: none
	@Descriptions: This function operates pop_Stack. Tail of the list will be removed and and changed.
	@Error cases: list->type_of_list is 0. / number is smaller than 1. / number is bigger than number of nodes.
 */
void pop_Stack(struct linked_list* list, int number)
{
	struct linked_node* pop_node = list->tail;

	if(list->type_of_list == 0) // If type of list is normal, print error message.
	{
		printf("Function pop_Stack: The list type is not a stack.\n");
		return;
	}

	if(number < 1)
	{
		printf("Function pop_Stack: The number of nodes which will be removed is more than 1.\n");
		return;
	}

	if(number > list->number_of_nodes)
	{
		printf("Function pop_Stack: The number of nodes which will be removed is more than that in the stack.\n");
		return;
	}

	if(number < list->number_of_nodes && list->number_of_nodes != number) // After operation, number_of_nodes > 0.
	{
		while(number > 0)
	    {
			struct linked_node* prev_node;

			prev_node = pop_node->prev;		
		    list->tail = prev_node; // Tail of the list is changed.
			list->tail->next = NULL;
		    pop_node->prev = NULL;
		    pop_node->next = NULL;
		    free(pop_node); // The previous tail node is freed.

            pop_node = prev_node;
		    (list->number_of_nodes)--;
		    number--;
	    }
		list->tail = pop_node;
	}
	if(number == list->number_of_nodes) // If number == list->number_of_nodes, list_exist will be 0.
	{
	    while(number > 0)
	    {
		    struct linked_node* pop_node = list->tail; // The pop_node is changed continuously whenever while statement is operated.
		
		    list->tail = list->tail->prev; // Tail of the list is changed.
		    pop_node->prev = NULL;
		    pop_node->next = NULL;
		    free(pop_node); // The previous tail node is freed.

		    (list->number_of_nodes)--;
		    number--;
	    }
		list->head = NULL;
		list->tail = NULL;
		free(list); // The list is freed.
	    list_exist = 0;
	}
}

/*
	@Function name: search_node
	@Parameters: list, find_node_value
	@Returns: none
	@Descriptions: This function is used to find node whose value is equal to find_node_value and count the order of the node.
	@Error cases: There is no node whose value is find_node_value.
 */

void search_node(struct linked_list* list, int find_node_value)
{
	struct linked_node* s_node;
	s_node = list->head; // s_node starts in head of the list.
	int order = 1; // The order of head is 1.

	while(s_node != NULL) // Function is finding find_node_value.
	{
		if(s_node->value == find_node_value) // Fucntion found find_node_value.
		{
			printf("The order of %d is %d\n", find_node_value, order);
			break;
		}
		else if(s_node->value != find_node_value)
		{
		    s_node = s_node->next; // s_node moves to the next node.
		    order++;
		}
	}
	if(s_node == NULL) // Function can't find a node whose value is find_node_value.
	{
		printf("Function search_node: There is no such node to search.\n");
	}
}

/*
	@Function name: swap_nodes
	@Parameters: list, node1, node2
	@Returns: none
	@Descriptions: This function swaps two nodes whose value are node1 and node2.
	@Error cases: node1 is equal to node2. / number of nodes is 1. / There is no node whose value is node1 or node2.
*/
void swap_nodes(struct linked_list* list, int node1, int node2)
{
	struct linked_node* swap_node1 = list->head;
	struct linked_node* swap_node2 = list->head;
	struct linked_node* prev1;
	struct linked_node* prev2;
	struct linked_node* next1;
	struct linked_node* next2;

	int order1 = 1;
	int order2 = 1;
	
	if(node1 == node2)
	{
		printf("Function swap_nodes: The node numbers are the same. Nothing to swap.\n");
		return;
	}

	while(swap_node1 != NULL)  // Finding node whose value is node1.
	{
		if(swap_node1->value == node1) 
		{
			break;
		}
		else if(swap_node1->value != node1)
		{
		    swap_node1 = swap_node1->next;
			order1++;
		}
	}

	while(swap_node2 != NULL)  // Finding node whose value is node2.
	{
		if(swap_node2->value == node2) 
		{
			break;
		}
		else if(swap_node2->value != node2)
		{
		    swap_node2 = swap_node2->next;
			order2++;
		}
	}

	if(order1 == 1 && order2 != list->number_of_nodes && swap_node2 != NULL && order2-order1 != 1) // node1 is head value && node2 is not tail value && next of node1 is not node2.
	{
		next1 = swap_node1->next;
		next2 = swap_node2->next;
		prev2 = swap_node2->prev;

		list->head = swap_node2;
		next2->prev = swap_node1;
		prev2->next = swap_node1;
		next1->prev = swap_node2;
		swap_node1->next = next2;
		swap_node1->prev = prev2;
		swap_node2->next = next1;
		swap_node2->prev = NULL;
	}

	if(order1 == 1 && order2 != list->number_of_nodes && swap_node2 != NULL && order2-order1 == 1) // node1 is head value && node2 is not tail value && next of node1 is node2.
	{
		next2 = swap_node2->next;

		list->head = swap_node2;
		next2->prev = swap_node1;
		swap_node1->next = next2;
		swap_node1->prev = swap_node2;
		swap_node2->next = swap_node1;
		swap_node2->prev = NULL;
	}

	if(order1 != list->number_of_nodes && swap_node1 != NULL && order2 == 1 && order1-order2 != 1) // node2 is head value && node1 is not tail value && next of node2 is not node1.
	{
		next2 = swap_node2->next;
		next1 = swap_node1->next;
		prev1 = swap_node1->prev;

		list->head = swap_node1;
		next1->prev = swap_node2;
		prev1->next = swap_node2;
		next2->prev = swap_node1;
		swap_node2->next = next1;
		swap_node2->prev = prev1;
		swap_node1->next = next2;
		swap_node1->prev = NULL;
	}

	if(order1 != list->number_of_nodes && swap_node1 != NULL && order2 == 1 && order1-order2 == 1) // node2 is head value && node1 is not tail value && next of node2 is node1.
	{
		next1 = swap_node1->next;

		list->head = swap_node1;
		next1->prev = swap_node2;
		swap_node2->next = next1;
		swap_node2->prev = swap_node1;
		swap_node1->next = swap_node2;
		swap_node1->prev = NULL;
	}

	if(order1 == list->number_of_nodes && order2 != 1 && swap_node2 != NULL && order1-order2 != 1) // node1 is tail value && node2 is not head value && next of node2 is not node1.
	{
		prev1 = swap_node1->prev;
		prev2 = swap_node2->prev;
		next2 = swap_node2->next;

		list->tail = swap_node2;
		prev1->next = swap_node2;
		prev2->next = swap_node1;
		next2->prev = swap_node1;
		swap_node1->next = next2;
		swap_node1->prev = prev2;
		swap_node2->prev = prev1;
		swap_node2->next = NULL;
	}

	if(order1 == list->number_of_nodes && order2 != 1 && swap_node2 != NULL && order1-order2 == 1) // node1 is tail value && node2 is not head value && next of node2 is node1.
	{
		prev2 = swap_node2->prev;

		list->tail = swap_node2;
		prev2->next = swap_node1;
		swap_node1->prev = prev2;
		swap_node1->next = swap_node2;
		swap_node2->prev = swap_node1;
		swap_node2->next = NULL;
	}

	if(order1 != 1 && swap_node1 != NULL && order2 == list->number_of_nodes && order2-order1 != 1) // node2 is tail value && node1 is not head value && next of node1 is not node2.
	{
		prev2 = swap_node2->prev;
		prev1 = swap_node1->prev;
		next1 = swap_node1->next;

		list->tail = swap_node1;
		prev2->next = swap_node1;
		prev1->next = swap_node2;
		next1->prev = swap_node2;
		swap_node2->next = next1;
		swap_node2->prev = prev1;
		swap_node1->prev = prev2;
		swap_node1->next = NULL;
	}

	if(order1 != 1 && swap_node1 != NULL && order2 == list->number_of_nodes && order2-order1 == 1) // node2 is tail value && node1 is not head value && next of node1 is node2.
	{
		prev1 = swap_node1->prev;

		list->tail = swap_node1;
		prev1->next = swap_node2;
		swap_node2->prev = prev1;
		swap_node2->next = swap_node1;
		swap_node1->prev = swap_node2;
		swap_node1->next = NULL;
	}

	if(order1 == 1 && order2 == list->number_of_nodes && list->number_of_nodes != 2) // node1 is head value && node2 is tail value && next of node1 is not node2.
	{
		next1 = swap_node1->next;
		prev2 = swap_node2->prev;

		list->head = swap_node2;
		list->tail = swap_node1;
		prev2->next = swap_node1;
		next1->prev = swap_node2;
		swap_node1->prev = prev2;
		swap_node1->next = NULL;
		swap_node2->next = next1;
		swap_node2->prev = NULL;
	}

	if(order1 == list->number_of_nodes && order2 == 1 && list->number_of_nodes != 2) // node 1 is tail value && node2 is head value && next of node2 is not node1.
	{
		next2 = swap_node2->next;
		prev1 = swap_node1->prev;

		list->head = swap_node1;
		list->tail = swap_node2;
		prev1->next = swap_node2;
		next2->prev = swap_node1;
		swap_node2->prev = prev1;
		swap_node2->next = NULL;
		swap_node1->next = next2;
		swap_node1->prev = NULL;

	}

	if(swap_node1 == list->head && swap_node2 == list->tail && order2-order1 == 1) // node1 is head value && node2 is tail value && next of node1 is node2.
	{
		swap_node1->prev = swap_node2;
		swap_node2->next = swap_node1;
		swap_node1->next = NULL;
		swap_node2->prev = NULL;
		list->head = swap_node2;
		list->tail = swap_node1;
	}

	if(swap_node1 == list->tail && swap_node2 == list->head && order1-order2 == 1) // node 1 is tail value && node2 is head value && next of node2 is node1.
	{
		swap_node2->prev = swap_node1;
		swap_node1->next = swap_node2;
		swap_node2->next = NULL;
		swap_node1->prev = NULL;
		list->head = swap_node1;
		list->tail = swap_node2;
	}

	if(swap_node1 != list->head && swap_node1 != list->tail && swap_node1 != NULL && swap_node2 != list->head && swap_node2 != list->tail && swap_node2 != NULL && order1-order2 != 1 && order2-order1 != 1) 
	// node1 and node2 are not value of head and tail && next or prev of node1 is not node2.
	{
	    prev1 = swap_node1->prev;
	    next1 = swap_node1->next;
	    prev2 = swap_node2->prev;
	    next2 = swap_node2->next;

		prev1->next = swap_node2;
		next1->prev = swap_node2;
		swap_node2->prev = prev1;
		swap_node2->next = next1;
		prev2->next = swap_node1;
		next2->prev = swap_node1;
		swap_node1->prev = prev2;
		swap_node1->next = next2;
	}

	if(swap_node1 != list->head && swap_node1 != list->tail && swap_node1 != NULL && swap_node2 != list->head && swap_node2 != list->tail && swap_node2 != NULL && order1-order2 == 1)
	// node 1 and node2 are not value of head and tail && next of node2 is node1.
	{
	    next1 = swap_node1->next;
	    prev2 = swap_node2->prev;

		next1->prev = swap_node2;
		prev2->next = swap_node1;
		swap_node2->prev = swap_node1;
		swap_node2->next = next1;
		swap_node1->prev = prev2;
		swap_node1->next = swap_node2;
	}

	if(swap_node1 != list->head && swap_node1 != list->tail && swap_node1 != NULL && swap_node2 != list->head && swap_node2 != list->tail && swap_node2 != NULL && order2-order1 == 1)
	// node 1 and node2 are not value of head and tail && next of node1 is node2.
	{
	    prev1 = swap_node1->prev;
	    next2 = swap_node2->next;
		
		next2->prev = swap_node1;
		prev1->next = swap_node2;
		swap_node1->prev = swap_node2;
		swap_node1->next = next2;
		swap_node2->prev = prev1;
		swap_node2->next = swap_node1;
	}

	if(list->number_of_nodes == 1)
	{
		printf("Function swap_nodes: The list size is smaller than 2, there is nothing to swap.\n");
		return;
	}

	if(swap_node1 == NULL || swap_node2 == NULL)
	{
		printf("Function swap_nodes: either one of the nodes is not available.\n");
		return;
	}
}

/*
	@Function name: forward_by_one
	@Parameters: list
	@Returns: none
	@Descriptions: After this function run, head node will be tail node and the others move to left.
	@Error case: There is no list. / number of nodes is 1. / list type is 1.
*/
void forward_by_one(struct linked_list* list) 
{
	if(list_exist == 0 || list->number_of_nodes == 1)
	{
		printf("Function forward_by_one: The list size is smaller than 2, there is nothing to rotate.\n");
		return;
	}
	else if(list_exist == 1 && list->number_of_nodes >= 2)
	{
		struct linked_node* new_node1 = list->head;
	    struct linked_node* new_node2 = list->tail;

		list->head = list->head->next; // Making new head.
		list->head->prev = NULL;
		list->tail = new_node1; // Original head will be tail of new list.
		new_node2->next = new_node1;
		new_node1->prev = new_node2;
		new_node1->next = NULL;
	}

	if(list->type_of_list == 1) // If the type of list is stack, print error message.
	{
		printf("Function forward_by_one: The list type is not normal.\n");
		return;
	}
}

/*
	@Function name: backward_by_one
	@Parameters: list
	@Returns: none
	@Descriptions: After this function run, tail node will be head node and the others move to right.
	@Error cases: There is no list. / number of nodes is 1. / list type is 1.
*/
void backward_by_one(struct linked_list* list)
{
	if(list_exist == 0 || list->number_of_nodes == 1)
	{
		printf("Function forward_by_one: The list size is smaller than 2, there is nothing to rotate.\n");
		return;
	}
	else if(list_exist == 1 && list->number_of_nodes >= 2)
	{
		struct linked_node* new_node3 = list->head;
	    struct linked_node* new_node4 = list->tail;

		list->tail = new_node4->prev; // Making new tail.
		list->tail->next = NULL;
		new_node3->prev = new_node4;
		new_node4->next = new_node3;
		list->head = new_node4; // Original tail will be head of new list.
	}

	if(list->type_of_list == 1) // If the type of list is stack, print error message.
	{
		printf("Function forward_by_one: The list type is not normal.\n");
		return;
	}
}

/*
	@Function name: reverse_range
	@Parameters: list, order1, order2
	@Returns: none
	@Descriptions: This function reverse the nodes between order1 and order2.
	@Error cases: order1 is bigger than oreder 2. / order 2 is bigger than number of nodes. / order1 is smaller 1.
*/

void reverse_range(struct linked_list* list, int order1, int order2)
{
	struct linked_node* re_node_1 = list->head;
	struct linked_node* re_node_2 = list->head;

	int i;

	if(order1 > order2 || order2 > list->number_of_nodes || order1 <1 )
	{
		printf("Function reverse_range: Input value is invalid.\n");
		return;
	}	

	for(i = 1; i < order1; i++) // Finding node of order1.
	{
		re_node_1 = re_node_1->next;
	}

	for(i = 1; i < order2; i++) // Finding node of order2.
	{
		re_node_2 = re_node_2->next;
	}

	if((order2 - order1) % 2 == 1) // Number of reversing nodes is even. 
	{
		for(i = 0; i < (order2 - order1 +1)/2; i++)
		{
			if(i % 2 == 0) // After this statement, order of re_node_1 is bigger than order of re_node_2.
			{
				swap_nodes(list, re_node_1->value, re_node_2->value);
			    re_node_1 = re_node_1->prev;
			    re_node_2 = re_node_2->next;
			}

			if(i % 2 == 1) // After this statement, order of re_node_1 is smaller than order of re_node_2.
			{
				swap_nodes(list, re_node_1->value, re_node_2->value);
			    re_node_1 = re_node_1->next;
			    re_node_2 = re_node_2->prev;
			}
		}
	}

	else if((order2 - order1) % 2 == 0) // Number of reversing nodes is odd.
	{
		for(i = 0; i < (order2 - order1)/2; i++)
		{
			if(i % 2 == 0)
			{
				swap_nodes(list, re_node_1->value, re_node_2->value);
			    re_node_1 = re_node_1->prev;
			    re_node_2 = re_node_2->next;
			}

			if(i % 2 == 1)
			{
				swap_nodes(list, re_node_1->value, re_node_2->value);
			    re_node_1 = re_node_1->next;
			    re_node_2 = re_node_2->prev;
			}
		}
	}
}

/*
	@Function name: powerofN_reverse
	@Parameters: list, n
	@Returns: none
	@Descriptions: This function uses reverse_range function. The nodes will be reversed in pow(n,i).
	@Error cases: none
*/


void powerofN_reverse(struct linked_list* list, int n)
{
	int i;
	int k = list->number_of_nodes;

	for(i = 1; k - ((pow(n,i+1))-1)/(n-1) >= 0; i++) // In this loop, the nodes are reversed in pow(n,0), pow(n,1), pow(n,2) ... etc.
	{
		reverse_range(list, 1+((pow(n,i))-1)/(n-1), ((pow(n,i+1))-1)/(n-1)); // sum of geometric sequence
	}

	if(k - ((pow(n,i))-1)/(n-1) != 0) // In this if statement, the other nodes which are not reversed in for loop will be reversed.
	{
		reverse_range(list, 1+((pow(n,i))-1)/(n-1), k);
	}
}

/*
	@Function name: print_list
	@Parameters: list
	@Returns: none
	@Descriptions: This function prints list.
	@Error cases: There is no list.
 */
void print_list(struct linked_list* list)
{
	if(list_exist == 0)
	{
		printf("There is no list to print\n");
		return;
	}
	struct linked_node * temp = list->head;
	printf("****************************************************************************\n\n");
	printf("	Number of nodes: %d\n", list->number_of_nodes);
	printf("\n");
	int i=0;
	for(i=0; i < list->number_of_nodes; i++)
	{
		printf ("%d   ", temp->value);
		temp = temp->next;
	}
	printf("\n");
	printf("****************************************************************************\n\n");
	free(temp);
}