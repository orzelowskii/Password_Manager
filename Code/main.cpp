#include <iostream>
#include "fmt/core.h"
#include "fmt/ranges.h"
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>
#include "Category.h"
#include "Files.h"

Category category;
Files files;

auto crypt(std::vector<std::string>& files) -> void;
auto findPassword() -> void;
auto sortPasswords() -> void ;
auto addPassword() -> void ;
auto editPassword() -> void ;
auto removePassword() -> void ;
auto addCetegory() -> void ;
auto removeCategory() -> void ;
auto saveTimestamp(bool const condition) -> void;
auto start() -> void ;
auto exit() -> void;

auto main() -> int {

    category.addCategory("work");
    category.addCategory("home");

    files.addFile("work.txt");
    files.addFile("home.txt");

    int trails = 3;

    std::string passwordToMH = "Pjctonajlepszyprzedmiot";
    std::string password;

    do {
        auto condition = false;

    std::cout << "Podaj hasło: ";
    std::cin >> password;
    std::cout << std::endl;

        if (password == passwordToMH) {
            condition = true;
            saveTimestamp(condition);
            crypt(files.files);
            start();
        } else {
            saveTimestamp(condition);
            trails--;
            if(trails == 0){
                exit(0);
            }
            std::cout << "Błedne hasło !!!" << std::endl << "Pozostały " << trails << " proby" << std::endl;
        }
    } while (password != passwordToMH);

    return 0;
}

/**
 * Funkcja start() - rozpoczyna program dopoki sie z niego nie wyjdzie
 */
auto start() -> void {

    auto x = 0;

    std::cout << "1. Wyszukaj haslo" << std::endl
              << "2. Posortuj hasla" << std::endl
              << "3. Dodaj haslo" << std::endl
              << "4. Edytuj haslo" << std::endl
              << "5. Ususn haslo" << std::endl
              << "6. Dodaj kategorie" << std::endl
              << "7. Usun kategorie" << std::endl
              << "8. Wyjdz" << std::endl
              << "Wybierz opcje: ";

    std::cin >> x;


    switch (x) {
        case 1:
            findPassword();
            start();
        case 2:
            sortPasswords();
            start();
        case 3:
            addPassword();
            start();
        case 4:
            editPassword();
            start();
        case 5:
            removePassword();
            start();
        case 6:
            addCetegory();
            start();
        case 7:
            removeCategory();
            start();
        case 8:
            exit();
            start();
    }

}

auto exit() -> void {
    crypt(files.files);
    exit(0);
}

/**
 * Funkcja saveTimestamp() - zapisuje w pliku czas proby odgadniecie hasla do programu
 * i zapisuje kazda probe niezaleznie czy jest poprawna czy nie
 */
auto saveTimestamp(bool const condition) -> void {
    auto currentTime = std::chrono::system_clock::now();
    std::time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime);

    std::tm* localTime = std::localtime(&currentTime_t);

    std::string timestamp = std::to_string(localTime->tm_hour) + "." +
                            std::to_string(localTime->tm_min) + "." +
                            std::to_string(localTime->tm_sec);

    std::ofstream file("timestamp.txt", std::ios::app);
    if (file.is_open()) {
        if(condition){
            file << timestamp << " - Udana" << std::endl;
        } else{
            file << timestamp << " - Nieudana" << std::endl;
        }
        file.close();
    }
}

/**
 * Funkcja isPasswordSecure() - sprawdza zcy haslo jest odpowiednio bezpieczne.
 * Sprawdza male, duze litery i znaki specjalne
 */
auto isPasswordSecure(std::string const& password) -> bool{
    if (password.length() < 8)
        return false;

    bool hasUpperCase = false;
    bool hasLowerCase = false;
    for (char c : password)
    {
        if (isupper(c))
            hasUpperCase = true;
        else if (islower(c))
            hasLowerCase = true;
    }
    if (!hasUpperCase || !hasLowerCase){
        return false;
    }

    bool hasSpecialChar = false;
    for (char c : password){
        if (!isalnum(c)){
            hasSpecialChar = true;
            break;
        }
    }
    if (!hasSpecialChar) {
        return false;
    }

    return true;
}

/**
 *Funkcja generateRandomPassword() - generuje i zwraca haslo o ustalonej dlugosci
 */
auto generateRandomPassword(int const length, bool const includeUpperCase, bool const includeLowerCase, bool const includeSpecialChar) -> std::string{
    std::string password;
    std::string upperCaseChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string lowerCaseChars = "abcdefghijklmnopqrstuvwxyz";
    std::string specialChars = "!@#$%^&*()";

    if (includeUpperCase)
        password += upperCaseChars;
    if (includeLowerCase)
        password += lowerCaseChars;
    if (includeSpecialChar)
        password += specialChars;

    std::string generatedPassword;
    for (int i = 0; i < length; i++)
    {
        generatedPassword += password[rand() % password.length()];
    }

    return generatedPassword;
}

