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

    int choice;  // �O�ФW���ﶵ
    string name[16];
    int width;  // ����UI�e��
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

    /**�^��name + add_name�r��*/
    static string CreateFilename(string name, string add_name);

   protected:
    /**�����D*/
    void SetTitle(string title, bool bold);
    /**�[�J���D(��)*/
    void AddTitle(string line, bool bold);
    /**���UI�e��*/
    void SetWidth(int width);
    /**�@���K�[�@�ӿﶵ*/
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
    /**Ū�ɿ��A�^�ǿ�J���r��(�t)*/
    static string Read_input_filename();
    /**�]�w�C��A�HRGB�Ȫ��*/
    static void SetColor(int color);
    /**�D���A�^�ǿ襤���ﶵ(�ѤW�ӤU�q0�}�l)*/
    int IO();

    BasicUI();
};  // class BasicUI

#include "UI_implement.h"
#endif