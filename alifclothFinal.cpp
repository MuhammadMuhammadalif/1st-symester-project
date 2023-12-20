#include <iostream>
#include <windows.h>
#include <cctype>
#include <string>
#include <conio.h>
#include <cmath>
#include <fstream>
using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void header();

string inputName();
string inputPassword();
string inputRole();

bool checkString(string name);
bool checkSpace(string name);
bool checkInteger(string value);
bool checkFloat(string value);

void signUpLogo();
bool signUp(string name, string password, string role, string username[], string userpassword[], string userrole[], int &usercount);

void signInLogo();
string signin(string username[], string userrole[], string userpassword[], int usercount);

int adminMenu();
void clothNames();
void addCloth(string clothName[], float clothPrice[], int clothQuantity[], int &clothIndex, string clothPriceString[], string clothQuantityString[]);
void deleteCloth(string clothName[], int clothQuantity[], float clothPrice[], int &clothIndex);
void updateQuantity(string clothName[], int clothQuantity[], float clothPrice[], int clothIndex);
void updateName(string clothName[], int clothQuantity[], float clothPrice[], int clothIndex);
void updatePrice(string clothName[], int clothQuantity[], float clothPrice[], int clothIndex);
void discount(string clothName[], int clothQuantity[], float clothPrice[], int clothIndex);
void viewStock(string clothName[], float clothPrice[], int clothQuantity[], int clothIndex);
void viewClients(string username[], string userpassword[], string userrole[], int usercount);
void deleteClient(string username[], string userpassword[], string userrole[], int &usercount);
bool checkCloth(string clothName[], int clothIndex, string name2);

int clientMenu();
void viewSession();
void viewColor();
void viewCatagory();
void viewTypes();
void addToCart(string clothName[], float clothPrice[], int clothQuantity[], int clothIndex, string cartName[], float cartPrice[], int cartQuantity[], int &cartIndex);
void viewCart(string cartName[], float cartPrice[], int cartQuantity[], int cartIndex);
void updateCartQuantity(string cartName[], int cartQuantity[], float cartPrice[], int cartIndex);

void deleteFromCart(string cartName[], float cartPrice[], int cartQuantity[], int cartIndex);

void buyCart(string clothName[], float clothPrice[], int clothQuantity[], int clothIndex, string cartName[], float cartPrice[], int cartQuantity[], int cartIndex, bool &cartBought);
void calculateBill(string cartName[], float cartPrice[], int cartQuantity[], int cartIndex, string userName[]);
void paymentMethod();

void shiftArrayForClient(string username[], string userpassword[], string userrole[], int arrCount, int &totalCount);
void shiftArrayForCloth(string clothName[], int clothQuantity[], float clothPrice[], int clothIndex, int &totlaCount);

void storeUsersInFile(string username[], string userpassword[], string userrole[], int usercount, string path);
// void appendUsreInFile(string username[], string userpassword[], string userrole[], int usercount, string path);

string getField(string record, int field);
void readUsersFromFile(string username[], string userpassword[], string userrole[], int &usercount);

void storeClothInFile(string clothName[], float clothPrice[], int clothQuantity[], int clothIndex, string path);
void readClothFromFile(string clothName[], float clothPrice[], int clothQuantity[], int &clothIndex);

void deleteClothFromFile(string clothName[], int clothQuantity[], float clothPrice[], int &clothIndex);
void updateClothNameInFile(string clothName[], int clothQuantity[], float clothPrice[], int clothIndex);
void updateClothQuantityInFile(string clothName[], int clothQuantity[], float clothPrice[], int clothIndex);
void updateClothPriceInFile(string clothName[], int clothQuantity[], float clothPrice[], int clothIndex);
void deleteClientFromFile(string username[], string userpassword[], string userrole[], int &usercount);

