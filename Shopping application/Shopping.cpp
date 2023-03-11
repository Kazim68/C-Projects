#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <fstream>
using namespace std;

// headers, messages, validations etc
void printheader();
void printuserheader();
void main_screen_function();
void printmainscreen();
void menu();
void again();
void welcome();
void continuekey();
int Quantity();
int option(int optcount);
bool integervalidation(string);
bool floatvalidation(string);

// sign in/up functions
void signin();
void signup();

// admin functions
int admin();
void print_admin_brands_option();
void print_admin_staff_menu();
void print_brand_items_to_modify(int i);
void admin_sales();
void admin_discounts();
void deletebrand();
void showproducts();
int printadminbrands();
void showbrandproducts(int i);
void admin_complaints();
void modifybrand();
void addbrand();
void printaccountmenu();
void adminsettings();
void approval();

// employee functions
int employee();
int accountsetting();
int employeeNewOrder();
void allemployees();
void employeeOrderSummary();
void printemployeemenu();
void help();

// customer functions
void customer();
void printbrands();
int printitems(int);
float calculatebill(int);
void showbrands();
void customer_order_table();
int neworder();
int ordertrack();
int payments();
int history();
void complaints();

// data fetching and writing
void savedata();
void loaddata();
void getusercredentials();
void writeusercredentials();
void loadbrands();
void writebrands();
void loaditems();
void writeitems();
void load_brand_item_idx();
void write_brand_item_idx();
void loaditemprice();
void writeitemprice();
void loadorders();
void writeorders();
void loadorderstatus();
void writeorderstatus();
void load_customer_count();
void write_customer_count();
void load_employee_count();
void write_employee_count();
void load_employee_data();
void write_employee_data();
void load_account_requests();
void write_account_requests();
void loadcomplains();
void writecomplains();
void loaddiscount();
void writediscount();

// global array and variable assignments

// order status
bool billstatus[100];     // = {false};    // bill paid status for each order
bool delivered[100];      // = {false};      // has the employee delivered the order
bool finished[100];       // = {false};      // order completed after customer rates the service
bool discountstatus[100]; // = {false}; // checks discount for each order

// arrays for storing indexes of items in brands and their prices
int items[20][20];       // = {{0, 2, 3, 5, -1}, {0, 1, 2, 3, 5, -1}, {2, 3, 5, -1}, {0, 1, 4, -1}, {0, 1, 2, 3, 4, -1}, {0, 1, 2, 3, 4, 5, -1}};
float itemprice[20][20]; // = {{3, 10, 7, 12, -1}, {2, 4, 7, 7, 9, -1}, {12, 10, 15, -1}, {3, 5, 8, -1}, {2, 5, 10, 8, 13, -1}, {4, 6, 15, 12, 20, 18, -1}};

// stores names of brands and products
string brands[20];   //= {"Nike", "Gucci", "Adidas", "Puma", "Levi's", "Ideas"};
string itemname[20]; // = {"Shirt", "Jeans", "Jacket", "Trouser", "Kurta", "Sneaker"};

// stores record of all orders
string orderRecords[20][20]; //= {"-1"}; // {{brand name, item name, price, quantity, brand name, item name, price, quantity}}
int sales[20] = {0};         // sales of each brand

string customercount[20]; // = {"-1"}; // stores name of customer against every order

// sign in arrays
string usernames[100]; // {"kazim", "naruto", "sasuke"};
string passwords[100]; // {"kazim123", "ramen", "itachi"};
string role[100];      // {"Admin", "Customer", "Employee"};

// employee data
string employeeorders[40][40]; // = {{"-1"}}; // {{customer name, ratings, -1}}  // keeps track of orders fulfilled by each employee
string employee_hired[100];    // = {"Hired"}; // keeps track of employee employment status
int rating[100];               // = {0};                  // emloyee service ratings from customers
int salary[100];               // = {500};                // salaries of employees
int employeeordercount[100];   // = {0};      // stores the numbers of orders completed by each individual employee

string new_account[100]; // = {"-1"}; // stores sign up data for admin to approve
string complains[100];   // = {""}; // stores complains/help messages of users for admin to view

float discount = 0.9; // discount constant

// index variables for above arrays
int brandidx = 0, itemidx = 0;
int employeeCountIdx = 1, totalemployees = 0;
int customerOrderCount = 0, customerCountIndex = 0, indextracker = 0, complainidx = 0, profit = 0, users = 0;

// name of current user      discount code set by admin
string current_username = "", discountcode = "";

int main()
{
    loaddata();        // initially loads all the arrays with data
    printmainscreen(); // application starts
}

void customer() // customer option menu handler
{
    system("Color 06");
    int opt = 0;

    while (opt != 7)
    {
        printheader();
        menu();
        opt = option(7);

        if (opt == 1)
        {
            neworder();
        }
        else if (opt == 2)
        {
            ordertrack();
        }
        else if (opt == 3)
        {
            payments();
        }
        else if (opt == 4)
        {
            history();
        }
        else if (opt == 5)
        {
            accountsetting();
        }
        else if (opt == 6)
        {
            complaints();
        }
        else
        {
            break;
        }
    }

    cout << "Thank You for shopping!" << endl;
    Sleep(1000);
    printmainscreen();
}

void complaints() // complaints of customers
{
    string text;
    printheader();
    cout << "Write your reviews & complaints: " << endl;
    getline(cin.ignore(), text);
    complains[complainidx++] = "Customer";
    complains[complainidx++] = current_username;
    complains[complainidx++] = text;
}

void printheader() // prints header of application
{
    system("cls");
    cout << "============================================================================================" << endl;
    cout << "============================================================================================" << endl;
    cout << "          ###########             ####           #############         ###       ###     " << endl;
    cout << "        ###         ###        ###    ###        ###          ###      ###      ###     " << endl;
    cout << "        ###         ###      ###        ###      ###           ###     ###    ###     " << endl;
    cout << "        ###                 ###          ###     ###          ###      ###  ###     " << endl;
    cout << "         ############       ################     ### ##########        ### ###     " << endl;
    cout << "                    ###     ###          ###     ###  ###              ###    ###     " << endl;
    cout << "        ###         ###     ###          ###     ###     ###           ###      ###     " << endl;
    cout << "        ###         ###     ###          ###     ###        ###        ###        ###     " << endl;
    cout << "          ###########       ###          ###     ###         ###       ###         ###     " << endl;
    cout << "============================================================================================" << endl;
    cout << "============================================================================================" << endl
         << endl
         << endl;

    cout << "**********Welcome to SARK Shopping!**********" << endl
         << endl;
}

