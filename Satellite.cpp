#include <iostream>
#include <stdexcept>
#include <sstream>

class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() {}
};

class ILogger {
public:
    virtual void log(const std::string& message) const = 0;
    virtual ~ILogger() {}
};


class ConsoleLogger : public ILogger {
public:
    void log(const std::string& message) const override {
        std::cout << message << std::endl;
    }
};

class Satellite {
private:
    std::string orientation;
    bool solarPanelsActive;
    int dataCollected;

public:
    Satellite() : orientation("North"), solarPanelsActive(false), dataCollected(0) {}

    void rotate(const std::string& direction) {
        orientation = direction;
    }

    void activatePanels() {
        solarPanelsActive = true;
    }

    void deactivatePanels() {
        solarPanelsActive = false;
    }

    void collectData() {
        if (solarPanelsActive) {
            dataCollected += 10;
        } else {
            throw std::logic_error("Solar panels are inactive. Cannot collect data.");
        }
    }

    std::string getOrientation() const {
        return orientation;
    }

    std::string getSolarPanelStatus() const {
        return solarPanelsActive ? "Active" : "Inactive";
    }

    int getDataCollected() const {
        return dataCollected;
    }
};

class CommandExecutor {
private:
    Satellite& satellite;
    ILogger& logger;

public:
    CommandExecutor(Satellite& satellite, ILogger& logger) : satellite(satellite), logger(logger) {}

    void executeCommand(const std::string& input) {
        std::istringstream iss(input);
        std::string action;
        std::string argument;
        iss >> action;

        try {
            if (action == "rotate") {
                iss >> argument;
                satellite.rotate(argument);
                logger.log("Satellite rotated to " + argument + " direction.");
            } else if (action == "activate") {
                satellite.activatePanels();
                logger.log("Solar panels activated.");
            } else if (action == "deactivate") {
                satellite.deactivatePanels();
                logger.log("Solar panels deactivated.");
            } else if (action == "collect") {
                satellite.collectData();
                logger.log("Data collected.");
            } else if (action == "status") {
                logger.log("Orientation: " + satellite.getOrientation());
                logger.log("Solar Panels: " + satellite.getSolarPanelStatus());
                logger.log("Data Collected: " + std::to_string(satellite.getDataCollected()));
            } else {
                throw std::invalid_argument("Invalid command!");
            }
        } catch (const std::exception& e) {
            logger.log(e.what());
        }
    }
};

int main() {
    Satellite satellite;
    ConsoleLogger logger;
    CommandExecutor executor(satellite, logger);

    logger.log("Initial State:");
    logger.log("Orientation: " + satellite.getOrientation());
    logger.log("Solar Panels: " + satellite.getSolarPanelStatus());
    logger.log("Data Collected: " + std::to_string(satellite.getDataCollected()));

    std::string input;
    while (true) {
        std::cout << "\nEnter command:\n1. rotate\n2. activate\n3. deactivate\n4. collect\n5. status\n6. exit\n";
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }

        executor.executeCommand(input);
    }

    return 0;
}
