//Zeye Gu 101036562
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "header.h"

int main(){
  ListType booksByTitle, booksByYear, tmpList;
  initList(&booksByTitle);
  initList(&tmpList);
  initList(&booksByYear);

  BookType **book=malloc(sizeof(BookType *));

  while(1){
    if(initBook(book) == C_OK){
      addByTitle(&booksByTitle,*book);
    }
    else{
      break;
    }
  }
  printf("-----------This is the list: bookByTitle:----------\n");
  printList(&booksByTitle);
  copyList(&booksByTitle, &tmpList);
  printf("\n-----------This is the list: tmpList:----------\n");
  printList(&tmpList);
  char name[MAX_STR];
  printf("Which author do you want to delete?\n");
  scanf("%s",name);
  printf("-----------This is the list: bookByTitle:----------\n");
  printList(&booksByTitle);

  printf("\n-----------This is the list: tmpList( %s deleted):----------\n",name);
  delAuthor(&tmpList,name);
  printList(&tmpList);
  copyByYear(&booksByTitle,&booksByYear);
  printf("\n-----------This is the list: bookByTitle:----------\n");
  printList(&booksByTitle);
  printf("-----------This is the list: booksByYear :----------\n");
  printList(&booksByYear);
  free(*book);
  free(book);
  cleanupList(&booksByYear);
  cleanupList(&tmpList);
  cleanupData(&booksByTitle);
  cleanupList(&booksByTitle);
  printf("\nAll allocated memory has been cleaned\n");
  return C_OK;
}

/*
  Function:  addByTitle
  Purpose:   This function will prompt the user for a book title, author, and year. If the user enters “end” for a book
             title, the function will return a failure code. If a different string is entered for a title, the user will be
             prompted for the author and year, then a book structure will be dynamically allocated and initialized
             with the data entered. The new book will be returned using the function’s output parameter book, and
             success will be returned as the return value.
  Parameters:
    in:      a book
    out:     a book which has allocted memory, and the book has title, author and year of publication
    return:  C_OK for success, C_NOK for fail.
*/

int initBook(BookType **book){
  char name[MAX_STR];
  printf("\nTitle?\n");
  scanf("%s",name);
  if(strcmp(name,"end")==0){
    return C_NOK;
  }
  else{
    char author[MAX_STR];

    *book =(BookType *)malloc(sizeof(BookType));
    strcpy((*book)->title, name);
    printf("Author?\n");
    scanf("%s",author);
    strcpy((*book)->author, author);
    printf("Publication year?\n");
    scanf("%d",&(*book)->year);

  }
  return C_OK;
}
/*
  Function:  initList
  Purpose:    the initList() function will initialize the fields of the given list
  Parameters:
    in:      a list
    out:     a list with NULL value at head and tail.
*/

void initList(ListType *list){
  //list =malloc(sizeof(ListType));
  list->head=NULL;
  list->tail=NULL;
}


/*
  Function:  printList
  Purpose:   the printList() function will print all the data for the books contained in list; after all the books
             are printed out, the function will indicate which book corresponds to the head node, and which one
             corresponds to the tail node
  Parameters:
    in:      a list
    out:     print data of every Node in the linked list.
*/

void printList(ListType *list){
  if(list->head !=NULL){
  NodeType *currNode = list->head;
  printf("\nBook List:\n");
  while (currNode != NULL) {

    printf("--%32s by %20s,Yr: %d\n",
           currNode->data->title,
           currNode->data->author,
           currNode->data->year);
    currNode = currNode->next;
  }

  if (list->tail !=NULL){
    printf("-->HEAD IS:--      %32s by %20s,Yr: %d\n",
           list->head->data->title,
           list->head->data->author,
           list->head->data->year);
    printf("-->TAIL IS:--      %32s by %20s,Yr: %d\n",
           list->tail->data->title,
           list->tail->data->author,
           list->tail->data->year);

    }
  }else{
    printf("This is an empty list ");
  }
}

/*
  Function:  addByTitle
  Purpose:    add newBook to the correct position in list, to keep the list in
              ascending alphabetical order by title
  Parameters:
    in:      book list and book
    out:     linked list ordered by booktitle
*/

void addByTitle(ListType *list, BookType *newBook){
  NodeType * bookNode = malloc(sizeof(NodeType));
  bookNode->data = newBook;
  bookNode->next = NULL;
  if(list->head == NULL){//base case
      list->head = bookNode;
      list->tail = bookNode;
      //printf("added to head\n");
  }else{
    char title[MAX_STR];
    strcpy(title,bookNode->data->title);
    if(strcmp(title,list->head->data->title)< 0){// add to the head
      //printf("add to the front");
      bookNode->next = list->head;
      list->head = bookNode;
    }else{
    //  printf("start while loop");
      NodeType * tempNode = list->head;
      int added=0;
      while(1){
        if(tempNode->next == NULL){
        //  printf("loop finished by reaching end");
          break;
        }else if(strcmp(title, tempNode->data->title)>=0 && strcmp(title, tempNode->next->data->title)<0){// add to somewhere mid
        //  printf("add to somewhere mid");
          bookNode->next = tempNode->next;
          tempNode->next = bookNode;
          added=1;
          break;
          }else{
            tempNode = tempNode->next;
          }
        }
          if(added==0){
        //  printf(" add to the end");
          tempNode->next = bookNode;//add to the end
          list->tail = bookNode;
      }
    }
  }
}

