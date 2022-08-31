#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 500;
//���������Ľṹ��
typedef struct node
{
	char c;//����
	int weight;//Ȩ��
	int leftson;//����
	int rightson;//�Һ���
	int parents;//˫��
}node;

node* CreateTree(int n);//����һ�ż򵥵���
int FindMIN(node* HT, int n);//����Ȩ�ص���С�����
void BornHuffmanTree(node* HT, int n, int m);//���ɹ�������
void encoding(int n);//�������ַ������й���������
void decoding(int n);//���ַ�����������
void Print();//ӡ�����ļ�
void TreePrinting(int n);//ӡ��������
int Init();//��ʼ��
void xiangeng(node* HT, int n, int depth);//�ȸ�������������
void Menu();//��ʾ�˵�

//��ʾ�˵�
void Menu()
{
	//��ʾ�˵����������������û�ʹ��
	printf("��������Ĳ���\n0.�˳�\n1.����\n2.����\n3.ӡ�����ļ�\n4.ӡ��������\n");
}
//�����򵥵���
node* CreateTree(int n)
{
	int m;
	m = 2 * n - 1;//��������������Ҫ2n-1�����
	node* HT = (node*)malloc(sizeof(node) * (m + 1));//��һ��ʼ�������
	int i;
	//��ʼ���������
	for (i = 0; i < m + 1; i++)
	{
		HT[i].leftson = 0;
		HT[i].rightson = 0;
		HT[i].parents = 0;
		HT[i].weight = 0;
		HT[i].c = '*';
	}
	printf("���������ݺ�Ȩ�أ�\n");
	//ȥ���س����Խ�����ݵ�Ӱ��
	getchar();
	for (i = 1; i < n + 1; i++)
	{
		//������������Լ�Ȩ��
		scanf("%c %d", &HT[i].c, &HT[i].weight);
		//ȥ���س����Խ�����ݵ�Ӱ��
		getchar();
	}
	return HT;
}
//�ҵ���СȨ�صĽ��
int FindMIN(node* HT,int n)
{
	int i;
	int min0;
	int f = maxsize;
	//ѭ��������СȨ�صĽ��
	for (i = 1; i <= n; i++)
	{
		if (HT[i].weight < f && HT[i].parents == 0)
		{
			min0 = i;
			f = HT[i].weight;
		}
	}
	//�ҵ���С�Ľ���ǣ���ֹ�ظ�
	HT[min0].parents = 1;
	return min0;
}
//���ɹ�������
void BornHuffmanTree(node* HT,int n,int m)
{
	int min1, min2, i;
	//ѭ������������ķ�Χ�������½��ļӽ����Ľ��
	for (i = n + 1; i <= m; i++)
	{
		min1 = FindMIN(HT, i - 1);//�ҵ���С�Ľ��
		min2 = FindMIN(HT, i - 1);//�ҵ��ڶ�С�Ľ��
		//������������
		HT[min1].parents = i;
		HT[min2].parents = i;
		HT[i].leftson = min1;
		HT[i].rightson = min2;
		HT[i].weight = HT[min1].weight + HT[min2].weight;
		HT[i].c = '*';
	}
	//�����ļ�
	FILE* fp = fopen("hfmTree.txt", "w");
	for (i = 1; i <= 2 * n - 1; i++)
	{
		//�����ڵ������д���ļ�
		fprintf(fp,"%d\t%c\t%d\t%d\t%d\t%d\n", i, HT[i].c, HT[i].weight, HT[i].parents, HT[i].leftson, HT[i].rightson);
	}
	//�ر��ļ�
	fclose(fp);
}
//���뺯��
void encoding(int n)
{
	//�򿪴������ݵ��ļ�
	FILE* fp = fopen("hfmTree.txt", "r");
	node* HT = (node*)malloc(sizeof(node) * (2*n));
	int i;
	for (i = 1; i <= 2 * n - 1; i++)
	{
		//���ļ��ж�������
		fscanf(fp, "%d\t%c\t%d\t%d\t%d\t%d\n", &i, &HT[i].c, &HT[i].weight, &HT[i].parents, &HT[i].leftson, &HT[i].rightson);
	}
	//�������ÿ�������������
	char** HC = (char*)malloc(sizeof(char*) * (n + 1));
	//�ַ������е�һ���ַ���Ӧ������ֵ
	int start;
	char* temp = (char*)malloc(sizeof(char) * n);
	//����ַ����Ľ�β�ַ�
	temp[n - 1] = '\0';
	for (i = 1; i <= n; i++)
	{	
		//����һ�����ӽ��
		int c = i;
		start = n - 1;
		int parents = HT[i].parents;
		while (parents != 0)
		{
			--start;
			//���������������0
			if (HT[parents].leftson == c)
			{
				temp[start] = '0';
			}
			//������Һ���������1
			else
			{
				temp[start] = '1';
			}
			//�������ϻ���
			c = parents;
			parents = HT[parents].parents;
		}
		//�����Ӧ�Ŀռ���ÿ�����ı���
		HC[i] = (char*)malloc(sizeof(char) * (n - start));
		strcpy(HC[i], &temp[start]);
		printf("%c %s", HT[i].c, HC[i]);
	}
	//�ͷ��ڴ�
	free(temp);
	fclose(fp);
	//�򿪴�ű�����ļ�
	fp = fopen("CodeFile.txt", "w");
	//��һ��ʼ��õ��ַ���
	FILE* fp0 = fopen("ToBeTran.txt", "r");
	while(!feof(fp0))
	{
		//�����ݼ��ж����ַ�
		char c = fgetc(fp0);
		for (i = 1; i <= n; i++)
		{
			//�ҵ���Ӧ���ַ����������
			if (HT[i].c == c)
			{
				fprintf(fp, "%s", HC[i]);
				break;
			}
		}
	}
	//�ر��ļ�
	fclose(fp0);
	fclose(fp);
	//�ͷ��ڴ�
	free(HT);
	for (int i = 1; i <= n; i++)
	{
		free(HC[i]);
	}
	free(HC);
	printf("����ɹ�������");
	system("pause");
	system("cls");
}
//���뺯��
void decoding(int n)
{
	//�ļ�����
	FILE* fp1 = fopen("hfmTree.txt", "r");
	node* HT = (node*)malloc(sizeof(node) * (2 * n));
	int i;
	for (i = 1; i <= 2 * n - 1; i++)
	{
		fscanf(fp1, "%d\t%c\t%d\t%d\t%d\t%d\n", &i, &HT[i].c, &HT[i].weight, &HT[i].parents, &HT[i].leftson, &HT[i].rightson);
	}
	fclose(fp1);
	//�򿪱����ļ�����������
	fp1 = fopen("CodeFile.txt", "r");
	int parents = 2 * n - 1;
	//���������ļ����������������
	FILE* fp2 = fopen("TextFile.txt", "w");
	while (!feof(fp1))
	{
		char ch = fgetc(fp1);
		//�����0����Ϊ����
		if (ch == '0')
		{
			parents = HT[parents].leftson;
		}
		//1Ϊ�Һ���
		if(ch == '1')
		{
			parents = HT[parents].rightson;
		}
		//������Һ��Ӷ���0����˵��ΪҶ�ӽ�㣬�ҵ������ڵ�����ݣ���������
		if (HT[parents].leftson == 0 && HT[parents].rightson == 0)
		{
			char c = HT[parents].c;
			fprintf(fp2, "%c", c);
			parents = 2 * n - 1;
		}
	}
	//�������������Ķ����Ʊ��벻������������
	if (parents != 2 * n - 1)
	{
		printf("����Ĳ��Դ������󣡣���");
	}
	//�ر��ļ�
	fclose(fp1);
	fclose(fp2);
	printf("����ɹ�������");
	system("pause");
	system("cls");
}
//ӡ�����ļ�����
void Print()
{
	//���ļ�����������
	FILE* fp1 = fopen("CodeFile.txt", "r");
	FILE* fp2 = fopen("CodePrin.txt", "w");
	int i = 0;
	while (!feof(fp1))
	{
		char c = fgetc(fp1);
		printf("%c", c);
		i++;
		//ÿ50��һ��
		if (i % 50 == 0)
			printf("\n");
		fprintf(fp2, "%c", c);
	}
	//�ر��ļ�
	fclose(fp1);
	fclose(fp2);
	printf("\n");
	system("pause");
	system("cls");
}
//ӡ������������
void TreePrinting(int n)
{
	FILE* fp0 = fopen("TreePrint.txt", "w");
	//��������������
	FILE* fp1 = fopen("hfmTree.txt", "r");
	node* HT = (node*)malloc(sizeof(node) * (2 * n));
	int i;
	for (i = 1; i <= 2 * n - 1; i++)
	{
		fscanf(fp1, "%d\t%c\t%d\t%d\t%d\t%d\n", &i, &HT[i].c, &HT[i].weight, &HT[i].parents, &HT[i].leftson, &HT[i].rightson);
	}
	fclose(fp1);
	//�ȸ�������������
	fclose(fp0);
	xiangeng(HT, 2 * n - 1, 0);
}
//�ȸ���������
void xiangeng(node* HT, int number, int depth) 
{
	//�����漰���ݹ飬������׷д��������д���ļ�
	FILE* fp = fopen("TreePrint.txt", "a");
	int i;
	//������ȴ�ӡ���ٿո�
	for (i = 0; i < depth; i++)
	{
		printf(" ");
		fprintf(fp, " ");
	}
	//��ӡ���ڵ�������Լ�Ȩ��
	printf("%c%d\n", HT[number].c, HT[number].weight);
	fprintf(fp,"%c%d\n", HT[number].c, HT[number].weight);
	//�����Ҷ�ӽ����ֱ�ӷ���
	if (HT[number].leftson == 0 && HT[number].rightson == 0)
	{
		fclose(fp);
		return;
	}
	//�ȷ������ӣ��ٷ����Һ���
	fclose(fp);
	xiangeng(HT, HT[number].leftson, depth + 1);
	xiangeng(HT, HT[number].rightson, depth + 1);
}
//��ʼ������
int Init()
{
	int n;
	printf("��������Ľ�������\n");
	scanf("%d", &n);
	//����n�����
	node* HT;
	HT = CreateTree(n);
	BornHuffmanTree(HT, n, 2 * n - 1);
	return n;
}
//������
int main()
{
	int	n = Init();
	//�û�ѡ�����
	while (1)
	{
		Menu();
		int choice;
		scanf("%d", &choice);
		system("cls");
		switch (choice)
		{
			case 0:
				printf("��л����ʹ�ã�");
				system("pause");
				exit(0);
				break;
			case 1:
				encoding(n);
				break;
			case 2:
				decoding(n);
				break;
			case 3:
				Print();
				break;
			case 4:
				TreePrinting(n);
				system("pause");
				system("cls");
				break;
			default:
				printf("����������������룡��");
				system("pause");
				system("cls");
				break;
		}
	}
	system("pause");
	system("cls");
	return 0;
}