void menu() // customer menu
{
    cout << "What can we do for you?" << endl
         << endl;
    cout << "1. New Order" << endl;
    cout << "2. Track your Order" << endl;
    cout << "3. Payments" << endl;
    cout << "4. Order History" << endl;
    cout << "5. Account settings" << endl;
    cout << "6. Complains & Reviews" << endl;
    cout << "7. Exit" << endl;
}

int option(int optcount) // takes in option number input by the user
{
    bool found = false;
    string opt;
    cout << "Enter the option number you want to choose: ";
    cin >> opt;
    while (found == false)
    {
        if (integervalidation(opt) == true)
        {
            if (stoi(opt) > 0 && stoi(opt) <= optcount)
            {
                found = true;
                break;
            }
        }
        cout << "Invalid input! Try again: ";
        cin >> opt;
    }

    return stoi(opt);
}

bool integervalidation(string num) // applies integer validation to the value entered by user
{
    string digits = "0123456789";
    for (int i = 0; i < num.length(); i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (digits[j] == num[i])
            {
                break;
            }
            if (j == 9)
            {
                return false;
            }
        }
    }
    return true;
}

bool floatvalidation(string num) // applies float number validation
{
    string digits = "0123456789.";
    for (int i = 0; i < num.length(); i++)
    {
        for (int j = 0; j < 11; j++)
        {
            if (digits[j] == num[i])
            {
                break;
            }
            if (j == 10)
            {
                return false;
            }
        }
    }
    return true;
}

void printbrands() // print names of all brands as an option menu
{
    int count = 0;
    printheader();
    cout << "Select Brand." << endl;
    for (int i = 0; i < brandidx; i++)
    {
        cout << i + 1 << ". " << brands[i] << endl;
        count++;
    }
    cout << count + 1 << ". Back" << endl;
    cout << "If you enter an option twice, the first input will be lost!" << endl;
    int opt = option(count + 1);
    if (opt == count + 1)
    {
        menu();
    }
    else
    {
        printitems(opt - 1);
    }
}

int printitems(int i) // prints items of respective brand for customer to select
{
    printheader();
    int count = 0, opt = 0, c = 0, a = 0;
    int temp[10] = {-1};
    cout << "Brand: " << brands[i] << endl;
    cout << "Sr#.\t\tItem\t\t\t\tPrice" << endl;
    for (int j = 0; items[i][j] != -1; j++)
    {
        cout << j + 1 << "\t\t" << itemname[items[i][j]] << "\t\t\t\t" << itemprice[i][j] << endl;
        count++;
    }
    cout << count + 1 << "\t\tBack/Finalize order" << endl;

    while (opt != count + 1)
    {
        opt = option(count + 1);
        if (opt == count + 1)
        {
            break;
        }
        int quantity = Quantity();
        orderRecords[customerCountIndex][indextracker++] = brands[i];
        orderRecords[customerCountIndex][indextracker++] = itemname[items[i][opt - 1]];
        orderRecords[customerCountIndex][indextracker++] = to_string(itemprice[i][opt - 1]);
        orderRecords[customerCountIndex][indextracker++] = to_string(quantity);
        orderRecords[customerCountIndex][indextracker] = "-1";
    }
    billstatus[customerCountIndex] = false;
    delivered[customerCountIndex] = false;
    finished[customerCountIndex] = false;
    discountstatus[customerCountIndex] = false;

    printbrands();
}

float calculatebill(int idx) // calculates the bill of customer order
{
    float total = 0;
    for (int a = 0; orderRecords[idx][a] != "-1"; a += 4)
    {
        total += stoi(orderRecords[idx][a + 2]) * stoi(orderRecords[idx][a + 3]);
    }
    if (discountstatus[customerCountIndex] == true)
    {
        total *= discount;
    }
    return total;
}

int neworder() // initialize array indexes for customer to place a new order
{
    customerCountIndex = customerOrderCount;
    customercount[customerCountIndex] = current_username;
    customercount[customerCountIndex + 1] = "-1";
    printbrands();
}

int Quantity() // takes in the quantity of selected product
{
    string quantity;
    cout << "Quantity: ";
    cin >> quantity;
    while (!integervalidation(quantity) || stoi(quantity) < 0)
    {
        cout << "Incorrect! Try again: ";
        cin >> quantity;
    }
    return stoi(quantity);
}

void customer_order_table() // prints the reciept of customer order
{
    int tempidx[20] = {-1};
    int i = 0, c = 0, idx = customerCountIndex;
    cout << "Brand\t\t\tItem\t\t\tPrice\t\t\tQuantity" << endl;
    for (int a = 0; orderRecords[idx][a] != "-1"; a += 4)
    {
        cout << orderRecords[idx][a] << "\t\t\t" << orderRecords[idx][a + 1] << "\t\t\t" << orderRecords[idx][a + 2] << "\t\t\t" << orderRecords[idx][a + 3] << endl;
    }
    cout << "Total bill: " << calculatebill(idx) << endl;
}

void continuekey() // to pause the program until user key press
{
    cout << "Press any key to continue: ";
    getch();
}

int ordertrack() // prints order status of customer
{
    printheader();
    if (orderRecords[customerCountIndex][0] == "-1") // in case of no pending order
    {
        cout << "No orders yet." << endl;
        continuekey();
    }
    else
    {
        if (finished[customerCountIndex] == false)
        {
            customer_order_table();
            if (billstatus[customerCountIndex] == false) // if payment is pending
            {
                cout << "Payment is pending..." << endl;
            }
            else
            {
                if (delivered[customerCountIndex] == true) // order has been delivered by employee
                {
                    cout << "Your order has been delivered!" << endl;
                    cout << "Rate our service out of 5: " << endl;
                    for (int i = 1; i <= 5; i++)
                    {
                        cout << i << " Star" << endl;
                    }
                    int rate = option(5), c = 0;
                    rating[employeeCountIdx - 1] += rate;
                    finished[customerCountIndex] = true;
                    for (int i = 0; employeeorders[employeeCountIdx - 1][i] != "-1"; i++)
                    {
                        c++;
                    }
                    employeeorders[employeeCountIdx - 1][c] = current_username;
                    employeeorders[employeeCountIdx - 1][c + 1] = to_string(rate);
                    employeeorders[employeeCountIdx - 1][c + 2] = "-1";
                }
                else // if payment is made but order has not been delivered by employee yet
                {
                    cout << "Order is being shipped!" << endl;
                }
            }
        }
        else // if order has been completed
        {
            cout << "No orders yet!" << endl;
        }
        continuekey();
    }
}

