#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 350 // maximum line lenght
//using namespace std;


struct person
{
	char **firstname;
	char **lastname;
	char **email;
	char **number;
};

void myswap(char *p1, char *p2);

int main(int argc, char const *argv[])
{
	struct person readed;
	readed.firstname = (char **)malloc(sizeof(char) * 2400);
	readed.lastname = (char **)malloc(sizeof(char) * 2400);
	readed.email = (char **)malloc(sizeof(char) * 2400);
	readed.number = (char **)malloc(sizeof(char) * 2400);
	FILE *filepointer;
	filepointer = fopen("hw4_disordered_people.txt", "r");

	if ((filepointer = fopen("hw4_disordered_people.txt", "r")) == NULL)
	{
		printf("No such file\n");
		exit(1);
	}

	char control[MAX]; // this is for taking and temporary storing line data
	int line = 0;
	char *token; //parçalanmış sitringi tutmak için pointer

	while (!feof(filepointer))
	{
		int fnamenum = 0, lnamenum = 0, emailnum = 0, numnum = 0; // satırda aynı elemandan kaç tane olduğıunu tutan değişkenler.
		fgets(control, 299, filepointer);
		token = strtok(control, " ,\n"); // parçalama fonksiyonu her satırı boşlulara göre bölüyor. \n varsa siliyor.
		while (token != NULL)
		{
			if (token[1] <= 'Z' && token[1] >= 'A') // soy isim kontrolü eğer kelimenin 2. harfi büyükse soy isim arrayine atıyor.
			{
				if (lnamenum == 0)
				{
					readed.lastname[line] = (char *)malloc(strlen(token) * 2);
					strcpy(readed.lastname[line], token);
					lnamenum++;
				}
				else if (lnamenum != 0)
				{
					readed.lastname[line] = (char *)realloc(readed.lastname[line], strlen(token) * 2);
					strcat(readed.lastname[line], " ");
					strcat(readed.lastname[line], token);
					lnamenum++;
				}
			}
			else if ((token[0] >= 'A' && token[0] <= 'Z') && (token[1] <= 'z' && token[1] >= 'a')) // isim kontrolü eğer ilk harf büyük 2. hark küçükse isim arrayine atıyor.
			{
				if (fnamenum == 0)
				{
					readed.firstname[line] = (char *)malloc(strlen(token) * 2);
					strcpy(readed.firstname[line], token);
					fnamenum++;
				}
				else if (fnamenum != 0)
				{

					readed.firstname[line] = (char *)realloc(readed.firstname[line], strlen(token) * 2);
					strcat(readed.firstname[line], " ");
					strcat(readed.firstname[line], token);
					fnamenum++;
				}
			}
			else if (token[0] >= '0' && token[0] <= '9') // sayı kontrolü eğer ilk harf bir sayıysa ıd arrayine atıyor.
			{
				if (numnum == 0)
				{
					readed.number[line] = (char *)malloc(strlen(token) * 2);
					strcpy(readed.number[line], token);
					numnum++;
				}
				else if (numnum != 0)
				{
					readed.number[line] = (char *)realloc(readed.number[line], strlen(token) * 2);
					strcat(readed.number[line], " ");
					strcat(readed.number[line], token);
					numnum++;
				}
			}
			else if (token[1] >= 'a' && token[1] <= 'z') // mail kontrolü eğer ilk ve 2. harfler küçükse mail arrayine atıyor.
			{
				if (emailnum == 0)
				{
					readed.email[line] = (char *)malloc(strlen(token) * 2);
					strcpy(readed.email[line], token);
					emailnum++;
				}
				else if (emailnum != 0)
				{
					readed.email[line] = (char *)realloc(readed.email[line], strlen(token) * 2);
					strcat(readed.email[line], " ");
					strcat(readed.email[line], token);
					emailnum++;
				}
			}
			token = strtok(NULL, " ,\n "); // parçalama fonksiyonun devamı satırı parçalama devam ediyor.
		}
		line++;
	}

	fclose(filepointer);

	//sıralama adımları
	char choose;

	printf("PLEASE ENTER WHAT DO YOU WANT TO SORT BY \nPRESS 'N' OR 'n' FOR NAME : \nPRESS 'S' OR 's' FOR SURNAME : \nPRESS 'E' OR 'e' FOR EMAIL : \nPRESS 'I' OR 'i' FOR NUMBER : \nQUIT : 'q OR 'Q\n");
	choose = getchar();

	
	switch (choose)
	{
	case 'n':
	case 'N':
		for (int i = 0; i < line - 2; ++i)
		{
			for (int j = 0; j < line - 2; ++j)
			{
				if (strcmp(readed.firstname[j], readed.firstname[j + 1]) > 0)
				{
					myswap(readed.firstname[j], readed.firstname[j + 1]);
					myswap(readed.lastname[j], readed.lastname[j + 1]);
					myswap(readed.email[j], readed.email[j + 1]);
					myswap(readed.number[j], readed.number[j + 1]);
				}
			}
		}

		break;
	case 'S':
	case 's':
		for (int i = 0; i < line - 2; ++i)
		{
			for (int j = 0; j < line - 2; ++j)
			{
				if (strcmp(readed.lastname[j], readed.lastname[j + 1]) > 0)
				{
					myswap(readed.firstname[j], readed.firstname[j + 1]);
					myswap(readed.lastname[j], readed.lastname[j + 1]);
					myswap(readed.email[j], readed.email[j + 1]);
					myswap(readed.number[j], readed.number[j + 1]);
				}
			}
		}
		break;
	case 'E':
	case 'e':
		for (int i = 0; i < line - 2; ++i)
		{
			for (int j = 0; j < line - 2; ++j)
			{
				if (strcmp(readed.email[j], readed.email[j + 1]) > 0)
				{
					myswap(readed.firstname[j], readed.firstname[j + 1]);
					myswap(readed.lastname[j], readed.lastname[j + 1]);
					myswap(readed.email[j], readed.email[j + 1]);
					myswap(readed.number[j], readed.number[j + 1]);
				}
			}
		}
		break;
	case 'I':
	case 'i':
		for (int i = 0; i < line - 2; ++i)
		{
			for (int j = 0; j < line - 2; ++j)
			{
				if (strcmp(readed.number[j], readed.number[j + 1]) > 0)
				{
					myswap(readed.firstname[j], readed.firstname[j + 1]);
					myswap(readed.lastname[j], readed.lastname[j + 1]);
					myswap(readed.email[j], readed.email[j + 1]);
					myswap(readed.number[j], readed.number[j + 1]);
				}
			}
		}
		break;
	case 'Q':
	case 'q':
		exit(0);
	default:
		printf("WARNING!!\nPLEASE WRITE CORRECTlY : ");
		exit(0);
	}


	// dosyaya yazdırma işlemleri
	filepointer = fopen("orderedFile.txt", "w");
	if ((filepointer = fopen("orderedFile.txt", "w")) == NULL)
	{
		printf("No such file\n");
		exit(1);
	}

	printf("LIST INSERTED!\n");

	if (choose == 'N' || choose == 'n')
	{
		fprintf(filepointer, "%-20s%-20s%-20s%-40s\n", "NAME", "SURNAME", "ID", "EMAIL");
		for (int i = 0; i < line - 1; ++i)
		{

			fprintf(filepointer, "%-20s", readed.firstname[i]);
			fprintf(filepointer, "%-20s", readed.lastname[i]);
			fprintf(filepointer, "%-20s", readed.number[i]);
			fprintf(filepointer, "%-40s", readed.email[i]);
			fprintf(filepointer, "\n");
		}
	}
	if (choose == 'S' || choose == 's')
	{
		fprintf(filepointer, "%-20s%-20s%-20s%-40s\n", "SURNAME", "NAME", "ID", "EMAIL");
		for (int i = 0; i < line - 1; ++i)
		{

			fprintf(filepointer, "%-20s", readed.lastname[i]);
			fprintf(filepointer, "%-20s", readed.firstname[i]);
			fprintf(filepointer, "%-20s", readed.number[i]);
			fprintf(filepointer, "%-40s", readed.email[i]);
			fprintf(filepointer, "\n");
		}
	}
	if (choose == 'I' || choose == 'i')
	{
		fprintf(filepointer, "%-20s%-20s%-20s%-40s\n", "ID", "NAME", "SURNAME", "EMAIL");
		for (int i = 0; i < line - 1; ++i)
		{

			fprintf(filepointer, "%-20s", readed.number[i]);
			fprintf(filepointer, "%-20s", readed.firstname[i]);
			fprintf(filepointer, "%-20s", readed.lastname[i]);
			fprintf(filepointer, "%-40s", readed.email[i]);
			fprintf(filepointer, "\n");
		}
	}

	if (choose == 'E' || choose == 'e')
	{
		fprintf(filepointer, "%-40s%-20s%-20s%-20s\n", "EMAIL", "NAME", "SURNAME", "ID");
		for (int i = 0; i < line - 1; ++i)
		{

			fprintf(filepointer, "%-40s", readed.email[i]);
			fprintf(filepointer, "%-20s", readed.firstname[i]);
			fprintf(filepointer, "%-20s", readed.lastname[i]);
			fprintf(filepointer, "%-20s", readed.number[i]);
			fprintf(filepointer, "\n");
		}
	}

	fclose(filepointer);

	// memory boşaltma adımları

	free(readed.number);
	free(readed.firstname);
	free(readed.lastname);
	free(readed.email);

	return 0;
}

void myswap(char *p1, char *p2)
{
	char temp[150];
	strcpy(temp, p1);
	strcpy(p1, p2);
	strcpy(p2, temp);
} 