main()
{

    system("cls");
    header();
    string username[100];
    string userpassword[100];
    string userrole[100];
    int usercount = 0;

    string clothName[100];
    float clothPrice[100];
    int clothQuantity[100];
    int clothIndex = 0;

    string cartName[100];
    float cartPrice[100];
    int cartQuantity[100];
    int cartIndex = 0;

    string option;
    int opt1;
    int adminOption;
    int clientOption;

    string name, password, role, ifRole;
    string nameIn, passwordIn;
    bool cartBought = false;

    while (true)
    {

        system("cls");
        header();
        cout << "\n\n\n\t\t1: Sign Up!" << endl;
        cout << "\t\t2: Sign In!" << endl;
        cout << "\t\t3: Exit!" << endl;
        cout << "\t\t\tEnter your option: ";
        readUsersFromFile(username, userpassword, userrole, usercount);

        cin >> option;

        if (!checkInteger(option))
        {
            cout << "\n\t\t\tInvalid input." << endl;
            cout << "\t\t\tPress any key to continue...";
            getch();
            continue;
        }
        else
        {
            opt1 = stoi(option);
        }

        // when option is 1 sign up menu will open
        if (opt1 == 1)
        {
            signUpLogo();
            name = inputName();
            if (name == "invalid")
            {
                cout << "\t\tInvalid username." << endl;
                cout << "\t\tPress any key to continue...";
                getch();
                continue;
            }
            if (name.length() < 5)
            {
                cout << "\n\n\t\t The name must contain atleast 5 characters!!" << endl;
                cout << " \t\tPress any key to continue...";
                getch();
                continue;
            }

            password = inputPassword();
            if (password.length() < 8)
            {
                cout << "\n\n\t\t The password must contain atleast 8 characters!!" << endl;
                cout << " \t\tPress any key to continue...";
                getch();
                continue;
            }
            ifRole = inputRole();

            // if role is other than admin or client.  it will not be accepted.
            if (ifRole == "admin" || ifRole == "Admin" || ifRole == "ADMIN" || ifRole == "client" || ifRole == "Client" || ifRole == "CLIENT")
            {
                role = ifRole;
            }
            else
            {
                cout << "\n\n Invalid user role.Try another." << endl;
                cout << " Press any key to continue...";
                getch();
                continue;
            }

            // it will check weather the user has aleady entered or not.
            if (signUp(name, password, role, username, userpassword, userrole, usercount))
            {
                cout << "\n\n\t The username has already taken.Please choose another!" << endl;
                cout << "\tPress any key to continue...";
                getch();
                continue;
            }
            else
            {
                system("cls");
                header();
                cout << usercount;
                cout << "\n\n\t\tSigned Up Successfully!!" << endl;
                cout << "\t\tPress any key to continue...";
                string variableForFile = "users.txt";
                storeUsersInFile(username, userpassword, userrole, usercount, variableForFile);

                getch();
                continue;
            }
        }
        else if (opt1 == 2)
        {

            // when option is 2 sign up menu will open
            string signInOutput = signin(username, userrole, userpassword, usercount);
            if (signInOutput == "admin" || signInOutput == "Admin" || signInOutput == "ADMIN")

            {
                readClothFromFile(clothName, clothPrice, clothQuantity, clothIndex);
                cout << clothName[0];
                // here while loop will control the iterations of admin menu.
                while (true)

                {
                    adminOption = adminMenu();
                    if (adminOption == 1)
                    {
                        addCloth(clothName, clothPrice, clothQuantity, clothIndex);
                        storeClothInFile(clothName, clothPrice, clothQuantity, clothIndex, "stock.txt");
                    }
                    else if (adminOption == 2)
                    {
                        deleteClothFromFile(clothName, clothQuantity, clothPrice, clothIndex);
                    }
                    else if (adminOption == 3)
                    {
                        updateClothQuantityInFile(clothName, clothQuantity, clothPrice, clothIndex);
                    }
                    else if (adminOption == 4)
                    {
                        updateClothNameInFile(clothName, clothQuantity, clothPrice, clothIndex);
                    }
                    else if (adminOption == 5)
                    {
                        updateClothPriceInFile(clothName, clothQuantity, clothPrice, clothIndex);
                    }
                    else if (adminOption == 6)
                    {
                        discount(clothName, clothQuantity, clothPrice, clothIndex);
                    }
                    else if (adminOption == 7)
                    {
                        viewStock(clothName, clothPrice, clothQuantity, clothIndex);
                    }
                    else if (adminOption == 8)
                    {
                        viewClients(username, userpassword, userrole, usercount);
                    }
                    else if (adminOption == 9)
                    {
                        deleteClientFromFile(username, userpassword, userrole, usercount);
                    }

                    else
                    {
                        break;
                    }
                }
            }
            else if (signInOutput == "client" || signInOutput == "Client" || signInOutput == "CLIENT")
            {

                // here while loop will control the iterations of admin menu.
                while (true)
                {
                    clientOption = clientMenu();
                    if (clientOption == 1)
                    {
                        viewSession();
                    }
                    else if (clientOption == 2)
                    {
                        viewColor();
                    }
                    else if (clientOption == 3)
                    {
                        viewCatagory();
                    }
                    else if (clientOption == 4)
                    {
                        viewTypes();
                    }
                    else if (clientOption == 5)
                    {
                        viewStock(clothName, clothPrice, clothQuantity, clothIndex);
                    }
                    else if (clientOption == 6)
                    {
                        addToCart(clothName, clothPrice, clothQuantity, clothIndex, cartName, cartPrice, cartQuantity, cartIndex);
                    }
                    else if (clientOption == 7)
                    {
                        viewCart(cartName, cartPrice, cartQuantity, cartIndex);
                    }
                    else if (clientOption == 8)
                    {
                        updateCartQuantity(cartName, cartQuantity, cartPrice, cartIndex);
                    }
                    else if (clientOption == 9)
                    {
                        deleteFromCart(cartName, cartPrice, cartQuantity, cartIndex);
                    }
                    else if (clientOption == 10)
                    {
                        buyCart(clothName, clothPrice, clothQuantity, clothIndex, cartName, cartPrice, cartQuantity, cartIndex, cartBought);
                    }
                    else if (clientOption == 11)
                    {
                        if (cartBought)
                        {
                            SetConsoleTextAttribute(h, 15);
                            calculateBill(cartName, cartPrice, cartQuantity, cartIndex, username);
                            SetConsoleTextAttribute(h, 9);
                        }
                        else
                        {
                            cout << "\t\tYou do not buy any cloth yet!";
                        }
                    }
                    else if (clientOption == 12)
                    {
                        paymentMethod();
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                cout << "\n\t\t\tUser not found!!";
                getch();
            }
        }

        else if (opt1 == 3)
        {
            system("cls");
            cout << "\n\n\t\tThanks for using our application!!";
            break;
        }
        else
        {
            cout << "\n\t\t\tInvalid input." << endl;
            cout << "\t\t\tPress any key to continue...";
            getch();
            continue;
        }
    }
}

// function to print header.
void header()
{
    SetConsoleTextAttribute(h, 10);
    cout << "\n\n\t    @@@@@ @    @@@ @@@@   @@@@ @    @@@@ @@@@@ @  @  @@@@@   " << endl;
    cout << " \t   @   @ @     @  @      @    @    @  @   @   @  @  @       " << endl;
    cout << "  \t  @@@@@ @     @  @@@@   @    @    @  @   @   @@@@  @@@@@   " << endl;
    cout << "   \t @   @ @     @  @      @    @    @  @   @   @  @      @   " << endl;
    cout << "    \t@   @ @@@@ @@@ @      @@@@ @@@@ @@@@   @   @  @  @@@@@   " << endl;
    SetConsoleTextAttribute(h, 9);
}

// function to print signUp logo.
void signUpLogo()
{
    system("cls");
    SetConsoleTextAttribute(h, 10);

    cout << "\n\n\t _____  _                  _   _______ " << endl;
    cout << "\t/  ___ (_)                | | | | ___ \\" << endl;
    cout << "\t\\ `--. _  __ _  _ __      | | | | |_/ /" << endl;
    cout << " \t`--. \\ |/ _` | | '_ \\     | | | |  __/" << endl;
    cout << "\t/\\__/ / | (_| | | | |     | |_| | |" << endl;
    cout << "\t\\____/|_|\\__,||_| |_|      \\___/\\_| " << endl;
    cout << " \t          __/ |                  " << endl;
    cout << " \t         |___/                    " << endl;
    SetConsoleTextAttribute(h, 9);
}

// functio to allow sign up.
bool signUp(string name, string password, string role, string username[], string userpassword[], string userrole[], int &usercount)
{

    for (int i = 0; i <= usercount; i++)
    {
        if (name == username[i] && password == userpassword[i])
        {
            return true;
        }
    }

    username[usercount] = name;
    userpassword[usercount] = password;
    userrole[usercount] = role;
    usercount++;
    return false;
}
// function to take input name.
string inputName()
{
    string name;
    cout << "\n\n\n\t\tEnter User name: ";
    cin.ignore();
    getline(cin, name);

    if (checkString(name) && checkSpace(name))
    {
        return name;
    }
    else
    {
        return "invalid";
    }
}

// functio to take input password.
string inputPassword()
{
    string password;
    cout << "\t\tEnter passowrd(atleast 8 characters): ";
    getline(cin, password);
    return password;
}

// function to take input role.
string inputRole()
{
    string role;
    cout << "\t\tEnter User role(Admin/Client): ";
    getline(cin, role);
    return role;
}

// function to print signIn logo.
void signInLogo()
{
    system("cls");
    SetConsoleTextAttribute(h, 10);

    cout << "\n\n\t _____  _                   | " << endl;
    cout << "\t/  ___ (_)                  | " << endl;
    cout << "\t\\ `--. _  __ _  _ __        | " << endl;
    cout << " \t`--. \\ |/ _` | | '_ \\       |   " << endl;
    cout << "\t/\\__/ / | (_| | | | |       | " << endl;
    cout << "\t\\____/|_|\\__,||_| |_|       | " << endl;
    cout << " \t          __/ |                    " << endl;
    cout << " \t         |___/                  " << endl;
    SetConsoleTextAttribute(h, 9);
}

// function for signIn which will take name and password. and will return role.
string signin(string username[], string userrole[], string userpassword[], int usercount)
{
    string nameIn, passwordIn;
    system("cls");
    signInLogo();
    nameIn = inputName();
    passwordIn = inputPassword();
    for (int i = 0; i < usercount; i++)
    {
        if (nameIn == username[i] && passwordIn == userpassword[i])
        {
            return userrole[i];
        }
    }
    return "invalid";
}

// function to print admin menu. and will return option selected by admin.
int adminMenu()
{
start:
    string menu;
    int opt2;

    system("cls");
    header();
    cout << "\n\n\tADMIN MENU:";
    cout << "\n\n\n\t\t1:  Add new cloth" << endl;
    cout << "\t\t2:  Delete a cloth " << endl;
    cout << "\t\t3:  Update a cloth quantity" << endl;
    cout << "\t\t4:  Update a cloth name" << endl;
    cout << "\t\t5:  Update a cloth price" << endl;
    cout << "\t\t6:  Offer discounts" << endl;
    cout << "\t\t7:  View stock" << endl;
    cout << "\t\t8:  View clients" << endl;
    cout << "\t\t9:  Remove clients" << endl;
    cout << "\t\t0: Exit" << endl;

    cout << "\n\t\tSelect your option....";
    cin >> menu;
    if (checkInteger(menu) && checkSpace(menu))
    {
        opt2 = stoi(menu);
    }
    else
    {
        cout << "\t\t\tInvalid input!" << endl;
        cout << "\t\t\tPress any key to continue...";
        getch();
        goto start;
    }

    return opt2;
}

// admin function to add cloth.
void addCloth(string clothName[], float clothPrice[], int clothQuantity[], int &clothIndex)
{
start:
    system("cls");
    header();
    clothNames();
    string name, name2, price, quantity;

    cout << "\n\t\t\tEnter the cloth name you want to add: ";
    cin.ignore();
    getline(cin, name);
    if (checkString(name))
    {
        name2 = name;
    }
    else
    {
        cout << "\t\t\tInvalid cloth!" << endl;
        cout << "\t\t\tPress any key to continue!" << endl;
        getch();
        goto start;
    }

    if (checkCloth(clothName, clothIndex, name2))
    {
        clothName[clothIndex] = name2;
    }
    else
    {
        cout << "\t\t\tThe cloth is already added.Use update quantity function to add more quantity.";
        cout << "\n\t\t\tPress any key to continue...";
        getch();
        goto start;
    }

    cout << "\t\t\tEnter the price of cloth: ";
    cin >> price;
    if (checkFloat(price) && checkSpace(price))
    {
        clothPrice[clothIndex] = stof(price);
    }
    else
    {
        cout << "\t\t\tInvalid price!" << endl;
        cout << "\t\t\tPress any key to continue...";
        getch();
        goto start;
    }

    cout << "\t\t\tEnter the number of clothes: ";
    cin >> quantity;
    if (checkInteger(quantity) && checkSpace(quantity))
    {
        clothQuantity[clothIndex] = stoi(quantity);
    }
    else
    {
        cout << "\t\t\tInvalid quantity!" << endl;
        getch();
        goto start;
    }

    cout << "\n\t\tCloth has been added: ";

    clothIndex++;
    cout << "\n\t\tPress any key to continue...";
    getch();
}

// function to check weather the input string is integer.
bool checkInteger(string value)
{
    for (int i = 0; i != value.length(); i++)
    {

        if (!((value[i] >= '0') && (value[i] <= '9')))
        {
            return false;
        }
        return true;
    }
}

// function to check weather the input string is float.
bool checkFloat(string value)
{

    for (int i = 0; i < value.length(); i++)
    {

        if (!(((value[i] >= '0') && (value[i] <= '9')) || value[i] == '.'))
            return false;
    }
    return true;
}

// function to check weather the input string is string.and there is no special character.other than underscore.
bool checkString(string name)
{
    if (name[0] == '\0')
        return false;
    for (int i = 0; i < name.length(); i++)
    {

        if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= '0' && name[i] <= '9') || name[i] == '_'))
        {
            return false;
        }
    }
    return true;
}
bool checkSpace(string name)
{
    int spacecount = 0;

    for (char c : name)
    {
        if (isspace(c))
        {
            spacecount++;
        }
    }
    if (spacecount >= 3)
    {
        return false;
    }
    return true;
}

