#include <stdio.h>          //Name:Khaled Hammad || ID:1220857 ||sec:3 ||Doctor : Radi Jarrar
#include <stdlib.h>
#include <string.h>
int size =1;//for heap
typedef struct node* vertixT;
typedef struct node2* edgeT;
typedef struct node3* Queue;
typedef struct node4* vertix;
typedef struct node5* edge;
struct node{ //vertix of topolocial
    char word[20];
    int indegree;
    vertixT nextvertix;
    edgeT nextedge;
};
struct node2{//edge of topolocial
    char nameofvertix[20];
    vertixT nextV;
    edgeT nextE;
};
struct node3 {
    char word[20];
    Queue Next;
    Queue Last;
};
struct node4{// vertix of Dijkstra
    char word[20];
    int cost;
    int inHeap;// 1 mean that the vertix is go to heap || 0 otherwise
    vertix nextvertix;
    vertix prevertix;
    edge nextedge;
};
struct node5{//edge of Dijkstra
    char nameofvertix[20];
    int weight;
    vertix nextV;
    edge nextE;
};

vertix creatGraphOfDijkstra();//To creat graph of vertix for dijkstra
void creatVertixOfDijkstra(vertix Head,char word[]);//To creat a vertix for Dijksta
vertix Findvertix(char word[],vertix L);//to find the vertix from the graph
void addEdgeOfDijkstra(vertix L,char word1 [],char word2 [],int weight);//to add edge between 2 vertix in dijkstra
void printListOfDijkstra(vertix L);//extra
int Dijkstra(vertix graph,char source[],char dest[]);//to find the short distance of path between 2 building
void DijkstraWithPath(vertix graph,char source[],char dest[]);//to find the short path with distance between 2 buliding
void enqueueInHeap(vertix *heap,vertix vr);//to insert vertix in heap
void swap(vertix *a,int i1,int i2);//to put the vertix in correct place in heap
vertix dequeueFromHeap(vertix *a);//to delete vertix from the heap
void deleteMinInHeap(vertix *a,int index);//to put the vertix in the place where the min vertix was deleted and swap other element
void loadInputFileOfDijkstra(vertix L);//to load the input from the file

Queue CreateQueue();//to creat queue
void makeQueueEmpty(Queue Q);//extra
int isEmptyQueue(Queue Q);//extra
void Enqueue(char word[50],Queue Q);//to insert the name of cource in queue to print it
void Dequeue(Queue Q);//to name of cource from queue if we need
char* Front(Queue Q);//to see the first element in queue
void printQueue(Queue s);//to print the element in queue

vertixT creatGraphOfTopological();//to creat graph of vertix for topological
void creatVertixOFTopological(vertixT Head,char word[]);//to creat vertix for topological
vertixT FindvertixOfTopli(char word[],vertixT L);//to find  vertix from graph
vertixT FindperviousVertix(vertixT temp,vertixT L);//to find previous vertix of vertix
void addEdgeInTopoloical(vertixT L,char word1 [],char word2 []);//to add edge between 2 vertix in graph
void printListOFTopological(vertixT L);//extra
int SizeofGraph(vertixT graph);//to count the number of vertix in graph
void deleteVertix(vertixT H,vertixT temp);//to delete vertix from graph
void topolgiclay(vertixT head,Queue q);//to do the topolgical in course
void loadInputFileOFTopological(vertixT graph);//to load the input from file

void shortDistanceBetween2Buliding_2(vertix graphD);//to print the short distance between two building
void shortDistanceWithPathBetween2Buliding_3(vertix graphT);//to print the short distance with the path between 2 biulding

