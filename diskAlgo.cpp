#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

/* algorithm */
int fcfsAlgo(int , int , vector<int>& );
int sstfAlgo(int , int , vector<int>& );
int scanAlgo(int , int , vector<int>& );
int cscanAlgo(int , int , vector<int>& );

/* Sector Size */
int sectorMax = 300;
int sectorMin = 0;

/* algorithm num */
enum algo {
    FCFS = 1,
    SSTF,
    SCAN,
    CSCAN
};

enum sectorPart{
    sectorPrePart = 1,
    secotrHeadPart,
    secotrTracePart
};

/* get test file location */
string fatchFile(){
    string configfile = "../test.txt"; // /filelocation/filename
    return configfile;
}

/* get the test data */
void getData(int& prePosition , int& head, vector<int>& slot, const string& configFile){
    vector<string> array;
    string space_delimter=" ";
    string sectorStr;
    size_t sectorPosition;
    try {
        int data=0;
        ifstream fin(configFile);
        while (getline(fin, sectorStr)){
            data++;
            while((sectorPosition = sectorStr.find(space_delimter)) != string::npos){
                array.push_back(sectorStr.substr(0, sectorPosition));
                sectorStr.erase(0, sectorPosition + space_delimter.length());
            }
            array.push_back(sectorStr.substr(0, sectorPosition));
            for(string s:array){
            }
            switch (data) {
                case sectorPrePart:
                    prePosition = stoi(array[0]);
                    cout << "sloct pre-location: " << prePosition << endl;
                    array.pop_back();
                    break;
                case secotrHeadPart:
                    head = stoi(array[0]);
                    cout<<"sloct current-location: "<< head<<endl;
                    array.pop_back();
                    break;
                case secotrTracePart:
                    cout<<"next-location:";
                    for(string s:array){
                        slot.push_back(stoi(s));
                        cout<<" "<<s;
                    }
                    cout<<endl;
                default:
                    break;
            }
        }
    }catch (std::exception &e) {
        cout<<"exception: " << e.what()<<endl;
    }
}

/* fcfsAlgo */
int fcfsAlgo(const int prePosition, int head, vector<int>& sectorProsition){
    int total = 0;
    for(auto trace:sectorProsition){
        total += abs(head - trace);
    }

    return total;
}


/* algo sstf */
int sstfAlgo(const int prePosition, int head, vector<int>& sectorProsition){
    /****** init *******/
    int total = 0;
    int tempTracePoint = head;
    vector<int> tracePosition; //the head trace postion

    /****** implement *******/
    sort(sectorProsition.begin(), sectorProsition.end());
    int size = sectorProsition.size();

    for(uint32_t i = 0; i<size;i++){
        int deviation = abs(tempTracePoint - sectorProsition[0]);
        int po = 0;
        for(int j =0; j<sectorProsition.size();j++) {
            if (deviation > abs(tempTracePoint - sectorProsition[j])) {
                deviation = abs(tempTracePoint - sectorProsition[j]);
                po = j;
            }

        }
        tempTracePoint = sectorProsition[po];
        total += deviation;
        tracePosition.push_back(tempTracePoint);
        sectorProsition.erase(sectorProsition.begin()+po);
    }


    /****** update return tracepath *******/
    for(auto trace:tracePosition){
        sectorProsition.push_back(trace);
    }
    return total;
}

