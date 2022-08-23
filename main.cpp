#define _CRT_SECURE_NO_WARNINGS

#include<cstdio>
#include<string>
#include<stdlib.h>
#include<ctime>

#define to_array_length(array) (sizeof(array) / sizeof(array[0]))

using namespace std;

struct {
	int age = 0;
	int rea[2] = { -1,-1 };
	int rst = -1;
	int LastName = -1;
	int province = -1;
	int industry = -1;
	int rst_p = -1;
	int rst_s = -1;
}info;

struct S {
	string Name;
	int ageMin;
	int ageMax;
};
S s[] = { {"����",18,40},{"С��",18,30},{"Ů��",18,40},{"�к�",8,18},{"Ů��",8,18},{"����",1,8} };

struct Rea {
	string reason;
	string detial;
};
Rea rea[] = { { "��ҹ","�Ӱൽ��ҹ" }, { "������","���˾ͺ�����" }, { "������","���˾ͳ�����" }, { "���ֻ�","���ֻ�����Ƶ" }, { "����Ϸ","����Ϸ" }, { "���յ�","���յ�" } };

struct Rst {
	string rst;
	string prefix[16];
	int num_of_prefix; //ǰ׺����
	string suffix[16];
	int num_of_suffix;
	string symptom;
};

Rst rst[] = { \
{"", { "���", "����", "�" }, 3, { "θ��","�ΰ�","�ΰ�" }, 3, "����"}, \
{"", { "ס��" }, 1, { "ICU","EICU","ҽԺ" }, 3, "����"}, \
{"���", { "�շ�" }, 1, { "" }, 1, "���ܿ��Ƶĳ鴤"}, \
{"�Գ�Ѫ", { "����","ͻ��" }, 2, { "" }, 1, "ͻ��ͷʹ������Ż�¡����ﲻ��"}, \
{"֬����", { "����","���" }, 2, { "" }, 1, "��ʹ"}, \
{"��Ѫ��", { "����","����" }, 2, { "" }, 1, "���ظ�Ⱦ"}, \
{"ʹ��", { "����" }, 1, { "" }, 1, "�ؽھ�����ʹ"}\
};

string adv[] = { "����","ÿ��","����" };

string province[] = { "�ӱ�","ɽ��","���ɹ�","����","����","������","����","�㽭","����","����","����","ɽ��","����","����","����","�㶫","����","����","�Ĵ�","����","����","����","����","�ຣ","����","���Ļ���","�½�ά���" };
string LastName[] = { "��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","֣","л","��","��","��","��","��","��","��","��","��","��","��","��","��","��","Ԭ","��","��","��","��","��","��","Ҷ","��","��","κ","��","��","��","��","Ҧ","¬","��","��","��","̷","½","��","��","��","ʯ","��","��","��","Τ","��","��","��","��","��","��","��","��","��","��","Ѧ","��","��","��","��","��","ʷ","��","��","��","��","ë","��","��","��","��","Ǯ","��","��","��","��","Ī","��","��","��" };
string industry[] = { "��������","��������","�����豸","IT����","΢����","ͨ��","רҵ��ѯ����","���ز�","��е����","����" };

string tplt = "%province%������%industry%��ҵ��С%LastName%����%age%�꣬����ԭ��%adv%%reason%�����˶������գ������Ӱ�����о�ȫ������������������Ƶʱ%symptom%������飬С%LastName%��%result%��ר�����ѣ�%adv%%reason2%���ܻᵼ��%result2%��";

string Subject()
{
	string subject = "";
	int age = (rand() % 40) + 1;
	info.age = age;
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
		index = rand() % to_array_length(s);
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
	if (rand() % 5) reason += adv[rand() % to_array_length(adv)];
	int lst_index = -1;
	while (Num--)
	{
		int index = rand() % to_array_length(rea);

		if (index == lst_index) break;
		lst_index = index; //��ֹ������ͬ
		info.rea[Num] = index;

		reason += rea[index].reason;
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
	int index = rand() % to_array_length(rst);
	info.rst = index;
	result = rst[index].prefix[info.rst_p = rand() % rst[index].num_of_prefix] + rst[index].rst + rst[index].suffix[info.rst_s = rand() % rst[index].num_of_suffix];
	return result;
}

void Replace(string* input, const char* keyword, string replace)
{
	string tmp = *input;
	size_t t = tmp.find(keyword);
	while (t != -1)
	{
		tmp.replace(t, strlen(keyword), replace);
		t = tmp.find(keyword);
	}
	*input = tmp;
	return;
}

string Detial()
{
	info.LastName = rand() % to_array_length(LastName);
	info.province = rand() % to_array_length(province);
	info.industry = rand() % to_array_length(industry);
	string detial = tplt;

	Replace(&detial, "%province%", province[info.province]);
	Replace(&detial, "%industry%", industry[info.industry]);
	Replace(&detial, "%LastName%", LastName[info.LastName]);
	char* buffer = new char[3];
	_itoa(info.age, buffer, 10);
	Replace(&detial, "%age%", buffer);
	Replace(&detial, "%adv%", adv[rand() % to_array_length(adv)]);
	Replace(&detial, "%symptom%", rst[info.rst].symptom);

	if (rst[info.rst].rst.length() == 0)Replace(&detial, "%result%", rst[info.rst].prefix[info.rst_p] + rst[info.rst].suffix[info.rst_s]);
	else Replace(&detial, "%result%", "���Ϊ" + rst[info.rst].rst); //����Ҫ��

	string reason="";
	for (int i = 0; i < to_array_length(info.rea); i++)
		if (info.rea[i] != -1)
			reason += (rea[info.rea[i]].detial + ",");
	Replace(&detial, "%reason%", reason);

	reason = "";
	for (int i = 0; i < to_array_length(info.rea); i++)
		if (info.rea[i] != -1)
			reason += rea[info.rea[i]].reason;
	Replace(&detial, "%reason2%", reason);

	if (rst[info.rst].rst.length() == 0) Replace(&detial, "%result2%", rst[info.rst].prefix[info.rst_p] + rst[info.rst].suffix[info.rst_s]);
	else Replace(&detial, "%result2%", rst[info.rst].rst);


	return detial;
}

int main(int argc, char* argv[])
{
	if (argc == 1) srand(time(0));
	else srand(atoi(argv[1])); //�����������

	//����
	printf("#%s%s%s#\n", Subject().data(), Reason().data(), Result().data());

	//��ϸ
	printf("%s\n", Detial().data());
	


	return 0;
}