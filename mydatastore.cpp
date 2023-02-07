#include "mydatastore.h"
	
	


	MyDataStore::MyDataStore(){

	}

	MyDataStore::~MyDataStore(){
		for(size_t i = 0; i < deleteProducts.size(); i++){
			delete deleteProducts[i];
		}
		for(size_t i = 0; i < deleteUsers.size(); i++){
			delete deleteUsers[i];
		}

	}

	//adds product to the inventory
	void MyDataStore::addProduct(Product* p){


	std::set<std::string> s1 = p->keywords();

	if(allProducts.find(p) == allProducts.end()) //product not fond
	{
		deleteProducts.push_back(p);
		allProducts.insert(p);
	}	


	//get all product keywords as key
	for(std::set<std::string>::iterator it = s1.begin(); it != s1.end(); ++it){
		
		if(keymap.find(*it) != keymap.end()){ //found
			keymap[*it].insert(p);

		}
		else{//not found
			std::set<Product*> keyset;
			keyset.insert(p);
			keymap[*it] = keyset;
		}
		
	}




}

//adds user to the "data base" while also assigning them carts
void MyDataStore::addUser(User* u){
	if(allUsers.find(u) == allUsers.end()) //product not fond
	{
			deleteUsers.push_back(u);

		allUsers.insert(u);
	}	
	std::vector<Product*> usercart; 

	usercartmap[u->getName()] = usercart;
	usermap[u->getName()] = u;

	


}

//searches for the terms
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
	std::vector<Product*> pReturn;
	
	
	std::set<Product*> unionset;
	//or
	if(type == 1){
		for(size_t i = 0; i < terms.size(); i++){
			if(keymap.find(convToLower(terms[i])) != keymap.end()){ //found
				unionset = setUnion(unionset, keymap[terms[i]]);
			}	
		}

	}
	else if(type == 0){
		
		//add an if statement to check if it is empty bc it is intersecting with empy set


		for(size_t i = 0; i < terms.size(); i++){
			if(keymap.find(convToLower(terms[i])) != keymap.end()){ //found
				if(unionset.size() < 1){ //empty
					unionset = keymap[terms[i]];
				
				}
				else{
					unionset = setIntersection(unionset, keymap[terms[i]]);
				}
			}
			else if(keymap.find(convToLower(terms[i])) == keymap.end()){ //doesnt exist
				return pReturn; //empty vector
			}	
		}

	}
	//turn into a vector to easily access
	for(std::set<Product*>::iterator it = unionset.begin(); it != unionset.end(); ++it){
		pReturn.insert(pReturn.begin(), *it);
	}

	prevSearch = pReturn;
	

	return pReturn; 

}


//add an item to the cart based on the prevSearch vector also check for exceptions
void MyDataStore::addingtoCart(std::string username,  size_t index){
	if(index - 1 > prevSearch.size() || index < 0){
		std::cout << "Invalid request" << std::endl;
		return;

	}
	
	else if(usercartmap.find(username) == usercartmap.end()){ //found
		std::cout << "Invalid request" << std::endl;
		return;
	}
	
	else{
		// usercartmap[username].insert(usercartmap[username].begin(), prevSearch[index - 1]);
		usercartmap[username].push_back(prevSearch[index - 1]);

	}
	

}

//view the user cart through using the usercartmap
void MyDataStore::viewingCart(std::string username){

	if(usercartmap.find(username) == usercartmap.end()){ //not found
		std::cout << "Invalid username" << std::endl;
		return;
	}
	else{
		int cnt = 1;
		//iterating thru the cart printing out all the items
		for (std::vector<Product*>::iterator it = usercartmap[username].begin(); it != usercartmap[username].end(); ++it){
			std::cout << "Item " << cnt << std::endl;
			std::cout << (*it)->displayString() << std::endl;
			cnt++; 
		}

	}

}

//buying the items in user cart while deducting the amount and subtracting the qty (first making sure user has enough money and there is stock)
void MyDataStore::buyingCart(std::string username){
	if(usercartmap.find(username) == usercartmap.end()){ //found
		std::cout << "Invalid username" << std::endl;
		return;
	}
	std::vector<Product*> copyusercart;

	

	for (std::vector<Product*>::iterator it = usercartmap[username].begin(); it != usercartmap[username].end(); ++it){
		if( (*it)->getQty() > 0 && usermap[username]->getBalance() >= (*it)->getPrice() ){
			(*it)->subtractQty(1);
			usermap[username]->deductAmount((*it)->getPrice());

		}
		else if((*it)->getQty() < 1 || usermap[username]->getBalance() < (*it)->getPrice() ){
			copyusercart.push_back(*it);
			std::cout << "Not able to purchase" << std::endl;
			continue;
		}
	}

	usercartmap[username] = copyusercart;
}
//prints out the inventory and user data
void MyDataStore::dump(std::ostream& ofile){


	ofile << "<products>" << std::endl;
	for(std::set<Product*>::iterator it = allProducts.begin(); it != allProducts.end(); ++it){
		(*it)->dump(ofile);
	}
	ofile << "</products>" << std::endl;

	ofile << "<users>" << std::endl;
	for(std::set<User*>::iterator it = allUsers.begin(); it != allUsers.end(); ++it){
		(*it)->dump(ofile);
	}
	ofile << "</users>" << std::endl;

}