/**
 * Funkcja addPassword() - dodaje haslo do odpowiedniego pliku
 */
auto addPassword() -> void{
    std::cout << "Czy chcesz wybrac istniejacy plik czy podac sciezke absolutna? (1 - istniejacy plik, 2 - sciezka absolutna): ";
    int choice;
    std::cin >> choice;

    std::string filePath;
    if (choice == 1){

        for (int i = 0; i < files.size(); i++){
            std::cout << i + 1 << ". " << files.at(i) << std::endl;
        }
        std::cout << "Wybierz jeden z istniejacych plikow:";

        int fileChoice;
        std::cin >> fileChoice;

        if (fileChoice < 1 || fileChoice > files.size()){
            std::cout << "Nieprawidlowy wybor pliku." << std::endl;
            return;
        }

        filePath = files.at(fileChoice - 1);
    }else if (choice == 2){
        std::cout << "Podaj sciezke absolutna pliku: ";
        std::getline(std::cin, filePath);
    }else{
        std::cout << "Nieprawidlowy wybor." << std::endl;
        return;
    }

    std::cout << "Czy chcesz wygenerowac haslo automatycznie czy wpisac wlasne? (1 - automatyczne, 2 - wlasne): ";
    int passwordChosen;
    std::cin >> passwordChosen;

    std::string password;
    if (passwordChosen == 1)
    {
        std::cout << "Wybierz parametry generacji hasla:" << std::endl;
        std::cout << "Ilosc znakow: ";
        int length;
        std::cin >> length;

        std::cout << "Czy ma zawierac wielkie litery?" << std::endl << "(1 - tak, 0 - nie): ";
        bool includeUpperCase;
        std::cin >> includeUpperCase;

        std::cout << "Czy ma zawierac male litery?" << std::endl << "(1 - tak, 0 - nie): ";
        bool includeLowerCase;
        std::cin >> includeLowerCase;

        std::cout << "Czy ma zawierac znaki specjalne?" << std::endl << "(1 - tak, 0 - nie): ";
        bool includeSpecialChar;
        std::cin >> includeSpecialChar;

        password = generateRandomPassword(length, includeUpperCase, includeLowerCase, includeSpecialChar);
        std::cout << "Wygenerowane haslo: " << password << std::endl;
    }else if (passwordChosen == 2){
        while (true){
            std::cout << "Podaj haslo: ";
                std::cin >> password;

            if (isPasswordSecure(password))
                break;

            std::cout << "Haslo nie spelnia wymagan bezpieczenstwa. Sprobuj ponownie." << std::endl;
        }
    }else{
        std::cout << "Nieprawidlowy wybor." << std::endl;
        return;
    }

    std::cout << "Podaj nazwe hasla: ";
    std::string passwordName;
    std::cin >> passwordName;

    std::cout << "Rodzaje kategorii: ";
    std::cout << std::endl;
    fmt::print("{}",category.categories);
    std::string category;
    std::cout << "Podaj kategorie: ";
    std::cin >> category;

    if (!isPasswordSecure(password))
    {
        std::cout << "Haslo nie spelnia wymagan bezpieczenstwa." << std::endl;
        return;
    }

    std::ifstream file(filePath);
    std::string line;
    std::vector<std::string> passwords;
    while (std::getline(file, line))
    {
        passwords.push_back(line);
    }
    file.close();

    for (const std::string& existingPassword : passwords)
    {
        if (existingPassword == password)
        {
            std::cout << "Haslo zostalo juz wczesniej uzyte. Prosze wybrac inne haslo." << std::endl;
            return;
        }
    }

    std::ofstream outFile(filePath, std::ios_base::app);
    outFile << passwordName << std::endl;
    outFile << password << std::endl;
    outFile << std::endl;
    outFile.close();

    std::cout << "Haslo zostalo dodane do pliku." << std::endl;
}

auto sortPasswords() -> void {

}

/**
 * Funkcja findPassword() - wyszukuje hasla po wybranych parametrach
 * typu(nazwa,haslo,kategoria)
 */
