# Test Auriga
## FIRST TASK
The problem is that allocating item-next is wrong because . It should be assigned the newly allocated memory, but it is being assigned the existing item->next value
```c
    /* Inserts a new list item after the one specified as the argument.
*/
void insert_next_to_list(list_t *item, int data) {
(item->next = malloc(sizeof(list_t)))->next = item->next;
item->next->data = data;
}
```
    To fix this we should assign item->next to newuly allocated memory
```c
void insert_next_to_list(list_t *item, int data) {
    list_t *new_item = malloc(sizeof(list_t)); 
    new_item->next = item->next; 
    item->next = new_item; 
    new_item->data = data; 
}
```
    2. This code has a problem in free(item->next)  after freeing this code can provide undefind behaviour because it accesing non freed memory
```c
void remove_next_from_list(list_t *item) {
	 if (item->next) {
		free(item->next);
        item->next = item->next->next;
     }
}
```
    To fix this we should assign item next to a pointer and than free its
```c
void remove_next_from_list(list_t *item) {
    if (item->next) {
        list_t *next_item = item->next;
        item->next = next_item->next; 
        free(next_item); 
    }
}
```

    
    The problem with this function is not so important but can provide undefind beahvior cause buf is not a dynamicly located array and better way is to return a pointer after allocating memory
```c
char *item_data(const list_t *list)
{
	char buf[12];

	sprintf(buf, "%d", list->data);
	return buf;
}
``` 
    Like this
```c
char *item_data(const list_t *list) {
    char *buf = malloc(12); // Allocate memory dynamically
    sprintf(buf, "%d", list->data);
    return buf;
}
```

## SECOND TASK

1) First case is portability when u are puting down ur app with static libs it become more self-contained and u dont need to install as much deps as u need with dynamic apps;
2) Second case is simple deployment because u dont need to manage a lot of dynamic linked libraries and other deps 
3) Security and trust its more important take because u eliminates external deppendincies that can change at any time and have vulenerabilities and u can make a security oriented forks of static libs
4) Performance case static apps are all about reducing runtime access things for example u dont need to resolve runtime symbols or dynamic elements
5) Embedded case in resource-constrained environments such as embedded systems or devices with limited storage or memory statically linking can be beneficial it allows you to reduce the overall footprint of the application by eliminating the need for external dynamic libraries

## THIRD TASK
- inside folder aurig_message_parser
## FORTH TASK
At a high level inside unix like os breakpoint is mechanism called trap or signal handling, debugger modifies program code temporarily and run app than signal is waiting for trap is activating and than callback inside debuger holds this case

## FIFTH TASK

All applications load their libs or other context inside their memory space and doesn't affect others
, so putting trap or breakpoint doesnt affect other applications linked to the same libs.

## SIXTH TASK
If a user process initiates an I/O operation with a device and then stops waiting for the operation to complete in the device the device operation will complete during the execution of some other process in the system. The hardware interrupt signaling the completion of the operation will be handled by the operating system. Since handling the interrupt takes some time the current process in a single-processor system will be suspended. Thus any process in the system unpredictably affects the performance of other processes regardless of their priorities.