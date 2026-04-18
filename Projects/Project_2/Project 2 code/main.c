#include <stdio.h>                // Name : khaled Hammad -- ID : 1220857 -- section : 3 -- Doctor : Radi Jarrar
#include <stdlib.h>
#include <string.h>

typedef struct node* Queue;
typedef struct node1* Stack;
struct node {//Queue
    char word[50];
    Queue Next;
    Queue Last;
};
struct node1 {//Stack
    char  sWord[50];
    int operation;// 1 == insert | 0 == remove
    int index;
    int type;//complete string == 1 || incomplete string == 0
    Stack Next;
};

Stack creatStack();
void makeEmpty(Stack s);
int isEmpty(Stack s);
void push(char word[50],int op,int index,int type,Stack s);
void Pop(Stack s);
Stack Top(Stack s);
void printStack(Stack s);
void DisposeStack(Stack s);

Queue CreateQueue();
void makeQueueEmpty(Queue Q);
int isEmptyQueue(Queue Q);
int isLast(Queue p,Queue Q);//extra
Queue Find(char wor[],Queue Q);//extra
Queue FindPrevious(char wor[],Queue Q);//extra
char* Front(Queue Q);
void DisposeQueue(Queue Q);

void LoadInputFile(int x,char Text[]);
void printTheLoaded(int x,char TextFile[]);
void insertSentence(Stack undo,char Text[],int x);
void removeString(Stack undo,char Text[]);
void UndoOperation(Stack undo,Stack redo,char Text[]);
void RedoOperation(Stack undo,Stack redo,char Text[]);
void PrintUndoAndRedo(Stack undo,Stack redo);
void SaveOutputToFile(char Text[]);

