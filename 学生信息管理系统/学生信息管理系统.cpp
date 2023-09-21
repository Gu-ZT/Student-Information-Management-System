#define _CRT_SECURE_NO_WARNINGS	  
#include<stdio.h>	 // scanf ; printf;
#include<stdlib.h>   // malloc free; //realloc calloc//�����ķ���
#include<assert.h>
#include<string.h>

struct Student
{
	char s_id[20];
	char s_name[20];
	char s_sex[10];
	char s_class[20];
	char s_major[20];
	int s_age;
};
typedef struct Student ElemType;//����������
typedef struct DuNode
{
	ElemType data;	  //   	56
	struct DuNode* prev; // 4
	struct DuNode* next;  // 4
}DuNode;

typedef struct
{
	struct DuNode* head;
	int cursize;
}DuLinkList;

struct DuNode* Buynode(struct DuNode* parg = nullptr, struct DuNode* narg = nullptr)//����һ�����
{
	struct DuNode* s = (struct DuNode*)malloc(sizeof(struct DuNode));//4+4+4=12���ֽ�
	if (nullptr == s) exit(EXIT_FAILURE);//���nullptr==s������ռ�ʧ��
	s->prev = (parg == nullptr ? s : parg);
	s->next = (narg == nullptr ? s : narg);
	return s;
}
void Freenode(struct DuNode* p)//�ͷſռ�
{
	free(p);
}

void InitList(DuLinkList* plist)//��ʼ������
{
	assert(plist != nullptr);
	plist->head = Buynode();//ͷ�����ڱ��ڵ�
	plist->cursize = 0;
}

int GetSize(DuLinkList* plist)
{
	assert(plist != nullptr);
	return plist->cursize;
}
bool Is_Empty(DuLinkList* plist)
{
	assert(plist != nullptr);
	return GetSize(plist) == 0;
}

