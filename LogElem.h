#pragma once
#ifndef LOGELEM_H
#define LOGELEM_H
#include <iostream>
#include <iomanip>
#include<string>
#include "C:\Users\Марат\Prog\LAB2_basic\LAB2_basic\terminal.h"
using namespace std;

namespace Class1 {
    class LogicalElement {
    private:
        Terminal* inputTerminals;
        Terminal* outputTerminals;
        int numInputs;
        int numOutputs;

    public:
        LogicalElement();
        LogicalElement(int numInputs, int numOutputs);
        LogicalElement(const string* terminalDescriptions, int length);

        int getNumInputs() const;
        int getNumOutputs() const;

        Terminal& getInputTerminal(int index);
        Terminal& getOutputTerminal(int index);

        void addInputTerminal();
        void addOutputTerminal();

        void formatAsPseudoGraphic() const;

        void operator>>(LogicalElement& logicElement);

        istream& inputState(istream& is);
        ostream& outputState(ostream& os) const;

        void updateInputTerminalStates(istream& is);
        void updateOutputTerminalStates(istream& is);

        Terminal& getTerminalByIndex(int index);
        const Terminal& getTerminalByIndex(int index) const;
        Terminal& operator[](int index);
        const Terminal& operator[](int index) const;
        ~LogicalElement();

        LogicalElement(const LogicalElement& other);
        LogicalElement(LogicalElement&& other) noexcept;
        LogicalElement& operator=(LogicalElement&& other);
        LogicalElement& operator=(LogicalElement& other) noexcept;
    };

}
#endif LOGELEM_H
