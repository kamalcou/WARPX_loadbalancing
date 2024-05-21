#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstring>
#include "mpi.h"
using namespace std;
bool array_true=false;

char* getfn(int it, char* b, char* c, char* d)
{
    char * fn = new char[20+std::strlen(b)+strlen(c)+5];
    if (it == 1)std::strcpy(fn,"guess_"); 
    else if(it == 2)std::strcpy(fn,"ranks_");

    else if(it == 3)std::strcpy(fn,"combo_");
    else if(it == 4)std::strcpy(fn,"norep_");

    std::strcat(fn,b);
    std::strcat(fn,"_");
    std::strcat(fn,c);
    std::strcat(fn,"_it");
    std::strcat(fn,d);
    std:cout<<d;
   

    if((it==3)||(it==4)){
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	char r [6+sizeof(char)];
        std::sprintf(r,"%d",world_rank);	
	std::strcat(fn,".");
	std::strcat(fn,r);
    }
     std::strcat(fn,".txt");
    return fn;
}

double get_maxt(int *rank, double *guess, int len,int nr) {
    double maxg[nr]={0};
    double maxt=0;
    for (int r=0;r<nr;r++){ // for every rank
        for (int i=0;i<len;i++) { //for every element
            if(rank[i]==r){
                maxg[r]+=guess[i]; // this guess is on rank r so add to the sum
            }
        }
        if (maxg[r]>maxt){
            maxt=maxg[r];
        }
    }
    return maxt;
}

int* ternary(int n, int b,int len) {
    int * nums = new int[len];
    for(int i=0;i<len;i++) nums[i]=0;
    int L=len;
    while (n){
        auto dv= std::div(n,b);
        n = dv.quot;
	int r = dv.rem;
	if (L==0){
            nums[0]=-1;
	    break;
	}
	L--;
        nums[L]=r;
    }
    return nums;
 
}
    
void basechange_fill(int len, int nr,double *guess,ofstream& myfile) {
    int world_size,world_rank;

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    double nmin=double(world_rank)/double(world_size)*pow(nr,(len));
    double nmax=(world_rank+1.0)/double(world_size)*pow(nr,(len));
    int i=nmin;
    while((i>=nmin) && (i<nmax)){
        int * combo = new int[len+1];
        for (int j=0;j>len;j++){
            combo[j] = 0;
        }
        //check there is more than one rank
        if (nr!=1){
            combo=ternary(i,nr,len);
            if (combo[0]==-1) {	    
                cout<<"Nmax too large"<<endl;
		exit(0);
	    }
        }
        double maxt=get_maxt(combo,guess,len,nr);
        for (int j=0;j<len;j++){
	    myfile<<combo[j]<<" ";
	}
	myfile<<maxt<<endl;
	i++;
	}
}


void get_all_combos(int len, int nr, double *guess, int *ranks, char *fn){

    double tot = double(pow(len,nr));
    int combo[len];
    int ln=0;

    ofstream myfile;
    myfile.open(fn);
    basechange_fill(len, nr,guess,myfile);
    myfile.close();
    return;
    }

void countFreq(int arr[], int n, int *ranks, int *freqs)
{
    // Mark all array elements as not visited
    vector<bool> visited(n, false);
 
    // Traverse through array elements and
    // count frequencies
    for (int i = 0; i < n; i++) {
 
        // Skip this element if already processed
        if (visited[i] == true)
            continue;
 
        // Count frequency
        int count = 1;
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                visited[j] = true;
                count++;
            }
        }
        ranks[i]=arr[i];
        freqs[i]=count;
    }
}

void eliminate_repetitions(int len, int nr, char *fn, char *tfn){
    
    ifstream myfile;
    myfile.open(fn);
    ofstream myfile2;
    myfile2.open(tfn);

    std::string line;
    while(std::getline(myfile,line))
    {
	bool write=true;
        int * combo = new int[len];
	std::string r;
	double guess;
	int j=0;
	int z=0;
        for (int i=0;i<line.length();i++)
	{
	    if((line[i]!=' ')&&(i<line.length()-1))
	    {
                if(z==0){
		    r=line[i];
		}
		else{
                    r+=line[i];
		}
		z++;
	    }
	    else
	    { //we have reached a space or the end of the line, store what we read and reset r
                if(j<len and i>0)
		{
                    combo[j]=stoi(r);
		    z=0;
	            j++;
		}
		if(j==len)
		{
                    guess=stof(r);
		}
	    }
	}
      

	int * ranks = new int[len];
	int * freqs = new int[len];
	countFreq(combo,len,ranks,freqs);
	for (int i=0;i<len;i++)
	{
            for (int j=0;j<len;j++)
		{
		if((freqs[i]==freqs[j])&(i>j)&(ranks[i]<ranks[j]))
			write=false;
		}
	}
	if(write)	
	{
	    myfile2<<line<<endl;
	}
	
	//cout<< guess<<endl;//guess is at lower precision than originally, should be to 6sf		   
    }
    myfile2.close();
    myfile.close();
}


int main( int argc, char* argv[]) {


    auto start_time = std::chrono::high_resolution_clock::now();

    char *itn = new char[10];
    if (argc!=5 and argc!=6){
    cout<< "usage: ./a.out Nranks Nbox_per_rank mean stddev" <<endl;
    return 0;
    } 
    else{

    // get inputs 
    int nr=atoi(argv[1]); //nr= number of ranks
    int N=atoi(argv[2])*nr; //boxes per rank is the new input
    int mean=atoi(argv[3]); 
    int stddev=atoi(argv[4]);
    if(argc==6){
        itn=argv[5];
    } 
    else{
	    std::strcpy(itn,"0\0");
    }
    // initialize arrays
    double guess [N];
    int ranks [N];

    //Initialize MPI
    MPI_Init(NULL,NULL);
    // generate filenames
    char * guess_fn = getfn(1,argv[3],argv[4],itn);
    char * ranks_fn = getfn(2,argv[3],argv[4],itn);
    char * combo_fn = getfn(3,argv[3],argv[4],itn);
    char * temps_fn = getfn(4,argv[3],argv[4],itn);
   
    ofstream myfile;
    myfile.open(ranks_fn);
    for (int i = 0; i<nr;i++){
        ranks[i]=i;
        myfile << ranks[i] << " ";   // write number of ranks in the ranks_meanValue_stdValue
    }
    myfile.close();

    //generate array of guesses with normal distribution
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(mean,stddev);
    myfile.open(guess_fn);
    for (int i=0;i<N;i++){
        guess[i]=distribution(generator);  //guess value based on the normal distribution
	if (guess[i]<0){
	    cout<<"negative guess, make mean higher or standard devation smaller"<<endl;
            exit(0);
	}
	myfile << guess[i] << " ";
    }
    myfile.close();
    get_all_combos(N,nr,guess,ranks,combo_fn);
//    eliminate_repetitions(N,nr,combo_fn,temps_fn);
    MPI_Finalize();
    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

    cout << "Time taken: " << elapsed_time.count() << " seconds" << endl;

    return 0;
}
}
