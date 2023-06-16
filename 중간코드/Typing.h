#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <filesystem>
using namespace std;
class Typing {
    double totalWord, totalLine, totalLong, totalGame1, totalGame2;
    double now, correct, duration;
    double score, lank;
    double process, wrong, accuracy, elapsed;
    public:
        Typing();
        void addData(string data, string filename); // 단어/문장 데이터 추가
        void modData(string origin, string data, string filename); // 단어/문장 데이터 수정
        void delData(string data, string filename); // 단어/문장 데이터 삭제
        void removeFile(string id); // 회원 정보 삭제
        void countWordLine(string word, string line, string longline,
                            string game1, string game2); // 파일에 있는 전체 단어/문장 개수 카운팅
        void wordTest(); // 낱말 연습
        void shortTest(); // 짧은글 연습
        void longTest();  // 긴글 연습
        void reverseGame(); // 거꾸로 읽기 게임
        void guessWord(); // 단어 만들기 게임
        void writeResult(string idtxt); // 게임 결과 기록 
        void printResult(string wordORline); // 결과 출력
        void showRecord(string idtxt); // 회원 정보 조회
};

Typing::Typing() {
    totalWord = 0;
    totalLine = 0;
    totalLong = 0;
    totalGame1 = 0;
    totalGame2 = 0;
    now = 0;
    correct = 0;
    duration = 0;
    score = 0;
    lank = 0;
    process = 0;
    wrong = 0;
    accuracy = 0;
    elapsed = 0;
}

void Typing::addData(string data, string filename) {
    ofstream ioFile(filename, ios::app);
    if (filename == "word.txt") {
        ioFile << data << " ";
    }
    else if (filename == "sentence.txt") {
        ioFile << data << "\n";
    }
    ioFile.close();
}

void Typing::modData(string origin, string data, string filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Failed to open the file." << endl;
    }
    
    string word, line;
    string result;
    if (filename == "word.txt") {
        while(inputFile >> word) {
            if (word != origin) result += word + " ";
            else result += data + " ";
        }
    }
    else if (filename == "sentence.txt") {
        while(getline(inputFile, line)) {
            if (line != origin) result += line + "\n";
            else result += data + "\n";
        }
    }
    inputFile.close();

    ofstream outputFile(filename);
    outputFile << result;
    outputFile.close();
}

void Typing::delData(string data, string filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Failed to open the file." << endl;
    }
    
    string word, line;
    string result;
    if (filename == "word.txt") {
        while(inputFile >> word) {
            if (word != data) result += word + " ";
        }
    }
    else if (filename == "sentence.txt") {
        while(getline(inputFile, line)) {
            if (line != data) result += line + "\n";
        }
    }
    inputFile.close();

    ofstream outputFile(filename);
    outputFile << result;
    outputFile.close();
}

void Typing::removeFile(string id) {
    string file = id + ".txt";
    auto exist = filesystem::remove(file);
}

void Typing::countWordLine(string word, string line, string longline, string game1, string game2) {
    ifstream wordfile(word), linefile(line), longfile(longline), game1file(game1), game2file(game2);
    string data;
    while (wordfile >> data) totalWord++;
    while (getline(linefile, data)) totalLine++;
    while (getline(longfile, data)) totalLong++;
    while (getline(game1file, data)) totalGame1++;
    while (game2file >> data) totalGame2++;
}

void Typing::wordTest() {
    time_t start, finish;
    start = time(NULL);

    ifstream inputFile("word.txt");
    if (!inputFile.is_open()) {
        cout << "Failed to open the file." << endl;
    }

    now = 0;
    correct = 0;
    string word;
    string myans;
    while (inputFile >> word) {
        now++;
        cout << "\n" << word << endl;
        cout << "-> ";
        cin >> myans;
        if (word == myans) correct++;
        else if (myans == "q") {
            now--;
            break;
        }
    }
    inputFile.close();

    finish = time(NULL);
    duration = (double)(finish - start);

    printResult("word");
}

void Typing::shortTest() {
    time_t start, finish;
    start = time(NULL);

    ifstream inputFile("sentence.txt");
    if (!inputFile.is_open()) {
        cout << "Failed to open the file." << endl;
    }

    now = 0;
    correct = 0;
    string line;
    string myans;
    while (getline(inputFile, line)) {
        now++;
        cout << "\n" << line << endl;
        cout << "-> ";
        if (now == 1) cin.ignore(); // 처음 한번만 입력 버퍼 비우기
        getline(cin, myans);

        if (line == myans) correct++;
        else if (myans == "q") {
            now--;
            break;
        }
    }
    inputFile.close();

    finish = time(NULL);
    duration = (double)(finish - start);

    printResult("line");
}

