#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include <math.h>

void WordSearch(char word[]);
void History();
void AlphaSearch(char alpha);
void WordOfDay(int n);
void AddWord();
int NumLines(FILE *ptr);
int spellCheck(char word[]);
void PatternSearch1(char query[]);
void PatternSearch2(char query[]);
void PatternSearch3(char query[]);

int main()
{
    int choice, n, i,len, flag;
    char query[100], alpha;
    srand(time(NULL));
    system ("clscr");
    
    printf("----------------------------------------------");
    printf("\nTHESAURUS\n");
    printf("----------------------------------------------\n");
    l1: printf("What do you want to do today ?\n");
    printf(" 1. Search for a word\n");
    printf(" 2. Search for list\n");
    printf(" 3. Word of the day!\n");
    printf(" 4. Search history\n");
    printf(" 5. Add Word\n");
    printf(" 6. Pattern wise Search\n");
    printf(" 7. Exit\n");
    printf("----------------------------------------------\n");
    printf("Enter your choice : ");
    scanf("%d", &choice);
    switch (choice)
    {
        case 1: 
        {
            printf("\nSEARCH WORD IN THESAURUS\n");
            scanf("%s", query);
            strlwr(query);
            WordSearch(query);
            goto l1;
            break;
        }
        case 2:
        {
            l2: printf("Enter letter to view list using starting alphabet: ");
            scanf("%*c%c", &alpha);
            printf("----------------------------------------------\n");
            printf("\nWORDS STARTING WITH THE LETTER %c", alpha);
            printf("\n\n");
            tolower(alpha);
            if(alpha>='a' && alpha<='z')
            {
                AlphaSearch(alpha);
                printf("----------------------------------------------\n");
            }
            else
            {
                printf("\n");
                printf("Please enter valid alphabet !\n");
                printf("\n");
                goto l2;
            }
            goto l1;
            break;
        }
        case 3:
        {
            n=rand();
            WordOfDay(n);
            goto l1;
            break;
        }
        case 4:
        {
            printf("----------------------------------------------\n");
            printf("\nYOUR SEARCH HISTORY\n");
            History();
            printf("----------------------------------------------\n");
            goto l1;
            break;
        }
        case 5:
        {
            AddWord();
            goto l1;
        }
        case 6:
        {
            l3:printf("Choose pattern : \n\ta. *'text'\n\tb. 'text'*\n\tc. ?'text'\n");
            scanf("%s",query);
            len=strlen(query);
            if(query[0]=='*')
            {
                PatternSearch1(query);
                goto l1;
            }
            else if(query[len-1]=='*')
            {
                PatternSearch2(query);
                goto l1;
            }
            else
            {
                for(i=0; i<len; i++)
                {
                    if(query[i]=='?')
                    {
                        flag=1;
                    }
                }
                if(flag==1)
                {
                    PatternSearch3(query);
                    goto l1;
                }
                else
                {
                    printf("Enter valid pattern !\n");
                    goto l3;
                }
            }
            
            
        }
        case 7:
        {
            //User wishes to terminate the program
            srand(time(NULL));
            system ("clear");
            printf("Good-bye !!\n");
            printf("----------------------------------------------\n");
            exit(0);
        }
        default: 
        {
            printf("\n");
            printf("UH-OH! PLEASE ENTER VALID OPTION !!");
            printf("\n\n");
            printf("----------------------------------------------\n");
            goto l1;
            break;
        }

    }
}
//Function to search word in thesaurus from already existing list of words 
void WordSearch(char word[])
{
    int flag=0,spellFlag=0;
    char ans;
    char buf[100], syn1[100], syn2[100], syn3[100], syn4[100], ant1[100], ant2[100], fos[100];
    FILE* ptr = fopen("word.txt","r");
    if (ptr==NULL)
    {
        printf("No such file.");
    }
    while(fscanf(ptr,"%s %s %s %s %s %s %s %s",buf, syn1, syn2, syn3, syn4, ant1, ant2, fos) != EOF)
    {
        if(strcmp(buf, word)==0)
        {
            flag=1;
            printf("----------------------------------------------\n");
            printf("\nWORD- %s\n\n", buf);
            printf("SYNONYMS- %s, %s, %s, %s\n\n", syn1, syn2, syn3, syn4);
            printf("ANTONYMS- %s, %s\n\n", ant1, ant2);
            printf("FIGURE OF SPEECH- %s", fos);
            printf("\n");
            printf("----------------------------------------------\n");
        }        
        
    }
    //Incase the word doesn't exist, the user is given the choice to add/edit the word into the thesaurus
    //If the user chooses to add, AddWord function is called.
    if(flag==0)
    {
            printf("WORD NOT FOUND. Would you like to see similar words? \n");
            printf("(y/n) : \n");
            scanf("%*c%c",&ans);
            if(ans=='y')
            {
                spellFlag=spellCheck(word);
            }
            if(ans=='n')
            {
                printf("WORD NOT FOUND :(\nWe are expanding our database ! Would you like to add the details of the word %s ?\n", word);
                printf("(y/n) : \n");
                scanf("%*c%c", &ans);
                if(ans=='y')
                    AddWord();
            }
            
    }
    FILE* new = fopen("history.txt","a");
    if(new==NULL)
    { 
            printf("Oops, Couldn't add word to search history :(\n");
    }
    fprintf(new,"%s\n", word);
    fclose(new);
    

}
int spellCheck (char Word[])
{
    char buf[100],sample[100],correctedWord[100];
    char ans;
    int i,j,flag;
    FILE * ptr = fopen("spellWords.txt","r");
    int lenWord;
    lenWord=strlen(Word);
    if(ptr==NULL)
    {
        printf("Couldn't open the thesaurus at the moment.\n");
    }
    printf("Couldn't find the word ' %s ' in the thesaurus.\n", Word);
    printf("Did you mean one of the following: \n");
    while(fscanf(ptr,"%s %*s %*s %*s %*s %*s %*s %*s",buf) != EOF)
    {
        if(abs(lenWord - strlen(buf))<2)
        {
            if(Word[0]==buf[0])
            {
                flag=0;
                for(i=0,j=0;i<lenWord;i++,j++)
                {
                    if(buf[i]==Word[i])
                    {
                        sample[j]=buf[i];
                        flag++;
                    }
                }
                if(abs(lenWord-strlen(sample))<2 )
                {
                    printf("%s\n",buf);
                    strcpy(sample,"");
                }
            }
            else if(Word[0]!=buf[0])
            {
                flag=0;
                for(i=1,j=0;i<lenWord;i++,j++)
                {
                    if(buf[i]==Word[i])
                    {
                        sample[j]=buf[i];
                        flag++;
                    }
                }
                if(abs(lenWord-strlen(sample))<=2 )
                {
                    printf("%s\n",buf);
                    strcpy(sample,"");
                }
                
            }
        }
    }
    printf("\n");
    if(flag==0)
    {
        printf("No similar words found in our thesaurus.\n");
    }
    if(flag!=0)
    {
        printf("\nDo you want to search for one of the above words ?\n");
        printf("y/n : \n");
        scanf("%*c%c",&ans);
        if(ans=='y')
        {
            printf("Enter Word: ");
            scanf("%s",correctedWord);
            WordSearch(correctedWord);
            return 1;
        }
        else
        {
            return 0;
        }
    }
    fclose(ptr);
}

