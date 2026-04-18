#include <stdlib.h>              //Name: Khaled Hammad ||ID = 1220857 || sec : 3 || Doctor : Radi Jarrar
#include <stdio.h>
#include <string.h>

typedef struct AVLnode *AVLNode;
typedef struct node Hashword;
struct AVLnode
{
    char word[25];
    AVLNode Left;
    AVLNode Right;
    int frequancy;
    int Height; //Balance information
};
struct node{
    int frequency;
    char word[25];
};
int sizeofTable = 1000 ;//inital value of Hash Table
int countNumHash =0;
/******************************************************/
//Library of AVL
AVLNode MakeEmpty(AVLNode T );
AVLNode Find( char word[25], AVLNode T );
AVLNode FindMin( AVLNode T );
AVLNode FindMax( AVLNode T );
int Height( AVLNode P );
int Max( int L, int R );
AVLNode SingleRotateWithLeft( AVLNode K2 );//rotate to right
AVLNode SingleRotateWithRight( AVLNode K1 );//rotate to lift
AVLNode DoubleRotateWithLeft( AVLNode K3 );//left right rotate
AVLNode DoubleRotateWithRight(AVLNode K1);//right left rotate
AVLNode Insert( char word[25], AVLNode T );
AVLNode Delete( char word[25], AVLNode T );
/************************************************************/
//Library of Hashing
Hashword* ReHash(Hashword *T);
int hash(char* key,Hashword Table[]);
Hashword* insertToHash(char word[],Hashword Table[]);
int FindFromHash(char* key,Hashword Table[]);
void DeleteFromHash(char* key,Hashword Table[]);
int IsprimeNumber(int x);
int MinPrime(int num);
int MaxPrime(int num);
void printHashTable(Hashword T[]);
/*************************************************************/

void LoadDataFromTheFile_1(char Text[],int x);
AVLNode CreateTheAVLtree_2(AVLNode T,char Text[]);
AVLNode InsertwordToTheAVLtree_3(AVLNode T);
AVLNode DeleteWordFromTheAVLtree_4(AVLNode T);
void PrintInOrder_5( AVLNode t);
void CreateTheHashTable_6(AVLNode tree,Hashword T[]);
Hashword* InsertWordtToTheHashTable_7(Hashword T[]);
void DeleteWordtToTheHashTable_8(Hashword T[]);
void SearchWordInTheHashTable_9(Hashword T[]);
void printStatics_10(AVLNode tree,Hashword T[],int z,int y);
AVLNode MaxFrequentInTree(AVLNode t,AVLNode max);
int MaxFreuentInHashTable(Hashword T[]);
void frequentInHashTree(AVLNode t,Hashword T[]);

