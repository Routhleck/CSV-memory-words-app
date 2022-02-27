#include"logic.h"

using namespace std;

void logic::autoLoad(string& path, vector<Word>& words, vector<int>& history) {
	//自动读取文件
	ifstream myFile;
	char buffer[MAX_PATH];
	_getcwd(buffer, MAX_PATH);
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

		Word Words(word, wordClass, chinese, forgetTime, reviewTime, history);
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
}

void logic::calculateStatus(int& amount, vector<Word>& tempWords, vector<Word>& words, vector<Word>::iterator& iter, int& wordAmount, int& wordMemory, int& wordNeedMemory, int& wordRest, int& wordMaster)
{
	//单词总数
	//单词记忆数量
	//单词未记忆数量
	//当前一轮学习量剩余
	//(记忆次数-遗忘次数)/(记忆次数+1)大于55%的单词数量
	if (amount < 0)
		amount = 0;
	tempWords = words;
	sort(tempWords.begin(), tempWords.end(), compReview);
	iter = find(tempWords.begin(), tempWords.end(), 0);
	wordAmount = tempWords.size();
	wordMemory = iter - tempWords.begin();
	wordNeedMemory = wordAmount - wordMemory;
	wordRest = amount;
	wordMaster = 0;
	sort(tempWords.begin(), tempWords.end(), compRate);

	iter = tempWords.begin();

	if (iter._Ptr != nullptr) {
		while (iter->ReviewTime != 0) {
			if (((float)(iter->ReviewTime - iter->ForgetTime) / (float)(iter->ReviewTime + 1)) > 0.55) {
				wordMaster++;
			}
			iter++;
		}
	}
}

void logic::manualLoad(string& path, vector<Word>& words, vector<int>& history)
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

		Word Words(word, wordClass, chinese, forgetTime, reviewTime, history);
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
}

void logic::saveFile(vector<Word>& words, string& path)
{
	sort(words.begin(), words.end(), compRate);
	ofstream list;
	list.open(path);
	list << "单词" << "," << "词性" << "," << "释义" << "," << "遗忘次数" << "," << "记忆次数" << endl;
	for (int i = 0; i < words.size(); i++) {
		list << words.at(i).TheWord << "," << words.at(i).WordClass << "," << words.at(i).Chinese << "," << words.at(i).ForgetTime << "," << words.at(i).ReviewTime << endl;
	}
	list.close();
}

void logic::exportCsv(vector<Word>& words, string& path)
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
		return;
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

void logic::startMemory(int& npos, vector<Word>& words, vector<Word>::iterator& iter, int& amount, bool& bool_start, bool& bool_end, bool& bool_chinese, int& startPos)
{
	if (npos < (int)(words.size() - 1)) {
		sort(words.begin(), words.end(), compReview);
		iter = find(words.begin(), words.end(), 0);
		npos = iter - words.begin();
		char s[10];
		InputBox(s, 10, "请输入记忆单词数量：");

		startPos = npos;
		amount = atoi(s) - 1;
		bool_start = true;
		bool_end = false;
		bool_chinese = true;
	}
}

void logic::reviewMemory(int& npos, vector<Word>& words, vector<Word>::iterator& iter, int& amount, bool& bool_start, bool& bool_end, bool& bool_chinese, int& startPos)
{
	npos = 0;
	startPos = 0;
	if (npos < (int)(words.size() - 1)) {
		sort(words.begin(), words.end(), compRate);
		iter = find(words.begin(), words.end(), 0);
		amount = iter - words.begin() - 1;
		bool_start = true;
		bool_end = false;
		bool_chinese = false;
	}
}

void logic::rememberWord(int& npos, vector<Word>& words, bool& bool_stop, bool& bool_optimize, bool& bool_start, bool& bool_end, int& amount,int & lastPos)
{
	if (bool_start == true && bool_end == false) {
		lastPos = npos;
		words[npos].ReviewTime++;
		words[npos].History.push_back(0);
		bool_stop = false;
		if (npos < (int)(words.size() - 1)) {
			if (bool_optimize)
			{
				npos++;
				while (words[npos].ReviewTime != 0 && bool_stop == false) {
					if (((float)(words[npos].ReviewTime - words[npos].ForgetTime) / (float)(words[npos].ReviewTime + 1)) > 0.55) {
						npos++;
					}
					else {
						bool_stop = true;
					}
				}
				amount--;
			}
			else
			{
				npos++;
				amount--;
			}
		}
		else
			amount = -1;
		if (amount < 0)
		{
			bool_start = false;
			bool_end = true;
			bool_optimize = false;
		}
	}
}

