#include<iostream>
#include<pthread.h>

using namespace std;




class   singleton{
    
        int resource;
        static  singleton   *instance;
        static  pthread_mutex_t lock;
            
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
 
                    /*
                        thread safe
                    
                    */
                    
                    pthread_mutex_lock(&lock);
                    
                        if( NULL == instance)
                        {
                            instance = new  singleton();
                        }
 
                    pthread_mutex_unlock(&lock);
                    
                }
                
                return  instance;
                
            }
            
            int getResource(){
                
                return  resource;
                
            }
    
    };



//allocate memory for the static members

singleton   *   singleton:: instance = 0;

int singleton::countInstances = 0;

pthread_mutex_t singleton::lock;

/*
    function trying to access the
    instance of singleton class.
    Multiple threads might try to
    create the new instance.

*/

void    *   getAccess(void  * arg){
    
    int pid = *(int *)arg;
    
    cout<<"\nPID: "<<pid<<" accessed the instance with resource value: "<<singleton::getInstance()->getResource()<<endl<<cout.flush();
    
    cout<<"\nInstances: "<<singleton::countInstances<<endl<<cout.flush();
    
    pthread_exit(0);

}



int main(){
    
    //call static method
    
    pthread_t   pid;
    
    cout<<"\nReosurce: "<<singleton::getInstance()->getResource()<<endl;
    cout<<"\nReosurce: "<<singleton::getInstance()->getResource()<<endl;
    
    
    for(int i=0; i < 5; i++){
        
        pthread_create(&pid, NULL, getAccess,(void *) &i);
        sleep(1);
        
    }
  

    pthread_join(pid, NULL);
    
    
    return  0;
}