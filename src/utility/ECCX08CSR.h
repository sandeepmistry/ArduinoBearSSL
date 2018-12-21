/*
 * Copyright (c) 2018 Arduino SA. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _ECCX08_CSR_H_
#define _ECCX08_CSR_H_

#include <Arduino.h>

class ECCX08CSRClass {
public:
  ECCX08CSRClass();
  virtual ~ECCX08CSRClass();

  int begin(int slot, bool newPrivateKey = true);
  String end();

  void setCountryName(const char *countryName);
  void setCountryName(const String& countryName) { setCountryName(countryName.c_str()); }

  void setStateProvinceName(const char* stateProvinceName);
  void setStateProvinceName(const String& stateProvinceName) { setStateProvinceName(stateProvinceName.c_str()); }

  void setLocalityName(const char* localityName);
  void setLocalityName(const String& localityName) { setLocalityName(localityName.c_str()); }

  void setOrganizationName(const char* organizationName);
  void setOrganizationName(const String& organizationName) { setOrganizationName(organizationName.c_str()); }

  void setOrganizationalUnitName(const char* organizationalUnitName);
  void setOrganizationalUnitName(const String& organizationalUnitName) { setOrganizationalUnitName(organizationalUnitName.c_str()); }

  void setCommonName(const char* commonName);
  void setCommonName(const String& commonName) { setCommonName(commonName.c_str()); }

private:
  int encodeCsrInfo(byte buffer[]);
  int encodeEcdsaSignature(const byte signature[], byte buffer[]);

  int encodeName(const char* name, int length, int type, byte buffer[]);
  int encodePublicKey(byte buffer[]);

private:
  int _slot;

  String _countryName;
  String _stateProvinceName;
  String _localityName;
  String _organizationName;
  String _organizationalUnitName;
  String _commonName;

  byte _publicKey[64];
};

extern ECCX08CSRClass ECCX08CSR;

#endif