//Function to ask user to enter a single alphabet
//The program then displays list of words that exist in the thesaurus starting with entered alphabet

void AlphaSearch(char alpha)
{
    char buf[100], word[100];
    FILE* ptr = fopen("word.txt","r");
    if (ptr==NULL)
    {
        printf("no such file.");
        printf("\n");
    }
    while(fscanf(ptr,"%s %*s %*s %*s %*s %*s %*s %*s",buf) != EOF)
    {
        if(buf[0]==alpha)
        {
            printf("%s\n", buf);
        }
    }
    printf("\n");
}

//Function to display history of words searched 
//All the words searched from the first time the program is run are stored into a new file : "history.txt"
void History()
{
    int i;
    const unsigned l=256;
    char buf[100];
    FILE * new= fopen("history.txt","r");
    if(new==NULL)
    {
        printf("Oops couldn't display search history at the moment!\n ");
    } 
    while (fgets(buf,l,new))
    {
        printf("%s",buf);
    }
    printf("\n");
    fclose(new);
}

//Word of Day Function initializes a random number betwwen 1 - N (N: total number of lines in word.txt); 
//The function NumLines is called to find the total number of lines in the current thesaurus
//The file pointer variable then prints the details of the word at that particular line
void WordOfDay(int n)
{
    int i, num;
    FILE* ptr = fopen("word.txt","r");
    int c=NumLines(ptr)-1;
    num=n%c;
    if(num != 1)
    {
        char buf[100], syn1[100], syn2[100], syn3[100], syn4[100], ant1[100], ant2[100], fos[100];
        fseek(ptr, 0, SEEK_SET);
        for(i=0; i<num; i++)
        {
            fscanf(ptr,"%s %s %s %s %s %s %s %s",buf, syn1, syn2, syn3, syn4, ant1, ant2, fos);
        }
        printf("----------------------------------------------\n");
        printf(" WORD OF THE DAY !!\n");
        printf("\n\nWORD- %s\n", buf);
        printf("\nSYNONYMS- %s, %s, %s, %s\n", syn1, syn2, syn3, syn4);
        printf("\nANTONYMS- %s, %s\n", ant1, ant2);
        printf("\nFIGURE OF SPEECH- %s\n", fos);
        printf("----------------------------------------------\n");
    }
    else
    {
        n=rand();
        WordOfDay(n);
    }
}
//ADD WORD FUNCTION
//Function to enable user to add & edit new words according to user requirements
//Incase the word searched doesnot exist in the thesaurus , the program asks the user whether they wish to add to the list
//If the user chooses to do so, the function AddWord() is called
//If not the program returns to initial prompt message
void AddWord()
{
    FILE* ptr = fopen("word.txt","a");
    char word[100], syn1[100], syn2[100], syn3[100], syn4[100], ant1[100], ant2[100], fos[100];
    printf("\nADD WORD\n\n");
    printf("Enter Word: ");
    scanf("%s", word);
    strlwr(word);
    printf("Enter Synonym 1: ");
    scanf("%s", syn1);
    strlwr(syn1);
    printf("Enter Synonym 2: ");
    scanf("%s", syn2);
    strlwr(syn2);
    printf("Enter Synonym 3: ");
    scanf("%s", syn3);
    strlwr(syn3);
    printf("Enter Synonym 4: ");
    scanf("%s", syn4);
    strlwr(syn4);
    printf("Enter Antonym 1: ");
    scanf("%s", ant1);
    strlwr(ant1);
    printf("Enter Antonym 2: ");
    scanf("%s", ant2);
    strlwr(ant2);
    printf("Enter Figure of Speech: ");
    scanf("%s", fos);
    strlwr(fos);
    fseek(ptr,0, SEEK_END);
    fprintf(ptr, "\n%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s", word, syn1, syn2, syn3, syn4, ant1, ant2, fos);
    printf("Word has been successfully added !\n\n");
    printf("----------------------------------------------\n\n");
    fclose(ptr);

}
void PatternSearch1(char query[])
{
    FILE* ptr= fopen("word.txt", "r");
    char buf[100], buf1[100];
    int n=strlen(query);
    strrev(query);
    query[n-1]='\0';
    strrev(query);
    printf("Words that end with ' %s ' :\n",query);
    while(fscanf(ptr, "%s %*s %*s %*s %*s %*s %*s %*s", buf) != EOF)
    {
        strcpy(buf1, buf);
        if(strncmp(strrev(buf), strrev(query), n-1)==0)
        {
            printf("%s\n", buf1);
        }
    }
    fclose(ptr);
    
}

