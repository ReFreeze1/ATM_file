#include <iostream>
#include<fstream>



int main() {
	int bills[6] = { 100,200,500,1000,2000,5000 };
	int money[1000];
	char operation;
	std::cout << "Choose an operation ";
	std::cin >> operation;

	std::ifstream in_ATM("ATM.bin",std::ios::binary);
	if (in_ATM.is_open()) {
		in_ATM.read((char*)money, sizeof(money));
		in_ATM.close();
	}
	else {
		for (int i = 0; i < 1000; i++) {
			money[i] = 0;
		}
	}

	if (operation == '+') {
		for (int i = 0; i < 1000; i++) {
			if (money == 0) {
				money[i] = bills[rand() % 6];
			}
		}
		std::ofstream out_ATM("ATM.bin", std::ios::binary);
		out_ATM.write((char*)money, sizeof(money));
		out_ATM.close();
		return 0;
	}
	else if (operation == '-') {
		std::cout << "Amount: ";
		int amount;
		std::cin >> amount;
		if ((amount % 100) != 0) {
			std::cerr << "Invalid amount: " << amount << std::endl;
			return 1;
		}
		int amount_to_collect = amount;
		for (int i = 5; i >= 0; i--) {
			int bill = bills[i];
			for (int j = 0; j < 1000; j++) {
				if (money[j] == bill) {
					if (amount_to_collect >= bill) {
						money[j] = 0;
						amount_to_collect -= bill;
						if (amount_to_collect == 0) {
							std::cout << "Amount taken: " << amount<<"\n";
							std::ofstream out_file("ATM.bin", std::ios::binary);
								out_file.write((char*)money, sizeof(money));
								return 0;
							
						}
					}
				}
			}
			
		}
		std::cerr << "Not enough compatible bills!" << std::endl;
		return 1;
	}


}
