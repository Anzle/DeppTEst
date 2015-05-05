/**********************************************
        CS415  Project 3
        Spring  2015
        Student version
**********************************************/

#include <stdio.h>
#include "deptest.h" 



//Check for dependence of the form a[i+5] = a[6];
int ziv(Node* lhs, Node* rhs, int lb, int ub){
	
	if(lhs->arr != rhs->arr)
		return 0; // No dependence, different arrays
	
	//format check
	if(lhs->a > 1 || rhs->a != 0)
		return -1; //must perform siv test
	
	int cx = rhs->c - lhs->c;
	if (lb <= cx && cx <= ub)
		return 1; //dependence found
	
	return 0; //no dependence
}

//Check for dependence of the form a[2*i+5] = a[2*i+2]
int siv(Node* lhs, Node* rhs, int lb, int ub){
	
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
