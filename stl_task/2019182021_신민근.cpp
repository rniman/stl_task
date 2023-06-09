#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <format>
#include <numeric>
#include <chrono>
#include <algorithm>


using namespace std;

constexpr size_t PLAYER_NUM = 200'0000;

class Player
{
public:
	Player();
	~Player();

	Player(const Player& other);
	Player& operator=(const Player& other);

	Player(Player&& other) noexcept;
	Player& operator=(Player&& other) noexcept;

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

	ifstream in{ "2023 STL 과제 파일", ios::binary };

	if (!in)
	{
		cout << "2023 STL 과제 파일 열기 실패!\n";
		return 0;
	}

	for (Player& player : players)
	{
		player.read(in);
	}

	ExecuteFirst();

	ExecuteSecond();

	ExecuteThird();

	ExecuteFourth();

	ExecuteFifth();
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

Player::Player(Player&& other) noexcept
{
	name = other.name;
	score = other.score;
	id = other.id;
	num = other.num;
	p = other.p;

	other.name = "";
	other.score = 0;
	other.id = 0;
	other.num = 0;
	other.p = nullptr;
}

Player& Player::operator=(Player&& other) noexcept
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
	p = other.p;

	other.name = "";
	other.score = 0;
	other.id = 0;
	other.num = 0;
	other.p = nullptr;

	return *this;
}

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
	cout << format("이름:{:15}, ", name) << " 아이디:" << id << ", 점수:" << score << ", 자원수:" << num << endl;
	cout << "저장된글자:";
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
	cout << "1번 문제\n";
	players[PLAYER_NUM - 1].print();
	cout << "--------------------------------------------------------------------------------" << endl << endl;
}

void ExecuteSecond()
{
	//2 점수:423456369 , 평균: 123468028
	cout << "2번 문제\n";
	//start_time = std::chrono::high_resolution_clock::now();

	long long sum = 0;

	sum += players[0].getScore();
	auto max_score = max_element(players.begin(), players.end(), [&sum](const Player& a, const Player& b) {
		sum += b.getScore();
		return a.getScore() < b.getScore();
		});

	//int max = numeric_limits<int>::min();
	//int max_index = 0;

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

	//players[max_index].print();

	cout << "가장 큰 점수의 Player\n";
	max_score->print();
	cout << "모든 Player의 평균 점수:" << sum / PLAYER_NUM << endl;

	//end_time = std::chrono::high_resolution_clock::now();
	//duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
	//cout << "걸린 시간: " << duration << "micro sedconds" << endl;

	cout << "--------------------------------------------------------------------------------" << endl << endl;
}

void ExecuteThird()
{
	//1149459

	cout << "3번 문제\n";

	//start_time = std::chrono::high_resolution_clock::now();

	sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
		return a.getID() < b.getID();
		});

	//end_time = std::chrono::high_resolution_clock::now();
	//duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
	//cout << "걸린 시간: " << duration << "s" << endl;


	ofstream out{ "같은아이디.txt" };

	int allSameNum = 0;
	auto itr = players.begin();
	auto prevItr = itr;
	while (true)
	{
		itr = find_if(prevItr, players.end(), [&prevItr](const Player& p) {
			return p.getID() != prevItr->getID();
			});


		if (distance(prevItr, itr) > 1)
		{
			for (auto p = prevItr; p != itr; ++p)
			{
				++allSameNum;
				out << "이름:" << p->getName() << ", ID:" << p->getID() << endl;
			}
		}

		if (itr == players.end())
			break;
		prevItr = itr;
	}

	//int firstIndex = 0;
	//int sameCount = 1;
	//size_t prevID = players[0].getID();
	//for (int i = 1; i < PLAYER_NUM; ++i)
	//{
	//	if (players[i].getID() != prevID)
	//	{
	//		if (sameCount > 1)
	//		{
	//			for (int j = firstIndex; j < firstIndex + sameCount; ++j)
	//			{
	//				++allSameNum;
	//				out << "이름:" << players[j].getName() << ", ID:" << players[j].getID() << endl;
	//			}
	//		}
	//		sameCount = 1;
	//		firstIndex = i;
	//		prevID = players[i].getID();
	//		continue;
	//	}
	//	++sameCount;

	//	if (i == PLAYER_NUM - 1)
	//	{
	//		if (sameCount > 1)
	//		{
	//			for (int j = firstIndex; j < firstIndex + sameCount; ++j)
	//			{
	//				++allSameNum;
	//				out << "이름:" << players[j].getName() << ", ID:" << players[j].getID() << endl;
	//			}
	//		}
	//		break;
	//	}
	//}
	cout << "ID가 같은 모든 객체의 수:" << allSameNum << endl;

	cout << "--------------------------------------------------------------------------------" << endl << endl;
}

