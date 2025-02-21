#include <iostream>

using namespace std;

int main(int argc,char * argv[]){
    if(argc == 1){
        cout << "Please input numbers to find average.";
    }else{
        float sum;
        float count = 0;
        for(int i = 1;i < argc;i++){
            sum += atof(argv[i]);
            count++;
        }
        cout << "---------------------------------" << endl;
        cout << "Average of " << argc - 1 << " numbers = " << sum/count << endl;
        cout << "---------------------------------";
    }
    return 0;
}