int main() {
    vertix graphD = creatGraphOfDijkstra();//the graph of Dijkstra
    vertixT graphT = creatGraphOfTopological();//the graph of Topological
    Queue q = CreateQueue();//to put the name of course in it to print it in choice 5
    int x=0,y=0;//we use them as flag

    int choose=0;
    while(choose !=6){
        printf("****************************************************************************************\n");
        printf("Enter opeartion\n\n");
        printf("1. Load the two files.\n");
        printf("2. Calculate the shortest distance between two buildings.\n");
        printf("3. Print the shortest route between two buildings and the total distance.\n");
        printf("4. Sort the courses using the topological sort.\n");
        printf("5. Print the sorted courses.\n");
        printf("6. Exit the application. \n");
        printf("****************************************************************************************\n");

        scanf("%d",&choose);

        switch(choose){
            case 1:if(x == 0){
                        loadInputFileOfDijkstra(graphD);
                        loadInputFileOFTopological(graphT);
                        x=1;
                    }
                    else
                        printf("you loaded the information\n");
                    break;
            case 2: if(x == 0){
                        printf("There is no Data to sorted please insert data first\n");
                        break ;
                    }
                    shortDistanceBetween2Buliding_2(graphD);
                    break;
            case 3:if(x == 0){
                        printf("There is no Data to sorted please insert data first\n");
                        break ;
                    }
                    shortDistanceWithPathBetween2Buliding_3(graphD);
                    break;
            case 4: if(y == 1){
                        printf("You already sorted the Data\n");
                        break ;
                    }
                    if(graphT->nextvertix == NULL){
                        printf("There is no Data to sorted please insert data first\n");
                        break;
                    }
                    y = 1;
                    topolgiclay(graphT,q);
                    break;
            case 5: if(y == 0){
                        printf("please sort the cource first\n");
                        break ;
                    }
                    printQueue(q);
                    break;
            case 6: //Exit
                    break;
            default : printf("There is no operation with this number please try again\n");
                    getchar();//to avoid the problem of infint loop when we insert word
                    break;
        }

    }
    return 0;
}
void shortDistanceBetween2Buliding_2(vertix graph){
    char B1[25],B2[25];
    printf("Enter the name of source building\n");
    getchar();
    gets(B1);
    printf("Enter the name of destination building\n");
    gets(B2);
    int x = Dijkstra(graph,B1,B2);
    if(x == -1){
            return;
    }
    printf("The short distance between (%s) and (%s) is %d\n",B1,B2,x);
}
void shortDistanceWithPathBetween2Buliding_3(vertix graph){
    char B1[25],B2[25];
    printf("Enter the name of source building\n");
    getchar();
    gets(B1);
    printf("Enter the name of destination building\n");
    gets(B2);
    DijkstraWithPath(graph,B1,B2);
}
//************************************Library of Dijkstra*************************************************
vertix creatGraphOfDijkstra(){
    vertix l = (vertix)malloc(sizeof(struct node4));
    l->nextedge = NULL;
    l->nextvertix = NULL;
    l->cost =0;
    strcpy(l->word,"head");
    return l;
}
void creatVertixOfDijkstra(vertix Head,char word[]){
    vertix v = (vertix)malloc(sizeof(struct node4));
    strcpy(v->word,word);
    v->cost = -1;
    v->inHeap = 0;
    v->nextedge = NULL;
    v->nextvertix = Head->nextvertix;
    Head->nextvertix = v;
}
vertix Findvertix(char word[],vertix L){
    vertix p;
    p = L;
    while(p != NULL && strcmp(p->word,word) != 0){
        p = p->nextvertix;
    }
    return p;
}
void addEdgeOfDijkstra(vertix L,char word1 [],char word2 [],int weight){
    vertix v1 = Findvertix(word1,L);
    vertix v2 = Findvertix(word2,L);
    if(v1 == NULL){
        creatVertixOfDijkstra(L,word1);
        v1 = Findvertix(word1,L);
    }
    if(v2 == NULL){
        creatVertixOfDijkstra(L,word2);
        v2 = Findvertix(word2,L);
    }
    edge e = (edge)malloc(sizeof(struct node5));
    strcpy(e->nameofvertix,v2->word);
    e->weight = weight;
    e->nextE = v1->nextedge;
    v1->nextedge = e;
    e->nextV = v2;
    //beacuse it is undirected graph
    edge e2 = (edge)malloc(sizeof(struct node5));
    strcpy(e2->nameofvertix,v1->word);
    e2->weight = weight;
    e2->nextE = v2->nextedge;
    v2->nextedge = e2;
    e2->nextV = v1;
}
void printListOfDijkstra(vertix L){//extra
    vertix p;
    p = L->nextvertix;
    while(p!= NULL){
        printf("\nvertix [%s] || his edge : ",p->word);
        edge o = p->nextedge;
        while(o != NULL){
            printf("[%s] wieght = %d,",o->nameofvertix,o->weight);
            o= o->nextE;
        }
        p = p->nextvertix;
    }
}
int Dijkstra(vertix graph,char source[],char dest[]){//return the short path between 2 building
    vertix *heap = (vertix)malloc(sizeof(vertix) * 100);
    for(int i=0 ; i<100 ; i++){//creat heap
        heap[i] = NULL;
    }
    vertix v = Findvertix(source,graph);
    vertix v2 = Findvertix(dest,graph);
    if(v == NULL){
        printf("There is no building with this name (%s) please try again\n",source);
        return -1;
    }
    if(v2 == NULL){
        printf("There is no building with this name (%s) please try again\n",dest);
        return -1;
    }
    v->cost =0;
    v->inHeap =1;
    enqueueInHeap(heap,v);
    while(heap[1] != NULL){
        vertix vr = dequeueFromHeap(heap);
        edge e = vr->nextedge;
        while(e != NULL){
            if(e->nextV->cost == -1 || e->nextV->cost > vr->cost+e->weight){
                e->nextV->cost = vr->cost+e->weight;
            }
            if(e->nextV->inHeap == 0){
                enqueueInHeap(heap,e->nextV);
                e->nextV->inHeap = 1;
            }
            e = e->nextE;
        }
    }
    vertix destination = Findvertix(dest,graph);
    int distance = destination->cost;
    vertix p = graph->nextvertix;
    while(p != NULL){//to return the value of vertix to original value
        p->cost =-1;
        p->inHeap = 0;
        p = p->nextvertix;
    }
    free(heap);
    return distance;
}
void DijkstraWithPath(vertix graph,char source[],char dest[]){//return the short path between 2 building with path
    vertix *heap = (vertix)malloc(sizeof(vertix) * 100);//same as above
    for(int i=0 ; i<100 ; i++){
        heap[i] = NULL;
    }
    vertix v = Findvertix(source,graph);
    vertix v2 = Findvertix(dest,graph);
    if(v == NULL){
        printf("There is no building with this name (%s) please try again\n",source);
        return ;
    }
    if(v2 == NULL){
        printf("There is no building with this name (%s) please try again\n",dest);
        return ;
    }
    v->prevertix = NULL;
    v->cost =0;
    v->inHeap =1;
    enqueueInHeap(heap,v);
    while(heap[1] != NULL){
        vertix vr = dequeueFromHeap(heap);
        edge e = vr->nextedge;
        while(e != NULL){
            if(e->nextV->cost == -1 || e->nextV->cost > vr->cost+e->weight){
                e->nextV->prevertix = vr;//to know the path
                e->nextV->cost = vr->cost+e->weight;
            }
            if(e->nextV->inHeap == 0){
                enqueueInHeap(heap,e->nextV);
                e->nextV->inHeap = 1;
            }
            e = e->nextE;
        }
    }
    vertix destination = Findvertix(dest,graph);
    vertix temp = creatGraphOfDijkstra();//to order the path
    vertix p = destination;
    while(p != NULL){
        creatVertixOfDijkstra(temp,p->word);
        p = p->prevertix;
    }
    vertix k = temp->nextvertix;
    printf("The short path between (%s) and (%s) is %d\nThe path :",source,dest,destination->cost);
    while(k != NULL){
        printf("(%s)",k->word);
        if(k->nextvertix != NULL)
            printf("-->");
        k = k->nextvertix;
    }
    printf("\n");
    vertix g = graph->nextvertix;
    while(g != NULL){//to return the value of vertix to orignal
        g->cost =-1;
        g->inHeap = 0;
        g->prevertix = NULL;
        g = g->nextvertix;
    }
    free(heap);
}
void loadInputFileOfDijkstra(vertix L){//to load the input
    FILE *input;
    char f[200],building1[50],building2[50],weight[50];
    input = fopen("input_buildings.txt","r");

    while(fgets(f,200,input) != NULL){
        char *token = strtok(f,"#");
        strcpy(building1,token);
        token = strtok(NULL,"#");
        strcpy(building2,token);
        token = strtok(NULL,"#");
        strcpy(weight,token);
        addEdgeOfDijkstra(L,building1,building2,atoi(weight));//atoi convert from string to int
    }
    fclose(input);
}
//******************************************************Library of Heap**************************************
void enqueueInHeap(vertix *heap,vertix vr){//insert
    heap[size] = vr;
    if(size > 1 && heap[(int)size/2]->cost > vr->cost){//if the parent is bigger than the parent do the swap
        swap(heap,(int)size/2,size);
    }
    size++;
}
void swap(vertix *a,int i1,int i2){
    vertix temp =a[i2];
    a[i2] = a[i1];
    a[i1] = temp;
    if(i2 > 4){//if the parent is bigger than the parent do the swap again
        if(a[(int)i1/2]->cost > a[i1]->cost){
            swap(a,(int)i1/2,i1);
        }
    }
}
vertix dequeueFromHeap(vertix *a){//to return the a[1] which it the smallest value in heap
    int index =0;
    vertix v= a[1];
    if(a[2] == NULL && a[3] == NULL){
        a[1] = NULL;
    }
    else if(a[2] == NULL && a[3] != NULL){//this case is extra because it is imbosible to add in index 3 while index 2 is empty
        a[1] = a[3];
        a[3] = NULL;
    }
    else if(a[2] != NULL && a[3] == NULL){
        a[1] = a[2];
        a[2] = NULL;
    }
    else{
        if(a[2]->cost < a[3]->cost)
            index = 2;
        else
            index = 3;
        a[1] = a[index];
        deleteMinInHeap(a,index);//to swap the child to parent place
    }
    size--;
    return v;
}
void deleteMinInHeap(vertix *a,int index){
    if(a[(2*index)] == NULL && a[(2*index)+1] ==NULL ){
        a[index] = NULL;
        if(a[index+1] != NULL){
            for(int i = index ; i<100 ; i++){//do shift if the place is empty but after is not empty
                a[i] = a[i+1];
            }
        }
        return ;
    }
    else if(a[(2*index)] == NULL && a[(2*index)+1] !=NULL){
        a[index] = a[2*index+1];
        a[(2*index)+1] = NULL;
    }
    else if(a[(2*index)] != NULL && a[(2*index)+1] ==NULL){
        a[index] = a[(2*index)];
        a[(2*index)] = NULL;
    }
    else if(a[(2*index)] != NULL && a[(2*index)+1] !=NULL){
        int ind =0;
        if(a[(2*index)]->cost < a[(2*index)+1]->cost)
            ind = 2*index;
        else
            ind = (2*index)+1;
        a[index] = a[ind];
        deleteMinInHeap(a,ind);//swap again
    }
}
///////////////////////////////Topolgiclay library//////////////////////////////////////////////////////////
vertixT creatGraphOfTopological(){
    vertixT l = (vertixT)malloc(sizeof(struct node));
    l->nextedge = NULL;
    l->nextvertix = NULL;
    l->indegree = -1;//value of indegree in head //extra
    return l;
}
void creatVertixOFTopological(vertixT Head,char word[]){
    vertixT v = (vertixT)malloc(sizeof(struct node));
    strcpy(v->word,word);
    v->indegree = 0;//inital value of indegree
    v->nextedge = NULL;
    v->nextvertix = Head->nextvertix;
    Head->nextvertix = v;
}
vertixT FindvertixOfTopli(char word[],vertixT L){
    vertixT p;
    p = L;
    while(p != NULL && strcmp(p->word,word) != 0){
        p = p->nextvertix;
    }
    return p;
}
vertixT FindperviousVertix(vertixT temp,vertixT L){
    vertixT p;
    p = L;
    while(p->nextvertix != NULL && p->nextvertix != temp){
        p = p->nextvertix;
    }
    return p;
}
void addEdgeInTopoloical(vertixT L,char word1 [],char word2 []){
    vertixT v1 = FindvertixOfTopli(word1,L);
    vertixT v2 = FindvertixOfTopli(word2,L);
    if(v1 == NULL){
        creatVertixOFTopological(L,word1);
        v1 = FindvertixOfTopli(word1,L);
    }
    if(v2 == NULL){
        creatVertixOFTopological(L,word2);
        v2 = FindvertixOfTopli(word2,L);
    }
    //undirected graph
    edgeT e = (edgeT)malloc(sizeof(struct node2));
    e->nextE = v1->nextedge;
    strcpy(e->nameofvertix,v2->word);
    v1->nextedge = e;
    v2->indegree++;
    e->nextV = v2;
}
int SizeofGraph(vertixT graph){
    int size =0;
    vertixT p = graph->nextvertix;
    while(p != NULL){
        size++;
        p = p->nextvertix;
    }
    return size;
}
void printListOFTopological(vertixT L){//extra
    vertixT p;
    p = L->nextvertix;
    while(p!= NULL){
        printf("\nvertix [%s] || indegree = %d || his edge : ",p->word,p->indegree);
        edgeT o = p->nextedge;
        while(o != NULL){
            printf("[%s],",o->nameofvertix);
            o= o->nextE;
        }
        p = p->nextvertix;
    }
}
void deleteVertix(vertixT H,vertixT temp){//to delete vertix from graph
    vertixT pre = FindperviousVertix(temp,H);
    edgeT e = temp->nextedge,temp2;
    temp->nextedge = NULL;
    while(e != NULL){
        e->nextV->indegree--;
        temp2 = e->nextE;
        free(e);
        e = temp2;
    }
    pre->nextvertix = temp->nextvertix;
    free(temp);
}
void topolgiclay(vertixT head,Queue q){
    vertixT temp = head->nextvertix;
    int size = SizeofGraph(head);//number of vertix in graph
    for(int i=0 ; i<size ; i++){//loop same as vertix number
        while(temp != NULL){
            if(temp->indegree == 0){
                Enqueue(temp->word,q);
                deleteVertix(head,temp);
                break;
            }
            temp =temp->nextvertix;
        }

        temp = head->nextvertix;
    }
}
void loadInputFileOFTopological(vertixT graph){
    FILE *input;
    char f[100],temp[25];
    input = fopen("input_courses.txt","r");
    while(fgets(f,100,input) != NULL){
        int len = strlen(f);
        strcpy(f+len-1,"");//we do this because when we get the line from the file it bring the \n with it and cause problem
        char *token = strtok(f,"#");
        if(token != '\0'){
            strcpy(temp,token);
            creatVertixOFTopological(graph,token);
            token = strtok(NULL,"#");
            while(token != '\0'){
                addEdgeInTopoloical(graph,token,temp);
                token = strtok(NULL,"#");
            }
        }
    }
    fclose(input);
}
////////////////////////////////////////Queue Library///////////////////////////////////////////////////////////////////////
Queue CreateQueue(){
    Queue p;
    p = (Queue)malloc(sizeof(struct node3));
    if (p == NULL)
        printf("out of space\n");
    p->Next = NULL;
    p->Last = p;
    return p;
}
void makeQueueEmpty(Queue Q){
    if (isEmptyQueue(Q)){
        printf("Empty\n");
        return ;
    }
    Queue temp = Q->Next;
        while( !isEmptyQueue(Q)){
            Dequeue(Q);
        }
}
int isEmptyQueue(Queue Q){
    return Q->Next == NULL;
}
int isLast(Queue p,Queue Q){
    return p->Next == NULL;
}
void Enqueue(char word[50],Queue Q){//insert Last
    Queue temp;
    temp = (Queue)malloc(sizeof(struct node3));
    if(temp == NULL){
        printf("out of space");
    }
    else{
    strcpy(temp->word,word);
    Q->Last->Next = temp;
    Q->Last = temp;
    temp->Next = NULL;
    }
}
void Dequeue(Queue Q){
    if(isEmptyQueue(Q)){
        printf("Empty Queue");
        return ;
    }
    Queue temp = Q->Next;
    Q->Next = temp->Next;
    free(temp);
}
char* Front(Queue Q){//peek
    if(isEmptyQueue(Q)){
        printf("Empty Queue");
        return ;
    }
    else
        return Q->Next->word;//return the first number
}
void printQueue(Queue s){
    if( isEmptyQueue(s)){
        printf("Empty Queue");
        return ;
    }
    else{
        while(s->Next != NULL){
            printf("%s\n",s->Next->word);
            s = s->Next;
        }
    }
}
/****************************************************End of queue Library**********************************************************/
