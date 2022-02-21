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
using namespace std;



float Width = GetSystemMetrics(SM_CXSCREEN);
float Height = GetSystemMetrics(SM_CYSCREEN);
float uWidth = Width / 1920;
float uHeight = Height / 1080;

//按钮
struct button
{
	int x;
	int y;
	int width;
	int height;
	COLORREF color;
	char* pText;
};

//初始化按钮
struct button* createButton(int x, int y, int width, int height, COLORREF color, const char* pText) 
{
	struct button* pB = (struct button*)malloc(sizeof(struct button));
	pB->x = x;
	pB->y = y;
	pB->width = width;
	pB->height = height;
	pB->color = color;
	pB->pText = (char*)malloc(strlen(pText) + 1);
	strcpy(pB->pText, pText);
	return pB;
}
//按钮设置
struct button* load = createButton(10 * uWidth, 10 * uHeight, 200 * uWidth, 50 * uHeight, 0xDEC4B0, "加载csv");
struct button* choose = createButton(10 * uWidth, 70 * uHeight, 200 * uWidth, 50 * uHeight, 0xDEC4B0, "存储路径");
struct button* save = createButton(10 * uWidth, 130 * uHeight, 200 * uWidth, 50 * uHeight, 0xDEC4B0, "保存文件");
struct button* exportFile = createButton(10 * uWidth, 190 * uHeight, 200 * uWidth, 50 * uHeight, 0xDEC4B0, "导出文件");
struct button* musicOn = createButton(10 * uWidth, 300 * uHeight, 200 * uWidth, 50 * uHeight, 0x3366ff, "振作起来");
struct button* start = createButton(10 * uWidth, 380 * uHeight, 200 * uWidth, 50 * uHeight, 0xFFFFE1, "开始记忆");
struct button* review = createButton(10 * uWidth, 440 * uHeight, 200 * uWidth, 50 * uHeight, 0xFFFFE1, "复习本轮");
struct button* remember = createButton(10 * uWidth, 560 * uHeight, 200 * uWidth, 50 * uHeight, 0x32CD32, "记    得");
struct button* forget = createButton(10 * uWidth, 620 * uHeight, 200 * uWidth, 50 * uHeight, 0x3C14DC, "遗    忘");
//画按钮
void drawButton(struct button* pB)
{
	setfillcolor(pB->color);
	settextstyle(35*uWidth, 0*uHeight, "黑体");
	setlinecolor(BLACK);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	fillrectangle(pB->x, pB->y, pB->x + pB->width, pB->y + pB->height);
	outtextxy(pB->x + 30*uWidth, pB->y + 10*uHeight,pB->pText);
}
//判断鼠标是否在按钮中
bool mouseInButton(struct button* pB, MOUSEMSG m) 
{
	if (pB->x < m.x && m.x <= pB->x + pB->width && pB->y < m.y && m.y <= pB->y + pB->height)
	{
		if (pB == load)
			load->color = 0xB69C88;
		else if (pB == choose)
			choose->color = 0xB69C88;
		else if (pB == save)
			save->color = 0xB69C88;
		else if (pB == exportFile)
			exportFile->color = 0xB69C88;
		else if (pB == musicOn)
			musicOn->color = 0x003399;
		else if (pB == start)
			start->color = 0xD7D7B9;
		else if (pB == review)
			review->color = 0xD7D7B9;
		else if (pB == remember)
			remember->color = 0x0AA50A;
		else if (pB == forget)
			forget->color = 0x0A00B4;
		
		return true;
	}
	if (pB == load)
		load->color = 0xDEC4B0;
	else if (pB == choose)
		choose->color = 0xDEC4B0;
	else if (pB == save)
		save->color = 0xDEC4B0;
	else if (pB == exportFile)
		exportFile->color = 0xDEC4B0;
	else if (pB == musicOn)
		musicOn->color = 0x3366ff;
	else if (pB == start)
		start->color = 0xFFFFE1;
	else if (pB == review)
		review->color = 0xFFFFE1;
	else if (pB == remember)
		remember->color = 0x32CD32;
	else if (pB == forget)
		forget->color = 0x3C14DC;
	return false;
}
//判断鼠标点击按钮
bool clickButton(struct button* pB, MOUSEMSG m)
{
	if (mouseInButton(pB, m) && m.uMsg == WM_LBUTTONDOWN)
	{
		return true;
	}
	return false;

}

//结构体数组存储数据
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

	bool operator == (const int &x)
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

//自定义compare
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

