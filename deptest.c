/**********************************************
        CS415  Project 3
        Spring  2015
        Student version
**********************************************/

#include <stdio.h>
#include "deptest.h"
#include "attr.h" 



//Check for dependence of the form a[i+5] = a[6];
int ziv(Node* lhs, Node* rhs, int lb, int ub){
	
  if(!rhs)
    return 0; //no righthand side. 
  
	if(lhs->arr != rhs->arr)
		return ziv(lhs, rhs->next, lb,ub); // different arrays, check next in list
	
	//format check
	if(lhs->a > 1 || rhs->a != 0)
		return -1; //must perform siv test
	
	int cx = rhs->c - lhs->c;
	if (lb <= cx && cx <= ub){
		emitFoundOutputDependence(lhs->arr);
    return 1; //dependence found
  }
	
	return ziv(lhs, rhs->next, lb,ub); // different arrays, check next in list; //no dependence
}

//Check for dependence of the form a[2*i+5] = a[2*i+2]
int siv(Node* lhs, Node* rhs, int lb, int ub){
	
  if(!rhs){
   
    return 0; //no righthand side. 
  }
  
  if(lhs->arr != rhs->arr)
		return siv(lhs, rhs->next, lb,ub); // No dependence, different arrays
  
  //A's must match for hard SIC+V
  if(lhs->a != rhs->a){
    emitAssumeTrueDependence(lhs->arr);
     return 1; // Could do more, but for now, return dependence
  }
  
  float d = ((float)lhs->c - (float)rhs->c) / (float)lhs->a;
  int di = (lhs->c - rhs->c)/lhs->a;
  if(d != (float)di)
     return siv(lhs, rhs->next, lb,ub);//Not an int
  
  if(d < 1)
      return siv(lhs, rhs->next, lb,ub);//Smaller than 1
  
  if(d > (ub-lb))
      return siv(lhs, rhs->next, lb,ub);
  
  emitFoundTrueDependenceWithDistance(lhs->arr, d);
  return 1; // Cann't prove it doesn't have a dependence
  
  
}

void emitFoundTrueDependenceWithDistance(char *arrayName, int distance) 
{
  sprintf(CommentBuffer, " <<< Found TRUE dependence on variable \"%s\" with distance %d >>>", 
	  arrayName, distance);
  emitComment(CommentBuffer);
  fprintf(depstats, "%s\n", CommentBuffer);  
}

void emitAssumeTrueDependence(char *arrayName)
{
  sprintf(CommentBuffer, " <<< Assume TRUE dependence on variable \"%s\" with unknown distance >>>", 
	  arrayName);
  emitComment(CommentBuffer);
  fprintf(depstats, "%s\n", CommentBuffer);  
}

void emitFoundOutputDependence(char *arrayName)
{
  sprintf(CommentBuffer, " <<< Found OUTPUT dependence on variable \"%s\" >>>", 
	  arrayName);
  emitComment(CommentBuffer);
  fprintf(depstats, "%s\n", CommentBuffer);  
}

void emitAssumeOutputDependence(char *arrayName)
{
  sprintf(CommentBuffer, " <<< Assume OUTPUT dependence on variable \"%s\" >>>", 
	  arrayName);
  emitComment(CommentBuffer);
  fprintf(depstats, "%s\n", CommentBuffer);  
}

void emitFoundNoDependenciesAndWillVectorize()
{
  sprintf(CommentBuffer, " <<< Found NO dependencies: VECTORIZE >>>");
  emitComment(CommentBuffer);
  fprintf(depstats, "%s\n\n", CommentBuffer);  
}

void emitFoundDependenciesAndWillNotVectorize()
{
  sprintf(CommentBuffer, " <<< Found at least one dependence: CANNOT VECTORIZE >>>");
  emitComment(CommentBuffer);
  fprintf(depstats, "%s\n\n", CommentBuffer);  
}
