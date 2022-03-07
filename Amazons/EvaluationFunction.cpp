// evaluationfunction.cpp: implementation of the evaluationfunction class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EvaluationFunction.h"
#include<math.h>

#ifdef _DEBUG
                                                                                                                        #undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
// evaluationfunction

EvaluationFunction::EvaluationFunction() {

}

EvaluationFunction::~EvaluationFunction() {

}

void EvaluationFunction::KingMoveSearch() {
    int i, j;
    for (i = 0; i < 12; i++) {
        for (j = 0; j < 12; j++) {

            kingMoveWhite[i][j] = 0;//初始化为0
            kingMoveBlack[i][j] = 0;

        }
    }

    for (i = 0; i < 12; i++) {
        for (j = 0; j < 12; j++) {
            if (currentPosition[i][j] == 2)//white king 1
            {
                if (currentPosition[i - 1][j - 1] == 0) { kingMoveWhite[i - 1][j - 1] = 1; }

                if (currentPosition[i - 1][j] == 0) { kingMoveWhite[i - 1][j] = 1; }

                if (currentPosition[i - 1][j + 1] == 0) { kingMoveWhite[i - 1][j + 1] = 1; }

                if (currentPosition[i][j - 1] == 0) { kingMoveWhite[i][j - 1] = 1; }

                if (currentPosition[i][j + 1] == 0) { kingMoveWhite[i][j + 1] = 1; }

                if (currentPosition[i + 1][j - 1] == 0) { kingMoveWhite[i + 1][j - 1] = 1; }

                if (currentPosition[i + 1][j] == 0) { kingMoveWhite[i + 1][j] = 1; }

                if (currentPosition[i + 1][j + 1] == 0) { kingMoveWhite[i + 1][j + 1] = 1; }
            }

            if (currentPosition[i][j] == 3)//black king 1
            {
                if (currentPosition[i - 1][j - 1] == 0) { kingMoveBlack[i - 1][j - 1] = 1; }

                if (currentPosition[i - 1][j] == 0) { kingMoveBlack[i - 1][j] = 1; }

                if (currentPosition[i - 1][j + 1] == 0) { kingMoveBlack[i - 1][j + 1] = 1; }

                if (currentPosition[i][j - 1] == 0) { kingMoveBlack[i][j - 1] = 1; }

                if (currentPosition[i][j + 1] == 0) { kingMoveBlack[i][j + 1] = 1; }

                if (currentPosition[i + 1][j - 1] == 0) { kingMoveBlack[i + 1][j - 1] = 1; }

                if (currentPosition[i + 1][j] == 0) { kingMoveBlack[i + 1][j] = 1; }

                if (currentPosition[i + 1][j + 1] == 0) { kingMoveBlack[i + 1][j + 1] = 1; }
            }
        }
    }

    for (int n = 1; n < 11; n++) {
        for (i = 0; i < 12; i++) {
            for (j = 0; j < 12; j++) {
                if (kingMoveWhite[i][j] == n)//white king 2-10
                {
                    if (currentPosition[i - 1][j - 1] == 0 && kingMoveWhite[i - 1][j - 1] == 0) {
                        kingMoveWhite[i - 1][j - 1] = n + 1;
                    }

                    if (currentPosition[i - 1][j] == 0 && kingMoveWhite[i - 1][j] == 0) {
                        kingMoveWhite[i - 1][j] = n + 1;
                    }

                    if (currentPosition[i - 1][j + 1] == 0 && kingMoveWhite[i - 1][j + 1] == 0) {
                        kingMoveWhite[i - 1][j + 1] = n + 1;
                    }

                    if (currentPosition[i][j - 1] == 0 && kingMoveWhite[i][j - 1] == 0) {
                        kingMoveWhite[i][j - 1] = n + 1;
                    }

                    if (currentPosition[i][j + 1] == 0 && kingMoveWhite[i][j + 1] == 0) {
                        kingMoveWhite[i][j + 1] = n + 1;
                    }

                    if (currentPosition[i + 1][j - 1] == 0 && kingMoveWhite[i + 1][j - 1] == 0) {
                        kingMoveWhite[i + 1][j - 1] = n + 1;
                    }

                    if (currentPosition[i + 1][j] == 0 && kingMoveWhite[i + 1][j] == 0) {
                        kingMoveWhite[i + 1][j] = n + 1;
                    }

                    if (currentPosition[i + 1][j + 1] == 0 && kingMoveWhite[i + 1][j + 1] == 0) {
                        kingMoveWhite[i + 1][j + 1] = n + 1;
                    }
                }

                if (kingMoveBlack[i][j] == n)//black king 2-10
                {
                    if (currentPosition[i - 1][j - 1] == 0 && kingMoveBlack[i - 1][j - 1] == 0) {
                        kingMoveBlack[i - 1][j - 1] = n + 1;
                    }

                    if (currentPosition[i - 1][j] == 0 && kingMoveBlack[i - 1][j] == 0) {
                        kingMoveBlack[i - 1][j] = n + 1;
                    }

                    if (currentPosition[i - 1][j + 1] == 0 && kingMoveBlack[i - 1][j + 1] == 0) {
                        kingMoveBlack[i - 1][j + 1] = n + 1;
                    }

                    if (currentPosition[i][j - 1] == 0 && kingMoveBlack[i][j - 1] == 0) {
                        kingMoveBlack[i][j - 1] = n + 1;
                    }

                    if (currentPosition[i][j + 1] == 0 && kingMoveBlack[i][j + 1] == 0) {
                        kingMoveBlack[i][j + 1] = n + 1;
                    }

                    if (currentPosition[i + 1][j - 1] == 0 && kingMoveBlack[i + 1][j - 1] == 0) {
                        kingMoveBlack[i + 1][j - 1] = n + 1;
                    }

                    if (currentPosition[i + 1][j] == 0 && kingMoveBlack[i + 1][j] == 0) {
                        kingMoveBlack[i + 1][j] = n + 1;
                    }

                    if (currentPosition[i + 1][j + 1] == 0 && kingMoveBlack[i + 1][j + 1] == 0) {
                        kingMoveBlack[i + 1][j + 1] = n + 1;
                    }
                }
            }
        }
    }
}

