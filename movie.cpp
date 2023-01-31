
#include "movie.h"
#include "util.h"


Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating)
	:
		Product(category, name, price, qty)
	{
		genre_ = genre;
		rating_ = rating;

	}

Movie::~Movie(){

}

std::set<std::string> Movie::keywords() const{

	std::set<std::string> keywordset;
	std::set<std::string> tempset = parseStringToWords(convToLower(genre_));
	
	keywordset = parseStringToWords(convToLower(name_));
	keywordset = setUnion( keywordset,  tempset);
	keywordset.insert(rating_);


	return keywordset;

	
}

std::string Movie::displayString() const{
	
	std::string dispstring;
	dispstring = name_;
	dispstring += '\n';
	dispstring += "Genre: "; 
	dispstring += genre_;
	dispstring += " Rating: ";
	dispstring += rating_;	
	dispstring += '\n';
	dispstring += std::to_string(price_);
	dispstring += " ";
	dispstring += std::to_string(qty_);
	dispstring += " left.";
	dispstring += '\n';

	return dispstring;
}

void Movie::dump(std::ostream& os) const{
	os << category_ << std::endl;
	os << name_ << std::endl;
	os << price_ << std::endl;

	os << qty_ << std::endl;
	os << genre_ << std::endl;
	os << rating_ << std::endl;

}