int payments() // payment transaction system for customer
{
    printheader();
    if (orderRecords[customerCountIndex][0] == "-1")
    {
        cout << "No orders yet." << endl;
        continuekey();
        return 0;
    }
    customer_order_table();
    char input;
    string code;
    cout << "Status: ";
    if (billstatus[customerCountIndex] == false)
    {
        cout << "Unpaid!" << endl;
        cout << "Enter discount code: ";
        getline(cin.ignore(), code);
        if (code == discountcode)
        {
            discountstatus[customerCountIndex] = true;
        }
        cout << "Would you like to make the payment now? (y/n): ";
        cin >> input;
        while (input != 'y' && input != 'Y' && input != 'n' && input != 'N')
        {
            cout << "Invalid input! Try again: ";
            cin >> input;
        }
        if (input == 'y' || input == 'Y')
        {
            cout << "Please wait while your transaction is in process..." << endl;
            Sleep(1000);
            cout << "Payment successful!" << endl;
            billstatus[customerCountIndex] = true;
            delivered[customerOrderCount] = false;
            profit += calculatebill(customerCountIndex);
            customerOrderCount++;
        }
    }
    if (billstatus[customerCountIndex] == true)
    {
        cout << "Paid!" << endl;
    }
    continuekey();
}

int history() // order history of customer
{
    printheader();
    if (orderRecords[customerCountIndex][0] == "-1")
    {
        cout << "No orders yet." << endl;
        continuekey();
    }
    else
    {
        int tempidx[20] = {-1};
        int i = 0, c = 0, idx;
        while (customercount[i] != "-1")
        {
            if (customercount[i] == current_username)
            {
                if (finished[i] == true)
                {
                    tempidx[c] = i;
                    c++;
                }
                else
                {
                    cout << "No orders yet." << endl;
                    continuekey();
                    return 0;
                }
            }
            i++;
        }
        cout << "Brand\t\t\tItem\t\t\tPrice\t\t\tQuantity" << endl;
        for (int j = 0; j < c; j++)
        {
            idx = tempidx[j];
            for (int a = 0; orderRecords[idx][a] != "-1"; a += 4)
            {
                cout << orderRecords[idx][a] << "\t\t\t" << orderRecords[idx][a + 1] << "\t\t\t" << orderRecords[idx][a + 2] << "\t\t\t" << orderRecords[idx][a + 3] << endl;
            }
            cout << "Total bill: " << calculatebill(idx) << endl;
        }
        continuekey();
    }
}

int accountsetting() // changing account credentials of customer
{
    printaccountmenu();
    int opt = option(3);
    int i = 0;
    char choice;
    while (i < 100)
    {
        if (usernames[i] == current_username)
        {
            break;
        }
        i++;
    }
    if (opt == 1)
    {
        cout << "Enter new password: ";
        getline(cin.ignore(), passwords[i]);
    }
    else if (opt == 2)
    {
        cout << "Are you sure you want to delete your account? (y/n): ";
        cin >> choice;
        while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
        {
            cout << "Invalid input! Try again: ";
            cin >> choice;
        }
        if (choice == 'y' || choice == 'Y')
        {
            cout << "Deleting your account..." << endl;
            Sleep(1000);
            cout << "Account deleted!" << endl;
            usernames[i] = "";
            passwords[i] = "";
            orderRecords[i][0] = "-1";
            continuekey();
            printmainscreen();
        }
    }
}

bool renamecheck(string name) // check duplicate name during sign up
{
    for (int i = 0; i < users; i++)
    {
        if (usernames[i] == name)
        {
            return true;
        }
    }
    return false;
}

void signup() // sign up -> stores the new user's credentials temporary for admin to approve
{
    string username, password;
    int c = 0;
    system("cls");
    cout << "**************Sign Up!**************\n"
         << endl;
    while (true)
    {
        cout << "Enter username: ";
        cin >> username;
        if (!renamecheck(username))
        {
            break;
        }
        cout << "Username already taken :( Try another one..." << endl;
    }
    cout << "Enter password: ";
    cin >> password;
    cout << "1.Admin" << endl;
    cout << "2.Customer" << endl;
    cout << "3.Employee" << endl;
    cout << "Select your account type..." << endl;
    int opt = option(3);

    while (new_account[c] != "-1")
    {
        c++;
    }
    if (opt == 1)
    {
        new_account[c] = "Admin";
    }
    else if (opt == 2)
    {
        new_account[c] = "Customer";
    }
    else
    {
        new_account[c] = "Employee";
    }
    new_account[c + 1] = username;
    new_account[c + 2] = password;
    new_account[c + 3] = "-1";
    printmainscreen();
}

void printmainscreen() // prints starting screen of login options menu
{
    system("cls");
    system("Color 0B");
    cout << "********************Welcome!******************" << endl;
    cout << "##############################################" << endl;
    cout << "#                  1.Sign in                 #" << endl;
    cout << "#                  2.Sign up                 #" << endl;
    cout << "#                  3.Exit                    #" << endl;
    cout << "##############################################" << endl;
    main_screen_function();
}

void main_screen_function() // functionality of login screen
{
    int opt = option(3);
    cin.ignore();
    if (opt == 1)
    {
        signin();
    }
    else if (opt == 2)
    {
        signup();
    }
    else
    {
        cout << "Exiting..." << endl;
        Sleep(750);
        system("cls");
        savedata();
        exit(0);
    }
}
void welcome() // prompts welcome on screen upon successful sign in
{
    cout << "Welcome!" << endl;
    Sleep(1000);
}

void again() // prompts error message in case of wrong sing in and redirects back to login menu
{
    cout << "Wrong credentials... Redirecting back to menu." << endl;
    Sleep(1500);
    signin();
}

void printuserheader() // user selection upon sign in
{
    system("cls");
    cout << "********************Sign in*******************" << endl;
    cout << "##############################################" << endl;
    cout << "#                  1.Admin                   #" << endl;
    cout << "#                  2.Customer                #" << endl;
    cout << "#                  3.Employee                #" << endl;
    cout << "#                  4.Back                    #" << endl;
    cout << "##############################################" << endl;
}

