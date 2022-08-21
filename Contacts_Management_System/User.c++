#include "Utility.hh"
namespace user
{
    static const int LOGIN = 1;
    static const int SIGNUP = 0;
    using namespace utl;
    class User
    {

    protected:
        // G
        static std::string getAdminFilepath() { return adminFilepath; }

        static std::string getContactsFilepath() { return contactsFilepath; }

        int getPin() { return pin; }

        std::string getUserId() { return userId; }

        std::string getUserName() { return userName; }

        std::string getUserNameFromFile()
        {
            std::fstream fin;
            Utility::openReadMode(adminFilepath, fin);
            std::string str, s;
            std::vector<std::string> line;
            getline(fin, str);
            std::stringstream ss(str);
            while (std::getline(ss, s, ','))
            {
                line.push_back(s);
            }
            return line[0];
        }

        // I
        void inputUser(const int &param = LOGIN)
        {
            int validId = 0, validPin = 0;
            std::string userId, pin;
            if (param == SIGNUP)
            {
                std::string userName;
                std::cout << "\n\n\t\t\tEnter your name : ";
                std::getline(std::cin, userName);
                setUserName(userName);
            }
            if (param == SIGNUP)
            {
                std::cout << "\n\n\t\t\t(Your User ID must be at least three characters long and no longer than thirty characters long. There was no empty space.)";
            }
            do
            {
                if (validId > 0)
                {
                    std::cout << "\n\n\t\t\tThe User ID is invalid. Please try again.";
                }
                userId.clear();
                std::cout << "\n\n\t\t\tEnter your User Id : ";
                std::getline(std::cin, userId);
                ++validId;
            } while (isValidUserId(userId) != true);
            setUserId(userId);
            if (param == SIGNUP)
            {
                std::cout << "\n\n\t\t\t(Your PIN must be at least 3 characters long and no more than 9 characters long.)";
            }
            do
            {
                if (validPin > 0)
                {
                    std::cout << "\n\n\t\t\tThe pin is invalid. Please try again.";
                }
                pin.clear();
                std::cout << "\n\n\t\t\tEnter your pin : ";
                std::getline(std::cin, pin);
                ++validPin;
            } while (isValidPin(pin) != true);
            setPin(stoi(pin));
        }

        bool isCorrectPin(const int &pin)
        {

            if (!Utility::isFileAvailable(adminFilepath))
            {
                std::cout << "\n\t\t\tfail to open file 'data.csv'";
                return false;
            }
            std::fstream fin;
            Utility::openReadMode(adminFilepath, fin);
            std::string str, s;
            std::vector<std::string> line;
            std::getline(fin, str);
            Utility::closeFile(fin);
            std::stringstream ss(str);
            while (std::getline(ss, s, ','))
            {
                line.push_back(s);
            }
            if (line[2] == std::to_string(pin))
                return true;
            else
                return false;
        }

        bool isCorrectUserId(const std::string &userId)
        {
            if (!Utility::isFileAvailable(adminFilepath))
            {
                std::cout << "\n\t\t\tfail to open file ";
                return false;
            }
            std::fstream fin;
            Utility::openReadMode(adminFilepath, fin);
            std::string str, s;
            std::vector<std::string> line;
            std::getline(fin, str);
            Utility::closeFile(fin);
            std::stringstream ss(str);
            ;
            while (std::getline(ss, s, ','))
            {
                line.push_back(s);
            }
            if (line[1] == userId)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        bool isUserExist()
        {
            if (Utility::isFileAvailable(adminFilepath))
            {
                std::fstream fin;
                Utility::openReadMode(adminFilepath, fin);
                std::string line;
                std::getline(fin, line);
                Utility::closeFile(fin);
                if (line.size() >= 9)
                {
                    std::stringstream ss(line);
                    std::vector<std::string> rows;
                    while (std::getline(ss, line, ','))
                    {
                        rows.push_back(line);
                        line.clear();
                    }
                    if (rows.size() == 3)
                    {
                        if (rows[0].size() > 0 && (rows[1].size() >= 3 && rows[1].size() <= 30) && (rows[2].size() >= 3 && rows[2].size() <= 9))
                            return true;
                        else
                            return false;
                    }
                    else
                        return false;
                }
                else
                    return false;
            }
            return false;
        }

        bool isValidPin(const std::string &pin)
        {
            if (pin.size() < 3 || pin.size() > 9)
            {
                return false;
            }
            for (auto i : pin)
            {
                if (!(i >= '0' && i <= '9'))
                {
                    return false;
                }
            }
            int pin_number = stoi(pin);
            if (!(pin_number >= 111 && pin_number <= 999999999))
            {
                return false;
            }
            return true;
        }

        bool isValidUserId(const std::string &userId)
        {
            if ((userId.size() != 0) && (userId.size() >= 3) && (userId.size() <= 30))
            {
                for (auto i : userId)
                {
                    if (i == ' ')
                        return false;
                }
                return true;
            }
            return false;
        }

        // L
        bool logIn()
        {
            Utility::clearScreen();
            Utility::logo();
            Utility::printTitle("Log In", 6);
            inputUser();
            if (verifyUser(this->userId, (this->pin)))
            {
                Utility::sleep(1000);
                Utility::processingText(utl::LOGIN);
                Utility::printTitle("Log In", 6);
                this->userName = getUserNameFromFile();
                std::cout << "\n\n\n\n\t\t\tHey, " << userName << "! You have successfully logged in.";
                Utility::sleep(450);
                Utility::redirectMessage("Home Screen");
                return true;
            }
            else
            {
                return false;
            }
        }

        // S
        static void setAdminFilepath(const std::string &adminFilepath) { User::adminFilepath = adminFilepath; }

        static void setContactsFilepath(const std::string &scontactsFilepath) { User::contactsFilepath = contactsFilepath; }

        void setPin(const int &pin) { User::pin = pin; }

        void setUserId(const std::string &userId) { this->userId = userId; }

        void setUserName(const std::string &userName) { this->userName = userName; }

        bool signUp()
        {
            Utility::clearScreen();
            Utility::logo();
            Utility::printTitle("Sign Up", 7);
            inputUser(SIGNUP);
            storeUserDetails(userName, userId, std::to_string(pin));
            Utility::
                Utility::sleep(450);
            Utility::processingText(utl::SIGNUP);
            Utility::clearScreen();
            Utility::printTitle("Sign Up", 7);
            Utility::sleep(50);
            std::cout << "\n\n\n\n\n\t\t\tDear " << User::getUserName() << ", welcome. Your account has been created!";
            std::cout << "\n\n\n\t\t\tRemember " << User::getUserName() << " your pin is '" << pin << "'. If you forget your pin, you can't access your contacts.";
            Utility::sleep(4000);
            Utility::redirectMessage("LogIn screen");
            return true;
        }

        bool storeUserDetails(const std::string &userName, const std::string &userId, const std::string &pin)
        {
            if (!Utility::isFileAvailable(adminFilepath))
            {
                std::fstream fout;
                Utility::openWriteMode(adminFilepath, fout);
                fout << userName << ',' << userId << ',' << pin << '\n';
                Utility::closeFile(fout);
                return true;
            }
            else
            {
                return false;
            }
        }

        // V
        bool verifyUser(const std::string &userId, const int &pin)
        {
            if ((isCorrectUserId(userId)) && (isCorrectPin(pin)))
                return true;
            else
                return false;
        }

    private:
        int pin;
        std::string userId;
        std::string userName;
        static std::string adminFilepath;
        static std::string contactsFilepath;
    };

    std::string User::adminFilepath;
    std::string User::contactsFilepath;

}
