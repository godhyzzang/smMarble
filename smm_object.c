//
//  smm_object.h
//  SMMarble object
//
//  Created by Juyeop Kim on 2023/11/05.
//

#include "smm_common_h";
#include "smm_object_h";
#include <stdio.h>

#define MAX_TYPE 7
#define MAX_GRADE 9
#define MAX_NODE 100 





static char smmNodeName[SMMNODE_TYPE_MAX][MAX_CHARNAME] = {
       "����",
       "�Ĵ�",
       "�����",
       "��",
       "����Ƿ��̵�",
       "��������",
       "�����ð�"
};

char* smmObj_getTypeName(int type)
{
    return (char*)smmNodeName[type];
}


//1,����ü ���� ����
typedef struct smmObject {
    char name[MAX_CHARNAME];
    int type;
    int credit;
    int energy;
}smmObject_t; // struct ���� ���ܻ�� ����

//2. ����ü �迭 ���� ����
static smmObject_t smm_node[MAX_NODE]; 

static int smmObject_noNode = 0; //��� ���� ���� �ʱ�ȭ

//3. �����Լ� ����
//genNode
void smmObj_genNode(char* name, int type, int credit, int energy) { //���ڴ� char*�����ͷ�
    strcpy(smm_node[smmObject_noNode].name, name); //���ڴ� �ܼ����� �Ұ�.strcpy�ʿ�
        smm_node[smmObject_noNode].type = type; 
        smm_node[smmObject_noNode].credit = credit;
        smm_node[smmObject_noNode].energy = energy;

        smmObj_noNode++;//node��ȣ +1 
}
//getNodeName
char* smmObj_getNodeName(int node_nr) { //noNode�ƴ� node_nr�� �� ���� �����ʿ�
    return smm_node[int node_nr];
}
// 
//getNodeType
int smmObj_getNodeType(int node_nr)
{
    return smm_node[node_nr].type;
}
//getNodeCredit
int smmObj_getNodeCredit(int node_nr)
{
    return smm_node[node_nr].credit;
}
//getNodeEnergy
int smmObj_getNodeEnergy(int node_nr)
{
    return smm_node[node_nr].energy;
}