void EvaluationFunction::copy(BYTE position[][12]) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            currentPosition[i][j] = position[i][j];
        }
    }
}

void EvaluationFunction::QueenMoveSearch() {
    int i, j, k, l;
    for (i = 0; i < 12; i++) {
        for (j = 0; j < 12; j++) {


            queenMoveWhite[i][j] = 0;
            queenMoveBlack[i][j] = 0;
        }
    }
    for (int k = 0; k < 12; k++) {
        for (int l = 0; l < 12; l++) {
            if (currentPosition[k][l] == 2)//白方queen1
            {
                i = k;
                j = l;
                while (currentPosition[i - 1][j - 1] == 0 || queenMoveWhite[i - 1][j - 1] == 1) {
                    queenMoveWhite[i - 1][j - 1] = 1;
                    i--;
                    j--;
                }
                i = k;
                j = l;
                while (currentPosition[i - 1][j] == 0 || queenMoveWhite[i - 1][j] == 1) {
                    queenMoveWhite[i - 1][j] = 1;
                    i--;
                }
                i = k;
                j = l;
                while (currentPosition[i - 1][j + 1] == 0 || queenMoveWhite[i - 1][j + 1] == 1) {
                    queenMoveWhite[i - 1][j + 1] = 1;
                    i--;
                    j++;
                }
                i = k;
                j = l;
                while (currentPosition[i][j - 1] == 0 || queenMoveWhite[i][j - 1] == 1) {
                    queenMoveWhite[i][j - 1] = 1;
                    j--;
                }
                i = k;
                j = l;
                while (currentPosition[i][j + 1] == 0 || queenMoveWhite[i][j + 1] == 1) {
                    queenMoveWhite[i][j + 1] = 1;
                    j++;
                }
                i = k;
                j = l;
                while (currentPosition[i + 1][j - 1] == 0 || queenMoveWhite[i + 1][j - 1] == 1) {
                    queenMoveWhite[i + 1][j - 1] = 1;
                    i++;
                    j--;
                }
                i = k;
                j = l;
                while (currentPosition[i + 1][j] == 0 || queenMoveWhite[i + 1][j] == 1) {
                    queenMoveWhite[i + 1][j] = 1;
                    i++;
                }
                i = k;
                j = l;
                while (currentPosition[i + 1][j + 1] == 0 || queenMoveWhite[i + 1][j + 1] == 1) {
                    queenMoveWhite[i + 1][j + 1] = 1;
                    i++;
                    j++;
                }
            }

            if (currentPosition[k][l] == 3)//黑方queen1
            {
                i = k;
                j = l;
                while (currentPosition[i - 1][j - 1] == 0 || queenMoveBlack[i - 1][j - 1] == 1) {
                    queenMoveBlack[i - 1][j - 1] = 1;
                    i--;
                    j--;
                }
                i = k;
                j = l;
                while (currentPosition[i - 1][j] == 0 || queenMoveBlack[i - 1][j] == 1) {
                    queenMoveBlack[i - 1][j] = 1;
                    i--;
                }
                i = k;
                j = l;
                while (currentPosition[i - 1][j + 1] == 0 || queenMoveBlack[i - 1][j + 1] == 1) {
                    queenMoveBlack[i - 1][j + 1] = 1;
                    i--;
                    j++;
                }
                i = k;
                j = l;
                while (currentPosition[i][j - 1] == 0 || queenMoveBlack[i][j - 1] == 1) {
                    queenMoveBlack[i][j - 1] = 1;
                    j--;
                }
                i = k;
                j = l;
                while (currentPosition[i][j + 1] == 0 || queenMoveBlack[i][j + 1] == 1) {
                    queenMoveBlack[i][j + 1] = 1;
                    j++;
                }
                i = k;
                j = l;
                while (currentPosition[i + 1][j - 1] == 0 || queenMoveBlack[i + 1][j - 1] == 1) {
                    queenMoveBlack[i + 1][j - 1] = 1;
                    i++;
                    j--;
                }
                i = k;
                j = l;
                while (currentPosition[i + 1][j] == 0 || queenMoveBlack[i + 1][j] == 1) {
                    queenMoveBlack[i + 1][j] = 1;
                    i++;
                }
                i = k;
                j = l;
                while (currentPosition[i + 1][j + 1] == 0 || queenMoveBlack[i + 1][j + 1] == 1) {
                    queenMoveBlack[i + 1][j + 1] = 1;
                    i++;
                    j++;
                }

            }
        }
    }

    for (int n = 1; n < 6; n++) {
        for (k = 0; k < 12; k++) {
            for (int l = 0; l < 12; l++) {
                if (queenMoveWhite[k][l] == n)//白方queen2-5
                {

                    i = k;
                    j = l;
                    while ((queenMoveWhite[i - 1][j - 1] == 0 || queenMoveWhite[i - 1][j - 1] == n + 1) &&
                           currentPosition[i - 1][j - 1] == 0) {
                        queenMoveWhite[i - 1][j - 1] = n + 1;
                        i--;
                        j--;
                    }
                    i = k;
                    j = l;
                    while ((queenMoveWhite[i - 1][j] == 0 || queenMoveWhite[i - 1][j] == n + 1) &&
                           currentPosition[i - 1][j] == 0) {
                        queenMoveWhite[i - 1][j] = n + 1;
                        i--;
                    }
                    i = k;
                    j = l;
                    while ((queenMoveWhite[i - 1][j + 1] == 0 || queenMoveWhite[i - 1][j + 1] == n + 1) &&
                           currentPosition[i - 1][j + 1] == 0) {
                        queenMoveWhite[i - 1][j + 1] = n + 1;
                        i--;
                        j++;
                    }
                    i = k;
                    j = l;
                    while ((queenMoveWhite[i][j - 1] == 0 || queenMoveWhite[i][j - 1] == n + 1) &&
                           currentPosition[i][j - 1] == 0) {
                        queenMoveWhite[i][j - 1] = n + 1;
                        j--;
                    }
                    i = k;
                    j = l;
                    while ((queenMoveWhite[i][j + 1] == 0 || queenMoveWhite[i][j + 1] == n + 1) &&
                           currentPosition[i][j + 1] == 0) {
                        queenMoveWhite[i][j + 1] = n + 1;
                        j++;
                    }
                    i = k;
                    j = l;
                    while ((queenMoveWhite[i + 1][j - 1] == 0 || queenMoveWhite[i + 1][j - 1] == n + 1) &&
                           currentPosition[i + 1][j - 1] == 0) {
                        queenMoveWhite[i + 1][j - 1] = n + 1;
                        i++;
                        j--;
                    }
                    i = k;
                    j = l;
                    while ((queenMoveWhite[i + 1][j] == 0 || queenMoveWhite[i + 1][j] == n + 1) &&
                           currentPosition[i + 1][j] == 0) {
                        queenMoveWhite[i + 1][j] = n + 1;
                        i++;
                    }
                    i = k;
                    j = l;
                    while ((queenMoveWhite[i + 1][j + 1] == 0 || queenMoveWhite[i + 1][j + 1] == n + 1) &&
                           currentPosition[i + 1][j + 1] == 0) {
                        queenMoveWhite[i + 1][j + 1] = n + 1;
                        i++;
                        j++;
                    }

                }

                if (queenMoveBlack[k][l] == n)//黑方queen2-5
                {
                    i = k;
                    j = l;
                    while ((queenMoveBlack[i - 1][j - 1] == 0 || queenMoveBlack[i - 1][j - 1] == n + 1) &&
                           currentPosition[i - 1][j - 1] == 0) {
                        queenMoveBlack[i - 1][j - 1] = n + 1;
                        i--;
                        j--;
                    }
                    i = k;
                    j = l;
                    while ((queenMoveBlack[i - 1][j] == 0 || queenMoveBlack[i - 1][j] == n + 1) &&
                           currentPosition[i - 1][j] == 0) {
                        queenMoveBlack[i - 1][j] = n + 1;
                        i--;
                    }
                    i = k;
                    j = l;
                    while ((queenMoveBlack[i - 1][j + 1] == 0 || queenMoveBlack[i - 1][j + 1] == n + 1) &&
                           currentPosition[i - 1][j + 1] == 0) {
                        queenMoveBlack[i - 1][j + 1] = n + 1;
                        i--;
                        j++;
                    }
                    i = k;
                    j = l;
                    while ((queenMoveBlack[i][j - 1] == 0 || queenMoveBlack[i][j - 1] == n + 1) &&
                           currentPosition[i][j - 1] == 0) {
                        queenMoveBlack[i][j - 1] = n + 1;
                        j--;
                    }
                    i = k;
                    j = l;
                    while ((queenMoveBlack[i][j + 1] == 0 || queenMoveBlack[i][j + 1] == n + 1) &&
                           currentPosition[i][j + 1] == 0) {
                        queenMoveBlack[i][j + 1] = n + 1;
                        j++;
                    }
                    i = k;
                    j = l;
                    while ((queenMoveBlack[i + 1][j - 1] == 0 || queenMoveBlack[i + 1][j - 1] == n + 1) &&
                           currentPosition[i + 1][j - 1] == 0) {
                        queenMoveBlack[i + 1][j - 1] = n + 1;
                        i++;
                        j--;
                    }
                    i = k;
                    j = l;
                    while ((queenMoveBlack[i + 1][j] == 0 || queenMoveBlack[i + 1][j] == n + 1) &&
                           currentPosition[i + 1][j] == 0) {
                        queenMoveBlack[i + 1][j] = n + 1;
                        i++;
                    }
                    i = k;
                    j = l;
                    while ((queenMoveBlack[i + 1][j + 1] == 0 || queenMoveBlack[i + 1][j + 1] == n + 1) &&
                           currentPosition[i + 1][j + 1] == 0) {
                        queenMoveBlack[i + 1][j + 1] = n + 1;
                        i++;
                        j++;
                    }


                }
            }
        }
    }

}

