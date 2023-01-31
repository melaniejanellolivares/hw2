
#include "book.h"
#include "util.h"


Book::~Book(){};
Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author)
	:
		Product(category, name, price, qty)
	{
		isbn_ = isbn;
		author_ = author;


	}

std::set<std::string> Book::keywords() const{

	std::set<std::string> keywordset;
	std::set<std::string> tempset = parseStringToWords(convToLower(author_));
	
	keywordset = parseStringToWords(convToLower(name_));
	keywordset = setUnion( keywordset,  tempset );
	keywordset.insert(isbn_);


	return keywordset;

	
}

std::string Book::displayString() const{

	

	std::string dispstring;
	dispstring = name_;
	dispstring += '\n';
	dispstring += "Author: "; 
	dispstring += author_;
	dispstring += " ISBN: ";
	dispstring += isbn_;	
	dispstring += '\n';
	dispstring += std::to_string(price_);
	dispstring += " ";
	dispstring += std::to_string(qty_);
	dispstring += " left.";
	dispstring += '\n';
	


	return dispstring;
}

void Book::dump(std::ostream& os) const{
	os << category_ << std::endl;
	os << name_ << std::endl;
	os << price_ << std::endl;
	os << qty_ << std::endl;
	os << isbn_ << std::endl;
	os << author_ << std::endl;


}