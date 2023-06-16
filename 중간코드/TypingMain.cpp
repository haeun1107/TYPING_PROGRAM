#include <iostream>
#include "Typing.h"
using namespace std;

int main(void) {
    Typing typing;
    cout << "******** 타자연습 프로그램을 시작합니다 ********" << endl;
    cout << "관리자(1) / 사용자(2) 선택하세요 : ";
    int usermanager;
    cin >> usermanager;

    // 관리자 권한
    if (usermanager == 1) { 
        cout << "비밀번호를 입력하세요 : ";
        int password;
        cin >> password;
        while (true) {
            if (password == 1014) {
                cout << "로그인 성공!" << endl;
                break;
            }
            else {
                cout << "비밀번호가 틀렸습니다. 다시 입력해주세요 : ";
                cin >> password;
            }
        }
        cout << "\n******************************" << endl;
        cout << "1. 단어 데이터 추가" << endl;
        cout << "2. 단어 데이터 수정" << endl;
        cout << "3. 단어 데이터 삭제" << endl;
        cout << "4. 문장 데이터 추가" << endl;
        cout << "5. 문장 데이터 수정" << endl;
        cout << "6. 문장 데이터 삭제" << endl;
        cout << "7. 회원 정보 삭제" << endl;
        cout << "0. 종료" << endl;
        cout << "******************************" << endl;

        while(1) {
            cout << "\n원하는 기능을 선택하세요 : ";
            int func;
            cin >> func;
            if (func == 0) break;
            cin.ignore(); // 입력 버퍼 비우기
            
            string data;
            string origin;
            switch (func) {
                case 1:
                    cout << "추가할 단어를 입력하세요 : ";
                    getline(cin, data);
                    typing.addData(data, "word.txt");
                    break;
                case 2:
                    cout << "기존 단어와 수정할 단어를 입력하세요." << endl;
                    cout << "기존 단어 : ";
                    getline(cin, origin);
                    cout << "수정할 단어 : ";
                    getline(cin, data);
                    typing.modData(origin, data, "word.txt");
                    break;
                case 3:
                    cout << "삭제할 단어를 입력하세요 : ";
                    getline(cin, data);
                    typing.delData(data, "word.txt");
                    break;
                case 4:
                    cout << "추가할 문장을 입력하세요 : ";
                    getline(cin, data);
                    typing.addData(data, "sentence.txt");
                    break;
                case 5:
                    cout << "기존 문장과 수정할 문장를 입력하세요." << endl;
                    cout << "기존 문장 : ";
                    getline(cin, origin);
                    cout << "수정할 문장 : ";
                    getline(cin, data);
                    typing.modData(origin, data, "sentence.txt");
                    break;
                case 6:
                    cout << "삭제할 문장을 입력하세요 : ";
                    getline(cin, data);
                    typing.delData(data, "sentence.txt");
                    break;
                case 7:
                    cout << "삭제할 회원의 닉네임을 입력하세요 : ";
                    getline(cin, data);
                    typing.removeFile(data);
                default:
                    break;
                }
            }
        }

    // 사용자 권한
    else if (usermanager == 2) {
        cout << "닉네임을 입력하세요 : ";
        string id;
        cin >> id;
        string idtxt = id + ".txt";

        ifstream inputFile(idtxt);
        cout << endl;
        if (!inputFile.is_open()) {
            cout << "신규 회원이시네요. 반갑습니다!\n";
        }
        else cout << id << "회원님, 반갑습니다!\n";

        cout << "\n******************************" << endl;
        cout << "1. 낱말 연습" << endl;
        cout << "2. 짧은글 연습" << endl;
        cout << "3. 긴글 연습" << endl;
        cout << "4. 게임 결과 확인" << endl;
        cout << "5. 거꾸로 읽기 게임 (난이도 하)" << endl;
        cout << "6. 단어 맞추기 게임 (난이도 상)" << endl;
        cout << "0. 종료" << endl;
        cout << "******************************" << endl;

        typing.countWordLine("word.txt", "sentence.txt", "longscript.txt", 
                                "English_sentence.txt", "English_word.txt");

        while(1) {
            cout << "\n원하는 기능을 선택하세요 : ";
            int func;
            cin >> func;
            if (func == 0) break;

            switch (func) {
                case 1:
                    cout << "\n***** 낱말 연습을 시작합니다! *****" << endl;
                    typing.wordTest();
                    break;
                case 2:
                    cout << "\n**** 짧은글 연습을 시작합니다! *****" << endl;
                    typing.shortTest();
                    break;
                case 3:
                    cout << "\n***** 긴글 연습을 시작합니다! *****" << endl;
                    typing.longTest();
                    break;
                case 4:
                    cout << "\n***** 게임 결과를 조회합니다! *****" << endl;
                    typing.showRecord(idtxt);
                    break;
                case 5:
                    cout << "\n***** 거꾸로 읽기 게임을 시작합니다! *****" << endl;
                    typing.reverseGame();
                    typing.writeResult(idtxt);
                    break;
                case 6:
                    cout << "\n***** 단어 맞추기 게임을 시작합니다! *****" << endl;
                    typing.guessWord();
                    typing.writeResult(idtxt);
                    break;
                default:
                    break;
                }
            }

    }
    else cout << "접근할 수 없습니다." << endl;
}