int main()
{
    Hashword *T = (Hashword*)malloc(sizeof(Hashword) * sizeofTable);

    char Text[1000] = "";
    int choose=0,x=0,y=0,z=0;
    while(choose !=11){
        printf("****************************************************************************************\n");
        printf("Enter opeartion\n\n");
        printf("1. Load data from the file.\n");
        printf("2. Create the AVL tree.\n");
        printf("3. Insert a word to the AVL tree.\n");
        printf("4. Delete a word from the AVL tree.\n");
        printf("5. Print the words as sorted in the AVL tree.\n");
        printf("6. Create the Hash Table.\n");
        printf("7. Insert a word to the Hash table.\n");
        printf("8. Delete a word from the hash table.\n");
        printf("9. Search for a word in the hash table and print its frequency.\n");
        printf("10.Print words statistics.\n");
        printf("11.Exit the application.\n");
        printf("****************************************************************************************\n");

        scanf("%d",&choose);
        switch(choose){
            case 1: LoadDataFromTheFile_1(Text,x);
                    x=1;
                    break;

            case 2:if(x==0){//if we dont load data from file
                        printf("Please Load the data from file first\n");
                        break ;
                    }
                    AVLNode tree = MakeEmpty( NULL );
                    tree = CreateTheAVLtree_2(tree,Text);
                    z =1;
                    break;

            case 3:if(z == 0){//if we dont creat Avl
                        printf("please creat the Avl Tree first\n");
                        break;
                    }
                    tree = InsertwordToTheAVLtree_3(tree);
                    break;

            case 4:if(z == 0){//if we dont creat Avl
                        printf("please creat the Avl Tree first\n");
                        break;
                    } tree = DeleteWordFromTheAVLtree_4(tree);
                    break;

            case 5:if(z == 0){//if we dont creat Avl
                        printf("please creat the Avl Tree first\n");
                        break;
                    }
                    PrintInOrder_5(tree);
                    printf("\n");
                    break;

            case 6: if(z == 0){//if we dont creat Avl
                        printf("please creat the Avl Tree first\n");
                        break;
                    }
                    for(int i=0 ; i<sizeofTable ; i++){
                        T[i].frequency =0;
                        strcpy(T[i].word,"");
                    }
                    CreateTheHashTable_6(tree,T);
                    y=1;
                    break;

            case 7: if(y==0){//if we dont creat Hash Table
                        printf("please creat the hash table first\n");
                        break ;
                    }
                    T = InsertWordtToTheHashTable_7(T);
                    break;

            case 8: if(y==0){//if we dont creat Hash Table
                        printf("please creat the hash table first\n");
                        break ;
                    }
                    DeleteWordtToTheHashTable_8(T);
                    break;
            case 9: if(y==0){//if we dont creat Hash Table
                        printf("please creat the hash table first\n");
                        break ;
                    }
                    SearchWordInTheHashTable_9(T);
                    break;
            case 10: printStatics_10(tree,T,z,y);
                     break;
            case 11: // exit
                    break;
            default : printf("There is no operation with this number please try again\n");
                    getchar();
                    break;
        }

    }
    return 0;
}
void printHashTable(Hashword T[]){
    for(int i=0 ; i< sizeofTable ; i++){
        printf("T[%d] : %s == %d\n",i,T[i].word,T[i].frequency);
    }
}
void LoadDataFromTheFile_1(char Text[1000],int x){
    if(x == 1){
        printf("You loaded the information\n");
        return ;
    }
    char f[1000];
    FILE *input;
    input = fopen("input.txt","r");
    while(fgets(f,1000,input) != NULL){
        char *token = strtok(f," ");
        while(token != NULL){
            if(IsWord(token)){
                strcat(Text,token);
                strcat(Text," ");
          }
            token = strtok(NULL," ");
        }
    }
    fclose(input);
}
int IsWord(char word[25]){//to check that if is word is alphabetical characters.
    for(int i=0 ; i<strlen(word) ; i++){
        if(word[i] < 65 || (word[i]>90 &&word[i]<97) || word[i]>122)
            return 0;
    }
    return 1;
}
AVLNode CreateTheAVLtree_2(AVLNode T,char Text[1000]){//to put the value from file to tree
    char *token = strtok(Text," ");
    int i=0;
    while(token != NULL){
        AVLNode p = Find(token,T);
        if(p != NULL)
            p->frequancy++;
        else{
            T = Insert(token,T);
            i++;
        }
        token = strtok(NULL," ");
    }
    sizeofTable = MaxPrime((int)i*3);
    return T;
}
AVLNode InsertwordToTheAVLtree_3(AVLNode T){
    char word[25];
    printf("Enter the word that you want to insert please\n");
    getchar();
    gets(word);
    if(IsWord(word) ==0 ){
        printf("please enter correct word\n");
        return T;
    }
    AVLNode p = Find(word,T);
    if(p != NULL)
        p->frequancy++;
    else
        T = Insert(word,T);
    return T;
}
AVLNode DeleteWordFromTheAVLtree_4(AVLNode T){
    char word[25];
    printf("Enter the word that you want to delete please\n");
    getchar();
    gets(word);
    if(IsWord(word) ==0 ){
        printf("please enter correct word\n");
        return T;
    }
    AVLNode p = Find(word,T);
    if(p == NULL)
        printf("This word is not exist please try again\n");
    else{
        if(p->frequancy > 1)
            p->frequancy--;
        else
            T = Delete(word,T);
    }
    return T;
}
void PrintInOrder_5( AVLNode t){
    if( t != NULL)
    {
        PrintInOrder_5( t->Left );
        printf("%s:%d\n", t->word,t->frequancy);
        PrintInOrder_5( t->Right );
    }
}
void CreateTheHashTable_6(AVLNode tree,Hashword T[]){
    if(tree != NULL){
        CreateTheHashTable_6(tree->Left,T);
        T = insertToHash(tree->word,T);
        int index = FindFromHash(tree->word,T);
        T[index].frequency = tree->frequancy;
        CreateTheHashTable_6(tree->Right,T);
    }
}
Hashword* InsertWordtToTheHashTable_7(Hashword T[]){
    char word[25];
    printf("Enter the word that you want insert to HashTable\n");
    getchar();
    gets(word);
    if(IsWord(word) ==0 ){
        printf("please enter correct word\n");
        return T;
    }
    T = insertToHash(word,T);
    return T;
}
void DeleteWordtToTheHashTable_8(Hashword T[]){
    char word[25];
    printf("Enter the word that you want to delete from HashTable\n");
    getchar();
    gets(word);
    if(IsWord(word) ==0 ){
        printf("please enter correct word\n");
        return T;
    }
    DeleteFromHash(word,T);
}
void SearchWordInTheHashTable_9(Hashword T[]){
    char word[25];
    printf("Enter the word that you want to find it from HashTable\n");
    getchar();
    gets(word);
    int index = FindFromHash(word,T);
    if(index == -1){
        printf("This word is not exist\n");
        return ;
    }
    printf("The word is : %s in index [%d] with frequency = %d\n",T[index].word,index,T[index].frequency);

}
void printStatics_10(AVLNode tree,Hashword T[],int z,int y){
    if(z != 0){
        AVLNode t = MaxFrequentInTree(tree,tree);
        printf("The max word frequent in Tree is [%s] for %d times.\n",t->word,t->frequancy);
    }
    if(y != 0){
        int h = MaxFreuentInHashTable(T);
        printf("The max word frequent in HashTable is [%s] for %d times.\n",T[h].word,T[h].frequency);
        int count =0;
        for(int i=0 ; i<sizeofTable ; i++){
            if(T[i].frequency == 1)
                count++;
        }
        printf("The number of unique word is : %d\n",count);//unique value is the value that dont frequent
    }
    if( y!= 0 && z!=0)
        frequentInHashTree(tree,T);
}
AVLNode MaxFrequentInTree(AVLNode t,AVLNode max){//to return the max frequent word in Avl
    if(t != NULL){
        MaxFrequentInTree(t->Left,max);
        if(max->frequancy < t->frequancy)
            max = t;
        MaxFrequentInTree(t->Right,max);
    }
    return max;
}
int MaxFreuentInHashTable(Hashword T[]){//to return the max frequent word in Hash
    int max = T[0].frequency,k=0;
    for(int i =1 ; i<sizeofTable ; i++){
        if(T[i].frequency != 0){
            if(max < T[i].frequency){
                max = T[i].frequency;
                k =i;
            }
        }
    }
    return k;
}
void frequentInHashTree(AVLNode t,Hashword T[]){//to find value that exist in Tree and Hash but frequent in hash more than Tree
    if(t!= NULL){
        frequentInHashTree(t->Left,T);
        int h = FindFromHash(t->word,T);
        if(h != -1){
            if(t->frequancy < T[h].frequency)
                printf("The word [%s] frequent in Hash more than Tree ,in Hash = %d ,in Tree = %d\n",t->word,T[h].frequency,t->frequancy);
        }
        frequentInHashTree(t->Right,T);
    }
}
//*******************************************************************************************************************/
/**************************************************AVL Library***********************************************/
AVLNode MakeEmpty(AVLNode T )
{
    if( T != NULL )
    {
        MakeEmpty( T->Left );
        MakeEmpty( T->Right );
        free( T );
    }
    return NULL;
}
AVLNode Find( char word[20], AVLNode T )
{
    if( T == NULL )
        return NULL;
    if(strcasecmp(word,T->word) < 0)
        return Find(word,T->Left);
    else if( strcasecmp(word,T->word) > 0)
        return Find(word,T->Right);
    else
        return T;
}

