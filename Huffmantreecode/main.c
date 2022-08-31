#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 500;
//定义树结点的结构体
typedef struct node
{
	char c;//内容
	int weight;//权重
	int leftson;//左孩子
	int rightson;//右孩子
	int parents;//双亲
}node;

node* CreateTree(int n);//创建一颗简单的树
int FindMIN(node* HT, int n);//查找权重的最小结点编号
void BornHuffmanTree(node* HT, int n, int m);//生成哈夫曼树
void encoding(int n);//给给定字符串进行哈夫曼编码
void decoding(int n);//给字符串进行译码
void Print();//印代码文件
void TreePrinting(int n);//印哈夫曼树
int Init();//初始化
void xiangeng(node* HT, int n, int depth);//先根遍历哈夫曼树
void Menu();//显示菜单

//显示菜单
void Menu()
{
	//显示菜单，按键操作，供用户使用
	printf("请输入你的操作\n0.退出\n1.编码\n2.译码\n3.印代码文件\n4.印哈夫曼树\n");
}
//创建简单的树
node* CreateTree(int n)
{
	int m;
	m = 2 * n - 1;//创建哈夫曼树需要2n-1个结点
	node* HT = (node*)malloc(sizeof(node) * (m + 1));//从一开始存放数据
	int i;
	//初始化结点数据
	for (i = 0; i < m + 1; i++)
	{
		HT[i].leftson = 0;
		HT[i].rightson = 0;
		HT[i].parents = 0;
		HT[i].weight = 0;
		HT[i].c = '*';
	}
	printf("请输入数据和权重：\n");
	//去除回车符对结点内容的影响
	getchar();
	for (i = 1; i < n + 1; i++)
	{
		//读入结点的内容以及权重
		scanf("%c %d", &HT[i].c, &HT[i].weight);
		//去除回车符对结点内容的影响
		getchar();
	}
	return HT;
}
//找到最小权重的结点
int FindMIN(node* HT,int n)
{
	int i;
	int min0;
	int f = maxsize;
	//循环查找最小权重的结点
	for (i = 1; i <= n; i++)
	{
		if (HT[i].weight < f && HT[i].parents == 0)
		{
			min0 = i;
			f = HT[i].weight;
		}
	}
	//找到最小的结点标记，防止重复
	HT[min0].parents = 1;
	return min0;
}
//生成哈夫曼树
void BornHuffmanTree(node* HT,int n,int m)
{
	int min1, min2, i;
	//循环帮助扩大结点的范围，包括新建的加进来的结点
	for (i = n + 1; i <= m; i++)
	{
		min1 = FindMIN(HT, i - 1);//找到最小的结点
		min2 = FindMIN(HT, i - 1);//找到第二小的结点
		//构建哈夫曼树
		HT[min1].parents = i;
		HT[min2].parents = i;
		HT[i].leftson = min1;
		HT[i].rightson = min2;
		HT[i].weight = HT[min1].weight + HT[min2].weight;
		HT[i].c = '*';
	}
	//创建文件
	FILE* fp = fopen("hfmTree.txt", "w");
	for (i = 1; i <= 2 * n - 1; i++)
	{
		//将树节点的内容写入文件
		fprintf(fp,"%d\t%c\t%d\t%d\t%d\t%d\n", i, HT[i].c, HT[i].weight, HT[i].parents, HT[i].leftson, HT[i].rightson);
	}
	//关闭文件
	fclose(fp);
}
//编码函数
void encoding(int n)
{
	//打开存有数据的文件
	FILE* fp = fopen("hfmTree.txt", "r");
	node* HT = (node*)malloc(sizeof(node) * (2*n));
	int i;
	for (i = 1; i <= 2 * n - 1; i++)
	{
		//从文件中读入数据
		fscanf(fp, "%d\t%c\t%d\t%d\t%d\t%d\n", &i, &HT[i].c, &HT[i].weight, &HT[i].parents, &HT[i].leftson, &HT[i].rightson);
	}
	//创建存放每个结点编码的数组
	char** HC = (char*)malloc(sizeof(char*) * (n + 1));
	//字符数组中第一个字符对应的索引值
	int start;
	char* temp = (char*)malloc(sizeof(char) * n);
	//存放字符串的结尾字符
	temp[n - 1] = '\0';
	for (i = 1; i <= n; i++)
	{	
		//定义一个孩子结点
		int c = i;
		start = n - 1;
		int parents = HT[i].parents;
		while (parents != 0)
		{
			--start;
			//如果是左孩子则填入0
			if (HT[parents].leftson == c)
			{
				temp[start] = '0';
			}
			//如果是右孩子则填入1
			else
			{
				temp[start] = '1';
			}
			//不断向上回溯
			c = parents;
			parents = HT[parents].parents;
		}
		//分配对应的空间存放每个结点的编码
		HC[i] = (char*)malloc(sizeof(char) * (n - start));
		strcpy(HC[i], &temp[start]);
		printf("%c %s", HT[i].c, HC[i]);
	}
	//释放内存
	free(temp);
	fclose(fp);
	//打开存放编码的文件
	fp = fopen("CodeFile.txt", "w");
	//打开一开始存好的字符串
	FILE* fp0 = fopen("ToBeTran.txt", "r");
	while(!feof(fp0))
	{
		//从数据集中读入字符
		char c = fgetc(fp0);
		for (i = 1; i <= n; i++)
		{
			//找到相应的字符，存入编码
			if (HT[i].c == c)
			{
				fprintf(fp, "%s", HC[i]);
				break;
			}
		}
	}
	//关闭文件
	fclose(fp0);
	fclose(fp);
	//释放内存
	free(HT);
	for (int i = 1; i <= n; i++)
	{
		free(HC[i]);
	}
	free(HC);
	printf("编码成功！！！");
	system("pause");
	system("cls");
}
//译码函数
void decoding(int n)
{
	//文件操作
	FILE* fp1 = fopen("hfmTree.txt", "r");
	node* HT = (node*)malloc(sizeof(node) * (2 * n));
	int i;
	for (i = 1; i <= 2 * n - 1; i++)
	{
		fscanf(fp1, "%d\t%c\t%d\t%d\t%d\t%d\n", &i, &HT[i].c, &HT[i].weight, &HT[i].parents, &HT[i].leftson, &HT[i].rightson);
	}
	fclose(fp1);
	//打开编码文件，读入数据
	fp1 = fopen("CodeFile.txt", "r");
	int parents = 2 * n - 1;
	//打开译码后的文件，存放译码后的数据
	FILE* fp2 = fopen("TextFile.txt", "w");
	while (!feof(fp1))
	{
		char ch = fgetc(fp1);
		//如果是0，则为左孩子
		if (ch == '0')
		{
			parents = HT[parents].leftson;
		}
		//1为右孩子
		if(ch == '1')
		{
			parents = HT[parents].rightson;
		}
		//如果左右孩子都是0，则说明为叶子结点，找到了树节点的内容，存入数据
		if (HT[parents].leftson == 0 && HT[parents].rightson == 0)
		{
			char c = HT[parents].c;
			fprintf(fp2, "%c", c);
			parents = 2 * n - 1;
		}
	}
	//如果出现已输入的二进制编码不能完成译码操作
	if (parents != 2 * n - 1)
	{
		printf("输入的测试代码有误！！！");
	}
	//关闭文件
	fclose(fp1);
	fclose(fp2);
	printf("译码成功！！！");
	system("pause");
	system("cls");
}
//印代码文件函数
void Print()
{
	//打开文件，读入数据
	FILE* fp1 = fopen("CodeFile.txt", "r");
	FILE* fp2 = fopen("CodePrin.txt", "w");
	int i = 0;
	while (!feof(fp1))
	{
		char c = fgetc(fp1);
		printf("%c", c);
		i++;
		//每50换一行
		if (i % 50 == 0)
			printf("\n");
		fprintf(fp2, "%c", c);
	}
	//关闭文件
	fclose(fp1);
	fclose(fp2);
	printf("\n");
	system("pause");
	system("cls");
}
//印哈夫曼树函数
void TreePrinting(int n)
{
	FILE* fp0 = fopen("TreePrint.txt", "w");
	//将哈夫曼树读入
	FILE* fp1 = fopen("hfmTree.txt", "r");
	node* HT = (node*)malloc(sizeof(node) * (2 * n));
	int i;
	for (i = 1; i <= 2 * n - 1; i++)
	{
		fscanf(fp1, "%d\t%c\t%d\t%d\t%d\t%d\n", &i, &HT[i].c, &HT[i].weight, &HT[i].parents, &HT[i].leftson, &HT[i].rightson);
	}
	fclose(fp1);
	//先根遍历哈夫曼树
	fclose(fp0);
	xiangeng(HT, 2 * n - 1, 0);
}
//先根遍历函数
void xiangeng(node* HT, int number, int depth) 
{
	//由于涉及到递归，所以用追写操作进行写入文件
	FILE* fp = fopen("TreePrint.txt", "a");
	int i;
	//多少深度打印多少空格
	for (i = 0; i < depth; i++)
	{
		printf(" ");
		fprintf(fp, " ");
	}
	//打印树节点的内容以及权重
	printf("%c%d\n", HT[number].c, HT[number].weight);
	fprintf(fp,"%c%d\n", HT[number].c, HT[number].weight);
	//如果是叶子结点则直接返回
	if (HT[number].leftson == 0 && HT[number].rightson == 0)
	{
		fclose(fp);
		return;
	}
	//先访问左孩子，再访问右孩子
	fclose(fp);
	xiangeng(HT, HT[number].leftson, depth + 1);
	xiangeng(HT, HT[number].rightson, depth + 1);
}
//初始化函数
int Init()
{
	int n;
	printf("请输入你的结点个数：\n");
	scanf("%d", &n);
	//分配n个结点
	node* HT;
	HT = CreateTree(n);
	BornHuffmanTree(HT, n, 2 * n - 1);
	return n;
}
//主函数
int main()
{
	int	n = Init();
	//用户选择操作
	while (1)
	{
		Menu();
		int choice;
		scanf("%d", &choice);
		system("cls");
		switch (choice)
		{
			case 0:
				printf("感谢您的使用！");
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
				printf("输入错误！请重新输入！！");
				system("pause");
				system("cls");
				break;
		}
	}
	system("pause");
	system("cls");
	return 0;
}