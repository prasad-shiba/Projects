#include "User.c++"
namespace contact_management
{
    using namespace user;
    class ContactManagement : protected User
    {
    protected:
        // A
        void addContact(const std::string &contactsFilepath)
        {
            Utility::clearScreen();
            Utility::printTitle("ADD CONTACT", 11);
            std::vector<std::string> line;
            Utility::inputContactFile(line);
            std::fstream fout;
            Utility::openWriteMode(contactsFilepath, fout);
            fout << line[0] << ',' << line[1] << ',' << line[2] << '\n';
            Utility::closeFile(fout);
            Utility::processingText(utl::ADDING);
            Utility::printTitle("ADD CONTACT", 11);
            Utility::sleep(1000);
            std::cout << std::endl
                      << "\n\n\n\n\t\t\t" << line[0] << "'s contact information has been added to the contact list.'";
            Utility::redirectMessage("Home screen");
            shrink_to_fit(contactsFilepath);
        }

        // D
        bool deleteAllContacts(const std::string &contactsFilepath)
        {
            Utility::clearScreen();
            Utility::printTitle("Delete All Contacts", 19);
            if (!Utility::isFileAvailable(contactsFilepath))
            {
                return Utility::fileNotFoundMessage();
            }
            if (Utility::confirmMessage("delete all contacts"))
            {
                Utility::printTitle("Delete All Contacts", 19);
                Utility::processingText(utl::DELETING);
                Utility::deleteFile(getContactsFilepath());
                std::cout << "\n\n\t\t\tThe contact information has been completely erased.";
                Utility::sleep(450);
                Utility::redirectMessage("Home screen");
                return true;
            }
            Utility::redirectMessage("Home screen");
            return false;
        }

        bool deleteContact(const std::string &contactsFilepath)
        {
            Utility::clearScreen();
            if (!Utility::isFileAvailable(contactsFilepath))
            {
                return Utility::fileNotFoundMessage();
            }
            std::string number_or_email;
            std::vector<std::vector<std::string>> filedata;
            Utility::printTitle("DELETE CONTACT", 14);
            std::cout << "\n\n\t\t\tEnter email or phone number of contact you want to delete : ";
            std::getline(std::cin, number_or_email);
            if (Utility::confirmMessage("delete the contact"))
            {
                bool op = Utility::copyFileToString_Delete(contactsFilepath.c_str(), filedata, number_or_email);
                Utility::deleteFile(contactsFilepath);
                Utility::copyStringToFile(contactsFilepath.c_str(), filedata);
                shrink_to_fit(contactsFilepath);
                if (op)
                {

                    Utility::processingText(utl::DELETING);
                    Utility::printTitle("DELETE CONTACT", 14);
                    std::cout << "\n\n\t\t\t" << number_or_email << "'s contact information has been erased.";
                }
                else
                {
                    return Utility::recordNotFoundMessage(number_or_email);
                }
            }
            Utility::redirectMessage("Home screen");
            return true;
        }

        // S
        bool searchContact(const std::string &contactsFilepath)
        {
            Utility::clearScreen();
            Utility::printTitle("SEARCH CONTACT", 14);
            if (!Utility::isFileAvailable(contactsFilepath))
            {
                return Utility::fileNotFoundMessage();
            }
            std::string name_number_mail;
            std::vector<std::vector<std::string>> filedata;
            std::vector<std::vector<std::string>> files;
            std::cout << "\n\n\t\t\t\tEnter email or phone number or name of contact you want to search : ";
            std::getline(std::cin, name_number_mail);
            Utility::processingText(utl::SEARCHING);
            Utility::printTitle("SEARCH CONTACT", 14);
            Utility::copyFileToString(contactsFilepath, filedata);
            for (auto i : filedata)
            {
                if (i[0] == name_number_mail || i[1] == name_number_mail || i[2] == name_number_mail)
                    files.push_back(i);
            }
            if (!files.size())
            {
                return Utility::recordNotFoundMessage(name_number_mail);
            }
            printAllContacts(files);
            return true;
        }