// admin function to print cloth names.
void clothNames()
{
    cout << "\n\n\t\tPlane_Cloth  !                                                          " << endl;
    cout << "\t\tFabric_2_piece  !                                                           " << endl;
    cout << "\t\tReady_to_wear  !                                                            " << endl;
    cout << "\t\tNew_on_sale  !                                                              " << endl;
    cout << "\t\tSpecial_Boutique  !                                                         " << endl;
    cout << "\t\tTrending_kurta  !                                                           " << endl;
}

// admin function to view stock.
void viewStock(string clothName[], float clothPrice[], int clothQuantity[], int clothIndex)
{
    system("cls");
    header();
    SetConsoleTextAttribute(h, 9);
    cout << "\n\n\tAvailable Stock.";
    SetConsoleTextAttribute(h, 10);

    cout << "\n\n\t\tCloth name\t\tCloth Price\t\tQuantity" << endl;
    for (int i = 0; i < clothIndex; i++)
    {

        cout << "\t\t" << clothName[i] << "\t\t\t" << clothPrice[i] << "\t\t\t" << clothQuantity[i] << endl;
    }
    cout << "\n\t\tPress any key to continue...";

    getch();
}

// admin function to delete a cloth.
void deleteCloth(string clothName[], int clothQuantity[], float clothPrice[], int &clothIndex)
{
start:
    int count = 0;
    string del, name, stay;
    int finalStay = 10;
    viewStock(clothName, clothPrice, clothQuantity, clothIndex);
    cout << "\n\n\t\t\tEnter the cloth you want to delete: ";
    cin.ignore();
    getline(cin, name);
    if (checkString(name))
    {
        del = name;
    }
    else
    {
        cout << "\t\tInvalid cloth!" << endl;
        cout << "\t\tPress 1 to stay or press 0 to exit.";
        cin >> stay;
        if (checkInteger(stay))
        {
            finalStay = stoi(stay);
        }
        if (finalStay == 1)
        {
            goto start;
        }
        else
        {
            finalStay = 0;
        }
    }
    if (finalStay != 1 && finalStay != 0)
    {

        for (int i = 0; i < clothIndex; i++)
        {
            if (del == clothName[i])
            {

                shiftArrayForCloth(clothName, clothQuantity, clothPrice, i, clothIndex);

                count++;
                break;
            }
        }
        if (count == 0)
        {
            cout << "\n\t\tInvalid name";

            goto start;
        }
        cout << "\n\t\tPress any key to continue...";
        getch();
    }
}

