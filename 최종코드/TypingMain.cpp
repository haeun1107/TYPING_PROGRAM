#include <iostream>
#include "Typing.h"
using namespace std;

int main(void) {
    Typing typing;
    typing.textcolor(RED);
    cout << "\n******** 타자연습 프로그램을 시작합니다 ********\n" << endl;
    typing.textcolor(WHITE);
    cout << "관리자(1) / 사용자(2) 선택하세요 : ";
    int usermanager; 
    cin >> usermanager; // 관리자 or 사용자 선택

    // 관리자 권한으로 들어올 경우
    if (usermanager == 1) { 
        cout << "비밀번호를 입력하세요 : ";
        int password; // 비밀번호
        cin >> password;
        typing.textcolor(LIGHTMAGENTA);
        while (true) {
            if (password == 1014) { // 입력한 값이 비밀번호와 일치한다면
                cout << "\n로그인 성공!" << endl; // 로그인 성공 메시지 출력
                break;
            }
            else { // 비밀번호가 틀리다면
                cout << "비밀번호가 틀렸습니다. 다시 입력해주세요 : "; // 오류 메시지 출력
                cin >> password; // 다시 입력 받음
            }
        }
        
        typing.textcolor(RED);
        // 기능 메뉴
        cout << "\n******************************" << endl;
        cout << "1. 단어 데이터 추가" << endl;
        cout << "2. 단어 데이터 수정" << endl;
        cout << "3. 단어 데이터 삭제" << endl;
        cout << "4. 문장 데이터 추가" << endl;
        cout << "5. 문장 데이터 수정" << endl;
        cout << "6. 문장 데이터 삭제" << endl;
        cout << "7. 회원 정보 삭제" << endl;
        cout << "8. 점수 기록 삭제" << endl;
        cout << "0. 종료" << endl;
        cout << "******************************" << endl;

        typing.textcolor(WHITE);
        while(1) {
            cout << "\n원하는 기능을 선택하세요 : ";
            int func;
            cin >> func; // 번호 입력
            if (func == 0) break; // 0 입력 시 프로그램 종료
            cin.ignore(); // 입력 버퍼 비우기
            
            string data; // 추가, 삭제, 수정 후 단어/문장
            string origin; // 수정 전 단어/문장
            switch (func) {
                case 1:
                    cout << "추가할 단어를 입력하세요 : ";
                    getline(cin, data); // 추가할 단어 입력
                    typing.addData(data, "word.txt"); // "word.txt" 파일에 data 추가
                    break;
                case 2:
                    cout << "기존 단어와 수정할 단어를 입력하세요." << endl;
                    cout << "기존 단어 : ";
                    getline(cin, origin); // 수정 전 단어
                    cout << "수정할 단어 : ";
                    getline(cin, data); // 수정 후 단어
                    typing.modData(origin, data, "word.txt"); // "word.txt" 파일에 있는 단어 수정
                    break;
                case 3:
                    cout << "삭제할 단어를 입력하세요 : ";
                    getline(cin, data); // 삭제할 단어 입력
                    typing.delData(data, "word.txt"); // "word.txt" 파일에 있는 단어 삭제
                    break;
                case 4:
                    cout << "추가할 문장을 입력하세요 : ";
                    getline(cin, data); // 추가할 문장 입력
                    typing.addData(data, "sentence.txt");  // "sentence.txt" 파일에 data 추가
                    break;
                case 5:
                    cout << "기존 문장과 수정할 문장를 입력하세요." << endl;
                    cout << "기존 문장 : ";
                    getline(cin, origin); // 수정 전 문장
                    cout << "수정할 문장 : ";
                    getline(cin, data); // 수정 후 문장
                    typing.modData(origin, data, "sentence.txt"); // "sentence.txt" 파일에 있는 문장 수정
                    break;
                case 6:
                    cout << "삭제할 문장을 입력하세요 : ";
                    getline(cin, data); // 삭제할 문장 입력
                    typing.delData(data, "sentence.txt"); // "sentence.txt" 파일에 있는 문장 삭제
                    break;
                case 7:
                    cout << "삭제할 회원의 닉네임을 입력하세요 : ";
                    getline(cin, data); // 삭제할 회원 닉네임 입력
                    typing.removeFile(data); // 회원 이름으로 된 파일 삭제
                    break;
                case 8:
                    cout << "score.txt에 저장된 점수 기록들을 삭제합니다." << endl;
                    typing.removeScore(); // 점수 기록 삭제
                    break;
                default:
                    break;
                }
            }
        }

    // 사용자 권한으로 들어올 경우
    else if (usermanager == 2) {
        cout << "닉네임을 입력하세요 : ";
        string id;
        cin >> id; // 닉네임 입력
        string idtxt = id + ".txt"; // 회원 이름으로 된 파일 이름
        typing.setId(idtxt);

        ifstream inputFile(idtxt); // 파일 열기
        cout << endl;
        typing.textcolor(LIGHTMAGENTA);
        if (!inputFile.is_open()) cout << "신규 회원이시네요. 반갑습니다!\n"; // 파일이 없다면 신규 회원으로 등록
        else cout << id << "회원님, 반갑습니다!\n"; // 파일이 열린다면 기존 회원

        typing.textcolor(RED);
        cout << "\n******************************" << endl;
        cout << "1. 낱말 연습" << endl;
        cout << "2. 짧은글 연습" << endl;
        cout << "3. 긴글 연습" << endl;
        cout << "4. 게임 결과 확인" << endl;
        cout << "5. 거꾸로 읽기 게임 (난이도 하)" << endl;
        cout << "6. 단어 맞추기 게임 (난이도 상)" << endl;
        cout << "0. 종료" << endl;
        cout << "******************************" << endl;

        // 파일에 있는 총 단어/문자 개수 카운팅
        typing.countWordLine("word.txt", "sentence.txt", "longscript.txt", 
                                "English_sentence.txt", "English_word.txt");

        while(1) {
            typing.textcolor(WHITE);
            cout << "\n원하는 기능을 선택하세요 : ";
            int func;
            cin >> func; // 번호 입력
            if (func == 0) break; // 0 입력 시 프로그램 종료

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
                    typing.showRecord(idtxt); // 회원 닉네임으로 저장된 파일 열고 결과 출력
                    break;
                case 5:
                    cout << "\n***** 거꾸로 읽기 게임을 시작합니다! *****" << endl;
                    typing.reverseGame(); // 게임 후 회원 닉네임으로 저장된 파일에 결과 작성
                    break;
                case 6:
                    cout << "\n***** 단어 맞추기 게임을 시작합니다! *****" << endl;
                    typing.guessWord(); // 게임 후 회원 닉네임으로 저장된 파일에 결과 작성
                    break;
                default:
                    break;
                }
            }

    }
    else cout << "잘못 입력하셨습니다." << endl;
}