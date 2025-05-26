#include <iostream>
#include <string>
using namespace std;

// Person class to store basic personal information
class Person {
private:
    string FirstName, lastName, NationalID, gender;
    int BirthYear;
public:
    // Constructor for initializing Person attributes
    Person(string firstN = "", string lastN = "", string nationalid = "", int birthyear = 0, string g = "")
            : FirstName(firstN), lastName(lastN), NationalID(nationalid), BirthYear(birthyear), gender(g) {}

    // Virtual destructor for proper cleanup in inheritance
    virtual ~Person() {}

    // Virtual function to display person information
    virtual void showInfo() const {
        cout << "Name: " << FirstName << " " << lastName << endl;
        cout << "National ID: " << NationalID << endl;
        cout << "Birth Year: " << BirthYear << endl;
        cout << "Gender: " << gender << endl;
    }
    // Getter for national ID
    string getNationalID() const { return NationalID; }
};
// Customer class, inherits from Person, adds customer-specific details
class Customer : public Person {
private:
    string customerID, Province, city;
public:
    // Constructor for initializing Customer attributes
    Customer(string customerid = "", string firstN = "", string lastN = "", string nationaid = "", int birthyear = 0, string g = "",
             string province = "", string cty = "")
            : Person(firstN, lastN, nationaid, birthyear, g), customerID(customerid), Province(province), city(city) {}

    // Destructor for cleanup
    ~Customer() {}

    // Override showInfo to display customer-specific information
    void showInfo() const override {
        cout << "<----- Customer Info ----->" << endl;
        Person::showInfo();
        cout << "Customer Code: " << customerID << endl;
        cout << "Province: " << Province << endl;
        cout << "City: " << city << endl;
    }

    // Getter for customer ID
    string getCustomerID() const { return customerID; }
};

// Product class to store product details
class Product {
private:
    string ProductID, Name, Brand;
    double Price, Weight;
public:
    // Constructor for initializing Product attributes
    Product(string productid = "", string name = "", double price = 0, string brand = "", double weight = 0)
            : ProductID(productid), Name(name), Price(price), Brand(brand), Weight(weight) {}

    // Destructor for cleanup
    ~Product() {}

    // Display product information
    void showInfo() const {
        cout << "Product Info:" << endl;
        cout << "Product ID: " << ProductID << endl;
        cout << "Name: " << Name << endl;
        cout << "Price: " << Price << endl;
        cout << "Brand: " << Brand << endl;
        cout << "Weight: " << Weight << " kg" << endl;
    }

    // Getters for product ID and price
    string getProductID() const { return ProductID; }
    double getPrice() const { return Price; }
};

// Dealer class to store dealer information
class Dealer {
private:
    string DealerID, Name, EconomicCode, OwnerName, Province, City;
    int EstablishmentYear;
public:
    // Constructor for initializing Dealer attributes
    Dealer(string dealerid = "", string name = "", int Esyear = 0, string ecocode = "", string ownername = "", string province = "",
           string city = "")
            : DealerID(dealerid), Name(name), EstablishmentYear(Esyear), EconomicCode(ecocode), OwnerName(ownername), Province(province),
              City(city) {}

    // Destructor for cleanup
    ~Dealer() {}

    // Display dealer information
    void showInfo() const {
        cout << "Dealer Info:" << endl;
        cout << "Dealer ID: " << DealerID << endl;
        cout << "Name: " << Name << endl;
        cout << "Year Established: " << EstablishmentYear << endl;
        cout << "Economic Code: " << EconomicCode << endl;
        cout << "Owner: " << OwnerName << endl;
        cout << "Province: " << Province << endl;
        cout << "City: " << City << endl;
    }

    // Getter for dealer ID
    string getDealerID() const { return DealerID; }
};
// Purchase class to store purchase details
class Purchase {
public:
    Customer *customer;
    Product *product;
    Dealer *dealer;
    int quantity;
    string purchaseDate;

    // Display purchase information
    void showInfo() const {
        cout << "<----Purchase Info---->" << endl;
        customer->showInfo();
        product->showInfo();
        dealer->showInfo();
        cout << "Quantity: " << quantity << endl;
        cout << "Purchase Date: " << purchaseDate << endl;
    }
};
// Global arrays to store products, customers, dealers, and purchases
Product *products[100] = {nullptr};
int productCount = 0;
Customer *customers[100] = {nullptr};
int customerCount = 0;
Dealer *dealers[100] = {nullptr};
int dealerCount = 0;
Purchase *purchases[100] = {nullptr};
int purchaseCount = 0;