void Typing::longTest() {
    time_t start, finish;
    start = time(NULL);

    ifstream inputFile("longscript.txt");
    if (!inputFile.is_open()) {
        cout << "Failed to open the file." << endl;
    }

    now = 0;
    correct = 0;
    string line;
    string myans;
    while (getline(inputFile, line)) {
        now++;
        cout << "\n" << line << endl;
        cout << "-> ";
        if (now == 1) cin.ignore(); // 처음 한번만 입력 버퍼 비우기
        getline(cin, myans);

        if (line == myans) correct++;
        else if (myans == "q") {
            now--;
            break;
        }
    }
    inputFile.close();

    finish = time(NULL);
    duration = (double)(finish - start);
    
    printResult("long");
}

void Typing::reverseGame() {
    time_t start, finish;
    start = time(NULL);
    
    ifstream inputFile("English_sentence.txt");
    if (!inputFile.is_open()) {
        cout << "Failed to open the file." << endl;
    }

    now = 0;
    correct = 0;
    string line;
    string myans;
    while (getline(inputFile, line)) {
        string origin = line;
        istringstream iss(line);
        string word;
        cout << endl;
        while (iss >> word) {
            reverse(word.begin(), word.end());
            cout << word << " ";
        }

        now++;
        cout << endl;
        cout << "-> ";
        if (now == 1) cin.ignore(); // 처음 한번만 입력 버퍼 비우기

        getline(cin, myans);
        if (origin == myans) correct++;
        else if (myans == "q") {
            now--;
            break;
        }
    }
    inputFile.close();
    
    finish = time(NULL);
    duration = (double)(finish - start);

    printResult("game1");
}

void Typing::guessWord() {
    time_t start, finish;
    start = time(NULL);

    ifstream inputFile("English_word.txt");
    if (!inputFile.is_open()) {
        cout << "Failed to open the file." << endl;
    }

    now = 0;
    correct = 0;
    string myans;
    string word;
    srand(time(NULL));
    while (inputFile >> word) {
        string origin = word;
        for(int i = 0; i < 3; i++) {    // 섞는작업을 30번 반복하기 위한 for문
            int len = word.length();
            int randNum1 = rand() % (len-1) + 1;    //0~len-1까지의 랜덤한 수를 발생한다.
            int randNum2 = rand() % (len-1) + 1;
            char temp;
            temp = word[randNum1];
            word[randNum1] = word[randNum2];
            word[randNum2] = temp;
        }
        cout << word << " ";

        now++;
        cout << endl;
        cout << "-> ";
        if (now == 1) cin.ignore(); // 처음 한번만 입력 버퍼 비우기

        getline(cin, myans);
        cout << endl;
        if (origin == myans) correct++;
        else if (myans == "q") {
            now--;
            break;
        }
    }
    inputFile.close();

    finish = time(NULL);
    duration = (double)(finish - start);

    printResult("game2");
}

void Typing::writeResult(string idtxt) {
    ofstream outputFile(idtxt, ios::app);

    outputFile << "진행도 " << process << "\n";
    outputFile << "오타수 " << wrong << "\n";
    outputFile << "정확도 " << accuracy << "\n";
    outputFile << "경과 시간 " << duration << "\n";
    outputFile << "점수 " << score << "\n\n";
    outputFile.close();

    ofstream scoreFile("score.txt", ios::app);
    scoreFile << score << " ";
    scoreFile.close();
}

void Typing::printResult(string wordORline) {
    wrong = now - correct;
    accuracy = (correct / now) * 100;
    if (wordORline == "word") process = (now / totalWord) * 100;
    else if (wordORline == "line") process = (now / totalLine) * 100;
    else if (wordORline == "long") process = (now / totalLong) * 100;
    else if (wordORline == "game1") process = (now / totalGame1) * 100;
    else if (wordORline == "game2") process = (now / totalGame2) * 100;

    if (duration <= 60) elapsed = 100;
    else if (duration > 60 && duration <= 70) elapsed = 80;
    else if (duration > 70 && duration <= 80) elapsed = 60;
    else elapsed = 90;

    score = (process * 0.2) + (accuracy * 0.5) + (elapsed * 0.3);
    cout << "\n진행도 : " << process << "%" << endl;
    cout << "오타수 : " << wrong << "개"<< endl;
    cout << "정확도 : " << accuracy << "%" << endl;
    cout << "경과 시간 : " << duration << "초" << endl;
    cout << "점수 : " << score << "점" << endl;

    if (wordORline == "game1" || wordORline == "game2") {
        ifstream inputFile("score.txt");
        lank = 1;
        string word;
        while (inputFile >> word) {
            if (score < stod(word)) lank++;
        }
        cout << "순위 : " << lank << "위" << endl;
    }
}

void Typing::showRecord(string idtxt) {
    ifstream inputFile(idtxt);

    cout << endl;
    string line;
    while (getline(inputFile, line)) {
        cout << line << endl;
    }
    inputFile.close();
}