// admin function to update quantity.
void updateQuantity(string clothName[], int clothQuantity[], float clothPrice[], int clothIndex)
{
start:
    string update, name;
    int quantity1;
    int count = 0;

    viewStock(clothName, clothPrice, clothQuantity, clothIndex);
    cout << "\n\t\tEnter the cloth you want to update: ";
    getline(cin, name);

    if (checkString(name) && checkSpace(name))
    {
        update = name;
    }
    else
    {
        cout << "\t\tInvalid cloth!" << endl;
        cout << "\n\t\tPress any key to continue...";
        getch();
        goto start;
    }
    for (int i = 0; i < clothIndex; i++)
    {
        if (update == clothName[i])
        {
            cout << "\n\t\tEnter the updated quantity: ";
            cin >> quantity1;
            clothQuantity[i] = quantity1;
            count++;
        }
    }
    if (count == 0)
    {
        cout << "\n\t\tInvalid name";
        cout << "\n\t\tPress any key to continue...";
        getch();
    }
    else
    {
        cout << "\n\t\tQuantity has been updated.";
        cout << "\n\t\tPress any key to continue...";
        getch();
    }
}

// admin function to update price.
void updatePrice(string clothName[], int clothQuantity[], float clothPrice[], int clothIndex)
{
start:
    string update, name;
    int price1;
    int count = 0;

    viewStock(clothName, clothPrice, clothQuantity, clothIndex);
    cout << "\n\t\tEnter the cloth you want to update: ";
    getline(cin, name);

    if (checkString(name) && checkSpace(name))
    {
        update = name;
    }
    else
    {
        cout << "\t\tInvalid cloth!" << endl;
        cout << "\n\t\tPress any key to continue...";
        getch();
        goto start;
    }
    for (int i = 0; i < clothIndex; i++)
    {
        if (update == clothName[i])
        {
            cout << "\n\t\tEnter the updated price: ";
            cin >> price1;
            clothPrice[i] = price1;
            count++;
        }
    }
    if (count == 0)
    {
        cout << "\n\t\tInvalid name";
        cout << "\n\t\tPress any key to continue...";
        getch();
    }
    else
    {
        cout << "\n\t\tPrice has been updated.";
        cout << "\n\t\tPress any key to continue...";
        getch();
    }
}