AVLNode FindMin( AVLNode T )
{
    if( T == NULL )
        return NULL;
    else if( T->Left == NULL )
        return T;
    else
        return FindMin( T->Left );
}

AVLNode FindMax( AVLNode T )
{
    if( T != NULL )
        while( T->Right != NULL )
            T = T->Right;

    return T;
}
int Height( AVLNode P )
{
    if( P == NULL )
        return -1;
    else
        return P->Height;
}
int Max( int L, int R )//left hight , right hight
{
    return L > R ? L : R;
}
AVLNode SingleRotateWithLeft( AVLNode K2 )//rotate to right
{
    AVLNode  K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

    return K1;  /* New root */
}
AVLNode SingleRotateWithRight( AVLNode K1 )//rotate to lift
{
    AVLNode K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
    K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

    return K2;  /* New root */
}
AVLNode DoubleRotateWithLeft( AVLNode K3 ) //left right rotate
{
    /* Rotate between K1 and K2 */
    K3->Left = SingleRotateWithRight( K3->Left );//rotate to left

    /* Rotate between K3 and K2 */
    return SingleRotateWithLeft( K3 );//rotate to right
}
AVLNode DoubleRotateWithRight(AVLNode K1)//right left rotate
{
    /* Rotate between K3 and K2 */
    K1->Right = SingleRotateWithLeft(K1->Right);//rotate to right

    /* Rotate between K1 and K2 */
    return SingleRotateWithRight( K1 );//rotate to left
}

