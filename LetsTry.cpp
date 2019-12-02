#include <iostream>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

struct node{
    int number;
    node* next;
};

struct vertex {
    bool used=false;
    bool official=false;
    int level=0;
    node* List=NULL;
};

typedef pair<int, int> pi;

void add(vertex tab[], int x, int y){ //Adding edge from x to y to the graph
    node* edge=new node();
    edge->number=y;
    edge->next=tab[x].List;
    tab[x].List=edge;
    tab[x].level++;
}


int main(){
    string somestaff;
    cin>>somestaff;
    int n, m, k;
    cin>>n;
    cin>>k;
    vertex tab[n]; //Lets create table of vertexes
    for(int i=0;i<k;i++){ //Let's mark officials
        int x;
        cin>>x;
        tab[x].official=true;
    }
    cin>>m;
    for(int i=0;i<m;i++){ //Getting all of the meetings added to our graph
        int x,y;
        cin>>x;
        cin>>y;
        add(tab,x,y);
        add(tab,y,x);
    }
    // ---------------
    //End of data input
    priority_queue<pi, vector<pi>, greater<pi> > Q; //To keep our vertexes (ordered by 1st) - 1st of pair its level, second is number of vertex
    //pq.push(make_pair(10, 200));
    //pair<int, int> top = pq.top();

    for(int i=0;i<n;i++){
        Q.push(make_pair(tab[i].level,i));
    }
    /*
    for(int i=0;i<n;i++){
        pair<int, int> top=Q.top();
        Q.pop();
        cout<<top.second<<" of level"<<top.first<<endl;
    }
    */
    queue<pi> eQ;
    int vertexLeft=n;
    //cout<<"Lets start while"<<endl;
    while(vertexLeft>0 and !Q.empty()){
        //cout<<"Still running while, and vertexLeft= "<<vertexLeft<<endl;
        pair<int, int> current=Q.top(); //Getting the lowest level vertex from the priority queue
        Q.pop();
        int i=current.second;
        //cout<<"Before the 1st if"<<endl;
        if(!tab[i].used){ //If it hasn't been processed yet
            //cout<<"In the 1st if"<<endl;
            int min_level=INT_MAX;
            node* tmp=tab[i].List;
            int j=-1;
            //cout<<"Before the inner while"<<endl;
            while(!tmp==NULL){ //While there are any vertexes nearby
                if(tab[tmp->number].level<min_level && !tab[tmp->number].used){ //Looking for smallest lvl vertex possible, that haven't been marked as "used"
                    j=tmp->number; //Storing number of found vertex in j
                    min_level=tab[tmp->number].level;
                }
                tmp=tmp->next;
            }
            //cout<<"After the inner while"<<endl;
            if(j==-1){ //If there are no valid vertexes to pick and edge to
                vertexLeft--; //Just deleting this vertex
                tab[i].used=true; //Not needed in fact, but in case of further directed graph implementation
            }
            else{ //If we found vertex that creates our edge to process (i,j)
                //cout<<i<<" "<<j<<endl; //For now let's just print it out in here already instead of storing it in memory
                eQ.push(make_pair(i,j));
                tab[i].used=true;
                tab[j].used=true;
                vertexLeft-=2;
                //No we should get all adjacent vertexes and reinsert them into the priority queue with level lower by 1
                node* tmp=tab[i].List;
                while(!tmp==NULL){
                    if(!tab[tmp->number].used){
                        tab[tmp->number].level--;
                        Q.push(make_pair(tab[tmp->number].level,tmp->number));
                    }
                    tmp=tmp->next;
                }
                tmp=tab[j].List;
                while(!tmp==NULL){
                    if(!tab[tmp->number].used){
                        tab[tmp->number].level--;
                        Q.push(make_pair(tab[tmp->number].level,tmp->number));
                    }
                    tmp=tmp->next;
                }
            }
        }
    }
    int t=eQ.size();
    cout<<t<<endl;
    for(int i=0;i<t;i++){
        cout<<eQ.front().first<<" "<<eQ.front().second<<endl;
        eQ.pop();
    }


}


/*
4
2
0
1
3
0 2
0 3
1 2
*/
