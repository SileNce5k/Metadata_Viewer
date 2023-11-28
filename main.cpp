#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <cstring>

#define MAX_BYTES 2048 // Maximum of bytes to care about when parsing the bytes.
char separator = 23;




// TODO: Change name of byte_parse to something more descriptive.
void parse_artist_name(std::vector<std::string> &artist_name, size_t byte_parse, std::vector<char> all_bytes)
{
	std::cout << "Parsing artist name...\n";
	std::string a_name = "";
	while(all_bytes[byte_parse] != separator && all_bytes[byte_parse] != 0 && byte_parse < all_bytes.size()){
		// std::cout << "all_bytes[byte_parse]:\t" << all_bytes[byte_parse] << "\n";
		// append all_bytes[byte_parse] to a_name
		a_name += all_bytes[byte_parse];
		//std::cout << "a_name in while loop:\t" << a_name << "\n"; 
		byte_parse++;

	}
	std::cout << "\n" << "a_name is:\"" << a_name << "\"\nsize:\t"<< a_name.size() <<"\n";
	artist_name.push_back(a_name);
}


void parse_ID3(bool &artist_found)
{
	if()
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
			for(int j = 0; j < sizeof(artist_metatag); ++j){
				if(all_bytes[i+j] == artist_metatag[size_of_artist_metatag-1] && i+j < all_bytes.size()){
					size_t byte_parse = i + j; //  The byte to start parsing the artist name from
					std::cout << "byte_parse: " << byte_parse << "\n";
					parse_artist_name(artist_name, byte_parse + 1, all_bytes);
					artist_found = false;
				}
					
			}
			std::cout << "\n";
		}
		return i + j;
}

enum parser_to_use{
	no_parser = 0,
	other_parser = 1,
	ID3_parser = 2
};


int main(int argc, char **argv)
{
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

	char ID3[] = {73, 68, 53}; // ID3
	bool do_ID3_parse = false;

	parser_to_use parser = no_parser;

	// Check if ID3 is at the start of the file
	std::cout << "0:\t" << all_bytes[0] << "\n1:\t" << all_bytes[1] << "\n2:\t" << all_bytes[2] << "\n";
	if(all_bytes[0] == ID3[0] && all_bytes[1] == ID3[1] && all_bytes[2] == ID3[2])
		parser = ID3_parser; 
	

	// READ THROUGH all_bytes:: but only the first 2048 bytes (for now)
	
	for(size_t i = 3; i < all_bytes.size() && !artist_found && i < MAX_BYTES; ++i){
		if(do_ID3_parse && i > 3){
			std::cerr << "ID3 PARSER NOT IMPLEMENTED YET :)\n";
		}else if(i > 3){
			i = parse_other(artist_found, artist_name, all_bytes, i);
		}


	
		
	}
	std::cout << "Got " << artist_name.size() << " artist names:\n";
	for(int i = 0; i < artist_name.size(); i++){
		std::cout << "\t" << artist_name[i] << "\n";
	} 

	return 0;
}
