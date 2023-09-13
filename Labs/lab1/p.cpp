#include <iostream> //As we need to print data
using namespace  std;
class Count{
    public:
    int count;
    Count(int c){count=c;}
    Count(){ count=0;}
};
void increment (Count c, int& times){
    c.count++;
    times++;
}
int main(){
   Count myCount;
   int times = 0;

   for(int i =0; i < 100; i++){
    increment(myCount,times);
    cout<<"my count is "<<myCount.count;
    cout<<"time is "<< times;
   }
    return 0;
}