// Find product birthyear ID, returns index or -1 if not found
int findProduct(const string &productid) {
    for (int i = 0; i < productCount; i++)
        if (products[i] && products[i]->getProductID() == productid) return i;
    return -1;
}

// Find customer birthyear national ID, returns index or -1 if not found
int findCustomer(const string &nationalid) {
    for (int i = 0; i < customerCount; i++)
        if (customers[i] && customers[i]->getNationalID() == nationalid) return i;
    return -1;
}

// Find dealer birthyear ID, returns index or -1 if not found
int findDealer(const string &dealerid) {
    for (int i = 0; i < dealerCount; i++)
        if (dealers[i] && dealers[i]->getDealerID() == dealerid) return i;
    return -1;
}

// Validate date format (YYYY/MM/DD)
bool validDate(const string &d) {
    return d.size() == 10 && d[4] == '/' && d[7] == '/';
}

// Add a new product to the system
void addProduct() {
    if (productCount >= 100) {
        cout << " You Cannot add more products." << endl;
        return;
    }
    string productid, name, brand;
    double price, weight;
    cout << "Enter Product ID: "; cin >> productid;
    if (findProduct(productid) != -1) {
        cout << "Product ID already exists." << endl;
        return;
    }
    cout << "Enter Product Name: "; cin >> name;
    cout << "Enter Product Brand: "; cin >> brand;
    do {
        cout << "Enter Product Price: ";
        cin >> price;
        if (price <= 0)
            cout << "Error! Price must be positive.\n";
    } while (price <= 0);
    do {
        cout << "Enter Product Weight(kg): ";
        cin >> weight;
        if (weight <= 0)
            cout << "Error! Weight must be positive.\n";
    } while (weight <= 0);
    products[productCount++] = new Product(productid, name, price, brand, weight);
    cout << "Product added successfully." << endl;
}

// Remove a product and associated purchases
void removeProduct() {
    string productid;
    cout << "Enter Product ID to remove: "; cin >> productid;
    int index = findProduct(productid);
    if (index == -1) {
        cout << "Product not found." << endl;
        return;
    }
    delete products[index];
    for (int i = index; i < productCount - 1; i++) {
        products[i] = products[i + 1];
    }
    products[--productCount] = nullptr;
    for (int i = 0; i < purchaseCount;) {
        if (purchases[i]->product->getProductID() ==productid) {
            delete purchases[i];
            for (int j = i; j < purchaseCount - 1; j++) {
                purchases[j] = purchases[j + 1];
            }
            purchases[--purchaseCount] = nullptr;
        } else i++;
    }
    cout << "Product and related purchases removed." << endl;
}

// Add a new customer to the system
void addCustomer() {
    if (customerCount >= 100) {
        cout << "Cannot add more customers." << endl;
        return;
    }
    string nationalid, firstN, lastN, customerid, gender, province, city;
    int birthYr;
    cout << "Enter National ID: "; cin >> nationalid;
    if (findCustomer(nationalid) != -1) {
        cout << "Customer with this nationalID already exists." << endl;
        return;
    }
    cout << "Enter First Name: "; cin >> firstN;
    cout << "Enter Last Name: "; cin >> lastN;
    cout << "Enter CustomerID: "<<endl; cin >> customerid;
    cout << "Enter Gender: "; cin >> gender;
    do {
        cout << "Enter Birth Year: "; cin >> birthYr;
        if (birthYr <= 0)
            cout << "Error! Invalid birth year.\n";
    } while (birthYr <= 0);
    cout << "Enter Province: "; cin >> province;
    cout << "Enter City: "; cin >> city;
    customers[customerCount++] = new Customer(customerid, firstN, lastN, nationalid, birthYr, gender, province, city);
    cout << "Customer added successfully." << endl;
}

// Remove a customer and associated purchases
void removeCustomer() {
    string nationalid;
    cout << "Enter National ID of customer to remove: "; cin >> nationalid;
    int index = findCustomer(nationalid);
    if (index == -1) {
        cout << "Customer not found." << endl;
        return;
    }
    delete customers[index];
    for (int i = index; i < customerCount - 1; i++) {
        customers[i] = customers[i + 1];
    }
    customers[--customerCount] = nullptr;
    for (int i = 0; i < purchaseCount;) {
        if (purchases[i]->customer->getNationalID() == nationalid) {
            delete purchases[i];
            for (int j = i; j < purchaseCount - 1; j++) {
                purchases[j] = purchases[j + 1];
            }
            purchases[--purchaseCount] = nullptr;
        } else i++;
    }
    cout << "Customer and related purchases removed." << endl;
}

