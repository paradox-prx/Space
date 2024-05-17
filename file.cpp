#include<iostream>
#include<fstream>


using namespace std;
void setScore(int num,string nm){

fstream file;
string name,score;
file.open("score.txt",ios::app);
file<<num<<endl;
file<<nm<<endl;
file.close();
file.open("score.txt",ios::in);
file>>name;
int count=0;
while(!file.eof()){
    file>>name;
    count++;
}
count/=2;

string* names=new string[count];
string* scores=new string[count];
file.close();
file.open("score.txt",ios::in);
for(int i=0;i<count;i++){
    file>>name;
    scores[i]=name;
    file>>name;
    names[i]=name;
}

file.close();

for(int i=0;i<count;i++){
    bool change=0;
    for(int j=0;j<count-i-1;j++){
        int num1=stoi(scores[j]);
        int num2=stoi(scores[j+1]);
        if(num1<num2){
            string temp1=scores[j];
            string temp2=names[j];

            scores[j]=scores[j+1];
            names[j]=names[j+1];

            scores[j+1]=temp1;
            names[j+1]=temp2;
            change=1;
        }
    }
}

file.open("score.txt",ios::out);
for(int i=0;i<count;i++){
    file<<scores[i]<<endl;
    file<<names[i]<<endl;
}
file.close();



}





int main(){
    setScore(200,"Izhan");
    setScore(1000,"Abdullah");
    setScore(800,"Junaid");
    setScore(400,"Hamza");
    setScore(274,"Ahmed");
    setScore(1200,"Dilli");
    setScore(600,"Fasseh");
    setScore(50,"Hashir");
    setScore(750,"Mahtab");
    setScore(600,"Myke");
    

    return 0;
}