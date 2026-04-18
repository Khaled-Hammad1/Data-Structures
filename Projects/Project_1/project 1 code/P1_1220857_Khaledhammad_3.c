#include <stdio.h>                // Name : khaled hammad || ID : 1220857 || section: 3 || Doctor : Radi Jarrar
#include <stdlib.h>
#include <string.h>
typedef struct node* District;
typedef struct node1* Town;

struct node {
    int population;
    char DistName[50];
    Town NextT;
    District up;
    District down;
    District Last;
    Town LastTown;
};
struct node1{
    int population;
    char TownName[50];
    Town nextTown;
    Town preTown;
};
// District Library
District makeEmpty(District L);
int IsEmptyDistric(District L);
int IsLastDistrict(District p,District L);
District FindDistrict(char dist[50],District L);
District FindPreviousOfDistrict(char dist[50],District L);//extra
void insertDistrict(char dist[50],District L);
void insertDistrictLast(char dist[50],District L);
void printAll(District L);
void DeleteDistrict(char dist[50],District L);
void DeleteListOfDistrict(District L);
int sizeOfDistrict(District L);
//Town library
int IsEmptyTown(District L);
int IsLastTown(Town p,Town L);
void insertTown (char dist[50],char town[50],int population,District L);
void insertTownLast (char dist[50],char town[50],int population,District L);
int sizeOfTown (District L);
void DeleteListOfTown(District L);
Town FindTown(char town[50],District L);
Town FindTownInDistrict(char TownName[50],char dist[50],District L);
Town FindPreviousTown(char town[50],District L);//extra
void DeleteTown(char Nametown[50],char  Namedist[50],District d);
void ChangeTownPopulation(char Namedist[50],char Nametown[50],int newpopulation,District L);

