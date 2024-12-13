#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
    string name;
    float price;

public:
    Product(const string &name, float price) : name(name), price(price) {
    }

    string getName() { return name; }
    float getPrice() { return price; }

    void setName(const string &newName) { name = newName; }
    void setPrice(float newPrice) { price = newPrice; }

    virtual float getFinalPrice() = 0;
};

class Discountable {
public:
    virtual float applyDiscount(float price) = 0;
};

class Electronics : public Product, public Discountable {
private:
    float discountRate;

public:
    Electronics(const string &name, float price, float discountRate)
        : Product(name, price), discountRate(discountRate) {
    }

    float applyDiscount(float price) override {
        return price - (price * discountRate / 100.0f);
    }

    float getFinalPrice() override {
        return applyDiscount(price);
    }
};

class Clothing : public Product, public Discountable {
    float fixedDiscount;

public:
    Clothing(const string &name, float price, float fixedDiscount)
        : Product(name, price), fixedDiscount(fixedDiscount) {
    }

    float applyDiscount(const float price) override {
        return price - fixedDiscount > 0 ? price - fixedDiscount : 0;
    }

    float getFinalPrice() override {
        return applyDiscount(price);
    }
};

int main() {
    Electronics laptop("Laptop", 1000.0f, 10.0f);
    Clothing tShirt("T-Shirt", 50.0f, 5.0f);

    cout << laptop.getName() << " - Base Price: " << laptop.getPrice()
            << ", Final Price: " << laptop.getFinalPrice() << endl;

    cout << tShirt.getName() << " - Base Price: " << tShirt.getPrice()
            << ", Final Price: " << tShirt.getFinalPrice() << endl;

    return 0;
}
