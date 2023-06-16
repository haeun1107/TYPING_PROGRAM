#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <filesystem>
#include "Windows.h"
using namespace std;

class Typing {
    string id; // 회원 닉네임
    double totalWord, totalLine, totalLong, totalGame1, totalGame2; // 파일에 있는 총 단어(문장) 개수
    double completed, correct, duration; // 입력한 단어(문장) 개수, 맞은 단어(문장) 개수, 경과 시간
    double score, lank; // 점수, 순위
    double process, wrong, accuracy, trans_duration; // 진행도, 오타수, 정확도, 비율에 맞게 조정된 경과 시간
    public:
        Typing(); // 생성자
        void setId(string id); // 닉네임 저장
        void addData(string data, string filename); // 단어/문장 데이터 추가
        void modData(string origin, string data, string filename); // 단어/문장 데이터 수정
        void delData(string data, string filename); // 단어/문장 데이터 삭제
        void removeFile(string id); // 회원 정보 삭제
        void removeScore(); // 점수 기록 삭제
        void countWordLine(string word, string line, string longline,
                            string game1, string game2); // 파일에 있는 전체 단어/문장 개수 카운팅
        void wordTest(); // 낱말 연습
        void shortTest(); // 짧은글 연습
        void longTest();  // 긴글 연습
        void showRecord(string idtxt); // 회원 정보 조회
        void reverseGame(); // 거꾸로 읽기 게임
        void guessWord(); // 단어 만들기 게임
        void printResult(string wordORline); // 연습/게임 기록 출력, 순위 계산, 파일에 게임 기록 저장
        void textcolor(int foreground); // 글자색 변경 
};

Typing::Typing() {
    // 멤버 변수 초기화
    this->totalWord = 0;
    this->totalLine = 0;
    this->totalLong = 0;
    this->totalGame1 = 0;
    this->totalGame2 = 0;
    this->completed = 0;
    this->correct = 0;
    this->duration = 0;
    this->score = 0;
    this->lank = 0;
    this->process = 0;
    this->wrong = 0;
    this->accuracy = 0;
    this->trans_duration = 0;
}

void Typing::setId(string id) {
    this->id = id;
}

// 단어/문장 데이터 추가
void Typing::addData(string data, string filename) {
    ofstream ioFile(filename, ios::app); // 기존의 파일 뒤에 새로운 내용 작성 모드로 파일 열기
    if (filename == "word.txt") { // 단어 파일이라면
        ioFile << data << " "; // 파일에 단어와 공백 작성
    }
    else if (filename == "sentence.txt") { // 문장 파일이라면
        ioFile << data << "\n"; // 파일에 문장과 줄바꿈 작성
    }
    ioFile.close(); // 파일 닫기
}

// 단어/문장 데이터 수정
void Typing::modData(string origin, string data, string filename) {
    ifstream inputFile(filename); // 파일 읽기 모드
    if (!inputFile.is_open()) { // 파일이 열리지 않는다면
        cout << "Failed to open the file." << endl; // 오류메시지 출력
    }
    
    string word, line;
    string result; // 단어를 수정하여 파일에 새로 작성할 내용
    if (filename == "word.txt") { // 단어 파일이라면
        while(inputFile >> word) { // 한 단어씩 읽어오기
            if (word != origin) result += word + " "; // 수정할 단어가 아니라면 result에 덧붙임
            else result += data + " "; // 수정할 단어가 발견되면 수정 후 result에 덧붙임
        }
    }
    else if (filename == "sentence.txt") { // 문장 파일이라면
        while(getline(inputFile, line)) { // 한 줄씩 읽어오기
            if (line != origin) result += line + "\n"; // 수정할 문장이 아니라면 result에 덧붙임
            else result += data + "\n"; // 수정할 문장이 발견되면 수정 후 result에 덧붙임
        }
    }
    inputFile.close(); // 파일 닫기

    ofstream outputFile(filename); // 파일 쓰기 모드
    outputFile << result; // 수정하고 재작성한 내용을 파일에 작성
    outputFile.close(); // 파일 닫기
}

// 단어/문장 데이터 삭제
void Typing::delData(string data, string filename) {
    ifstream inputFile(filename); // 파일 읽기 모드
    if (!inputFile.is_open()) { // 파일이 열리지 않는다면
        cout << "Failed to open the file." << endl; // 오류메시지 출력
    }
    
    string word, line;
    string result;
    if (filename == "word.txt") { // 단어 파일이라면
        while(inputFile >> word) { // 한 단어씩 읽어오기
            if (word != data) result += word + " "; // 삭제할 단어가 아니라면 result에 덧붙임
        }
    }
    else if (filename == "sentence.txt") { // 문장 파일이라면
        while(getline(inputFile, line)) { // 한 줄씩 읽어오기
            if (line != data) result += line + "\n"; // 삭제할 문장이 아니라면 result에 덧붙임
        }
    }
    inputFile.close(); // 파일 닫기

    ofstream outputFile(filename); // 파일 쓰기 모드
    outputFile << result; // 삭제하고 재작성한 내용을 파일에 작성
    outputFile.close(); // 파일 닫기
}

