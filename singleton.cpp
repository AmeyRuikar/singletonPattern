#include<iostream>

using namespace std;


class   singleton{
    
        int resource;
        static  singleton   *instance;

  
            
            singleton(){
                
                resource = 10;
                countInstances++;
                
            }
        
        public:
            
            /*
                to check how many instances
                are being created on multiple calls to
                getInstance
            */
               
            static  int  countInstances;
               
            /*
                call this method directly without
                requiring an object.
                Also instance is static in nature
                
            */
            static  singleton   *   getInstance(){
                
                if( NULL == instance){
                    
                    instance = new  singleton();
                    
                }
                
                return  instance;
                
            }
            
            int getResource(){
                
                return  resource;
                
            }
    
    };

//allocate memory for the static member

singleton   *   singleton:: instance = 0;

int singleton::countInstances = 0;


int main(){
    
    //call static method
    
    cout<<"\nReosurce: "<<singleton::getInstance()->getResource()<<endl;
    cout<<"\nReosurce: "<<singleton::getInstance()->getResource()<<endl;
    
  
    cout<<"\nInstances: "<<singleton::countInstances<<endl;
    
    
    
    return  0;
}