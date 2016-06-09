//CMS.cpp

CMS::CMS(int w,int d)
{
	width=w;
	depth=d;
	count=0;
	c=new int*[d];
	for (int i=0;i<depth;i++)
	{
		c[i]=new int[width];
		for(int j=0;j<w;j++)
			c[i][j]=0;
	}
	hashA=new HashTable*[d];
	hashB=new HashTable*[d];
	//srand(time(0));
	for(int i=0;i<depth;i++)
	{
		hashA[i]=new HashTable(rand());
		hashB[i]=new HashTable(rand());	
	}
	
}

CMS::~CMS()
{
	for (int i=0;i<depth;i++)
	{
		delete hashA[i];
		delete hashB[i];
		delete c[i];
	}
	
	delete []c;
	delete []hashA;
	delete []hashB;
	
}

void CMS::update(unsigned int item,int diff)
{
	count=count+diff;
	int val=0;
	for(int i=0;i<depth;i++)
	{
		val= (hashA[i]->hash(item)+hashB[i]->hash(item)) % width;
		c[i][val]++;
	}
	
}

int CMS::pointEstimate(int item)
{
	int minimum=INT_MAX;
	int val=0;
	for (int i=0;i<depth;i++)
	{	
		val= (hashA[i]->hash(item)+hashB[i]->hash(item)) % width;
		minimum=min(minimum,c[i][val]);
	}
	return minimum;
}