// 회원 정보 삭제
void Typing::removeFile(string id) {
    string file = id + ".txt"; // 회원 이름으로 된 파일
    ifstream inputFile(file); // 파일 열기
    // 해당 회원이 존재하지 않는다면
    if (!inputFile.is_open()) cout << "삭제할 회원 정보가 없습니다!\n";
    else auto exist = filesystem::remove(file); // 회원의 게임 기록이 저장된 파일 삭제
}

// 점수 기록 삭제
void Typing::removeScore() {
    ofstream scorefile("score.txt"); // 파일 쓰기 모드
    scorefile.clear(); // 파일에 있는 내용 지우기
    scorefile.close(); // 파일 닫기
}


// 파일에 있는 전체 단어/문장 개수 카운팅
void Typing::countWordLine(string word, string line, string longline, string game1, string game2) {
    ifstream wordfile(word), linefile(line), longfile(longline), game1file(game1), game2file(game2); // 파일 읽기 모드
    string data;
    while (wordfile >> data) totalWord++; // 한 단어씩 읽으면서 카운팅
    while (getline(linefile, data)) totalLine++; // 한 줄씩 읽으면서 카운팅
    while (getline(longfile, data)) totalLong++; // 한 줄씩 읽으면서 카운팅
    while (getline(game1file, data)) totalGame1++; // 한 줄씩 읽으면서 카운팅
    while (game2file >> data) totalGame2++; // 한 단어씩 읽으면서 카운팅
}

// 낱말 연습
void Typing::wordTest() {
    ifstream inputFile("word.txt"); // 파일 읽기 모드
    if (!inputFile.is_open()) { // 파일이 열리지 않는다면 
        cout << "Failed to open the file." << endl; // 오류 메시지 출력
    }

    // 시간 측정
    time_t start, finish;
    start = time(NULL);

    // 새로운 연습이 시작되었으므로 입력한 단어 개수, 맞은 단어 개수 초기화
    completed = 0;
    correct = 0;
    string word;
    string myAnswer;
    while (inputFile >> word) { // 한 단어씩 읽어오기
        cout << "\n" << word << endl;
        cout << "-> ";
        cin >> myAnswer; // 단어 따라 입력
        completed++; // 입력한 단어 개수 1증가
        if (word == myAnswer) correct++; // 단어가 일치하다면 맞은 단어 개수 1증가
        else if (myAnswer == "q") { // 'q'를 입력하면
            completed--; // 단어를 입력했다고 보지 않음
            break; // 연습 종료
        }
    }
    inputFile.close(); // 파일 닫기

    finish = time(NULL);
    duration = (double)(finish - start); // 경과 시간 게산

    printResult("word"); // 연습 결과 출력
}

// 짧은글 연습
void Typing::shortTest() {
    ifstream inputFile("sentence.txt"); // 파일 읽기 모드
    if (!inputFile.is_open()) { // 파일이 열리지 않는다면 
        cout << "Failed to open the file." << endl; // 오류 메시지 출력
    }

    // 시간 측정
    time_t start, finish;
    start = time(NULL);

    // 새로운 연습이 시작되었으므로 입력한 문장 개수, 맞은 문장 개수 초기화
    completed = 0;
    correct = 0;
    string line;
    string myAnswer;
    while (getline(inputFile, line)) { // 한 줄씩 읽어오기
        textcolor(YELLOW);
        cout << "\n" << line << endl; 
        textcolor(WHITE);
        cout << "-> ";
        if (completed == 0) cin.ignore(); // 처음 한번만 입력 버퍼 비우기
        getline(cin, myAnswer); // 문장 따라 입력
        completed++; // 입력한 문장 개수 1증가

        if (line == myAnswer) correct++; // 문장이 일치하다면 맞은 문장 개수 1증가
        else if (myAnswer == "q") { // 'q'를 입력하면
            completed--; // 문장을 입력했다고 보지 않음
            break; // 연습 종료
        }
    }
    inputFile.close(); // 파일 닫기

    finish = time(NULL);
    duration = (double)(finish - start); // 경과 시간 계산

    printResult("line"); // 연습 결과 출력
}

