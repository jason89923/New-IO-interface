

BasicUI::Instruction BasicUI::Create_instructions(string str) {
    Instruction temp;
    temp.str = str;
    return temp;
}  // Create_instructions

void BasicUI::gotoxy(int xpos, int ypos) {
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos;
    scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
}  // gotoxy

void BasicUI::gotoxy(COORD loc) {
    COORD scrn = loc;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOuput, scrn);
}  // gotoxy

COORD BasicUI::GetConsoleCursorPosition() {
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi)) {
        return cbsi.dwCursorPosition;
    }  // if
    else {
        // The function failed. Call GetLastError() for details.
        COORD invalid = {0, 0};
        return invalid;
    }  // else
}  // GetConsoleCursorPosition

void BasicUI::SetKeyBoard(int num) {
    HWND hCon = GetConsoleWindow();
    DWORD dwNewKeybLayout = num;  // Layout must be already loaded!
    PostMessage(hCon, WM_INPUTLANGCHANGEREQUEST, 0, (LPARAM)dwNewKeybLayout);
    PostMessage(hCon, WM_INPUTLANGCHANGE, 0, (LPARAM)dwNewKeybLayout);
}  // SetKeyBoard

void BasicUI::CoutMiddle(string str) {
    cout << setw(width) << right << str.substr(0, str.size() / 2);
    cout << setw(width) << left << str.substr(str.size() / 2, str.size() / 2 + 1);
}  // CoutMiddle
void BasicUI::CoutMiddleTitle(string str) {
    cout << underline << setw(width) << right << str.substr(0, str.size() / 2);
    cout << setw(width) << left << str.substr(str.size() / 2, str.size() / 2 + 1) << off;
}  // CoutMiddle

void BasicUI::Set_choice_position(int choice, int previous_choice) {
    gotoxy(instructions[previous_choice].position);
    SetColor(optionColor);
    CoutMiddle(instructions[previous_choice].str);
    gotoxy(instructions[choice].position);
    SetColor(choiceColor);
    string str;
    str = "< " + instructions[choice].str + " >";
    CoutMiddle(str);
    SetColor(7);
}  // Set_choice_position

void BasicUI::Set_choice_position(COORD optionlocation[], int choice, int previous_choice) {
    gotoxy(optionlocation[previous_choice]);
    int length = 0;
    if (previous_choice == 0) {
        length = 15;
        SetColor(240);
    }  // if
    else {
        length = 10;
        SetColor(176);
    }  // else

    gotoxy(0, optionlocation[previous_choice].Y);
    putchar(' ');
    gotoxy(length, optionlocation[previous_choice].Y);
    putchar(' ');
    if (choice == 0) {
        length = 15;
        SetColor(240);
    }  // if
    else {
        length = 10;
        SetColor(176);
    }  // else

    gotoxy(0, optionlocation[choice].Y);
    putchar('<');
    gotoxy(length, optionlocation[choice].Y);
    putchar('>');
    SetColor(7);
}  // Set_choice_position

bool BasicUI::FileExist(string str) {
    fstream file(str.c_str(), ios::in);
    if (file) {
        return true;
    }  // if
    else {
        return false;
    }  // else
}  // FileExist

void BasicUI::PrintFileStatus(string str, int Y) {
    str = "input" + str + ".txt";
    gotoxy(17, Y);
    SetColor(7);
    cout << "                                              ";
    if (str != "input.txt") {
        gotoxy(17, Y);
        if (FileExist(str)) {
            SetColor(159);
            cout << "File ";
            SetColor(224);
            cout << str;
            SetColor(159);
            cout << " found !";
        }  // else if
        else {
            SetColor(207);
            cout << "No such file named ";
            SetColor(224);
            cout << str;
            SetColor(207);
            cout << " !";
        }  // else if
    }      // if

    SetColor(7);
}  // PrintFileStatus

void BasicUI::Instructions() {
    cout << endl;
    if (title.empty() || instructions.empty()) {
        if (title.empty() && instructions.empty()) {
            throw "Both Title and Options did not correctly be set";
        }  // if
        else if (title.empty() && !instructions.empty()) {
            throw "Title did not correctly be set";
        }  // else if
        else if (title.empty() && !instructions.empty()) {
            throw "Options did not correctly be set";
        }  // else if
    }      // if

    for (int i = 0; i < title.size(); i++) {
        SetColor(titleColor);
        if (title[i].bold) {
            CoutMiddleTitle(title[i].str);
        }  // if
        else {
            CoutMiddle(title[i].str);
        }  // else

        SetColor(7);
        cout << endl;
    }  // for

    for (int i = 0; i < instructions.size(); i++) {
        SetColor(optionColor);
        CoutMiddle(instructions[i].str);
        SetColor(7);
        cout << endl;
    }  // for

}  // Instructions()

void BasicUI::RemoveElement(string& str, const char ch) {
    if (!str.empty()) {
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == ch) {
                str.erase(str.begin() + i);
                i--;
            }  // if
        }      // for
    }          // if
}  // RemoveElement

void BasicUI::Print_symbol(const char ch, const int amount) {
    for (int i = 0; i < amount; i++) {
        cout << ch;
    }  // for

    cout << endl;
}  // Print_symbol

