//GK.cpp
#include "GK.h"
#include<string.h>
/*
The GreenWald Khanna Sketch: An Algorithm for computing approximate quantile 
summaries of very large data sequences.
*/

/*
Pre-Condition: The maximum number of Tuples.
Post-Condition: A Dynamically alloacted array of maxTuples.
*/
GK::GK(int maxTuples)
{
	num_tuples=0;
	num_observations=0;
	max=maxTuples;
	summary=new Tuple*[maxTuples];
	for (int i = 0; i < max; i++)
		summary[i] = NULL;
	stream_size =0;
}
/*
Pre-Condition: None.
Post-Condition: Deallocates dynamicaly allocated memory.
*/
GK::~GK()
{	
	for (int i=0;i<max;i++)
	{
		delete summary[i];
	}
	delete []summary;
}
/*
Pre-Condition: The value to be inserted.
Post-Condition: A tuple holding val as its value is inserted into the summary.
*/
void GK::insert(double val)
{ 
	stream_size +=1; 
	int index= find_index(val);
	if(summary[index]==NULL)
	{
		insert_tuple(new Tuple(val),index); 
	}
	else
	{
		double store=summary[index]->g+summary[index]->delta-1; 
		insert_tuple(new Tuple(val,1.0,store),index);
	}
	if(num_tuples==max)
		delete_merge();
	num_observations++;

}
/*
Pre-Condition: The Tuple to be inserted and the index in summary at
which at has to be inserted.
Post-Condition: The Tuple is inserted is inserted at index.
*/
void GK::insert_tuple(Tuple* t,int index)
{	
	/*int destpos=num_tuples;
	int srcpos=num_tuples-1;
	for(int i=0;i<num_tuples-index;i++)
	{	
		summary[destpos]=summary[srcpos];
		srcpos--;
		destpos--;
	}*/
	
	int size_of_pointer= sizeof(summary[0]);
        int total_size=size_of_pointer * (num_tuples-index);
        memmove(&(summary[index+1]),&(summary[index]),total_size);
	
	summary[index]=t;
	num_tuples++;
}
/*
Pre-Condition: A double value
Post-Condition: Finds the index of a tuple whose value is greater than value
*/
int GK::find_index(double val)
{
	int high= num_tuples;int low=-1,mid;
	while(high-low >1)
	{
		mid=(high+low)/2;
		if(summary[mid]->v >val)
			high=mid;
		else
			low=mid;
	}
	return high;
}
/*
Pre-Condition:None.
Post-Condition: Does a merge and deletes the tuple that is least full.
*/
void GK::delete_merge()
{	
	int leastIndex = 0;
	long leastFull= LLONG_MAX;
        for (int i = 1; i <num_tuples - 1; i++) 
        {
            long f = summary[i]->g + summary[i + 1]->g+summary[i + 1]->delta;   
            if ((summary[i]->delta >=summary[i + 1]->delta)
                    && (f < leastFull)) 
            {
                leastFull = f;
                leastIndex = i;
            }
        }
        if (leastIndex > 0) 
            delete_tuple(leastIndex);
}
/*
Pre-Condition: the index of the tuple to be deleted.
Post-Condition: the tuple at the index is deleted.
*/
void GK::delete_tuple(int index)
{	
        Tuple *hold  = summary[index];
	summary[index] = new Tuple(summary[index + 1]->v,
                summary[index]->g + summary[index + 1]->g,
                summary[index + 1]->delta);
        delete hold;
	delete summary[index+1];
        int size_of_pointer= sizeof(summary[0]);
        int total_size=size_of_pointer * (num_tuples-index-2);
        memmove(&(summary[index+1]),&(summary[index+2]),total_size);
	summary[num_tuples-1]=NULL;
	num_tuples--;
}
/*
Pre-Condition: The quantile interval.
Post-Condition: The quantile estimate.
*/
double GK::getQuantile(double quant)
{
	long rank= (long) ceil(quant* num_observations);
	long current_rank=0;
	for (int i = 0; i < num_tuples - 1; i++)
	{
		current_rank +=summary[i]->g;
		if ((current_rank +summary[i + 1]->g) > rank)
            	    return summary[i]->v;
        }
        return summary[num_tuples - 1]->v;
}



