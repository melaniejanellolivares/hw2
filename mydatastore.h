#include <string>
#include <iostream>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include "datastore.h"



#include "util.h"

class MyDataStore : public DataStore {

	public:
	MyDataStore();
	~MyDataStore();
	void addProduct(Product* p);

	void addUser(User* u);

	std::vector<Product*> search(std::vector<std::string>& terms, int type);

	void addingtoCart(std::string username,  size_t index);
	void viewingCart(std::string username);
	void buyingCart(std::string username);
	void dump(std::ostream& ofile);



	public:

	std::map<std::string,std::set<Product*>> keymap;
	std::map<std::string,std::vector<Product*>> usercartmap;
	std::map<std::string, User*> usermap;
	std::vector<Product*> prevSearch;
	std::set<Product*> allProducts;
	std::set<User*> allUsers;
	std::vector<Product*> deleteProducts;
	std::vector<User*> deleteUsers;



};