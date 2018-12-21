#include <ArduinoECCX08.h>
#include <ArduinoBearSSL.h>
#include <utility/ECCX08CSR.h>
#include <utility/ECCX08TLSConfig.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!ECCX08.begin()) {
    Serial.println("No ECC508 present!");
    while (1);
  }

  Serial.print("ECCX08 Serial Number = ");
  Serial.println(ECCX08.serialNumber());
  Serial.println();

  if (!ECCX08.locked()) {
    String lock = promptAndReadLine("The ECCX08 on your board is not locked, would you like to configure and lock it now? (y/N): ");

    if (!lock.startsWith("y")) {
      Serial.println("Unfortunately you can't proceed without locking it :(");
      while (1);
    }

    if (!ECCX08.writeConfiguration(DEFAULT_ECCX08_TLS_CONFIG)) {
      Serial.println("Writing ECCX08 configuration failed!");
      while (1);
    }

    if (!ECCX08.lock()) {
      Serial.println("Locking ECC508 configuration failed!");
      while (1);
    }

    Serial.println("ECCX08 locked successfully");
    Serial.println();
  }

  Serial.println("Hi there, in order to generate a new CSR for your board, we'll need the following information ...");
  Serial.println();

  String country            = promptAndReadLine("Country Name (2 letter code): ");
  String stateOrProvince    = promptAndReadLine("State or Province Name (full name): ");
  String locality           = promptAndReadLine("Locality Name (eg, city): ");
  String organization       = promptAndReadLine("Organization Name (eg, company): ");
  String organizationalUnit = promptAndReadLine("Organizational Unit Name (eg, section): ");
  String common             = promptAndReadLine("Common Name (e.g. server FQDN or YOUR name): ");
  String slot               = promptAndReadLine("What ECC508 slots would you like to use? (0 - 4): ");
  String generateNewKey     = promptAndReadLine("Would you like to generate a new private key? (y/N): ");

  Serial.println();

  generateNewKey.toLowerCase();

  if (!ECCX08CSR.begin(slot.toInt(), generateNewKey.startsWith("y"))) {
    Serial.println("Error starting CSR generation!");
    while (1);
  }

  ECCX08CSR.setCountryName(country);
  ECCX08CSR.setStateProvinceName(stateOrProvince);
  ECCX08CSR.setLocalityName(locality);
  ECCX08CSR.setOrganizationName(organization);
  ECCX08CSR.setOrganizationalUnitName(organizationalUnit);
  ECCX08CSR.setCommonName(common);

  String csr = ECCX08CSR.end();

  if (!csr) {
    Serial.println("Error generating CSR!");
    while (1);
  }

  Serial.println("Here's your CSR, enjoy!");
  Serial.println();
  Serial.println(csr);
}

void loop() {
  // do nothing
}


String promptAndReadLine(const char* prompt) {
  Serial.print(prompt);
  String s = readLine();
  Serial.println(s);

  return s;
}

String readLine() {
  String line;

  while (1) {
    if (Serial.available()) {
      char c = Serial.read();

      if (c == '\r') {
        // ignore
      } else if (c == '\n') {
        break;
      }

      line += c;
    }
  }

  return line;
}
