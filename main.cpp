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
S s[] = { {"男子",18,40},{"小伙",18,30},{"女子",18,40},{"男孩",8,18},{"女孩",8,18},{"宝宝",1,8} };

struct Rea {
	string reason;
	string detial;
};
Rea rea[] = { { "熬夜","加班到深夜" }, { "喝饮料","渴了就喝饮料" }, { "吃外卖","饿了就吃外卖" }, { "玩手机","玩手机看视频" }, { "玩游戏","玩游戏" }, { "吹空调","吹空调" } };

struct Rst {
	string rst;
	string prefix[16];
	int num_of_prefix; //前缀数量
	string suffix[16];
	int num_of_suffix;
	string symptom;
};

Rst rst[] = { \
{"", { "查出", "导致", "罹患" }, 3, { "胃癌","肺癌","肝癌" }, 3, "昏迷"}, \
{"", { "住进" }, 1, { "ICU","EICU","医院" }, 3, "昏迷"}, \
{"癫痫", { "诱发" }, 1, { "" }, 1, "不受控制的抽搐"}, \
{"脑出血", { "导致","突发" }, 2, { "" }, 1, "突发头痛、恶心呕吐、言语不清"}, \
{"脂肪肝", { "导致","造成" }, 2, { "" }, 1, "腹痛"}, \
{"白血病", { "导致","引发" }, 2, { "" }, 1, "严重感染"}, \
{"痛风", { "导致" }, 1, { "" }, 1, "关节剧烈疼痛"}\
};

string adv[] = { "经常","每天","长期" };

string province[] = { "河北","山西","内蒙古","辽宁","吉林","黑龙江","江苏","浙江","安徽","福建","江西","山东","河南","湖北","湖南","广东","广西","海南","四川","贵州","云南","陕西","甘肃","青海","西藏","宁夏回族","新疆维吾尔" };
string LastName[] = { "王","李","张","刘","陈","杨","黄","赵","吴","周","徐","孙","马","朱","胡","郭","何","高","林","郑","谢","罗","梁","宋","唐","许","韩","冯","邓","曹","彭","曾","萧","田","董","袁","潘","于","蒋","蔡","余","杜","叶","程","苏","魏","吕","丁","任","沈","姚","卢","姜","崔","钟","谭","陆","汪","范","金","石","廖","贾","夏","韦","付","方","白","邹","孟","熊","秦","邱","江","尹","薛","闫","段","雷","侯","龙","史","陶","黎","贺","顾","毛","郝","龚","邵","万","钱","严","覃","武","戴","莫","孔","向","汤" };
string industry[] = { "电子商务","计算机软件","网络设备","IT服务","微电子","通信","专业咨询服务","房地产","机械制造","基金" };

string tplt = "%province%，从事%industry%行业的小%LastName%今年%age%岁，因工作原因%adv%%reason%很少运动。近日，连续加班的他感觉全身无力，随后与家人视频时%symptom%。经检查，小%LastName%被%result%。专家提醒，%adv%%reason2%可能会导致%result2%！";

string Subject()
{
	string subject = "";
	int age = (rand() % 40) + 1;
	info.age = age;
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
		index = rand() % to_array_length(s);
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
	if (rand() % 5) reason += adv[rand() % to_array_length(adv)];
	int lst_index = -1;
	while (Num--)
	{
		int index = rand() % to_array_length(rea);

		if (index == lst_index) break;
		lst_index = index; //防止两次相同
		info.rea[Num] = index;

		reason += rea[index].reason;
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
	else Replace(&detial, "%result%", "诊断为" + rst[info.rst].rst); //这里要改

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
	else srand(atoi(argv[1])); //输入随机种子

	//标题
	printf("#%s%s%s#\n", Subject().data(), Reason().data(), Result().data());

	//详细
	printf("%s\n", Detial().data());
	


	return 0;
}