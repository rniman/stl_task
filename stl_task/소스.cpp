#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <numeric>
#include <format>
#include<algorithm>

#include<unordered_map> //3��
using namespace std;


const int player_c = 2'000'000;

class Player {

public:
    Player()
    {

    };
    ~Player()
    {
        delete[] p;
    };

    string name; // �̸�, ����[3, 15]
    int score; // ����
    size_t id; // ���̵�, ��ġ�� ���̵� ���� �� ����
    size_t num; // free store�� Ȯ���� ����Ʈ ��
    char* p; // free store�� Ȯ���� �޸��� ���۹���abab

    void write(ostream& os) {
        os.write((char*)this, sizeof(Player));
        os.write((char*)p, num);
    }
    void read(istream& in) {
        in.read((char*)this, sizeof Player);
        p = nullptr;
        p = new char[num + 1];
        in.read(p, num);
        p[num] = '\0';
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& players) {
        os << "�̸�:" << format("{:25}", players.name) << ", ���̵�:  " << players.id <<
            ",����: " << players.score << ", �ڿ���:" << players.num << "\n"; 
    }
};


array<Player, player_c> ap;



bool compareById(const Player& p1, const Player& p2) {
    return p1.id < p2.id;
}

bool compareByName(const Player& p1, const Player& p2) {
    return p1.name < p2.name;
}

bool compareByScore(const Player& p1, const Player& p2) {
    return p1.score < p2.score;
}



int main()
{
    ifstream in{ "2023 STL ���� ����",ios::binary };
    if (!in)
    {
        cout << "���� ���� ����";
        return 1;
    }

    //���� �迭�� ����
    for (int i = 0; i < player_c; ++i)
    {
        in.read((char*)&ap[i], sizeof(Player));
        ap[i].p = nullptr;
        ap[i].p = new char[ap[i].num];
        in.read(ap[i].p, ap[i].num);

    }



    ////   ��ü ��� �ڵ�
    //for (const Player& play : ap)
    //{
    //   cout << play;
    //   cout << "����� ����:";
    //   for (int i = 0; i < play.num; ++i)
    //   {
    //      cout << play.p[i];
    //   }
    //   cout << '\n' ;
    //}
    //


    //1��
    cout << ap[player_c - 1];
    cout << "����� ����:";
    for (int i = 0; i < ap[player_c - 1].num; ++i) {
        cout << ap[player_c - 1].p[i];
    }
    cout << "\n";

    cout << "===========================================================" << "\n";


    //2��
    int max_score = numeric_limits<int>::min(); //int�ּڰ�
    string max_player = ""; //���� ���� ������ ���� player

    long long sum = 0;

    for (int i = 0; i < ap.size(); ++i) {
        if (ap[i].score > max_score)
        {
            max_score = ap[i].score;
            max_player = ap[i].name;
        }
        sum += ap[i].score;
    }

    cout << "������ ���� ū player:" << max_player << endl;
    cout << "���" << sum / player_c << endl;


    //3��
    ofstream out{ "�������̵�.txt" };

    sort(ap.begin(), ap.end(), [](const Player& p1, const Player& p2) {
        return p1.id < p2.id;
        });

    int cnt = 0;


    for (int i = 0; i < ap.size(); ++i) {
        if (ap[i - 1].id == ap[i].id) {
            cnt++;
            if (cnt == 2)
            {
                out << ap[i - 1].name << " " << ap[i - 1].id << "\n";
                out << ap[i].name << " " << ap[i].id << "\n";
            }
            else if (cnt > 2)
            {
                out << ap[i].name << " " << ap[i].id << "\n";
            }
        }
        else
        {
            cnt = 1;
        }
    }

    cout << "����Ϸ�" << "\n";


    //unordered_map<size_t, int >idCount;  //id�� �ڷ��� size_t

    //for (const Player& player : ap) {

    //   idCount[player.id]++;
    //   if (idCount[player.id] > 1) {
    //      out << player.name << " " << player.id << endl;
    //   }
    //}



    //4�� p�� �о�� �޸𸮸� char ������������ �����϶�.

    //vector<Player> players;
    //string name;
    //size_t id;
    //while (in >> name >> id) {
    //   Player player;
    //   player.name = name;
    //   player.id = id;
    //   players.push_back(player);
    //}

    //sort(players.begin(), players.end());



    //int count = count_if(players.begin(), players.end(), [](const Player& p) {
    //   return std::count(p.name.begin(), p.name.end(), 'a') >= 10;
    //   });

    //std::cout << "'a'�� 10���� �̻��� Player�� ����: " << count << std::endl;




    //5�� id�� �Է¹޾� �����ϴ� id��� ���� ������ �� ���� ȭ�� ����϶�.

    while (1)
    {
        size_t idcheck;
        cout << "id�� �Է¹޽��ϴ�." << "\n";
        cin >> idcheck;

        sort(ap.begin(), ap.end(), compareById);
        for (int i = 0; i < ap.size(); ++i)
        {
            if (idcheck == ap[i].id)
            {
                cout << "����" << "\n";
                cout << "===============================================================" << "\n";
                cout << ap[i - 1] << "\n";
                cout << "===============================================================" << "\n";
                cout << ap[i] << "\n";
                cout << "===============================================================" << "\n";
                cout << ap[i + 1] << "\n";
            }
        }



    }
}