void PatternSearch2(char query[])
{
    FILE* ptr = fopen("word.txt","r");
    char buf[100];
    int n=strlen(query);
    query[n-1]='\0';
    printf("Words that start with ' %s '\n",query);
    while(fscanf(ptr,"%s %*s %*s %*s %*s %*s %*s %*s",buf) != EOF)
    {
        if(strncmp(buf, query, n-1)==0)
        {
            printf("%s\n", buf);
        }
    }
    fclose(ptr);
    
}

void PatternSearch3(char query[])
{
    FILE* ptr = fopen("word.txt","r");
    char str[100];
    char buf[100];
    int n=strlen(query), i, index;
    int flag;
    char l;
    for(i=0; i<n; i++)
    {
        if(query[i]=='?')
        {
            index=i;
        }
    }
    while(fscanf(ptr, "%s %*s %*s %*s %*s %*s %*s %*s", buf) != EOF)
    {
        if(strlen(buf)==n)
        {
            for(l='a'; l<='z'; l++)
            {
                query[index]=l;
                if(strcmp(buf, query)==0)
                {
                    printf("%s\n", buf);
                    flag=1;
                }
            }
        }   
    }
    fclose(ptr);
}

//Function to count total number of lines to create range for random number initalisation
int NumLines(FILE *ptr)
{
    int c=0;
    while(fscanf(ptr,"%*s %*s %*s %*s %*s %*s %*s %*s") != EOF)
    {
        c++;
    }
    return c;
}
