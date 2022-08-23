#define _CRT_SECURE_NO_WARNINGS

#include<cstdio>
#include<string>
#include<stdlib.h>
#include<ctime>

using namespace std;

struct S {
	string Name;
	int ageMin;
	int ageMax;
};
S s[] = { {"男子",18,40},{"小伙",18,30},{"女子",18,40},{"男孩",8,18},{"女孩",8,18},{"宝宝",1,8} };
string rea[] = { "熬夜","喝饮料","吃外卖","玩手机","玩游戏","吹空调" };

struct Rst {
	string rst;
	string prefix[16];
	int num_of_prefix; //前缀数量
	string suffix[16];
	int num_of_suffix;
};

Rst rst[] = { \
{"",{"查出", "导致", "罹患"},3,{"胃癌","肺癌","肝癌"},3},\
{"",{"住进"},1,{"ICU","EICU","医院"},3},\
{"癫痫",{"诱发"},1,{""},1},\
{"脑出血",{"导致","突发"},2,{""},1},\
{"导致痛风",{""},1,{""},1}\
};

string adv[] = { "经常","每天","长期" };


string Subject()
{
	string subject = "";
	int age = (rand() % 40) + 1;
	if (rand() % 5) //显示年龄 
	{
		char* buffer = new char[3];
		_itoa(age, buffer, 10);
		subject = buffer;
		subject += "岁";
	}


	int index = 0;
	int T = (sizeof(s) / sizeof(s[0])) * 5;
	while (--T) //生成主语 
	{
		index = rand() % (sizeof(s) / sizeof(s[0]));
		if (s[index].ageMax >= age && s[index].ageMin <= age)
		{
			subject += s[index].Name;
			break;
		}
	}
	if (!T) subject += "某人";

	return subject;
}

string Reason()
{
	string reason = "";
	int Num = rand() % 2 + 1; //原因个数
	if (rand() % 5) reason += adv[rand() % (sizeof(adv) / sizeof(adv[0]))];
	int lst_index = -1;
	while (Num--)
	{
		int index = rand() % (sizeof(rea) / sizeof(rea[0]));

		if (index == lst_index) break;
		lst_index = index; //防止两次相同

		reason += rea[index];
		switch (index) {
		case 0:
			char* buffer = new char[3];
			int time = rand() % 5 + 1;
			_itoa(time, buffer, 10);
			reason += "到" + (string)buffer + "点";
			break;
		}
	}
	return reason;
}

string Result()
{
	string result = "";
	int index = rand() % (sizeof(rst) / sizeof(rst[0]));
	result = rst[index].prefix[rand() % rst[index].num_of_prefix] + rst[index].rst + rst[index].suffix[rand() % rst[index].num_of_suffix];
	return result;
}

int main(int argc, char* argv[])
{
	if (argc == 1) srand(time(0));
	else srand(atoi(argv[1])); //输入随机种子

	printf("#%s%s%s#", Subject().data(), Reason().data(), Result().data());

	return 0;
}