// admin function to view client.
void viewClients(string username[], string userpassword[], string userrole[], int usercount)
{
    system("cls");
    header();
    cout << "\n\tSignedUp clients";
    cout << "\n\t\tName\t\tPassword" << endl;

    for (int j = 0; j < usercount; j++)
    {
        if (userrole[j] == "client")
        {

            cout << "\t" << username[j] << "\t\t" << userpassword[j] << endl;
        }
    }
    cout << "\n\t\tPress any key to continue...";
    getch();
}

// admin function to remove client.
void deleteClient(string username[], string userpassword[], string userrole[], int &usercount)
{
start:
    string del2, name;
    int count = 0;
    viewClients(username, userpassword, userrole, usercount);
    cout << "\n\n\t\tEnter the client name you want to delete: ";
    cin.ignore();
    getline(cin, name);
    if (checkString(name) && checkSpace(name))
    {
        del2 = name;
    }
    else
    {
        cout << "\t\tInvalid client name!" << endl;
        getch();
        goto start;
    }
    for (int j = 0; j < usercount; j++)
    {
        if (del2 == username[j])
        {
            shiftArrayForClient(username, userpassword, userrole, j, usercount);

            count++;
        }
    }
    if (count == 0)
    {
        cout << "\n\t\tInvalid client name";
    }
    cout << "\n\t\tPress any key to continue...";
    getch();
}

// admin function to update name.
void updateName(string clothName[], int clothQuantity[], float clothPrice[], int clothIndex)
{
start:
    string opt4;
    string name1, name;
    int count = 0;

    viewStock(clothName, clothPrice, clothQuantity, clothIndex);
    cout << "\n\n\t\tEnter the cloth you want to update: ";
    getline(cin, name);
    if (checkString(name) && checkSpace(name))
    {
        opt4 = name;
    }
    else
    {
        cout << "\t\tInvalid cloth!" << endl;
        cout << "\n\t\tPress any key to continue...";
        getch();
        goto start;
    }
    for (int j = 0; j < clothIndex; j++)
    {
        if (opt4 == clothName[j])
        {
            cout << "\n\t\tEnter the updated name: ";
            cin >> name1;
            clothName[j] = name1;
            count++;
        }
    }
    if (count == 0)
    {
        cout << "\n\t\tInvalid name";
        cout << "\n\t\tPress any key to continue...";
        getch();
    }
    else
    {
        cout << "\n\t\tName has been updated.";
        cout << "\n\t\tPress any key to continue...";
        getch();
    }
}

// admin function to offer discounts.
void discount(string clothName[], int clothQuantity[], float clothPrice[], int clothIndex)
{
start:
    string opt5, name;
    float discountPercent;
    float discountAmount;
    int count = 0;

    viewStock(clothName, clothPrice, clothQuantity, clothIndex);
    cout << "\n\t\tEnter the product to which you want to apply discount: ";
    getline(cin, name);
    if (checkString(name) && checkSpace(name))
    {
        opt5 = name;
    }
    else
    {
        cout << "\t\tInvalid cloth!" << endl;
        getch();
        goto start;
    }
    for (int j = 0; j < clothIndex; j++)
    {
        if (clothName[j] == opt5)
        {
            cout << "\t\tEnter the discount percentage: ";
            cin >> discountPercent;

            discountAmount = (clothPrice[j] * discountPercent) / 100;
            clothPrice[j] = clothPrice[j] - discountAmount;
            count++;
        }
    }
    if (count == 0)
    {
        cout << "\n\t\tInvalid cloth";
    }
    cout << "\n\t\tPress any key to continue...";
    getch();
}
// void viewFeedback(string username[], string userpassword[], string userrole[], int usercount)
//----------------------------------------------------------------------------------//