void signin() // sign validations and calls the function of respective user upon successful sign in
{
    printuserheader();
    int opt = option(4);
    string name, password;

    bool found = false;
    int c = 0;

    if (opt == 4)
    {
        printmainscreen();
    }
    else
    {
        cout << "Enter username: ";
        cin >> name;
        for (int i = 0; i < users; i++)
        {
            if (usernames[i] == name)
            {
                break;
            }
            c++;
        }
        if (c == users)
        {
            again();
        }
        else
        {
            string inputrole;
            cout << "Enter password: ";
            cin >> password;
            if (opt == 1)
            {
                inputrole = "Admin";
            }
            else if (opt == 2)
            {
                inputrole = "Customer";
            }
            else
            {
                inputrole = "Employee";
            }
            if (role[c] == inputrole && passwords[c] == password)
            {
                current_username = name;
                welcome();
                if (inputrole == "Admin")
                {
                    admin();
                }
                else if (inputrole == "Customer")
                {
                    int cust = 0;
                    for (int i = 0; customercount[i] != "-1"; i++)
                    {
                        if (customercount[i] == current_username && finished[i] == false)
                        {
                            customerCountIndex = i;
                            break;
                        }
                    }
                    customer();
                }
                else
                {
                    int e = 0;
                    for (int i = 0; i <= c; i++) // counting employee number
                    {
                        if (role[i] == "Employee")
                        {
                            e++;
                        }
                    }
                    employeeCountIdx = e;
                    if (employee_hired[e - 1] == "Hired")
                    {
                        printemployeemenu();
                    }
                    else
                    {
                        cout << "You are Fired!" << endl;
                        continuekey();
                        printmainscreen();
                    }
                }
            }
            else
            {
                again();
            }
        }
    }
}

void admin_sales() // prints sales record of each brand
{
    system("cls");
    printheader();
    cout << "_____________________________" << endl;
    for (int c = 0; c < 20; c++)
    {
        for (int i = 0; orderRecords[c][i] != "-1"; i += 4)
        {
            for (int j = 0; j < brandidx; j++)
            {
                if (orderRecords[c][i] == brands[j])
                {
                    sales[j]++;
                    break;
                }
            }
        }
    }
    cout << "Brand.\t\tsales." << endl;
    for (int i = 0; i < brandidx; i++)
    {
        cout << brands[i] << "\t\t" << sales[i] << endl;
    }
    continuekey();
    admin();
}

void admin_discounts() // discount menu of admin
{
    system("cls");
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    cout << "1.Change discount code" << endl;
    cout << "2.Change discount ratio" << endl;
    cout << "3.Back" << endl;
    int opt = option(3);
    if (opt == 1)
    {
        cout << "Enter new discount code: " << endl;
        getline(cin.ignore(), discountcode);
        while (discountcode == "")
            cout << "Discount code changed!" << endl;
        continuekey();
        admin();
    }
    else if (opt == 2)
    {
        cout << "Enter new discount value: ";
        cin >> discount;
        while (discount < 0 || discount >= 1)
        {
            cout << "Invalid input! Re-enter: ";
            cin >> discount;
        }
        cout << "Discount changed successfully!" << endl;
        continuekey();
        admin();
    }
    else if (opt == 3)
    {
        admin();
    }
}

void admin_complaints() // compliants menu for admin
{
    system("cls");
    cout << "_____________________________" << endl;
    if (complains[0] == "")
    {
        cout << "No complains." << endl;
    }
    else
    {
        for (int i = 0; complains[i] != ""; i += 3)
        {
            cout << complains[i] << "\t" << complains[i + 1] << endl;
            cout << complains[i + 2] << endl
                 << endl;
        }
    }
    continuekey();
    admin();
}

void approval() // admin approves new account requests of new users
{
    system("cls");
    int c = 0;
    cout << "********************************************" << endl;
    if (new_account[0] == "-1")
    {
        cout << "No pending account requests." << endl;
    }
    else
    {
        for (int i = 0; new_account[i] != "-1"; i += 3)
        {
            cout << c + 1 << ". " << new_account[i] << "\t\t" << new_account[i + 1] << endl;
            c++;
        }
        cout << endl;
        char choice;
        cout << "Approve new sign ups? (y/n): ";
        cin >> choice;
        while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
        {
            cout << "Invalid input! Re-try: ";
            cin >> choice;
        }
        if (choice == 'y' || choice == 'Y')
        {
            for (int i = 0; new_account[i] != "-1"; i += 3)
            {
                role[users] = new_account[i];
                usernames[users] = new_account[i + 1];
                passwords[users] = new_account[i + 2];
                users++;
                new_account[i] = "-1";
                new_account[i + 1] = "-1";
                new_account[i + 2] = "-1";
            }
        }
        else
        {
            for (int i = 0; new_account[i] != "-1"; i += 3)
            {
                new_account[i] = "-1";
                new_account[i + 1] = "-1";
                new_account[i + 2] = "-1";
            }
        }
    }
    continuekey();
    admin();
}

void adminsettings() // account settings of admin
{
    printaccountmenu();
    int opt = option(3);
    int i = 0;
    char choice;
    while (i < 100)
    {
        if (usernames[i] == current_username)
        {
            break;
        }
        i++;
    }
    if (opt == 1)
    {
        cout << "Enter new password: ";
        getline(cin.ignore(), passwords[i]);
    }
    else if (opt == 2)
    {
        cout << "Are you sure you want to delete your account? (y/n): ";
        cin >> choice;
        while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
        {
            cout << "Invalid input! Try again: ";
            cin >> choice;
        }
        if (choice == 'y' || choice == 'Y')
        {
            cout << "Deleting your account..." << endl;
            Sleep(1000);
            cout << "Account deleted!" << endl;
            usernames[i] = "";
            passwords[i] = "";
            continuekey();
            printmainscreen();
        }
    }
    else
    {
        if (role[i] == "Admin")
        {
            admin();
        }
        else // since admin and employee account modification menu is same so we can use the same function
        {
            printemployeemenu();
        }
    }
}

