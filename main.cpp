#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#define MAX_BYTES 2048 // Maximum of bytes to care about when parsing the bytes.
char separator = 23;


int main(int argc, char **argv)
{
	char filename[] = "sk.opus";
	std::ifstream file(filename, std::ios::binary);

	if(!file.is_open())
	{
		std::cerr << "Unable to open file '" << filename << "'\n"; 
		return 1;
	}
	const char artist_metatag[] = {65, 82, 84, 73, 83, 84, 61};
	
	std::vector<char> artist_name;
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
	std::cout << "Sizeof all_bytes is " << all_bytes.size() << "\n";

	// READ THROUGH all_bytes:: but only the first 2048 bytes (for now)
	for(size_t i = 0; i < all_bytes.size() && !artist_found && i < MAX_BYTES; ++i){
		if(artist_metatag[0] == all_bytes[i]){
			for(size_t j = 0; j < sizeof(artist_metatag); ++j){
				if(all_bytes[i+j] == artist_metatag[j] && i+j < all_bytes.size()){
					// if(all_bytes[i+j < )
				}
					
			}
			std::cout << "\n";
		}
		
	}


	return 0;
}
