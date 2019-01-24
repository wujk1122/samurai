
#include "precision.h"
#include "VarDriver3D.h"
#include <iostream>
#include <QtCore>
#include <QtXml>

#include "Xml.h"

void usage() {
  std::cout << "Usage: samurai <samurai_configuration.xml>" << std::endl;
}

int main (int argc, char *argv[]) {
	
  // Read the command line argument to get the XML configuration file

  switch (argc) {
    
  case 1:
    usage();
    return EXIT_FAILURE;
    break;
    
  case 2:
    QDomDocument *domDoc = readXmlConfig(argv[1]);
    if (domDoc == NULL)
      return EXIT_FAILURE;
    
    QDomElement root = domDoc->documentElement();
    
    // Generic driver which will be instanced by the configuration specification
    VarDriver *driver = new VarDriver3D();
    
    // Make sure we were able to create a driver, then drive
    if (driver != NULL) {
      // Do the analysis
      if(!driver->initialize(root)) {
	delete driver;
	return EXIT_FAILURE;
      }
      if(!driver->run()) {
	delete driver;
	return EXIT_FAILURE;
      }
      if(!driver->finalize()) {
	delete driver;
	return EXIT_FAILURE;
      }
      delete driver;
      std::cout << "Analysis successful!\n";
      return EXIT_SUCCESS;
    } else {
      std:: cout << "No run mode found!" << std::endl;
      return EXIT_FAILURE;
    }
    break;
    
  default:
    
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