int admin() // admin menu
{
    system("Color 0A");
    printheader();
    cout << "************************************************" << endl;
    cout << "*            1. Brands & Products              *" << endl;
    cout << "*            2. Sales & Profit                 *" << endl;
    cout << "*            3. Discount & Promos              *" << endl;
    cout << "*            4. Staff                          *" << endl;
    cout << "*            5. Complaints                     *" << endl;
    cout << "*            6. Account Approvals              *" << endl;
    cout << "*            7. Account settings               *" << endl;
    cout << "*            8. Exit                           *" << endl;
    cout << "************************************************" << endl;
    int opt = option(8);
    while (opt != 8)
    {
        if (opt == 1)
        {
            print_admin_brands_option();
        }
        else if (opt == 2)
        {
            admin_sales();
        }
        else if (opt == 3)
        {
            admin_discounts();
        }
        else if (opt == 4)
        {
            print_admin_staff_menu();
        }
        else if (opt == 5)
        {
            admin_complaints();
        }
        else if (opt == 6)
        {
            approval();
        }
        else if (opt == 7)
        {
            adminsettings();
        }
    }
    printmainscreen();
}

void printaccountmenu() // account modification menu
{
    system("cls");
    cout << "************************************************" << endl;
    cout << "               1. Change Password" << endl;
    cout << "               2. Remove account" << endl;
    cout << "               3. Back" << endl;
    cout << "************************************************" << endl;
}

void showbrandproducts(int i) // show products of each respective brand to admin
{
    printheader();
    cout << "Brand: " << brands[i] << endl;
    cout << "Sr#.\t\tItem\t\t\t\tPrice" << endl;
    for (int j = 0; items[i][j] != -1; j++)
    {
        cout << j + 1 << "\t\t" << itemname[items[i][j]] << "\t\t\t\t" << itemprice[i][j] << endl;
    }
    continuekey();
    showbrands();
}

int printadminbrands() // prints all the brands as menu for admin
{
    int count = 0;
    printheader();
    cout << "Select Brand." << endl;
    for (int i = 0; i < brandidx; i++)
    {
        cout << i + 1 << ". " << brands[i] << endl;
        count++;
    }
    cout << count + 1 << ". Back" << endl;
    return count;
}

void showbrands() // lets the admin to view products of each brand
{
    int count = printadminbrands();
    cout << "Which Brand's products do you want to see?" << endl;
    int opt = option(count + 1);
    if (opt == count + 1)
    {
        print_admin_brands_option();
    }
    else
    {
        showbrandproducts(opt - 1);
    }
}

void showproducts() // show all available products selling to admin
{
    for (int i = 0; i < itemidx; i++)
    {
        cout << i + 1 << ". " << itemname[i] << endl;
    }
    continuekey();
    print_admin_brands_option();
}

void addbrand() // adds a new brand
{
    string brandname, price;
    int tempitems[20] = {-1};
    float tempprice[20];
    int itemcount = 0;
    int c = 0;
    system("cls");
    cout << "_________________________________________________" << endl
         << endl;
    cout << "                    Add Brand                    " << endl;
    cout << "_________________________________________________" << endl;
    cout << "Enter brand name: ";
    getline(cin.ignore(), brandname);
    cout << "Choose products for the brand..." << endl;
    for (int i = 0; i < itemidx; i++)
    {
        c++;
        cout << i + 1 << ". " << itemname[i] << endl;
    }
    cout << c + 1 << ". Finalize brand/Back" << endl;
    int opt = 0;
    while (opt != c + 1)
    {
        opt = option(c + 1);
        if (opt == c + 1)
        {
            break;
        }
        cout << "Enter price: ";
        getline(cin.ignore(), price);
        while (!integervalidation(price) || stof(price) <= 0)
        {
            cout << "Invalid input! Re-try: ";
            cin >> price;
        }
        tempitems[itemcount] = opt - 1;
        tempprice[itemcount] = stof(price);
        itemcount++;
    }
    if (tempitems[0] == -1)
    {
        print_admin_brands_option();
    }
    else
    {
        tempitems[itemcount] = -1;
        for (int i = 0; tempitems[i] != -1; i++)
        {
            for (int j = i + 1; tempitems[j] != -1; j++)
            {
                if (tempitems[j] < tempitems[i])
                {
                    int temporary = tempitems[j];
                    tempitems[j] = tempitems[i];
                    tempitems[i] = temporary;
                    float temporaryprice = tempprice[j];
                    tempprice[j] = tempprice[i];
                    tempprice[i] = temporaryprice;
                }
            }
        }
        for (int i = 0; tempitems[i] != -1; i++)
        {
            items[brandidx][i] = tempitems[i];
            itemprice[brandidx][i] = tempprice[i];
        }
        items[brandidx][itemcount] = -1;
        brands[brandidx] = brandname;
        brandidx++;
        cout << "Brand successfully created!" << endl;
        continuekey();
        print_admin_brands_option();
    }
}

void deletebrand() // deletes an existing brand
{
    int count = printadminbrands();
    cout << "Select Brand to delete or return back: " << endl;
    int opt = option(count + 1);
    if (opt == count + 1)
    {
        print_admin_brands_option();
    }
    else
    {
        cout << "Do you want to delete brand " << brands[opt - 1] << "? (y/n)" << endl;
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            cout << "Brand Deleted!" << endl;
            for (int i = opt - 1; i <= brandidx; i++)
            {
                brands[i] = brands[i + 1];
            }
            brandidx--;
            continuekey();
            print_admin_brands_option();
        }
    }
}

void print_brand_items_to_modify(int i) // prints products of a specific brand for admin to modify
{
    cout << "Brand: " << brands[i] << endl;
    cout << "Sr#.\t\tItem\t\t\t\tPrice" << endl;
    for (int j = 0; items[i][j] != -1; j++)
    {
        cout << j + 1 << "\t\t" << itemname[items[i][j]] << "\t\t\t\t" << itemprice[i][j] << endl;
    }
}

