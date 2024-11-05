#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class Items {
private:
	std::string name;
	int price;
	int weight;
	Items(std::string name, int price, int weight) : name(name), price(price), weight(weight) {}
public:
	int GetPrice() { return price; }
	int GetWeight() { return weight; }
};

class ShopBase {
protected:
	std::string name;
	std::vector<Items> items;
public:
	int getName();
	ShopBase(std::string name) : name(name) {}
	void addItem(Items item) {
		items.push_back(item);
	}
	std::vector<Items> getItems() { return items; }
};

class CustomShop : public ShopBase {
public:
	CustomShop(std::string name) : ShopBase(name) {}
	float AveragePrice() {
		int all_p = 0;
		for (Items item : items) {
			all_p += item.GetPrice();
		}
		return (float)all_p / items.size();
	}
	float AverageWeight() {
		int all_w = 0;
		for (Items item : items) {
			all_w += item.GetWeight();
		}
		return (float)all_w / items.size();
	}
};


int main()
{
	std::ifstream file("ShopeBased.txt");
	std::string line;
	std::vector<CustomShop> ShopBased;

	if (file.is_open()) {
		CustomShop* shop = nullptr;
		while (std::getline(file, line)) {
			std::stringstream all(line);
			std::string type, inf_basa;
			all >> type >> inf_basa;


			if (type == "Shop") {
				if (shop != nullptr) {
					ShopBased.push_back(*shop);
				}
				shop = new CustomShop(inf_basa);
			}
			else if (type == "Items") {
			}
			else {
				std::string name;
				int price, weight;
				all >> name >> price >> weight;
				Items item(name, price, weight);
				shop->addItem(item);
			}
		}
		if (shop != nullptr) {
			ShopBased.push_back(*shop);
		}
		file.close();
	}
	for (CustomShop shop : ShopBased) {
		std::cout << "Store: " << shop.getName() << std::endl;
		std::cout << "Average price: " << shop.AveragePrice() << std::endl;
		std::cout << "Average weight: " << shop.AverageWeight() << std::endl;
		std::cout << std::endl;
	}
	return 0;
}

int ShopBase::getName()
{
	return 0;
}
