#include "Settings.hpp"

#include <cpptoml.h>
#include <string>
#include <windows.h>

#include "Note.hpp"
#include <iostream>

Settings::Settings()
{
}

Settings::~Settings()
{
}

bool Settings::loadFromFile(const std::string& path)
{

  try {
    auto config = cpptoml::parse_file(path);
    auto keyMapConfig = config->get_table("keymap");

    for(auto it = keyMapConfig->begin(); it != keyMapConfig->end(); ++it) {
      auto noteStr = it->first;
      // first -> Note, second -> key string
      if (auto note = Note::fromString(noteStr)) {
        auto keyStr = it->second->as<std::string>()->get();
        short keyscan = VkKeyScan(*(keyStr.c_str()));
        auto keycode = LOBYTE(keyscan);
        m_map[noteStr] = keycode;
      }
    }

    return true;
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return false;
  }
}

std::optional<short> Settings::getMappingNote(const std::string& noteStr)
{
  auto it = m_map.find(noteStr);
  if (it != m_map.end()) {
    return m_map[noteStr];
  }
  return {};
}