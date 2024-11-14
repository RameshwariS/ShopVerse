#include <bits/stdc++.h>
using namespace std;
class Product{
    public:
    int id;
    string name;
    double price;
    int quantity;
    Product(int id,string name,double price,int quantity){
        this->id = id;
        this->name = name;
        this->price = price;
        this->quantity = quantity;
    }
    //methods for admin
    // protected:
    public:
        void getDetails() const
        {
            cout << "Product Id: " << id << endl;
            cout << "Product Name: " << name << endl;
            cout << "Product Price: " << price << endl;
            cout << "Product Quantity: " << quantity << endl;
        }

    public: void updateQuantity(int n){
            this->quantity = n;
        }
};

class Customer{
public:
    int Customerid;
    string Customername;
    string Email;
    string Address;
    Customer(int Customerid, string Customername, string Email, string Address)
    {
        this->Customerid = Customerid;
        this->Customername = Customername;
        this->Email = Email;
        this->Address = Address;
    }
    // methods for admin
    //  protected:
public:
    void getDetails()
    {
        cout << "Customer Id: " << Customerid << endl;
        cout << "Customer Name: " << Customername << endl;
        cout << "Customer Address: " << Address << endl;
        cout << "Customer Address: " << Address << endl;
    }

public:
    void updateAddress(string newA)
    {
        this->Address = newA;
    }
};

class ShoppingCart{
    public:
        int cartID;
        vector<Product> items;
        void addItem(Product new1){
            items.push_back(new1);
        }
       void removeItem(int id1){
           for (auto it = items.begin(); it != items.end(); ++it)
           {
               if (it->id == id1)
                   items.erase(it);
               break;
           }
       }
       void viewCart(){
           double total = 0;
           for (int i = 0; i < items.size(); i++)
           {
               cout<<"Item no,"<<i+1 << items[i].name <<" Price: "<<items[i].price<< endl;
               total += items[i].price ;
           }
           cout << "Total Price: " << total;
       }
       void clearCart(){
           items.clear();
           cout << "Cart is cleared" << endl;
       }
};
class Order{
    public:
        int orderID ;
        int customerID ;
        vector<Product> items;
        double totalAmount;
        string status;
        Order(int id, int custID, vector<Product> itemList) : orderID(id), customerID(custID), items(itemList), totalAmount(0), status("Pending")
        {
            for (auto &item : items)
                totalAmount += item.price;
        }
       void placeOrder(){
           cout << "Order placed with ID: " << orderID << " for Custoemr ID: " << customerID << endl;
           status = "Placed";
       }
       void updateStatus(string newStatus){
           status = newStatus;
       }
       void viewOrderDetails(){
           cout << "Order ID: " << orderID << " | Status: " << status << " | Total Amount: $" << totalAmount << endl;
           for (auto &item : items)
               item.getDetails();
       }
       
};
class ShopVerse
{
    public:
        vector<Product> products;
        vector<Customer> customers;
        vector<Order> orders;

    public: void addProduct(Product new1){
            products.push_back(new1);
        }
        void registerCustomer(Customer newC){
            customers.push_back(newC);
        }
        void processOrder(Customer c1,ShoppingCart o1){
            Order newOrder(orders.size() + 1, c1.Customerid, o1.items);
        }
        void updateInventory(){
            for (auto &order : orders)
            {
                for (auto &orderItem : order.items)
                {
                    for (auto &product : products)
                    {
                        if (product.id == orderItem.id)
                        {
                            product.updateQuantity(product.quantity - 1);
                        }
                    }
                }
            }
        }

void addProductByAdmin()
{
    int n;
    cout << "Number of Products to be add: ";
    cin >> n;
    while(n--){
    int id, quantity;
    string name;
    double price;

    cout << "Enter product details to add a new product:\n";
    cout << "Product ID: ";
    cin >> id;
    cin.ignore();
    cout << "Name: ";
    getline(cin, name);
    cout << "Price: ";
    cin >> price;
    cout << "Quantity: ";
    cin >> quantity;
    
    Product newProduct(id, name, price, quantity);
    addProduct(newProduct);
    }
    
}
void viewInventory() const
{
    cout << "Inventory:\n";
    for (const auto &product : products)
        product.getDetails();
}
};

int main()
{
    ShopVerse ecommerce;
    ShoppingCart cart;
    Customer customer(1, "John Doe", "john@example.com", "123 Elm Street");
    ecommerce.registerCustomer(customer);
    int choice;
    do
    {
        cout << "\n--- E-Commerce System ---\n";
        cout << "1. Add Product (Admin)\n";
        cout << "2. Register Customer\n";
        cout << "3. View Inventory\n";
        cout << "4. Add Product to Cart\n";
        cout << "5. View Cart\n";
        cout << "6. Remove Product from Cart\n";
        cout << "7. Place Order\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            ecommerce.addProductByAdmin();
            break;
        case 2:
            ecommerce.registerCustomer(customer);
            break;
        case 3:
            ecommerce.viewInventory();
            break;
        case 4:
        {
            int productID;
            cout << "Enter Product ID to add to cart: ";
            cin >> productID;
            bool found = false;
            for (const auto &product : ecommerce.products)
            {
                if (product.id == productID)
                {
                    cart.addItem(product);
                    cout << "Product added to cart.\n";
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "Product ID not found.\n";
            break;
        }
        case 5:
            cart.viewCart();
            break;
        case 6:
        {
            int productID;
            cout << "Enter Product ID to remove from cart: ";
            cin >> productID;
            cart.removeItem(productID);
            break;
        }
        case 7:
            ecommerce.processOrder(customer, cart);
            break;
        case 8:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);
}