void loadInputFile_1(District L,int x);
void printInputFile_2();
void sortDistrict_3(District L);
void sortTown_4(District D);
void printSortedInformation_5(District L);
void insertDistrict_6(District L);
void TownInsert_7(District L);
void TownDelete_8(District L);
void DeleteDistrict_9(District L);
void MaxAndMin_10(District L);
void PrintDistrict_11(District L);
void changePopluation_12(District L);
void printToFile_13(District L);
void sortLinkedList(District L);
int maxdigit(District L);
int maxLetter(District L);
int main()
{
    District L = makeEmpty(NULL);
    int x=0;

    int choose=0;
    while(choose !=14){
        printf("****************************************************************************************\n");
        printf("Enter opeartion\n\n");
        printf("1. Load the input file (Palestinian districts and their town with population).\n");
        printf("2. Print the loaded information before sorting (as in the input file format).\n");
        printf("3. Sort the districts alphabetically using Radix sort.\n");
        printf("4. Sort the towns for each district based on population in ascending order.\n");
        printf("5. Print the sorted information.\n");
        printf("6. Add a new district to the list of sorted districts (and sort the list).\n");
        printf("7. Add a new town to a certain district.\n");
        printf("8. Delete a town from a specific district.\n");
        printf("9. Delete a complete district.\n");
        printf("10.Calculate the population of Palestine, the max and min town population.\n");
        printf("11.Print the districts and their total population (without towns details).\n");
        printf("12.Change the population of a town, after prompting the user to enter the district name.\n");
        printf("13.Save to output file.\n");
        printf("14.Exit.\n");
        printf("****************************************************************************************\n");

        scanf("%d",&choose);

        switch(choose){
            case 1: loadInputFile_1(L,x);
                    if(!IsEmptyDistric(L)){
                       sortDistrict_3(L);
                        x=1; //After reading the strings successfully, your application should sort the districts using the
                    }        //Radix Sort algorithm. And sorting the towns based on the population.
                    if(!IsEmptyTown(L))
                       sortTown_4(L);
                    break;
            case 2: printInputFile_2(x);
                    break;
            case 3: sortDistrict_3(L);
                    break;
            case 4: sortTown_4(L);
                    break;
            case 5: printSortedInformation_5(L);
                    break;
            case 6: insertDistrict_6(L);
                    break;
            case 7: TownInsert_7(L);
                    break;
            case 8: TownDelete_8(L);
                    break;
            case 9: DeleteDistrict_9(L);
                    break;
            case 10: MaxAndMin_10(L);
                    break;
            case 11: PrintDistrict_11(L);
                     //printAll(L);
                    break;
            case 12: changePopluation_12(L);
                    break;
            case 13: printToFile_13(L);
                    break;
            case 14: //exit File
                    break;
            default : printf("There is no operation with this number please try again\n");
                    break;
        }

    }
    return 0;
}
void loadInputFile_1(District L,int x){
    if(x == 1){
        printf("You loaded the information\n");
        return ;
    }
    FILE *input;
    char f[100],distName[50],TownName[50],pop[50];
    input = fopen("districts.txt","r");

    while(fgets(f,100,input) != NULL){
        char *token = strtok(f,"|");
        strcpy(distName,token);
        token = strtok(NULL,"|");
        strcpy(TownName,token);
        token = strtok(NULL,"|");
        strcpy(pop,token);
        insertTownLast(distName,TownName,atoi(pop),L);
    }
    if(IsEmptyDistric(L))
        printf("There is no any information in file ,please fill file before load information\n");

    fclose(input);
}
void printInputFile_2(int x){
    if(x== 0){
        printf("please load the information before print it\n");
        return ;
    }
    FILE *input;
    char f[100];
    input = fopen("districts.txt","r");

    while(fgets(f,100,input) != NULL){
            printf("%s",f);
    }
    printf("\n");
}
void sortDistrict_3(District L){
    if(IsEmptyDistric(L) == 1){
        printf("It is empty,Please enter information first\n");
        return ;
    }
    District A[54],p;//first node for empty letter | exp : ab>abc
    int max  =maxLetter(L);
    int n = max-1;
    int siz = sizeOfDistrict(L);
    for(int j=0 ; j<max ; j++){
        for(int i=0; i<54 ;i++){
            A[i] = makeEmpty(NULL);
        }
         p = L->down;
            for(int i=0 ; i<siz ; i++){
                        int x = p->DistName[n];
                        if(x >=97 && x<= 122){
                            x = x-96;
                            int k = 2*x;//a=2,b=4,c=6,d=8 ....
                            A[k]->Last->down = p;
                            A[k]->Last = p;
                            p = p->down;
                            A[k]->Last->down = NULL;
                        }
                        else if(x>= 65 && x<=90){
                            x = x-65;
                            int h = (2*x)+1;//A=1,B=3,C=5,D=7 ....
                            A[h]->Last->down = p;
                            A[h]->Last = p;
                            p = p->down;
                            A[h]->Last->down = NULL;
                        }

                    else if (p->DistName[n] == '\0'){
                        A[0]->Last->down = p;
                        A[0]->Last = p;
                        p = p->down;
                        A[0]->Last->down = NULL;
                    }
                    else {
                        A[53]->Last->down = p;
                        A[53]->Last = p;
                        p = p->down;
                        A[53]->Last->down = NULL;
                    }

            }
            L->Last = L;
            L->down = NULL;
            int y=0,s=0;
            while(y<54 && s <siz ){
                if(A[y]->down != NULL){
                     District k = A[y]->down;
                     while(k != NULL){
                        if(IsEmptyDistric(L)){
                            L->Last->down = k;
                            L->Last = k;
                            k->up = L;
                        }
                        else{
                            L->Last->down = k;
                            District temp = L->Last;
                            L->Last = k;
                            k->up = temp;
                        }
                        k = k->down;
                        L->Last->down = NULL;
                        s++;
                     }
                }
                y++;
            }
            n--;

    }
}
int maxLetter(District L){
    District p = L->down;
    int maxNum = strlen(p->DistName);
    p = p->down;
    while(p != NULL){
        if(strlen(p->DistName) > maxNum)
            maxNum = strlen(p->DistName);
        p = p->down;
    }
    return maxNum;
}
void sortTown_4(District D){
    if(IsEmptyDistric(D) || IsEmptyTown(D)){
        printf("It is empty,please enter information first\n");
        return ;
    }
    District dist = D->down;
    if(dist->NextT != NULL){
        sortLinkedList(dist);
    }
    while(dist != NULL){
            if(dist->NextT != NULL){
                sortLinkedList(dist);
            }
        dist = dist->down;
    }
}
void sortLinkedList(District L){
    District A[10];
    Town p;
    int max = maxdigit(L);
    int count = sizeOfTown(L);
    int n=1;
    for(int j=0 ; j< max ; j++){
        for(int i=0; i<10 ;i++){
            A[i] = makeEmpty(NULL);
        }
        p = L->NextT;
            for(int i=0 ; i<count ; i++){
                int x = (p->population / n)%10;
            if(A[x]->NextT == NULL){
                A[x]->LastTown = p;
                A[x]->NextT = p;
            }
            else{
                A[x]->LastTown->nextTown = p;
                A[x]->LastTown = p;
            }
            p = p->nextTown;
            A[x]->LastTown->nextTown = NULL;
            }
            L->LastTown = L;
            L->NextT = NULL;
            int siz =0,y=0;
            while(siz < count && y<10 ){
                if(A[y]->NextT != NULL){
                    Town temp = A[y]->NextT;
                    while(temp != NULL){
                     if(L->NextT == NULL){
                        L->LastTown = temp;
                        L->NextT = temp;
                    }
                    else{
                        L->LastTown->nextTown = temp;
                        Town pree =L->LastTown;
                        L->LastTown = temp;
                        temp->preTown = pree;
                    }
                    temp = temp->nextTown;
                    L->LastTown->nextTown = NULL;
                    siz++;
                    }
                }
                y++;
            }
            n = n*10;
    }
}
int maxdigit(District L){
    Town p = L->NextT;
    int maxNum = p->population;
    p = p->nextTown;
    while(p != NULL){
        if(p->population > maxNum)
            maxNum = p->population;
        p = p->nextTown;
    }
    int Maxdigit = 0;
    while(maxNum != 0){
        maxNum = maxNum/10;
        Maxdigit++;
    }
    return Maxdigit;
}
void printSortedInformation_5(District L){
    if(IsEmptyDistric(L) == 1){
        printf("It is empty,please enter information first\n");
        return ;
    }
    sortDistrict_3(L);
    if(IsEmptyTown(L) == 0){
        sortTown_4(L);
    }
    District distTemp = L->down;
    Town townTemp;
    printf("\n_______________________________________________________________\n");
    int i=0;
    while(distTemp != NULL){
        printf("%s District , Population = %d\n",distTemp->DistName,distTemp->population);
        townTemp = distTemp->NextT;
        while(townTemp != NULL){
            printf("%s , %d\n",townTemp->TownName,townTemp->population);
            townTemp = townTemp->nextTown;
        }
        distTemp = distTemp->down;
        i++;
    }
    printf("_______________________________________________________________\n");
}
void insertDistrict_6(District L){
    char dist[50];
    if (!IsEmptyDistric(L)){
        sortDistrict_3(L);
    }
    printf("Enter Name of district\n");
    getchar();
    gets(dist);
    insertDistrict(dist,L);
    sortDistrict_3(L);
}
void TownInsert_7(District L){
    char distName[50],townName[50];
    int population;
    printf("Enter Town Name\n");
    getchar();
    gets(townName);
    printf("Enter District Name of town\n");
    gets(distName);
    District dist = FindDistrict(distName,L);
    if(dist == NULL){
        printf("Thers is no district with this name ,Enter it befor insert town\n");
        return ;
    }
    Town t = FindTownInDistrict(townName,distName,L);
    if(t != NULL){
        printf("This town is already exist ,please enter another one\n");
        return ;
    }
    printf("Enter Town population\n");
    scanf("%d",&population);
    insertTownLast(distName,townName,population,L);
}
void TownDelete_8(District L){
    if(IsEmptyDistric(L) == 1){
        printf("It is empty,please enter information first\n");
        return ;
    }
    char distName[50],townName[50];
    printf("Enter Town Name\n");
    getchar();
    gets(townName);
    printf("Enter District Name of town\n");
    gets(distName);
    District dist = FindDistrict(distName,L);
    if(dist == NULL){
        printf("Thers is no district with this name ,please try again\n");
        return ;
    }
    Town to = FindTown(townName,L);
    if(to == NULL){
        printf("Thers is no town with this name ,please try again\n");
        return ;
    }
    DeleteTown(townName,distName,L);
}
void DeleteDistrict_9(District L){
    if(IsEmptyDistric(L) == 1){
        printf("It is empty,please enter information first\n");
        return ;
    }
    char dist[50];
    printf("Enter Name of District\n");
    getchar();
    gets(dist);
    District d = FindDistrict(dist,L);
    if(d != NULL){
        DeleteDistrict(dist,L);
    }
    else{
        printf("The District is not exist\n");
    }

}
void MaxAndMin_10(District L){
    if(IsEmptyDistric(L) == 1){
        printf("It is empty ,please Enter information first\n");
        return ;
    }
    District dist = L->down;
    int sum =0;
    while(dist != NULL){
        sum += dist->population;
        dist = dist->down;
    }
    dist = L->down;
    if(IsEmptyTown(L)){
        printf("There no any town entered,please insert town\n");
        return ;
    }
    while(dist->NextT == NULL){
        dist = dist->down;
    }
    Town town = dist->NextT;
    Town maxtown = town,mintown=town;
    int max = town->population,min = town->population;
    while(dist != NULL){
            town = dist->NextT;
        while(town != NULL){
            if(town->population > max){
                max  = town->population;
                maxtown = town;
            }
            if(town->population < min){
                min = town->population;
                mintown = town;
            }
            town = town->nextTown;
        }
        dist = dist->down;
    }
    printf("The total population of palestine is: %d\n",sum);
    printf("The town with the max population is: %s |That have : %d\n",maxtown->TownName,max);
    printf("The town with the min population is: %s |That have : %d\n",mintown->TownName,min);
}
void PrintDistrict_11(District L){
    if(IsEmptyDistric(L) == 1){
        printf("It is empty,please enter information first\n");
        return ;
    }
    District distTemp = L->down;
    printf("\n_______________________________________________________________\n");
    int i=0;
    while(distTemp != NULL){
        printf("%s District , Population = %d\n",distTemp->DistName,distTemp->population);
        distTemp = distTemp->down;
        i++;
    }
    printf("_______________________________________________________________\n");

}
void changePopluation_12(District L){
    if(IsEmptyDistric(L) == 1){
        printf("It is empty,please enter information first\n");
        return ;
    }
    char distName[50],townName[50];
    int population;
    getchar();
    printf("Enter the District Name for Town\n");
    gets(distName);
    if(FindDistrict(distName,L) == NULL){
        printf("There is no District with this name , please try again\n");
        return ;
    }
    printf("Enter town name\n");
    gets(townName);
    if(FindTownInDistrict(townName,distName,L) == NULL){
        printf("There is no town with this name in %s,please try again\n",distName);
        return ;
    }
    printf("Enter new population of town\n");
    scanf("%d",&population);
    ChangeTownPopulation(distName,townName,population,L);
}
void printToFile_13(District L){
    if(IsEmptyDistric(L) == 1){
        printf("There is no any information , please enter information before load it to file\n");
        return ;
    }
    FILE *output;
    output = fopen("sorted_districts.txt","w");

    District distTemp = L->down;
    Town townTemp;
    int i=0;
    while(distTemp != NULL){
        fprintf(output,"%s District , Population = %d\n",distTemp->DistName,distTemp->population);
        townTemp = distTemp->NextT;
        while(townTemp != NULL){
            fprintf(output,"%s , %d\n",townTemp->TownName,townTemp->population);
            townTemp = townTemp->nextTown;
        }
        distTemp = distTemp->down;
        i++;
    }
    fclose(output);
}
//***********************************************************************************************************************
///////////////////////////////////District Library/////////////////////////////////////////////////////////////
District makeEmpty(District L){
    if(L != NULL){
        DeleteListOfDistrict(L);
    }
    L = (District)malloc(sizeof(struct node));
    if(L == NULL)
        printf("\nout of Memory\n");

    L->NextT =NULL;
    L->down = NULL;
    L->up =NULL;
    L->Last  = L;
    L->LastTown = L;
    return L;
}
int IsEmptyDistric(District L){
    return L->down == NULL;
}
int IsLastDistrict(District p,District L){// p is node in the List L which L is a head
    return p->down == NULL;
}
District FindDistrict(char dist[50],District L){
    if(IsEmptyDistric(L) == 1){
        return NULL;
    }
    District temp;
    temp = L->down;

    while(temp != NULL &&  strcmp(temp->DistName,dist) != 0){
        temp = temp->down;
    }
    if(temp == NULL){
        return NULL;
    }
    return temp;
}
District FindPreviousOfDistrict(char dist[50],District L){
    if(IsEmptyDistric(L) == 1){
        return NULL;
    }
    District temp;
    temp = L;
    while(temp->down != NULL && strcmp(temp->down->DistName,dist) != 0){
        temp = temp->down;
    }
    return temp;

}
void insertDistrict(char dist[50],District L){
    District p = FindDistrict(dist ,L);
    if( p != NULL){
        printf("This District is already extist\n");
        return ;
    }
    District temp1;
    temp1 = (District)malloc(sizeof(struct node));
    strcpy(temp1->DistName,dist);
    if(IsEmptyDistric(L) == 0){//if there is District
        District d = L->down;
        temp1->down =d;
        temp1->up = L;
        L->down = temp1;
        d->up = temp1;
    }
    else{//there is no district in L
        temp1->up = L;
        L->down = temp1;
        temp1->down = NULL;
    }
    temp1->NextT = NULL;
    temp1->population =0;
}
void insertDistrictLast(char dist[50],District L){
    District p = FindDistrict(dist ,L);
    if( p != NULL){
        printf("This District is already extist\n");
        return ;
    }
    District temp1;
    temp1 = (District)malloc(sizeof(struct node));
    strcpy(temp1->DistName,dist);
    if(IsEmptyDistric(L) == 0){//to check if there is District
        L->Last->down =temp1;
        District preDist = L->Last;
        L->Last = temp1;
        temp1->down =NULL;
        temp1->up = preDist;
    }
    else{//there is no district in L
        temp1->up = L;
        L->Last->down = temp1;
        L->Last = temp1;
        temp1->down = NULL;
    }
    temp1->NextT = NULL;
    temp1->population =0;
}
void printAll(District L){
    if(IsEmptyDistric(L) == 1){
        printf("\nThers is no any District it is Empty List\n");
        return ;
    }
    District distTemp = L->down;
    Town townTemp;
    printf("\n_______________________________________________________________\n");
    int i=0;
    while(distTemp != NULL){
        printf("%s District , Population = %d\n",distTemp->DistName,distTemp->population);
        townTemp = distTemp->NextT;
        while(townTemp != NULL){
            printf("%s , %d\n",townTemp->TownName,townTemp->population);
            townTemp = townTemp->nextTown;
        }
        distTemp = distTemp->down;
        i++;
    }
    printf("_______________________________________________________________\n");

}
void DeleteDistrict(char dist[50],District L){
    District temp,preDist,postDist;
    temp = FindDistrict(dist,L);
    preDist = temp->up;

    if ( IsLastDistrict(preDist,L) == 0){//if p is last this mean that x is not found so x already deleted
        preDist->down = temp->down;
        if(temp->down !=NULL){
            postDist = temp->down;
            postDist->up = preDist;
        }
        DeleteListOfTown(temp);
        free(temp);
    }
    else
        printf("\nThere is no District with this name so we can not delete it\n");
}
void DeleteListOfDistrict(District L){
    District p,temp;
    p = L->down;
    L->down = NULL;
     while(p != NULL){
        if(p->NextT != NULL){
            DeleteListOfTown(p);
        }
        temp = p->down;
        free(p);
        p = temp;
     }
     free(L);
}
int sizeOfDistrict(District L){
    if(IsEmptyDistric(L)== 1){
        return 0;
    }
    District temp = L->down;
    int count = 0;
    while(temp != NULL){
        count++;
        temp = temp->down;
    }
    return count;

}

