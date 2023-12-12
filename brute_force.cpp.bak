#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstring>
using namespace std;

int ln;

int countDistinct(int *arr, int n)
{
    int res = 1;

    for (int i = 1; i < n; i++) {
	int j = 0;
        for (j = 0; j < i; j++)
            if (arr[i] == arr[j])
                break;

        if (i == j){
            res++;
	}
    }
    return res;
}

char* getfn(int it, char* b, char* c)
{
    char * fn = new char[7+std::strlen(b)+strlen(c)+5];
    if (it == 1){
        std::strcpy(fn,"guess_");
    }
    else if(it == 2){
        std::strcpy(fn,"ranks_");
    }
    else if(it == 3){
        std::strcpy(fn,"combo_");
    }
    std::strcat(fn,b);
    std::strcat(fn,"_");
    std::strcat(fn,c);
    std::strcat(fn,".txt");

    return fn;
}

double get_maxt(int *rank, double *guess, int len) {
    int nrt = countDistinct(rank,len); // get number of unique ranks for this solution
    double maxg[nrt];
    double maxt=0;
    for (int r=0;r<nrt;r++){ // for every rank
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


void recursively_fill(int *ranks, int *combo, double *guess, int len, int nr, int tot, int last, int index, int *combos, double *guesses) {
    for (int i=0;i<nr;i++){
        combo[index]=ranks[i];
	if (index == last){
//	     guesses[i+index]=get_maxt(combo,guess,len);    
	     for (int j=0;j<len;j++){ 
	        cout << ln*len+j<< ", ";
	        combos[ln*len+j]=combo[j];
	     }
             ln++;
//	     cout<<ln <<endl;
//	     cout << guesses[i+index] << endl;
	}
    else
	recursively_fill(ranks, combo, guess, len, nr, tot, last, index+1, combos, guesses);
    }
}
     

void get_all_combos(int len, int nr, double *guess, int *ranks, char *fn){

    int tot = int(pow(len,nr));
    int combo[len]={-1};
    double guesses[tot]={-1};
    int combos[len*tot]={-1};
    ln=0;
    recursively_fill(ranks,combo,guess,len, nr,tot,len-1,0,combos,guesses);
    cout<< "filled" << endl; 
    ofstream myfile;
    myfile.open(fn);
    cout << "------------------------------------------------" << endl;
    for (int i=0;i<tot;i++){
        for (int j=0;j<len;j++){
            cout << combos[i*len+j] << " " ; 
    }
        cout << endl;
    }
	//cout << guesses[i] << endl;
    myfile.close();
    }


int main( int argc, char* argv[]) {

    if (argc!=5){
    cout<< "usage: ./a.out Nrank Nbox mean stddev" <<endl;
    return 0;
    }
    else{
    auto start_time = std::chrono::high_resolution_clock::now();
  
    // get inputs 
    int nr=atoi(argv[1]);
    int N=atoi(argv[2]);
    int mean=atoi(argv[3]);
    int stddev=atoi(argv[4]);

    // initialize arrays
    double guess[N];
    int ranks[nr];
    // generate filenames
    char * guess_fn = getfn(1,argv[3],argv[4]);
    char * ranks_fn = getfn(2,argv[3],argv[4]);
    char * combo_fn = getfn(3,argv[3],argv[4]);
    ofstream myfile;
    myfile.open(ranks_fn);

    for (int i = 0; i<nr;i++){
        ranks[i]=i;
        myfile << ranks[i] << " ";
    }
    myfile.close();

    //generate array of guesses with normal distribution
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(mean,stddev);
    myfile.open(guess_fn);
    for (int i=0;i<N;i++){
        guess[i]=distribution(generator);
	if (guess[i]<0){
	    cout<<"negative guess, make mean higher or standard devation smaller"<<endl;
            exit(0);
	}
	myfile << guess[i] << " ";
    }
    myfile.close();
    get_all_combos(N,nr,guess,ranks,combo_fn);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

    cout << "Time taken: " << elapsed_time.count() << " seconds" << endl;


    return 0;
}
}
