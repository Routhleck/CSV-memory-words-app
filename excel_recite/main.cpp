#include<iostream>
#include<graphics.h>
#include <Windows.h>
#include<stdio.h>
#include<string>
#include"Shlobj.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <algorithm>
#include <iterator>
#include <Mmsystem.h>
#pragma comment(lib,"WinMM.Lib")
#include "ui.h"
#include <direct.h>
using namespace std;

//�ṹ������洢����
struct Word {
public:
	Word(
		string theword,
		string wordClass,
		string chinese,
		int forgetTime,
		int reviewTime
	) {
		TheWord = theword;
		WordClass = wordClass;
		Chinese = chinese;
		ForgetTime = forgetTime;
		ReviewTime = reviewTime;
	}

	bool operator == (const int& x)
	{
		return (this->ReviewTime == x);
	}

	void display() {
		cout << "Word:" << TheWord << endl;
		cout << "Class:" << WordClass << endl;
		cout << "Chinese:" << Chinese << endl;
		cout << "ForgetTime:" << ForgetTime << endl;
		cout << "ReviewTime:" << ReviewTime << endl;
	}

	string TheWord;
	string WordClass;
	string Chinese;
	int ForgetTime;
	int ReviewTime;
};

//�Զ���compare
bool compRate(const Word& a, const Word& b) {
	int aReviewTime;
	int bReviewTime;
	if (a.ReviewTime == 0)
		aReviewTime = 1;
	else
		aReviewTime = a.ReviewTime;
	if (b.ReviewTime == 0)
		bReviewTime = 1;
	else
		bReviewTime = a.ReviewTime;

	return ((float)a.ForgetTime / (float)aReviewTime) > ((float)b.ForgetTime / (float)bReviewTime);
}
bool compReview(const Word& a, const Word& b) {
	return a.ReviewTime > b.ReviewTime;
}

