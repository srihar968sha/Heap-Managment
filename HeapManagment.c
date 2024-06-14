#include<stdio.h>
#include<stdlib.h>
#define h_size 2048

char HeapMemory[h_size];//heap memory

typedef struct metadata_tag
    {
    int size;
    int free;/* used to know if a memory is free or allocated 1 if free 0 if allocated*/
    struct metadata_tag * next;
} metadata;


metadata *hptr = (void *) HeapMemory;//pointer to heap memory


//initialising the metadata of the heap pointer
void initialize( metadata *hptr)
 {
    hptr->size=h_size-sizeof(metadata);
    hptr->free=1;
    hptr->next=NULL;
}



void* Allocate(int userbytes){
    metadata*current;
    void * result;
    current=hptr;

    while(((current->size<userbytes)|| (current->free==0 ))&& current !=NULL){
      
        current=current->next;

    }
    if(current->size==userbytes){
        current->free=0;
        result=(void *)current + sizeof(metadata);
    }
    else if(current->size> userbytes){

        if(current->size > userbytes +sizeof(metadata)){
        
        metadata *new;
        new=( void *)((void *)(current) + sizeof(metadata) + userbytes);
       
        new->free=1;
        new->size=current->size-userbytes-sizeof(metadata);
       
        current->free=0;       
        current->size=userbytes;
        current->next=new;
        result=(void *)current +sizeof(metadata);
    }
    }
    else if(current==NULL){
        result=NULL;
        printf("Memory shortage can't allocate memory:\n");
    }

    return  result;
}

void merge(){
    metadata*current,*Next;
    int flag;
    current=hptr;
    Next=current->next;
    flag=0;

    while(flag==0 && Next!=NULL){

        if(current->free==1&&Next->free==1){

            if(Next->next!=NULL && Next->next->free==1){

                current->size=current->size+2*sizeof(metadata)+Next->size+(Next->next->size);
                current->next=Next->next->next;
            }
            else{
                current->size=current->size + sizeof(metadata) + Next->size;
                current->next=Next->next;
            }
            flag=1;
        }
        else{
            current=Next;
            Next=Next->next;
        }
    }

}
void freee(void * ptr){
    if(ptr>=(void*) hptr &&ptr <= ((void*)hptr+ h_size)){
    metadata *nptr = ptr - sizeof(metadata);
    nptr->free=1;
    merge();
    printf("memory is now freed\n");
    }
    else{
        printf("Free called on unallocated memory\n ");
    }
}

void displayheap()
{
    
	metadata *ptr;
    ptr = hptr;
	while(ptr != NULL)
	{
        if(ptr->free == 0)
        {
            printf("%16s\n", "ALLOCATED");
            printf("----------------------\n");
            printf("%10s %7d\n","Size: ",ptr->size);
            printf("----------------------\n");	
        }
        else
        {
            printf("%12s\n", "FREE");
            printf("----------------------\n");
            printf("%10s %7d\n","Size: ",ptr->size);
            printf("----------------------\n");
        }
        ptr = ptr->next;
	}
}
int main(){
   
 initialize(hptr);
 displayheap();
printf("_\n");
 void *z=Allocate(1);
 displayheap();
printf("_\n");

 void *y=Allocate(100);
 displayheap();
printf("_\n");

 freee(z);
 displayheap();
printf("_\n");

 freee(y);
 displayheap();
 return 0;
}