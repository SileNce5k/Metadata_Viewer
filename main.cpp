#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <cstring>
#include <algorithm>

#define MAX_BYTES 2048 // Maximum of bytes to care about when parsing the bytes.
char separator = 23;

struct Track
{
	std::string artist_name;
	std::string title;
	std::string album_title;
	std::uint16_t track_number;
	std::uint16_t year;
	std::string genre;
	std::string comments;
};








// TODO: Change name of byte_parse to something more descriptive.
void parse_artist_name(std::vector<std::string> &artist_name, size_t byte_parse, std::vector<char> all_bytes)
{
	std::cout << "Parsing artist name...\n";
	std::string a_name = "";
	while(all_bytes[byte_parse] != separator && all_bytes[byte_parse] != 0 && byte_parse < all_bytes.size()){
		a_name += all_bytes[byte_parse];
		byte_parse++;
	}
	std::cout << "\n" << "a_name is:\"" << a_name << "\"\nsize:\t"<< a_name.size() <<"\n";
	artist_name.push_back(a_name);
}

void parse_album_name()
{
}

void parse_title(std::vector<std::string> &title, size_t byte_parse, std::vector<char> all_bytes)
{
	std::cout << "Parsing title...\n";
	std::string a_title = "";
	while(all_bytes[byte_parse] != separator && all_bytes[byte_parse] != 0 && byte_parse < all_bytes.size()){
		a_title += all_bytes[byte_parse];
		byte_parse++;
	}

}




int parse_ID3(
				 bool &artist_found
			   	,std::vector<std::string> &artist_name
			   	,std::vector<char> &all_bytes
				,size_t i
			  )
{
	char ID3_title[] = {84, 73, 84, 50}; // TIT2
	return i;
}



int parse_other(bool &artist_found
				,std::vector<std::string> &artist_name
				,std::vector<char> &all_bytes
	 			,size_t i
				)
{
	int j = 0;
	const char artist_metatag[] = {65, 82, 84, 73, 83, 84, 61}; // "ARTIST="
	size_t size_of_artist_metatag = sizeof(artist_metatag) / sizeof(char);
		if(artist_metatag[0] == all_bytes[i]){
			for(int j = 0; j < sizeof(artist_metatag) && i + j < all_bytes.size(); ++j){
				if(all_bytes[i+j] == artist_metatag[size_of_artist_metatag - 1]){
					size_t byte_parse = i + j; //  The byte to start parsing the artist name from
					parse_artist_name(artist_name, byte_parse + 1, all_bytes);
					artist_found = false;
				}else if(all_bytes[i+j] == title_metatag[size_of_artist_metatag - 1]){
					size_t byte_parse = i + j;
					parse_title(title_name, byte_parse + 1, all_bytes)
				}
				
					
			}
			std::cout << "\n";
		}
		return i + j;
}



enum class Parser{
	no_parser = 0,
	other_parser = 1,
	ID3_parser = 2
};


int main(int argc, char **argv)
{
	Track track;
	if(argc < 2){
		std::cerr << "ERROR: filename not in arguments\n";
		return -1;
	}
	std::string filename;// = "sk.opus";
	

	for(int i = 0; i < argc - 1; i++){
		if(strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0){
			filename = argv[i+1];
			break;
		}
	}
	std::ifstream file(filename, std::ios::binary);

	if(!file.is_open())
	{
		std::cerr << "Unable to open file '" << filename << "'\n"; 
		return 1;
	}
	std::cout << "Parsing '" << filename << "'\n\n";
	
	
	std::vector<std::string> artist_name;
	int numOfArtists = 0;
	bool artist_found = false;
	size_t found_at = 0;
	
	std::vector<char> all_bytes;
	char byte;
	size_t amount_of_bytes = 0;
	while(file.read(&byte, sizeof(byte)) && amount_of_bytes < MAX_BYTES)
	{
		all_bytes.push_back(byte);
		amount_of_bytes++;
	}
	file.close();

	char ID3[] = {73, 68, 51}; // ID3
	bool do_ID3_parse = false;

	Parser parser = Parser::no_parser;

	// Check if ID3 is at the start of the file
	std::cout << "0:\t" << all_bytes[0] << "\n1:\t" << all_bytes[1] << "\n2:\t" << all_bytes[2] << "\n";
	if(std::equal(all_bytes.begin(), all_bytes.begin() + 3, ID3)){
		parser = Parser::ID3_parser; 
	}
	

	// READ THROUGH all_bytes:: but only the first 2048 bytes (for now)
	
	for(size_t i = 3; i < all_bytes.size() && !artist_found && i < MAX_BYTES; ++i){
		if(i > 3){
			if(parser == Parser::ID3_parser){
				parse_ID3(artist_found, artist_name, all_bytes, i);
			}else{
				//i = parse_other(artist_found, artist_name, all_bytes, i);
			}
		}


	
		
	}
	std::cout << "Got " << artist_name.size() << " artist names:\n";
	for(int i = 0; i < artist_name.size(); i++){
		std::cout << "\t" << artist_name[i] << "\n";
	} 

	return 0;
}
