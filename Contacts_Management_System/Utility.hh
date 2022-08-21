#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <ctime>
#include <chrono>

namespace utl
{

    const int SEARCHING = 1;
    const int UPDATING = 2;
    const int DELETING = 3;
    const int ADDING = 4;
    const int LOGIN = 5;
    const int SIGNUP = 6;
    class Utility
    {
    private:
        Utility();

    public:
        // C
        static void clearScreen() { system("cls"); }

        static void closeFile(std::fstream &file) { file.close(); }

        static void closeWindow(const std::string &name)
        {
            clearScreen();
            printTitle("Exit", 4);
            std::cout << "\n\n\n\n\n\t\t\t\t" << getLastMessage() << name;
            sleep(650);
            std::cout << "\n\n\n\t\t\t\tClosing Contacts application ";
            for (int i = 0; i < 7; ++i)
            {
                std::cout << ". ";
                sleep(500);
            }
            sleep(350);
            exit(0);
        }

        static bool confirmMessage(const std::string &message)
        {
            std::string confirm;
            std::cout << "\n\n\t\t\tDo you really want to " << message << " ? (y / n) : ";
            std::getline(std::cin, confirm);
            transform(confirm.begin(), confirm.end(), confirm.begin(), ::tolower);
            clearScreen();
            if (confirm == "yes" || confirm == "y")
                return true;
            else
                return false;
        }

        static bool copyFileToString_Delete(const std::string &filepath, std::vector<std::vector<std::string>> &filedata, const std::string &number_or_email)
        {
            std::fstream fin;
            openReadMode(filepath.c_str(), fin);
            bool op = false;
            std::vector<std::string> line;
            while (!fin.eof())
            {
                std::string row_contact, str;
                line.clear();
                std::getline(fin, row_contact);
                std::stringstream ss(row_contact, std::stringstream::in);
                while (std::getline(ss, str, ','))
                {
                    line.push_back(str);
                    str.clear();
                }
                if (line[1] != number_or_email && line[2] != number_or_email)
                {
                    if (line.size() > 0)
                        filedata.push_back(line);
                }
                else
                {
                    op = true;
                }
            }
            closeFile(fin);
            return op;
        }

        static bool copyFileToString_Update(const std::string &filepath, std::vector<std::vector<std::string>> &filedata, const std::string &number_or_email)
        {
            std::fstream fin;
            openReadMode(filepath.c_str(), fin);
            bool op = false;
            std::vector<std::string> line;
            while (!fin.eof())
            {
                line.clear();
                std::string row_contact, str;
                std::getline(fin, row_contact);
                std::stringstream ss(row_contact, std::stringstream::in);
                while (std::getline(ss, str, ','))
                {

                    line.push_back(str);
                    str.clear();
                }
                if (line[1] == number_or_email || line[2] == number_or_email)
                {
                    inputContactFile(line);
                    op = true;
                }
                if (line.size() > 0)
                    filedata.push_back(line);
            }
            closeFile(fin);
            return op;
        }

        static void copyFileToString(const std::string &filepath, std::vector<std::vector<std::string>> &filedata)
        {
            std::fstream fin;
            openReadMode(filepath.c_str(), fin);
            std::vector<std::string> line;
            while (!fin.eof())
            {
                line.clear();
                std::string row_contact, str;
                std::getline(fin, row_contact);
                std::stringstream ss(row_contact, std::stringstream::in);
                while (std::getline(ss, str, ','))
                {
                    line.push_back(str);
                    str.clear();
                }
                if (line.size() > 0)
                    filedata.push_back(line);
            }
            closeFile(fin);
        }

        static void copyStringToFile(const std::string &filepath, const std::vector<std::vector<std::string>> &filedata)
        {
            std::fstream fout;
            openWriteMode(filepath.c_str(), fout);
            int k = 0;
            for (auto i : filedata)
            {
                for (auto j : i)
                {
                    fout << j;
                    if (j != i.back())
                        fout << ',';
                }
                if (i[k].size() > 0)
                    fout << '\n';
                ++k;
            }
            closeFile(fout);
        }