void modifybrand() // brand modification
{
    int count = printadminbrands();
    cout << "Select Brand to modify..." << endl;
    int opt = option(count + 1);
    if (opt == count + 1)
    {
        print_admin_brands_option();
    }
    else
    {
        int i = opt - 1, c = 0;
        for (int j = 0; items[i][j] != -1; j++)
        {
            c++;
        }
        system("cls");
        cout << "__________________" << endl
             << endl;
        cout << "1. Delete products" << endl;
        cout << "2. Add products   " << endl;
        cout << "3. Change Price   " << endl;
        cout << "4. Back           " << endl;
        cout << "__________________" << endl;
        opt = option(4);
        if (opt == 1)
        {
            print_brand_items_to_modify(i);
            int choice = option(c);
            cout << "Product Deleted!" << endl;
            for (int j = choice - 1; j < c + 1; j++)
            {
                items[i][j] = items[i][j + 1];
                itemprice[i][j] = itemprice[i][j + 1];
            }
            continuekey();
            print_admin_brands_option();
        }
        else if (opt == 2)
        {
            string newproduct;
            string newprice;
            cout << "Enter name of product: ";
            cin >> newproduct;
            cout << "Enter price of product: ";
            cin >> newprice;
            while (!floatvalidation(newprice))
            {
                cout << "incorrect input! Try again: ";
                cin >> newprice;
            }
            cout << endl;
            cout << "Product added successfully!" << endl;
            itemname[itemidx] = newproduct;
            items[i][c] = itemidx;
            items[i][c + 1] = -1;
            itemprice[i][c] = stof(newprice);
            itemprice[i][c + 1] = -1;
            itemidx++;
            continuekey();
            print_admin_brands_option();
        }
        else if (opt == 3)
        {
            print_brand_items_to_modify(i);
            int changeprice = option(c);
            string newprice;
            cout << "Enter new price of product: ";
            getline(cin, newprice);
            while (!floatvalidation(newprice))
            {
                cout << "Invalid price! Re-enter: ";
                getline(cin, newprice);
            }
            itemprice[i][changeprice - 1] = stof(newprice);
            cout << "Successfully changed price!";
            continuekey();
            print_admin_brands_option();
        }
        else if (opt == 4)
        {
            print_admin_brands_option();
        }
    }
}

void print_admin_brands_option() // prints and controls brands and products menu for admin
{
    system("cls");
    cout << "************************************************" << endl;
    cout << "*              1. Show Brands                  *" << endl;
    cout << "*              2. Show Products                *" << endl;
    cout << "*              3. Add Brand                    *" << endl;
    cout << "*              4. Delete Brand                 *" << endl;
    cout << "*              5. Modify Brand                 *" << endl;
    cout << "*              6. Back                         *" << endl;
    cout << "************************************************" << endl;

    int opt = option(6);
    while (opt != 6)
    {
        if (opt == 1)
        {
            showbrands();
        }
        else if (opt == 2)
        {
            showproducts();
        }
        else if (opt == 3)
        {
            addbrand();
        }
        else if (opt == 4)
        {
            deletebrand();
        }
        else if (opt == 5)
        {
            modifybrand();
        }
    }
    if (opt == 6)
    {
        admin();
    }
}

void print_admin_staff_menu() // admin can view all the staff members and can make changes to them such as fire or change thire salary
{
    system("cls");
    int c = 0, a = 0;
    float totalratings = 0;

    for (int i = 0; employeeorders[employeeCountIdx - 1][i] != "-1"; i += 2)
    {
        a++;
        totalratings += stoi(employeeorders[employeeCountIdx - 1][i + 1]);
    }

    cout << "*******************************************************************" << endl;
    cout << "  Name             Status          Ratings         Salaries($)     " << endl;
    for (int i = 0; i < 100; i++)
    {
        if (role[i] == "Employee")
        {
            cout << c + 1 << ". " << usernames[i] << "\t\t" << employee_hired[c] << "\t\t";
            if (employeeordercount[c] == 0)
            {
                cout << totalratings / 1;
            }
            else
            {
                cout << totalratings / a;
            }
            cout << "\t\t" << salary[c] << endl;
            c++;
        }
    }
    cout << "*******************************************************************" << endl;
    cout << endl;
    cout << "                         1. Modify employee" << endl;
    cout << "                         2. Go back" << endl
         << endl;
    int opt = option(2);
    if (opt == 1)
    {
        cout << "Select employee: " << endl;
        int selection = option(c + 1);
        cout << "1. Fire employee" << endl;
        cout << "2. Change Salary" << endl;
        opt = option(2);
        if (opt == 1)
        {
            employee_hired[selection - 1] = "Fired";
            salary[selection - 1] = 0;
            rating[selection - 1] = 0;
            cout << "Employee fired!" << endl;
            continuekey();
            print_admin_staff_menu();
        }
        else if (opt == 2)
        {
            int newsalary;
            cout << "Enter new salary: ";
            cin >> newsalary;
            while (newsalary <= 0 || integervalidation(to_string(newsalary)) == false)
            {
                cout << "Invalid input! Re-enter: ";
                cin >> newsalary;
            }
            salary[selection - 1] = newsalary;
            cout << "Salary changed successfully!" << endl;
            continuekey();
            print_admin_staff_menu();
        }
    }
    admin();
}

void printemployeemenu() // prints menu of employee
{
    system("Color 0C");
    printheader();
    cout << "******************************************************" << endl;
    cout << "*                1. New Orders                       *" << endl;
    cout << "*                2. Summary                          *" << endl;
    cout << "*                3. Account Settings                 *" << endl;
    cout << "*                4. Help                             *" << endl;
    cout << "*                5. Back                             *" << endl;
    cout << "******************************************************" << endl;
    employee();
}

void help() // emplpoyee help or complaints functionality for employee
{
    string text;
    printheader();
    cout << "Write your problem here: " << endl;
    getline(cin.ignore(), text);
    complains[complainidx++] = "Employee";
    complains[complainidx++] = current_username;
    complains[complainidx++] = text;
    continuekey();
    printemployeemenu();
}

int employeeNewOrder() // allows an employee to see and deliver a new order placed by any customer
{
    system("cls");
    int c = 0;
    int temp[customerOrderCount] = {-1};
    for (int i = 0; i < customerOrderCount; i++)
    {
        if (delivered[i] == false && billstatus[i] == true)
        {
            cout << "Brand\t\t\tItem\t\t\tPrice\t\t\tQuantity" << endl;
            for (int a = 0; orderRecords[i][a] != "-1"; a += 4)
            {
                cout << orderRecords[i][a] << "\t\t\t" << orderRecords[i][a + 1] << "\t\t\t" << orderRecords[i][a + 2] << "\t\t\t" << orderRecords[i][a + 3] << endl;
            }
            temp[c] = i;
            c++;
        }
    }
    if (temp[0] == -1)
    {
        cout << "No orders due!" << endl;
    }
    else
    {
        temp[c] = -1;
        char choice;
        cout << "Deliver orders? (y/n): ";
        cin >> choice;
        while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
        {
            cout << "Incorrect choice! Try again: ";
            cin >> choice;
        }
        if (choice == 'y' || choice == 'Y')
        {
            cout << "Orders delivered successfully!" << endl;
            for (int i = 0; i <= c; i++)
            {
                delivered[temp[i]] = true;
                employeeordercount[employeeCountIdx]++;
            }
        }
    }
    continuekey();
    printemployeemenu();
}

