// SPDX-License-Identifier: GPL-v3.0
#include "app/caesar.hpp"
#include "app/dat/data.hpp"
#include "app/dat/args/arguments.hpp"
#include "app/dat/excep/caesarException.hpp"
#include <stdexcept>
#include <iostream>

int main(const int nArgs, const char* sArgs[]){

//  1: Save arguments.
    SherpadCaesar::Arguments_t args { nArgs, sArgs };

	try
	{
//      2: Translate from arguments to input data.
        SherpadCaesar::Data_t data { args };

//      3: With input data Caesar_t works.
	    SherpadCaesar::Caesar_t c { data };

	    switch (args.getNumArguments()){
//          There aren't arguments.
            case 0:
                c.ask();
                c.performTransformation();

                break;
//          There are arguments.
            default:
                c.validateInputParameters();
                c.process();
        }
	}
    catch (SherpadCaesar::CaesarException_t const &e) {
        std::cerr << e.what();
    }
    catch (std::out_of_range const &e) {
        std::cerr << e.what() << '\n';
        std::cerr << "[-]FATAL ERROR!!!, an invalid argument has been entered. \n";
        std::cerr << "[-]This error usually occurs when the program espects a integer value and it receives a numeric value TOO BIG or TOO SMALL. \n";
    }
    catch (std::bad_alloc const &e) {
        std::cerr << e.what() << '\n';
        std::cerr << "[-]FATAL ERROR!!!, Insufficient memory. \n";
        std::cerr << "[-]This error usually occurs when an attempt is made to encrypt or decrypt a string or file that is too large and there is not enough memory to store it. \n";
    }
    catch (std::exception const &e) {
        std::cerr << e.what() << '\n';
        std::cerr << "[-]FATAL ERROR!!!, Unexpected failure. \n";
    }

	return 0;
}
