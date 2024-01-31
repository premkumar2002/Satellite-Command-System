#include <iostream>
#include <stdexcept>
#include <sstream>

using namespace std;

class Satellite {
private:
    string orientation;
    bool solarPanelsActive;
    int dataCollected;

public:
    Satellite() : orientation("North"), solarPanelsActive(false), dataCollected(0) {}

    void rotate(const string& direction) {
        orientation = direction;
        cout << "Satellite rotated to " + direction + " direction." << endl;
    }

    void activatePanels() {
        solarPanelsActive = true;
        cout << "Solar panels activated." << endl;
    }

    void deactivatePanels() {
        solarPanelsActive = false;
        cout << "Solar panels deactivated." << endl;
    }

    void collectData() {
        if (solarPanelsActive) {
            dataCollected += 10;
            cout << "Data collected." << endl;
        } else {
            throw logic_error("Solar panels are inactive. Cannot collect data.");
        }
    }

    string getOrientation() const {
        return orientation;
    }

    string getSolarPanelStatus() const {
        return solarPanelsActive ? "Active" : "Inactive";
    }

    int getDataCollected() const {
        return dataCollected;
    }

    void printStatus() const {
        cout << "Orientation: " + orientation << endl;
        cout << "Solar Panels: " + getSolarPanelStatus() << endl;
        cout << "Data Collected: " + to_string(dataCollected) << endl;
    }
};

int main() {
    Satellite satellite;

    cout << "Initial State:" << endl;
    satellite.printStatus();

    string input;
    while (true) {
        cout << "\nEnter command:\n1. rotate\n2. activate\n3. deactivate\n4. collect\n5. status\n6. exit\n";
        getline(cin, input);

        if (input == "exit") {
            break;
        }

        istringstream iss(input);
        string action, argument;
        iss >> action;

        try {
            if (action == "rotate") {
                iss >> argument;
                satellite.rotate(argument);
            } else if (action == "activate") {
                satellite.activatePanels();
            } else if (action == "deactivate") {
                satellite.deactivatePanels();
            } else if (action == "collect") {
                satellite.collectData();
            } else if (action == "status") {
                satellite.printStatus();
            } else {
                throw invalid_argument("Invalid command!");
            }
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}
