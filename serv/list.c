
#include "list.h"


//Student 301369321 
//name: Sanseerat Virk
//email:ssv3@sfu.camake

//////////////////////////////////////////////////////////////////////////////
/////////////////////////////RESOURSCES///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// https://www.youtube.com/watch?v=-gXWhJyeJvA
// https://github.com/Skylan916/S-Talk/blob/master/list.h
// found the exact implemetation online however all code below written by me
// test written accordinly 
static List list[LIST_MAX_NUM_HEADS];
static Node node[LIST_MAX_NUM_NODES];

bool first_time = true;

// format code crtl shit I



void first_time1()
{

    free_list = &list[0];
    free_node = &node[0];

    for (int i = 0; i < LIST_MAX_NUM_HEADS - 1; i++)
    {

        list[i].next_free_list = &list[i + 1];
    }

    // end of list space
    list[LIST_MAX_NUM_HEADS - 1].next_free_list = NULL;

    for (int i = 0; i < LIST_MAX_NUM_NODES - 1; i++)
    {

        node[i].next = &node[i + 1];
    }

    node[LIST_MAX_NUM_NODES - 1].next = NULL;
}

void stage_list(List *newlist)
{

    // check should not be null because list avalibility also checks
    assert(newlist != NULL);
    newlist->items = 0;
    newlist->head = NULL;
    newlist->tail = NULL;
    newlist->current = NULL;
    newlist->bound = LIST_OOB_START;
    newlist->next_free_list = NULL;
}

void empty_list(List *list)
{

    assert(list != NULL);
    list->items = 0;
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    list->bound = LIST_OOB_START;
    list->next_free_list = NULL;
}

List *list_avalibility()
{

    if (free_list != NULL)
    {

        List *new_list = free_list;
        free_list = free_list->next_free_list;
        stage_list(new_list); // reset
        return new_list;
    }

    return NULL;
}

// prepare for data inseration
void stage_node(Node *new_node)
{

    new_node->data = NULL;
    new_node->next = NULL;
    new_node->next = NULL;
}

Node *node_avalibility()
{

    if (free_node != NULL)
    {

        Node *new_node = free_node;
        free_node = free_node->next;
        stage_node(new_node);
        return new_node;
    }

    return NULL;
}

// tail and head point to same node change bounds,change size
int empty_insert(List *plist, void *item)
{

    Node *new_node = node_avalibility();

    // no more nodes
    if (new_node == NULL)
    {

        return LIST_FAIL;
    }

    new_node->data = item;

    plist->head = new_node;
    plist->tail = new_node;
    plist->items++;

    plist->current = new_node;
    plist->bound = LIST_OOB_IN;

    return LIST_SUCCESS;
}

List *List_create()
{

    // link the list to make use of next avalaible list
    // do a n operation on first call
    // only executes on first call
    if (first_time)
    {
        first_time1();
        first_time = false;
    }

    // track if allocation of list avaliable
    List *new_list = list_avalibility();

    return new_list;
}

// update item count on addition
int List_count(List *pList)
{
    assert(pList != NULL);
    return pList->items;
}

// head points to first item in list
// intilizes current pointer
// change items+ addtion of nodes to list
// tracking emptiness with items
void *List_first(List *pList)
{

    assert(pList != NULL);

    if (pList->items > 0)
    {

        pList->current = pList->head;
        pList->bound = LIST_OOB_IN;
        return pList->current->data;
    }
    pList->current = NULL;
    return NULL;
}

// tail is the last item in list
void *List_last(List *pList)
{
    assert(pList != NULL);

    if (pList->items > 0)
    {
        // if size is 1 tail==head
        pList->current = pList->tail;
        pList->bound = LIST_OOB_IN;
        return pList->current->data;
    }

    pList->current = NULL;

    return NULL;
}

// require work
//must recive correct bounds otherwise will cause sef fault
void *List_next(List *pList)
{

    assert(pList != NULL);

    // CURENT NEXT WIILL CAUSE ERROR IF CURRENT IS TAIL

    if (pList->items == 0)
    {
        pList->current = NULL;
        pList->bound = LIST_OOB_END;
        return NULL;
    }
    else if (pList->bound == LIST_OOB_END)
    {
        return NULL;

        // if at start next is head
    }
    else if (pList->bound == LIST_OOB_START)
    {
        //current pointer is moved in bounds
        pList->current = pList->head;
        pList->bound = LIST_OOB_IN;
        return pList->current->data;
    }
    else if (pList->bound == LIST_OOB_IN)
    {
        
        // two cases current can be tail
        //can go out of bounds on this move
        if (pList->current == pList->tail)
        {

            //if memory acess done on next current seg fault
            pList->current = NULL;
            pList->bound = LIST_OOB_END;
            return NULL; // will cause seg fault 
        }
        else
        {


            pList->current = pList->current->next;
            return pList->current->data;
        }
    }
    else
    {

        // should not come here make sure all bounds are set correctly
        // every time current pointer is changed
        assert(true);
    }

    return NULL;
}