// function to print client menu. and will return option selected by client.
int clientMenu()
{
start:
    string menu;
    int opt2;

    system("cls");
    header();
    cout << "\n\n\tCLIENT MENU:";
    cout << "\n\n\n\t\t1:  View sessions" << endl;
    cout << "\t\t2:  View colors" << endl;
    cout << "\t\t3:  View catagory" << endl;
    cout << "\t\t4:  View types" << endl;
    cout << "\t\t5:  View clothes" << endl;
    cout << "\t\t6:  Add to cart" << endl;
    cout << "\t\t7:  View cart" << endl;
    cout << "\t\t8:  Update quantity in cart" << endl;
    cout << "\t\t9:  Delete from cart" << endl;
    cout << "\t\t10: Buy cart" << endl;
    cout << "\t\t11: Calculate bill" << endl;
    cout << "\t\t12: Select payment method" << endl;

    cout << "\t\t0: Exit" << endl;

    cout << "\n\t\tSelect your option....";
    cin >> menu;
    if (checkInteger(menu) && checkSpace(menu))
    {
        opt2 = stoi(menu);
    }
    else
    {
        cout << "\t\t\tInvalid input!" << endl;
        cout << "\t\t\tPress any key to continue...";
        getch();
        goto start;
    }

    return opt2;
}

// client function to print sessions.
void viewSession()
{
    system("cls");
    header();
    cout << "\n\n\t\tClothes available for the sessions:";
    cout << "\n\n\t\t\tSUMMER";
    cout << "\n\t\t\tMID SUMMER";
    cout << "\n\t\t\tWINTER";
    cout << "\n\t\t\tSPRING";
    cout << "\n\n\t\t\tPress any key to continue...";
    getch();
}

// client function to print colors.
void viewColor()
{
    system("cls");
    header();
    cout << "\n\n\t\tAvailable colors:";
    cout << "\n\n\t\t\tBLACK";
    cout << "\n\t\t\tRED";
    cout << "\n\t\t\tBLUE";
    cout << "\n\t\t\tORANGE";
    cout << "\n\t\t\tPURPLE";
    cout << "\n\t\t\tMAGENTA";
    cout << "\n\t\t\tWHITE";
    cout << "\n\t\t\tROYAL BLACK";
    cout << "\n\t\t\tNAVY BLUE";
    cout << "\n\n\t\t\tPress any key to continue...";
    getch();
}

// client function to print catagories.
void viewCatagory()
{
    system("cls");
    header();
    cout << "\n\n\t\tAvailable catagories:";
    cout << "\n\n\t\t\tMOTHER'S COLLECTION";
    cout << "\n\t\t\tGENTS";
    cout << "\n\t\t\tLADIES";
    cout << "\n\t\t\tBABIES CARE";
    cout << "\n\n\t\t\tPress any key to continue...";
    getch();
}

// client function to print types.
void viewTypes()
{
    system("cls");
    header();
    cout << "\n\n\t\tAvailable types:";
    cout << "\n\n\t\t\tKHADDAR";
    cout << "\n\t\t\tLAWN";
    cout << "\n\t\t\tLINEN";
    cout << "\n\t\t\tCOTTON";
    cout << "\n\t\t\t2020";
    cout << "\n\t\t\tCOTAIL";
    cout << "\n\t\t\tMARINA";
    cout << "\n\t\t\tLATHA";
    cout << "\n\t\t\tDOUBLE HORSE BOSKI(8 pound)";
    cout << "\n\n\t\t\tPress any key to continue...";
    getch();
}

// client function to add a cloth to cart.
void addToCart(string clothName[], float clothPrice[], int clothQuantity[], int clothIndex, string cartName[], float cartPrice[], int cartQuantity[], int &cartIndex)
{
start:
    string name, name2, quantity;
    int checkValidQuantity, quantityIndex;
    int count = 0;
    viewStock(clothName, clothPrice, clothQuantity, clothIndex);
    cout << "\n\n\t\tAdd a cloth to cart: ";
    cin >> name;

    for (int i = 0; i < clothIndex; i++)
    {
        if (name == clothName[i])
        {

            name2 = clothName[i];
            quantityIndex = i;
            count++;
        }
    }
    if (checkCloth(cartName, cartIndex, name2))
    {
        cartName[cartIndex] = name2;

        if (count == 0)
        {
            cout << "\n\t\tInvalid name";
        }
        else
        {
            cout << "\t\tEnter the number of cloths you want to add: ";
            cin >> quantity;
        }
        if (checkInteger(quantity) && checkSpace(quantity))
        {
            checkValidQuantity = stoi(quantity);
        }
        else
        {
            cout << "\n\t\t\tInvalid quantity!" << endl;
            getch();
            goto start;
        }
        if (checkValidQuantity > clothQuantity[quantityIndex])
        {
            cout << "\n\t\tNot enough stock!!";
            cout << "\n\t\tPress any key to continue...";
            getch();

            goto start;
        }
        else
        {
            cartQuantity[cartIndex] = checkValidQuantity;
        }
        cartPrice[cartIndex] = clothPrice[quantityIndex];

        cout << "\n\t\t" << cartName[cartIndex] << " successfully added to your cart.";
        cout << "\n\t\tPress any key to continue...";
        cartIndex++;
        getch();
    }
    else
    {
        cout << "\t\t\tThe cloth is already added.Use update quantity function to add more clothes.";
        cout << "\n\t\t\tPress any key to continue...";
        getch();
    }
}

// client function to view his cart.
void viewCart(string cartName[], float cartPrice[], int cartQuantity[], int cartIndex)
{
    system("cls");
    header();
    cout << "\n\n\tYour cart contains:";
    cout << "\n\n\t\tCloth name\t\tCloth Price\t\tQuantity" << endl;
    for (int i = 0; i < cartIndex; i++)
    {
        if (cartName[i] == "null")
        {
            continue;
        }
        cout << "\t\t" << cartName[i] << "\t\t\t" << cartPrice[i] << "\t\t\t" << cartQuantity[i] << endl;
    }
    cout << "\n\t\tPress any key to continue...";
    getch();
}

