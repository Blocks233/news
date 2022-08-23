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
S s[] = { {"����",18,40},{"С��",18,30},{"Ů��",18,40},{"�к�",8,18},{"Ů��",8,18},{"����",1,8} };
string rea[] = { "��ҹ","������","������","���ֻ�","����Ϸ","���յ�" };

struct Rst {
	string rst;
	string prefix[16];
	int num_of_prefix; //ǰ׺����
	string suffix[16];
	int num_of_suffix;
};

Rst rst[] = { \
{"",{"���", "����", "�"},3,{"θ��","�ΰ�","�ΰ�"},3},\
{"",{"ס��"},1,{"ICU","EICU","ҽԺ"},3},\
{"���",{"�շ�"},1,{""},1},\
{"�Գ�Ѫ",{"����","ͻ��"},2,{""},1},\
{"����ʹ��",{""},1,{""},1}\
};

string adv[] = { "����","ÿ��","����" };


string Subject()
{
	string subject = "";
	int age = (rand() % 40) + 1;
	if (rand() % 5) //��ʾ���� 
	{
		char* buffer = new char[3];
		_itoa(age, buffer, 10);
		subject = buffer;
		subject += "��";
	}


	int index = 0;
	int T = (sizeof(s) / sizeof(s[0])) * 5;
	while (--T) //�������� 
	{
		index = rand() % (sizeof(s) / sizeof(s[0]));
		if (s[index].ageMax >= age && s[index].ageMin <= age)
		{
			subject += s[index].Name;
			break;
		}
	}
	if (!T) subject += "ĳ��";

	return subject;
}

string Reason()
{
	string reason = "";
	int Num = rand() % 2 + 1; //ԭ�����
	if (rand() % 5) reason += adv[rand() % (sizeof(adv) / sizeof(adv[0]))];
	int lst_index = -1;
	while (Num--)
	{
		int index = rand() % (sizeof(rea) / sizeof(rea[0]));

		if (index == lst_index) break;
		lst_index = index; //��ֹ������ͬ

		reason += rea[index];
		switch (index) {
		case 0:
			char* buffer = new char[3];
			int time = rand() % 5 + 1;
			_itoa(time, buffer, 10);
			reason += "��" + (string)buffer + "��";
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
	else srand(atoi(argv[1])); //�����������

	printf("#%s%s%s#", Subject().data(), Reason().data(), Result().data());

	return 0;
}