/*
  Function:  copyList
  Purpose:    the copyList() function will add each book currently in the src list to the dest list, in ascending
              order by title; no changes should be made to the src list
  Parameters:
    in:      src list(the list we want to copy)
    in:      dest list(the list we copy to )
    out:     dest list
*/
void copyList(ListType *src, ListType *dest){
  NodeType *currNode = src->head;
  while(currNode!=NULL){
    addByTitle(dest, currNode->data);
    currNode=currNode->next;
  }
}
/*
  Function:  delAuthor
  Purpose:   the delAuthor() function will remove from list all the books by the author specified in name
  Parameters:
    in:      the list need to do the delete by author operation
    in:      the name of the author
    out:     modified list
*/
void delAuthor(ListType *list, char *name){
    /*currNode = list->head;
    prevNode = NULL;
    if(strcmp(name,currNode->data->author)==0){
      printf("delete the head");
      list->head =list->head->next;
      free(currNode->data);
      free(currNode);
    *///}else{
  if(list->head->next == NULL){
    if(strcmp(name,list->head->data->author)==0){
      free(list->head);
      list->head=NULL;
      list->tail=NULL;
      return;
    }
  }
    NodeType *currNode,*prevNode;
    prevNode = list->head;
    currNode = list->head->next;
        if(strcmp(name,prevNode->data->author)==0&&currNode->next==NULL){
          free(prevNode);
          list->head=currNode;
          list->tail=currNode;
        }


      while(currNode->next!= NULL){
        if(strcmp(name,prevNode->data->author)==0){
          //  printf("delete the head");
            free(prevNode);
            prevNode=currNode;
            list->head= currNode;
            currNode=currNode->next;
        }
        else if(strcmp(name,currNode->data->author)==0){
          //printf("delete in somwhere mid");
          prevNode->next=currNode->next;
          free(currNode);
          currNode=prevNode->next;
          if(currNode->next==NULL){list->tail=currNode;}

        }
        else{
          prevNode = currNode;
          currNode = currNode->next;
        }
      }
      if(strcmp(name,currNode->data->author)==0){
        //printf("delete the tail");
        prevNode->next=NULL;
        list->tail=prevNode;
        free(currNode);
      }else{
          list->tail=currNode;
      }

  //  }

}
/*
  Function:  addByYear
  Purpose:   the addByYear() function will add newBook to the correct position in list, to keep the list in
             descending order by year
  Parameters:
    in:      the linked list to modify
    in:      the book need to be added into linked list
    out:     linked list contains books  ordered by year;
*/
void addByYear(ListType *list, BookType *newBook){
  NodeType * bookNode = malloc(sizeof(NodeType));
  bookNode->data = newBook;
  bookNode->next = NULL;
  if(list->head == NULL){//base case
      list->head = bookNode;
      list->tail = bookNode;
    //  printf("added to head\n");
  }else{
    int year =bookNode->data->year;
    if(year>list->head->data->year){// add to the head
    //  printf("add to the front");
      bookNode->next = list->head;
      list->head = bookNode;
    }else{
    //  printf("start while loop");
      NodeType * tempNode = list->head;
      int added=0;
      while(1){
        if(tempNode->next == NULL){
        //  printf("loop finished by reaching end");
          break;
        }else if(year<=tempNode->data->year && year>tempNode->next->data->year){// add to somewhere mid
        //  printf("add to somewhere mid");
          bookNode->next = tempNode->next;
          tempNode->next = bookNode;
          added=1;
          break;
          }else{
            tempNode = tempNode->next;
          }
        }
          if(added==0){
        //  printf(" add to the end");
          tempNode->next = bookNode;//add to the end
          list->tail = bookNode;
      }
    }
  }
}

/*
  Function:  copyByYear
  Purpose:    the copyByYear() function will add each book currently in the src list to the dest list, in descending
              order by year; no changes should be made to the src list
  Parameters:
    in:      src list(the list we want to copy)
    in:      dest list(the list we copy to )
    out:     dest list
*/
void copyByYear(ListType *src, ListType *dest){
  if(src->head != NULL){
    NodeType *currNode = src->head;
    while(currNode!=NULL){
      addByYear(dest, currNode->data);
      currNode=currNode->next;
    }
  }
}

/*
  Function:  cleanupList
  Purpose:   the cleanupList() function will clean up the memory associated with the nodes in list
  Parameters:
    in:      list need to be freed
    out:     list has been freed
*/
void cleanupList(ListType *list){

  NodeType *prevNode = list->head;
  NodeType *currNode = NULL;
  while(prevNode->next!=NULL){
    currNode=prevNode->next;
    free(prevNode);
    prevNode = currNode;
  }

    free(list->head);
    free(list->tail);

  list->head = NULL;
  list->tail = NULL;
}


/*
  Function:  cleanupData
  Purpose:   the cleanupData() function will clean up the memory associated with the books contained in list
  Parameters:
    in:      list need to be freed
    out:     list has been freed
*/
void cleanupData(ListType* list){
  NodeType *prevNode = list->head;
  NodeType *currNode = NULL;
  while(prevNode->next!=NULL){
    currNode=prevNode->next;
    free(prevNode->data);
    prevNode =currNode;
  }

    free(list->head->data);
    free(list->tail->data);
}