// client function to delete a cloth from cart.
void deleteFromCart(string cartName[], float cartPrice[], int cartQuantity[], int cartIndex)
{
start:
    int count = 0;
    string del;
    viewCart(cartName, cartPrice, cartQuantity, cartIndex);
    cout << "\n\n\t\t\tEnter the cloth you want to delete: ";
    cin >> del;

    for (int i = 0; i <= cartIndex; i++)
    {
        if (del == cartName[i])
        {
            cartName[i] = "null";
            count++;
        }
    }
    if (count == 0)
    {
        cout << "\n\t\tInvalid name";
    }
    cout << "\n\t\tPress any key to continue...";
    getch();
}

// client menu to update quantity in cart.
void updateCartQuantity(string cartName[], int cartQuantity[], float cartPrice[], int cartIndex)
{
start:
    string update, name;
    int quantity1;
    int count = 0;

    viewCart(cartName, cartPrice, cartQuantity, cartIndex);
    cout << "\n\t\tEnter the cloth you want to update: ";
    cin >> name;

    if (checkString(name) && checkSpace(name))
    {
        update = name;
    }
    else
    {
        cout << "\t\tInvalid cloth!" << endl;
        cout << "\n\t\tPress any key to continue...";
        getch();
        goto start;
    }
    for (int i = 0; i < cartIndex; i++)
    {
        if (update == cartName[i])
        {
            cout << "\n\t\tEnter the updated quantity: ";
            cin >> quantity1;
            cartQuantity[i] = quantity1;
            count++;
        }
    }
    if (count == 0)
    {
        cout << "\n\t\tInvalid name";
        cout << "\n\t\tPress any key to continue...";
        getch();
    }
    else
    {
        cout << "\n\t\tQuantity has been updated.";
        cout << "\n\t\tPress any key to continue...";
        getch();
    }
}
// client function to buy clothes in his cart.
void buyCart(string clothName[], float clothPrice[], int clothQuantity[], int clothIndex, string cartName[], float cartPrice[], int cartQuantity[], int cartIndex, bool &cartBought)
{
    for (int i = 0; i < cartIndex; i++)
    {
        for (int j = 0; j < clothIndex; j++)
        {
            if (cartName[i] == clothName[j])
            {
                clothQuantity[i]--;
            }
        }
    }
    cout << "\n\n\t\tYou have bought the cart successfully. Now you can calculate bill !!";
    cartBought = true;
    cout << "\n\n\t\tPress any key to continue...";
    getch();
}

// client function to calculate bill.
void calculateBill(string cartName[], float cartPrice[], int cartQuantity[], int cartIndex, string userName[])
{
    system("cls");
    header();
    float lineTotal[100];
    float total = 0;
    int count = 0;
    // cout<<"\n\n\tBill to: "<<userName[]
    cout << "\n\n\tCLOTH NAME\t\tQUANTITY\t\tCOST\t\tLINE TOTAL" << endl
         << endl;
    for (int i = 0; i < cartIndex; i++)
    {
        lineTotal[i] = cartQuantity[i] * cartPrice[i];
        cout << "\t" << cartName[i] << "\t\t" << cartQuantity[i] << "\t\t\t" << cartPrice[i] << "\t\t" << lineTotal[i] << endl;
        count++;
    }
    for (int i = 0; i < count; i++)
    {
        total += lineTotal[i];
    }
    cout << "\n\t\t\t\t\t\t\t\t\tGRAND TOTAL= " << total;
    cout << " \n\n\n\t#THANK YOU FOR BEING OUR VALUED CUSTOMER" << endl;
    cout << "\n\tPress any key to continue...";
    getch();
}

// client function to print payment methods.
void paymentMethod()
{
start:
    system("cls");
    header();
    string jazzCash;
    cout << "\n\n\t\t1: JazzCash" << endl;
    cout << "\t\t2: EasyPaisa" << endl;
    cout << "\t\t3: Bank transfer" << endl;
    cout << "\t\t4: Raast" << endl;
    cout << "\t\t5: Payoneer" << endl;
    cout << "\n\n\t\t\tEnter your option: ";
    cin >> jazzCash;
    if (!checkInteger(jazzCash))
    {
        cout << "\n\t\t\tInvalid option.";
        goto start;
    }
    else
    {
        cout << "\t\tPress any key to continue...";
        getch();
    }
}