int main()
{
    Stack Undo = creatStack();
    Stack Redo = creatStack();
    char Text[700],TextFile[200];//Text file : the text that load from file
    int choose=0,x=0;
    while(choose !=9){
        printf("****************************************************************************************\n");
        printf("Enter operation\n\n");
        printf("1. Load the input file which contains the initial text.\n");
        printf("2. Print the loaded text. \n");
        printf("3. Insert strings to the text. \n");
        printf("4. Remove strings from the text. \n");
        printf("5. Perform Undo operation. \n");
        printf("6. Perform Redo operation.\n");
        printf("7. Print the Undo Stack and the Redo stack. \n");
        printf("8. Save the updated text to the output file.\n");
        printf("9. Exit\n");
        printf("****************************************************************************************\n");
        scanf("%d",&choose);
        switch(choose){
            case 1: LoadInputFile(x,Text);
                    strcpy(TextFile,Text);
                    x=1;
                    break;
            case 2: printTheLoaded(x,TextFile);
                    //printf("%s\n",Text);
                    break;
            case 3: insertSentence(Undo,Text,x);
                    break;
            case 4: removeString(Undo,Text);
                    break;
            case 5: UndoOperation(Undo,Redo,Text);
                    break;
            case 6: RedoOperation(Undo,Redo,Text);
                    break;
            case 7: PrintUndoAndRedo(Undo,Redo);
                    break;
            case 8: SaveOutputToFile(Text);
                    break;
            case 9:
                    break;
            default : printf("There is no operation with this number please try again\n");
                    getchar();
                    break;
        }

    }
    return 0;
}
void LoadInputFile(int x,char Text[700]){
    if(x == 1){
        printf("You loaded the information\n");
        return ;
    }
    FILE *input;
    input = fopen("input.txt","r");
    fgets(Text,200,input);

}
void printTheLoaded(int x,char TextFile[200]){
    if(x == 0){
        printf("please load the information first\n");
        return ;
    }
    printf("%s\n",TextFile);
}
void insertSentence(Stack undo,char Text[700],int x){//Insert the sentence to queue then from queue insert to Text and push to undo
    if(x == 0){
        printf("please Load the input file before insert string to it\n");
        return ;
    }
    char sentence[150];
    Queue q = CreateQueue();
    printf("Enter the string that you want to insert it to text\n");
    getchar();
    gets(sentence);
    char *token = strtok(sentence," ");
    while(token != NULL){
        Enqueue(token,q);
        token = strtok(NULL," ");
    }
    int choose = 0;

    do{
    printf("___________________________________\n");
    printf("please Enter how you want to insert the string :\n\n");
    printf("1-Insert at the Last of Text\n");
    printf("2-Insert after name of string\n");
    printf("___________________________________\n");

    scanf("%d",&choose);
        switch(choose){
            case 1 : { //Case of insert at last same as project
                        if(Text[strlen(Text)-1] != '.')//if we want to insert last after do not put space
                            strcat(Text," ");
                        while(!isEmptyQueue(q)){
                            strcat(Text,Front(q));
                            if(q->Next->Next != NULL){
                                strcat(Text," ");
                            }
                            push(Front(q),1,-1,1,undo);//1 (Name of word,1 mean the operation is insert,index,(comlete string1/incomplete 0),stack)
                            Dequeue(q);
                        }
                            free(q);//free head
                            break ;
            }
            case 2 : { // extra - case of insert string at any place after word in text
                        char name[10],temp[200];
                       printf("Enter the Name that you want to insert after\n");
                       getchar();
                       gets(name);
                       char *search = strstr(Text,name); // the strstr() is a function in string.Library that return all text after the word that we put in it
                       if(search == NULL){
                            printf("\nThis string is not exist,please try again\n");
                            choose = 0;
                            break ;
                       }
                       int index = (strlen(Text) - strlen(search))+strlen(name)+1; // to give the index to put word after it
                       while(!isEmptyQueue(q)){
                            if(Text[index-1] == '.'){//to insert after word with . without problem
                                strcpy(temp,Text + index-1);//this method copy all text after the index in temp
                                strcpy(Text +index-1 ," ");//this method to put space after the word
                                strcat(Text,Front(q));//this method concat the text with word
                                strcat(Text,temp);//this method concat the text after insert word with temp
                                /*this example explain how to use this method: char Text [50] = Welcome to Data.
                                    Text + 2 ==> lecome to Data.
                                    strcpy(Text,Text + 2); ==>lecome to Data.
                                    strcpy(Text +2 ,"khaled"); ==>wekhaled
                                */
                            }
                            else{//normal case
                                strcpy(temp,Text + index);
                                strcpy(Text + index,Front(q));
                                strcat(Text," ");
                                strcat(Text,temp);
                            }
                            push(Front(q),1,index,1,undo);
                            index = index + strlen(Front(q)) +1;
                            Dequeue(q);
                       }
                       free(q);//free head
                       break ;
            }
            default : printf("please enter number 1 or 2\n");
                    getchar();//to avoid problem of infinte loop when enter char
                    break;
        }

    }while(choose !=1 && choose != 2);
}
void removeString(Stack undo,char Text[200]){ // To remove strings or char from the text.
    if(Text[0] == '\0'){
        printf("It is empty,there is no text\n");
        return ;
    }
    char word[100],temp[200];
    strcpy(temp,Text);
    printf("Enter the String that you want to delete\n");
    getchar();
    gets(word);
    char *search = strstr(Text,word);
    if(search == NULL){
        printf("This String is not found , please try again\n");
        return ;
    }
    int indexCal = strlen(Text) - strlen(search);
    int len=0,x=0;

    char *token = strtok(temp," .");
    while(token != NULL){
        if(strcmp(token,word) == 0){
            x =1;//to see if we want to delete complete string or char from string 1 mean complete string 0 mean incomplete (char)
        }
        token = strtok(NULL," .");
    }
    if(x==1){//case of delete complete string
            if(Text[indexCal+strlen(word)] == '.' || Text[indexCal+strlen(word)] == '\0'){//to delete word without . then return . to previous string
                len = strlen(word);                     //to solve problem of delete last word
                strcpy(Text + indexCal-1,Text + indexCal + len);   //we do this to return the . to prev word same as project example
            }
            else{
                len = strlen(word)+1;//we put +1 to len to delete one space with it to return post string to prev string
                strcpy(Text + indexCal,Text + indexCal + len);
            }
            //this method copy the text from the after of word to the index of word to delete word
    }
    else{ //case of delete char or many char but not complete string * we but it special case because in complete string we delete space with string but here we don't want to delete any thing extra
            len = strlen(word) ;
            strcpy(Text + indexCal, Text + indexCal + len);
    }
    push(word,0,indexCal,x,undo);//(word that we delete,type of operation(0 == delete),index of word,type of string,stack)
}
void UndoOperation(Stack undo,Stack redo,char Text[]){
    if(isEmpty(undo)){
        printf("There is no Undo operation yet\n");
        return ;
    }
    Stack top = Top(undo);
    char temp[200];
    int x=0;
   //Case 1:if we want to insert complete word to senrence
        if(top->operation == 0){//type of operation is remove so we want to insert
             if(Text[top->index -1] == '.'){//to insert after . without problem
                strcpy(temp,Text + top->index-1);
                strcpy(Text +top->index-1 ," ");
                strcat(Text,top->sWord);
                strcat(Text,temp);
            }
           else{ char temp[200];
                strcpy(temp,Text+top->index);
                strcpy(Text + top->index,top->sWord);
                if(top->type == 1){//complete word
                    if(temp[top->index] != '.'){
                        strcat(Text," ");
                    }
                }
                strcat(Text,temp);
           }
            push(top->sWord,top->operation,top->index,top->type,redo);
        }
        if(top->operation == 1){//type of operation is insert so we want to remove
             int size = strlen(top->sWord),index =0;
            if(top->index == -1){//to remove string that we insert last without any problem
                index = (strlen(Text) - size);
                push(top->sWord,top->operation,-1,top->type,redo);
                if(Text[index - 1] == '.'){
                    strcpy(Text + index , "");
                }
                else{
                    strcpy(Text + index -1 ,"");
                }
            }
            else {
                 index = top->index;
                 push(top->sWord,top->operation,index,top->type,redo);
                 strcpy(Text + index-1 ,Text+ index + size );
            }
        }
    Pop(undo);
}
void RedoOperation(Stack undo,Stack redo,char Text[]){
    if(isEmpty(redo)){
        printf("There is no Redo operation yet\n");
        return ;
    }
    Stack top = Top(redo);
    char temp[200];
    if(top->operation == 1){//type of operation is remove so we want to insert
        if(top->index == -1){//to insert the string that we insert last without any problem
            if(Text[strlen(Text)-1] != '.')//if we want to insert last after do not put space
                strcat(Text," ");
            strcat(Text,top->sWord);
            push(top->sWord,1,-1,1,undo);//1 (Name of word,1 mean the operation is insert,index,(comlete string-1/incomplete 0),stack)
            Pop(redo);
            return ;
        }
             if(Text[top->index -1] == '.'){//to insert the word before . without problem
                strcpy(temp,Text + top->index-1);
                strcpy(Text +top->index-1 ," ");
                strcat(Text,top->sWord);
                strcat(Text,temp);
            }
            else{
                if(strlen(Text) < top->index){//if we remove word from last of string then we want to add it,we do this to avoid problem of indexing in null that will affect the strcoy()
                    strcat(Text," ");
                    strcat(Text,top->sWord);
                }
                 else{   char temp[200];
                    strcpy(temp,Text+top->index);
                    strcpy(Text + top->index,top->sWord);
                    if(top->type == 1){//complete word
                        if(temp[top->index] != '.'){
                            strcat(Text," ");
                        }
                    }
                    strcat(Text,temp);
                }
            }
    }
    int len =0;
    if(top->operation == 0){//type of operation is insert so we want to remove
        if(top->type == 1){
            if(Text[top->index+strlen(top->sWord)] == '.' || Text[top->index+strlen(top->sWord)] == '\0'){
                len = strlen(top->sWord);                   //to solve problem of delete last word
                strcpy(Text + top->index-1,Text + top->index + len);
            }
            else{
                len = strlen(top->sWord)+1;
                strcpy(Text + top->index,Text + top->index + len);
            }

        }
        else{
                len = strlen(top->sWord);
                strcpy(Text + top->index, Text + top->index + len);
        }
    }
    push(top->sWord,top->operation,top->index,top->type,undo);
    Pop(redo);
}
void PrintUndoAndRedo(Stack undo,Stack redo){
    if(isEmpty(undo)){
        printf("The undo stack is empty,there is no any undo operation Yet\n");
    }
    else{
        printf("        Undo Stack\n____________________________\n");
        printStack(undo);
    }
    printf("**********************************\n");
    if(isEmpty(redo)){
        printf("The redo stack is empty,there is no any undo operation Yet\n");
    }
    else{
        printf("\n       Redo Stack\n___________________________\n");
        printStack(redo);
    }
}
void SaveOutputToFile(char Text[]){
    if(Text[0] == '\0'){
        printf("There is no any String in text, please enter string before load it to file\n");
        return ;
    }
    FILE *output;
    output = fopen("output.txt","w");

    fprintf(output,"%s\n",Text);
    fclose(output);
}
//////////////////////////////////////////Library of stack/////////////////////////////////////////////////////////////
Stack creatStack(){
    Stack p;
    p = (Stack)malloc(sizeof(struct node));
    if (p == NULL)
        printf("out of space");
    p->Next = NULL;
    p->index = -1;
    return p;
}
void makeEmpty(Stack s){
    if (s == NULL)
        printf("out of space");
    else{
        while( !isEmpty(s)){
            Pop(s);
        }
    }
}
int isEmpty(Stack s){
    return s->Next == NULL;
}
void push(char word[50],int op,int index,int type,Stack s){//insert first
    Stack temp;
    temp = (Stack)malloc(sizeof(struct node));
    if(temp == NULL){
        printf("out of space");
        return ;
    }
    temp->Next = s->Next;
    s->Next = temp;
    strcpy(temp->sWord,word);
    temp->operation = op;
    temp->index = index;
    temp->type = type;
}
void Pop(Stack s){
    Stack temp;
    if(isEmpty(s)){
        printf("Empty Stack");
        return ;
    }
    else{
        temp = s->Next;
        s->Next = temp->Next;
        free(temp);
    }
}
Stack Top(Stack s){
    if(isEmpty(s)){
        printf("Empty Stack");
        return ;
    }
    else
        return s->Next;
}
void printStack(Stack s){//here we can doing it by linked list but because it stack we cant see any thing else the top so we print the top then transport to another stack then pop the s to see next top ...
    Stack temp = creatStack(),top;
    if( isEmpty(s)){
        return ;
    }
    else{
        while(!isEmpty(s)){
            top = Top(s);
            char operation[10];
            if(top->operation == 1)
                strcpy(operation,"Insert");
            else
                strcpy(operation,"Remove");
            printf("%s      %s      %d\n",top->sWord,operation,top->index);
            push(top->sWord,top->operation,top->index,top->type,temp);
            Pop(s);
        }
    }
    Stack t;
    while(!isEmpty(temp)){
        t = Top(temp);
        push(t->sWord,t->operation,t->index,t->type,s);
        Pop(temp);
    }
    free(temp);//to free head

}
void DisposeStack(Stack s){
    makeEmpty(s);
    free(s);
}
/*****************************************End of Stack Library**********************************************************/
////////////////////////////////////////Queue Library///////////////////////////////////////////////////////////////////////

Queue CreateQueue(){
    Queue p;
    p = (Queue)malloc(sizeof(struct node));
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
Queue Find(char wor[20],Queue Q){
    Queue p;
    p = Q->Next;

    while(p != NULL &&  strcmp(wor,p->word) != 0){
        p = p->Next;
    }
    return p;
}
Queue FindPrevious(char wor[20],Queue Q){
    Queue p;
    p = Q;
    while(p->Next != NULL && strcmp(wor,p->Next->word) != 0){
        p = p->Next;
    }
    return p;

}
void Enqueue(char word[50],Queue Q){//insert Last
    Queue temp;
    temp = (Queue)malloc(sizeof(struct node));
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
void DisposeQueue(Queue Q){
     if( Q != NULL ){
        makeEmpty(Q);
        free(Q);
    }

}
/****************************************************End of queue Library**********************************************************/
