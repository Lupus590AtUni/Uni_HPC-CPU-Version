#pragma once
//container class for lookup table values

//ABANDONED CODE: incompleate, untested, likely buggy
template <class _template> class NA_LookupTable
{
private:
	friend class NA_TestHarness;
	_template* table;
	unsigned int unitSize;
public:
	NA_LookupTable(void);
	~NA_LookupTable(void);
	_template lookup(unsigned int value);
	void init(_template (*func)(int),unsigned int unitSize,unsigned int numOfValues);//allocates table memory then, feeds values into func to populate table. values start from 0 and increase in UnitSize until the table size == numOfValues
};

template <class _template> _template NA_LookupTable<_template>::lookup(unsigned int value)
{
	return table[(int) value/unitSize];
}

template <class _template> void NA_LookupTable<_template>::init(_template (*func)(int),unsigned int unitSize,unsigned int numOfValues)
{
	this->unitSize = unitSize;
	table = new _template[numOfValues];
	
	for(unsigned int i = 0; i < numOfValues;i++)
	{
		table[unitSize*i] = func(unitSize*i);
	}
}


template <class _template> NA_LookupTable<_template>::NA_LookupTable(void)
{
	table = NULL;
	unitSize = 0;
}


template <class _template> NA_LookupTable<_template>::~NA_LookupTable(void)
{
	if(table != NULL)
	{
		delete table;
	}
}