// client function to check weather the cloth is already present in cart.
// admin function to check weather the cloth is already present in stock.
bool checkCloth(string clothName[], int clothIndex, string name2)
{
    for (int i = 0; i < clothIndex; i++)
    {
        if (name2 == clothName[i])
        {
            return false;
        }
    }
    return true;
}
void storeUsersInFile(string username[], string userpassword[], string userrole[], int usercount, string path)
{
    fstream file;
    file.open(path, ios::out);
    for (int i = 0; i < usercount; i++)
    {
        file << username[i] << "," << userpassword[i] << "," << userrole[i] << endl;
    }
    getch();
    file.close();
}
// void appendUsreInFile(string username[], string userpassword[], string userrole[], int usercount, string path)
// {
//     fstream file;
//     file.open(path, ios::app);
//     file << username[usercount] << "," << userpassword[usercount] << "," << userrole[usercount] << endl;
//     getch();
//     file.close();
// }
void readUsersFromFile(string username[], string userpassword[], string userrole[], int &usercount)
{
    int i = 0;
    string line;
    fstream file;
    file.open("users.txt", ios::in);
    while (getline(file, line))
    {
        username[i] = getField(line, 1);
        userpassword[i] = getField(line, 2);
        userrole[i] = (getField(line, 3));
        i = i + 1;
    }
    file.close();
    usercount = i;
}
void deleteClientFromFile(string username[], string userpassword[], string userrole[], int &usercount)
{
    deleteClient(username, userpassword, userrole, usercount);
    fstream file;
    string line;
    // file.open("users.txt", ios::in);
    file.open("tempfile.txt", ios::app);
    for (int i = 0; i < usercount; i++)
    {
        file << username[i] << "," << userpassword[i] << "," << userrole[i] << endl;
    }
    file.close();
    // file.close();
    rename("tempfile.txt", "stock.txt");
}
void storeClothInFile(string clothName[], float clothPrice[], int clothQuantity[], int clothIndex, string path)
{
    fstream file;
    file.open(path, ios::out);
    for (int i = 0; i < clothIndex; i++)
    {
        file << clothName[i] << "," << clothPrice[i] << "," << clothQuantity[i] << endl;
    }

    file.close();
}
// void appendClothInFile(string clothName[], float clothPrice[], int clothQuantity[], int clothIndex, string path)
// {
//     fstream file;
//     file.open(path, ios::app);
//     file << clothName[i] << "," << clothPrice[i] << "," << clothQuantity[i] << endl;
//     getch();
//     file.close();
// }
void readClothFromFile(string clothName[], float clothPrice[], int clothQuantity[], int &clothIndex)
{
    string secondField, thirdField;
    int i = 0;
    string line;
    fstream file;
    file.open("stock.txt", ios::in);
    while (getline(file, line))
    {
        secondField = getField(line, 2);
        thirdField = getField(line, 3);
        getline(file, line);
        clothName[i] = getField(line, 1);
        if (!secondField.empty())
        {
            clothPrice[i] = stof(secondField);
        }
        if (!thirdField.empty())
        {
            clothQuantity[i] = stoi(thirdField);
        }
        i = i + 1;
    }
    file.close();
    clothIndex = i;
}
void deleteClothFromFile(string clothName[], int clothQuantity[], float clothPrice[], int &clothIndex)
{
    deleteCloth(clothName, clothQuantity, clothPrice, clothIndex);
    fstream file;
    string line;
    file.open("tempfile.txt", ios::app);
    for (int i = 0; i < clothIndex; i++)
    {
        file << clothName[i] << "," << clothPrice[i] << "," << clothQuantity[i] << endl;
    }
    file.close();
    remove("stock.txt");
    rename("tempfile.txt", "stock.txt");
}
void updateClothQuantityInFile(string clothName[], int clothQuantity[], float clothPrice[], int clothIndex)
{
    updateQuantity(clothName, clothQuantity, clothPrice, clothIndex);
    fstream file;
    string line;
    file.open("tempfile.txt", ios::app);
    for (int i = 0; i < clothIndex; i++)
    {
        file << clothName[i] << "," << clothPrice[i] << "," << clothQuantity[i] << endl;
    }
    file.close();
    remove("stock.txt");
    rename("tempfile.txt", "stock.txt");
}
void updateClothPriceInFile(string clothName[], int clothQuantity[], float clothPrice[], int clothIndex)
{
    updatePrice(clothName, clothQuantity, clothPrice, clothIndex);
    fstream file;
    string line;
    file.open("tempfile.txt", ios::app);
    for (int i = 0; i < clothIndex; i++)
    {
        file << clothName[i] << "," << clothPrice[i] << "," << clothQuantity[i] << endl;
    }
    file.close();
    remove("stock.txt");
    rename("tempfile.txt", "stock.txt");
}
void updateClothNameInFile(string clothName[], int clothQuantity[], float clothPrice[], int clothIndex)
{
    updateName(clothName, clothQuantity, clothPrice, clothIndex);
    fstream file;
    string line;
    file.open("tempfile.txt", ios::app);
    for (int i = 0; i < clothIndex; i++)
    {
        file << clothName[i] << "," << clothPrice[i] << "," << clothQuantity[i] << endl;
    }
    file.close();
    remove("stock.txt");
    rename("tempfile.txt", "stock.txt");
}
string getField(string record, int field)
{
    int commaCount = 1;
    string item = "";
    for (int x = 0; x < record.length(); x++)
    {
        if (record[x] == ',')
        {
            commaCount = commaCount + 1;
        }
        else if (commaCount == field)
        {
            item = item + record[x];
        }
    }
    return item;
}
void shiftArrayForClient(string username[], string userpassword[], string userrole[], int arrCount, int &totalCount)
{
    for (int i = arrCount; i < totalCount; i++)
    {
        username[i] = username[i + 1];

        userpassword[i] = userpassword[i + 1];

        userrole[i] = userrole[i + 1];
    }
    username[totalCount] = "";
    userpassword[totalCount] = "";
    userrole[totalCount] = "";
    totalCount--;
}
void shiftArrayForCloth(string clothName[], int clothQuantity[], float clothPrice[], int arrCount, int &clothIndex)
{
    for (int i = arrCount; i < clothIndex; i++)
    {
        clothName[i] = clothName[i + 1];

        clothQuantity[i] = clothQuantity[i + 1];

        clothPrice[i] = clothPrice[i + 1];
    }
    clothName[clothIndex] = "";
    clothPrice[clothIndex] = 0.0;
    clothPrice[clothIndex] = 0;
    cout << clothIndex;
    clothIndex--;
    cout << clothIndex;
}