AVLNode Insert( char word[25], AVLNode T )
{
    if( T == NULL )
    {
        T = malloc( sizeof( struct AVLnode ) );
        if( T == NULL )
            printf( "Out of space!!!" );
        else
        {
            strcpy(T->word,word);
            T->Height = 0;
            T->frequancy = 1;
            T->Left = T->Right = NULL;
        }
    }
    else if( strcasecmp(word,T->word) < 0)
    {
        T->Left = Insert( word, T->Left );
        if( Height( T->Left ) - Height( T->Right ) == 2 )
            if( strcasecmp(word,T->Left->word) < 0 )
                T = SingleRotateWithLeft( T );//rotate to right
            else
                T = DoubleRotateWithLeft( T );//rotate to left then to right
    }
    else if(strcasecmp(word,T->word) >0 )
    {
        T->Right = Insert( word, T->Right );
        if( Height( T->Right ) - Height( T->Left ) == 2 )
            if( strcasecmp(word,T->Right->word) > 0)
                T = SingleRotateWithRight( T );
            else
                T = DoubleRotateWithRight( T );
    }
    /* Else X is in the tree already; we'll do nothing */
    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
    return T;
}
AVLNode Delete( char word[25], AVLNode T ){
    AVLNode TmpCell;
    if( T == NULL )
        printf( "Element not found" );
    else if( strcasecmp(word,T->word) < 0 ){  /*Go left */
        T->Left = Delete( word, T->Left );
        T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
        if( Height( T->Right ) - Height( T->Left ) == 2 ){
            if( Height(T->Right->Right) >= Height(T->Right->Left))
                T = SingleRotateWithRight( T );
            else
                T = DoubleRotateWithRight( T );
        }
    }
    else if( strcasecmp(word,T->word) > 0 ){  /* X > T->element Go right */
        T->Right = Delete( word, T->Right );
        T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
        if( Height( T->Left ) - Height( T->Right ) == 2 ){
            if( Height(T->Left->Left) >= Height(T->Left->Right) )
                T = SingleRotateWithLeft( T );
            else
                T = DoubleRotateWithLeft( T );
        }

    }
    else{  /* Found element to be deleted */
        if( T->Left != NULL && T->Right != NULL) /* Two children */
        {
            TmpCell = FindMin( T->Right );
            strcpy(T->word,TmpCell->word);
             T->Right = Delete( T->word, T->Right );
        }
         else  /* One or zero children */{
            TmpCell = T;
            if( T->Left == NULL )
                T = T->Right;
             else if( T->Right == NULL )
                    T = T->Left;
            free( TmpCell );
            }
        if(T != NULL){
            T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
        }
    }
    return T;
}
//*******************************************************************************************************************
//********************************************Library of Hash********************************************;
int hash(char* key,Hashword Table[]){//to return index of good index place in hash
    int hashValue = 0;
    char word[25];
    strcpy(word,key);
    while (*key != '\0'){
        hashValue = ((hashValue << 5) + *key++)%sizeofTable;
    }
    int index =0,R = MinPrime(sizeofTable);//R is a that prime smaller than Table size
    for(int i=0 ; i<sizeofTable ; i++){
         index = (hashValue + (i*(R - hashValue%R)))%sizeofTable;
         if(Table[index].frequency == 0){
            return index;
         }
         if(strcasecmp(Table[index].word,word) == 0){
            Table[index].frequency++;
            return -2;
         }
    }
    return -1;
}
Hashword* ReHash(Hashword *T){
    int newsize = MaxPrime(sizeofTable*2);//new size of new TableHash
    int siz = sizeofTable;
    sizeofTable = newsize;//here we change the sizeofTable for Hash
    Hashword *newTable = (Hashword*)malloc(sizeof(Hashword) * newsize);//we implemnt a new table
    for(int i=0 ; i<newsize ; i++){//we put inital value for it
        newTable[i].frequency = 0;
        strcpy(newTable[i].word,"");
    }
    for(int i=0 ; i<siz ; i++){//we transfer the data from oldTable to new Table
        if( T[i].frequency != 0){
            insertToHash(T[i].word,newTable);
        }
    }
    free(T);//free old Table
    return newTable;//we return the pointer of new table
}
Hashword* insertToHash(char word[25],Hashword Table[]){
    int index = hash(word,Table);
    if(index == -2){//this case will occure when they insert same word ,we do allthing in hash
    }
    else {
        strcpy(Table[index].word,word);
        Table[index].frequency = 1;
        countNumHash++;
    }
    int x = 0.6*sizeofTable;
    if(countNumHash >= x){//to doing rehash if the data is being more than %60 of HashTable
        Table = ReHash(Table);
    }
    return Table;
}
int FindFromHash(char* key,Hashword Table[]){//we find the value same as we hash it
    int hashValue = 0;
    char word[25];
    strcpy(word,key);
    while (*key != '\0') {
        hashValue = (hashValue << 5) + *key++;
    }
    int index,R = MinPrime(sizeofTable);//R is a that prime smaller than Table size
    for(int i=0 ; i<sizeofTable ; i++){
         index = (hashValue + (i*(R - hashValue%R)))%sizeofTable;
         if(Table[index].frequency == 0){//the value dont exist
            return -1;
         }
         else if(strcasecmp(Table[index].word,word) == 0){
            return index;
         }
    }
    return -1;
}
void DeleteFromHash(char* key,Hashword Table[]){
    char word[25];
    strcpy(word,key);
    int index = FindFromHash(word,Table);
    if(index == -1){
        printf("This word is not exist\n");
        return ;
    }
    else if(Table[index].frequency > 1){//the word is exist more than once
        Table[index].frequency--;
    }
    else{//to chnge value in index that we want to delete
        strcpy(Table[index].word,"");
        Table[index].frequency = 0;
        countNumHash--;
    }
}
int IsprimeNumber(int x){//to check if the number is prime
    if(x<=1)
        return 0;
    for(int i=2 ; i*i <= x ; i++){
        if(x%i == 0)
            return 0;
    }
    return 1;

}
int MinPrime(int num){//to return prime number min than we insert
    for(int p = num-1 ; p>1 ; p-- ){
        if(IsprimeNumber(p))
            return p;
    }
    return -1;
}
int MaxPrime(int num){//to return prime number max than we insert
    for(int p = num+1 ; p<num*100 ; p++){
        if(IsprimeNumber(p))
            return p;
    }
    return -1;
}
