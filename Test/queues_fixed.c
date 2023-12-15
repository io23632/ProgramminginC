#include "../ADTs/General/general.h"
#include "../ADTs/Queue/queue.h"
#include <time.h>

#define ELEMSIZE 20

typedef int queuetype;

typedef struct queue queue;

#define BOUNDED 5000
#define DOTFILE 5000

struct queue{
    queuetype a[BOUNDED];
    int front;
    int end;
};

int main(void)
{
   queue* q;
   queuetype d;
   char str[1000];

   srand(time(NULL));
   q = queue_init();
   while(queue_size(q) < 10){
      /* Slow output */
      if(rand()%10 < 1){
         queue_dequeue(q, &d);
      }
      /* Faster input */
      if(rand()%10 < 3){
         d = rand()%1000;
         queue_enqueue(q, d);
      }
      queue_tostring(q, str);
      printf("Queue : %s\n", str);
   }
         
   queue_free(q);
   return 0;
}

queue* queue_init(void)
{
    // allocate memory to the queue struct:

    queue* q = (queue*)calloc(1, sizeof(queue));

    return q;
}

void queue_enqueue(queue* q, queuetype v)
{
    if(q){

        q->a[q->end] = v;
        
        q->end = (q->end + 1) % BOUNDED;

        if (q->front == q->end) {
            fprintf(stderr, "Queue is too large");
            return;
        }
    }
}

bool queue_dequeue(queue* q, queuetype* d)
{
    if (q == NULL || q->front ==  q->end){
        return false;
    }

    *d = q->a[q->front];
    q->front = (q->front + 1) % BOUNDED;
    return true;
}

void queue_tostring(queue* q, char* str)
{
    char temp[ELEMSIZE];
    str[0] = '\0';


    for (int i = q->front; i != q->end; i++)
    {
        sprintf(temp, "%d", q->a[i]);
        strcat(str, temp);
        strcat(str, "|");
    }
    str[strlen(str) - 1] = '\0';


}

int queue_size(queue* q)
{
   if(q==NULL){
      return 0;
   }
   if(q->end >= q->front){
      return q->end-q->front;
   }
   return q->end + BOUNDED - q->front;
}

bool queue_free(queue* q)
{
   free(q);
   return true;
}