//////////////////////////////////////End of District library//////////////////////////////////////


//*********************************************************************************************************************


///////////////////////////////////////////Town Library/////////////////////////////////////
int IsEmptyTown(District L){
    if(IsEmptyDistric(L) == 1){
        return 1;
    }
    District dist = L->down;
    while(dist != NULL){
        if(dist->NextT != NULL){
            return 0;
        }
        dist = dist->down;
    }
    return  1;
}
int IsLastTown(Town p,Town L){// p is node in the List L which L is head
    return p->nextTown == NULL;
}
void insertTown (char dist[50],char town[50],int population,District L){//Insert from first
        District d;
        d = FindDistrict(dist,L);
        if(d != NULL){//Case 1 : The district is exsist
                 Town temp,p;
            temp = (Town)malloc(sizeof(struct node1));
            if(d->NextT != NULL){//if there is town in district
                p = d->NextT;
                d->NextT = temp;
                temp->nextTown = p;
                p->preTown = temp;
            }
            else{//if there is town in district
                d->NextT = temp;
                temp->nextTown = NULL;
            }
            strcpy(temp->TownName,town);
            temp->population = population;
            d->population += population;
            return;
        }
    // case 2 :the district is not exsist
    insertDistrict(dist,L);
    District temp1;
    temp1 =FindDistrict(dist,L);

    Town temp2;
    temp2 = (Town)malloc(sizeof(struct node1));
    temp2->nextTown = NULL;
    temp1->NextT =temp2;
    strcpy(temp2->TownName,town);
    temp2->population = population;
    temp1->population = population;
    return;
}
void insertTownLast (char dist[50],char town[50],int population,District L){//Insert Last
        District d;
        d = FindDistrict(dist,L);
        if(d == NULL){//Case 1 : For insert file
            insertDistrictLast(dist,L);
        }
        d = FindDistrict(dist,L);
            Town temp,pree;
            temp = (Town)malloc(sizeof(struct node1));
            if(d->NextT != NULL){//if there is town in district
                d->LastTown->nextTown = temp;
                pree =d->LastTown;
                d->LastTown = temp;
                temp->nextTown = NULL;
                temp->preTown = pree;
            }
            else{//if there is no town in district
                d->LastTown = temp;
                d->NextT = temp;
            }
            d->LastTown->nextTown = NULL;
            strcpy(temp->TownName,town);
            temp->population = population;
            d->population += population;
            return;

}
int sizeOfTown (District L){
    if (  L->NextT == NULL){
        return 0;
    }
    Town p = L->NextT;
    int count = 0;
    while(p != NULL){
        count++;
        p = p->nextTown;
    }
    return count;
}
void DeleteListOfTown(District L){
    Town p,temp;
    p = L->NextT;
    L->NextT = NULL;
     while(p != NULL){
        temp = p->nextTown;
        free(p);
        p = temp;
     }
}
Town FindTown(char town[50],District L){
    if(IsEmptyDistric(L) == 1){
        printf("\nThers is no any District so there is no town it is Empty List");
        return NULL;
    }
    District distTemp;
    distTemp = L->down;
    Town townTemp;
    while(distTemp != NULL){
        townTemp = distTemp->NextT;
        while(townTemp != NULL){
            if(strcmp(townTemp->TownName,town) ==0)
                return townTemp;
            else
                townTemp = townTemp->nextTown;
        }
            distTemp = distTemp->down;
        }
        return NULL;
}
Town FindTownInDistrict(char townName[50],char dist[50],District L){
    District tempDist = FindDistrict(dist,L);
    if (tempDist == NULL)
        return NULL;

    Town townTemp = tempDist->NextT;
    while(townTemp != NULL){
        if(strcmp(townTemp->TownName,townName) == 0){
            return townTemp;
        }
        townTemp=townTemp->nextTown;
    }
    return NULL;
}
Town FindPreviousTown(char town[50],District L){
    if(IsEmptyDistric(L) == 1){
        return NULL;
    }
    District distTemp;
    distTemp = L->down;
    Town townTemp;
    while(distTemp != NULL){
        townTemp = distTemp->NextT;
        while(townTemp->nextTown != NULL){
            if(strcmp(townTemp->nextTown->TownName,town) ==0)
                return townTemp;
            else
                townTemp = townTemp->nextTown;
        }
            distTemp = distTemp->down;
        }
    return townTemp;

}
void DeleteTown(char Nametown[50],char  Namedist[50],District d){
    Town prevTown,temp,postTown;
    District head;
    temp = FindTown(Nametown,d);
    head = FindDistrict(Namedist,d);
    if(head == NULL){
        printf("There is no district with this name\n");
        return ;
    }
    if(temp == NULL){//case 1:the town is not exist
        printf("There is no town with this name\n");
        return ;
    }
    if(temp == head->NextT){//case 2 :delete the first town
        head->NextT = temp->nextTown;
        head->population -=temp->population;
        free(temp);
        return ;
    }
    prevTown = temp->preTown;
    postTown = temp->nextTown;
    prevTown->nextTown = temp->nextTown;
    if(temp->nextTown != NULL){
        postTown = temp->nextTown;
        postTown->preTown = prevTown;
    }
    head->population -=temp->population;
    free(temp);
}
void ChangeTownPopulation(char Namedist[50],char Nametown[50],int newpopulation,District L){
    District tempDist = FindDistrict(Namedist,L);
    Town townTemp = FindTownInDistrict(Nametown,Namedist,L);
    if(tempDist == NULL || townTemp ==NULL){
        printf("\nThe town is not found\n");
        return ;
    }
    tempDist->population -=townTemp->population;
    townTemp->population = newpopulation;
    tempDist->population +=townTemp->population;
}
/////////////////////////////////////////End Town library/////////////////////////////////////////////////////////////
/*
Name : khaled hammad
ID : 1220857
Section : 3
Doctor : Radi Jarrar
Data : 8/4/2024
day (
*/