//加载csv文件
//void loadCsv_TCHAR(TCHAR szBuffer[], vector<Word> words);
//void loadCsv_CHAR(char szBuffer[], vector<Word> words);
int main() {

	
	initgraph(1280*uWidth, 720*uHeight);
	setfillcolor(0xE16941);
	fillrectangle(0, 0, 1280 * uWidth, 720 * uHeight);
	bool bool_start = false;
	bool bool_end = false;
	bool bool_review = false;
	bool lerp = false;
	int amount = 0;
	int npos = 0;
	int correct = 0;
	int max_review = 0;
	float rate = 0;
	int rate_i = 0;
	string rate_s;
	string ForgetTime;
	string ReviewTime;
	string path;
	string musicPath;
	LPCSTR str[6];
	vector<Word> words;
	vector<Word>::iterator iter;
	fstream prep;
	prep.open("data.dat");
	prep >> path;
	prep.close();

	//读取文件
	ifstream myFile;
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
			words[i].Chinese.erase(std::remove(words[i].Chinese.begin(), words[i].Chinese.end(), '\"'), words[i].Chinese.end());
		}
		line = "";
	}
	myFile.close();
	for (auto Words : words) {
		Words.display();
	}
	cout << words.size() << endl;
	while (1) 
	{
		BeginBatchDraw();
		setfillcolor(0xE16941);
		fillrectangle(0, 0, 1280 * uWidth, 720 * uHeight);
		drawButton(load);
		drawButton(choose);
		drawButton(save);
		drawButton(exportFile);
		drawButton(start);
		drawButton(review);
		drawButton(remember);
		drawButton(forget);
		drawButton(musicOn);
		
		//开始记忆
		if (bool_start == true) {
			//设置单词
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(140 * uHeight, 70 * uWidth, "黑体");
			str[0] = words[npos].TheWord.c_str();
			outtextxy(250 * uWidth, 50 * uHeight, str[0]);
			//设置词性
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(50 * uHeight, 30 * uWidth, "黑体");
			str[1] = words[npos].WordClass.c_str();
			outtextxy(250 * uWidth, 230 * uHeight, str[1]);
			
			//设置中文
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(100 * uHeight, 50 * uWidth, "黑体");
			str[2] = words[npos].Chinese.c_str();
			outtextxy(250 * uWidth, 350 * uHeight, str[2]);

			//设置遗忘次数
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(30 * uHeight, 15 * uWidth, "黑体");
			outtextxy(370 * uWidth, 605 * uHeight, "遗忘次数:");
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(40 * uHeight, 30 * uWidth, "黑体");
			cout << ForgetTime << endl;
			ForgetTime = to_string(words[npos].ForgetTime);
			str[3] = ForgetTime.c_str();
			outtextxy(520 * uWidth, 600 * uHeight, str[3]);

			//设置记忆次数
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(30 * uHeight, 15 * uWidth, "黑体");
			outtextxy(600 * uWidth, 605 * uHeight, "记忆次数:");
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(40 * uHeight, 30 * uWidth, "黑体");
			ReviewTime = to_string(words[npos].ReviewTime);
			str[4] = ReviewTime.c_str();
			outtextxy(750 * uWidth, 600 * uHeight, str[4]);

			//设置遗忘率
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(30 * uHeight, 15 * uWidth, "黑体");
			outtextxy(870 * uWidth, 605 * uHeight, "遗忘率:");
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(40 * uHeight, 30 * uWidth, "黑体");
			if (words[npos].ReviewTime == 0)
				correct = 1;
			else
				correct = words[npos].ReviewTime;
			rate = (float)words[npos].ForgetTime / (float)correct;
			rate_i = rate * 100;
			rate_s = to_string(rate_i);
			str[5] = rate_s.c_str();
			outtextxy(1000 * uWidth, 600 * uHeight, str[5]);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(30 * uHeight, 15 * uWidth, "黑体");
			outtextxy(1100 * uWidth, 605 * uHeight, "%");
		}

		//本轮记忆完成
		if (bool_end == true) {
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(175 * uHeight, 85 * uWidth, "黑体");
			str[0] = words[npos].TheWord.c_str();
			outtextxy(250 * uWidth, 250 * uHeight, "本轮学习完成");
		}
		//获取光标
		MOUSEMSG m = GetMouseMsg();

		//1加载文件
		if (clickButton(load, m))
		{
			//启动文件选择对话框
			TCHAR szBuffer[MAX_PATH] = { 0 };
			OPENFILENAME ofn = { 0 };
			ofn.lStructSize = sizeof(ofn);
			ofn.lpstrFilter = _T("Csv文件(*.csv)\0*.csv\0所有文件(*.*)\0*.*\0");//要选择的文件后缀   
			ofn.lpstrInitialDir = _T("D:\\Program Files");//默认的文件路径   
			ofn.lpstrFile = szBuffer;//存放文件的缓冲区   
			ofn.nMaxFile = sizeof(szBuffer) / sizeof(*szBuffer);
			ofn.nFilterIndex = 0;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;//标志如果是多选要加上OFN_ALLOWMULTISELECT  
			BOOL bSel = GetOpenFileName(&ofn);
			//outtextxy(250, 40, szBuffer);

			words.clear();
			//读取文件
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
					words[i].Chinese.erase(std::remove(words[i].Chinese.begin(), words[i].Chinese.end(), '\"'), words[i].Chinese.end());
				}
				line = "";
			}
			myFile.close();
			//for (auto Words : words) {
				//Words.display();
			//}

		}

		//2设置存储路径
		if (clickButton(choose, m))
		{
			TCHAR szBuffer[MAX_PATH] = { 0 };
			BROWSEINFO bi;
			ZeroMemory(&bi, sizeof(BROWSEINFO));
			bi.hwndOwner = NULL;
			bi.pszDisplayName = szBuffer;
			bi.lpszTitle = _T("从下面选文件夹目录:");
			bi.ulFlags = BIF_RETURNFSANCESTORS;
			LPITEMIDLIST idl = SHBrowseForFolder(&bi);
			if (NULL == idl)
			{
				return 0 ;
			}
			SHGetPathFromIDList(idl, szBuffer);
			path = szBuffer;
			ofstream data;
			path = path + "\\list.csv";
			data.open("data.dat");
			data << path << endl;
			data.close();
		}

		//3保存文件
		if (clickButton(save, m))
		{
			sort(words.begin(), words.end(), compRate);
			ofstream list;
			list.open(path);
			list << "单词" << "," << "词性" << "," << "释义" << "," << "遗忘次数" << "," << "记忆次数" << endl;
			for (int i = 0; i < words.size(); i++) {
				list << words.at(i).TheWord <<"," << words.at(i).WordClass << "," << words.at(i).Chinese << "," << words.at(i).ForgetTime << "," << words.at(i).ReviewTime << endl;
			}
			list.close();
		}

		//4导出文件
		if (clickButton(exportFile, m))
		{
			TCHAR szBuffer[MAX_PATH] = { 0 };
			BROWSEINFO bi;
			ZeroMemory(&bi, sizeof(BROWSEINFO));
			bi.hwndOwner = NULL;
			bi.pszDisplayName = szBuffer;
			bi.lpszTitle = _T("从下面选文件夹目录:");
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
			list << "单词" << "," << "词性" << "," << "释义" << "," << "遗忘次数" << "," << "记忆次数" << endl;
			for (int i = 0; i < words.size(); i++) {
				list << words.at(i).TheWord << "," << words.at(i).WordClass << "," << words.at(i).Chinese << "," << words.at(i).ForgetTime << "," << words.at(i).ReviewTime << endl;
			}
			list.close();
		}

		//5开始记忆
		if (clickButton(start, m))
		{
			if (npos < (int)(words.size() - 1)) {
				sort(words.begin(), words.end(), compReview);
				iter = find(words.begin(), words.end(), 0);
				npos = iter - words.begin();
				char s[10];
				InputBox(s, 10, "请输入记忆单词数量：");

				amount = atoi(s)-1;
				bool_start = true;
				bool_end = false;
			}
		}

		//6复习本轮
		if (clickButton(review, m))
		{
			npos = 0;
			if (npos < (int)(words.size()-1)){
				sort(words.begin(), words.end(), compRate);
				iter = find(words.begin(), words.end(), 0);
				amount = iter - words.begin() - 1;
				bool_start = true;
				bool_end = false;
			}
		}

		//7记得
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

		//8遗忘
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

		//9音乐
		if (clickButton(musicOn, m)) {
			lerp = !lerp;
			musicPath = "braveman.wav";
			if (lerp == true)
				PlaySound(_T(musicPath.c_str()), NULL, SND_FILENAME | SND_ASYNC);
			else
				PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
			
		}
		EndBatchDraw();
	}
	return 0;
}

//void loadCsv_TCHAR(TCHAR szBuffer[],vector<Word> words) {
//}
//void loadCsv_CHAR(char* szBuffer, vector<Word> words) {
//}