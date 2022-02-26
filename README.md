# CSV背单词v0.6

视频教程：https://www.bilibili.com/video/BV1PP4y1A77a

bug反馈请私信~

excel模板是example.xlsx

![Image text](https://raw.githubusercontent.com/Routhleck/CSVrecite/v0.5/img-folder/new.png)

# V0.1

## 按钮功能说明：

### 加载csv

弹出资源管理器文件选择窗口，选择需要加载的csv格式文件
csv格式文件说明：共5列，每行元素依次为单词，词性，释义，记忆次数，遗忘次数

### 保存文件

将已经读取的csv格式文件存储到本程序的目录下，为save.csv

### 导出文件

弹出资源管理器文件夹选择窗口，选择要存储到的文件夹，将已读取的内容导出到此文件夹下，为list.csv

### 振作起来

播放音乐，提高神

### 开始记忆：

弹出输入窗口，输入需要记忆单词数量的正整数，便可开始记忆记忆次数为0的单词

### 复习本轮

将所有记忆次数不为0的单词，按照遗忘率大小排序，进行一轮的记忆

### 释义显示

对本单词的释义进行开关

### 记得

将本单词的记忆次数+1，仅在学习中（点击开始记忆或复习本轮且没有结束学习）可用

### 遗忘

将本单词的遗忘次数和记忆次数均+1，仅在学习中（点击开始记忆或复习本轮且没有结束学习）可用

## 界面显示说明:

![Image text](https://raw.githubusercontent.com/Routhleck/CSVrecite/v0.3/img-folder/image-20220223165152022.png)

# V0.2

## 更新界面信息：

![Image text](https://raw.githubusercontent.com/Routhleck/CSVrecite/v0.3/img-folder/image-20220223165629927.png)

### 单词总数 

总共的单词数量

### 单词记忆数量 

单词记忆次数大于0的数量

### 单词未记忆数量 

单词记忆次数等于0的数量

### 当前一轮学习量剩余 

开始记忆或者复习本轮还剩未学习的单词数量（不包括现在学习的单词）

### 已掌握单词数量

(记忆次数-遗忘次数)/(记忆次数+1)大于70%的单词数量 

# V0.3

## 更新功能按钮：

![Image text](https://raw.githubusercontent.com/Routhleck/CSVrecite/v0.3/img-folder/image-20220223165834447.png)

### 撤销记忆

将正在学习（界面展示）的单词遗忘次数与记忆次数均-1

### 上个单词

回到上个单词，不会修改任何数据

### 撤销上个单词记忆

将上两步操作合并在一起，便于取消上个单词的误操作

##源码文件更改

新增ui.cpp和ui.h以增加代码可读性

# V0.4

##问题修复

###返回逻辑

修复了撤销的逻辑，现在用单独的int型vector去存储每个单词的记忆的历史记录，但仅限于撤销本次打开应用后的单词记忆

## 更新功能按钮

###优化复习

本复习方法将不会把已掌握单词(记忆次数-遗忘次数)/(记忆次数+1)大于70%的单词数量）划入复习范围中

## 更新界面信息

###统计图表

![Image text](https://raw.githubusercontent.com/Routhleck/CSVrecite/v0.4/img-folder/1645626102(1).jpg)

# V0.5

## 问题修复

修复一些之前没有注意到的致命性问题

## 更新界面显示

### DPI缩放优化

现在可以根据显示器的dpi缩放进行分辨率调整，将不会有分辨率损失

### 上一个单词显示

可以显示上一个记忆的单词信息

![Image text](https://raw.githubusercontent.com/Routhleck/CSVrecite/v0.5/img-folder/v0.5.png)

## 源码文件更改

新增logic.cpp和logic.h以增加代码可读性

# V0.6

## 问题修复

上一个单词的记忆和遗忘显示bug修复

## 更新功能

### 单词读音

每次学习的单词都会朗读

## 更新按钮功能

###读音

可以朗读当前单词

![Image text](https://raw.githubusercontent.com/Routhleck/CSVrecite/v0.6/img-folder/v0.6.png)

## 源码文件更改

添加textToSpeech.h以及textToSpeech.cpp
使用微软TTF引擎，接入文字转语音API

#v0.7

## 问题修复

调用微软TTF API时，没有反应，需要用户联网，现在会持续与api建立连接，直到语音实现

## 更新按钮功能

###加载历史

现在可以实时保存用户的操作记录至data.dat文件中，若发生闪退等情况退出应用，点击此按钮便可直接读取上次未完成的记忆
注：在记忆时无法进行该操作

![Image text](https://raw.githubusercontent.com/Routhleck/CSVrecite/v0.7/img-folder/v0.7.png)