void ExecuteFourth()
{
	//983062
	cout << "4번 문제\n";

	int moreThan10Num = 0;
	for (Player& player : players)
	{
		sort(player.getP(), player.getP() + player.getNum());

		auto itr = find_if(player.getP(), player.getP() + player.getNum(), [](char c) {
			return c != 'a';
			});

		if (distance(player.getP(), itr) >= 10)
		{
			++moreThan10Num;
		}	

		//int aNum = 0;
		//for (int i = 0; i < player.getNum(); ++i)
		//{
		//	if (player.getP()[i] != 'a')
		//	{
		//		break;
		//	}

		//	++aNum;
		//}

		//if (aNum >= 10)
		//{
		//	++moreThan10Num;
		//}

		//if (count(player.getP(), player.getP() + player.getNum(), 'a') >= 10)
		//{
		//	moreThan10Num++;
		//}
	}
	cout << "a가 10개 이상인 Player의 수:" << moreThan10Num << endl;

	cout << "--------------------------------------------------------------------------------" << endl << endl;
}

void ExecuteFifth()
{
	cout << "5번 문제\n";

	size_t inputId;
	cout << "ID입력(ID외의 입력시 종료):";
	while (cin >> inputId)
	{
		cout << endl << "ID 정렬";
		sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
			return a.getID() < b.getID();
			});

		//start_time = std::chrono::high_resolution_clock::now();

		array<Player, PLAYER_NUM>::iterator itr = players.begin();
		int numSameId = 0;

		itr = lower_bound(players.begin(), players.end(), inputId, [](const Player& a, size_t id) {
			return a.getID() < id;
			});

		//itr = find_if(players.begin(), players.end(), [&inputId](const Player& a) {
		//	return a.getID() == inputId;
		//	});

		//if (itr != players.end())
		if (itr != players.end() && itr->getID() == inputId)
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
				++numSameId;
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
			cout << endl << "존재하지 않는 ID입니다.";
			cout << "--------------------------------------------------------------------------------" << endl;
			cout << "ID입력(ID외의 입력시 종료):";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}


		//end_time = std::chrono::high_resolution_clock::now();
		//duration = std::chrono::duration_cast<std::chrono::milliseconds> (end_time - start_time).count();
		//cout << "걸린 시간: " << duration << "ms" << endl;

		cout << endl << endl << "--------------------------------------------------------------------------------" << endl;
		cout << "name 정렬";
		sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
			return a.getName() < b.getName();
			});

		int numOutput = 0;
		itr = players.begin();

		while (true)
		{
			itr = find_if(itr, players.end(), [&inputId](const Player& a) {
				return a.getID() == inputId;
				});

			if (itr == players.end())
			{
				break;
			}
			
			if (itr != players.begin())
			{
				(itr - 1)->print();
			}

			++numOutput;
			itr->print();

			if (itr + 1 != players.end())
			{
				(itr + 1)->print();
			}
			cout << endl << endl;

			if (numOutput == numSameId)
				break;

			++itr;
		}

		cout << endl << endl << "--------------------------------------------------------------------------------" << endl;
		cout << "score 정렬";
		
		sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
			return a.getScore() < b.getScore();
			});

		numOutput = 0;
		itr = players.begin();
		while (true)
		{
			itr = find_if(itr, players.end(), [&inputId](const Player& a) {
				return a.getID() == inputId;
				});

			if (itr == players.end())
			{
				break;
			}

			if (itr != players.begin())
			{
				(itr - 1)->print();
			}

			++numOutput;
			itr->print();

			if (itr + 1 != players.end())
			{
				(itr + 1)->print();
			}
			cout << endl << endl;

			if (numOutput == numSameId)
				break;

			++itr;
		}


		cout << "--------------------------------------------------------------------------------" << endl;
		cout << "ID입력(ID외의 입력시 종료):";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}
