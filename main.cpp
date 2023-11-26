#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

#define MAX_BYTES 2048 // Maximum of bytes to care about when parsing the bytes.
char separator = 23;

// TODO: Change name of byte_parse to something more descriptive.
void parse_artist_name(std::vector<std::string> &artist_name, size_t byte_parse, std::vector<char> all_bytes)
{
	std::cout << "Parsing artist name...\n";
	std::string a_name = "";
	while(all_bytes[byte_parse] != separator && byte_parse < all_bytes.size()){
		// std::cout << "all_bytes[byte_parse]:\t" << all_bytes[byte_parse] << "\n";
		// append all_bytes[byte_parse] to a_name
		a_name += all_bytes[byte_parse];
		//std::cout << "a_name in while loop:\t" << a_name << "\n"; 
		byte_parse++;

	}
	std::cout << "\n" << "a_name is:\t" << a_name << "\nsize:\t"<< a_name.size() <<"\n";
}


void parse_ID3()
{

}

void parse_other(bool &artist_found
				,std::vector<std::string> &artist_name
				,size_t &size_of_artist_metatag
				,std::vector<char> &all_bytes
				,const char &artist_metatag
	 			,size_t i
				)
{
		if(artist_metatag[0] == all_bytes[i]){
			for(size_t j = 0; j < sizeof(artist_metatag); ++j){
				if(all_bytes[i+j] == artist_metatag[size_of_artist_metatag-1] && i+j < all_bytes.size()){
					size_t byte_parse = i + j; //  The byte to start parsing the artist name from
					artist_name.push_back("TEST ARTIST!");
					std::cout << "byte_parse: " << byte_parse << "\n";
					parse_artist_name(artist_name, byte_parse + 1, all_bytes);
					artist_found = false;
				}
					
			}
			std::cout << "\n";
		}
}


int main(int argc, char **argv)
{
	if(argc < 2){
		std::cerr << "ERROR: filename not in arguments\n";
		return -1;
	}
	std::string filename = "sk.opus"; //maximum filename size is 1024

	for(int i = 0; i < argc -1; i++){
		if((argv[i] == "--file" || "-f")){
			filename = argv[i+1];
		}
	}
	

	std::ifstream file(filename, std::ios::binary);

	if(!file.is_open())
	{
		std::cerr << "Unable to open file '" << filename << "'\n"; 
		return 1;
	}
	const char artist_metatag[] = {65, 82, 84, 73, 83, 84, 61}; // "ARTIST="
	size_t size_of_artist_metatag = sizeof(artist_metatag) / sizeof(char);
	
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

	

	// READ THROUGH all_bytes:: but only the first 2048 bytes (for now)
	for(size_t i = 0; i < all_bytes.size() && !artist_found && i < MAX_BYTES; ++i){
		parse_other(artist_found, artist_name, size_of_artist_metatag, all_bytes, artist_metatag, i);


	
		
	}


	return 0;
}
