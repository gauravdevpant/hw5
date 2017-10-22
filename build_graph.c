//      Gaurav Dev Pant <gdp2075@rit.edu>

#include<stdio.h>
#include "simple_graph.h"
#define BUFSIZE 1024

int main(int argc, char * argv[]){ 
  
  printf("Reading graph data...\n");
  FILE * input=stdin;// fopen(argv[1],"r");
  
  if(input==NULL){
    printf("That file doesnot exist because of reasons.");
    return 1;  
  }
  // return 1;
  ObjectList * graph=ol_create();
  grh_load_file(graph, input);
  printf("Finished reading graph data.\n");
  
  grh_print_graph(graph);
  
  fclose(input);
  ol_destroy(graph);
  
  return 0;
  
  }
  
