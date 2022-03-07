// Searchengine.h: interface for the Searchengine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEARCHENGINE_H__2079319B_9CE5_4036_8219_7B2F9AAB5712__INCLUDED_)
#define AFX_SEARCHENGINE_H__2079319B_9CE5_4036_8219_7B2F9AAB5712__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include"MoveGenerator.h"
#include"EvaluationFunction.h"
#endif // _MSC_VER > 1000

# define CUT_NODE 1
# define ALL_NODE -1
# define PV_NODE 0
const int PHASE_HASH = 0;
const int PHASE_KILLER1 = 1;
const int PHASE_KILLER2 = 2;
const int PHASE_CreatePM = 3;
enum ENTRY_TYPE {
    exact,
    lower_bound,
    upper_bound
};
typedef struct HASHITEM {
    LONGLONG checksum;    // or long long might be even better
    ENTRY_TYPE entry_type;
    short depth;
    double eval;
    Move hashMove;
} HashItem;

class SearchEngine {
public:
    SearchEngine();

    virtual ~SearchEngine();

    Move searchMove(BYTE position[][12], bool side, int &md_, int &score_, int &node_);

    BYTE makeMove(Move *MOVE);

    void unMakeMove(Move *MOVE, BYTE ID);

    //////////////////searchengine//////////////////////////
    double sR(int depth, int node_type, bool side);

    double moveScore(double alpha, double beta, int depth, int node_type);

    int sortMove(int depth, int count, bool flag, double score);

    friend bool Valid(Move move);

    friend bool rules(int x, int y, int xx, int yy);

    friend bool xor(
     Move move1 ,
     Move move2
    );

    friend bool testMove(int depth, int count, Move mv);

    void SetBestMove(Move MV, int depth);

    //////////////////   ////////////////////////////
    //////////////history heustic/////////////////////////////////
    int *m_HistoryTable;

    BYTE GetHistoryScore(Move *MOVE);

    void EnterHistoryScore(Move *MOVE, int depth);

    void qrs(int depth, int left, int right);

/////////////////Hash Table////////////////////////////////////
    void InitializeHashKey();

    void CalculateInitHashKey(BYTE position[][12]);

    void Hash_MakeMove(Move *MOVE, BYTE position[][12]);

    void Hash_UnMakeMove(Move *MOVE, BYTE position[][12]);

    double LookUpHashTable(double alpha, double beta, int depth, Move &mv);

    void EnterHashTable(ENTRY_TYPE entry_type, double eval, short depth, Move mv);
/////////////////////////////////////////////////////////////////
public:
    HashItem *m_p_TT;
    UINT m_nHashKey32[4][10][10];
    ULONGLONG m_ulHashKey64[4][10][10];
    UINT m_HashKey32;
    LONGLONG m_HashKey64;
    EvaluationFunction *p_evaluation;//π¿÷µ∫À–ƒ÷∏’Î
    Move bestMove;
    int maxDepth;
};

#endif // !defined(AFX_SEARCHENGINE_H__2079319B_9CE5_4036_8219_7B2F9AAB5712__INCLUDED_)
