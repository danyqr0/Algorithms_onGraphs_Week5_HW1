//============================================================================
// Name        : Algorithms_onGraphs_Week5_HW1.cpp
// Author      : Daniel Ramirez
// Version     :
// Copyright   : HW1_Week5
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <cstdlib>
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <utility>
#include <set>
#include <cmath>
#include <iomanip>

using namespace std;
using std::vector;

typedef pair<int,int> Pair;
typedef pair< double, Pair> Pair_double;

class Graph{
  private:
    int V;
    vector<Pair> v_xy;
    vector<Pair_double> xy_w;
  public:
    Graph(int v):V(v){}

    void addVertex(int x, int y){
        v_xy.push_back(make_pair(x,y));
    }

    void printGraphVertex(void){
       vector<Pair_double>::iterator it_xyw;
       //cout<<"xy_w size="<<xy_w.size()<<endl;
       for(it_xyw=xy_w.begin();it_xyw!=xy_w.end();it_xyw++){
                cout<<(*it_xyw).first<<" "<<(*it_xyw).second.first<<" "<<(*it_xyw).second.second<<endl;
       }
    }

    void distance(void){
     int v=this->V;
     double dist_XY;
     int dist_X,dist_Y,i;
     vector<Pair_double>::iterator it_xyw;
     i=0;
     while(i<v){
         for(int j=0;j<v;j++){
             if(i!=j){
                 dist_X= v_xy[i].first - v_xy[j].first;
                 dist_Y= v_xy[i].second - v_xy[j].second;
                 dist_XY=sqrt( pow(dist_X,2.0) + pow(dist_Y,2.0));
                 xy_w.push_back(make_pair(dist_XY,make_pair(i,j)));
             }
         }
         i++;
     }

     sort(xy_w.begin(),xy_w.end());
    }

    double kruskal();
};

class DisjointSets{
   int n;
   vector<int> parent;
   vector<int> rank;
   public:
      DisjointSets(int N){
         this->n=N;
         this->parent.resize(n);
         this->rank.resize(n,0);
         for(int i=0;i<n;i++)
            parent[i]=i;
      }

      int find(int x){
          if( parent[x] != x)
              parent[x]=find(parent[x]);
          return parent[x];

      }

      void merge(int x, int y){
         x = find(x), y=find(y);

         if (x == y){
            return;
         }

         if (rank[x]<rank[y]){
            parent[x]=y;
         }
         else if(rank[x] > rank[y]){
            parent[y]=x;
         }
         else{
              parent[x]=y;
              rank[y]=rank[y]+1;
         }
      }
};

/*
KRUSKAL(G):
 A = ¯
 foreach v ? G.V:
    MAKE-SET(v)
 foreach (u, v) in G.E ordered by weight(u, v), increasing:
    if FIND-SET(u) ? FIND-SET(v):
       A = A ? {(u, v)}
       UNION(u, v)
 return
*/

double Graph::kruskal(){
   double weight;
   vector<Pair_double>::iterator it;
   DisjointSets ds(this->V);
   int x,y;
   int setx,sety;
   weight=0;

   for(it=xy_w.begin();it!=xy_w.end(); ++it){
         x=(*it).second.first;
         y=(*it).second.second;

         setx=ds.find(x);
         sety=ds.find(y);

         if(setx != sety){
            weight += (*it).first;
            ds.merge(setx,sety);
            //cout<<weight<<endl;
         }
   }

   return weight;
}


int main(){
  int n,x,y;
  cin>>n;
  if(n>=1 && n<=200){
    Graph *g=new Graph(n);
    for(int i=0;i<n;i++)
    {
       cin>>x>>y;
       if( y<=10e3 && x>=(-10e3))
          g->addVertex(x,y);
    }
    g->distance();
    cout<<setprecision(10)<<g->kruskal()<<endl;
  }
  return 0;
}