        static bool shrink_to_fit(const std::string &contactsFilepath)
        {
            Utility::clearScreen();
            if (!Utility::isFileAvailable(contactsFilepath))
            {
                return Utility::fileNotFoundMessage();
            }
            std::vector<std::vector<std::string>> filedata;
            Utility::copyFileToString(contactsFilepath, filedata);
            Utility::deleteFile(contactsFilepath);
            std::fstream fout;
            Utility::openWriteMode(contactsFilepath, fout);
            Utility::copyStringToFile(contactsFilepath, filedata);
            Utility::closeFile(fout);
            return true;
        }

        // U
        bool updateContact(const std::string &contactsFilepath)
        {
            Utility::clearScreen();
            if (!Utility::isFileAvailable(contactsFilepath))
            {
                return Utility::fileNotFoundMessage();
            }
            std::string number_or_email;
            std::vector<std::vector<std::string>> filedata;
            Utility::printTitle("UPDATE CONTACT", 14);
            std::cout << "\n\n\t\t\tEnter email or phone number of contact you want to update : ";
            std::getline(std::cin, number_or_email);
            if (Utility::confirmMessage("Update the contact"))
            {
                bool op = Utility::copyFileToString_Update(contactsFilepath.c_str(), filedata, number_or_email);
                remove(contactsFilepath.c_str());
                Utility::copyStringToFile(contactsFilepath.c_str(), filedata);
                shrink_to_fit(contactsFilepath);
                if (op)
                {
                    Utility::processingText(utl::UPDATING);
                    Utility::printTitle("UPDATE CONTACT", 14);
                    std::cout << "\n\n\t\t\t" << number_or_email << "'s contact information has been updated.";
                }
                else
                {
                    return Utility::recordNotFoundMessage(number_or_email);
                }
            }
            Utility::redirectMessage("Home Screen");
            return true;
        }

        // P
        bool printAllContacts(std::vector<std::vector<std::string>> &filedata)
        {
            Utility::clearScreen();
            Utility::printTitle("View All Contacts", 17);
            if (filedata.size() != 0)
            {
                Utility::sortByName(filedata);
                std::cout << "\n\n\t\t\t\t\tContacts \n\n";
                std::cout << "\n-----------------------------------------------------------------------------------------------------------------------\n"
                          << std::endl
                          << std::endl;
                std::cout << "\tName                          Phone number        Email                                   " << std::endl
                          << std::endl;
                for (int i = 0; i < filedata.size(); ++i)
                {

                    std::string name(30 - filedata[i][0].size(), ' ');
                    std::string pno(20 - filedata[i][1].size(), ' ');
                    std::string mail(40 - filedata[i][2].size(), ' ');
                    std::string result = filedata[i][0] + name + filedata[i][1] + pno + filedata[i][2] + mail;
                    std::cout << "\t" << result << "\t" << std::endl;
                }
                Utility::pauseWindow();
                Utility::redirectMessage("Home screen");
                return true;
            }
            else
            {
                return Utility::fileNotFoundMessage();
            }
        }

        // V
        bool viewAllContacts(const std::string &contactsFilepath)
        {
            Utility::clearScreen();
            Utility::printTitle("View All Contacts", 17);
            if (!Utility::isFileAvailable(contactsFilepath))
            {
                return Utility::fileNotFoundMessage();
            }
            int validPin = 0;
            do
            {
                std::string mPin;
                if (validPin > 0)
                {
                    std::cout << "\n\n\t\t\tThe pin is invalid. Please try again.";
                    Utility::sleep(500);
                    Utility::clearScreen();
                    Utility::printTitle("View All Contacts", 17);
                }
                std::cout << "\n\n\t\t\tEnter your pin : ";
                std::getline(std::cin, mPin);
                if (isValidPin(mPin))
                {
                    if (isCorrectPin(stoi(mPin)))
                    {
                        setPin(stoi(mPin));
                        break;
                    }
                }
                ++validPin;
            } while (true);
            std::fstream fin;
            Utility::openReadMode(contactsFilepath, fin);
            std::vector<std::vector<std::string>> filedata;
            Utility::copyFileToString(contactsFilepath, filedata);
            Utility::closeFile(fin);
            return printAllContacts(filedata);
        }
    };
}
