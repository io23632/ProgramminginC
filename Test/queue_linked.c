#include "../ADTs/General/general.h"
#include "../ADTs/Queue/queue.h"

#define ELEMSIZE 20

typedef struct dataframe{
    queuetype i;
    struct dataframe* next;
}dataframe;

struct queue {
   /* Underlying array */
   dataframe* front;
   dataframe* end;
   int size;
};


queue* queue_init(void)
{
   queue* q = (queue*) ncalloc(1, sizeof(queue));
   return q;
}

void queue_enqueue(queue* q, queuetype d)
{
     dataframe* f;
   if(q==NULL){
      return;
   }

/*Assign some memory to the f node*/

f = (dataframe*)calloc(1, sizeof(dataframe));
f->i = d;



/* We are going to store two pointers, one pointing to the fron to the list and one to the back of the list */
/*Adding data to the front*/
if (q->front == NULL){
    q->front = f; 
    q->end = f;
    q->size++;
}

/*adding data not from the front of the list*/
q->end->next = f;
q->end = f;
q->size++;

  
}

bool queue_dequeue(queue* q, queuetype* d)
{
   dataframe* f;
   if((q==NULL) || (q->front==NULL) || (q->end==NULL)){
      return false;
   }
   f = q->front->next;
   *d = q->front->i;
   free(q->front);
   q->front = f;
   q->size = q->size - 1;
   return true;
}


bool queue_free(queue* q)
{
   if(q){
      dataframe* tmp;
      dataframe* p = q->front;
      while(p!=NULL){
         tmp = p->next;
         free(p);
         p = tmp;
      }
      free(q);
   }
   return true;
}

void queue_tostring(queue* q, char* str)
{
   dataframe *p;
   char tmp[ELEMSIZE];
   str[0] = '\0';
   if((q==NULL) || (q->front == NULL)){
      return;
   }
   p = q->front;
   while(p){
      sprintf(tmp, "%d", p->i); 
      strcat(str, tmp);
      strcat(str, "|");
      p = p->next;
   }
   str[strlen(str)-1] = '\0';
}

int queue_size(queue* q)
{
   if((q==NULL) || (q->front==NULL)){

      return 0;
   }
   return q->size;
}
