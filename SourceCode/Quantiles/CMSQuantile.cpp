//CMSQuantile.cpp

CMSQuantile::CMSQuantile()
{
	
	
}

CMSQuantile::~CMSQuantile()
{
	
	
}

void CMSQuantile::insert(double item)
{	
	
	// do the double converstion to integer.
	
	count_min.update(item,diff??);// Check what the 2nd parameter is.
	
}

double CMSQuantile::getQuantile(double frac)
{
	if (frac<0 || frac>1)
		cout<<"Error";
	
	return (findRange((count_min->count*(1-frac))/2)+
		altFindRange((count_min->count*(1-frac))/2));
	
}

int CMSQuantile::findRange(int sum)
{
	
	unsigned long low=0,high=??,mid=0,est; //what is high
	
	for (int i=0;i<cmh->U;i++) //fix loop
	{
		mid=(low+high)/2;
		est=Rangesum(0,mid);
		if (est>sum)
			high=mid;
		else
			low=mid;
	}
	return mid;

}


int CMSQuantile::altFindRange(int sum)
{
	unsigned long low, high, mid=0, est, top;
  int i;
  // find a range starting from the right hand side that adds up to sum

  	low=0;
  	top=1<<cmh->U; // what??
  	high=top;
  	for (int i=0;i<cmh->U;i++) //fix loop
  	{
  		mid=(low+high)/2;
  		est=CMH_Rangesum(mid,top);
  		if (est<sum)
  			high=mid;
  		else
  			low=mid;
  	}
  	return mid;	
}

int CMSQuantile::RangeSum(int start.int end)
{
	
	
	
	
	
}