// 긴글 연습
void Typing::longTest() {
    ifstream inputFile("longscript.txt"); // 파일 읽기 모드
    if (!inputFile.is_open()) { // 파일이 열리지 않는다면 
        cout << "Failed to open the file." << endl; // 오류 메시지 출력
    }

    // 시간 측정
    time_t start, finish;
    start = time(NULL);

    // 새로운 연습이 시작되었으므로 입력한 문장 개수, 맞은 문장 개수 초기화
    completed = 0;
    correct = 0;
    string line;
    string myAnswer;
    while (getline(inputFile, line)) { // 한 줄씩 읽어오기
        textcolor(YELLOW);
        cout << "\n" << line << endl;
        textcolor(WHITE);
        cout << "-> ";
        if (completed == 0) cin.ignore(); // 처음 한번만 입력 버퍼 비우기
        getline(cin, myAnswer); // 문장 따라 입력
        completed++; // 입력한 문장 개수 1증가

        if (line == myAnswer) correct++; // 문장이 일치하다면 맞은 문장 개수 1증가
        else if (myAnswer == "q") { // 'q'를 입력하면
            completed--; // 문장을 입력했다고 보지 않음
            break; // 연습 종료
        }
    }
    inputFile.close(); // 파일 닫기

    finish = time(NULL);
    duration = (double)(finish - start); // 경과 시간 계산
    
    printResult("long"); // 연습 결과 출력
}

// 회원 정보 조회
void Typing::showRecord(string idtxt) {
    ifstream inputFile(idtxt); // 파일 읽기 모드
    if (!inputFile.is_open()) { // 회원 이름으로 된 파일이 없다면 (회원이 게임을 한 기록이 없다면)
        textcolor(RED);
        cout << "No game record!!" << endl; // 오류 메시지 출력
        textcolor(WHITE);
    }

    cout << endl;
    string line;
    textcolor(RED);
    while (getline(inputFile, line)) { // 한 줄씩 읽어오기
        cout << line << endl;
    }
    textcolor(WHITE);
    inputFile.close(); // 파일 닫기
}

// 거꾸로 읽기 게임
void Typing::reverseGame() {
    ifstream inputFile("English_sentence.txt"); // 파일 읽기 모드
    if (!inputFile.is_open()) { // 파일이 열리지 않는다면 
        cout << "Failed to open the file." << endl; // 오류 메시지 출력
    }

    // 시간 측정
    time_t start, finish;
    start = time(NULL);

    // 새로운 게임이 시작되었으므로 입력한 문장 개수, 맞은 문장 개수 초기화
    completed = 0;
    correct = 0;
    string line;
    string myAnswer;
    while (getline(inputFile, line)) { // 한 줄씩 읽어오기
        string origin = line; // 원본 문장을 origin에 저장
        istringstream iss(line); // 문자열 읽기 모드
        string word;
        cout << endl;

        while (iss >> word) { // 문장에 있는 단어 읽어오기
            reverse(word.begin(), word.end()); // 단어를 거꾸로 뒤집기
            textcolor(YELLOW);
            cout << word << " ";
        }
        
        textcolor(WHITE);
        cout << "\n-> ";
        if (completed == 0) cin.ignore(); // 처음 한번만 입력 버퍼 비우기
        getline(cin, myAnswer); // 거꾸로 뒤집어진 문장을 원래 문장으로 바꾸어 입력
        completed++; // 입력한 문장 개수 1증가

        if (origin == myAnswer) correct++; // 원래 문장과 일치하다면 맞은 문장 개수 1증가
        else if (myAnswer == "q") { // 'q'를 입력하면
            completed--; // 문장을 입력했다고 보지 않음
            break; // 연습 종료
        }
    }
    inputFile.close(); // 파일 닫기
    
    finish = time(NULL);
    duration = (double)(finish - start); // 경과 시간 계산

    printResult("game1"); // 게임 결과 출력
}

