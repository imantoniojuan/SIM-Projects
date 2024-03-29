
#include "CountryData.h"

// ====================================================================

void readData ()
{
	FILE * pFile;
	NoOfRecordsRead = 0;
   	char buffer [Line_Char_Buffer_Size];

	pFile = fopen (INPUT_FILE_NAME , "r");
   
	if (pFile == NULL) 
		perror ("Error opening file 'Countries.txt' !");
	else
	{
		while ( !feof (pFile) )
     	{
			char* aLine = get_line (buffer, Line_Char_Buffer_Size, pFile);

			if (aLine != NULL)
			{
//				printf ("%d] aLine => %s\n", NoOfRecordsRead, aLine);
				globalCountryDataArray [NoOfRecordsRead++] = createCountryRecord (aLine);
			}
     	}

     fclose (pFile);
	
	}
}

// ====================================================================

char* get_line (char *s, size_t n, FILE *f)
{
	char *p = fgets (s, n, f);

	if (p != NULL) 
	{
		size_t last = strlen (s) - 1;
		if (s[last] == '\n') 
			s[last] = '\0';
	}
	return p;
}

// ====================================================================

CountryRecordType createCountryRecord (char* aLine)
{
	CountryRecordType ctryRec;
	char* pch = strtok (aLine, LINE_DATA_DELIMITER);

	// 1) Retrieve TLD
	strcpy (ctryRec.TLD, pch);
	pch = strtok (NULL, LINE_DATA_DELIMITER);

	// 2) Retrieve Country
	strcpy (ctryRec.Country, pch);
	pch = strtok (NULL, LINE_DATA_DELIMITER);

	// 3) Retrieve FIPS104
	strcpy (ctryRec.FIPS104, pch);
	pch = strtok (NULL, LINE_DATA_DELIMITER);

	// 4) Retrieve ISO2
	strcpy (ctryRec.ISO2, pch);
	pch = strtok (NULL, LINE_DATA_DELIMITER);

	// 5) Retrieve ISO3
	strcpy (ctryRec.ISO3, pch);
	pch = strtok (NULL, LINE_DATA_DELIMITER);

	// 6) Retrieve ISONo
	ctryRec.ISONo = atof (pch);
	pch = strtok (NULL, LINE_DATA_DELIMITER);

	// 7) Retrieve Capital
	strcpy (ctryRec.Capital, pch);
	pch = strtok (NULL, LINE_DATA_DELIMITER);

	// 8) Retrieve Region
	strcpy (ctryRec.Region, pch);
	pch = strtok (NULL, LINE_DATA_DELIMITER);

	// 9) Retrieve Currency
	strcpy (ctryRec.Currency, pch);
	pch = strtok (NULL, LINE_DATA_DELIMITER);

	// 10) Retrieve CurrencyCode
	strcpy (ctryRec.CurrencyCode, pch);
	pch = strtok (NULL, LINE_DATA_DELIMITER);

	// 11) Retrieve Population
	ctryRec.Population = atof (pch);

	return (ctryRec);

}

// ====================================================================

void displayRecordContent (CountryRecordType ctryRec)
{
	printf("\n");
	printf ("TLD			: %s\n", ctryRec.TLD);
	printf ("Country		\t: %s\n", ctryRec.Country);
	printf ("FIPS104		\t: %s\n", ctryRec.FIPS104);
	printf ("ISO2			: %s\n", ctryRec.ISO2);
	printf ("ISO3			: %s\n", ctryRec.ISO3);
	printf ("ISONo			: %0.2f\n", ctryRec.ISONo);
	printf ("Capital		\t: %s\n", ctryRec.Capital);
	printf ("Region			: %s\n", ctryRec.Region);
	printf ("Currency		: %s\n", ctryRec.Currency);
	printf ("CurrencyCode	\t: %s\n", ctryRec.CurrencyCode);
	printf ("Population		: %0.2f\n", ctryRec.Population);
	printf("\n");
}

// ====================================================================

void showAllRecords ()
{
	int i=0;
	for (i=0; i<NoOfRecordsRead; i++)
	{
		printf ("(%d)\n", i);
		displayRecordContent (globalCountryDataArray [i]);
	}
}

// ====================================================================

int findCountryRecord (const char* countryName)
{
	int idx		= -1;
	int found	= 0;

	while (!found && (++idx < Max_Record_Size))
		if (strcmp (globalCountryDataArray [idx].Country, countryName) == 0)
			found = 1;

	if (found)
		return (idx);
	else
		return (-1);
}

// ====================================================================

char* getCapital (const char* countryName)
{
	int idx = findCountryRecord (countryName);

	if (idx < 0)
		return (NULL);
	else
		return (globalCountryDataArray [idx].Capital);
}

// ====================================================================

char* getCurrencyCode (const char* countryName)
{
	int idx = findCountryRecord (countryName);

	if (idx < 0)
		return (NULL);
	else
		return (globalCountryDataArray [idx].CurrencyCode);
}

// ====================================================================

CountryRecordType getCountryData (const char* countryName)
{
	int idx = findCountryRecord (countryName);

	if (idx < 0)
	{
		CountryRecordType ctryRec;
		strcpy(ctryRec.TLD,"NULL");
		return (ctryRec);
	}
	else
		return (globalCountryDataArray [idx]);
}

void getCountryDataString(char getString[],const char* countryName)
{
	CountryRecordType ctryRec = getCountryData (countryName);

	char buffer[Max_Buffer_Size] = "";
	char numbers[Max_Buffer_Size];

	if(strcmp(ctryRec.TLD,"NULL")==0)
		strcpy(getString,"Invalid");
	else
	{
		strcat(buffer,ctryRec.TLD);
		strcat(buffer,LINE_DATA_DELIMITER);
		strcat(buffer,ctryRec.Country);
		strcat(buffer,LINE_DATA_DELIMITER);
		strcat(buffer,ctryRec.FIPS104);
		strcat(buffer,LINE_DATA_DELIMITER);
		strcat(buffer,ctryRec.ISO2);
		strcat(buffer,LINE_DATA_DELIMITER);
		strcat(buffer,ctryRec.ISO3);
		strcat(buffer,LINE_DATA_DELIMITER);
		sprintf(numbers, "%.2f", ctryRec.ISONo);
		strcat(buffer,numbers);
		strcat(buffer,LINE_DATA_DELIMITER);
		strcat(buffer,ctryRec.Capital);
		strcat(buffer,LINE_DATA_DELIMITER);
		strcat(buffer,ctryRec.Region);
		strcat(buffer,LINE_DATA_DELIMITER);
		strcat(buffer,ctryRec.Currency);
		strcat(buffer,LINE_DATA_DELIMITER);
		strcat(buffer,ctryRec.CurrencyCode);
		strcat(buffer,LINE_DATA_DELIMITER);
		sprintf(numbers, "%.2f", ctryRec.Population);
		strcat(buffer,numbers);

		strcpy(getString,buffer);
	}
}

// ====================================================================

/*
main ()
{
	readData ();
//	showAllRecords ();

	char* country1 = "Andorra";

	printf ("%s Capital       : %s\n", country1, getCapital (country1));
	printf ("%s Currency Code : %s\n", country1, getCurrencyCode (country1));


	char* country2 = "Zimbabwe";

	printf ("%s Capital       : %s\n", country2, getCapital (country2));
	printf ("%s Currency Code : %s\n", country2, getCurrencyCode (country2));

	char* country3 = "Malaysia";

	printf ("%s Capital       : %s\n", country3, getCapital (country3));
	printf ("%s Currency Code : %s\n", country3, getCurrencyCode (country3));

}
*/
// ====================================================================