void employeeOrderSummary() // employee can see their order history and overall ratings
{
    system("cls");
    int c = 0;
    float totalratings = 0;
    cout << "**************************************" << endl;
    cout << "Name of customer whose order fulfilled" << endl;
    for (int i = 0; employeeorders[employeeCountIdx - 1][i] != "-1"; i += 2)
    {
        cout << c + 1 << ". " << employeeorders[employeeCountIdx - 1][i] << "\t\t" << employeeorders[employeeCountIdx - 1][i + 1] << endl;
        c++;
        totalratings += stoi(employeeorders[employeeCountIdx - 1][i + 1]);
    }
    cout << "**************************************" << endl;
    cout << endl;
    cout << "Total orders: " << c << "\t\t"
         << "Overall Ratings: " << totalratings / c << endl;
    continuekey();
    printemployeemenu();
}

int employee() // employee functionality controls
{
    int opt = option(5);
    while (opt != 5)
    {
        if (opt == 1)
        {
            employeeNewOrder();
        }
        else if (opt == 2)
        {
            employeeOrderSummary();
        }
        else if (opt == 3)
        {
            adminsettings();
        }
        else if (opt == 4)
        {
            help();
        }
    }
    printmainscreen();
}

void allemployees()
{
    for (int i = 0; i < users; i++)
    {
        if (role[i] == "Employee")
        {
            totalemployees++;
        }
    }
}

void loaddata()
{
    allemployees();
    getusercredentials();
    loadbrands();
    load_brand_item_idx();
    loaditemprice();
    loadorderstatus();
    load_customer_count();
    loadorders();
    load_employee_count();
    load_employee_data();
    load_account_requests();
    loadcomplains();
}

void savedata()
{
    writeusercredentials();
    writebrands();
    write_brand_item_idx();
    writeitemprice();
    writeorderstatus();
    write_customer_count();
    writeorders();
    write_employee_count();
    write_employee_data();
    write_account_requests();
    writecomplains();
}

void getusercredentials() // loads user credentials from file into arrays
{
    string comma;
    fstream file;
    file.open("usercredentials.txt", ios::in);
    while (!file.eof())
    {
        file >> usernames[users];
        file >> comma;
        file >> passwords[users];
        file >> comma;
        file >> role[users];
        users++;
    }
    file.close();
}

void writeusercredentials() // writes users credentials so that any new users or modifications are added
{
    string comma = " , ";
    fstream file;
    file.open("usercredentials.txt", ios::out);
    for (int i = 0; i < users - 1; i++)
    {
        file << usernames[i];
        file << comma;
        file << passwords[i];
        file << comma;
        file << role[i];
        file << "\n";
    }
    file.close();
}

void loadbrands() // loads brands from file into array
{
    fstream file;
    file.open("brands.txt", ios::in);
    while (!file.eof())
    {
        getline(file, brands[brandidx]);
        brandidx++;
    }
    file.close();
    brandidx--;
    loaditems();
}

void writebrands() // writes brand names for any additions and modifications
{
    fstream file;
    file.open("brands.txt", ios::out);
    for (int i = 0; i < brandidx; i++)
    {
        file << brands[i];
        file << "\n";
    }
    file.close();
    writeitems();
}

void loaditems() // load items of brands
{
    fstream file;
    file.open("items.txt", ios::in);
    while (!file.eof())
    {
        getline(file, itemname[itemidx]);
        itemidx++;
    }
    file.close();
    itemidx--;
}

void writeitems() // writes item names for any additions and modifications
{
    fstream file;
    file.open("items.txt", ios::out);
    for (int i = 0; i < itemidx; i++)
    {
        file << itemname[i];
        file << "\n";
    }
    file.close();
}

void load_brand_item_idx() // loads indexes of items of each respective brand
{
    // append in array and when the variable has value -1 increment idx of array
    bool found;
    int j = 0;
    string comma, value = "";
    fstream file;
    file.open("itemsidx.txt", ios::in);
    for (int i = 0; i < brandidx; i++)
    {
        found = false;
        j = 0;
        while (found == false)
        {
            file >> value;
            items[i][j] = stoi(value);
            if (value == "-1")
            {
                found = true;
            }
            else
            {
                file >> comma;
            }
            j++;
        }
    }
    file.close();
}

void write_brand_item_idx() // writes indexes of brand items for any modifications
{
    // write from array and when value at particular index reaches -1 make a new line in file
    int c;
    string comma = " , ";
    fstream file;
    file.open("itemsidx.txt", ios::out);
    for (int i = 0; i < brandidx; i++)
    {
        c = 0;
        while (items[i][c] != -1)
        {
            file << items[i][c];
            file << comma;
            c++;
        }
        file << items[i][c];
        file << "\n";
    }
    file.close();
}

void loaditemprice() // loads prices of respective brand items into arrays
{
    bool found;
    int j = 0;
    string comma, value = "";
    fstream file;
    file.open("itemprice.txt", ios::in);
    for (int i = 0; i < brandidx; i++)
    {
        found = false;
        j = 0;
        while (found == false)
        {
            file >> value;
            itemprice[i][j] = stof(value);
            if (value == "-1")
            {
                found = true;
            }
            else
            {
                file >> comma;
            }
            j++;
        }
    }
    file.close();
}

void writeitemprice() // write prices of brand items into file
{
    int c;
    string comma = " , ";
    fstream file;
    file.open("itemprice.txt", ios::out);
    for (int i = 0; i < brandidx; i++)
    {
        c = 0;
        while (itemprice[i][c] != -1)
        {
            file << itemprice[i][c];
            file << comma;
            c++;
        }
        file << itemprice[i][c];
        file << "\n";
    }
    file.close();
}

void loadorders() // load order records into array
{
    bool found;
    int j = 0;
    string comma, value = "";
    fstream file;
    file.open("orders.txt", ios::in);
    for (int i = 0; i <= customerOrderCount; i++)
    {
        found = false;
        j = 0;
        while (found == false)
        {
            file >> value;
            orderRecords[i][j] = value;
            if (value == "-1")
            {
                found = true;
            }
            else
            {
                file >> comma;
            }
            j++;
        }
    }
    file.close();
}

