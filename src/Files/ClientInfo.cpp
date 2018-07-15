#include "Files/ClientInfo.h"

#ifndef WIN32
#include <strings.h>
#define _strcmpi strcasecmp
#endif

#include "Common/ErrorMsg.h"
#include "Common/Globals.h"
#include "Common/server_type.h"
#include "Common/service_type.h"
#include "File.h"

ClientInfo::ClientInfo(const std::string& file_path) : file_path_(file_path) {}

bool ClientInfo::Load() {
  using namespace tinyxml2;

  CFile fp;
  if (!fp.Open(file_path_, 0)) {
    return false;
  }

  tinyxml2::XMLDocument document;
  if (document.Parse(reinterpret_cast<const char*>(fp.GetBuf()),
                     fp.GetLength()) != XML_SUCCESS) {
    fp.Close();
    return false;
  }

  SetOption(document);
  fp.Close();

  return true;
}

void ClientInfo::SetOption(const tinyxml2::XMLDocument& document) {
  using namespace tinyxml2;

  const XMLElement* clientinfo = document.FirstChildElement("clientinfo");
  if (!clientinfo) {
    return;
  }

  const XMLElement* servicetype = clientinfo->FirstChildElement("servicetype");
  if (servicetype) {
    const char* servicetype_str = servicetype->GetText();
    if (!_strcmpi(servicetype_str, "korea")) {
      g_serviceType = ServiceType::kKorea;
    } else if (!_strcmpi(servicetype_str, "america")) {
      g_serviceType = ServiceType::kAmerica;
    } else if (!_strcmpi(servicetype_str, "japan")) {
      g_serviceType = ServiceType::kJapan;
    } else if (!_strcmpi(servicetype_str, "china")) {
      g_serviceType = ServiceType::kChina;
    } else if (!_strcmpi(servicetype_str, "taiwan")) {
      g_serviceType = ServiceType::kTaiwan;
    } else if (!_strcmpi(servicetype_str, "thai")) {
      g_serviceType = ServiceType::kThai;
    } else if (!_strcmpi(servicetype_str, "indonesia")) {
      g_serviceType = ServiceType::kIndonesia;
    } else if (!_strcmpi(servicetype_str, "philippine")) {
      g_serviceType = ServiceType::kPhilippine;
    } else if (!_strcmpi(servicetype_str, "malaysia")) {
      g_serviceType = ServiceType::kMalaysia;
    } else if (!_strcmpi(servicetype_str, "singapore")) {
      g_serviceType = ServiceType::kSingapore;
    } else if (!_strcmpi(servicetype_str, "germany")) {
      g_serviceType = ServiceType::kGermany;
    } else if (!_strcmpi(servicetype_str, "india")) {
      g_serviceType = ServiceType::kIndia;
    } else if (!_strcmpi(servicetype_str, "brazil")) {
      g_serviceType = ServiceType::kBrazil;
    } else if (!_strcmpi(servicetype_str, "autralia")) {
      g_serviceType = ServiceType::kAustralia;
    } else if (!_strcmpi(servicetype_str, "russia")) {
      g_serviceType = ServiceType::kRussia;
    } else if (!_strcmpi(servicetype_str, "vietnam")) {
      g_serviceType = ServiceType::kVietnam;
    } else if (!_strcmpi(servicetype_str, "chile")) {
      g_serviceType = ServiceType::kChile;
    } else if (!_strcmpi(servicetype_str, "france")) {
      g_serviceType = ServiceType::kFrance;
    } else {
      ErrorMsg("No ServiceType !");
    }

    SetLoginStartMode();
  }

  const XMLElement* servertype = clientinfo->FirstChildElement("servertype");
  if (servertype) {
    const char* servertype_str = servertype->GetText();
    if (!_strcmpi(servertype_str, "primary")) {
      g_serverType = ServerType::kPrimary;
    } else if (!_strcmpi(servertype_str, "sakray")) {
      g_serverType = ServerType::kSakray;
    } else if (!_strcmpi(servertype_str, "local")) {
      g_serverType = ServerType::kLocal;
    } else if (!_strcmpi(servertype_str, "pk")) {
      g_serverType = ServerType::kPK;
    } else {
      ErrorMsg("No ServerType !");
    }
  }

  if (clientinfo->FirstChildElement("hideaccountlist")) {
    g_hideAccountList = true;
  }

  if (clientinfo->FirstChildElement("passwordencrypt")) {
    g_passwordEncrypt = true;
  }

  if (clientinfo->FirstChildElement("passwordencrypt2")) {
    g_passwordEncrypt = true;
    g_passwordEncrypt2 = true;
  }

  if (clientinfo->FirstChildElement("extendedslot")) {
    g_extendedSlot = true;
  }

  if (clientinfo->FirstChildElement("readfolder")) {
    g_readFolderFirst = true;
  }

  // Loading screens
  const XMLElement* loading = clientinfo->FirstChildElement("loading");
  if (loading) {
    for (const XMLElement* e = loading->FirstChildElement("image");
         e != nullptr; e = e->NextSiblingElement("image")) {
      std::string name = e->GetText();
      s_loadingScreenList.push_back(name);
    }
  }

  // TODO: Iterate through connections
  const XMLElement* connection = clientinfo->FirstChildElement("connection");
  if (connection) {
    const XMLElement* address = connection->FirstChildElement("address");
    if (address) {
      strncpy(g_accountAddr, address->GetText(), sizeof(g_accountAddr));
    }

    const XMLElement* port = connection->FirstChildElement("port");
    if (port) {
      strncpy(g_accountPort, port->GetText(), sizeof(g_accountPort));
    }
  }
}

void ClientInfo::SetLoginStartMode() {
  switch (g_serviceType) {
    case ServiceType::kKorea:
    case ServiceType::kAmerica:
      g_loginStartMode = 0;
      break;
    case ServiceType::kJapan:
    case ServiceType::kChina:
    case ServiceType::kThai:
      g_loginStartMode = 2;
      break;
    case ServiceType::kTaiwan:
    case ServiceType::kIndonesia:
    case ServiceType::kMalaysia:
    case ServiceType::kSingapore:
    case ServiceType::kBrazil:
    case ServiceType::kRussia:
      g_loginStartMode = 1;
  };
}