string BasicUI::CreateFilename(string name, string add_name) {
    return add_name + name + ".txt";
}  // Create_input_filename

string BasicUI::Read_input_filename() {
    cout << endl;
    SetColor(240);
    cout << "  input";
    SetColor(224);
    cout << "   ";
    SetColor(240);
    cout << ".txt  ";
    SetColor(7);
    cout << endl;
    SetColor(176);
    cout << "  Go Back  ";
    SetColor(7);
    cout << endl;
    COORD position[2];
    COORD backup_position = GetConsoleCursorPosition();
    position[0].X = 1;
    position[1].X = 1;
    position[1].Y = backup_position.Y - 1;
    position[0].Y = backup_position.Y - 2;
    int previous_command = 0;
    int command = 0;
    string str;
    str.clear();
    Set_choice_position(position, command, previous_command);
    while (true) {
        previous_command = command;
        char ch = getch();
        if (ch == -32) {
            ch = getch();
            if (ch == 72) {
                command--;
                if (command < 0) {
                    command = 1;
                }  // if

                Set_choice_position(position, command, previous_command);
            }  // if
            else if (ch == 80) {
                command++;
                if (command > 1) {
                    command = 0;
                }  // if

                Set_choice_position(position, command, previous_command);
            }  // else if
        }      // if
        else if (ch >= '0' && ch <= '9') {
            if (str.length() < 3) {
                gotoxy(7 + str.length(), backup_position.Y - 2);
                SetColor(224);
                putchar(ch);
                str.push_back(ch);
                PrintFileStatus(str, backup_position.Y - 2);
                SetColor(7);
                gotoxy(7 + str.length(), backup_position.Y - 2);
            }  // if
        }      // else if
        else if (ch == 8) {
            if (str.length() > 0) {
                gotoxy(7 + str.length() - 1, backup_position.Y - 2);
                SetColor(224);
                putchar(' ');
                str.erase(str.begin() + str.length() - 1);
                PrintFileStatus(str, backup_position.Y - 2);
                SetColor(7);
                gotoxy(7 + str.length() - 1, backup_position.Y - 2);
            }  // if
        }      // else if
        else if (ch == '\r') {
            if (command == 1) {
                gotoxy(backup_position);
                return "back";
            }  // if
            else if (command == 0) {
                if (!str.empty()) {
                    gotoxy(backup_position);
                    return str;
                }  // if
            }      // else if
        }          // else if
    }              // while
}  // Read_input_filename

void BasicUI::SetColor(int color) {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}  // SetColor

int BasicUI::IO() {
    try {
        Instructions();
        COORD start = GetConsoleCursorPosition();
        COORD temp = start;
        temp.Y = temp.Y - instructions.size();
        for (int i = 0; i < instructions.size(); i++) {
            instructions[i].position.X = 0;
            instructions[i].position.Y = temp.Y;
            temp.Y++;
        }  // for

        COORD nextposition = GetConsoleCursorPosition();
        int previousChoice = choice;
        Set_choice_position(choice, previousChoice);
        while (true) {
            previousChoice = choice;
            char ch = getch();
            if (ch == -32) {
                ch = getch();
                if (ch == 72) {
                    choice--;
                    if (choice < 0) {
                        choice = instructions.size() - 1;
                    }  // if
                }      // if
                else if (ch == 80) {
                    choice++;
                    if (choice > instructions.size() - 1) {
                        choice = 0;
                    }  // if
                }      // else if
            }          // if

            else if (ch == '\r') {
                gotoxy(nextposition);
                SetColor(7);
                return choice;
            }  // else if

            Set_choice_position(choice, previousChoice);

        }  // while
    } catch (const char* str) {
        cout << "Error! " << str << endl;
        system("pause");
    }  // catch

    return -1;
}  // IO

void BasicUI::SetTitle(string title, bool bold) {
    this->title.clear();
    TitleType temp;
    temp.bold = bold;
    temp.str = title;
    this->title.push_back(temp);
}  // SetTitle

void BasicUI::AddTitle(string title, bool bold) {
    TitleType temp;
    temp.bold = bold;
    temp.str = title;
    this->title.push_back(temp);
}  // SetTitle

void BasicUI::AddOptions(string option) {
    BasicUI::instructions.push_back(BasicUI::Create_instructions(option));
}  // AddOptions

void BasicUI::SetWidth(int width) {
    this->width = width;
}  // SetWidth

BasicUI::BasicUI() {
    choice = 0;
    width = 30;
    titleColor = 224;
    optionColor = 240;
    choiceColor = 176;
    system("cls");
}  // BasicUI

void BasicUI::ClearOptions() {
    BasicUI::instructions.clear();
}  // ClearOptions

void BasicUI::ClearTitle() {
    BasicUI::title.clear();
}  // ClearOptions

void BasicUI::EraseOptions(const int index) {
    BasicUI::instructions.erase(BasicUI::instructions.begin() + index);
}  // EraseOptions

void BasicUI::SetTitleColor(int color) {
    titleColor = color;
    ;
}  // SetTitleColor

void BasicUI::SetOptionColor(int color) {
    optionColor = color;
}  // SetOptionColor

void BasicUI::SetChoiceColor(int color) {
    choiceColor = color;
}  // SetChoiceColor