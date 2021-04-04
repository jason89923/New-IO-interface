#ifndef UI_Definition
#define UI_Definition

#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <windows.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
class BasicUI {
   private:
    const string bold = "\033[1m";

    const string off = "\033[0m";

    const string underline = "\033[4m";

    int choice;  // 記憶上次選項
    string name[16];
    int width;  // 控制UI寬度
    int titleColor;
    int optionColor;
    int choiceColor;

    struct Instruction {
        string str;
        COORD position;
    };  // struct Instruction

    struct TitleType {
        string str;
        bool bold;
    };

    vector<TitleType> title;
    vector<Instruction> instructions;

    Instruction Create_instructions(string str);

    static void gotoxy(int xpos, int ypos);

    static void gotoxy(COORD loc);

    static COORD GetConsoleCursorPosition();

    void SetKeyBoard(int num);

    void CoutMiddle(string str);

    void CoutMiddleTitle(string str);

    void Set_choice_position(int choice, int previous_choice);

    static void Set_choice_position(COORD optionlocation[], int choice, int previous_choice);

    static bool FileExist(string str);

    static void PrintFileStatus(string str, int Y);

    void Instructions();

    void RemoveElement(string& str, const char ch);

    void Print_symbol(const char ch, const int amount);

    /**回傳name + add_name字串*/
    static string CreateFilename(string name, string add_name);

   protected:
    /**更改標題*/
    void SetTitle(string title, bool bold);
    /**加入標題(行)*/
    void AddTitle(string line, bool bold);
    /**更改UI寬度*/
    void SetWidth(int width);
    /**一次添加一個選項*/
    void AddOptions(string option);
    /**defult color 224*/
    void SetTitleColor(int color);
    /**defult color 240*/
    void SetOptionColor(int color);
    /**defult color 176*/
    void SetChoiceColor(int color);

    void ClearOptions();

    void ClearTitle();

    void EraseOptions(const int index);

   public:
    /**讀檔選單，回傳輸入的字串(含)*/
    static string Read_input_filename();
    /**設定顏色，以RGB值表示*/
    static void SetColor(int color);
    /**主選單，回傳選中的選項(由上而下從0開始)*/
    int IO();

    BasicUI();
};  // class BasicUI

#include "UI_implement.h"
#endif