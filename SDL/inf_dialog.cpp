#include <map>
#include <fstream>
#include <sstream>
#include <string>

extern "C" const char *get_dialog_name( unsigned int n );

const char *get_dialog_name( unsigned int n )
{
	static std::map<unsigned int,std::string> table;
	static std::string dummy;
	static bool init = false;
	if( !init ){
		init = true;
		std::ifstream input( "etxt.h" );
		
		if( !input ){
			//not valid
		} else {
			//valid
			for( std::string line; getline( input, line ); ) {
			    std::istringstream iss(line);

				std::string a, b;
				unsigned int c;
			    if( !( iss >> a >> b >> c ) ) { break; } // error
				
				if( a == "#define" ){
					table[c] = b;
				}
			}
		}
	}

	if( table.find( n ) != table.end() ){
		return table.at( n ).c_str();
	} else {
		dummy = std::to_string( n );
		return dummy.c_str();
	}
}
