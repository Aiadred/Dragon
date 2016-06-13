#pragma once
#include <hash_map>
#include "Public.h"
#include "MakeMove.h"
using namespace std;
//�����û���			1.ʹ�����ݽṹΪhash��map����¼��Ϣ�ֱ�Ϊ1.��ǰ���̵�keyֵ 2.��� 3.alpha��beta 4.Evalute
//						2.�������ڵ��ֵ���Ǿ�ȷ�ڿ���Ҷ�ڵ��ֵ������ֱ�ӵ���map�е�ֵ�����ظ�����
//						3.����Ҫ��ÿ������ʱ���hashmap���ϴε��������ͬ������Ӧ�õ��´�
//							p.s.�����ö��hashmap��¼��ͬ��ε�ֵ������ͬ�Ĳ��������
//						4.hash-mapԽ��ɢ�г̶�Խ�ã����ǻ��б��͵�
//						
//				pro		1.�Ƿ���Ҷ�ڵ����hash_map,�ӽڵ����hashmap���ɻ��ʡ��ֵ���ѵ�ʱ��
//						2.���ڳ�ͻ���⣬�д���ȶ
//
//
enum entry_type{exact,lower_bound,upper_bound};
typedef struct HASHITEM
{
	LONGLONG Checksum;
	entry_type	Data_type;
	short nPly;
	int Eval;
}HashItem;

class CTrans_Table
{
public:
	CTrans_Table(void);
	virtual ~CTrans_Table(void);
public:
	//�������̼���keyֵ
	void CaculateInitHashKey(int (*Board_Input)[8]);
	//�����߷������µ�keyֵ
	void MakeMoveHashKey(CNodeChessInfo Chess_Input,int (*Board_Input)[8],int Turn);
	//�����߷������µ�keyֵ
	void ResetMoveHashKey(CNodeChessInfo Chess_Input,int (*Board_Input)[8],int Turn,int (*ValueBuff)[100]);
	//��ѯhash_map��ǰ�ڵ�����
	int SearchHashKey(int Alpha,int Beta,int nPly,int Turn);
	//����ǰ�ڵ�ֵѹ��Hash_map
	void PushNodeIntoHash(entry_type entry_type,int Evalute,short nPly,int Turn);
	//��ʼ��������鴴��Hash_map
	void SrandBulidHash();

	int ChessChoose(int nTypeChess);
public:
	UINT m_nHashKey_32[4][8][8];
	LONGLONG m_nHashKey_64[4][8][8];
	HashItem *m_pTT[2];
	UINT m_HashKey_32;
	LONGLONG m_HashKey_64;
};