// require work
void *List_prev(List *pList)
{

    if (pList->items == 0)
    {
        pList->current = NULL;
        pList->bound = LIST_OOB_START;
        return NULL;
    }
    else if (pList->bound == LIST_OOB_START)
    {
        return NULL;
    }
    else if (pList->bound == LIST_OOB_END)
    {
        pList->current = pList->tail;
        pList->bound = LIST_OOB_IN;
        return pList->current->data;
    }
    else if (pList->bound == LIST_OOB_IN)
    {
        //Fix here
         
        // two cases current can be head
        if (pList->current == pList->head)
        {

            pList->current = NULL;
            pList->bound = LIST_OOB_START;
            return NULL;
        }
        else
        {

            pList->current = pList->current->previous;
            return pList->current->data;
        }
    }
    else
    {

        // should not come here make sure all bounds are set correctly
        // every time current pointer is changed
        assert(false);
    }

    return NULL;
}

void *List_curr(List *pList)
{

    assert(pList != NULL);

    if (pList->bound == LIST_OOB_END || pList->bound == LIST_OOB_START)
    {

        return NULL;
    }else{

        return pList->current->data;
    }

    return NULL;
}

// Adds the new item to pList directly after the current item, and makes item the current item.
// If the current pointer is before the start of the pList, the item is added at the start. If
// the current pointer is beyond the end of the pList, the item is added at the end.
// Returns 0 on success, -1 on failure.
int List_insert_after(List *pList, void *pItem)
{

    assert(pList != NULL);

    if (pList->items == 0)
    {

        return empty_insert(pList, pItem);
    }
    else if (pList->bound == LIST_OOB_START)
    {
        return List_prepend(pList, pItem);
    }
    else if (pList->bound == LIST_OOB_END || pList->current == pList->tail)
    {
        return List_append(pList, pItem);
    }
    else
    { // in bounds

        Node *new_node = node_avalibility();

        if (new_node == NULL)
        {
            return LIST_FAIL;
        }

        new_node->data = pItem;
        new_node->previous = pList->current;
        new_node->next = pList->current->next;

        pList->current->next->previous = new_node;
        pList->current->next = new_node;

        pList->current = new_node;
        pList->bound = LIST_OOB_IN;
        pList->items++;

        return LIST_SUCCESS;
    }
    return LIST_FAIL;
}

int List_insert_before(List *pList, void *pItem)
{

    assert(pList != NULL);
    

    if (pList->items == 0)
    {

        return empty_insert(pList, pItem);
    }
    else if (pList->bound == LIST_OOB_START || pList->current == pList->head)
    {
        return List_prepend(pList, pItem);
    }
    else if (pList->bound == LIST_OOB_END)
    {
        return List_append(pList, pItem);
    }
    else
    { // in bounds

        Node *new_node = node_avalibility();

        if (new_node == NULL)
        {
            return LIST_FAIL;
        }
        new_node->data = pItem;
        new_node->next = pList->current;
        new_node->previous = pList->current->previous;

        //modify node to which inserted before
        pList->current->previous->next = new_node;
        pList->current->previous = new_node;

        pList->current = new_node;
        pList->bound = LIST_OOB_IN;
        pList->items++;

        return LIST_SUCCESS;
    }
    return LIST_FAIL;
}

// Adds item to the end of pList, and makes the new item the current one.
// Returns 0 on success, -1 on failure.
int List_append(List *pList, void *pItem)
{

    if (pList->items == 0)
    {

        return empty_insert(pList, pItem);
    }
    else
    {

        Node *new_node = node_avalibility();

        if (new_node == NULL)
        {

            return LIST_FAIL;
        }

        new_node->data = pItem;
        // join
        new_node->previous = pList->tail;
        pList->tail->next = new_node;

        pList->tail = new_node;
        pList->items++;

        pList->current = new_node;
        pList->bound = LIST_OOB_IN;

        return LIST_SUCCESS;
    }

    return LIST_FAIL;
}

// Adds item to the front of pList, and makes the new item the current one.
// Returns 0 on success, -1 on failure.
int List_prepend(List *pList, void *pItem)
{
    if (pList->items == 0)
    {

        return empty_insert(pList, pItem);
    }
    else
    {

        Node *new_node = node_avalibility();

        if (new_node == NULL)
        {

            return LIST_FAIL;
        }

        new_node->data = pItem;
        // join
        new_node->next = pList->head;
        pList->head->previous = new_node;

        pList->head = new_node;
        pList->items++;

        pList->current = new_node;
        pList->bound = LIST_OOB_IN;

        return LIST_SUCCESS;
    }

    return LIST_FAIL;
}
// removal dependent on current pointer, need to make sure its moves correct
void *List_remove(List *pList)
{

    if (pList->bound == LIST_OOB_END || pList->bound == LIST_OOB_START)
    {

        return NULL;
    }

    Node *ret = pList->current;

    if(pList->items==1){

        empty_list(pList); // head pointer current pointer need to be reset
        // free_node->previous = last_item;
        ret->next = free_node;
        free_node = ret;
        return ret->data;
    }

    if (pList->current == pList->head)
    {
        // insert current pointer moves
        //on size 0 it turns null;
        pList->head = pList->head->next;
        pList->head->previous = NULL;

    }
    else if (pList->current == pList->tail)
    {
        // insert current pointer moves
        pList->tail = pList->tail->previous;
        pList->tail->next = NULL;
        pList->bound=LIST_OOB_END;
       
    }
    else
    {

        pList->current->previous->next = pList->current->next;
        pList->current->next->previous = pList->current->previous;
    }

    // unnneccasry previous link but useful if testing for transversal, caused sed gault when no free node
    // free_node->previous = ret;

    // move current pointer to next, will take care of all cases
    List_next(pList);

    ret->next = free_node;
    free_node = ret;
    pList->items--;

    return ret->data;
}

