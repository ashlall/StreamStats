//GK.cpp

GK::GK(int maxTuples)
{
	numTuples=0;
	numObservations=0;
	max=maxTuples;
	summary=new Tuple*[maxTuples];
}

GK::~GK()
{	
	for (int i=0;i<max;i++)
	{
		delete summary[i];
	}
	delete []summary;
}

void GK::insert(double val)
{
	int index= findIndex(val);
	Tuple* tuple=summary[index];
	if(tuple==NULL)
		insertTuple(new Tuple(val,1,0),index); 
	else
		insertTuple(new Tuple(val,1,(tuple->g+tuple->delta)-1),index); 
	if(numTuples==max)
		deleteMerge();
	numObservations++;
}
void GK::insertTuple(Tuple* t,int index)
{	
	int pos=index;
	for(int i=0;i<numTuples-index;i++)
	{
		summary[pos]=summary[pos+1];
		pos++;
	}	
	
	summary[index]=t;
	numTuples++;
	
}

int GK::findIndex(double val)
{
	int high= numTuples;int low=-1,mid;
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

void GK::deleteMerge()
{	
	int leastIndex = 0;
	long leastFull= LLONG_MAX;
        for (int i = 1; i <numTuples - 1; i++) 
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
            deleteTuple(leastIndex);
}

void GK::deleteTuple(int index)
{	
	int srcpos=index+2;
	int destpos=index+1;
	summary[index] = new Tuple(summary[index + 1]->v,
                summary[index]->g + summary[index + 1]->g,
                summary[index + 1]->delta);
	for (int i=0;i<numTuples-index-2;i++)
	{	
		summary[destpos]->v=summary[srcpos]->v;
		summary[destpos]->g=summary[srcpos]->g;
		summary[destpos]->delta=summary[srcpos]->delta;
		srcpos++;
		destpos++;
	}
	summary[numTuples-1]=NULL;
	numTuples--;
}

double GK::getQuantile(double quant)
{
	long rank= (long) ceil(quant* numObservations);
	long current_rank=0;
	for (int i = 0; i < numTuples - 1; i++)
	{
		current_rank +=summary[i]->g;
		if ((current_rank +summary[i + 1]->g) > rank)
            	    return summary[i]->v;
        }
        return summary[numTuples - 1]->v;
}



