#include "ContactManagement.c++"
namespace cnt
{
    using namespace contact_management;
    class Contacts : private ContactManagement
    {
    public:
        Contacts()
        {
            Utility::clearScreen();
            Utility::showConsoleCursor(false);
            Utility::setColor("color 9f");
            Utility::loadingBar();
            User::setAdminFilepath("data.csv");
            User::setContactsFilepath("encrypted_contacts.csv");
            // exposeFile();
            Utility::clearScreen();
        }

        ~Contacts()
        {
            // protectFile();
            Utility::showConsoleCursor(true);
        }

        void startConsoleApplication()
        {
            Utility::clearScreen();
            if (!isUserExist())
            {
                while (signUp() != true)
                {
                };
            }
            while (logIn() != true)
            {
                std::cout << "\n\n\t\t\tInvalid Username or Pin! Please try again.";
                Utility::sleep(3500);
            };
            mainMenu();
        }

    private:
        void inputChoice()
        {
            char choice;
            std::cin >> choice;
            getchar();
            Utility::sleep(500);
            switch (choice)
            {
            case '1':
                addContact("encrypted_contacts.csv");
                mainMenu();
                break;
            case '2':
                updateContact("encrypted_contacts.csv");
                mainMenu();
                break;
            case '3':
                deleteContact("encrypted_contacts.csv");
                mainMenu();
                break;
            case '4':
                searchContact("encrypted_contacts.csv");
                mainMenu();
                break;
            case '5':
                viewAllContacts("encrypted_contacts.csv");
                mainMenu();
                break;
            case '6':
                deleteAllContacts("encrypted_contacts.csv");
                mainMenu();
                break;
            case '7':
                Utility::closeWindow(User::getUserName());
                break;
            default:
                std::cout << "\n\n\t\t\tInvalid option, re-enter correct option.";
                Utility::sleep(450);
                Utility::redirectMessage("Home screen");
                mainMenu();
                break;
            }
        }

        void mainMenu()
        {
            Utility::clearScreen();
            Utility::logo();
            std::cout << "\n\n\t\t\t     " << Utility::getGreetingMessage() << User::getUserName() << " .\n\n";
            std::cout << "\n\n\n\t\t\t\t1. Add Contact";
            std::cout << "\n\n\t\t\t\t2. Edit Contact";
            std::cout << "\n\n\t\t\t\t3. Delete Contact";
            std::cout << "\n\n\t\t\t\t4. Search Contact";
            std::cout << "\n\n\t\t\t\t5. View All Contacts";
            std::cout << "\n\n\t\t\t\t6. Delete All Contacts";
            std::cout << "\n\n\t\t\t\t7. Exit Contact";
            std::cout << "\n\n\t\t\t\tEnter an option : ";
            inputChoice();
        }
    };

}