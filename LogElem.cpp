#include "LogElem.h"
const int MAX_INPUTS = 10;  // Максимальное количество входных клемм
const int MAX_OUTPUTS = 10; // Максимальное количество выходных клемм
namespace Class1 {
    // Complicated Class
    LogicalElement::LogicalElement() : numInputs(0), numOutputs(0), inputTerminals(nullptr), outputTerminals(nullptr) {
    }

    LogicalElement::LogicalElement(int numInputs, int numOutputs) : numInputs(numInputs), numOutputs(numOutputs) {
        inputTerminals = new Terminal[numInputs];
        outputTerminals = new Terminal[numOutputs];
        for (int i = 0; i < numInputs; ++i) {
            inputTerminals[i] = Terminal(true);
        }
        for (int i = 0; i < numOutputs; ++i) {
            outputTerminals[i] = Terminal(false);
        }
    }

    LogicalElement::LogicalElement(const string* terminalDescriptions, int length) {
        int numInputs = 0;
        int numOutputs = 0;

        for (int i = 0; i < length; ++i) {
            if (terminalDescriptions[i] == "Input") {
                ++numInputs;
            }
            else if (terminalDescriptions[i] == "Output") {
                ++numOutputs;
            }
            else {
                cout << "Error: Invalid terminal description." << endl;
            }
        }

        this->numInputs = numInputs;
        this->numOutputs = numOutputs;

        // Проверки на допустимые значения
        if (numInputs > MAX_INPUTS) {
            cout << "Error: Number of inputs exceeds the maximum limit." << endl;
            numInputs = MAX_INPUTS;
        }

        if (numOutputs > MAX_OUTPUTS) {
            cout << "Error: Number of outputs exceeds the maximum limit." << endl;
            numOutputs = MAX_OUTPUTS;
        }

        inputTerminals = new Terminal[numInputs];
        outputTerminals = new Terminal[numOutputs];
        for (int i = 0; i < numInputs; ++i) {
            inputTerminals[i] = Terminal(true);
        }
        for (int i = 0; i < numOutputs; ++i) {
            outputTerminals[i] = Terminal(false);
        }
    }

    int LogicalElement::getNumInputs() const {
        return numInputs;
    }

    int LogicalElement::getNumOutputs() const {
        return numOutputs;
    }

    // Метод получения входной клеммы по индексу
    Terminal& LogicalElement::getInputTerminal(int index) {
        if (index >= 0 && index < numInputs) {
            return inputTerminals[index];
        }
        else {
             cout << "Error: Invalid input terminal index." << endl;
            // Возвращаем первую входную клемму по умолчанию
            return inputTerminals[0];
        }
    }

    Terminal& LogicalElement::getOutputTerminal(int index) {
        if (index >= 0 && index < numOutputs) {
            return outputTerminals[index];
        }
        else {
            cout << "Error: Invalid output terminal index." << endl;
            return outputTerminals[0];
        }
    }

    void LogicalElement::addInputTerminal() {
        if (numInputs < MAX_INPUTS) {
            inputTerminals[numInputs++] = Terminal(true);
        }
        else {
            cout << "Error: Can't add more input terminals" << endl;
        }
    }

    void LogicalElement::addOutputTerminal() {
        if (numOutputs < MAX_OUTPUTS) {
            outputTerminals[numOutputs++] = Terminal(false);
        }
        else {
            cout << "Error: Cann't add more output terminals" << endl;
        }
    }

    void LogicalElement::formatAsPseudoGraphic() const {        
        cout << setw(12) << "Inputs:";

        for (int i = 0; i < numInputs; ++i) {
            cout << " | " << (inputTerminals[i].getSignalState() == -1 ? "X" : to_string(inputTerminals[i].getSignalState()));
        }

        cout << " |" << endl;

        cout << setw(12) << "Outputs:";

        for (int i = 0; i < numOutputs; ++i) {
            cout << " | " << (outputTerminals[i].getSignalState() == -1 ? "X" : to_string(outputTerminals[i].getSignalState()));
        }

        cout << " |" << endl;
    }

    void LogicalElement::operator>>(LogicalElement& logicElement) {
        for (int i = 0; i < this->numOutputs; ++i) {
            if (this->outputTerminals[i].getConnectionCount() < 3) {
                for (int j = 0; j < logicElement.numInputs; ++j) {
                    if (logicElement.inputTerminals[j].getConnectionCount() == 0) {
                        this->outputTerminals[i] >> logicElement.inputTerminals[j];
                        return;
                    }
                }
            }
        }
        
    }