// 단어 만들기 게임
void Typing::guessWord() {
    ifstream inputFile("English_word.txt"); // 파일 읽기 모드
    if (!inputFile.is_open()) { // 파일이 열리지 않는다면 
        cout << "Failed to open the file." << endl; // 오류 메시지 출력
    }

    // 시간 측정
    time_t start, finish;
    start = time(NULL);

    // 새로운 게임이 시작되었으므로 입력한 단어 개수, 맞은 단어 개수 초기화
    completed = 0;
    correct = 0;
    string myAnswer;
    string word;
    srand(time(NULL));
    while (inputFile >> word) { // 한 단어씩 읽어오기
        string origin = word; // 원본 단어를 origin에 저장
        // 단어에 있는 문자들을 랜덤으로 섞는 작업을 30번 반복하기 위한 for문
        // 난이도를 고려하여 단어의 첫 알파벳은 원본과 동일하게 두고 나머지를 섞음
        for(int i = 0; i < 3; i++) {    
            int len = word.length(); // 단어의 길이
            int randNum1 = rand() % (len-1) + 1; //0~len-1까지의 랜덤한 수 생성
            int randNum2 = rand() % (len-1) + 1; //0~len-1까지의 랜덤한 수 생성
            char temp;
            // 두 랜덤 정수 인덱스에 있는 원소들끼리 서로 바꿈
            temp = word[randNum1];
            word[randNum1] = word[randNum2];
            word[randNum2] = temp;
        }
        textcolor(YELLOW);
        cout << "\n" << word << endl;
        textcolor(WHITE);
        cout << "-> ";
        cin >> myAnswer; // 순서가 랜덤으로 섞인 단어를 원래 단어로 바꾸어 입력
        completed++; // 입력한 단어 개수 1증가
        
        if (origin == myAnswer) correct++; // 원래 단어와 일치하다면 맞은 단어 개수 1증가
        else if (myAnswer == "q") { // 'q'를 입력하면
            completed--; // 단어를 입력했다고 보지 않음
            break; // 연습 종료
        }
    }
    inputFile.close(); // 파일 닫기

    finish = time(NULL);
    duration = (double)(finish - start); // 경과 시간 게산

    printResult("game2"); // 게임 결과 출력
}


// 결과 출력
void Typing::printResult(string wordORline) {
    // 오타수 = 입력한 단어 개수 - 맞은 단어 개수
    // 진행도 = (입력한 단어 개수) / (전체 단어 개수) * 100
    // 정확도 = (맞은 단어 개수) / (입력한 단어 개수) * 100
    wrong = completed - correct; // 오타수 계산
    accuracy = (correct / completed) * 100; // 정확도 계산

    // 진행도 계산
    if (wordORline == "word") process = (completed / totalWord) * 100;
    else if (wordORline == "line") process = (completed / totalLine) * 100;
    else if (wordORline == "long") process = (completed / totalLong) * 100;
    else if (wordORline == "game1") process = (completed / totalGame1) * 100;
    else if (wordORline == "game2") process = (completed / totalGame2) * 100;

    // 경과시간 비율에 맞게 조정
    if (duration <= 60) trans_duration = 100;
    else if (duration > 60 && duration <= 70) trans_duration = 80;
    else if (duration > 70 && duration <= 80) trans_duration = 60;
    else trans_duration = 90;

    // 진행도 20%, 정확도 50%, 경과시간 30%를 반영하여 점수 계산
    score = (process * 0.2) + (accuracy * 0.5) + (trans_duration * 0.3);

    // 게임 결과 출력
    textcolor(RED);
    cout << "\n진행도 : " << process << "%" << endl;
    cout << "오타수 : " << wrong << "개"<< endl;
    cout << "정확도 : " << accuracy << "%" << endl;
    cout << "경과 시간 : " << duration << "초" << endl;
    cout << "점수 : " << score << "점" << endl;
    textcolor(WHITE);

    // 게임 수행 시 순위 출력, 파일에 결과 기록
    if (wordORline == "game1" || wordORline == "game2") {
        ifstream inputFile("score.txt"); // 게임 결과 작성을 위해 "score.txt" 파일 열기
        lank = 1; // 순위
        string word;
        while (inputFile >> word) { // 한 단어씩 읽어오기
            if (score < stod(word)) lank++; // 회원의 점수가 다른 회원의 점수보다 작다면 lank가 1씩 밀림
        }
        textcolor(RED);
        cout << "순위 : " << lank << "위" << endl; // 순위 출력
        textcolor(WHITE);

        ofstream outputFile(id, ios::app); // 기존의 파일 뒤에 새로운 내용 작성 모드로 파일 열기
        // 파일에 게임 결과 작성
        outputFile << "진행도 " << process << "\n";
        outputFile << "오타수 " << wrong << "\n";
        outputFile << "정확도 " << accuracy << "\n";
        outputFile << "경과 시간 " << duration << "\n";
        outputFile << "점수 " << score << "\n\n";
        outputFile.close();
        // lank는 계속 바뀌므로 파일에 작성 X

        ofstream scoreFile("score.txt", ios::app); // 기존의 파일 뒤에 새로운 내용 작성 모드로 파일 열기
        scoreFile << score << " "; // 게임 점수 작성
        scoreFile.close(); // 파일 닫기
    }
}

void Typing::textcolor(int color) { 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); 
}