void logic::forgetWord(int& npos, vector<Word>& words, bool& bool_stop, bool& bool_optimize, bool& bool_start, bool& bool_end, int& amount, int& lastPos)
{
	if (bool_start == true && bool_end == false) {
		lastPos = npos;
		words[npos].ForgetTime++;
		words[npos].ReviewTime++;
		words[npos].History.push_back(1);
		bool_stop = false;
		if (npos < (int)(words.size() - 1)) {
			if (bool_optimize)
			{
				npos++;
				while (words[npos].ReviewTime != 0 && bool_stop == false) {
					if (((float)(words[npos].ReviewTime - words[npos].ForgetTime) / (float)(words[npos].ReviewTime + 1)) > 0.55) {
						npos++;
					}
					else {
						bool_stop = true;
					}
				}
				amount--;
			}
			else
			{
				npos++;
				amount--;
			}
		}
		else
			amount = -1;
		if (amount < 0)
		{
			bool_start = false;
			bool_end = true;
			bool_optimize = false;
		}
	}
}

void logic::playMusic(bool& lerp, string& musicPath)
{
	lerp = !lerp;
	musicPath = "braveman.wav";
	if (lerp == true)
		PlaySound(_T(musicPath.c_str()), NULL, SND_FILENAME | SND_ASYNC);
	else
		PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
}

void logic::undo(bool& bool_start, bool& bool_end, vector<Word>& words, int& npos,int& amount)
{
	if (bool_start == true && bool_end == false && words[npos].ReviewTime != 0&&!words[npos].History.empty()) {
		if (words[npos].History.back() == 0) {
			words[npos].ReviewTime--;
			words[npos].History.pop_back();
		}
		else if (words[npos].History.back() == 1) {
			words[npos].ForgetTime--;
			words[npos].ReviewTime--;
			words[npos].History.pop_back();
		}
		amount++;
	}
}

void logic::reviewOptimize(int& npos, vector<Word>& words, vector<Word>::iterator& iter, int& amount, int& wordMaster, bool& bool_start, bool& bool_end, bool& bool_chinese, bool& bool_optimize)
{
	npos = 0;
	if (npos < (int)(words.size() - 1)) {
		sort(words.begin(), words.end(), compRate);
		iter = find(words.begin(), words.end(), 0);
		amount = iter - words.begin() - 1;
		bool_start = true;
		bool_end = false;
		bool_chinese = false;
		bool_optimize = true;
		amount -= wordMaster;
	}
}

void logic::clearHistory()
{
	char buffer[MAX_PATH];
	_getcwd(buffer, MAX_PATH);
	string path = buffer;
	path = path + "\\data.dat";
	ofstream dataFile(path, ios::trunc);//ios::trunc是清除原文件内容,可不写,默认就是它
	if (!dataFile) {
		cout << "Create file failure...\n";
		exit(0);
	}
	dataFile.close();
}

//0 开始记忆
//1 优化复习
//2 复习本轮
//3 记得
//4 遗忘
//5 撤销记忆
//6 上个单词
//7 撤销上个单词记忆
void logic::saveHistory(int choice)
{
	char buffer[MAX_PATH];
	_getcwd(buffer, MAX_PATH);
	string path = buffer;
	path = path + "\\data.dat";
	ofstream dataFile(path, ios::app);
	dataFile << choice << endl;
	dataFile.close();
}

void logic::readHistory(int& npos, vector<Word>& words, vector<Word>::iterator& iter, int& amount, bool& bool_start, bool& bool_end, bool& bool_chinese, int& startPos,int& wordMaster, bool& bool_optimize, int& lastPos, bool& bool_stop)
{
	//读取文件
	ifstream dataFile;
	char buffer[MAX_PATH];
	_getcwd(buffer, MAX_PATH);
	string path = buffer;
	path = path + "\\data.dat";
	dataFile.open(path);
	vector<int> command;
	vector<int>::iterator iterInt;
	string readline;
	while (getline(dataFile, readline)) {
		command.push_back(atoi(readline.c_str()));
	}
	iterInt = command.begin();
	while (iterInt - command.begin() < (command.end()- command.begin())) {
		switch (*iterInt)
		{
		case 0:
			logic::startMemory(npos, words, iter, amount, bool_start, bool_end, bool_chinese, startPos);
			break;
		case 1:
			logic::reviewOptimize(npos, words, iter, amount, wordMaster, bool_start, bool_end, bool_chinese, bool_optimize);
			break;
		case 2:
			logic::reviewMemory(npos, words, iter, amount, bool_start, bool_end, bool_chinese, startPos);
			break;
		case 3:
			logic::rememberWord(npos, words, bool_stop, bool_optimize, bool_start, bool_end, amount, lastPos);
			break;
		case 4:
			logic::forgetWord(npos, words, bool_stop, bool_optimize, bool_start, bool_end, amount, lastPos);
			break;
		case 5:
			logic::undo(bool_start, bool_end, words, npos,amount);
			break;
		case 6:
			if (npos > 0)
				npos--;
			break;
		case 7:
			if (npos > 0) {
				npos--;
				logic::undo(bool_start, bool_end, words, npos,amount);
			}
			break;
		}
		iterInt++;
	}
}