auto findPassword() -> void{
    std::cout << "Jak chcesz wyszukac haslo? (1 - po nazwie, 2 - po hasle, 3 - po kategorii): ";
    int choice;
    std::cin >> choice;

    std::string searchValue;
    if (choice == 1){
        std::cout << "Podaj nazwe hasla do wyszukania: ";
        std::cin >> searchValue;
    }else if (choice == 2){
        std::cout << "Podaj haslo do wyszukania: ";
        std::cin >> searchValue;
    }else if (choice == 3){
        std::cout << "Rodzaje kategorii: ";
        fmt::print("{}",category.categories);
        std::cout << std::endl;
        std::cout << "Podaj kategorie do wyszukania: ";
        std::cin >> searchValue;
    }else{
        std::cout << "Nieprawidlowy wybor." << std::endl;
        return;
    }

    std::cout << "Czy chcesz przeszukac istniejacy plik czy podac sciezke absolutna? (1 - istniejacy plik, 2 - sciezka absolutna): ";
    int fileChoice;
    std::cin >> fileChoice;

    int chosenFile;

    std::string filePath;
    if (fileChoice == 1){

        for (int i = 0; i < files.size(); i++){
            std::cout << i + 1 << ". " << files.at(i) << std::endl;
        }
        std::cout << "Wybierz jeden z istniejacych plikow:";

        std::cin >> chosenFile;

        if (chosenFile < 1 || chosenFile > files.size()){
            std::cout << "Nieprawidlowy wybor pliku." << std::endl;
            return;
        }

        filePath = files.at(chosenFile - 1);
    }else if (fileChoice == 2){
        std::cout << "Podaj sciezke absolutna pliku: ";
        std::cin >> filePath;
    }else{
        std::cout << "Nieprawidlowy wybor." << std::endl;
        return;
    }

    std::ifstream file(filePath);
    std::string line;
    std::vector<std::string> passwords;
    while (std::getline(file, line))
    {
        passwords.push_back(line);
    }
    file.close();

    bool found = false;
    std::vector<std::string> foundPasswords;

    if (choice == 1 || choice == 2){
        for (int i = 0; i < passwords.size(); i += 3){
            if ((choice == 1 && passwords[i] == searchValue) || (choice == 2 && passwords[i + 1] == searchValue)){
                foundPasswords.push_back(passwords[i]);
                foundPasswords.push_back(passwords[i + 1]);
                foundPasswords.push_back(passwords[i + 2]);
                found = true;
                break;
            }
        }
    }else if (choice == 3){
        for (int i = 0; i < passwords.size(); i += 3){
            if (passwords[i + 2] == searchValue){
                foundPasswords.push_back(passwords[i]);
                foundPasswords.push_back(passwords[i + 1]);
                foundPasswords.push_back(passwords[i + 2]);
                found = true;
            }
        }
    }

    if (found && (choice == 1 || choice == 2)){
        std::cout << "Znalezione haslo:" << std::endl;
        for (int i = 0; i < foundPasswords.size(); i += 3){
            std::cout << "Nazwa: " << foundPasswords[i] << std::endl;
            std::cout << "Haslo: " << foundPasswords[i + 1] << std::endl;
            std::cout << "Kategoria: " << category.categories.at(chosenFile-1) << std::endl;
            std::cout << std::endl;
        }
    }else if (found && choice == 3){
        std::cout << "Znalezione haslo:" << std::endl;
        for (int i = 0; i < foundPasswords.size(); i += 3)
        {
            std::cout << "Nazwa: " << foundPasswords[i] << std::endl;
            std::cout << "Haslo: " << foundPasswords[i + 1] << std::endl;
            std::cout << std::endl;
        }
    } else{
        std::cout << "Nie znaleziono pasujacych hasel." << std::endl;
    }
}

auto editPassword() -> void{

}

auto removePassword() -> void{

}

auto addCetegory() -> void{

    std::string cat;
    std::cout << "Podaj nazwe kategorii: ";
    std::cin >> cat;

    category.addCategory(cat);

    cat += ".txt";
    std::ofstream file(cat);
    files.addFile(cat);

}

auto removeCategory() -> void{

    fmt::print("{}",category.categories);
    std::cout<< std::endl;
    std::string cat;
    std::cout << "Podaj nazwe kategorii ktora chcesz usunac: ";
    std::cin >> cat;

    category.removeCategory(cat);

    cat += ".txt";
    std::remove(cat.c_str());
    files.removeFile(cat);
}

/**
 *Funkcja crypt() - szyfruje i odszyfrowuje pliki txt podane w argumencie,
 * Uzywa do tego klucza i operatora XOR
 */
auto crypt(std::vector<std::string>& files) -> void {
    std::string key = "ZUPAPOMIDOROWA";

    for (std::string const& filename : files) {
        std::ifstream inputFile(filename);
        if (inputFile.is_open()) {
            std::string crypted;

            std::string line;
            while (std::getline(inputFile, line)) {
                std::string encryptedLine;
                for (char c : line) {
                    char encryptedChar = c ^ key[encryptedLine.size() % key.size()];
                    encryptedLine += encryptedChar;
                }
                crypted += encryptedLine + '\n';
            }
            inputFile.close();

            std::ofstream outputFile(filename);
            if (outputFile.is_open()) {
                outputFile << crypted;
                outputFile.close();
            } else {
                std::cout << "Błąd podczas zapisu szyfrowanego pliku: " << filename << std::endl;
            }
        } else {
            std::cout << "Błąd podczas otwierania pliku: " << filename << std::endl;
        }
    }
}