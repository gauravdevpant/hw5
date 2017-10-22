#include <stdio.h>
#include<string.h>                      // FILE
#include <object_list.h>                // linked list utility module
#include "simple_graph.h"
/// GraphNode implements a simple graph node using 
/// an adjacency list with a variable number of neighbors.
/// The simple graph uses the ObjectList unordered, dynamic list module
/// to store both the list of nodes in a graph and the list of 
/// adjacent, neighboring nodes for a given node in the graph.
/// @see ObjectList
/*
typedef struct GraphNode_S {
    char name[MAX_NAME];                ///< name of instance
    ObjectList * neighbors;             ///< neighbors of instance
} GraphNode;
*/
/// grh_create_node creates a graph node in dynamic storage.
/// The new instance has a copy of the name passed in.
/// @return pointer to the new instance.

GraphNode * grh_create_node( char * name ){
  GraphNode * nodeptr = (GraphNode *)malloc(sizeof(GraphNode));
  strcpy(nodeptr->name, name);
  return  nodeptr;  
}

/// grh_delete_node deletes the given node.
/// Note: due to potential cycles, the deletion cannot follow the neighbors.
/// To ensure destruction of all dynamic memory, it is necessary for
/// applications using this module to maintain a comprehensive list of
/// all nodes created.

void grh_delete_node( GraphNode * node ){
  free(node);
}
  

/// grh_delete_graph will delete the entire list of graph nodes.
/// @param graph the list of graph nodes

void grh_delete_graph( ObjectList * graph ){
  ol_destroy(graph);
}


/// grh_find_node_by_name searches the graph (a list of GraphNode) for
/// the node whose name matches the input name.
/// @param name the name of the node to find
/// @return pointer to the instance or NULL if not found.
/// @pre-condition graph is NOT NULL and list is NULL terminated

GraphNode * grh_find_node_by_name( ObjectList * graph, char * name ){
  Iter * graphIter=ol_iterator(graph);
  while(ol_has_next(graphIter)){
    GraphNode * current= ol_next(graphIter);
    if(strcmp((current->name),name)==0){
      return current;
      
    }
    
  }
  return NULL;
  
}

/// grh_print_graph
/// @param graph the list of nodes in the graph
/// @pre-condition graph is NOT NULL and list is NULL terminated

void grh_print_graph( ObjectList * graph ){
  printf("Graph: {name: neighbor names list}\n");
  Iter * graphIter=ol_iterator(graph);
  while(ol_has_next(graphIter)){
    GraphNode * current= ol_next(graphIter);
    if(strcmp((current->name),"")!=0){
      printf("%s: ",current->name);
      }
    if(current->neighbors != NULL)
    {
      Iter * neighborIter = ol_iterator(current->neighbors);
      // char * neigh = (char *) malloc(sizeof(char) * 100);
      while(ol_has_next(neighborIter)){
        GraphNode * neighbor = ol_next(neighborIter);
        printf("%s", neighbor->name);
        if(ol_has_next(neighborIter)){
          printf(", ");
        }
        }
      }
      if(strcmp((current->name),"")!=0){
        printf("\n");
      }
    }
    
  }


/// grh_load_file loads data from the input stream and creates 
/// zero or more graph nodes, which it adds to the graph.
/// @param graph the list of nodes already in the graph
/// @param input the file stream of node information to put into the graph
/// @pre-condition graph is NOT NULL and list is NULL terminated.
/// @pre-condition input is a valid open file object ready for reading.

void grh_load_file( ObjectList * graph, FILE * input ){
  char ch=fgetc(input);
  int i=0,j=0,wordCount=0;
  //char stringArr[100];
  char * line[2000];
  line[j] = (char *) malloc(sizeof(char) * 100);
  while(ch != EOF){
    if(ch == ','){ 
      i=0;                                        // The future new string;
      //str = (char *) malloc(sizeof(char) * 100);            // Allocate the string
      //strcpy(str, line[j]);                                     // Function from the C string.h standard librar
      // printf("%s\n", line[j]);
      j++;
      line[j] = (char *) malloc(sizeof(char) * 100);
      wordCount++;
    }
    else if(ch=='\n'){
      wordCount++;
      i=0;
      j=0;
      GraphNode * node=grh_create_node(line[j]);//(GraphNode)malloc(sizeof(GraphNode));
      node->neighbors = ol_create();
      // printf("%s\n", line[j]);
      //node->name=line[j];
      ol_insert(graph,node);
      j++;
      ObjectList * neighborsList=ol_create();
      // printf("Here");
      while( j < wordCount){// j < 2000 && strcmp(line[j],"")!=0 ){
         GraphNode * contains=grh_find_node_by_name(graph, line[j]);
         if(contains == NULL){
           contains = grh_create_node(line[j]);
           ol_insert(graph, contains);
           contains->neighbors = ol_create();
         }
         ol_insert(contains->neighbors, node);
         ol_insert(neighborsList,contains);
         // printf("%d \n", j);
         j++;
      }
      wordCount = 0;
      node->neighbors=neighborsList;
      j=0;
      // free(line);
      line[j] = (char *) malloc(sizeof(char));
    }
    else{
      line[j][i] = ch;
      i++;
    }
    ch=fgetc(input);
    // printf("%c\n", ch);
  }
}
