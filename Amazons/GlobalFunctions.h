#pragma once

CString GblGetDirectoryOfExecutableFile();
CString GblGetFileNameFromPathName(CString strPathName);
CString GblGetFileNameWithExFromPathName(CString strPathName);
long GblGetIPLong(LPCTSTR szIP);//���ص�long����addr�ĸ�ʽ
CString GblGetIPString(long ip);//����"127.0.0.1"�����ĸ�ʽ
int GetIntegerFromBuffer(LPCTSTR buffer, int *pStart);
int GetIntegerFromBuffer(LPCTSTR buffer, int default);//���û���ҵ����֣�����defaultֵ
void GetStringFromBuffer(CString& strDes,LPCTSTR buffer, int& iStart);//��iPtrָ����λ�ÿ�ʼ��ȡһ��"\r\n"��β���ַ���
void GetStringFromBuffer(LPTSTR bufferDes,LPCTSTR buffer, int& iStart);
int GblRevertByBit(int n);//��תһ��int������10011����תΪ11001
int GblRevertByint(int n);//��תһ��int������0xABCD����תΪ0xCDAB
