#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#ifndef bool
#define bool    int
#define true    1
#define false   0
#endif

#define LeftChild(x) 2 * x + 1
#define RightChild(x) 2 * x + 2

/*	Algorithm
After going through the problem once, I realized that the problem was related to
minimum spanning tree problem, I decided to implement a variation on prim's algorithm
where I reduce the time required to reach cities after selecting minimum edge on
each iteration. One way to think about it is, after selecting an edge every other edge
becomes a more viable option.
*/

//Edge struct, minHeap consists of these edges.
typedef struct Edge{
    int st_vertex;
    int end_vertex;
    int cost;
} Edge;

//minHeap struct
typedef struct minHeap {
    int size ;
    Edge *edge ;
} minHeap;

//initialize the mean heap data structure
minHeap* initMinHeap(int size) {
    
   minHeap *hp = malloc(sizeof(minHeap));
    if (!hp) {
        
        perror("Error:");
        exit(1);
        
    }
    
    hp->edge = NULL;
    hp->size = 0 ;
    return hp;
}


void swap(Edge *n1, Edge *n2) {
    Edge temp = *n1 ;
    *n1 = *n2 ;
    *n2 = temp ;   
}


//Heapify function which swaps elements to satisfy minHeap property.
void heapify(int i, minHeap* hp) {
    int minmumElement = (LeftChild(i) < hp->size && hp->edge[LeftChild(i)].cost < hp->edge[i].cost) ? LeftChild(i) : i ;
    if(RightChild(i) < hp->size && hp->edge[RightChild(i)].cost < hp->edge[minmumElement].cost) {
        
        minmumElement = RightChild(i) ;
        
    }
    
    if(minmumElement != i) {
        
        swap(&(hp->edge[i]), &(hp->edge[minmumElement])) ;
        heapify(minmumElement, hp) ;
        
    }
    
}


//extract and remove minimum element, from minHeap
Edge extractMean(minHeap* hp) {
    
    Edge e;
    e.cost = -1;
    
    if(hp->size) {
        
        e = hp->edge[0];
        hp->edge[0] = hp->edge[--(hp->size)] ;
        
        Edge *new_ptr = realloc(hp->edge, (hp->size) * sizeof(Edge));
        
        if (new_ptr == NULL){
            
            free(hp->edge);
            perror("Error:");
            exit(1);
            
        }
        
        hp->edge = new_ptr;
        heapify(0,hp);
        return e;
        
    }
    else {
        
        free(hp->edge) ;
        
    }
    
    return e;
    
}


//insert elements in the minHeap
void buildMinHeap(Edge e, minHeap* hp) {
    
    hp->edge[(hp->size)++] = e ;
    
}


//include all the edges of a city in the minHeap, this
//will be done whenever we have reached a city.
void includeCityInHeap(int city, int n, minHeap* hp, Edge *edges){
    
    int j = 0;
    
    if (hp->edge){
        
        
        Edge *new_ptr = realloc(hp->edge, (hp->size + n) * sizeof(Edge));
        
        if (new_ptr == NULL){
            
            free(hp->edge);
            perror("Error:");
            exit(1);
            
        }
        
        hp->edge = new_ptr;
        
    }
    
    else{
        hp->edge = malloc ((hp->size + n) * sizeof(Edge));
        if (! hp->edge){
            perror("Error:");
            exit(1);        
        }
    }
    
    for (j = 0 ; j < n ; j++)
        if (edges[city * n + j].cost > 0 )     
            buildMinHeap(edges[city * n + j], hp);
    
    
    for(j = (hp->size - 1) / 2; j >= 0; j--) {
        heapify(j, hp) ;
    }
}


//reduce time required to reach cities based on where we have already reached.
void updateTimeMinHeap(int minTime, minHeap* hp){
    
    int i = 0;
    
    while (i < hp->size){
        
        hp->edge[i].cost -= minTime;
        i++;
        
    }
    
}


//find minimum cost given the cities includued in the minHeap
int findMinCost(bool* minSet, int *time, int n, minHeap* hp, Edge *edges){
    
    int i =0;
    Edge minEdge = extractMean(hp);
    
    while (minEdge.cost == 0 || (minSet[minEdge.end_vertex] && minSet[minEdge.st_vertex])){
        
        minEdge = extractMean(hp);
        
    }
    
    if (minEdge.cost == -1){
        
        return 0;
        
    }
   
    int to = minSet[minEdge.end_vertex] ? minEdge.st_vertex : minEdge.end_vertex;
    
    minSet[to] = true;
    
    updateTimeMinHeap(minEdge.cost, hp);
    
    includeCityInHeap(to, n, hp, edges);
    
    *time += minEdge.cost;
    
    for(i=0; i != n; i++)  //check if all the cities received
    if(!minSet[i]) return true;
    return false;
    
}


//list of all the edges.
void insertToList( Edge e, int n, Edge *edges){
    edges[e.st_vertex * n + e.end_vertex] = e;
    edges[e.end_vertex * n + e.st_vertex] = e;
}


//parse data from line
void parseLine (char * buff, int columns, int n, Edge *edges){
    
    char *ch=buff;
    ch = strtok(ch, " ");
    Edge e;
    e.cost = INT_MAX;
    e.st_vertex = columns;
    e.end_vertex = 0;
    if (*ch != 'x'){
        e.cost = atoi(ch);
    }
    
    insertToList(e,n, edges);
    int columns_parsed = 1;
    while ( ch && columns_parsed < columns) {
        
        ch = strtok(NULL, " ,");
        Edge e;
        e.cost = INT_MAX;
        e.st_vertex = columns;
        e.end_vertex = columns_parsed++ ;
        if (*ch != 'x'){
            e.cost = atoi(ch);
        }
        insertToList(e,n, edges);
    }
 }


static int getLine (char *prmpt, char *buff, size_t sz) {
    
    int ch;
    // Get line with buffer overrun protection.
    if (prmpt != NULL) {
        
        printf ("%s", prmpt);
        fflush (stdout);
    }
    
    fgets (buff, sz, stdin);
    buff[strlen(buff)-1] = '\0';
    return 0;
}

int main(int argc, const char* argv[]) {
    
    char buff[100];
    int n;
    int i = 1;
    printf("Enter the input to desribe routes between the cities as specified in the document\n");
    fgets(buff, sizeof(buff), stdin);
    sscanf(buff, "%d", &n);
    Edge *edges = malloc(sizeof(Edge) * n * n);
	minHeap *hp;
    if (!edges){
        
        perror("Error:");
        exit(1);
        
    }
    
    while (i < n){
        
        getLine (NULL, buff, sizeof(buff));
        parseLine(buff,i, n, edges);
        ++i;       
    }
    
    bool minSet[n];
    
    i = 0;
    while (i<n){
        
        minSet[i++]= 0;
        
    }
    
    minSet[0]=1;
    int time = 0;
    hp = initMinHeap(n);
    includeCityInHeap(0,n, hp, edges);
    
    while (findMinCost(minSet, &time, n, hp, edges));
    
    printf("minimum time required to reach all cities will be: %d\n",time);
    
    return 0;
    
}