void EvaluationFunction::MobilitySearch() {
    int i, j, k, l;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            mobility[i][j] = 0;
        }
    }

    for (i = 0; i < 12; i++) {
        for (j = 0; j < 12; j++) {
            if (currentPosition[i][j] == 0) {
                if (currentPosition[i - 1][j - 1] == 0) { mobility[i][j] = mobility[i][j] + 1; }
                if (currentPosition[i - 1][j] == 0) { mobility[i][j] = mobility[i][j] + 1; }
                if (currentPosition[i - 1][j + 1] == 0) { mobility[i][j] = mobility[i][j] + 1; }
                if (currentPosition[i][j - 1] == 0) { mobility[i][j] = mobility[i][j] + 1; }
                if (currentPosition[i][j + 1] == 0) { mobility[i][j] = mobility[i][j] + 1; }
                if (currentPosition[i + 1][j - 1] == 0) { mobility[i][j] = mobility[i][j] + 1; }
                if (currentPosition[i + 1][j] == 0) { mobility[i][j] = mobility[i][j] + 1; }
                if (currentPosition[i + 1][j + 1] == 0) { mobility[i][j] = mobility[i][j] + 1; }
            }
        }

    }
}

void EvaluationFunction::t1Count() {
    t1 = 0;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (currentPosition[i][j] == 0) {
                if (queenMoveWhite[i][j] == queenMoveBlack[i][j] != 0) { t1 = t1 + 0.1; }

                if (queenMoveWhite[i][j] < queenMoveBlack[i][j]) {
                    if (queenMoveWhite[i][j] == 0) { t1 = t1 - 1; }
                    if (queenMoveWhite[i][j] != 0) { t1 = t1 + 1; }

                }
                if (queenMoveWhite[i][j] > queenMoveBlack[i][j]) {
                    if (queenMoveBlack[i][j] == 0) { t1 = t1 + 1; }
                    if (queenMoveBlack[i][j] != 0) { t1 = t1 - 1; }
                }

            }


        }
    }


}

