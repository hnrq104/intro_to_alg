#include <bits/stdc++.h>
#include <cmath>
#include <cstddef>
#include <vector>

/*van emde boas*/
/*20.1

20.1-1
instead of storing 1's or 0's, store integers

20.1-2
store pointers ("notice you wont be able to store duplicates")

20.1-3
search for x, keeping track of smallest element greater than x.
if we find x, look for the smallest element in right subtree

20.1-4
each node points to u^(1/k) nodes
so we will need k levels to reach u

each operation takes k*u^(1/k)
*/

/*
20.2
# i won't write real code, implementing this protostructure seems to much of a pain

20.2-1.

PROTO-vEB-MAXIMUM(V)
    if (V.u == 2)
        if(V.A[1] == 1) return 1;
        elif(V.A[0] == 1) return 0;
        return NIL;
    

    else
        max-cluster = PROTO-vEB-MAXIMUM(V.summary)
        
        if (max-cluster == nil) return NIL
        
        else
            offset = PROTO-vEB-MAXIMUM(V.cluster[max-cluster])
            return index(maxcluster,offset)

PROTO-vEB-PREDECESSOR(V,x)
    if(V.u == 2)
        if(x == 1 && V.A[0] == 1) return 0
        else return NIL
    
    else
        off-set = PROTO-vEB-PREDECESSOR(V.cluster[high(x)],low(x))
        if (off-set != NIL)
            return index(high(x),offset)
        
        else
            prec-cluster = PROTO-vEB-PREDECESSOR(V.summary,high(x) )
            if(prec-cluter == NIL) return NIL
            
            else
                off-set = PROTO-vEB-MAXIMUM(V.cluster[prec-cluster])
                return index(prec-cluster,offset)

20.2-2
DELETE(V,x)
    if(V.u == 2)
        V.A[x] = 0

    else
        DELETE(V.cluster[high(x)],low(x))

        bool empty = true
        for i values in v.cluster[high(x)]
            if member(v.cluster[high(x)],i)
                empty = false
                break

        if empty
            delete(V.summary,high(x))  


T(u) = 2*T(sqrt(u)) + O(sqrt(u)*lglgu)
let m = log u

T(2^m) = 2*T(2^(m/2)) + O(2^(m/2)*m)
S(m) = 2*s(m/2) + O(2^(m/2)*log m)
but this is certainly 2^(m/2)*log m = sqrt(u)*log(log*u)

20.2-3
it would change insert adding a n++ at each recursive step
and we would have to check if we added

delete(V,x)
    if(V.u == 2)
        V.A[x] == 0
        v.n--
    else
        delete(V.cluster[high(x)],low(x))
        n--
        bool empty = true 
        for cluster in v.cluster
            if cluster.n != 0
                empty = false
                break 

        if empty
            delete(V.sumary,high(x))

this is faster
T(u) = 2*T(sqrt(u)) + O(sqrt(u))
letting m = log u
T(2^m) = 2*T(2^(m/2)) + O(2^m/2)
S(m) = 2*S(m/2) + O(m)
but this is equal to mlogm
which is log(u)*log(log(u))

20.2-4
allow integers
20.2-5
allow pointers too

20.2-6

create-proto(u)
    if(u==2)
        cluster = new proto(2)
        return cluster
    
    else
        cluster = new cluster
        cluster.A = new cluster*[sqrt(u)]
        for i = 0, i < sqrt(u)
            cluster.A[i] = create-proto(sqrt(u))
        cluster.summary = create-proto(sqrt(u))
    
        return cluster
to discover how much space does the strcture need
we can discover how long this algorithim takes

T(U) = sqrt(u)*T(sqrt(u)) + sqrt(u)
S(m) = m/2 * S(m/2) + m
well this is not simple

but i think its u
yeah u works

20.2-7
of course, if the summary contains no minimum
then that cluster is empty

20.2-8

we would need u^3/4 cluster in each cluster array
it would still be the same for everything
*/

/*20.3 i should try to make it now*/


int upper_sqrt(int u){
    return (int)std::ceil(std::sqrt(u));
}

int lower_sqrt(int u){
    return (int)std::floor(std::sqrt(u));
}

int high(int x,int u){
    return (int) std::floor(x/lower_sqrt(u));
}
int low(int x, int u){
    return x % lower_sqrt(u);
}

int index(int x, int y,int u){
    return x*lower_sqrt(u) + y;
}

struct vEB{
    int u;
    int min;
    int max;

    vEB* summary;
    std::vector<vEB*> cluster;
};

int vEB_min(vEB* V){
    return V->min;
}

int vEB_max(vEB* V){
    return V->max;
}

bool vEB_member(vEB* V, int x){
    if(x == V->min || x==V->max) return true;
    if(V->u == 2) return false;
    return vEB_member(V->cluster.at(high(x,V->u)),low(x,V->u));
}

