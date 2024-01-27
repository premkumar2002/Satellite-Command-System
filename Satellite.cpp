#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Loggers interface
class ILogger {
  public:
    virtual void log(string message) = 0;
};

// Console logger 
class ConsoleLogger : public ILogger {
  public:
    void log(string message) override {
      cout << "[LOG] " << message << endl; 
    }
};

// Command interface
class ICommand {
  public:
    virtual void execute() = 0;
};

class Satellite {
    private:
        string orientation;
        string solarPanelStatus;
        int dataCollected;

    public:
        Satellite() {
            orientation = "North";
            solarPanelStatus = "Inactive";
            dataCollected = 0;
        }

        void rotate(string direction) {
            orientation = direction;
        }

        void activatePanels() {
            solarPanelStatus = "Active"; 
        }

        void deactivatePanels() {
            solarPanelStatus = "Inactive";
        }

        void collectData() {
          if(solarPanelStatus == "Active") {
            dataCollected = dataCollected + 10; 
          } else {
            cout << "Cannot collect data, solar panels deactivated" << endl;
          }
}

        string getOrientation() {
            return orientation; 
        }
        
        string getSolarPanelStatus() {
            return solarPanelStatus;
        }
        
        int getDataCollected() {
            return dataCollected;
        }
        void setDataCollected(int newData) {
            dataCollected = newData;
        }

};

void showStatus(Satellite satellite) {
    cout << "Orientation: " << satellite.getOrientation() << endl;
    cout << "Solar Panels: " << satellite.getSolarPanelStatus() << endl;
    cout << "Data Collected: " << satellite.getDataCollected() << endl;
}

class CollectDataCommand : public ICommand {
  public:
    CollectDataCommand(Satellite* satellite) {
      this->satellite = satellite;  
    }

    void execute() override {
      if(satellite->getSolarPanelStatus() == "Active") { 
        int dataCollected = satellite->getDataCollected();
        satellite->setDataCollected(dataCollected + 10);
      }
    }

  private:
    Satellite* satellite;
};


class RotateCommand : public ICommand {
  public:  
    RotateCommand(Satellite* satellite, string direction) {
      this->satellite = satellite;
      this->direction = direction;
    }

    void execute() override {
      satellite->rotate(direction); 
    }

  private:
    Satellite* satellite;
    string direction;
};

class ActivatePanelCommand : public ICommand {

  public:
    ActivatePanelCommand(Satellite* satellite) {
      this->satellite = satellite;  
    }

    void execute() override {
      satellite->activatePanels(); 
    }

  private:
    Satellite* satellite;
};

class ShowStatusCommand : public ICommand {

  public:
    ShowStatusCommand(Satellite* sat) {
      satellite = sat;
    }

    void execute() override {
      showStatus(*satellite);
    }

  private:
    Satellite* satellite;  
};

class CommandExecutor {
  public:
    void setLogger(ILogger* logger) {
      this->logger = logger;
    }

    void executeCommand(ICommand* command) {
      try {
        command->execute();
      } catch(exception& e) {
        logger->log("Command failed: " + string(e.what())); 
      }
    }

  private:
    ILogger* logger;
};


int main() {

  Satellite satellite;
  CommandExecutor executor;
  executor.setLogger(new ConsoleLogger());

  while(true) {
    string command;

    cout << "Enter command (rotate, activate, collect, status, exit): ";
    cin >> command;

    if(command == "exit") {
      break;
    }
    else if(command == "rotate") {
      string dir;
      cin >> dir;
      executor.executeCommand(new RotateCommand(&satellite, dir));

    } else if(command == "activate") {
      executor.executeCommand(new ActivatePanelCommand(&satellite));
    
    } else if(command == "status") {
    executor.executeCommand(new ShowStatusCommand(&satellite));
  }
  } 
}