void EvaluationFunction::t2Count() {
    t2 = 0;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (currentPosition[i][j] == 0) {
                if (kingMoveWhite[i][j] == kingMoveBlack[i][j] != 0) { t2 = t2 + 0.1; }

                if (kingMoveWhite[i][j] < kingMoveBlack[i][j]) {
                    if (kingMoveWhite[i][j] == 0) { t2 = t2 - 1; }
                    if (kingMoveWhite[i][j] != 0) { t2 = t2 + 1; }

                }
                if (kingMoveWhite[i][j] > kingMoveBlack[i][j]) {
                    if (kingMoveBlack[i][j] == 0) { t2 = t2 + 1; }
                    if (kingMoveBlack[i][j] != 0) { t2 = t2 - 1; }
                }

            }


        }
    }
}

void EvaluationFunction::c1Count() {
    c1 = 0;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (currentPosition[i][j] == 0) {
                if (queenMoveWhite[i][j] != 0 && queenMoveBlack[i][j] != 0) {
                    c1 = c1 + pow(2, -(queenMoveWhite[i][j])) - pow(2, -(queenMoveBlack[i][j]));
                }
                if (queenMoveWhite[i][j] == 0 && queenMoveBlack[i][j] != 0) {
                    c1 = c1 - pow(2, -(queenMoveBlack[i][j]));
                }
                if (queenMoveWhite[i][j] != 0 && queenMoveBlack[i][j] == 0) {
                    c1 = c1 + pow(2, -(queenMoveWhite[i][j]));
                }

            }
        }
    }
    c1 = c1 * 2;

}

