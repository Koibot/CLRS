#include<Windows.h>
#include<iostream>
#include<vector>
#include<map>
#include<time.h>
#include<algorithm>

using namespace std;

class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        int min = 1000;
        // for(vector<int>::iterator iter = arr.begin(); iter!= arr.end(); ++iter){
        //     if(*it<min){
        //         min = *iter;
        //     }
        // }
        



        //if(min <0){
            // for(vector<int>::iterator iter = arr.begin(); iter != arr.end(); ++iter){
            //     *iter += min;
            //     //cout<<*iter<<", ";
            // }
        //}
        int* occu = new int[2000]();
        for(vector<int>::iterator iter = arr.begin(); iter != arr.end(); ++iter){
            occu[*iter+1000] += 1;
        }


        //bool ans = true;
        
        for(int i = 0; i < 2000; i++){
            if(occu[i]==0){
                continue;
            }
            for(int j = 0; j < 2000; j++){
                if(i==j){
                    continue;
                }
                 if(occu[i]==occu[j]){
                    //cout<<"identical occurrence found"<<endl;
                    //ans = false;
                    //cout<<"occurrences of "<<i<<" and " << j << " are both "<<occu[i]<<endl;
                    //break;
                    return false;
                }//end if
            }//end j
               
            //if(ans==false){
            //    break;
            //}
        }//end i
        delete []occu;

        return true;
    }
};


class Solution_2 {

public:

    bool uniqueOccurrences(vector<int>& arr) {

        map<int,int>myMap;

        for(int i=0;i<arr.size();i++){

            myMap[arr[i]]++;

        }

        int temp=0;

        vector<int>v;

        for (auto i : myMap) {

            v.push_back(i.second);

        }

        sort(v.begin(),v.end());

        for(int i=0;i<v.size();i++){

            if(v[i]==temp)

                return false;

            else

                temp=v[i];

        }

        return true;

             

    }

};

void main(){
    vector<int> arr = {25,25,25,25,25,25,25,2,2,2,2,2,2,2,2,2,2,2,2,2,25,36,36,256,256,256,256,256,256,256,256,256,256,256,256,256,999,2,999,25,42,64,64,64,64,64,64,64,999,2,17,17,17,17,256,121,131,131,131,131,131,131,131,131,131,131,121,121,121,121,121};
    Solution s;
    clock_t start = clock();
    double time_s1 = 0;
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;  
    LARGE_INTEGER nEndTime;  
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);
    s.uniqueOccurrences(arr);
    QueryPerformanceCounter(&nEndTime);
    //clock_t end = clock();
    time_s1=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    //cout<<"run "<<double(end-start)/CLOCKS_PER_SEC<<" ms"<<endl;
    cout<<"run "<<time_s1*100<<" ms"<<endl;
    //cout<< ans << endl;

    Solution_2 s2;
    clock_t start_s2 = clock();
    double time_s2 = 0;
    LARGE_INTEGER nFreq_s2;
    LARGE_INTEGER nBeginTime_s2;  
    LARGE_INTEGER nEndTime_s2;  
    QueryPerformanceFrequency(&nFreq_s2);
    QueryPerformanceCounter(&nBeginTime_s2);
    s2.uniqueOccurrences(arr);
    QueryPerformanceCounter(&nEndTime_s2);
    time_s2=(double)(nEndTime_s2.QuadPart-nBeginTime_s2.QuadPart)/(double)nFreq_s2.QuadPart;
    //clock_t end_s2 = clock();
    //cout<<"run "<<double(end_s2-start_s2)/CLOCKS_PER_SEC<<" ms"<<endl;
    cout<<"run "<<time_s2*100<<" ms"<<endl;

    system("pause");
}