void PrintList(DuLinkList* plist)//��ӡ����
{
	assert(plist != nullptr);
	struct DuNode* p = plist->head->next; // ��ʱpָ���һ�������ݵĽ��
	while (p != plist->head)
	{
		//printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

struct DuNode* FindValue(DuLinkList* plist, ElemType val)//��ѯ����
{
	assert(plist != nullptr);
	struct DuNode* p = plist->head->next; // 
	//while (p != plist->head && p->data!= val)
	{
		p = p->next;
	}
	if (p == plist->head)
	{
		p = nullptr;
	}
	return p;
}

bool InsertNode(DuLinkList* plist, struct DuNode* ptr, struct DuNode* newnode)//����һ�����
{
	assert(plist != nullptr);
	if (ptr == nullptr || newnode == nullptr)//������һ��Ϊ�վ��޷����в���
	{
		return false;//����ʧ��
	}
	newnode->next = ptr; // 1
	newnode->prev = ptr->prev;	//2
	ptr->prev->next = newnode; // 3
	ptr->prev = newnode;    // 4
	plist->cursize += 1;
	return true;
}
bool Push_back(DuLinkList* plist, ElemType val)//���뵽��ǰ�б�ĩβ
{
	assert(plist != nullptr);
	struct DuNode* newnode = Buynode();
	newnode->data = val;
	return InsertNode(plist, plist->head, newnode);
}
bool Push_front(DuLinkList* plist, ElemType val)////���뵽��ǰ�б�ǰ��
{
	assert(plist != nullptr);
	struct DuNode* newnode = Buynode();
	newnode->data = val;
	return InsertNode(plist, plist->head->next, newnode);
}
bool EarseList(DuLinkList* plist, struct DuNode* ptr)//ɾ�����
{
	assert(plist != nullptr);
	if (nullptr == ptr) return false;
	ptr->prev->next = ptr->next;
	ptr->next->prev = ptr->prev;
	plist->cursize -= 1;
	printf("ɾ���ɹ�\n");
	return true;
}
bool Pop_back(DuLinkList* plist)//ɾ�����һ�����ݽ��
{
	assert(plist != nullptr);
	if (Is_Empty(plist)) return false;
	return EarseList(plist, plist->head->prev);
}
bool Pop_front(DuLinkList* plist)//ɾ����һ�����ݽ��
{
	assert(plist != nullptr);
	if (Is_Empty(plist)) return false;
	return EarseList(plist, plist->head->next);
}

struct DuNode* FindStudentId(DuLinkList* plist, char id[]);
bool Remove(DuLinkList* plist, char stuId[])//ɾ�����
{
	assert(plist != nullptr);
	struct DuNode* p = FindStudentId(plist, stuId);
	if (nullptr == p) return false;
	return EarseList(plist, p);
}

void ClearList(DuLinkList* plist)
{
	assert(plist != nullptr);
	while (!Is_Empty(plist))
	{
		Pop_back(plist);
	}
}
void DestroyList(DuLinkList* plist)//�ݻ�����
{
	assert(plist != nullptr);
	ClearList(plist);
	Freenode(plist->head);
	plist->head = nullptr;
}
int FindMenu()
{
	int select = 0;
	printf("*****ѧ���Ĳ�ѯ*****\n");
	printf("*  1. ��ѧ�Ų�ѯ   *\n");
	printf("*  2. ��������ѯ   *\n");
	printf("*  3. ���Ա��ѯ   *\n");
	printf("*  4. �������ѯ   *\n");
	printf("*  5. ��רҵ��ѯ   *\n");
	printf("*  0. �˳���ѯ     *\n");
	printf("********************\n");
	printf("��ѡ��..... \n");
	scanf("%d", &select);
	return select;
}

int MainMenu()
{
	int select = 0;
	printf("*********ѧ����Ϣ����ϵͳ*********\n");
	printf("* 1. ���                2.��ѯ*\n");
	printf("* 3. �޸�                4.רҵͳ��*\n");
	printf("* 5. ��ʾ                6.�Ա�ͳ��*\n");
	printf("* 7. ����ͳ��            8.ɾ��*\n");
	printf("* 9. ����                0.�˳�*\n");
	printf("******************************\n");
	printf("��ѡ��..... \n");
	scanf("%d", &select);
	return select;
}


void AddStudent(DuLinkList* plist)
{
	assert(plist != nullptr);
	struct Student tmp = {};
	printf("������ѧ����ѧ��: ");
	scanf("%s", tmp.s_id);
	printf("������ѧ��������: ");
	scanf("%s", tmp.s_name);
	printf("������ѧ�����Ա�: ");
	scanf("%s", tmp.s_sex);
	printf("������ѧ��������: ");
	scanf("%d", &tmp.s_age);
	printf("������ѧ����רҵ: ");
	scanf("%s", tmp.s_major);
	Push_back(plist, tmp);
}

//��ʾѧ����Ϣ
void PrintStudent(struct DuNode* p)
{
	assert(p != nullptr);
	printf("id: %-20s name: %-20s sex: %-10s age : %-8d  major:%-20s \n",
		p->data.s_id, p->data.s_name, p->data.s_sex, p->data.s_age, p->data.s_major);
}
void ShowStudent(DuLinkList* plist)
{
	assert(plist != nullptr);
	struct DuNode* p = plist->head->next; // first;
	while (p != plist->head)
	{
		PrintStudent(p);
		p = p->next;
	}
	printf("\n-------------------------------------\n");
}


//����ѧ��
void FindStudent_Id(DuLinkList* plist, char id[])
{
	assert(plist != nullptr);
	struct DuNode* p = plist->head->next;
	while (p != plist->head)
	{
		if (strcmp(p->data.s_id, id) == 0)
		{
			PrintStudent(p);
		}
		p = p->next;
	}

}

struct DuNode* FindStudentId(DuLinkList* plist, char id[])
{
	assert(plist != nullptr);
	struct DuNode* p = plist->head->next;
	while (p != plist->head)
	{
		if (strcmp(p->data.s_id, id) == 0)
		{
			return p;

		}
		p = p->next;
	}
	return nullptr;
}

void FindStudent_Name(DuLinkList* plist, char name[])
{
	assert(plist != nullptr);
	struct DuNode* p = plist->head->next;
	while (p != plist->head)
	{
		if (strcmp(p->data.s_name, name) == 0)
		{
			PrintStudent(p);
		}
		p = p->next;
	}

}

void FindStudent_Sex(DuLinkList* plist, char sex[])
{
	assert(plist != nullptr);
	struct DuNode* p = plist->head->next;
	while (p != plist->head)
	{
		if (strcmp(p->data.s_sex, sex) == 0)
		{
			PrintStudent(p);
		}
		p = p->next;
	}

}
void FindStudent_Major(DuLinkList* plist, char major[])
{
	assert(plist != nullptr);
	struct DuNode* p = plist->head->next;
	while (p != plist->head)
	{
		if (strcmp(p->data.s_major, major) == 0)
		{
			PrintStudent(p);
		}
		p = p->next;
	}

}
void FindStudent_Age(DuLinkList* plist, int age)
{
	assert(plist != nullptr);
	struct DuNode* p = plist->head->next;
	while (p != plist->head)
	{
		if (p->data.s_age == age)
		{
			PrintStudent(p);
		}
		p = p->next;
	}

}

void FindStudent(DuLinkList* plist)
{
	assert(plist != nullptr);
	char id[20] = {};
	char name[20] = {};
	char sex[10] = {};
	char major[20] = {};

	int age = 0;
	int select = 0;
	do
	{
		select = FindMenu();
		switch (select)
		{
		case 0: break;
		case 1:
			printf("����ѧ����ѧ��: ");
			scanf("%s", id);
			FindStudent_Id(plist, id);
			break;
		case 2:
			printf("����ѧ��������: ");
			scanf("%s", name);
			FindStudent_Name(plist, name);
			break;
		case 3:
			printf("����ѧ�����Ա�: ");
			scanf("%s", sex);
			FindStudent_Sex(plist, sex);
			break;
		case 4:
			printf("����ѧ��������: ");
			scanf("%d", &age);
			FindStudent_Age(plist, age);
			break;
		case 5:
			printf("����ѧ����רҵ: ");
			scanf("%s", major);
			FindStudent_Major(plist, major);
			break;
		default:
			printf("ѡ����� .... ����ѡ�� \n");
			break;
		}
	} while (select != 0);
}


//�����Ա�ͳ��
void CountGender(DuLinkList* plist) {
	assert(plist != nullptr);
	struct DuNode* p = plist->head->next;

	int male_count = 0;
	int female_count = 0;
	while (p != plist->head) {
		if (strcmp(p->data.s_sex, "��")) {
			male_count++;
		}
		else if (strcmp(p->data.s_sex, "Ů")) {
			female_count++;
		}
		p = p->next;
	}
	printf("Ů��������%d\n", male_count);
	printf("����������%d\n", female_count);
}
//����רҵͳ��
void CountStudent_Major(DuLinkList* plist, char major[])
{
	assert(plist != nullptr);
	struct DuNode* p = plist->head->next;
	int count = 0;
	while (p != plist->head)
	{
		if (strcmp(p->data.s_major, major) == 0)
		{
			count++;
		}
		p = p->next;
	}
	printf("רҵ %s ��ѧ������Ϊ: %d\n", major, count);
}

//��������
void CountStudent_Age(DuLinkList* plist, int age)
{
	assert(plist != nullptr);
	int count = 0;
	struct DuNode* p = plist->head->next;
	while (p != plist->head)
	{
		if (p->data.s_age == age)
		{
			count++;
		}
		p = p->next;
	}
	printf("Age %d: %d students\n", age, count);
}


void SaveFile(DuLinkList* plist)
{
	assert(plist != nullptr);
	FILE* fp = fopen("stud.txt", "w"); // "w" "r" "a" "wb" "rb" "ab" 
	if (fp == nullptr) return;
	fprintf(fp, "%d\n", GetSize(plist));
	struct DuNode* p = plist->head->next; // first
	while (p != plist->head)
	{
		fprintf(fp, "%s %s %s %d \n",
			p->data.s_id, p->data.s_name, p->data.s_sex, p->data.s_age);
		p = p->next;
	}
	fclose(fp); // 
	fp = nullptr;
}
void LoadFile(DuLinkList* plist)
{
	assert(plist != nullptr);
	int num = 0;
	struct Student tmp = {};
	FILE* fp = fopen("stud.txt", "r");
	if (nullptr == fp) return;
	fscanf(fp, "%d", &num);
	for (int i = 0; i < num; ++i)
	{
		fscanf(fp, "%s %s %s %d  %s", tmp.s_id, tmp.s_name, tmp.s_sex, &tmp.s_age, tmp.s_major);
		Push_back(plist, tmp);
	}
	fclose(fp);
	fp = nullptr;
}
void ModifyStudent(DuLinkList* plist, char name[])
{

	assert(plist != nullptr);
	struct DuNode* p = plist->head->next;
	while (p != plist->head)
	{
		if (strcmp(p->data.s_name, name) == 0)
		{
			printf("��ѧ��ѧ��Ϊ��%s\n", p->data.s_id);
			printf("�������µ�ѧ�ţ�\n");
			scanf("%s", p->data.s_id);

			printf("��ѧ������Ϊ��%s\n", p->data.s_name);
			printf("�������µ�������\n");
			scanf("%s", p->data.s_name);

			printf("��ѧ���Ա�Ϊ��%s\n", p->data.s_sex);
			printf("�������µ��Ա�\n");
			scanf("%s", p->data.s_sex);

			printf("��ѧ������Ϊ��%d\n", p->data.s_age);
			printf("�������µ����䣺\n");
			scanf("%d", &(p->data.s_age));

			printf("��ѧ��רҵΪ��%s\n", p->data.s_major);
			printf("�������µ�רҵ��\n");
			scanf("%s", p->data.s_major);

		}
		p = p->next;
	}
}
struct Student InputStudent()
{
	struct Student temp = {};
	printf("����ѧ����ѧ��");
	scanf("%s", temp.s_id);
	printf("����ѧ��������");
	scanf("%s", temp.s_name);
	printf("����ѧ�����Ա�");
	scanf("%s", temp.s_sex);
	printf("����ѧ��������");
	scanf("%d", &(temp.s_id));
	printf("����ѧ����רҵ");
	scanf("%s", temp.s_major);
	return temp;


}

int main()
{

	DuLinkList studlist;
	struct Student temp;
	int select = 0;

	InitList(&studlist);
	LoadFile(&studlist);
	DuLinkList plist = studlist;

	do
	{
		select = MainMenu();
		switch (select)
		{
		case 0: printf("�˳�ϵͳ.....\n");  break;
		case 1:
			AddStudent(&studlist);
			break;
		case 2:
			FindStudent(&studlist);
			break;
		case 3:
			char name[20];
			printf("�������޸���Ϣѧ��������: ");
			scanf("%s", name);
			ModifyStudent(&studlist, name);

			break;
		case 4: char major[20];
			printf("������Ҫͳ�Ƶ�רҵ: ");
			scanf("%s", major);
			CountStudent_Major(&studlist, major);
			break;
		case 5:
			ShowStudent(&studlist);
			break;
		case 6:CountGender(&studlist);
			break;
		case 7:
			int age;
			printf("������Ҫͳ�Ƶ�����: ");
			scanf("%d", &age);
			CountStudent_Age(&studlist, age);
			break;

		case 8:
			char stuId[20];
			printf("������Ҫɾ����ѧ����ѧ��: ");
			scanf("%s", stuId);
			Remove(&studlist, stuId);
			break;
		case 9:
		{
			char id[20];
			struct DuNode* newnode = Buynode();
			printf("������Ҫ���ĸ�ѧ��֮ǰ����ѧ����Ϣ:");
			scanf("%s", id);
			struct DuNode* p = FindStudentId(&studlist, id);
			assert(p != nullptr);
			printf("�����������ѧ����ѧ��:");
			scanf("%s", newnode->data.s_id);
			printf("�����������ѧ��������:");
			scanf("%s", newnode->data.s_name);
			printf("�����������ѧ�����Ա�:");
			scanf("%s", newnode->data.s_sex);
			printf("�����������ѧ��������:");
			scanf("%d", &(newnode->data.s_age));
			printf("�����������ѧ����רҵ:");
			scanf("%s", newnode->data.s_major);
			InsertNode(&studlist, p, newnode);
			printf("����ɹ�");
			break;
		}
		default:
			printf("ѡ����� .... ����ѡ�� \n");
			break;
		}
	} while (select != 0);

	SaveFile(&studlist);
	DestroyList(&studlist);
	return 0;
}