    istream& LogicalElement::inputState(istream& is) {
        for (int i = 0; i < numInputs; ++i) {
            //cout << "Input Terminal " << i + 1 << ":\n";
            int a;
            is >> a;
            // Проверка на количество соединений
            //while (true) {
                //cout << "Enter connection count: ";
                int count = inputTerminals[i].getConnectionCount();
                is >> count;
                if ((inputTerminals[i].getIsInput() && inputTerminals[i].getConnectionCount() == 1 || inputTerminals[i].getConnectionCount() == 0) || (!inputTerminals[i].getConnectionCount() && inputTerminals[i].getConnectionCount() <= 3 && inputTerminals[i].getConnectionCount() >= 0)) {
                    break; 
                }
                else {
                    //cout << "Error: Invalid connection count. Please enter a valid value." << endl;
                    is.setstate(std::ios_base::failbit);
                   // return is;
                }
            //}

            // Проверка типа сигнала
            //while (true) {
                //cout << "Enter signal state: ";
                int signal = inputTerminals[i].getSignalState();
                is >> signal;
                if (inputTerminals[i].getSignalState() == 0 || inputTerminals[i].getSignalState() == 1 || inputTerminals[i].getSignalState() == -1) {
                    //break; 
                }
                else {
                    is.setstate(std::ios_base::failbit);
                    return is;
                    //cout << "Error: Invalid signal state. Please enter 0, 1, or -1." << endl;
                }
            //}
        }

        for (int i = 0; i < numOutputs; ++i) {
            //cout << "Output Terminal " << i + 1 << ":\n";
            // Проверка на количество соединений
            //while (true) {
                //cout << "Enter connection count: ";
                int count = outputTerminals[i].getConnectionCount();
                is >> count;
                if ((outputTerminals[i].getIsInput() && outputTerminals[i].getConnectionCount() == 1 || outputTerminals[i].getConnectionCount() == 0) || (!outputTerminals[i].getIsInput() && outputTerminals[i].getConnectionCount() <= 3 && outputTerminals[i].getConnectionCount() >= 0)) {
                    //break;  
                }
                else {
                    is.setstate(std::ios_base::failbit);
                    return is;
                   // cout << "Error: Invalid connection count. Please enter a valid value." << endl;
                }
            //}

            // Проверка типа сигнала
            //while (true) {
              //  cout << "Enter signal state: ";
                int signal = outputTerminals[i].getSignalState();
                is >> signal;
                if (outputTerminals[i].getSignalState() == 0 || outputTerminals[i].getSignalState() == 1 || outputTerminals[i].getSignalState() == -1) {
                    //break;  
                }
                else {
                    is.setstate(std::ios_base::failbit);
                    return is;
                    //cout << "Error: Invalid signal state. Please enter 0, 1, or -1." << endl;
                }
            //}
        }
    }

    ostream& Class1::LogicalElement::outputState(ostream& os) const {

        os << "Input Terminals:\n";
        for (int i = 0; i < this->numInputs; ++i) {
            os << "Input Terminal " << i + 1 << ":\n" << inputTerminals[i] << endl;
        }

        os << "Output Terminals:\n";
        for (int i = 0; i < numOutputs; ++i) {
            os << "Output Terminal " << i + 1 << ":\n" << outputTerminals[i] << endl;
        }
    }

    // Метод для переопределения состояний всех входных клемм
    void Class1::LogicalElement::updateInputTerminalStates(istream& is) {
        cout << "\nEnter new states for input terminals:" << endl;
        for (int i = 0; i < numInputs; ++i) {
            cout << "Input Terminal :" << i + 1 << endl;
            
            while (true) {
                cout << "Enter connection count: ";
                int count = inputTerminals[i].getConnectionCount();
                is >> count;
                if ((inputTerminals[i].getIsInput() && inputTerminals[i].getConnectionCount() == 1 || inputTerminals[i].getConnectionCount() == 0) || (!inputTerminals[i].getIsInput() && inputTerminals[i].getConnectionCount() <= 3 && inputTerminals[i].getConnectionCount() >= 0)) {
                    break;  
                }
                else {
                    cout << "Error: Invalid connection count. Please enter a valid value." << endl;
                }
            }

            while (true) {
                cout << "Enter signal state: ";
                int signal = inputTerminals[i].getSignalState();
                is >> signal;
                if (inputTerminals[i].getSignalState() == 0 || inputTerminals[i].getSignalState() == 1 || inputTerminals[i].getSignalState() == -1) {
                    break;  
                }
                else {
                    cout << "Error: Invalid signal state. Please enter 0, 1, or -1." << endl;
                }
            }
        }
    }