int main() {

	
	initgraph(1280*uWidth, 720*uHeight,SHOWCONSOLE);
	initgraph(1280 * uWidth, 720 * uHeight);
	setfillcolor(0xE16941);
	fillrectangle(0, 0, 1280 * uWidth, 720 * uHeight);
	bool bool_start = false;
	bool bool_end = false;
	bool bool_review = false;
	bool lerp = false;
	bool bool_chinese = false;
	int amount = 0;
	int npos = 0;
	int correct = 0;
	int max_review = 0;
	float rate = 0;
	int rate_i = 0;
	int wordAmount = 0;
	int wordMemory = 0;
	int wordNeedMemory = 0;
	int wordRest = 0;
	int wordMaster = 0;
	int temp = 0;
	string rate_s;
	string ForgetTime;
	string ReviewTime;
	string path;
	string musicPath;
	LPCSTR str[6];
	vector<Word> words;
	vector<Word>::iterator iter;

	
	//�Զ���ȡ�ļ�
	ifstream myFile;
	char buffer[MAX_PATH];
	getcwd(buffer, MAX_PATH);
	path = buffer;
	path = path + "\\save.csv";
	myFile.open(path);

	string line = "";
	getline(myFile, line);
	line = "";
	while (getline(myFile, line)) {

		string word;
		string wordClass;
		string chinese;
		int forgetTime;
		string tempString1, tempString2;
		int reviewTime;

		stringstream inputString(line);

		getline(inputString, word, ',');
		getline(inputString, wordClass, ',');
		getline(inputString, chinese, ',');
		getline(inputString, tempString1, ',');
		getline(inputString, tempString2, ',');

		forgetTime = atoi(tempString1.c_str());
		reviewTime = atoi(tempString2.c_str());

		if (reviewTime == 0) {
			reviewTime = forgetTime;
		}

		Word Words(word, wordClass, chinese, forgetTime, reviewTime);
		words.push_back(Words);

		for (int i = 0; i < words.size(); i++) {
			words[i].TheWord.erase(std::remove(words[i].TheWord.begin(), words[i].TheWord.end(), '\"'), words[i].TheWord.end());
		}

		for (int i = 0; i < words.size(); i++) {
			words[i].WordClass.erase(std::remove(words[i].WordClass.begin(), words[i].WordClass.end(), '\"'), words[i].WordClass.end());
		}

		for (int i = 0; i < words.size(); i++) {
			words[i].Chinese.erase(std::remove(words[i].Chinese.begin(), words[i].Chinese.end(), '\"'), words[i].Chinese.end());
		}
		line = "";
	}
	myFile.close();

	while (1) 
	{
		BeginBatchDraw();
		setfillcolor(0xE16941);
		fillrectangle(0, 0, 1280 * uWidth, 720 * uHeight);
		drawAllButton();
		
		//��������ͳ��
		//��������
		//���ʼ�������
		//����δ��������
		//��ǰһ��ѧϰ��ʣ��
		//�����ʵ���25%�ĵ�������
		sort(words.begin(), words.end(), compReview);
		iter = find(words.begin(), words.end(), 0);
		wordAmount = words.size();
		wordMemory = iter - words.begin();
		wordNeedMemory = wordAmount - wordMemory;
		wordRest = amount;
		sort(words.begin(), words.end(), compRate);
		
		iter = words.begin();
		if (iter->ReviewTime == 0)
			temp = 1;
		else
			temp = iter->ReviewTime;
		while (((float)iter->ForgetTime / (float)temp) >= 0.25) {
			iter++;
			if (iter->ReviewTime == 0) 
				temp = 1;
			else
				temp = iter->ReviewTime;
			
		}
		wordMaster = iter - words.begin();
		drawStatus(wordAmount, wordMemory, wordNeedMemory, wordRest, wordMaster);





		//��ʼ����
		if (bool_start == true) {
			char* value0=(char*)words[npos].TheWord.c_str();
			char* value1 = (char*)words[npos].WordClass.c_str();
			char* value2 = (char*)words[npos].Chinese.c_str();
			int value3 = words[npos].ForgetTime;
			int value4 = words[npos].ReviewTime;
			drawMain(bool_chinese,(char*)value0, (char*)value1, (char*)value2,value3, value4);
		}
		

		//���ּ������
		if (bool_end == true) {
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(175 * uHeight, 85 * uWidth, "����");
			outtextxy(250 * uWidth, 250 * uHeight, "����ѧϰ���");
		}
		//��ȡ���
		MOUSEMSG m = GetMouseMsg();

		//1�����ļ�
		if (clickButton(load, m))
		{
			//�����ļ�ѡ��Ի���
			TCHAR szBuffer[MAX_PATH] = { 0 };
			OPENFILENAME ofn = { 0 };
			ofn.lStructSize = sizeof(ofn);
			ofn.lpstrFilter = _T("Csv�ļ�(*.csv)\0*.csv\0�����ļ�(*.*)\0*.*\0");//Ҫѡ����ļ���׺   
			ofn.lpstrInitialDir = _T("D:\\Program Files");//Ĭ�ϵ��ļ�·��   
			ofn.lpstrFile = szBuffer;//����ļ��Ļ�����   
			ofn.nMaxFile = sizeof(szBuffer) / sizeof(*szBuffer);
			ofn.nFilterIndex = 0;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;//��־����Ƕ�ѡҪ����OFN_ALLOWMULTISELECT  
			BOOL bSel = GetOpenFileName(&ofn);
			//outtextxy(250, 40, szBuffer);

			words.clear();
			//��ȡ�ļ�
			ifstream myFile;
			myFile.open(szBuffer);

			string line = "";
			getline(myFile, line);
			line = "";
			while (getline(myFile, line)) {

				string word;
				string wordClass;
				string chinese;
				int forgetTime;
				string tempString1, tempString2;
				int reviewTime;

				stringstream inputString(line);

				getline(inputString, word, ',');
				getline(inputString, wordClass, ',');
				getline(inputString, chinese, ',');
				getline(inputString, tempString1, ',');
				getline(inputString, tempString2, ',');

				forgetTime = atoi(tempString1.c_str());
				reviewTime = atoi(tempString2.c_str());

				if (reviewTime == 0) {
					reviewTime = forgetTime;
				}

				Word Words(word, wordClass, chinese, forgetTime, reviewTime);
				words.push_back(Words);

				for (int i = 0; i < words.size(); i++) {
					words[i].TheWord.erase(std::remove(words[i].TheWord.begin(), words[i].TheWord.end(), '\"'), words[i].TheWord.end());
				}

				for (int i = 0; i < words.size(); i++) {
					words[i].WordClass.erase(std::remove(words[i].WordClass.begin(), words[i].WordClass.end(), '\"'), words[i].WordClass.end());
				}

				for (int i = 0; i < words.size(); i++) {
					words[i].Chinese.erase(std::remove(words[i].Chinese.begin(), words[i].Chinese.end(), '\"'), words[i].Chinese.end());
				}
				line = "";
			}
			myFile.close();
			//for (auto Words : words) {
				//Words.display();
			//}
		}


		//3�����ļ�
		if (clickButton(save, m))
		{
			sort(words.begin(), words.end(), compRate);
			ofstream list;
			list.open(path);
			list << "����" << "," << "����" << "," << "����" << "," << "��������" << "," << "�������" << endl;
			for (int i = 0; i < words.size(); i++) {
				list << words.at(i).TheWord << "," << words.at(i).WordClass << "," << words.at(i).Chinese << "," << words.at(i).ForgetTime << "," << words.at(i).ReviewTime << endl;
			}
			list.close();
		}

		//4�����ļ�
		if (clickButton(exportFile, m))
		{
			TCHAR szBuffer[MAX_PATH] = { 0 };
			BROWSEINFO bi;
			ZeroMemory(&bi, sizeof(BROWSEINFO));
			bi.hwndOwner = NULL;
			bi.pszDisplayName = szBuffer;
			bi.lpszTitle = _T("������ѡ�ļ���Ŀ¼:");
			bi.ulFlags = BIF_RETURNFSANCESTORS;
			LPITEMIDLIST idl = SHBrowseForFolder(&bi);
			if (NULL == idl)
			{
				return 0;
			}
			SHGetPathFromIDList(idl, szBuffer);

			path = szBuffer;
			path = path + "\\save.csv";
			ofstream list;
			list.open(path);
			list << "����" << "," << "����" << "," << "����" << "," << "��������" << "," << "�������" << endl;
			for (int i = 0; i < words.size(); i++) {
				list << words.at(i).TheWord << "," << words.at(i).WordClass << "," << words.at(i).Chinese << "," << words.at(i).ForgetTime << "," << words.at(i).ReviewTime << endl;
			}
			list.close();
		}

		//5��ʼ����
		if (clickButton(start, m))
		{
			if (npos < (int)(words.size() - 1)) {
				sort(words.begin(), words.end(), compReview);
				iter = find(words.begin(), words.end(), 0);
				npos = iter - words.begin();
				char s[10];
				InputBox(s, 10, "��������䵥��������");

				amount = atoi(s) - 1;
				bool_start = true;
				bool_end = false;
				bool_chinese = true;
			}
		}

		//6��ϰ����
		if (clickButton(review, m))
		{
			npos = 0;
			if (npos < (int)(words.size() - 1)) {
				sort(words.begin(), words.end(), compRate);
				iter = find(words.begin(), words.end(), 0);
				amount = iter - words.begin() - 1;
				bool_start = true;
				bool_end = false;
				bool_chinese = false;
			}
		}

		//7�ǵ�
		if (clickButton(remember, m))
		{
			words[npos].ReviewTime++;
			if (npos < (int)(words.size() - 1)) {
				npos++;
				amount--;
			}
			else
				amount = -1;
			if (amount < 0)
			{
				bool_start = false;
				bool_end = true;
			}
		}

		//8����
		if (clickButton(forget, m))
		{
			words[npos].ForgetTime++;
			words[npos].ReviewTime++;
			if (npos < (int)(words.size() - 1)) {
				npos++;
				amount--;
			}
			else
				amount = -1;
			if (amount < 0)
			{
				bool_start = false;
				bool_end = true;
			}
		}

		//9����
		if (clickButton(musicOn, m)) {
			lerp = !lerp;
			musicPath = "braveman.wav";
			if (lerp == true)
				PlaySound(_T(musicPath.c_str()), NULL, SND_FILENAME | SND_ASYNC);
			else
				PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
			
		}

		//�������忪��
		if (clickButton(chineseSwitch, m)) {
			bool_chinese = !bool_chinese;
		}
		EndBatchDraw();
	}
	return 0;
}

