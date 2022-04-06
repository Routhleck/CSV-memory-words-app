#pragma once
#ifndef   LOGIC
#define   LOGIC
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <direct.h>
#include <string>
#include <sstream>
#include <Windows.h>
#include <algorithm>
#include <graphics.h>
#include <ShlObj.h>

using namespace std;

//结构体数组存储数据
struct Word {
public:
	Word(
		string theword,
		string wordClass,
		string chinese,
		int forgetTime,
		int reviewTime,
		vector<int> history
	) {
		TheWord = theword;
		WordClass = wordClass;
		Chinese = chinese;
		ForgetTime = forgetTime;
		ReviewTime = reviewTime;
		History = history;
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
	vector<int> History;
};

//自定义compare
bool compRate(const Word& a, const Word& b) {
	int aReviewTime = 0;
	int bReviewTime = 0;
	if (a.ReviewTime == 0)
		aReviewTime = 1;
	else
		aReviewTime = a.ReviewTime;
	if (b.ReviewTime == 0)
		bReviewTime = 1;
	else
		bReviewTime = b.ReviewTime;

	if ((float)((float)a.ForgetTime / ((float)aReviewTime)) == (float)(((float)b.ForgetTime) / ((float)bReviewTime))) {
		return (aReviewTime > bReviewTime);
	}
	else return ((float)((float)a.ForgetTime / ((float)aReviewTime)) > (float)(((float)b.ForgetTime) / ((float)bReviewTime)));
}
bool compReview(const Word& a, const Word& b) {
	return a.ReviewTime > b.ReviewTime;
}
class logic {
public:
	static void autoLoad(string& path, vector<Word>& words, vector<int>& history);
	static void calculateStatus(int& amount, vector<Word>& tempWords, vector<Word>& words, vector<Word>::iterator& iter, int& wordAmount, int& wordMemory, int& wordNeedMemory, int& wordRest, int& wordMaster);
	static void manualLoad(string& path, vector<Word>& words, vector<int>& history);
	static void saveFile(vector<Word>& words, string& path);
	static void exportCsv(vector<Word>& words, string& path);
	static void startMemory(int& npos, vector<Word>& words, vector<Word>::iterator& iter, int& amount, bool& bool_start, bool& bool_end, bool& bool_chinese, int& startPos);
	static void reviewMemory(int& npos, vector<Word>& words, vector<Word>::iterator& iter, int& amount, bool& bool_start, bool& bool_end, bool& bool_chinese, int& startPos);
	static void rememberWord(int& npos, vector<Word>& words, bool& bool_stop, bool& bool_optimize, bool& bool_start, bool& bool_end, int& amount,int& lastPos);
	static void forgetWord(int& npos, vector<Word>& words, bool& bool_stop, bool& bool_optimize, bool& bool_start, bool& bool_end, int& amount,int& lastPos);
	static void playMusic(bool& lerp, string& musicPath);
	static void undo(bool& bool_start, bool& bool_end, vector<Word>& words, int& npos,int& amount);
	static void reviewOptimize(int& npos, vector<Word>& words, vector<Word>::iterator& iter, int& amount, int& wordMaster, bool& bool_start, bool& bool_end, bool& bool_chinese, bool& bool_optimize); 
	static void clearHistory();
	static void saveHistory(int choice);
	static void readHistory(int& npos, vector<Word>& words, vector<Word>::iterator& iter, int& amount, bool& bool_start, bool& bool_end, bool& bool_chinese, int& startPos, int& wordMaster, bool& bool_optimize, int& lastPos, bool& bool_stop);
};
#endif