void writeorders() // save order records in file
{
    int c;
    string comma = " , ";
    fstream file;
    file.open("orders.txt", ios::out);
    for (int i = 0; i <= customerOrderCount; i++)
    {
        c = 0;
        while (orderRecords[i][c] != "-1")
        {
            file << orderRecords[i][c];
            file << comma;
            c++;
        }
        file << orderRecords[i][c];
        file << "\n";
    }
    file << "-1"
         << "\n";
    file.close();
}

void loadorderstatus() // loads status of order such as bill and delivery
{
    // bill status         delivery        finished         discount status
    string comma, billvalue, delivery, finish, discount_status;
    fstream file;
    file.open("orderstatus.txt", ios::in);
    while (!file.eof())
    {
        file >> billvalue;
        file >> comma;
        file >> delivery;
        file >> comma;
        file >> finish;
        file >> comma;
        file >> discount_status;
        if (billvalue == "1")
        {
            billstatus[customerOrderCount] = true;
        }
        else
        {
            billstatus[customerOrderCount] = false;
        }
        if (delivery == "1")
        {
            delivered[customerOrderCount] = true;
        }
        else
        {
            delivered[customerOrderCount] = false;
        }
        if (finish == "1")
        {
            finished[customerOrderCount] = true;
        }
        else
        {
            finished[customerOrderCount] = false;
        }
        if (discount_status == "1")
        {
            discountstatus[customerOrderCount] = true;
        }
        else
        {
            discountstatus[customerOrderCount] = false;
        }
        customerOrderCount++;
    }
    file.close();
    customerOrderCount--;
}

void writeorderstatus() // writes order status in file
{
    // bill status         delivery        finished         discount status
    string comma = " , ";
    fstream file;
    file.open("orderstatus.txt", ios::out);
    for (int i = 0; i < customerOrderCount; i++)
    {
        file << billstatus[i];
        file << comma;
        file << delivered[i];
        file << comma;
        file << finished[i];
        file << comma;
        file << discountstatus[i];
        file << "\n";
    }
    file.close();
}

void load_customer_count() // loads customer names into customer count array for tracking orders
{
    bool found = false;
    int c = 0;
    string comma, data = "";
    fstream file;
    file.open("customer_count.txt", ios::in);
    while (!found)
    {
        file >> data;
        customercount[c] = data;
        if (data == "-1")
        {
            found = true;
        }
        else
        {
            file >> comma;
        }
        c++;
    }
    file.close();
}

void write_customer_count() // saves the customer count array in a file
{
    int c = 0;
    string comma = " , ", data = "";
    fstream file;
    file.open("customer_count.txt", ios::out);
    for (int i = 0; i <= customerCountIndex; i++)
    {
        file << customercount[i];
        file << comma;
        c++;
    }
    file << customercount[c];
    file << "\n";
    file.close();
}

void load_employee_count() // loads employee order data of each employee
{
    bool found;
    int j = 0;
    string comma, value = "";
    fstream file;
    file.open("employee_count.txt", ios::in);
    for (int i = 0; i <= totalemployees; i++)
    {
        found = false;
        j = 0;
        while (found == false)
        {
            file >> value;
            employeeorders[i][j] = value;
            if (value == "-1")
            {
                found = true;
            }
            else
            {
                file >> comma;
            }
            j++;
        }
    }
    file.close();
}

void write_employee_count() // saves employee order data
{
    int c = 0;
    string comma = " , ", data = "";
    fstream file;
    file.open("employee_count.txt", ios::out);
    for (int i = 0; i <= totalemployees; i++)
    {
        c = 0;
        while (employeeorders[i][c] != "-1")
        {
            file << employeeorders[i][c];
            file << comma;
            c++;
        }
        file << employeeorders[i][c];
        file << "\n";
    }
    file << "-1";
    file << "\n";
    file.close();
}

void load_employee_data() // loads employee arrays such as their employent status and ratings
{
    // hired        rating      salary      ordercount
    string comma, rate, pay, ordcount;
    fstream file;
    file.open("employee_data.txt", ios::in);
    for (int i = 0; i <= totalemployees; i++)
    {
        file >> employee_hired[i];
        file >> comma;
        file >> rate;
        rating[i] = stoi(rate);
        file >> comma;
        file >> pay;
        salary[i] = stoi(pay);
        file >> comma;
        file >> ordcount;
        employeeordercount[i] = stoi(ordcount);
    }
    file.close();
}

void write_employee_data() // stores employee arrays data
{
    // hired       rating       salary      ordercount
    string comma = " , ";
    fstream file;
    file.open("employee_data.txt", ios::out);
    for (int i = 0; i <= totalemployees; i++)
    {
        file << employee_hired[i];
        file << comma;
        file << rating[i];
        file << comma;
        file << salary[i];
        file << comma;
        file << employeeordercount[i];
        file << "\n";
    }
    file.close();
}

void load_account_requests() // loads all new account requests data
{
    bool found = false;
    int c = 0;
    string comma, value;
    fstream file;
    file.open("account_requests.txt", ios::in);
    while (!found)
    {
        file >> value;
        new_account[c] = value;
        if (value == "-1")
        {
            found = true;
        }
        else
        {
            file >> comma;
        }
        c++;
    }
    file.close();
}

void write_account_requests() // stores all new account requests data
{
    string comma = " , ";
    fstream file;
    file.open("account_requests.txt", ios::out);
    for (int i = 0; new_account[i] != "-1"; i += 3)
    {
        file << new_account[i];
        file << comma;
        file << new_account[i + 1];
        file << comma;
        file << new_account[i + 2];
        file << comma;
        file << "\n";
    }
    file << "-1";
    file.close();
}

void loadcomplains() // loads all the complains
{
    fstream file;
    file.open("complains.txt", ios::in);
    while (!file.eof())
    {
        getline(file, complains[complainidx]);
        complainidx++;
    }
    complainidx--;
}

void writecomplains() // stores all the complains
{
    string newline = "\n";
    fstream file;
    file.open("complains.txt", ios::out);
    for (int i = 0; i < complainidx; i++)
    {
        file << complains[i];
        file << newline;
    }
    file.close();
}

void loaddiscount() // loads discount value and code
{
    string comma, value;
    fstream file;
    file.open("discount.txt", ios::in);
    file >> value;
    discount = stof(value);
    file >> comma;
    file >> discountcode;
    file.close();
}

void writediscount() // stores discount value and code
{
    string comma = " , ";
    fstream file;
    file.open("discount.txt", ios::out);
    file << discount;
    file << comma;
    file << discountcode;
    file.close();
}