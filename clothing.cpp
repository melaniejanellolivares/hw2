
#include "clothing.h"
#include "util.h"


Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand)
	:
		Product(category, name, price, qty) //call parent constructor to init data members
	{
		size_ = size; //init corressponding data members
		brand_ = brand;

	}
Clothing::~Clothing(){

}

//return a set of all the keywords of the item
std::set<std::string> Clothing::keywords() const{

	std::set<std::string> keywordset;
	std::set<std::string> tempset = parseStringToWords(convToLower(brand_));
	
	keywordset = parseStringToWords(convToLower(name_));
	keywordset = setUnion( keywordset,  tempset);
	keywordset.insert(convToLower(size_));


	return keywordset;

	
}

std::string Clothing::displayString() const{
	
	std::string dispstring;
	dispstring = name_;
	dispstring += '\n';
	dispstring += "Size: "; 
	dispstring += size_;
	dispstring += " Brand: ";
	dispstring += brand_;	
	dispstring += '\n';
	dispstring += std::to_string(price_);
	dispstring += " ";
	dispstring += std::to_string(qty_);
	dispstring += " left.";
	dispstring += '\n';

	return dispstring;
}
void Clothing::dump(std::ostream& os) const{
	os << category_ << std::endl;
	os << name_ << std::endl;
		os << price_ << std::endl;

	os << qty_ << std::endl;
	os << size_ << std::endl;
	os << brand_ << std::endl;

}
