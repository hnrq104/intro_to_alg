/*to reduce arguments, because push takes in so many different arguments,
i will write it directly into the function, python seems better sometimes right!*/

/*
PUSH(u,v){
    // applies when : u is overflowing (e(u) > 0), cf(u,v) > 0 and u.h = v.h + 1
    //action: pushes over min(e(u),cf(u,v)) from u to v
    deltaF = min(e(u),cf(u,v))
    if (u,v) in E
        f(u,v) = f(u,v) + deltaF
    else f(v,u) = f(v,u) - deltaF
    e(u) = e(u) - deltaF
    e(v) = e(v) + deltaF 
}
*/

/*
RELABLE(u)
    //applies when: u is overflowing and for all v in V such that (u,v) in Ef
        we have h(u) <= h(v)
    //action increase the height of u
    h(u) = 1 + min(h(v) for (u,v) in Ef)
*/

/*
INITIALIZE PRE-FLOW(G,s)
    for each vertex v in G.v
        h(v) = 0
        e(v) = 0
    
    for each edge (u,v) in G.e
        f(u,v) = 0
    
    s.h = |G.V|

    for each vertex v in s.Adj
        f(s,v) = c(s,v)
        v.e = c(s,v)
        s.e = s.e - c(s,v)

*/

/*gereric push-relable(G)
    Initialize push relable(G)
    while(there exists an applicable push or relable)
        select the application and do it
*/

/*I hardly understood this chapter, will have to come back later*/