        static void createFile(const std::string &filepath)
        {
            std::fstream fout(filepath.c_str(), std::fstream::out);
            fout.close();
        }

        // D
        // delte file
        static void deleteFile(const std::string &filepath) { remove(filepath.c_str()); }

        // E
        // unhide,unreadmode  files
        static void exposeFile()
        {
            system("attrib -r -s-h data.csv");
            system("attrib -r -s -h encrypted_contacts.csv");
            clearScreen();
        }

        // F
        static bool fileNotFoundMessage()
        {
            std::cout << "\n\nt\t\tThe file was not found OR the file is empty !";
            sleep(1050);
            redirectMessage("Home screen");
            return false;
        }

        // G
        // return current system time in hour
        static int getCurrentHour()
        {
            // get the current time point. Reference - http://en.cppreference.com/w/cpp/chrono/c/time
            const time_t now = time(nullptr);
            // convert it to (local) calendar time. Reference - http://en.cppreference.com/w/cpp/chrono/c/localtime
            const tm calendar_time = *localtime(std::addressof(now));
            return calendar_time.tm_hour;
        }

        // according to current time return greetings , like good morning, good night
        static std::string getGreetingMessage()
        {
            int hour = getCurrentHour();
            std::string greeting;
            if (hour >= 0 && hour < 12)
            {
                greeting = "Good Morning ! ";
            }
            else if (hour >= 12 && hour < 17)
            {
                greeting = "Good Afternoon ! ";
            }
            else if (hour >= 17 && hour < 20)
            {
                greeting = "Good Evening ! ";
            }
            else
            {
                greeting = "Welcome ! ";
            }
            return greeting;
        }

        // according to current time return greetings , like have a good day,have a  good night
        static std::string getLastMessage()
        {
            int hour = getCurrentHour();
            if (hour >= 5 && hour <= 17)
            {
                return "Have A Good Day ! ";
            }
            else
            {
                return "Have A Good Night ! ";
            }
        }

        // I
        // check file is available or not
        static bool isFileAvailable(const std::string &filepath)
        {
            std::fstream fin;
            openReadMode(filepath.c_str(), fin);
            bool available = !(!fin);
            fin.close();
            return available;
        }

        static void inputContactFile(std::vector<std::string> &line)
        {
            line.clear();
            line.resize(3);
            std::cout << "\n\n\n\t\t\tEnter user name : ";
            std::getline(std::cin, line[0]);
            std::cout << "\n\t\t\tEnter " << line[0] << "'s Phone Number : ";
            std::getline(std::cin, line[1]);
            std::cout << "\n\t\t\tEnter " << line[0] << "'s Email : ";
            std::getline(std::cin, line[2]);
        }

        // check 'system' command run on your system or not .  // system returns nonzero if command processor exists (or system can run). Otherwise returns 0.
        static bool isSystemAvailable() { return system(nullptr); }

        // L
        // print my name
        static void logo()
        {
            clearScreen();
            std::cout << std::endl
                      << "\n\n\t\t\tContacts : A Console Application\n\n\t\t\tapplication by SHIBA PRASAD SAHU\n\t\t\t";
            for (int i = 0; i < 8; ++i)
            {
                std::cout << "-----";
            }
            std::cout << std::endl;
            ;
        }

        // create a
        static void loadingBar() // 177, 219
        {
            {
                clearScreen();
                std::cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t Loading...\n"
                          << std::endl
                          << "\t\t\t\t\t";
                for (int i = 0; i < 27; ++i)
                {
                    std::cout << (char)177;
                }
                std::cout << '\r'; // carriage return, escape sequence
                std::cout << "\t\t\t\t\t";
                for (int i = 0; i < 8; ++i)
                {
                    std::cout << (char)219;
                    sleep(350);
                }
                for (int i = 0; i < 15; ++i)
                {
                    std::cout << (char)219;
                    sleep(50);
                }
                for (int i = 0; i < 4; ++i)
                {
                    std::cout << (char)219;
                    sleep(450);
                }
                sleep(800);
                if (!isSystemAvailable())
                {
                    clearScreen();
                    std::cout << "\n\n\n\n\n\n\n\n\t\t\tThis system can't have a mechanism to run this application";
                    sleep(6000);
                    closeWindow(" ");
                }
            }
        }