// Add a new dealer to the system
void addDealer() {
    if (dealerCount >= 100) {
        cout << "Cannot add more dealers." << endl;
        return;
    }
    string dealerid, name, eco, owner, prov, city;
    int year;
    cout << "Enter Dealer ID: "; cin >> dealerid;
    if (findDealer(dealerid) != -1) {
        cout << "Dealer ID already exists." << endl;
        return;}

    cout << "Enter Name: "; cin >> name;
    do {
        cout << "Enter Establishment Year: "; cin >> year;
        if (year <= 0)
            cout << "Error! Invalid Establishment Year.\n";
    } while (year <= 0);
    cout << "Enter Economic Code: "; cin >> eco;
    cout << "Enter Owner Name: "; cin >> owner;
    cout << "Enter Province: "; cin >> prov;
    cout << "Enter City: "; cin >> city;
    dealers[dealerCount++] = new Dealer(dealerid, name, year, eco, owner, prov, city);
    cout << "Dealer added successfully." << endl;
}
// Remove a dealer and associated purchases
void removeDealer() {
    string id;
    cout << "Enter Dealer ID to remove: "; cin >> id;
    int index = findDealer(id);
    if (index == -1) {
        cout << "Dealer not found." << endl;
        return;
    }
    delete dealers[index];
    for (int i = index; i < dealerCount - 1; i++) {
        dealers[i] = dealers[i + 1];
    }
    dealers[--dealerCount] = nullptr;
    for (int i = 0; i < purchaseCount;) {
        if (purchases[i]->dealer->getDealerID() == id) {
            delete purchases[i];
            for (int j = i; j < purchaseCount - 1; j++) {
                purchases[j] = purchases[j + 1];
            }
            purchases[--purchaseCount] = nullptr;
        } else i++;
    }
    cout << "Dealer and related purchases removed." << endl;
}
// Record a new purchase
void recordPurchase() {
    string nationalid, productid, dealerid, date;
    int qty;
    cout << "Enter Customer National ID: "; cin >> nationalid;
    int customerni = findCustomer(nationalid);
    if (customerni == -1) {
        cout << "Customer not found." << endl;
        return;
    }
    cout << "Enter Product ID: "; cin >> productid;
    int pi = findProduct(productid);
    if (pi == -1) {
        cout << "Product not found." << endl;
        return;
    }
    cout << "Enter Dealer ID: "; cin >> dealerid;
    int di = findDealer(dealerid);
    if (di == -1) {
        cout << "Dealer not found." << endl;
        return;
    }
        do {
            cout << "Enter Quantity: "; cin >> qty;
            if (qty <= 0)
                cout << "Error! Quantity must be positive.\n";
        } while (qty <= 0);

    cout << "Enter Purchase Date (YYYY/MM/DD): "; cin >> date;
    if (!validDate(date)) {
        cout << "Invalid date format." << endl;
        return;
    }
    purchases[purchaseCount++] = new Purchase{customers[customerni], products[pi], dealers[di], qty, date};
    cout << "Purchase recorded successfully." << endl;
}

// Calculate total purchase amount for a specific customer
void totalPurchaseOfCustomer() {
    string nationalid;
    cout << "Enter Customer National ID: "; cin >> nationalid;
    bool found = false;
    double total = 0;
    for (int i = 0; i < purchaseCount; i++) {
        if (purchases[i]->customer->getNationalID() == nationalid) {
            found = true;
            total += purchases[i]->quantity * purchases[i]->product->getPrice();
        }
    }
    if (found) cout << "Total purchase amount: " << total << endl;
    else cout << "No purchases found for this customer." << endl;
}

// List customers who purchased a specific product
void listCustomersOfProduct() {
    string productid;
    cout << "Enter Product ID: "; cin >> productid;
    bool any = false;
    cout << "***** Customers who bought product " << productid << " *****" << endl;
    for (int i = 0; i < purchaseCount; i++) {
        if (purchases[i]->product->getProductID() == productid) {
            purchases[i]->customer->showInfo();
            any = true;
        }
    }
    if (!any) cout << "No customers found for this product." << endl;
}

