#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <format>
#include <numeric>
#include <chrono>
#include <algorithm>
#include <unordered_map>


using namespace std;

constexpr size_t PLAYER_NUM = 200'0000;

class Player
{
public:
	Player();
	~Player();
	
	Player(const Player& other);
	Player& operator=(const Player& other);

	//Player(Player&& other) noexcept;
	//Player& operator=(Player&& other) noexcept;

	string getName() const;
	int getScore() const;
	size_t getID() const;
	size_t getNum() const;
	char* getP() const;

	friend ostream& operator<<(ostream& os, const Player& player);
	friend istream& operator>>(istream& os, Player& player);

	void read(istream& is);
	void print() const;

//private:
	string name;
	int score;
	size_t id;
	size_t num;
	char* p;
};

void ExecuteFirst();
void ExecuteSecond();
void ExecuteThird();
void ExecuteFourth();
void ExecuteFifth();

array<Player, PLAYER_NUM> players;

auto start_time = std::chrono::high_resolution_clock::now();
auto end_time = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();


int main()
{

	ifstream in{ "2023 STL ���� ����", ios::binary };

	if (!in)
	{
		cout << "2023 STL ���� ���� ���� ����!\n";
		return 0;
	}

	for (Player& player : players)
	{
		player.read(in);
	}
	
	ExecuteFirst();

	ExecuteSecond();

	ExecuteThird();

	//ExecuteFourth();
	
	//ExecuteFifth();
}

Player::Player()
{
}

Player::~Player()
{
	delete[] p; 
}

Player::Player(const Player& other)
{
	name = other.name;
	score = other.score;
	id = other.id;
	num = other.num;
	p = new char[num];
	memcpy(p, other.p, num);
}

Player& Player::operator=(const Player& other)
{
	if (this == &other)
	{
		return *this;
	}
	delete[] p;

	name = other.name;
	score = other.score;
	id = other.id;
	num = other.num;
	p = new char[num];
	memcpy(p, other.p, num);

	return *this;
}

//Player::Player(Player&& other) noexcept
//{
//	name = other.name;
//	score = other.score;
//	id = other.id;
//	num = other.num;
//	p = other.p;
//
//	other.name = "";
//	other.score = 0;
//	other.id = 0;
//	other.num = 0;
//	other.p = nullptr;
//}
//
//Player& Player::operator=(Player&& other) noexcept
//{
//	if (this == &other)
//	{
//		return *this;
//	}
//	delete[] p;
//
//	name = other.name;
//	score = other.score;
//	id = other.id;
//	num = other.num;
//	p = other.p;
//
//	other.name = "";
//	other.score = 0;
//	other.id = 0;
//	other.num = 0;
//	other.p = nullptr;
//
//	return *this;
//}

string Player::getName() const
{
	return name;
}

int Player::getScore() const
{
	return score;
}

size_t Player::getID() const
{
	return id;
}

size_t Player::getNum() const
{
	return num;
}

char* Player::getP() const
{
	return p;
}

void Player::read(istream& is)
{
	is.read((char*)this, sizeof Player);
	p = nullptr;
	p = new char[num];
	is.read(p, num);
}

void Player::print() const
{
	cout << endl;
	cout << format("�̸�:{:15}, ", name) << " ���̵�:" << id << ", ����:" << score << ", �ڿ���:" << num << endl;
	cout << "����ȱ���:";
	for (int i = 0; i < num; ++i)
	{
		cout << p[i];
	}
	cout << endl;
}

ostream& operator<<(ostream& os, const Player& player)
{
	player.print();
	return os;
}

istream& operator>>(istream& is, Player& player)
{
	return is.read((char*)&player, sizeof Player);
}

void ExecuteFirst()
{
	cout << "1�� ����\n";
	players[PLAYER_NUM - 1].print();
	cout << "--------------------------------------------------------------------------------" << endl << endl;
}

void ExecuteSecond()
{
	//2 ����:423456369 , ���: 123468028
	cout << "2�� ����\n";
	//start_time = std::chrono::high_resolution_clock::now();

	//����:123468028
	long long sum = 0;
	//int max = numeric_limits<int>::min();
	//int max_index = 0;

	sum += players[0].getScore();
	auto max_score = max_element(players.begin(), players.end(), [&sum](const Player& a, const Player& b) {
		sum += b.getScore();
		return a.getScore() < b.getScore();
		});
	
	//sum = accumulate(players.begin(), players.end(), 0ll, [](long long sum, const Player& a) {
	//	return sum + a.getScore();
	//	});

	//auto max_score = max_element(players.begin(), players.end(), [](const Player& a, const Player& b) {
	//	return a.getScore() < b.getScore();
	//	});

	//for (int i = 0; i < PLAYER_NUM; ++i)	
	//{
	//	sum += players[i].getScore();
	//	if (max < players[i].getScore())
	//	{
	//		max = players[i].getScore();
	//		max_index = i;
	//	}
	//}

	cout << "���� ū ������ Player\n";
	max_score->print();
	//players[max_index].print();
	cout << "��� Player�� ��� ����:" << sum / PLAYER_NUM << endl;

	//end_time = std::chrono::high_resolution_clock::now();
	//duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
	//cout << "�ɸ� �ð�: " << duration << "micro sedconds" << endl;

	cout << "--------------------------------------------------------------------------------" << endl << endl;
}