void EvaluationFunction::c2Count() {
    c2 = 0;
    double a;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (currentPosition[i][j] == 0) {
                if (kingMoveWhite[i][j] != 0 && kingMoveBlack[i][j] != 0) {
                    a = (kingMoveBlack[i][j] - kingMoveWhite[i][j]);
                    c2 = c2 + min(1, (double) max(-1, a / 6));
                }
                if (kingMoveWhite[i][j] == 0 && kingMoveBlack[i][j] != 0) {
                    c2 = c2 - 1;
                }
                if (kingMoveWhite[i][j] != 0 && kingMoveBlack[i][j] == 0) {
                    c2 = c2 + 1;
                }
            }
        }
    }


}

void EvaluationFunction::wCount() {
    w = 0;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (currentPosition[i][j] == 0) {
                if (queenMoveWhite[i][j] != 0 && queenMoveBlack[i][j] != 0) {
                    w = w + pow(2, -(fabs(queenMoveWhite[i][j] - queenMoveBlack[i][j])));
                }


            }
        }
    }

}

void EvaluationFunction::aCount() {
    int k, l, m;
    int n = 0;
    int h = 0;
    aWhite[0] = aWhite[1] = aWhite[2] = aWhite[3] = aBlack[0] = aBlack[1] = aBlack[2] = aBlack[3] = 0;


    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (currentPosition[i][j] == 2) {
                k = i;
                l = j;
                m = 1;
                while (currentPosition[k - 1][l - 1] == 0 && queenMoveBlack[k - 1][l - 1] != 0) {
                    aWhite[n] = aWhite[n] + mobility[k - 1][l - 1] / m;
                    k--;
                    l--;
                    m = m * 2;
                }

                k = i;
                l = j;
                m = 1;
                while (currentPosition[k - 1][l] == 0 && queenMoveBlack[k - 1][l] != 0) {
                    aWhite[n] = aWhite[n] + mobility[k - 1][l] / m;
                    k--;
                    m = m * 2;
                }

                k = i;
                l = j;
                m = 1;
                while (currentPosition[k - 1][l + 1] == 0 && queenMoveBlack[k - 1][l + 1] != 0) {
                    aWhite[n] = aWhite[n] + mobility[k - 1][l + 1] / m;
                    k--;
                    l++;
                    m = m * 2;
                }

                k = i;
                l = j;
                m = 1;
                while (currentPosition[k][l - 1] == 0 && queenMoveBlack[k][l - 1] != 0) {
                    aWhite[n] = aWhite[n] + mobility[k][l - 1] / m;
                    l--;
                    m = m * 2;
                }

                k = i;
                l = j;
                m = 1;
                while (currentPosition[k][l + 1] == 0 && queenMoveBlack[k][l + 1] != 0) {
                    aWhite[n] = aWhite[n] + mobility[k][l + 1] / m;
                    l++;
                    m = m * 2;
                }

                k = i;
                l = j;
                m = 1;
                while (currentPosition[k + 1][l - 1] == 0 && queenMoveBlack[k + 1][l - 1] != 0) {
                    aWhite[n] = aWhite[n] + mobility[k + 1][l - 1] / m;
                    k++;
                    l--;
                    m = m * 2;
                }

                k = i;
                l = j;
                m = 1;
                while (currentPosition[k + 1][l] == 0 && queenMoveBlack[k + 1][l] != 0) {
                    aWhite[n] = aWhite[n] + mobility[k + 1][l] / m;
                    k++;
                    m = m * 2;
                }

                k = i;
                l = j;
                m = 1;
                while (currentPosition[k + 1][l + 1] == 0 && queenMoveBlack[k + 1][l + 1] != 0) {
                    aWhite[n] = aWhite[n] + mobility[k + 1][l + 1] / m;
                    k++;
                    l++;
                    m = m * 2;
                }
                n++;
            }

            if (currentPosition[i][j] == 3) {
                k = i;
                l = j;
                m = 1;
                while (currentPosition[k - 1][l - 1] == 0 && queenMoveWhite[k - 1][l - 1] != 0) {
                    aBlack[h] = aBlack[h] + mobility[k - 1][l - 1] / m;
                    k--;
                    l--;
                    m = m * 2;
                }

                k = i;
                l = j;
                m = 1;
                while (currentPosition[k - 1][l] == 0 && queenMoveWhite[k - 1][l] != 0) {
                    aBlack[h] = aBlack[h] + mobility[k - 1][l] / m;
                    k--;
                    m = m * 2;
                }

                k = i;
                l = j;
                m = 1;
                while (currentPosition[k - 1][l + 1] == 0 && queenMoveWhite[k - 1][l + 1] != 0) {
                    aBlack[h] = aBlack[h] + mobility[k - 1][l + 1] / m;
                    k--;
                    l++;
                    m = m * 2;
                }

                k = i;
                l = j;
                m = 1;
                while (currentPosition[k][l - 1] == 0 && queenMoveWhite[k][l - 1] != 0) {
                    aBlack[h] = aBlack[h] + mobility[k][l - 1] / m;
                    l--;
                    m = m * 2;
                }

                k = i;
                l = j;
                m = 1;
                while (currentPosition[k][l + 1] == 0 && queenMoveWhite[k][l + 1] != 0) {
                    aBlack[h] = aBlack[h] + mobility[k][l + 1] / m;
                    l++;
                    m = m * 2;
                }

                k = i;
                l = j;
                m = 1;
                while (currentPosition[k + 1][l - 1] == 0 && queenMoveWhite[k + 1][l - 1] != 0) {
                    aBlack[h] = aBlack[h] + mobility[k + 1][l - 1] / m;
                    k++;
                    l--;
                    m = m * 2;
                }

                k = i;
                l = j;
                m = 1;
                while (currentPosition[k + 1][l] == 0 && queenMoveWhite[k + 1][l] != 0) {
                    aBlack[h] = aBlack[h] + mobility[k + 1][l] / m;
                    k++;
                    m = m * 2;
                }

                k = i;
                l = j;
                m = 1;
                while (currentPosition[k + 1][l + 1] == 0 && queenMoveWhite[k + 1][l + 1] != 0) {
                    aBlack[h] = aBlack[h] + mobility[k + 1][l + 1] / m;
                    k++;
                    l++;
                    m = m * 2;
                }
                h++;
            }


        }
    }

}

int ec = 0;

double EvaluationFunction::Evaluation(BYTE position[][12], int side) {
    ec++;
    double value;

    copy(position);
    nSide = side;
    KingMoveSearch();
    QueenMoveSearch();
    t1Count();
    t2Count();
    c1Count();
    c2Count();
    wCount();
    double a = (5 / (w + 5));
    double b = (w / (w + 20));
    double c = (1 - (a + b)) / 2;

    value = a * t1 + b * (t2 / 2) + c * ((c1 + c2) / 2);


    if (side == 0)
        return value;
    else
        return -value;


}

