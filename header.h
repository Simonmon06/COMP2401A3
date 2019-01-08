#define MAX_STR  32

#define C_OK   0
#define C_NOK -1

typedef struct {
  char title[MAX_STR];
  char author[MAX_STR];
  int  year;
} BookType;

typedef struct Node{
  BookType *data;
  struct Node *next;
} NodeType;

typedef struct {
  NodeType *head;
  NodeType *tail;
} ListType;


int initBook(BookType **book);
void initList(ListType *list);
void addByTitle(ListType *list, BookType *newBook);
void addByYear(ListType *list, BookType *newBook);
void copyList(ListType *src, ListType *dest);
void copyByYear(ListType *src, ListType *dest);
void delAuthor(ListType *list, char *name);
void printList(ListType *list);
void cleanupList(ListType *list);
void cleanupData(ListType* list);
