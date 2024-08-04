#include <stdio.h>
#include <string.h>
#include <windows.h>
const int maxn=500;
struct counter{
  int num2;
  char what ;
  int number;
  char code[50]; 
  int ind;
};
typedef struct counter counter;
struct every{
  int child[300];
  int number;
  int index;
  int right_side;
};
typedef struct every every;
int mid;
char * erorr_not_find_file="Unable to open the file with the name(dirct):";
void type_result_then_end(char* message , char * filename){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (strcmp(filename,"succed")==0){
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        printf("%s",message);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        return ;
    }else{
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("%s %s",message,filename);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        return ;
    }
}
counter a[500],b[500];
void merg_sort(counter a[] ,counter b[],int l, int r, int mid){
    if (l+1==r) return ;
    //int ll=l;
    mid=(l+r)/2;
    merg_sort(a,b,l,mid,mid);
    merg_sort(a,b,mid,r,mid);
    int index=l , left_ind=l, right_ind=mid;
    while (index<r){
            if (left_ind==mid){
                b[index]=a[right_ind];
                right_ind++;
            }else if (right_ind==r){
                b[index]=a[left_ind];
                left_ind++;
            }else if (a[left_ind].number<=a[right_ind].number){
                b[index]=a[left_ind];
                left_ind++;
            }else{
                b[index]=a[right_ind];
                right_ind++;
            }
            index++;
    }
    for (int i=l; i<r; i++){
        a[i]=b[i];
    }
    return ;
}
void make(counter a[],every cc[], int l, int r ,int size, char x){
     int ll=l;
    while (l+1!=r){
        if (cc[l].right_side<cc[l+1].right_side){
        for (int j=0; j<cc[l].index; j++){
            a[cc[l].child[j]].code[a[cc[l].child[j]].ind]='0';
            a[cc[l].child[j]].ind++;
        }
        for (int j=0; j<cc[l+1].index; j++){
            a[cc[l+1].child[j]].code[a[cc[l+1].child[j]].ind]='1';
            a[cc[l+1].child[j]].ind++;
        }
        }else{
        for (int j=0; j<cc[l].index; j++){
            a[cc[l].child[j]].code[a[cc[l].child[j]].ind]='1';
            a[cc[l].child[j]].ind++;
        }
        for (int j=0; j<cc[l+1].index; j++){
            a[cc[l+1].child[j]].code[a[cc[l+1].child[j]].ind]='0';
            a[cc[l+1].child[j]].ind++;
        }   
        }
        cc[l+1].number+=cc[l].number;
        if (cc[l].right_side>cc[l+1].right_side){
           cc[l+1].right_side=cc[l].right_side;
        }
        for (int j=0; j<cc[l].index; j++){
            cc[l+1].child[cc[l+1].index]=cc[l].child[j];
            cc[l+1].index++;
        }
        for (int j=l+1; j<r-1; j++){
            if (cc[j].number>cc[j+1].number){
                every x;
                x=cc[j+1];
                cc[j+1]=cc[j];
                cc[j]=x;
            }else break;
        }
        l++;
    }
    char tmp;
    for (int i=ll; i<r; i++){
        for (int j=0; j<a[i].ind/2; j++){
            tmp=a[i].code[j];
           a[i].code[j]=a[i].code[a[i].ind-j-1];
           a[i].code[a[i].ind-j-1]=tmp;
        }
    }
}
void make_sort_table(counter a[],long long per[], int l, int r ,int size, char x){
   // printf("UU\n");
  // printf("%d %d \n",l,r);
   if (r<=1) return ;
    if (r-l+1!=size) {
           for (int i=l; i<r; i++){
            a[i].code[a[i].ind]= x ;
            a[i].ind++;
           }
    }
    if (l+1==r) return ;
    long long sum=per[r-1]-per[l-1];
    long long check;
    int mid;
    int ll=l, rr=r;
    while (ll+1<rr){
        mid=(ll+rr)/2;
        check=per[mid]-per[l-1];
        if(check*2<=sum){
            ll=mid;
        }else rr=mid;
    }
    make_sort_table(a,per,l,rr,size,'0');
    make_sort_table(a,per,rr,r,size,'1');
}
int put_gide_to_a(counter a[],char* gide_filename){
  FILE *gide;
  gide=fopen(gide_filename,"r");
  if (gide==NULL){
        //printf("not able to open the file");
        return 0;
    }
    char c;
    int last_ind=1;
    while (fscanf(gide,"%c",&c)!=EOF){
        a[last_ind].what=c;
        fscanf(gide,"%c",&c);
        while (fscanf(gide,"%c",&c)!=EOF){
            if (c=='\n') break;
            a[last_ind].code[a[last_ind].ind]=c;
            a[last_ind].ind++;
        }
        last_ind++;
    }
    fclose(gide);
    return last_ind;
}
void backing_to_intial_file(counter a[],char *comppersed_filename,char *gide_filename ,char *initial_filename){
    FILE *file_bac,*myf;
    int last_ind=put_gide_to_a(a,gide_filename);
    if (last_ind==0){
        type_result_then_end(erorr_not_find_file,gide_filename);
        return ;
    }
    myf=fopen(comppersed_filename,"r");
    file_bac=fopen(initial_filename,"w");
    char c;
    if (myf==NULL){
        type_result_then_end(erorr_not_find_file,comppersed_filename);
        return ;
    }
    char check[100];
    for (int i=0; i<100; i++) check[i]='\0';
    int size_char=0;
    c='8';
    while(fscanf(myf,"%c",&c)!=EOF){
        int is_it = 0;
        int char_c_size=c-64;
        int tekrar =32;
        while (tekrar>0){
            if (char_c_size>=tekrar){
            check[size_char]='1';
            char_c_size-=tekrar;
            }else{
                check[size_char]='0';
            }
            tekrar/=2;
        size_char++;
        for (int i=1; i<last_ind; i++){
            if(strcmp(check,a[i].code)==0){
                fprintf(file_bac,"%c",a[i].what);
                while (size_char>=0){
                    check[size_char]='\0';
                    size_char--;
                }
                size_char=0;
                break;
            }
        }
        }
    }
    type_result_then_end("Your file has decompressed successfuly","Success");
    fclose(myf);
    fclose(file_bac);
    return ;
}
void copperes_given_file(every cc[],counter a[], counter b[],long long per[],char* given_filename, char*goal_filename, char*gide_filename){
    FILE *myfile,*goal_file,*gide_file;
    myfile=fopen(given_filename,"r");
    char c;
    int last_ind=0;
        if (myfile==NULL){
        type_result_then_end(erorr_not_find_file,given_filename);
        return ;
    }
    last_ind=1;
    while(fscanf(myfile,"%c",&c)!=EOF){
        int is_it = 0;
        for (int i=1; i<last_ind; i++){
            if (a[i].what==c){ is_it=1; a[i].number++; break;}
        }
        if (is_it==0){
            a[last_ind].what=c;
            a[last_ind].number=1;
            last_ind++;
        }
    }
    merg_sort(a,b,1,last_ind,1);
    per[0]=0;
    for (int i=1; i<last_ind; i++){
        per[i]=per[i-1]+a[i].number;
        a[i].ind=0;
    }
    for (int i=1; i<last_ind; i++){
        cc[i].index=0;
        cc[i].number=a[i].number;
       cc[i].child[cc[i].index]=i;
        cc[i].index++;
        a[i].num2=a[i].number;
        cc[i].right_side=i;
        b[i]=a[i];
    }
    make(a,cc,1,last_ind,last_ind,'0');
    //make_sort_table(a,per,1,last_ind,last_ind,'0');
    myfile=fopen(given_filename,"r");
    goal_file=fopen(goal_filename,"w");
    gide_file=fopen(gide_filename,"w");
    for (int i=1; i<last_ind; i++){
        fprintf(gide_file,"%c\n%s\n",a[i].what,a[i].code);
    }
    int code_jadid_int=64;
    int num_char=32;
    char code_jadid;
    int count=0; 
    while(fscanf(myfile,"%c",&c)!=EOF){
        //count++;
        for (int i=1; i<last_ind; i++){
            if (a[i].what==c){
                count+=a[i].ind;
                for (int j=0; j<a[i].ind; j++){
                    int hj=a[i].code[j]-('0');
                    code_jadid_int+=hj*num_char;
                    num_char/=2;
                    if (num_char==0){
                        code_jadid=code_jadid_int;
                        fprintf(goal_file,"%c",code_jadid);
                        num_char=32;
                        code_jadid_int=64;
                    }
                }
                break;
            }
        }
    }
    if (count%6){
        code_jadid=code_jadid_int;
        fprintf(goal_file,"%c",code_jadid);
    }
    type_result_then_end("Your file has compressed successfuly","Success");
    fclose(myfile);
    fclose(goal_file);
    fclose(gide_file);
    return ;
}
int main(int argc , char* argv[]){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char * given_filename , *gide_filename, *goal_filename , *initial_filename;
    given_filename="C:\\Users\\HP-m03\\Desktop\\mabani\\input.txt";
    gide_filename="C:\\Users\\HP-m03\\Desktop\\mabani\\gide.txt";
    goal_filename="C:\\Users\\HP-m03\\Desktop\\mabani\\gig.txt";
    initial_filename="C:\\Users\\HP-m03\\Desktop\\mabani\\real_file.txt";
    if (argc<2){
        printf("WTF bro");
        return 0;
    }
    if(strcmp(argv[1],"help")==0){
        printf ("here is some decuments about this program activties and options :\n");
        printf ("for working with this program you should type like this :\n");
        printf ("<name of program> <1 or 2> <first filename (or dirc)> <second filename> <third filename>\n");
        printf ("if you type <1> you actualy choose to compress  your file , so then you should print name of three file :\n");
        printf("as the First one should type name or dirct of your initial file\n");
        printf("as the Second one you should pik name or dirct for the gide of compressed file\n");
        printf("as the Third one you should pik name or dirct for the compressed file\n");
        printf ("if you type <2> you actualy choose to decompress  your file , so then you should print name of three file :\n");
        printf("as the First one should type name or dirct of your compressed file\n");
        printf("as the Second one should type name or dirct of the gide of compressed file\n");
        printf("as the Third one you should pik name or dirct for the recoveried file\n");
    }else
    if(strlen(argv[1])!=1 || argc!=5) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("your choosen option is not recognize");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        return 0;
    }
    long long per[maxn];
    per[0]=0;
    every cc[maxn];
    switch (argv[1][0])
    {
    case '1':
        given_filename=argv[2];
        goal_filename=argv[4];
        gide_filename=argv[3];
        copperes_given_file(cc,a,b,per,given_filename,goal_filename,gide_filename);
        break;
    case '2':
        goal_filename=argv[2];
        gide_filename=argv[3];
        initial_filename=argv[4];
        backing_to_intial_file(a,goal_filename,gide_filename,initial_filename);
        break;
    default:
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("your choosen option is not recognize");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        return 0;
        break;
    }
    //counter a[400],b[400];
   //copperes_given_file(cc,a,b,per,given_filename,goal_filename,gide_filename);
   //nemd.exe 2 C:\\Users\\HP-m03\\Desktop\\mabani\\gig.txt C:\\Users\\HP-m03\\Desktop\\mabani\\gide.txt C:\\Users\\HP-m03\\Desktop\\mabani\\real.txt
    return 0;
}