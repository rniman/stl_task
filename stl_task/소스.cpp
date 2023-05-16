#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <numeric>
#include <format>
#include<algorithm>

#include<unordered_map> //3번
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

    string name; // 이름, 길이[3, 15]
    int score; // 점수
    size_t id; // 아이디, 겹치는 아이디 있을 수 있음
    size_t num; // free store에 확보한 바이트 수
    char* p; // free store에 확보한 메모리의 시작번지abab

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
        os << "이름:" << format("{:25}", players.name) << ", 아이디:  " << players.id <<
            ",점수: " << players.score << ", 자원수:" << players.num << "\n"; 
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
    ifstream in{ "2023 STL 과제 파일",ios::binary };
    if (!in)
    {
        cout << "파일 열기 실패";
        return 1;
    }

    //파일 배열에 저장
    for (int i = 0; i < player_c; ++i)
    {
        in.read((char*)&ap[i], sizeof(Player));
        ap[i].p = nullptr;
        ap[i].p = new char[ap[i].num];
        in.read(ap[i].p, ap[i].num);

    }



    ////   전체 출력 코드
    //for (const Player& play : ap)
    //{
    //   cout << play;
    //   cout << "저장된 글자:";
    //   for (int i = 0; i < play.num; ++i)
    //   {
    //      cout << play.p[i];
    //   }
    //   cout << '\n' ;
    //}
    //


    //1번
    cout << ap[player_c - 1];
    cout << "저장된 글자:";
    for (int i = 0; i < ap[player_c - 1].num; ++i) {
        cout << ap[player_c - 1].p[i];
    }
    cout << "\n";

    cout << "===========================================================" << "\n";


    //2번
    int max_score = numeric_limits<int>::min(); //int최솟값
    string max_player = ""; //가장 높은 점수를 받은 player

    long long sum = 0;

    for (int i = 0; i < ap.size(); ++i) {
        if (ap[i].score > max_score)
        {
            max_score = ap[i].score;
            max_player = ap[i].name;
        }
        sum += ap[i].score;
    }

    cout << "점수가 가장 큰 player:" << max_player << endl;
    cout << "평균" << sum / player_c << endl;


    //3번
    ofstream out{ "같은아이디.txt" };

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

    cout << "쓰기완료" << "\n";


    //unordered_map<size_t, int >idCount;  //id의 자료형 size_t

    //for (const Player& player : ap) {

    //   idCount[player.id]++;
    //   if (idCount[player.id] > 1) {
    //      out << player.name << " " << player.id << endl;
    //   }
    //}



    //4번 p에 읽어온 메모리를 char 오름차순으로 정렬하라.

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

    //std::cout << "'a'가 10글자 이상인 Player의 개수: " << count << std::endl;




    //5번 id를 입력받아 존재하는 id라면 다음 내용을 한 번에 화면 출력하라.

    while (1)
    {
        size_t idcheck;
        cout << "id를 입력받습니다." << "\n";
        cin >> idcheck;

        sort(ap.begin(), ap.end(), compareById);
        for (int i = 0; i < ap.size(); ++i)
        {
            if (idcheck == ap[i].id)
            {
                cout << "정렬" << "\n";
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