// List products sold birthyear a specific dealer
void listProductsOfDealer() {
    string dealerid;
    cout << "Enter Dealer ID: "; cin >> dealerid;
    bool any = false;
    cout << "<----Products sold birthyear dealer " << dealerid << "---->" << endl;
    for (int i = 0; i < purchaseCount; i++) {
        if (purchases[i]->dealer->getDealerID() == dealerid) {
            purchases[i]->product->showInfo();
            any = true;
        }
    }
    if (!any) cout << "No products found for this dealer." << endl;
}

// Display total units sold for a specific product
void numberOfSalesOfProduct() {
    string pid;
    cout << "Enter Product ID: "; cin >> pid;
    int totalQty = 0;
    for (int i = 0; i < purchaseCount; i++) {
        if (purchases[i]->product->getProductID() == pid)
            totalQty += purchases[i]->quantity;
    }
    cout << "Total units sold for product " << pid << ": " << totalQty << endl;
}

// List products purchased birthyear a specific customer
void productsPurchasedByCustomer() {
    string nid;
    cout << "Enter Customer National ID: "; cin >> nid;
    bool any = false;
    cout << "<---Purchases birthyear customer with nationalID:" << nid << "--->" << endl;
    for (int i = 0; i < purchaseCount; i++) {
        if (purchases[i]->customer->getNationalID() == nid) {
            purchases[i]->product->showInfo();
            cout << "Quantity: " << purchases[i]->quantity << endl;
            cout << "Date: " << purchases[i]->purchaseDate << endl;
            cout << "-----------------------------" << endl;
            any = true;
        }
    }
    if (!any) cout << "No purchases found for this customer." << endl;
}
// Generate sales report for all dealers
void dealerSalesReport() {
    cout << "<----Dealer Sales Report---->" << endl;
    for (int d = 0; d < dealerCount; d++) {
        double sum = 0;
        for (int i = 0; i < purchaseCount; i++) {
            if (purchases[i]->dealer->getDealerID() == dealers[d]->getDealerID())
                sum += purchases[i]->quantity * purchases[i]->product->getPrice();
        }
        dealers[d]->showInfo();
        cout << "Total Sales: " << sum << endl;
    }
}
// Display the main menu of the store management system
void showMenu() {
    cout << "\n<---Store Management System--->\n" << endl;
    cout << "1. Add a Product\n";
    cout << "2. Remove a Product\n";
    cout << "3. Add a Customer\n";
    cout << "4. Remove a Customer\n";
    cout << "5. Add a Dealer\n";
    cout << "6. Remove a Dealer\n";
    cout << "7. Record a Purchase\n";
    cout << "8. Calculate and display the total purchase amount for a specific Customer\n";
    cout << "9. Display the list of Customers who purchased a specific Product\n";
    cout << "10. Display the list of Products sold birthyear a specific Dealer\n";
    cout << "11. Display the total number of units sold for a specific Product\n";
    cout << "12. Display the list of Products purchased birthyear a specific Customer\n";
    cout << "13. Display a report of all Dealers along with their total sales\n";
    cout << "14. Exit the Program\n";
    cout << "Enter your choice (1-14): ";
}
int main() {
    int choice;
    bool running = true;
    while (running) {
        showMenu();
        cin >> choice;
        switch (choice) {
            case 1: addProduct(); break;
            case 2: removeProduct(); break;
            case 3: addCustomer(); break;
            case 4: removeCustomer(); break;
            case 5: addDealer(); break;
            case 6: removeDealer(); break;
            case 7: recordPurchase(); break;
            case 8: totalPurchaseOfCustomer(); break;
            case 9: listCustomersOfProduct(); break;
            case 10: listProductsOfDealer(); break;
            case 11: numberOfSalesOfProduct(); break;
            case 12: productsPurchasedByCustomer(); break;
            case 13: dealerSalesReport(); break;
            case 14: running = false; cout << "Program has ended. We hope to see you again soon!" << endl; break;
            default:cout << "Invalid choice. Try again." << endl;
        }
    }
    // Clean up dynamically allocated memory
    for (int i = 0; i < productCount; i++) {
        delete products[i];
    }
    for (int i = 0; i < customerCount; i++) {
        delete customers[i];
    }
    for (int i = 0; i < dealerCount; i++) {
        delete dealers[i];
    }
    for (int i = 0; i < purchaseCount; i++) {
        delete purchases[i];
    }
    return 0;
}