// forgot to free up the node
// this is dependent on items
void *List_trim(List *pList)
{

    if (pList->items == 0)
    {

        return NULL;
    }

    Node *last_item = pList->tail;

    // removing last item list will be empty
    if (pList->items == 1)
    {

        empty_list(pList); // head pointer current pointer need to be reset
        // free_node->previous = last_item;
        last_item->next = free_node;
        free_node = last_item;
        return last_item->data;
    }

    pList->tail = pList->tail->previous;
    pList->tail->next = NULL;
    pList->current = pList->tail;
    pList->bound = LIST_OOB_IN;
    pList->items--;

    // program crash with this line if no more free nodes not good idea remove
    // free_node->previous = last_item;
    last_item->next = free_node;
    free_node = last_item;

    return last_item->data;
}

// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1.
// pList2 no longer exists after the operation; its head is available
// for future operations.
void List_concat(List *pList1, List *pList2)
{

    assert(pList1 != NULL && pList2 != NULL);

    if (pList1->items == 0)
    {
        // empty assuming previous functions kept everything null;
        if (pList2->items == 0)
        {
            // do nothing
        }
        else
        { // list 1 empty not list2

            // COPY PLIST2 INTO PLIST1
            pList1->head = pList2->head;
            pList1->items = pList2->items;
            pList1->current = pList2->current;
            pList1->tail = pList2->tail;
        }
    }
    else
    { // list 1 is not empty
        if (pList2->items == 0)
        {
            // do nothing
        }
        else
        {

            // attach tail PLIST2 INTO PLIST1
            // take care of total items
            pList2->head->previous = pList1->tail;
            pList1->tail->next=pList2->head;
            pList1->tail = pList2->tail;
            pList1->items = pList1->items + pList2->items;

        }
    }

    // mark as free list
    stage_list(pList2);
    pList2->next_free_list = free_list;
    free_list = pList2;
};

// Delete pList. pItemFreeFn is a pointer to a routine that frees an item.
// It should be invoked (within List_free) as: (*pItemFreeFn)(itemToBeFreedFromNode);
// pList and all its nodes no longer exists after the operation; its head and nodes are
// available for future operations.
typedef void (*FREE_FN)(void *pItem);
void List_free(List *pList, FREE_FN pItemFreeFn)
{

    if(pItemFreeFn!=NULL){

        assert(pList != NULL);
        Node *p = pList->head;
        Node *temp;
        while (p != NULL)
        {

            temp = p;
            p = p->next;

            (*pItemFreeFn)(temp->data);
            temp->next = free_node;
            free_node = temp;
        }

        stage_list(pList);
        pList->next_free_list = free_list;
        free_list = pList;
    }
   
};

// Search pList, starting at the current item, until the end is reached or a match is found.
// In this context, a match is determined by the comparator parameter. This parameter is a
// pointer to a routine that takes as its first argument an item pointer, and as its second
// argument pComparisonArg. Comparator returns 0 if the item and comparisonArg don't match,
// or 1 if they do. Exactly what constitutes a match is up to the implementor of comparator.
//
// If a match is found, the current pointer is left at the matched item and the pointer to
// that item is returned. If no match is found, the current pointer is left beyond the end of
// the list and a NULL pointer is returned.
//
// If the current pointer is before the start of the pList, then start searching from
// the first node in the list (if any).
typedef bool (*COMPARATOR_FN)(void *pItem, void *pComparisonArg);
void *List_search(List *pList, COMPARATOR_FN pComparator, void *pComparisonArg)
{
    if(pComparator==NULL){
        return NULL;
    }
    // what happens when current pointer is at end of list leaving this be
    if (pList->bound == LIST_OOB_START)
    {

        pList->current = pList->head;
        pList->bound = LIST_OOB_IN;
    }

    while (pList->current != NULL)
    {

        if ((pComparator)(pList->current->data, pComparisonArg))
        {

            return pList->current->data; // should take it out of the fucntion
                                         // no need to worry about bounds
        }

        pList->current = pList->current->next;
    }

    // if not already
    pList->bound = LIST_OOB_END;

    return NULL;
};
