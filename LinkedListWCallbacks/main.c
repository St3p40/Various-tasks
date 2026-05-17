#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

// Define for callback definition
#define CALLBACK_DEF(name)   void name() {\
  printf(#name " works.\n");\
}

//------------------------------------------------------------------------------
typedef struct list_obj {                                   ///< Structure name
  uint8_t priority;                                         ///< Node's priority
  char name[15];                                            ///< Node's name
  struct list_obj* next;                                    ///< Pointer to next Node
  void (*callback)(void);                                   ///< Callback function
} list_t;                                                   ///< List type name


//------------------------------------------------------------------------------
/// @brief Adding Node function
//------------------------------------------------------------------------------
void addObjectInList(list_t* head, uint8_t priority, char* name, void (*callback)(void)) {
  // Check correct input values
  assert(head != NULL);
  assert(name != NULL);
  assert(callback != NULL);

  // TODO: For multithreading app mutex lock should be there!
  while (head->next != NULL && head->next->priority <= priority) {
    head = head->next;
  }
 
  list_t* backup = head -> next;
  head->next = (list_t*)malloc(sizeof(list_t));
  head = head->next;
  head->next = backup;
  head->priority = priority;
  strcpy(head->name, name);
  head->callback = callback;

  // TODO: For multithreading app mutex unlock should be there!
}


//------------------------------------------------------------------------------
/// @brief Removing Node function
//------------------------------------------------------------------------------
void removeObjectInList(list_t* head, char* name) {
  // Check correct input values
  assert(head != NULL);

  // TODO: For multithreading app mutex lock should be there!
  list_t* b = head;

  if (strcmp(head -> next->name, name) == 0) {
    list_t* temp = head -> next;
    head -> next = head -> next -> next;
    free(temp);
    return;
  }

  while (b->next != NULL && strcmp(b->next->name, name) != 0) {
    b = b->next;
  }

  if (b->next == NULL)
    return;

  list_t* temp = b->next;
  b->next = b->next->next;
  free(temp);

  // TODO: For multithreading app mutex unlock should be there!
}


//------------------------------------------------------------------------------
/// @brief Running whole list function
//------------------------------------------------------------------------------
void runList(list_t* head) {
  // Check correct input values
  assert(head != NULL);
  // TODO: For multithreading app mutex lock should be there!
  list_t* temp = head -> next;
  while (temp != NULL) {
    if (temp->callback != NULL)
      temp->callback();
    temp = temp->next;
  }
  // TODO: For multithreading app mutex unlock should be there!
}


//------------------------------------------------------------------------------
/// @brief Making functions for callback
//------------------------------------------------------------------------------
CALLBACK_DEF(callBack1)
CALLBACK_DEF(callBack2)
CALLBACK_DEF(callBack3)


//------------------------------------------------------------------------------
int main() {
  list_t a = {0};

  addObjectInList(&a, 1, "node1", callBack1);
  addObjectInList(&a, 3, "node2", callBack2);
  addObjectInList(&a, 2, "node3", callBack3);
  runList(&a);
  printf("\n");
  removeObjectInList(&a, "node2");

  runList(&a);

  return 0;
}