    // Метод для переопределения состояний всех выходных клемм
    void Class1::LogicalElement::updateOutputTerminalStates(istream& is) {
        cout << "\nEnter new states for output terminals:" << endl;
        for (int i = 0; i < numOutputs; ++i) {
            cout << "Output Terminal :" << i + 1 << endl;
          
            while (true) {
                cout << "Enter connection count: ";
                int count = outputTerminals[i].getConnectionCount();
                is >> count;
                if ((outputTerminals[i].getIsInput() && outputTerminals[i].getConnectionCount() == 1 || outputTerminals[i].getConnectionCount() == 0) || (!outputTerminals[i].getIsInput() && outputTerminals[i].getConnectionCount() <= 3 && outputTerminals[i].getConnectionCount() >= 0)) {
                    break;  
                }
                else {
                    cout << "Error: Invalid connection count. Please enter a valid value." << endl;
                }
            }

            while (true) {
                cout << "Enter signal state: ";
                int signal = outputTerminals[i].getSignalState();
                is >> signal;
                if (outputTerminals[i].getSignalState() == 0 || outputTerminals[i].getSignalState() == 1 || outputTerminals[i].getSignalState() == -1) {
                    break;  
                }
                else {
                    cout << "Error: Invalid signal state. Please enter 0, 1, or -1." << endl;
                }
            }
        }
    }
    
    // Вспомогательный метод для получения клеммы по индексу
    Class1::Terminal& Class1::LogicalElement::getTerminalByIndex(int index) {
        if (index >= 0 && index < numInputs + numOutputs) {
            return (index < numInputs) ? inputTerminals[index] : outputTerminals[index - numInputs];
        }
        else {
            cout << "Error: Invalid terminal index." << endl;
            // Возвращаем первую входную клемму по умолчанию
            return inputTerminals[0];
        }
    }

     const Class1::Terminal& Class1::LogicalElement::getTerminalByIndex(int index) const {
        if (index >= 0 && index < numInputs + numOutputs) {
            return (index < numInputs) ? inputTerminals[index] : outputTerminals[index - numInputs];
        }
        else {
            cerr << "Error: Invalid terminal index." << endl;
            // Возвращаем первую входную клемму по умолчанию
            return inputTerminals[0];
        }
    }

    Class1::Terminal& Class1::LogicalElement::operator[](int index) {
        return getTerminalByIndex(index);
    }

    const Class1::Terminal& Class1::LogicalElement::operator[](int index) const {
        return getTerminalByIndex(index);
    }


    Class1::LogicalElement::~LogicalElement() {
        delete[] inputTerminals;
        delete[] outputTerminals;
    }

    LogicalElement::LogicalElement(const LogicalElement& other) {
        numInputs = other.numInputs;
        numOutputs = other.numOutputs;

        inputTerminals = new Terminal[numInputs];
        for (int i = 0; i < numInputs; ++i) {
            inputTerminals[i] = other.inputTerminals[i];
        }

        outputTerminals = new Terminal[numOutputs];
        for (int i = 0; i < numOutputs; ++i) {
            outputTerminals[i] = other.outputTerminals[i];
        }
    }

    Class1::LogicalElement::LogicalElement(LogicalElement&& other) noexcept{
        numInputs = other.numInputs;
        numOutputs = other.numOutputs;

        inputTerminals = other.inputTerminals;
        other.inputTerminals = nullptr;

        outputTerminals = other.outputTerminals;
        other.outputTerminals = nullptr;
    }

    // Перемещающий "="
    Class1::LogicalElement& Class1::LogicalElement::operator=(LogicalElement&& other) noexcept{
        if (this != &other) {
            // Освобождаем ресурсы текущего объекта
            delete[] inputTerminals;
            delete[] outputTerminals;

            // Копируем данные из другого объекта
            numInputs = other.numInputs;
            numOutputs = other.numOutputs;
            inputTerminals = other.inputTerminals;
            outputTerminals = other.outputTerminals;

            // Обнуляем указатели у другого объекта, чтобы не удалить данные в деструкторе другого объекта
            other.numInputs = 0;
            other.numOutputs = 0;
            other.inputTerminals = nullptr;
            other.outputTerminals = nullptr;
        }

        return *this;
    }

    Class1::LogicalElement& Class1::LogicalElement::operator=(LogicalElement& other)  {
        if (this != &other) {
            // Освобождаем ресурсы текущего объекта
            Terminal* tmpI =nullptr, * tmpO=nullptr;
            try {
                tmpI = new Terminal[other.numInputs];
                tmpO = new Terminal[other.numInputs];
            }catch(std::bad_alloc& x)
            {
                delete[] tmpI;
                throw x;
            }
            
            delete[] inputTerminals;
            delete[] outputTerminals;

            inputTerminals = tmpI;
            outputTerminals = tmpO;

            // Копируем данные из другого объекта
            numInputs = other.numInputs;
            numOutputs = other.numOutputs;
            for (int i = 0; i < numInputs; ++i) {
                inputTerminals[i] = other.inputTerminals[i];
            }

           // outputTerminals = new Terminal[numOutputs];
            for (int i = 0; i < numOutputs; ++i) {
                outputTerminals[i] = other.outputTerminals[i];
            }
        }

        return *this;
    }

}