        // O
        static void openReadMode(const std::string &filepath, std::fstream &fin) { fin.open(filepath.c_str(), std::fstream::in); }

        static void openWriteMode(const std::string &filepath, std::fstream &fout) { fout.open(filepath.c_str(), std::fstream::out | std::fstream::app); }

        // P
        // pause the screen until a key is pressed
        static void pauseWindow() { system("pause"); }

        static void printTitle(const std::string &title, const int &repeat)
        {
            std::cout << "\n\t\t\t\t\t*";
            for (int i = 0; i < repeat; ++i)
            {
                std::cout << '-';
            }
            std::cout << "*\n\t\t\t\t\t|" << title << "|\n\t\t\t\t\t*";
            for (int i = 0; i < repeat; ++i)
            {
                std::cout << '-';
            }
            std::cout << "*";
        }

        // show messages like processing
        static void processingText(const int &param)
        {

            std::string message;
            if (param == 1)
            {
                message = "Searching";
            }
            else if (param == 2)
            {
                message = "Updating";
            }
            else if (param == 3)
            {
                message = "Deleting";
            }
            else if (param == 4)
            {
                message = "Adding";
            }
            else if (param == 5)
            {
                message = "Logging In";
            }
            else if (param == 6)
            {
                message = "Signing Up";
            }
            std::cout << "\n\n"
                      << std::endl
                      << "\t\t\t\t" << message;
            for (int i = 0; i < 6; ++i)
            {
                std::cout << ".";
                sleep(450);
            }
            std::cout << std::endl;
            clearScreen();
            sleep(250);
        }

        // hide, readmode files
        static void protectFile()
        {
            system("attrib +r +s +h data.csv");
            system("attrib +r +s +h encrypted_contacts.csv");
            clearScreen();
        }

        // R
        static bool recordNotFoundMessage(const std::string &name_number_mail)
        {
            std::cout << "\n\n\t\t\t" << name_number_mail << "'s contact information was not found in the contact files.";
            sleep(1050);
            redirectMessage("Home screen");
            return false;
        }

        static void redirectMessage(const std::string &screen)
        {
            std::cout << "\n\n\t\t\tRe-directing to " << screen;
            for (int i = 0; i < 6; ++i)
            {
                std::cout << ".";
                sleep(350);
            }
        }

        static void renameFile(const std::string &old_filename, const std::string &new_filename) { rename(old_filename.c_str(), new_filename.c_str()); }

        // S
        static void setColor(const std::string &color) { system(color.c_str()); }

        // hide or show  console t cursor.   // Reference - https://docs.microsoft.com/en-us/windows/console/setconsolecursorinfo for Console API Functions
        static void showConsoleCursor(bool showFlag)
        {
            HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_CURSOR_INFO cursorInfo;
            cursorInfo.dwSize = 1;
            GetConsoleCursorInfo(out, &cursorInfo);
            cursorInfo.bVisible = showFlag; // set the cursor visibility
            SetConsoleCursorInfo(out, &cursorInfo);
        }

        // We can use the sleep() function to suspend the execution of the current thread until the specified number of milliseconds elapses. Reference - https://www.techiedelight.com/sleep-in-cpp/ for sleep() in c++
        static void sleep(DWORD milliseconds) { Sleep(milliseconds); }

        static void sortByEmail(std::vector<std::vector<std::string>> &filedata)
        {
            sort(filedata.begin(), filedata.end(), [](auto &lhs, auto &rhs)
                 { return lhs[2] < rhs[2]; });
        }

        static void sortByName(std::vector<std::vector<std::string>> &filedata)
        {
            sort(filedata.begin(), filedata.end(), [](auto &lhs, auto &rhs)
                 { return lhs[0] < rhs[0]; });
        }

        static void sortByPhoneNo(std::vector<std::vector<std::string>> &filedata)
        {
            sort(filedata.begin(), filedata.end(), [](auto &lhs, auto &rhs)
                 { return lhs[1] < rhs[1]; });
        }
    };

}