/* algo scan */
int scanAlgo(const int prePosition, int head, vector<int>& sectorProsition ){
    /* sort & inint */
    sort(sectorProsition.begin(), sectorProsition.end());
    int total=0;
    bool traceDirect = head > prePosition;
    vector<int> left;
    vector<int> right;

    /* create search right & left */
    for(auto s:sectorProsition){
        if(s<head){
            left.push_back(s);
        } else
            right.push_back(s);
    }
    size_t size = sectorProsition.size();

    /* clear the return sectorOrder*/
    for(auto i=0;i<size;i++){
        sectorProsition.pop_back();
    }

    /* sort the scan order */
    if(traceDirect){
        sort(left.begin(),left.end(),[=](auto a,auto b){
            return a>b;
        });
        sort(right.begin(),right.end(),[=](auto a,auto b){
            return a<b;
        });
    } else{
        sort(left.begin(),left.end(),[=](auto a,auto b){
            return a>b;
        });
        sort(right.begin(),right.end(),[=](auto a,auto b){
            return a<b;
        });
    }

    /* trace the sector position */
    if(traceDirect){
        for(int i=0;i<right.size();i++){
            total += abs(head-right[i]);
            head = right[i];
            sectorProsition.push_back(head);
        }
        head = sectorMax;
        for(int i=0;i<left.size();i++){
            total += abs(head-left[i]);
            head = left[i];
            sectorProsition.push_back(head);
        }
    } else{
        for(int i=0;i<left.size();i++) {
            total += abs(head - left[i]);
            head = left[i];
            sectorProsition.push_back(head);
        }
        head = sectorMin;
        for(int i=0;i<right.size();i++){
            total += abs(head-right[i]);
            head = right[i];
            sectorProsition.push_back(head);
        }
    }
    return total;

}


/* c-scan */
int cscanAlgo(const int prePosition, int head, vector<int>& sectorProsition ){

    /* sort & inint */
    sort(sectorProsition.begin(), sectorProsition.end());
    int total=0;
    bool traceDirect = head > prePosition;
    vector<int> left;
    vector<int> right;

    /* create search right & left */
    for(auto s:sectorProsition){
        if(s<head){
            left.push_back(s);
        } else
            right.push_back(s);
    }
    size_t size = sectorProsition.size();

    /* clear the return sectorOrder*/
    for(auto i=0;i<size;i++){
        sectorProsition.pop_back();
    }

    /* sort the scan order */
    if(traceDirect){
        sort(left.begin(),left.end(),[=](auto a,auto b){
            return a<b;
        });
        sort(right.begin(),right.end(),[=](auto a,auto b){
            return a<b;
        });
    } else{
        sort(left.begin(),left.end(),[=](auto a,auto b){
            return a>b;
        });
        sort(right.begin(),right.end(),[=](auto a,auto b){
            return a>b;
        });
    }


    /* trace the sector position */
    if(traceDirect){
        for(int i=0;i<right.size();i++){
            total += abs(head-right[i]);
            head = right[i];
            sectorProsition.push_back(head);
        }
        head = sectorMax;
        for(int i=0;i<left.size();i++){
            total += abs(head-left[i]);
            head = left[i];
            sectorProsition.push_back(head);
        }
    } else{
        for(int i=0;i<left.size();i++) {
            total += abs(head - left[i]);
            head = left[i];
            sectorProsition.push_back(head);
        }
        head = sectorMin;
        for(int i=0;i<right.size();i++){
            total += abs(head-right[i]);
            head = right[i];
            sectorProsition.push_back(head);
        }
    }
    return total;
}

/* main code */
int main() {
    /* init data */
    uint32_t choose;
    vector<int> sectorOrder;
    int preHead, head;
    int (*func)(int, int, vector<int>&);
    getData(preHead, head, sectorOrder, fatchFile());

    /* commmand line interfance */
    cout<<"-----------"<< endl;
    cout<< "1: FCFS, 2:SSTF, 3: SCAN, 4:CSCAN"<<endl;
    cout<<"choose the algo: ";
    while (cin>> choose){

        /* algorithm logic */
        //cout<< "exec algorithm"<<endl;
        switch (choose) {
            case FCFS:
                func = &fcfsAlgo;
                break;
            case SSTF:
                func = &sstfAlgo;
                break;
            case SCAN:
                func = &scanAlgo;
                break;
            case CSCAN:
                func = &cscanAlgo;
                break;
            default:
                cout<<"plz input the algorithm number";
                continue;
        }
        break;
    }

    /* print data */
    cout<<endl<<"total: "<<func(preHead, head, sectorOrder)<<endl;
    cout<<"the tracing Positions: ";
    for(auto value:sectorOrder){
        cout<<value<<" ";
    }

    return 0;
}