void ExecuteThird()
{
	cout << "3�� ����\n";

	start_time = std::chrono::high_resolution_clock::now();


	sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
		return a.getID() < b.getID();
		});

	end_time = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
	cout << "�ɸ� �ð�: " << duration << "s" << endl;


	ofstream out{ "�������̵�.txt" };

	int allSameNum = 0;
	int firstIndex = 0;
	int sameCount = 1;
	size_t prevID = players[0].getID();
	for (int i = 1; i < PLAYER_NUM; ++i)
	{
		if (players[i].getID() != prevID)
		{
			if (sameCount > 1)
			{
				for (int j = firstIndex; j < firstIndex + sameCount; ++j)
				{
					++allSameNum;
					out << "�̸�:" << players[j].getName() << ", ID:" << players[j].getID() << endl;
				}
			}
			sameCount = 1;
			firstIndex = i;
			prevID = players[i].getID();
			continue;
		}
		++sameCount;

		if (i == PLAYER_NUM - 1)
		{
			if (sameCount > 1)
			{
				for (int j = firstIndex; j < firstIndex + sameCount; ++j)
				{
					++allSameNum;
					out << "�̸�:" << players[j].getName() << ", ID:" << players[j].getID() << endl;
				}
			}
			break;
		}
	}
	cout << "ID�� ���� ��� ��ü�� ��:" << allSameNum << endl;

	cout << "--------------------------------------------------------------------------------" << endl << endl;
}

void ExecuteFourth()
{
	cout << "4�� ����\n";

	int moreThan10Num = 0;
	for (Player& player : players)
	{
		sort(player.getP(), player.getP() + player.getNum());
		
		int aNum = 0;
		for (int i = 0; i < player.getNum(); ++i)
		{
			if (player.getP()[i] != 'a')
			{
				break;
			}

			++aNum;
		}

		if (aNum >= 10)
		{
			++moreThan10Num;
		}

		//if (count(player.getP(), player.getP() + player.getNum(), 'a') >= 10)
		//{
		//	moreThan10Num++;
		//}
	}
	cout << "a�� 10�� �̻��� Player�� ��:" << moreThan10Num << endl;

	cout << "--------------------------------------------------------------------------------" << endl << endl;
}

void ExecuteFifth()
{
	cout << "5�� ����\n";

	size_t inputId;
	cout << "ID�Է�(ID���� �Է½� ����):";
	while (cin >> inputId)
	{
		cout << endl << "ID ����";
		sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
			return a.getID() < b.getID();
			});

		start_time = std::chrono::high_resolution_clock::now();

		array<Player, PLAYER_NUM>::iterator itr = players.begin();

		itr = lower_bound(players.begin(), players.end(), inputId, [](const Player& a, size_t id) {
			return a.getID() < id;
			});

		//itr = find_if(players.begin(), players.end(), [&inputId](const Player& a) {
		//	return a.getID() == inputId;
		//	});
		
		//if (itr != players.end())
		if(itr->getID() == inputId)
		{
			array<Player, PLAYER_NUM>::iterator  first, last;

			first = itr;
			while (true)
			{
				if (first == players.begin())
				{
					break;
				}

				if (first->getID() == (first - 1)->getID())
				{
					--first;
					continue;
				}

				break;
			}

			last = itr;
			while (true)
			{
				if (last + 1 == players.end())
				{
					break;
				}

				if (last->getID() == (last + 1)->getID())
				{
					++last;
					continue;
				}

				break;
			}

			if (first != players.begin())
			{
				(first - 1)->print();
			}

			for (auto p = first; p != last + 1; ++p)
			{
				p->print();
			}

			if (last + 1 != players.end())
			{
				(last + 1)->print();
			}

			//while (true)
			//{
			//	itr->print();

			//	if (itr != players.begin())
			//	{
			//		(itr - 1)->print();
			//	}

			//	if (itr + 1 == players.end())
			//	{
			//		break;
			//	}
			//	else if (itr->getID() != (itr + 1)->getID())
			//	{
			//		(itr + 1)->print();
			//		break;
			//	}
			//	else
			//	{
			//		(itr + 1)->print();
			//		++itr;
			//	}
			//}
		}
		else
		{
			cout << endl << "�������� �ʴ� ID�Դϴ�.";
			cout << "--------------------------------------------------------------------------------" << endl;
			cout << "ID�Է�(ID���� �Է½� ����):";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}


		end_time = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::milliseconds > (end_time - start_time).count();
		cout << "�ɸ� �ð�: " << duration << "ms" << endl;

		cout << endl << endl << "name ����";
		sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
			return a.getName() < b.getName();
			});

		
		itr = lower_bound(players.begin(), players.end(), inputId, [](const Player& a, size_t id) {
			return a.getID() < id;
			});

		//itr = find_if(players.begin(), players.end(), [&inputId](const Player& a) {
		//	return a.getID() == inputId;
		//	});

		if (itr != players.end())
		{

			itr->print();

			if (itr != players.begin())
			{
				(itr - 1)->print();
			}

			if (itr + 1 != players.end())
			{
				(itr + 1)->print();
			}
			cout << endl << endl;
		}

		cout << "score ����";
		sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
			return a.getScore() < b.getScore();
			});

		itr = players.begin();
		itr = find_if(players.begin(), players.end(), [&inputId](const Player& a) {
			return a.getID() == inputId;
			});
		if (itr != players.end())
		{

			itr->print();

			if (itr != players.begin())
			{
				(itr - 1)->print();
			}

			if (itr + 1 != players.end())
			{
				(itr + 1)->print();
			}
			cout << endl << endl;
		}


		cout << "--------------------------------------------------------------------------------" << endl;
		cout << "ID�Է�(ID���� �Է½� ����):";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}