/*should use a class here, but i am lazy*/
int vEB_suc(vEB* V, int x){
    if(V->u==2){
        if(x==0 && V->max == 1){
            return 1;
        }
        else return -1; /*-1 being NIL here*/
    }
    else if(V->min != -1/*NIL*/ && x<V->min){
        return V->min;
    }

    else{
        int max_low = vEB_max(V->cluster.at(high(x,V->u)));
        if(max_low != -1/*NIL*/ && low(x, V->u) < max_low){
            int offset = vEB_suc(V->cluster.at(high(x,V->u)),low(x,V->u));
            return index(high(x, V->u), offset, V->u);
        }
        else{
            int suc_cluster = vEB_suc(V->summary, high(x,V->u));
            if(suc_cluster == -1){ /*Nil*/
                return -1;/*NIL*/
            }
            else{
                int offset = vEB_min(V->cluster.at(suc_cluster));
                return index(suc_cluster,offset,V->u);
            }
        }
    }
}


int vEB_pred(vEB* V, int x){
    if(V->u==2){
        if(x==1 && V->min == 0){
            return 0;
        }
        else return -1; /*-1 being NIL here*/
    }
    else if(V->max != -1/*NIL*/ && x>V->max){
        return V->max;
    }

    else{
        int min_low = vEB_min(V->cluster.at(high(x,V->u)));
        if(min_low != -1/*NIL*/ && low(x, V->u) > min_low){
            int offset = vEB_pred(V->cluster.at(high(x,V->u)),low(x,V->u));
            return index(high(x, V->u), offset, V->u);
        }
        else{
            int pred_cluster = vEB_pred(V->summary, high(x,V->u));
            if(pred_cluster == -1){ /*Nil*/
                if(V->min != -1 && x>V->min){
                    return V->min;
                }
                else return -1;/*NIL*/
            }
            else{
                int offset = vEB_max(V->cluster.at(pred_cluster));
                return index(pred_cluster,offset,V->u);
            }
        }
    }
}

void vEB_insert_empty(vEB* V, int x){
    V->min = x;
    V->max = x;
}

void vEB_insert(vEB* V, int x){
    if(V->min == -1){
        vEB_insert_empty(V,x);
    }

    else{
        if(x<V->min){
            int tmp = x;
            x = V->min;
            V->min = tmp;
        }

        if(V->u > 2){
            if(vEB_min(V->cluster.at(high(x,V->u))) == -1){
                vEB_insert(V->summary, high(x,V->u));
                vEB_insert_empty(V->cluster.at(high(x,V->u)), low(x,V->u));
            }

            else vEB_insert(V->cluster.at(high(x, V->u)), low(x,V->u));
        }

        if(x > V->max){
            V->max = x;
        }
    }
}

void vEB_delete(vEB* V, int x){
    if(V->min == V->max){
        V->min = -1;
        V->max = -1;
    }
    else if(V->u == 2){
        if(x == 0){
            V->min = 1;
        }
        else{
            V->min = 0;
        }
        V->max = V->min;
    }

    else{
        if(x==V->min){
            int first_cluster = vEB_min(V->summary);
            x = index(first_cluster,vEB_min(V->cluster.at(first_cluster)),V->u);
            V->min = x;
        }

        vEB_delete(V->cluster.at(high(x,V->u)), low(x,V->u));
        if(vEB_min(V->cluster.at(high(x,V->u))) == -1){
            vEB_delete(V->summary, high(x, V->u));
            if(x==V->max){
                int summary_max = vEB_max(V->summary);
                if(summary_max == -1){
                    V->max = V->min; /**/
                }
                else{
                    V->max = index(summary_max,vEB_max(V->cluster.at(summary_max)),V->u);
                }
            }
        }

        else if (x ==V->max) {
            int h = high(x,V->u);
            V->max = index(h,vEB_max(V->cluster.at(h)),V->u);
        }
    }
}

/*20.3 question
20.3-1 save how many times an element appears
20.3-2 save pointers associated with elements
*/
/*20.3-3*/
vEB* create_veb(int u){
    if(u == 2){
        vEB* v = new vEB;
        v->u = 2;
        v->min = -1;
        v->max = -1;
        v->summary = nullptr; 
        return v;
    }
    vEB* v = new vEB;
    v->cluster.resize(upper_sqrt(u));
    for(int i = 0; i < upper_sqrt(u); i++){
        v->cluster.at(i) = create_veb(lower_sqrt(u));
    }
    v->summary = create_veb(lower_sqrt(u));
    
    v->u = u;
    v->min = -1;
    v->max = -1;
    
    return v;
}

/*20.3-4

it will go thru the same process, but setting won't do anything on base case
and a 0 to a 0 (in delete case)

keep an auxialiary array A[u] keeping track of elements

20.3-5

now the functions look something like
T(u) = T(u^1/k) + O(1)

which is precisely the same

20.3-6
u/lglg(u)
but really, this times any constant

*/
