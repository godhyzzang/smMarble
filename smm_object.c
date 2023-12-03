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
       "강의",
       "식당",
       "실험실",
       "집",
       "실험실로이동",
       "음식찬스",
       "축제시간"
};

char* smmObj_getTypeName(int type)
{
    return (char*)smmNodeName[type];
}


//1,구조체 형식 정의
typedef struct smmObject {
    char name[MAX_CHARNAME];
    int type;
    int credit;
    int energy;
}smmObject_t; // struct 없이 간단사용 가능

//2. 구조체 배열 변수 정의
static smmObject_t smm_node[MAX_NODE]; 

static int smmObject_noNode = 0; //노드 개수 변수 초기화

//3. 관련함수 변경
//genNode
void smmObj_genNode(char* name, int type, int credit, int energy) { //문자는 char*포인터로
    strcpy(smm_node[smmObject_noNode].name, name); //문자는 단순대입 불가.strcpy필요
        smm_node[smmObject_noNode].type = type; 
        smm_node[smmObject_noNode].credit = credit;
        smm_node[smmObject_noNode].energy = energy;

        smmObj_noNode++;//node번호 +1 
}
//getNodeName
char* smmObj_getNodeName(int node_nr) { //noNode아님 node_nr로 새 변수 선언필요
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
