#include "LogElem.h"

const int MAX_INPUTS = 10; 
const int MAX_OUTPUTS = 10; 
class Terminal;
class LogicalElement;

int main() {
    Class1::LogicalElement paramSource,sample,sample1,sample2;
    int option;
    bool exitFlag = false;
    try
    {
        while (!exitFlag)
        {
            cout << "1)Create class instances with initialization count of input and output logical element terminal\n";
            cout << "2)Creation of class instances with initialization of terminal handle array specified length; \n";
            cout << "3)Redefining the state of all input and output terminals by entering their new values from the input stream\n";
            cout << "4)([]) Receiving the terminal with the specified number (return by link);\n";
            cout << "5)Add input or output terminal;\n";
            cout << "6)(>>) connection between the output terminal and the input terminal of two logical terminals elements(if there are several terminals, the first unoccupied are joinedterminals); \n";
            cout << "7)format a logical element as a pseudo-graphic string with ASCII" << endl;
            cout << "8)exit" << endl;
            
            
            try
            {
                cin >> option;
                if (cin.fail()) {
                    cin.clear();  // Сброс ошибки ввода
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Очистка буфера ввода
                    throw std::invalid_argument("Invalid input. Please enter a valid option.");
                }

                switch (option)
                {
                case 1:
                {
                    sample = Class1::LogicalElement(5,5);
                    sample.outputState(cout);
                }
                break;
                case 2:
                {
                    string descriptions[] = { "Input", "Output", "Input", "Output" ,"Output"};
                    sample = Class1::LogicalElement(descriptions, 5);
                    sample.outputState(cout);
                }
                break;
                case 3:
                {
                    sample = Class1::LogicalElement(2,2);
                    sample.updateInputTerminalStates(cin);
                    sample.updateOutputTerminalStates(cin);
                    sample.outputState(cout);
                }
                break;
                case 4:
                {
                    sample = Class1::LogicalElement(5, 5);
                    cout << sample[3];
                }
                break;
                case 5:
                {
                    // sample
                    sample.addInputTerminal();
                    sample.addOutputTerminal();

                }

                break;
                case 6:
                {
                    sample1 = Class1::LogicalElement(4, 4);
                    sample2 = Class1::LogicalElement(2, 2);
                    sample1 >> sample2;
                    break;
                }
                case 7:
                {
                    sample = Class1::LogicalElement(3, 2);
                    sample.formatAsPseudoGraphic();
                    break;
                }
                
                case 8: {
                    exitFlag = true;
                  
                    break;
                }

                default:
                    cout << "No such command" << endl;
                }
            }
            catch (const std::invalid_argument)
            {
                cout << "Invalid argument, try again" << endl;
                continue;
            }
            catch (const std::bad_alloc)
            {
                cout << "Memory Error" << endl;
            }

        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }


    return 0;
}
